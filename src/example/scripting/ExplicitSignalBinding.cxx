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

#include <iostream>
/*
 * This example demonstrates firing an _existing_ C++ signal from a script.
 * In this case, the signal and slot are both set up in C++ code, but we never
 * fire the signal from C++ code; we do that in the script.
 *
 * A developer may wish to implement this strategy as a security measure to
 * explicit limit the application signals available to scripts.
 */
////////////////////////////////////////////////////////////////////////////////
void printInt( int num )
{
    std::cout << "C++ print: " << num << std::endl;
}
////////////////////////////////////////////////////////////////////////////////
int main()
{
    // Create the signal we want to bind to the SquirrelContext
    switchwire::Event< void(int) > IntSignal;
    switchwire::EventManager::instance()->RegisterSignal( &IntSignal, "IntSignal" );

    // We need a ScopedConnectionList because we're connecting a C++ slot, not
    // a scripted slot.
    switchwire::ScopedConnectionList connections;

    // Connect the C++ signal to the C++ slot.
    switchwire::ConnectSignalsStatic< void(int) >( "IntSignal",
                                                   &printInt,
                                                   connections );

    // Create a squirrel context. You must do this before you can expose any
    // signals, slots, signal types, or slot types.
    switchwire::SquirrelContext sqContext;

    // Bind the signal IntSignal to the squirrel context using the name
    // "ExplicitIntSignal"
    switchwire::ExposeSignal_1< void(int) >(&IntSignal, "ExplicitIntSignal", sqContext);

    // Load a script into the squirrel context
    sqContext.LoadScriptFromFile( "ExplicitSendInt.nut" );

    // Call the "Execute" function in the loaded script
    sqContext.ExecuteScript();

    // Notice that we never fire the signal from C++; that happens in the script.
    // Program output should be a series of "C++ print: " followed by a number

    return 0;
}

