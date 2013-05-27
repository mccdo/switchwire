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

#include <switchwire/ConnectSignals.h>
#include <switchwire/CompilerGuards.h>

#include <switchwire/squirrel/SquirrelContext.h>

namespace switchwire
{
////////////////////////////////////////////////////////////////////////////////
#define SW_REPETETIVE_SCRIPT_CONNECTIONCODE Sqrat::DefaultVM::Set( vm.GetVM().getVM() );\
    SqratFunctionPtr sqFunc = SqratFunctionPtr( new Sqrat::Function( Sqrat::RootTable().\
                      GetFunction( scriptFunctionName.c_str() ) ) );\
    vm.StoreSqratFunction( sqFunc )
////////////////////////////////////////////////////////////////////////////////
#define SW_CONNECTSCRIPT_ARG_LIST const std::string& signalPattern,\
    const std::string& scriptFunctionName,\
    SquirrelContext& vm )

#define SW_CONNECTSIG_ARG_LIST signalPattern,\
    &Sqrat::Function::Execute,\
    sqFunc.get(),\
    vm.GetConnections(),\
    EventManager::any_SignalType,\
    EventManager::normal_Priority
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
} // namespace switchwire
