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

#include <switchwire/EventBase.h>
#include <switchwire/SlotWrapper.h>
#include <switchwire/ScopedConnectionList.h>

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

    // This function exists for debugging and failure logging purposes.
    virtual long unsigned int GetSignalAddress()
    {
        return reinterpret_cast<long unsigned int>( &signal );
    }

    boost::signals2::signal<T,C> signal;
};
////////////////////////////////////////////////////////////////////////////////



}

