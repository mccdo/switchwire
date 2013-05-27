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
 * This example demonstrates exposing a slot *type* to the SquirrelContext,
 * allowing scripts to connect any suitable function defined in the script to
 * signals with a matching type.
 *
 * This technique is less secure than the one shown in ExplicitSlotBinding.cxx,
 * but is much more flexible because new signal/slot connections can be
 * requested by the script without having to change anything in the compiled
 * application.
 */
////////////////////////////////////////////////////////////////////////////////
int main()
{
    // Create and register a C++ signal.
    switchwire::Event< void (int) > intSignal;
    switchwire::EventManager::instance()->
            RegisterSignal( &intSignal , "ATestEvent" );

    // Create a squirrel context. You must do this before you can expose any
    // signals, slots, signal types, or slot types.
    switchwire::SquirrelContext sqContext;

    // Expose a void(int) slot type to the squirrel context. The script will use
    // the created-and-bound "VoidIntSlot" class to create a connection between
    // a script function and the signal "ATestEvent".
    switchwire::ExposeSlotType_1< void(int) >( "VoidIntSlot",
                                   sqContext );

    // Load the script into the squirrel context.
    sqContext.LoadScriptFromFile( "ReceiveInt.nut" );

    // Call the "Execute" function in the loaded script
    sqContext.ExecuteScript();

    // Fire the signal. The script "ReceiveInt.nut" will print out the argument
    // each time.
    intSignal.signal( 1 );
    intSignal.signal( 2 );
    intSignal.signal( 3 );
    intSignal.signal( 4 );

    return 0;
}
