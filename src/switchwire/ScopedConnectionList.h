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

#include <switchwire/CompilerGuards.h>
DIAG_OFF(unused-parameter)
    #include<boost/signals2/signal.hpp>
DIAG_ON(unused-parameter)
#include<boost/shared_ptr.hpp>

#include<list>

#include <switchwire/Exports.h>


namespace switchwire
{
/// @file ScopedConnectionList.h
/// @namespace switchwire
/** @class ScopedConnectionList
 * ScopedConnectionList is essentially a smart container for boost::signals2::scoped_connection
 * objects. It provides an easy way for another class to keep a set of scoped_connectionS
 * in scope for the entire lifetime of the class. It also provides a few simple methods
 * to manage scoped_connections. Use of this class by listeners is required by EventManager.
 *
 * If a ScopedConnectionList is held as a normal member of a class (ie., not as a pointer)
 * then all associated connections are automatically dropped and deleted when the owning class
 * is destroyed -- there is no need to explicitly call ScopedConnectionList::DropConnections from
 * the destructor of the owning class.
 *
 * There are three useful ways to use ScopedConnectionList:
 * @li For connections that should stay alive for the entire lifetime of the class, hold
 * a ScopedConnectionList as a normal class member. Connections will be automatically
 * disconnected as described above.
 * @li For connections that are frequently
 * made and broken during the lifetime of the class, either hold a ScopedConnectionList
 * as a normal class member and call ScopedConnectionList::DropConnections when you
 * need to break the connections, or
 * @li Hold a pointer to a ScopedConnectionList object
 * and delete the object when you want to break the connections.
 *
 * Be aware that the
 * last strategy is dangerous, as it does <em>not</em> ensure that all connections
 * are broken upon destruction of the owning class: if you forget to delete the ScopedConnectionList*
 * in the destructor of the owning class, you'll probably crash the application. Be careful.
 *
 * Fine-grained access to specific connections (and by extension, their lifetime) can
 * be had by using ScopedConnectionList::GetBegin and ScopedConnectionList::GetEnd to get
 * direct iterators into the underlying list. Calling std::list::erase on a specific
 * iterator will cause that connection to be broken (and cleaned up).
 *
 * ScopedConnectionList was inspired by the similarly-named class used by the
 * ardour project. See http://www.ardour.org
 **/
class SWITCHWIRE_EXPORT ScopedConnectionList
{
public:
    /// Easy way to refer to the internal list type.
    /// Std::list was chosen over std::vector here because it allows constant time
    /// erasure of elements anywhere in the list, and does not invalidate iterators
    /// to other elements during erasure. These two advantages should make up for
    /// the slight increase in storage overhead.
    typedef std::list< boost::shared_ptr< boost::signals2::scoped_connection > > ConnectionList_type;
    
    ScopedConnectionList( );
    ScopedConnectionList( const ScopedConnectionList& orig );
    virtual ~ScopedConnectionList( );

    /// Adds a connection to the internal list.
    /// @param connection Shared pointer to the scoped_connection object to add to the internal list.
    /// Boost::shared_ptr is used here so that other objects (especially EventManager) can
    /// track the lifetime of the underlying scoped_connection via a boost::weak_ptr.
    void AddConnection( boost::shared_ptr< boost::signals2::scoped_connection > connection );

    /// Drops all existing connections.
    /// Dropping a connection will result in the affected slot's no longer receiving
    /// the signal associated with that connection. Memory associated with the
    /// connection(s) is automatically cleaned up.
    void DropConnections( );

    /// Provides access to the beginning of the list of scoped_connectionS to allow callers
    /// to get the connection for modification or removal.
    /// Since the underlying type is a std::list, all other iterators remain valid when
    /// one is erased.
    ConnectionList_type::iterator GetBegin();

    /// Provides access to the end of the list of scoped_connectionS to allow callers
    /// to get the connection for modification or removal.
    /// Since the underlying type is a std::list, all other iterators remain valid when
    /// one is erased.
    ConnectionList_type::iterator GetEnd();

    ///
    /// Provided for convenience to directly get the last connection made
    boost::shared_ptr< boost::signals2::scoped_connection > GetLastConnection();

    /// Returns a weak pointer to this object without the need to create a shared ptr first.
    boost::weak_ptr< ScopedConnectionList > GetWeakPtr() const { return this_; }

    void Reset() { this_.reset(); }

private:
    boost::shared_ptr< ScopedConnectionList > this_;
    ConnectionList_type mConnections;

};

}

