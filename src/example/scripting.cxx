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
#include <switchwire/squirrel/ConnectScripts.h>
#include <switchwire/squirrel/ExposeSignals.h>
#include <switchwire/squirrel/SQStdMap.h>
#include <switchwire/squirrel/SQStdVector.h>

#include <switchwire/ConnectSignals.h>
#include <switchwire/CompilerGuards.h>

#include <squirrel.h>
DIAG_OFF(unused-parameter)
#include <sqrat.h>
#include <sqrat/sqratVM.h>
DIAG_ON(unused-parameter)

#include <vector>

Sqrat::SqratVM vm;
////////////////////////////////////////////////////////////////////////////////
void printInt( int num )
{
    std::cout << "C++ print: " << num << std::endl;
}
////////////////////////////////////////////////////////////////////////////////
int main()
{
    switchwire::ScopedConnectionList connections;

    // Create and register a couple of C++ signals.
    switchwire::Event< void (int) > intSignal;
    switchwire::EventManager::instance()->
            RegisterSignal( &intSignal , "ATestEvent" );

    switchwire::Event< void (std::string) > strSignal;
    switchwire::EventManager::instance()->
            RegisterSignal( &strSignal , "AStringEvent" );



    // Set up a default Squirrel VM.
    Sqrat::DefaultVM::Set(vm.getVM());

    // Give squirrel access to intSignal and strSignal. That is, access to the
    // *instances* of intSignal and strSignal created above
    ExposeSignal_1< void (int) >( &intSignal, "THEintSignal", vm );
    ExposeSignal_1< void (std::string) >( &strSignal, "THEstringSignal", vm );


    // Expose a void(int) signal type. Squirrel scripts can now use the class
    // "SetupVoidIntSignal" to create and register brand new signals with
    // signature void(int).
    ExposeSignalType_1< void(int) >( "SetupVoidIntSignal", vm );

    // In the sample script, we use the "SetupVoidIntSignal" class to create
    // and register a void(int) signal registered with name "ScriptIntSignal".
    // We want to connect this script signal to a C++ slot:
    switchwire::ConnectSignalsStatic< void(int) >( "ScriptIntSignal",
                                                   &printInt,
                                                   connections );


    // We can also connect functions in scripts as slots:
    // Connect signal "ATestEvent" to the function "prt" in the squirrel script
    // "scripts/printAnInt.nut" in the VM "vm".
    ConnectScript_1< void(int) >( true, "ATestEvent",
                          "prt",
                          "scripts/printAnInt.nut",
                          vm,
                          connections );

    // Do the same for prtStr -- the first argument is a boolean indicating
    // whether the script should be run after it is loaded. Scripts have to
    // be run at least once after being loaded before we can bind to functions
    // in them. In this case, we ran the script when we connected to the slot
    // "prt", so we don't need to run this script again.
    ConnectScript_1< void(std::string) >( false, "AStringEvent",
                          "prtStr",
                          "scripts/printAnInt.nut",
                          vm,
                          connections );

    // Make a std::vector<int> type available to scripts bound to name "IntVec"
    BindSQStdVector< int >( "IntVec" );

    // Make a std::map<int, std::string> type available bound to name "IntStringMap"
    BindSQStdMap< int, std::string >( "IntStringMap" );


    // Fire our signals
    intSignal.signal( 1 );
    std::string text("Test fire of strSignal in C++.");
    strSignal.signal( text );

    return 0;
}
