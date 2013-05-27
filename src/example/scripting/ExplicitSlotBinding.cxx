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
#include <switchwire/squirrel/Events.h>
#include <switchwire/squirrel/SquirrelContext.h>

#include <switchwire/ConnectSignals.h>
#include <switchwire/CompilerGuards.h>

/*
 * This example demonstrates connecting a script function as a slot to a signal.
 * The slot is implemented in the script, but the connection is made in C++.
 *
 * A developer may wish to use this strategy for security reasons: since no
 * general slot type has been exposed to the SquirrelContext, a script cannot
 * request a connection to any random signal in the application. The compiled
 * C++ code maintains explicit control over signal/slot connections.
 */
////////////////////////////////////////////////////////////////////////////////
int main()
{
    // Create and register a C++ signal.
    switchwire::Event< void (int) > intSignal;
    switchwire::EventManager::instance()->
            RegisterSignal( &intSignal , "ATestEvent" );

    // Create a SquirrelContext
    switchwire::SquirrelContext sqContext;

    // Load a script into the SquirrelContext
    sqContext.LoadScriptFromFile( "ExplicitReceiveInt.nut" );

    // Connect the function named "prt" in the loaded script to ATextEvent
    switchwire::ConnectScript_1< void(int) >( "ATestEvent",
                                              "prt",
                                              sqContext );

    // Notice that we don't need to call sqContext.Execute() in this case,
    // because there isn't an Execute function in the script. We're just pulling
    // a function out of it and connecting it to an event.

    // Fire the signal
    intSignal.signal( 1 );
    intSignal.signal( 2 );
    intSignal.signal( 3 );
    intSignal.signal( 4 );

    return 0;
}
