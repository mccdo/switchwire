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

#include <switchwire/ScopedConnectionList.h>
#include <switchwire/squirrel/SqratFunctionPtr.h>
#include <switchwire/squirrel/ManagedLifetime.h>

#include <cstdio> // This is required because sqratVM.h fails to properly
                  // include it and their release cycle is unspecified.
DIAG_OFF(format)
DIAG_OFF(unused-parameter)
#include <sqrat.h>
#include <sqrat/sqratVM.h>
DIAG_ON(unused-parameter)
DIAG_ON(format)

#include <string>
#include <vector>

// This file contains the implementation of the class as well as the definition
// to allow the squirrel bindings for switchwire to be entirely header-based.
// This has the added benefit of avoiding linking this object directly into
// the main switchwire library, thus casuing an undesirable dependency on
// Squirrel for the main library.

namespace switchwire
{
// This class has two functional purposes: to reduce the end-user code required
// to load and run a script with the special process we require for proper
// event binding, and to automatically manage memory allocated when registering
// and connecting events in scripts. Event connections made under a given
// instance of a SquirrelContext will have the same lifetime as the
// SquirrelContext.
class SquirrelContext
{
public:
    SquirrelContext();

    /// Attempts to load a script from a file. "Runs" the script to load
    /// symbols.
    void LoadScriptFromFile( const std::string& path );

    /// Attempts to load a script from a string. "Runs" the script to load
    /// symbols.
    void LoadScriptFromText( const std::string& scriptText );

    /// Binds and calls the "Execute" method of the script
    void ExecuteScript();

    /// Stores a SqratFunctionPtr to manage memory of scripted signals and slots
    void StoreSqratFunction( SqratFunctionPtr functionPtr );

    /// Stores a ManagedLifetime object and keeps it alive until this class is
    /// destroyed
    void StoreManagedLifetimeObject( ManagedLifetimePtr mlo );

    /// Returns the squirrel virtual machine
    Sqrat::SqratVM& GetVM()
    {
        return m_vm;
    }

    /// Returns connections list
    ScopedConnectionList& GetConnections()
    {
        return m_connections;
    }

private:
    Sqrat::SqratVM m_vm;

    std::vector< SqratFunctionPtr > m_SqratFunctions;
    std::vector< ManagedLifetimePtr > m_managedLifetimeObjects;
    ScopedConnectionList m_connections;
};

////////////////////////////////////////////////////////////////////////////////
SquirrelContext::SquirrelContext()
{
    Sqrat::DefaultVM::Set( m_vm.getVM() );
}
////////////////////////////////////////////////////////////////////////////////
void SquirrelContext::LoadScriptFromFile(const std::string &path)
{
    Sqrat::Script script;
    try
    {
        script.CompileFile( path );
        script.Run();
    }
    catch( Sqrat::Exception& e )
    {
        std::cout << "Sqrat exception: " << e.Message() << std::endl
                  << std::flush;
        return;
    }
}
////////////////////////////////////////////////////////////////////////////////
void SquirrelContext::LoadScriptFromText(const std::string &scriptText)
{
    Sqrat::Script script;
    try
    {
        script.CompileString( scriptText );
        script.Run();
    }
    catch( Sqrat::Exception& e )
    {
        std::cout << "Sqrat exception: " << e.Message() << std::endl
                  << std::flush;
        return;
    }
}
////////////////////////////////////////////////////////////////////////////////
void SquirrelContext::ExecuteScript()
{
    Sqrat::Function Execute( Sqrat::RootTable().GetFunction( "Execute" ) );
    Execute();
}
////////////////////////////////////////////////////////////////////////////////
void SquirrelContext::StoreSqratFunction(SqratFunctionPtr functionPtr)
{
    m_SqratFunctions.push_back( functionPtr );
}
////////////////////////////////////////////////////////////////////////////////
void SquirrelContext::StoreManagedLifetimeObject( ManagedLifetimePtr mlo )
{
    m_managedLifetimeObjects.push_back( mlo );
}
////////////////////////////////////////////////////////////////////////////////
} // namespace switchwire
