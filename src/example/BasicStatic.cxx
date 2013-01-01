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

// The minimal set of headers required to register a signal and connect a slot
// to it.
#include <switchwire/ConnectSignals.h>
#include <switchwire/Event.h>

// If you're just registering a signal but not connecting any slots in that
// compilation unit, you only need <switchwire/EventManager.h>

void prt( int num )
{
    std::cout << "prt: argument = " << num << std::endl;
}

int main()
{
    // Declare an event (usually done as a class member variable)
    switchwire::Event< void (int) > intSignal;

    // Create a ScopedConnectionList, which is required for connecting to an
    // event. This is frequently a class member variable also.
    switchwire::ScopedConnectionList connections;

    // Register the event with EventManager
    switchwire::EventManager::instance()->
      RegisterSignal( &intSignal , "ATestEvent" );

    // Request a connection between "ATestEvent" and function prt. This shows
    // how to connect to static functions or other functions which are not
    // members of a class.
    switchwire::ConnectSignalsStatic<void (int)>(
                    "ATestEvent",
                    &prt,
                    connections );

    // The two previous calls ( to RegisterSignal and ConnectSignalsStatic )
    // can happen in any order. When the call to RegisterSignal happens first,
    // the signal is connected immediately when ConnectSignalsStatic is called.
    // When ConnectSignalsStatic is called first, EventManager holds on to the
    // slot (prt) and the pattern it was trying to connect to ("ATestEvent").
    // When "ATestEvent" is later registered, EventManager sees there is already
    // a slot waiting to be connected to this signal, and makes the connection.
    // This behavior decouples the logic of signal/slot connection from the
    // order of object creation, a very useful feature in complex applications.

    // Fire the signal several times
    intSignal.signal( 1 );
    intSignal.signal( 0 );
    intSignal.signal( 5 );
    intSignal.signal( 4 );
    intSignal.signal( 5 );

    return 0;
}

