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

////////////////////////////////////////////////////////////////////////////////
//           Class: SlotInClass                                               //
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <switchwire/ConnectSignals.h>
#include <switchwire/ScopedConnectionList.h>
class SlotInClass
{
public:
    SlotInClass()
    {
        // Connect mySlot to the event with signature void(int) and name
        // "ATestEvent". Notice that we do not need any information about the
        // object that owns "ATestEvent". All we need to know is the name of the
        // event and its signature.

        switchwire::ConnectSignals_1< void (int), SlotInClass >(
                    "ATestEvent",
                    &SlotInClass::mySlot,
                    this,
                    m_connections,
                    switchwire::EventManager::any_SignalType,
                    switchwire::EventManager::normal_Priority );

        // Key points to notice in the above call:
        // * The template function name includes the number of arguments the
        //   event has; in this case, one.
        // * The template parameters specify the signature of the event you want
        //   and the type of the class which owns the slot
        // * The second function argument, &SlotInClass::mySlot, does not have
        //   parentheses after it! We want a pointer to the method, not a
        //   method call.
    }

    void mySlot( int arg )
    {
        std::cout << "SlotInClass::mySlot: argument = " << arg << std::endl;
    }

    switchwire::ScopedConnectionList m_connections;
};


////////////////////////////////////////////////////////////////////////////////
// Application entry point                                                    //
////////////////////////////////////////////////////////////////////////////////
#include <switchwire/EventManager.h>
#include <switchwire/Event.h>
int main()
{
    // Declare an event
    switchwire::Event< void (int) > intSignal;

    // Register the event with EventManager
    switchwire::EventManager::instance()->
      RegisterSignal( &intSignal , "ATestEvent" );

    // Create a ScopedConnectionList, which is required for connecting to an
    // event. This is frequently a class member variable also.
    switchwire::ScopedConnectionList connections;

    // Instantiate a class with a valid slot that connects to "ATestEvent". Look
    // at the class's code to see how this works. Most applications will connect
    // to events from inside classes far more often than in global or static
    // functions.
    SlotInClass mySlotClass;

    // We could even instantiate a few of these, and each one will be called
    // in turn. Uncomment to see the behavior.
    //SlotInClass msc2;
    //SlotInClass msc3;

    // Fire the signal several times
    intSignal.signal( 1 );
    intSignal.signal( 0 );
    intSignal.signal( 5 );
    intSignal.signal( 4 );
    intSignal.signal( 5 );

    return 0;
}

