#pragma once

#include <switchwire/ConnectSignals.h>

#include <squirrel.h>
#include <sqrat.h>
#include <sqrat/sqratVM.h>

////////////////////////////////////////////////////////////////////////////////
// This needs a ScopedScriptsList that stores a smart ptr to the Sqrat::Function
// so we don't leak that memory
template< typename Signature >
void ConnectScript_0( const std::string& signalPattern,
                      const std::string& scriptFunctionName,
                      const std::string& scriptPath,
                      Sqrat::SqratVM& vm,
                      switchwire::ScopedConnectionList& connections,
                      switchwire::EventManager::SignalType signalType = switchwire::EventManager::any_SignalType,
                      switchwire::EventManager::Priority priority = switchwire::EventManager::normal_Priority )
{
    Sqrat::DefaultVM::Set( vm.getVM() );

    // Attempt to load the squirrel script
    try
    {
        Sqrat::Script script;
        script.CompileFile( scriptPath );
        script.Run();
    }
    catch( Sqrat::Exception& e )
    {
        std::cout << "Sqrat exception: " << e.Message() << std::endl << std::flush;
        return;
    }
    catch( ... )
    {
        std::cout << "Unspecified Sqrat exception" << std::endl << std::flush;
        return;
    }

    // Get the squirrel function of interest by name
    Sqrat::Function* sqFunc = new Sqrat::Function( Sqrat::RootTable().
                             GetFunction( scriptFunctionName.c_str() ) );

    // Connect this "function" as a slot
    switchwire::ConnectSignals_0< Signature, Sqrat::Function >(
                    signalPattern,
                    &Sqrat::Function::Execute,
                    sqFunc,
                    connections,
                    signalType,
                    priority );
}
////////////////////////////////////////////////////////////////////////////////
template< typename Signature >
void ConnectScript_1( bool runScript,
                      const std::string& signalPattern,
                      const std::string& scriptFunctionName,
                      const std::string& scriptPath,
                      Sqrat::SqratVM& vm,
                      switchwire::ScopedConnectionList& connections,
                      switchwire::EventManager::SignalType signalType = switchwire::EventManager::any_SignalType,
                      switchwire::EventManager::Priority priority = switchwire::EventManager::normal_Priority )
{
    Sqrat::DefaultVM::Set( vm.getVM() );

    // Attempt to load the squirrel script
    try
    {
        Sqrat::Script script;
        script.CompileFile( scriptPath );
        if( runScript )
            script.Run();
    }
    catch( Sqrat::Exception& e )
    {
        std::cout << "Sqrat exception: " << e.Message() << std::endl << std::flush;
        return;
    }
    catch( ... )
    {
        std::cout << "Unspecified Sqrat exception" << std::endl << std::flush;
        return;
    }

    // Get the squirrel function of interest by name
    Sqrat::Function* sqFunc = new Sqrat::Function( Sqrat::RootTable().
                             GetFunction( scriptFunctionName.c_str() ) );

    // Connect this "function" as a slot
    switchwire::ConnectSignals_1< Signature, Sqrat::Function >(
                    signalPattern,
                    &Sqrat::Function::Execute,
                    sqFunc,
                    connections,
                    signalType,
                    priority );
}
////////////////////////////////////////////////////////////////////////////////
