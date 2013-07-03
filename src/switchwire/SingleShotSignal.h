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
//DIAG_OFF(unused-parameter)
//    #include<boost/signals2/signal.hpp>
//DIAG_ON(unused-parameter)
#include <switchwire/Event.h>
#include <switchwire/EventManager.h>

/// @file SingleShotSignal.h
/// @namespace switchwire

namespace switchwire
{

// Declarations through arity 5 are given here. Add more as needed.
// Unclear whether it's desirable to match the functor return type to that
// of the signal signature.

// Full version of what we're doing:
/*
template< class R, class A1 >
void SingleShotSignal( const std::string& name,
                       A1 a1 )
{
    typedef typename boost::signals2::signal< R (A1) > signalT;
    signalT event;
    switchwire::EventManager::instance()->RegisterSignal( &event,
                name, switchwire::EventManager::unspecified_SignalType );
    event.signal( a1 );
}
*/

#define SW_SS_CREATE_AND_REG_EVENT  \
    switchwire::EventManager::instance()->RegisterSignal( &event,\
                name, switchwire::EventManager::unspecified_SignalType )

template< class R >
void SingleShotSignal( const std::string& name )
{
    Event< R (void) > event;
    SW_SS_CREATE_AND_REG_EVENT;
    event.signal( );
}

template< class R, class A1 >
void SingleShotSignal( const std::string& name,
                       A1 a1 )
{
    Event< R (A1) > event;
    SW_SS_CREATE_AND_REG_EVENT;
    event.signal( a1 );
}

template< class R, class A1, class A2 >
void SingleShotSignal( const std::string& name,
                       A1 a1, A2 a2 )
{
    Event< R (A1, A2) > event;
    SW_SS_CREATE_AND_REG_EVENT;
    event.signal( a1, a2 );
}

template< class R, class A1, class A2, class A3 >
void SingleShotSignal( const std::string& name,
                       A1 a1, A2 a2, A3 a3 )
{
    Event< R (A1, A2, A3) > event;
    SW_SS_CREATE_AND_REG_EVENT;
    event.signal( a1, a2, a3 );
}

template< class R, class A1, class A2, class A3, class A4 >
void SingleShotSignal( const std::string& name,
                       A1 a1, A2 a2, A3 a3, A4 a4 )
{
    Event< R (A1, A2, A3, A4) > event;
    SW_SS_CREATE_AND_REG_EVENT;
    event.signal( a1, a2, a3, a4 );
}

template< class R, class A1, class A2, class A3, class A4, class A5 >
void SingleShotSignal( const std::string& name,
                       A1 a1, A2 a2, A3 a3, A4 a4, A5 a5 )
{
    Event< R (A1, A2, A3, A4, A5) > event;
    SW_SS_CREATE_AND_REG_EVENT;
    event.signal( a1, a2, a3, a4, a5 );
}

} // namespace
