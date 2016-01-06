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

#include <switchwire/squirrel/SquirrelContext.h>

// The underlying idea here
// is that ExposeSlotType_N<> creates an instance of a typed SlotConnector and
// binds it to the squirrel virtual machine using the name given as its first
// argument. Scripted code can then use the instance of SlotConnector bound to
// this name to request a connection between a named signal and a function
// within the script by calling the instance's ConnectSlotToSignal method.
namespace switchwire
{
// Examples of the class and functor without the macro buildup
/*
////////////////////////////////////////////////////////////////////////////////
template< class TT >
class SlotConnector_1
{
public:
    void ConnectSlotToSignal( const char* slotName, const char* signalPattern )
    {
        SqratFunctionPtr sqFunc = SqratFunctionPtr( new Sqrat::Function( Sqrat::RootTable().
                              GetFunction( slotName ) );
        m_vm->StoreSqratFunction( sqFunc );
        std::string pattern;
        pattern.assign(  signalPattern );
        switchwire::ConnectSignals_1< TT, Sqrat::Function >( pattern,
                                                           &Sqrat::Function::Execute,
                                                           sqFunc.get(),
                                                           m_vm->GetConnections(),
                                                           EventManager::any_SignalType,
                                                           EventManager::normal_Priority );
    }

    void SetContext( SquirrelContext& vm )
    {
        m_vm = &vm;
    }

    SquirrelContext* m_vm;
};
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSlotType_1( const std::string& squirrelSlotTypeName,
                       SquirrelContext& squirrelContext )
{
    Sqrat::DefaultVM::Set( squirrelContext.GetVM().getVM() );
    typedef SlotConnector_1< T > connectorType;
    Sqrat::RootTable().Bind( squirrelSlotTypeName.c_str(), Sqrat::Class< connectorType >()
                           .Func( "ConnectSlotToSignal", &connectorType::ConnectSlotToSignal ) );

    connectorType* connector = new connectorType;
    connector->SetContext( squirrelContext );
    Sqrat::RootTable().SetInstance( squirrelSlotTypeName.c_str(), connector );
}
////////////////////////////////////////////////////////////////////////////////
*/

// The macros that are used to build up different versions of the above...
#define CONNECTOR_BODY_ONE public:\
    void Connect( const char* slotName, const char* signalPattern )\
    {\
        SqratFunctionPtr sqFunc = SqratFunctionPtr( new Sqrat::Function( Sqrat::RootTable().\
                              GetFunction( slotName ) ) );\
        m_vm->StoreSqratFunction( sqFunc );\
        std::string pattern;\
        pattern.assign(  signalPattern )

#define CONNECTOR_CONNECTSIGNALS_ARGS pattern,\
    &Sqrat::Function::Execute,\
    sqFunc.get(),\
    m_vm->GetConnections(),\
    EventManager::any_SignalType,\
    EventManager::normal_Priority

#define CONNECTOR_BODY_TWO }\
    void SetContext( SquirrelContext& vm )\
    {\
        m_vm = &vm;\
    }\
    \
    SquirrelContext* m_vm


#define EXPOSE_SLOT_BODY_ONE Sqrat::DefaultVM::Set( squirrelContext.GetVM().GetVM() )

#define EXPOSE_SLOT_BODY_TWO Sqrat::RootTable().Bind( squirrelSlotTypeName.c_str(), Sqrat::Class< connectorType >( Sqrat::DefaultVM::Get(), squirrelSlotTypeName )\
    .Func( "ConnectSlotToSignal", &connectorType::Connect ) );\
    \
    connectorType* connector = new connectorType;\
    connector->SetContext( squirrelContext );\
    Sqrat::RootTable().SetInstance( squirrelSlotTypeName.c_str(), connector )




// The actual template classes and functors...
////////////////////////////////////////////////////////////////////////////////
template< class TT >
class SlotConnector_0
{
    CONNECTOR_BODY_ONE;
        switchwire::ConnectSignals_0< TT, Sqrat::Function >( CONNECTOR_CONNECTSIGNALS_ARGS );
    CONNECTOR_BODY_TWO;
};
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSlotType_0( const std::string& squirrelSlotTypeName,
                       SquirrelContext& squirrelContext )
{
    EXPOSE_SLOT_BODY_ONE;
    typedef SlotConnector_0< T > connectorType;
    EXPOSE_SLOT_BODY_TWO;
}
////////////////////////////////////////////////////////////////////////////////
template< class TT >
class SlotConnector_1
{
    CONNECTOR_BODY_ONE;
        switchwire::ConnectSignals_1< TT, Sqrat::Function >( CONNECTOR_CONNECTSIGNALS_ARGS );
    CONNECTOR_BODY_TWO;
};
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSlotType_1( const std::string& squirrelSlotTypeName,
                       SquirrelContext& squirrelContext )
{
    EXPOSE_SLOT_BODY_ONE;
    typedef SlotConnector_1< T > connectorType;
    EXPOSE_SLOT_BODY_TWO;
}
////////////////////////////////////////////////////////////////////////////////
template< class TT >
class SlotConnector_2
{
    CONNECTOR_BODY_ONE;
        switchwire::ConnectSignals_2< TT, Sqrat::Function >( CONNECTOR_CONNECTSIGNALS_ARGS );
    CONNECTOR_BODY_TWO;
};
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSlotType_2( const std::string& squirrelSlotTypeName,
                       SquirrelContext& squirrelContext )
{
    EXPOSE_SLOT_BODY_ONE;
    typedef SlotConnector_2< T > connectorType;
    EXPOSE_SLOT_BODY_TWO;
}
////////////////////////////////////////////////////////////////////////////////
template< class TT >
class SlotConnector_3
{
    CONNECTOR_BODY_ONE;
        switchwire::ConnectSignals_3< TT, Sqrat::Function >( CONNECTOR_CONNECTSIGNALS_ARGS );
    CONNECTOR_BODY_TWO;
};
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSlotType_3( const std::string& squirrelSlotTypeName,
                       SquirrelContext& squirrelContext )
{
    EXPOSE_SLOT_BODY_ONE;
    typedef SlotConnector_3< T > connectorType;
    EXPOSE_SLOT_BODY_TWO;
}
////////////////////////////////////////////////////////////////////////////////
template< class TT >
class SlotConnector_4
{
    CONNECTOR_BODY_ONE;
        switchwire::ConnectSignals_4< TT, Sqrat::Function >( CONNECTOR_CONNECTSIGNALS_ARGS );
    CONNECTOR_BODY_TWO;
};
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSlotType_4( const std::string& squirrelSlotTypeName,
                       SquirrelContext& squirrelContext )
{
    EXPOSE_SLOT_BODY_ONE;
    typedef SlotConnector_4< T > connectorType;
    EXPOSE_SLOT_BODY_TWO;
}
////////////////////////////////////////////////////////////////////////////////
template< class TT >
class SlotConnector_5
{
    CONNECTOR_BODY_ONE;
        switchwire::ConnectSignals_5< TT, Sqrat::Function >( CONNECTOR_CONNECTSIGNALS_ARGS );
    CONNECTOR_BODY_TWO;
};
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSlotType_5( const std::string& squirrelSlotTypeName,
                       SquirrelContext& squirrelContext )
{
    EXPOSE_SLOT_BODY_ONE;
    typedef SlotConnector_5< T > connectorType;
    EXPOSE_SLOT_BODY_TWO;
}
////////////////////////////////////////////////////////////////////////////////
}// namespace switchwire
