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
 * This example demonstrates exposing a signal *type* to the SquirrelContext,
 * which will allow any loaded script to declare a brand new signal matching
 * that type, but having any connection name the script chooses.
 *
 * This technique is less secure than the one shown in ExplicitSignalBinding.cxx,
 * but is far more flexible, since scripts can create new signals that don't
 * exist in the C++ code.
 */
////////////////////////////////////////////////////////////////////////////////
void printInt( int num )
{
    std::cout << "C++ print: " << num << std::endl;
}
////////////////////////////////////////////////////////////////////////////////
int main()
{
    switchwire::ScopedConnectionList connections;

    // Create a squirrel context. You must do this before you can expose any
    // signals, slots, signal types, or slot types.
    switchwire::SquirrelContext sqContext;

    // Expose a void(int) signal type. Squirrel scripts can now use the class
    // "IntSignal" to create and register brand new signals with
    // signature void(int).
    switchwire::ExposeSignalType_1< void(int) >( "IntSignal", sqContext );

    // In the "SendInt.nut" script, we use the "IntSignal" class to
    // create and register a void(int) signal registered with name
    // "ScriptIntSignal". We want to connect this signal to a C++ slot. Notice
    // that this connection call is just like any other ConnectSignalsStatic
    // connection -- we're not doing anything special here even though we know
    // the signal is coming from a script.
    switchwire::ConnectSignalsStatic< void(int) >( "ScriptIntSignal",
                                                   &printInt,
                                                   connections );

    // Load a script into the squirrel context
    sqContext.LoadScriptFromFile( "SendInt.nut" );

    // Call the "Execute" function in the loaded script
    sqContext.ExecuteScript();

    // Program output should be a series of "C++ print: " followed by a number

    return 0;
}
