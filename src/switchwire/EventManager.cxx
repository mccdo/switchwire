/*************** <auto-copyright.rb BEGIN do not edit this line> **************
 *
 * Copyright 2012-2012 by Ames Laboratory
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 *************** <auto-copyright.rb END do not edit this line> ***************/
#include <Poco/Data/Session.h>
#include <Poco/Data/SQLite/Connector.h>
#include <Poco/Data/DataException.h>
#include <Poco/Data/RecordSet.h>
#include <Poco/SingletonHolder.h>

#include <switchwire/EventManager.h>

#include <iostream>

using boost::shared_ptr;
using boost::weak_ptr;
using boost::signals2::scoped_connection;
using boost::signals2::shared_connection_block;

//#define DEBUG_DESTRUCTOR

namespace switchwire
{

namespace
{
    static Poco::SingletonHolder< EventManager > singleton;
}

EventManager* EventManager::instance()
{
    return singleton.get();
}

////////////////////////////////////////////////////////////////////////////////
EventManager::EventManager():
    mMonotonicID(0),
    m_logger( Poco::Logger::get("switchwire::EventManager") ),
    m_shutdown( false )
{
    m_logStream = LogStreamPtr( new Poco::LogStream( m_logger ) );

    SW_LOG_TRACE( "ctor" );

    // Open an in-memory database to allow efficient searches of existing signals
    Poco::Data::SQLite::Connector::registerConnector();
    mSession = new Poco::Data::Session( "SQLite", ":memory:" );
    ( *mSession ) << "CREATE TABLE signals (id INTEGER PRIMARY KEY, name TEXT, type INTEGER)",
            Poco::Data::now;

    // Create a table to store slots that have requested connection to a certain signal
    // or signal pattern that hasn't been registered yet
    ( *mSession ) << "CREATE TABLE slots (id INTEGER PRIMARY KEY, mapID INTEGER, pattern TEXT, type INTEGER, priority INTEGER)",
            Poco::Data::now;
}
////////////////////////////////////////////////////////////////////////////////
EventManager::~EventManager()
{
    Shutdown();

    // Delete all our signals
    {
//        std::map< std::string, boost::weak_ptr< EventBase > >::const_iterator iter = mSignals.begin();
//        std::map< std::string, boost::weak_ptr< EventBase > >::const_iterator max = mSignals.end();

//        while( iter != max )
//        {
//            delete ( iter->second );
//            ++iter;
//        }
    }
}
////////////////////////////////////////////////////////////////////////////////
void EventManager::LogAllConnections()
{
    try
    {
        Poco::Data::Statement statement( *mSession );
        statement << "SELECT * FROM slots";
        statement.execute();
        Poco::Data::RecordSet rs( statement );

        size_t cols = rs.columnCount();

        SW_LOG_FATAL( "What follows is a dump of all connected slots in the form (index, id, pattern, type, prio)." );
        bool more = rs.moveFirst();
        while (more)
        {
            std::string rowText;
            for (std::size_t col = 0; col < cols; ++col)
            {
                rowText += rs[col].convert<std::string>() + ",";
            }
            SW_LOG_FATAL( rowText );
            more = rs.moveNext();
        }
    }
    catch( ... )
    {
        std::cout << "EventManager::LogAllConnections exception." << std::endl;
    }
}
////////////////////////////////////////////////////////////////////////////////
void EventManager::Shutdown()
{
    if( m_shutdown )
    {
        return;
    }

    SW_LOG_TRACE( "dtor" );
#ifdef DEBUG_DESTRUCTOR
    LogAllConnections();
#endif

    // Delete all our stored slots
    {
        std::map< int, SlotWrapperBasePtr >::iterator iter = mExactSlotMap.begin();
        std::map< int, SlotWrapperBasePtr >::const_iterator max = mExactSlotMap.end();

        while( iter != max )
        {
#ifdef DEBUG_DESTRUCTOR
            SW_LOG_FATAL( "Deleting slot with id " << iter->first );
#endif
            iter->second = SlotWrapperBasePtr();
            ++iter;
        }

        mExactSlotMap.clear();
    }

    try
    {
        Poco::Data::SQLite::Connector::unregisterConnector();
    }
    catch( ... )
    {
        ;
    }

    m_shutdown = true;
}
////////////////////////////////////////////////////////////////////////////////
void EventManager::RegisterSignal( EventBase *sig, const std::string& sigName, SignalType sigType )
{
    SW_LOG_DEBUG( "RegisterSignal: " << sigName );

    // Add this signal to the lookup table
    try
    {
        // Check whether a signal with this name already exists
        std::map< std::string, boost::weak_ptr< EventBase > >::iterator iter = mSignals.find( sigName );
        if( iter != mSignals.end() )
        {
            // Check whether signal is still valid; remove if not.
            shared_ptr<EventBase> eventLock = iter->second.lock();
            if( !eventLock )
            {
                SW_LOG_INFO( "RegisterSignal: Removing expired Event/Signal \""
                          << sigName << "\"" );
                mSignals.erase( iter );
            }
            else
            {
                SW_LOG_WARNING( "RegisterSignal: " << sigName
                             << " will hide previous signal with same name" );
            }

            ( *mSession ) << "UPDATE signals SET type=:type WHERE name=:name",
                    Poco::Data::use( sigType ),
                    Poco::Data::use( sigName ),
                    Poco::Data::now;
        }
        else
        {
            SW_LOG_DEBUG( "RegisterSignal: Registering new signal " << sigName );

            ( *mSession ) << "INSERT INTO signals (name, type) VALUES (:name,:type)",
                    Poco::Data::use( sigName ),
                    Poco::Data::use( sigType ),
                    Poco::Data::now;
        }
    }
    catch( Poco::Data::DataException& ex )
    {
         SW_LOG_ERROR( ex.displayText() );
    }

    // Store the signal and weakptr to EventBase in the signal map
     mSignals[sigName] = sig->GetWeakPtr();

    ConnectToPreviousSlots( sigName );
}
////////////////////////////////////////////////////////////////////////////////
void EventManager::ConnectToPreviousSlots( const std::string& sigName )
{
    SW_LOG_TRACE( "ConnectToPreviousSlots" );

    std::vector< int > ids;
    std::vector< int > priorities;
    GetSlotMatches( sigName, ids, priorities );

    // Iterate through result set and attempt to connect to the matching slots
    std::vector< int >::iterator idsIter = ids.begin();
    std::vector< int >::iterator prioritiesIter = priorities.begin();
    while( idsIter != ids.end() )
    {
        SlotWrapperBasePtr slot = mExactSlotMap.find( *idsIter )->second;
        weak_ptr< ScopedConnectionList > wConnectionsPtr
                = mExactSlotConnections.find( *idsIter )->second;

        if( shared_ptr< ScopedConnectionList > sConnectionsPtr = wConnectionsPtr.lock() )
        {
           _ConnectSignal( sigName, slot, *(sConnectionsPtr.get()), *prioritiesIter, false );
        }
        else
        {
            // If we were unable to lock the weak ptr, the underlying object
            // must have been destroyed. Remove this entry from the database
            // so we don't have to deal with it in future.
            try
            {
                ( *mSession ) << "DELETE FROM slots WHERE mapID=:id",
                        Poco::Data::use( *idsIter ),
                        Poco::Data::now;
            }
            catch( Poco::Data::DataException& ex )
            {
                std::cout << ex.displayText() << std::endl;
            }

            // We can also remove this entry from mExactSlotMap and free up
            // associated memory
            std::map< int, SlotWrapperBasePtr >::iterator slotIter =
                    mExactSlotMap.find( *idsIter );
            if( slotIter != mExactSlotMap.end() )
            {
                //delete( slotIter->second );
                mExactSlotMap.erase( slotIter );
            }
        }
        ++idsIter;
        ++prioritiesIter;
    }
}
////////////////////////////////////////////////////////////////////////////////
void EventManager::ConnectSignal( const std::string& sigName,
                                  SlotWrapperBasePtr slot,
                                  ScopedConnectionList& connections,
                                  int priority )
{
    _ConnectSignal( sigName, slot, connections, priority, true );
}
////////////////////////////////////////////////////////////////////////////////
void EventManager::_ConnectSignal( const std::string& sigName,
                                  SlotWrapperBasePtr slot,
                                  ScopedConnectionList& connections,
                                  int priority,
                                  bool store )
{
    SW_LOG_TRACE( "_ConnectSignal" );
    // Find the appropriate SignalWrapperBase; using non-const iterator because
    // we will erase this entry if it has expired (can't lock weak ptr).
    std::map< std::string, boost::weak_ptr< EventBase > >::iterator iter = mSignals.find( sigName );
    if( iter != mSignals.end() )
    {
        weak_ptr<EventBase> event = iter->second;
        // Check whether signal is still valid; remove if not.
        shared_ptr<EventBase> eventLock = event.lock();
        if( !eventLock )
        {
            SW_LOG_INFO( "_ConnectSignal: Removing expired Event/Signal \""
                      << sigName << "\"" );
            mSignals.erase( iter );
            ( *mSession ) << "DELETE FROM signals where name=:name",
                    Poco::Data::use( sigName ),
                    Poco::Data::now;
            return;
        }

        SW_LOG_DEBUG( "_ConnectSignal: Connecting " << slot << " to signal "
                << sigName << " (" << eventLock->GetSignalAddress() << ")" );
        // Tell the SignalWrapper to connect its signal to this slot
        if( eventLock->ConnectSlot( slot, connections, priority ) )
        {
            SW_LOG_DEBUG( "_ConnectSignal: Connection successful" );
            //Connection was successful; store the details
            StoreConnection( connections, event );

            // Check whether there is currently a strong monopoly on this signal.
            // If so, immediately block the connection that was just made.
            StrongMonopolies_type::iterator mIter = mStrongMonopolies.find( event );
            if( mIter != mStrongMonopolies.end() )
            {
                if( shared_ptr< ConnectionMonopoly > monopoly = mIter->second.lock() )
                {
                    shared_ptr< shared_connection_block >
                            blocker( new shared_connection_block( *( connections.GetLastConnection() ) ) );
                    monopoly->AddBlocker( blocker );
                }
                else
                {
                    // Monopoly must have already been ended; remove this entry.
                    mStrongMonopolies.erase( mIter );
                }
            }
        }
        else
        {
            SW_LOG_ERROR( "_ConnectSignal: Connection to " << sigName << " failed. Wrong signature perhaps?" );
        }
    }
    else
    {
        SW_LOG_ERROR( "_ConnectSignal: Signal " << sigName << " not found. Has it been registered? Do the names match?" );
    }

    // Copy this slot off for later async connections
    if( store )
    {
        StoreSlot( sigName, slot, connections, EventManager::unspecified_SignalType, priority );
    }
}
////////////////////////////////////////////////////////////////////////////////
void EventManager::ConnectSignals( const std::string& stringToMatch,
                                   SlotWrapperBasePtr slot,
                                   ScopedConnectionList& connections,
                                   SignalType sigType,
                                   int priority )
{
    SW_LOG_DEBUG( "ConnectSignals: " << stringToMatch << " " << slot );
    std::vector< std::string > names;
    GetMatches( stringToMatch, sigType, names );

    // Iterate through result set and attempt to connect to the matching signals
    std::vector< std::string >::iterator namesIter = names.begin();
    while( namesIter != names.end() )
    {
        // Connect to the signal, but don't store slot details for each connection
        _ConnectSignal( ( *namesIter ), slot, connections, priority, false );
        namesIter++;
    }

    // Store slot details for general pattern
    StoreSlot( stringToMatch, slot, connections, sigType, priority );
}
////////////////////////////////////////////////////////////////////////////////
void EventManager::StoreSlot( const std::string& sigName,
                              SlotWrapperBasePtr slot,
                              ScopedConnectionList& connections,
                              int type,
                              int priority )
{
    SW_LOG_TRACE( "StoreSlot " << sigName << " " << slot );

    mExactSlotMap[ mMonotonicID ] = slot;

    mExactSlotConnections[ mMonotonicID ] = connections.GetWeakPtr();

    // Add this slot to the lookup table
    try
    {
        ( *mSession ) << "INSERT INTO slots (mapID, pattern, type, priority) VALUES (:id,:pattern,:type,:priority)",
                Poco::Data::use( mMonotonicID ),
                Poco::Data::use( sigName ),
                Poco::Data::use( type ),
                Poco::Data::use( priority ),
                Poco::Data::now;
    }
    catch( Poco::Data::DataException& ex )
    {
         SW_LOG_ERROR( ex.displayText() );
    }

    // Increment the ID so we never have name clashes when things get deleted
    // from the middle.
    ++mMonotonicID;
}
////////////////////////////////////////////////////////////////////////////////
void EventManager::GetMatches( const std::string stringToMatch, SignalType sigType, std::vector< std::string >& names )
{
    SW_LOG_TRACE( "GetMatches: " << stringToMatch << " " << sigType );
    try
    {
        Poco::Data::Statement statement( *mSession );
        statement << "SELECT name FROM signals WHERE name LIKE :name",
                Poco::Data::use( stringToMatch );
        if( sigType != any_SignalType )
        {
            statement << " AND type=:type",
                    Poco::Data::use( sigType );
        }
        statement, Poco::Data::into( names );
        statement.execute();
    }
    catch( Poco::Data::DataException& ex )
    {
        SW_LOG_ERROR( ex.displayText() );
    }
}
////////////////////////////////////////////////////////////////////////////////
void EventManager::GetSlotMatches( const std::string& sigName, std::vector< int >& ids, std::vector< int >& priorities )
{
    SW_LOG_TRACE( "GetSlotMatches: " << sigName );
    // TODO: Needs slightly more subtle matching that includes signal type
    try
    {
        Poco::Data::Statement statement( *mSession );
        statement << "SELECT mapID FROM slots WHERE :pattern LIKE pattern",
                Poco::Data::use( sigName ),
                Poco::Data::into( ids );
        statement.execute();
        int priority = 3;
        for( size_t count = 0; count < ids.size(); ++count )
        {
            ( *mSession ) << "SELECT priority FROM slots WHERE mapID=:id",
            Poco::Data::use( ids.at( count ) ),
            Poco::Data::into( priority ),
            Poco::Data::now;
            priorities.push_back( priority );
        }
    }
    catch( Poco::Data::DataException& ex )
    {
         SW_LOG_ERROR( ex.displayText() );
    }
}
////////////////////////////////////////////////////////////////////////////////
void EventManager::StoreConnection( ScopedConnectionList& connections, boost::weak_ptr<EventBase> event )
{
    SW_LOG_TRACE( "StoreConnection" );
    // Only store the connection if it represents an active connection
    boost::shared_ptr< boost::signals2::scoped_connection > connection = connections.GetLastConnection();
    if( connection->connected() )
    {
        weak_ptr< scoped_connection > weakConnection( connection );
        mConnections[ weakConnection ] = event;
    }
}
////////////////////////////////////////////////////////////////////////////////
shared_ptr< ConnectionMonopoly > EventManager::MonopolizeConnectionWeak( shared_ptr< scoped_connection > connection )
{
    SW_LOG_TRACE( "MonopolizeConnectionWeak" );
    shared_ptr< ConnectionMonopoly > monopoly( new ConnectionMonopoly );

    // Determine which SignalWrapper this connection is associated with
    ConnectionMap_type::iterator iter = mConnections.find( connection );

    if( iter != mConnections.end() )
    {
        shared_ptr<EventBase> signalWrapper = iter->second.lock();
        // Get the list of all connections from the signal wrapper and set up blocks
        // on all connections besides the one passed in here
        std::list< weak_ptr< scoped_connection > > connections = signalWrapper->GetConnections();

        std::list< weak_ptr< scoped_connection > >::iterator connectionsIter = connections.begin();
        while( connectionsIter != connections.end() )
        {
            weak_ptr< scoped_connection > wCurrentConnection = ( *connectionsIter );
            if( shared_ptr< scoped_connection > sCurrentConnection = wCurrentConnection.lock() )
            {
                if( sCurrentConnection != connection )
                {
                    shared_ptr< shared_connection_block >
                            blocker( new shared_connection_block( *sCurrentConnection ) );
                    monopoly->AddBlocker( blocker );
                }

                connectionsIter++;
            }
            else
            {
                // Failed to lock weak_ptr, which means the underlying shared_ptr
                // has gone out of scope. Jettison the expired entry so we don't
                // need to iterate through it next time.
                std::list< weak_ptr< scoped_connection > >::iterator oldIter = connectionsIter;
                connectionsIter++;
                connections.erase( oldIter );
            }
        }
    }

    return monopoly;
}
////////////////////////////////////////////////////////////////////////////////
shared_ptr< ConnectionMonopoly > EventManager::MonopolizeConnectionStrong( shared_ptr< scoped_connection > connection )
{
    SW_LOG_TRACE( "MonopolizeConnectionStrong" );
    // Determine which SignalWrapper this connection is associated with
    ConnectionMap_type::iterator iter = mConnections.find( connection );

    shared_ptr< ConnectionMonopoly > monopoly = MonopolizeConnectionWeak( connection );

    if( iter != mConnections.end() )
    {
        weak_ptr<EventBase> signalWrapper = iter->second;

        // Store a weak ptr to the monopoly and which SignalWrapper it affects so
        // the monopoly can be updated whenever a new slot connects to the signal
        weak_ptr< ConnectionMonopoly > cmPtr( monopoly );
        mStrongMonopolies[signalWrapper] = cmPtr;
    }

    return monopoly;
}
////////////////////////////////////////////////////////////////////////////////
} // namespace switchwire

