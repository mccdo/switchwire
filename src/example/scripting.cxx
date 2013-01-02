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
#include "ConnectScripts.h"
#include "ExposeSignals.h"

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
void SetupSignal( const char* signalName, const char* squirrelName )
{
    switchwire::Event< void(int) >* ev = new switchwire::Event<void(int)>;
    std::string name;
    name.assign( signalName );
    switchwire::EventManager::instance()->RegisterSignal( ev, name );
    name.assign( squirrelName );
    ExposeSignal_1< void(int) >( ev, name, vm );
}
////////////////////////////////////////////////////////////////////////////////
int main()
{
    switchwire::ScopedConnectionList connections;

    Sqrat::DefaultVM::Set(vm.getVM());
    Sqrat::RootTable().Func( "SetupSignal", &SetupSignal );

    switchwire::Event< void (int) > intSignal;
    switchwire::EventManager::instance()->
            RegisterSignal( &intSignal , "ATestEvent" );

    switchwire::Event< void (std::string) > strSignal;
    switchwire::EventManager::instance()->
            RegisterSignal( &strSignal , "AStringEvent" );

    // Create a squirrel virtual machine (VM) and set it as the default so
    // all following code dealing with the vm doesn't have to specify which
    // vm to talk to.
    //Sqrat::SqratVM vm;

    // Give squirrel access to intSignal and strSignal
    ExposeSignal_1< void (int) >( &intSignal, "THEintSignal", vm );
    ExposeSignal_1< void (std::string) >( &strSignal, "THEstringSignal", vm );

    switchwire::ConnectSignalsStatic< void(int) >( "ScriptIntSignal",
                                                   &printInt,
                                                   connections );


    // Connect script functions as slots
    // Connect signal "ATestEvent" to the function "prt" in the squirrel script
    // "scripts/printAnInt.nut" in the VM "vm".
    ConnectScript_1< void(int) >( true, "ATestEvent",
                          "prt",
                          "scripts/printAnInt.nut",
                          vm,
                          connections );

    // Do the same for prtStr
    ConnectScript_1< void(std::string) >( false, "AStringEvent",
                          "prtStr",
                          "scripts/printAnInt.nut",
                          vm,
                          connections );

 // -------- This code should go into a library init function along with ---- //
 //          similar versions for std::vector, std::map, and maybe some others.
 //          It would be nice to come up with a good way to extend this
 //          functionality by registering new wrapper classes or something.
    // Give Squirrel access to our std::string wrapper class
//    Sqrat::RootTable().Bind( "SQStdString", Sqrat::Class< SQStdString >()
//                             .Prop( "String", &SQStdString::Getc_str, &SQStdString::SetString )
//                             .Prop( "StdString", &SQStdString::GetStdString, &SQStdString::SetStdString ));
 // ----------------------------------- end ------------------------------- //

    typedef std::vector<int> vecint;
    Sqrat::RootTable().Bind( "IntVec", Sqrat::Class< vecint >()
                             .Func< int& (vecint::*)(size_t) >( "at", &vecint::at )
                             .Func( "push_back", &vecint::push_back )
                             .Func< size_t (vecint::*)() const >( "size", &vecint::size)
                             .Func( "clear", &vecint::clear) );

//    typedef std::map< int, int > mapintint;
//    Sqrat::RootTable().Bind( "IntIntMap", Sqrat::Class< mapintint >()
//                             .Func(  )
//                             .Func( "clear", &mapintint::clear) );




//    typedef SQStdVector<int> vecint;
//    Sqrat::RootTable().Bind( "IntVec", Sqrat::Class< vecint >()
//                             .Func( "at", &vecint::at )
//                             .Func( "push_back", &vecint::push_back )
//                             .Func( "size", &vecint::size )
//                             .Func( "clear", &vecint::clear ) );

    // Fire our signals
    intSignal.signal( 1 );
    std::string text("Test fire of strSignal in C++.");
    strSignal.signal( text );

    return 0;
}
