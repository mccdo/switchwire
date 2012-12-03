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
#include <switchwire/Exports.h>
#include <switchwire/SlotWrapperBase.h>
#include <switchwire/ScopedConnectionList.h>

namespace switchwire
{
struct null_deleter
{
    void operator()( void* ) {}
};
/// @file EventBase.h
/// @namespace switchwire
/** @class EventBase
  * Base class for templated Event<> class. Mainly for internal use in the
  * switchwire library. Applications generally should not need to use this
  * class explicitly.
  **/
class SWITCHWIRE_EXPORT EventBase
{
public:
    ///Default constructor
    EventBase()
    {
        this_ = boost::shared_ptr< EventBase >(this, null_deleter());    
    }
    ///Copy constructor
    EventBase( const EventBase& )
    {
        this_ = boost::shared_ptr< EventBase >(this, null_deleter());    
    }
    ///Assignment operator
    EventBase& operator=(EventBase const&)
    {
        return *this;
    }

    virtual ~EventBase(){}

    /// Returns a weak pointer to this object without the need to create a
    /// shared ptr first.
    boost::weak_ptr< EventBase > GetWeakPtr() { return this_; }

    /// Connects slot held in SlotWrapper to the signal owned by derived Event<>
    /// instance.
    /// @param slot Pointer to SlotWrapper<> that holds the slot
    /// @param connections Reference to a ScopedConnectionList object that is
    /// responsible for lifetime management of the resulting connnection
    /// @param priority The priority with which slot should be connected to this
    /// signal. This priority is a raw integer rather than one of the enumerated
    /// priorities from EventManager so that this class need not depend on
    /// EventManager.h
    virtual bool ConnectSlot( SlotWrapperBasePtr slot,
                              ScopedConnectionList& connections,
                              int priority ) = 0;

    /// Returns the list of scoped_connection objects referring to all slots
    /// connected to this signal. Note that the list holds boost::weak_ptrS to
    /// the scoped_connectionS. This list functions in the primary role of
    /// observer of the connections rather than the owner. The class holding the
    /// connected slot typically owns the connection.
    std::list< boost::weak_ptr< boost::signals2::scoped_connection > >& GetConnections()
    {
        return mConnections;
    }

    /// Returns a pointer cast as an int to the underlying signal. This is
    /// intended for debugging purposes to allow the signal's address to be printed
    /// out.
    virtual long unsigned int GetSignalAddress() = 0;


protected:
    std::list< boost::weak_ptr< boost::signals2::scoped_connection > > mConnections;

private:
    boost::shared_ptr< EventBase > this_;

};

} // namespace switchwire
