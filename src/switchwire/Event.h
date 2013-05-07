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
#pragma once

#include<boost/signals2/signal.hpp>
#include<boost/function.hpp>
#include<boost/type_traits.hpp>
#include<boost/shared_ptr.hpp>
#include<boost/weak_ptr.hpp>

#include <switchwire/EventManager.h>
#include <switchwire/EventBase.h>
#include <switchwire/SlotWrapper.h>
#include <switchwire/ScopedConnectionList.h>

#ifdef __GNUG__
#include <cxxabi.h>
#endif

namespace switchwire
{
/// @file Event.h
/// @namespace switchwire
/** @class Event
  * A manageable event (signal). You should never need to use any of the
  * functions here besides the constructor and the signal() operator. To declare
  * an event that can be managed by EventManager, provide the desired signal
  * signature as the first template paramter. To fire the signal, call signal(...),
  * where the elipses represents arguments appropriate to the signature with
  * which the event was declared. The second template parameter is an optional
  * combiner. See the documentation for boost::signals2::signal for more
  * information on using combiners.
  *
  * @tparam T The desired signal signature. Example:
  *           @code Event< bool( int, const std::string& ) > myEvent; @endcode
  *           declares an event which will take an integer and a std::string as
  *           arguments, and which returns a bool.
  * @tparam C An optional combiner. Leave this parameter blank if you don't
  *           require a special combiner.
  *
  * To fire the signal from the above example with arguments 33 and "test", you
  * would use
  * @code myEvent.signal( 33, "test" ); @endcode
  **/
template <typename T, typename C = boost::signals2::optional_last_value< typename boost::function_traits<T>::result_type > >
class Event : public EventBase
{
public:
    Event( )
    {
    }

    virtual ~Event()
    {
    }

    /// Attempts to connect the signal stored in this class to the slot passed
    /// in as @c slot. Returns true if connection was successfully made; false
    /// otherwise.
    virtual bool ConnectSlot( SlotWrapperBasePtr slot,
                              ScopedConnectionList& connections,
                              int priority )
    {
        //This is hack
        SlotWrapper< boost::signals2::signal<T,C> >* castSlot = dynamic_cast < SlotWrapper< boost::signals2::signal<T,C> >* > ( slot.get() );
        //SlotWrapper< boost::signals2::signal<T,C> >* castSlot = dynamic_cast < SlotWrapper< boost::signals2::signal<T,C> >* > ( slot );
        if ( castSlot )
        {
            boost::shared_ptr< boost::signals2::scoped_connection > connection( new boost::signals2::scoped_connection );
            *( connection.get() ) = signal.connect( priority, castSlot->GetSlot() );

            // If the connection was successful, we store the details of it
            if ( connection->connected() )
            {
                connections.AddConnection( connection );
                boost::weak_ptr< boost::signals2::scoped_connection > weakConnection( connection );
                mConnections.push_back( weakConnection );
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    /// If you want EventManager to be notified every time this signal is fired
    /// (so that it can log the signal fire), call this method with the name
    /// that should be logged to turn on notification. If the signal was
    /// registered under multiple names and you want each name logged, you can
    /// call this method more than once, providing a different name each time.
    ///
    /// Notification does not affect how this signal is propagated to connected
    /// slots; it's strictly a logging mechanism. The notification process is a
    /// bit costly, so it's unadvisable to turn on logging for signals that
    /// should have low latency or are otherwise performance-critical.
    ///
    /// If you only need this sort of signal logging while debugging, see
    /// @c EventManager::AutoNotify. Setting autonotify to true will cause
    /// EventManager to set up this notification automatically during the signal
    /// registration process. Of course, this means that it will log even
    /// performance-critical signals that you may not want logged.
    virtual void EnableNotification( const std::string& name )
    {
        m_names.push_back( name );
        // Since the slot and signal are destroyed at the same time, we don't
        // have to worry about connection lifetime manangement. However, we
        // only want to connect to the logging slot iff this is the first name
        // under which this signal was registered; otherwise the slot would get
        // called multiple times each time the signal was fired.
        if( 1 == m_names.size() )
        {
            signal.connect( 0, boost::bind( boost::mem_fn( &Event<T,C>::LogSlot ), this ) );
        }
    }

    /// This function exists for debugging and failure logging purposes.
    virtual long unsigned int GetSignalAddress()
    {
        return reinterpret_cast<long unsigned int>( &signal );
    }

    /// Returns the RTTI info of the signal. Useful for inspecting signal types
    /// and logging.
    virtual std::string GetTypeString()
    {
#ifdef __GNUG__
        int status;
        char* realname;
        realname = abi::__cxa_demangle( typeid( T ).name(), 0, 0, &status );
        std::string result( realname );
        free( realname );
        return result;
#else
        return std::string( typeid( T ).name() );
#endif
    }

    /// The raw boost signal, publically accessible since this is the way we
    /// directly invoke the signal.
    boost::signals2::signal<T,C> signal;

protected:
    /// Mechanism to log all invocations of this slot
    typename boost::function_traits<T>::result_type LogSlot()
    {
        // This is *not* how events are propagated to slots! This is strictly a
        // logging mechanism.
        EventManager::instance()->NotifySignalFiring( m_names );
        return typename boost::function_traits<T>::result_type();
    }

private:
    /// Stores all names associated with this event
    std::vector< std::string > m_names;
};
////////////////////////////////////////////////////////////////////////////////
} // namespace

