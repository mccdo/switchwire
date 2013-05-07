#pragma once

#include <switchwire/ConnectSignals.h>
#include <switchwire/CompilerGuards.h>

#include <squirrel.h>
DIAG_OFF(unused-parameter)
#include <sqrat.h>
#include <sqrat/sqratVM.h>
DIAG_ON(unused-parameter)

////////////////////////////////////////////////////////////////////////////////
#define SW_REPETETIVE_SCRIPT_CONNECTIONCODE Sqrat::DefaultVM::Set( vm.getVM() );\
    \
    try\
    {\
        Sqrat::Script script;\
        script.CompileFile( scriptPath );\
        if( runScript )\
        {\
            script.Run();\
        }\
    }\
    catch( Sqrat::Exception& e )\
    {\
        std::cout << "Sqrat exception: " << e.Message() << std::endl << std::flush;\
        return;\
    }\
    catch( ... )\
    {\
        std::cout << "Unspecified Sqrat exception" << std::endl << std::flush;\
        return;\
    }\
    \
    \
    Sqrat::Function* sqFunc = new Sqrat::Function( Sqrat::RootTable().\
                             GetFunction( scriptFunctionName.c_str() ) )
////////////////////////////////////////////////////////////////////////////////
#define SW_CONNECTSCRIPT_ARG_LIST bool runScript,\
    const std::string& signalPattern,\
    const std::string& scriptFunctionName,\
    const std::string& scriptPath,\
    Sqrat::SqratVM& vm,\
    switchwire::ScopedConnectionList& connections,\
    switchwire::EventManager::SignalType signalType = switchwire::EventManager::any_SignalType,\
    switchwire::EventManager::Priority priority = switchwire::EventManager::normal_Priority )

#define SW_CONNECTSIG_ARG_LIST signalPattern,\
    &Sqrat::Function::Execute,\
    sqFunc,\
    connections,\
    signalType,\
    priority
////////////////////////////////////////////////////////////////////////////////


// This needs a ScopedScriptsList that stores a smart ptr to the Sqrat::Function
// so we don't leak that memory
template< typename Signature >
void ConnectScript_0( SW_CONNECTSCRIPT_ARG_LIST
{
    SW_REPETETIVE_SCRIPT_CONNECTIONCODE;

    switchwire::ConnectSignals_0< Signature, Sqrat::Function >( SW_CONNECTSIG_ARG_LIST );
}
////////////////////////////////////////////////////////////////////////////////
template< typename Signature >
void ConnectScript_1( SW_CONNECTSCRIPT_ARG_LIST
{
    SW_REPETETIVE_SCRIPT_CONNECTIONCODE;

    switchwire::ConnectSignals_1< Signature, Sqrat::Function >( SW_CONNECTSIG_ARG_LIST );
}
////////////////////////////////////////////////////////////////////////////////
template< typename Signature >
void ConnectScript_2( SW_CONNECTSCRIPT_ARG_LIST
{
  SW_REPETETIVE_SCRIPT_CONNECTIONCODE;

  switchwire::ConnectSignals_2< Signature, Sqrat::Function >( SW_CONNECTSIG_ARG_LIST );
}
////////////////////////////////////////////////////////////////////////////////
template< typename Signature >
void ConnectScript_3( SW_CONNECTSCRIPT_ARG_LIST
{
    SW_REPETETIVE_SCRIPT_CONNECTIONCODE;

    switchwire::ConnectSignals_3< Signature, Sqrat::Function >( SW_CONNECTSIG_ARG_LIST );
}
////////////////////////////////////////////////////////////////////////////////
template< typename Signature >
void ConnectScript_4( SW_CONNECTSCRIPT_ARG_LIST
{
  SW_REPETETIVE_SCRIPT_CONNECTIONCODE;

  switchwire::ConnectSignals_4< Signature, Sqrat::Function >( SW_CONNECTSIG_ARG_LIST );
}
////////////////////////////////////////////////////////////////////////////////
template< typename Signature >
void ConnectScript_5( SW_CONNECTSCRIPT_ARG_LIST
{
    SW_REPETETIVE_SCRIPT_CONNECTIONCODE;

    switchwire::ConnectSignals_5< Signature, Sqrat::Function >( SW_CONNECTSIG_ARG_LIST );
}
////////////////////////////////////////////////////////////////////////////////
//template< class Signature >
//class ExposeSlotType_1( Sqrat::SqratVM& vm, switchwire::ScopedConnectionList& connections )
//{

//};

////////////////////////////////////////////////////////////////////////////////
