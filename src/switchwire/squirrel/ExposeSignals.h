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

#include <switchwire/Event.h>

#include <switchwire/squirrel/SquirrelContext.h>
#include <switchwire/squirrel/ManagedLifetime.h>

#include <boost/pointer_cast.hpp>
#include <boost/type_traits.hpp>

namespace switchwire
{

////////////////////////////////////////////////////////////////////////////////
/// Wrapper class used in ExposeSignal_N function templates.
template< class Signature >
class SQEventWrapper : public ManagedLifetime
{
public:
    SQEventWrapper():
        m_event( 0 ),
        m_manageEventLifetime( false )
    {
        ;
    }

    ~SQEventWrapper()
    {
        if( m_manageEventLifetime )
        {
            delete m_event;
        }
    }

    void setEvent( switchwire::Event< Signature>* event, bool manageEventLifetime )
    {
        m_event = event;
        m_manageEventLifetime = manageEventLifetime;
    }

    typename boost::function_traits< Signature >::result_type signal()
    {
        return m_event->signal();
    }

    template< typename A1 >
    typename boost::function_traits< Signature >::result_type signal( A1 a1 )
    {
        return m_event->signal( a1 );
    }

    template< typename A1, typename A2 >
    typename boost::function_traits< Signature >::result_type signal( A1 a1, A2 a2 )
    {
        return m_event->signal( a1, a2 );
    }

    template< typename A1, typename A2, typename A3 >
    typename boost::function_traits< Signature >::result_type signal( A1 a1, A2 a2, A3 a3 )
    {
        return m_event->signal( a1, a2, a3 );
    }

    template< typename A1, typename A2, typename A3, typename A4 >
    typename boost::function_traits< Signature >::result_type signal( A1 a1, A2 a2, A3 a3, A4 a4 )
    {
        return m_event->signal( a1, a2, a3, a4 );
    }

    template< typename A1, typename A2, typename A3, typename A4, typename A5 >
    typename boost::function_traits< Signature >::result_type signal( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5 )
    {
        return m_event->signal( a1, a2, a3, a4, a5 );
    }

    // switchwire only supports 5 arguments for right now, so we can stop here.

    switchwire::Event< Signature >* m_event;
    bool m_manageEventLifetime;
};
////////////////////////////////////////////////////////////////////////////////
// Example of full ExposeSignal_N functor without macro buildup.
/*
template< typename T >
void ExposeSignal_1( switchwire::Event< T >* event,
                     const std::string& squirrelName,
                     SquirrelContext& vm,
                     bool manageEventLifetime = false )
{
    Sqrat::DefaultVM::Set( vm.GetVM().getVM() );
    typedef SQEventWrapper< T > wrapperType;
    Sqrat::Class< wrapperType > signalClass;
    signalClass.template Func< typename boost::function_traits< T >::result_type
                (wrapperType::*)
                ( typename boost::function_traits< T >::arg1_type )>
                ( "signal", &wrapperType::signal );
    std::string className = "sq_class" + squirrelName;
    Sqrat::RootTable().Bind( className.c_str(), signalClass );
    ManagedLifetimePtr wrapper = ManagedLifetimePtr( new wrapperType );
    vm.StoreManagedLifetimeObject( wrapper );
    boost::static_pointer_cast< wrapperType >(wrapper)->setEvent( event, manageEventLifetime );
    Sqrat::RootTable().SetInstance( squirrelName.c_str(), boost::static_pointer_cast< wrapperType >(wrapper).get() );
}
*/

#define SW_EXPOSESIGNAL_ONE Sqrat::DefaultVM::Set( vm.GetVM().getVM() );\
    typedef SQEventWrapper< T > wrapperType;\
    Sqrat::Class< wrapperType > signalClass;\
    signalClass.template Func< typename boost::function_traits< T >::result_type\
            (wrapperType::*)

#define SW_EXPOSESIGNAL_TWO  >\
    ( "signal", &wrapperType::signal );\
    std::string className = "sq_class" + squirrelName;\
    Sqrat::RootTable().Bind( className.c_str(), signalClass );\
    ManagedLifetimePtr wrapper = ManagedLifetimePtr( new wrapperType );\
    vm.StoreManagedLifetimeObject( wrapper );\
    boost::static_pointer_cast< wrapperType >(wrapper)->setEvent( event, manageEventLifetime );\
    Sqrat::RootTable().SetInstance( squirrelName.c_str(), boost::static_pointer_cast< wrapperType >(wrapper).get() );


////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSignal_0( switchwire::Event< T >* event,
                     const std::string& squirrelName,
                     SquirrelContext& vm,
                     bool manageEventLifetime = false )
{
    SW_EXPOSESIGNAL_ONE
            ( )
    SW_EXPOSESIGNAL_TWO
}
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSignal_1( switchwire::Event< T >* event,
                     const std::string& squirrelName,
                     SquirrelContext& vm,
                     bool manageEventLifetime = false )
{
    SW_EXPOSESIGNAL_ONE
            ( typename boost::function_traits< T >::arg1_type)
    SW_EXPOSESIGNAL_TWO
}
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSignal_2( switchwire::Event< T >* event,
                     const std::string& squirrelName,
                     SquirrelContext& vm,
                     bool manageEventLifetime = false )
{
    SW_EXPOSESIGNAL_ONE
            ( typename boost::function_traits< T >::arg1_type,
              typename boost::function_traits< T >::arg2_type )
    SW_EXPOSESIGNAL_TWO
}
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSignal_3( switchwire::Event< T >* event,
                     const std::string& squirrelName,
                     SquirrelContext& vm,
                     bool manageEventLifetime = false )
{
    SW_EXPOSESIGNAL_ONE
            ( typename boost::function_traits< T >::arg1_type,
              typename boost::function_traits< T >::arg2_type,
              typename boost::function_traits< T >::arg3_type )
    SW_EXPOSESIGNAL_TWO
}
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSignal_4( switchwire::Event< T >* event,
                     const std::string& squirrelName,
                     SquirrelContext& vm,
                     bool manageEventLifetime = false )
{
    SW_EXPOSESIGNAL_ONE
            ( typename boost::function_traits< T >::arg1_type,
              typename boost::function_traits< T >::arg2_type,
              typename boost::function_traits< T >::arg3_type,
              typename boost::function_traits< T >::arg4_type )
    SW_EXPOSESIGNAL_TWO
}
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSignal_5( switchwire::Event< T >* event,
                     const std::string& squirrelName,
                     SquirrelContext& vm,
                     bool manageEventLifetime = false )
{
    SW_EXPOSESIGNAL_ONE
            ( typename boost::function_traits< T >::arg1_type,
              typename boost::function_traits< T >::arg2_type,
              typename boost::function_traits< T >::arg3_type,
              typename boost::function_traits< T >::arg4_type,
              typename boost::function_traits< T >::arg5_type)
    SW_EXPOSESIGNAL_TWO
}
////////////////////////////////////////////////////////////////////////////////

// Example of full SetupSignal_N template class without macro buildup
/*
template< class TT >
class SetupSignal_1 : public ManagedLifetime
{
public:
    void Create( const char* signalName, const char* squirrelName )
    {
        Event< TT >* ev = new switchwire::Event< TT >;
        std::string name;
        name.assign( signalName );
        EventManager::instance()->RegisterSignal( ev, name );
        name.assign( squirrelName );
        ExposeSignal_1< TT >( ev, name, *m_context );
    }

    void SetContext( SquirrelContext& context )
    {
        m_context = &context;
    }

    SquirrelContext* m_context;
};
*/

#define SW_SETUPSIGNAL_ONE public:\
void Create( const char* signalName, const char* squirrelName )\
    {\
        Event< TT >* ev = new Event< TT >;\
        std::string name;\
        name.assign( signalName );\
        EventManager::instance()->RegisterSignal( ev, name );\
        name.assign( squirrelName );
// ^^^ The Event allocated above does not leak because its lifetime is managed
// by an SQEventWrapper for the event, and the SquirrelContext manages the
// lifetime of the SQEventWrapper.
#define SW_SETUPSIGNAL_TWO }\
    \
    void SetContext( SquirrelContext& context )\
    {\
        m_context = &context;\
    }\
    \
    SquirrelContext* m_context;

////////////////////////////////////////////////////////////////////////////////
template< class TT >
class SetupSignal_0 : public ManagedLifetime
{
    SW_SETUPSIGNAL_ONE
        ExposeSignal_0< TT >( ev, name, *m_context, true );
    SW_SETUPSIGNAL_TWO
};
////////////////////////////////////////////////////////////////////////////////
template< class TT >
class SetupSignal_1 : public ManagedLifetime
{
    SW_SETUPSIGNAL_ONE
        ExposeSignal_1< TT >( ev, name, *m_context, true );
    SW_SETUPSIGNAL_TWO
};
////////////////////////////////////////////////////////////////////////////////
template< class TT >
class SetupSignal_2 : public ManagedLifetime
{
    SW_SETUPSIGNAL_ONE
        ExposeSignal_2< TT >( ev, name, *m_context, true );
    SW_SETUPSIGNAL_TWO
};
////////////////////////////////////////////////////////////////////////////////
template< class TT >
class SetupSignal_3 : public ManagedLifetime
{
    SW_SETUPSIGNAL_ONE
        ExposeSignal_3< TT >( ev, name, *m_context, true );
    SW_SETUPSIGNAL_TWO
};
////////////////////////////////////////////////////////////////////////////////
template< class TT >
class SetupSignal_4 : public ManagedLifetime
{
    SW_SETUPSIGNAL_ONE
        ExposeSignal_4< TT >( ev, name, *m_context, true );
    SW_SETUPSIGNAL_TWO
};
////////////////////////////////////////////////////////////////////////////////
template< class TT >
class SetupSignal_5 : public ManagedLifetime
{
    SW_SETUPSIGNAL_ONE
        ExposeSignal_5< TT >( ev, name, *m_context, true );
    SW_SETUPSIGNAL_TWO
};
////////////////////////////////////////////////////////////////////////////////

// Full example of ExposeSignalType_N functor without macro buildup
/*
template< typename T >
void ExposeSignalType_1( const std::string& squirrelSignalTypeName,
                         SquirrelContext& context )
{
    Sqrat::DefaultVM::Set( context.GetVM().getVM() );
    typedef SetupSignal_1< T > setupType;
    Sqrat::RootTable().Bind( squirrelSignalTypeName.c_str(),
                             Sqrat::Class< setupType >()
                            .Func( "RegisterSignal", &setupType::Create ) );

    ManagedLifetimePtr setup = ManagedLifetimePtr( new setupType );
    context.StoreManagedLifetimeObject( setup );
    boost::static_pointer_cast< setupType >(setup)->SetContext( context );
    Sqrat::RootTable().SetInstance( squirrelSignalTypeName.c_str(), boost::static_pointer_cast< setupType >(setup).get() );
}
*/

#define SW_EXPOSESIGNALTYPE_ONE Sqrat::DefaultVM::Set( context.GetVM().getVM() );


#define SW_EXPOSESIGNALTYPE_TWO \
    Sqrat::RootTable().Bind( squirrelSignalTypeName.c_str(),\
                             Sqrat::Class< setupType >()\
                            .Func( "RegisterSignal", &setupType::Create ) );\
    \
    ManagedLifetimePtr setup = ManagedLifetimePtr( new setupType );\
    context.StoreManagedLifetimeObject( setup );\
    boost::static_pointer_cast< setupType >(setup)->SetContext( context );\
    Sqrat::RootTable().SetInstance( squirrelSignalTypeName.c_str(), boost::static_pointer_cast< setupType >(setup).get() );


////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSignalType_0( const std::string& squirrelSignalTypeName,
                         SquirrelContext& context )
{
    SW_EXPOSESIGNALTYPE_ONE
    typedef SetupSignal_0< T > setupType;
    SW_EXPOSESIGNALTYPE_TWO
}
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSignalType_1( const std::string& squirrelSignalTypeName,
                         SquirrelContext& context )
{
    SW_EXPOSESIGNALTYPE_ONE
    typedef SetupSignal_1< T > setupType;
    SW_EXPOSESIGNALTYPE_TWO
}
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSignalType_2( const std::string& squirrelSignalTypeName,
                         SquirrelContext& context )
{
    SW_EXPOSESIGNALTYPE_ONE
    typedef SetupSignal_2< T > setupType;
    SW_EXPOSESIGNALTYPE_TWO
}
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSignalType_3( const std::string& squirrelSignalTypeName,
                         SquirrelContext& context )
{
    SW_EXPOSESIGNALTYPE_ONE
    typedef SetupSignal_3< T > setupType;
    SW_EXPOSESIGNALTYPE_TWO
}
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSignalType_4( const std::string& squirrelSignalTypeName,
                         SquirrelContext& context )
{
    SW_EXPOSESIGNALTYPE_ONE
    typedef SetupSignal_4< T > setupType;
    SW_EXPOSESIGNALTYPE_TWO
}
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSignalType_5( const std::string& squirrelSignalTypeName,
                         SquirrelContext& context )
{
    SW_EXPOSESIGNALTYPE_ONE
    typedef SetupSignal_5< T > setupType;
    SW_EXPOSESIGNALTYPE_TWO
}
////////////////////////////////////////////////////////////////////////////////
} //namespace switchwire


/*
* Different possible way of doing ExposeSignal which wouldn't require using
* numerical subscripts on the functor name. The undesirable thing about this
* technique is that the signal signature has to be broken across the template
* parameters. For example, a void( int, float ) signal would be exposed like
* this:
*
* ExposeSignal< void, int, float >( &MyEvent, "SomeName", MyVM );
*
* RPT: Leave this code here for now. It may be worth the odd template
* parameters to eliminate the issue of having to explicitly choose the correct
* template.
*/
/*
template< class R >
void ExposeSignal( switchwire::Event< R () >* event,
                     const std::string& squirrelName,
                     Sqrat::SqratVM& vm )
{
    Sqrat::DefaultVM::Set( vm.getVM() );
    typedef SQEventWrapper< R () > wrapperType;
    Sqrat::Class< wrapperType > signalClass;
    signalClass.template Func< R (wrapperType::*) () >
            ( "signal", &wrapperType::signal );
    std::string className = "sq_class" + squirrelName;
    Sqrat::RootTable().Bind( className.c_str(), signalClass );
    wrapperType* wrapper = new wrapperType;
    wrapper->setEvent( event );
    Sqrat::RootTable().SetInstance( squirrelName.c_str(), wrapper );
}
////////////////////////////////////////////////////////////////////////////////
template< class R, class A1 >
void ExposeSignal( switchwire::Event< R (A1) >* event,
                     const std::string& squirrelName,
                     Sqrat::SqratVM& vm )
{
    Sqrat::DefaultVM::Set( vm.getVM() );
    typedef SQEventWrapper< R (A1) > wrapperType;
    Sqrat::Class< wrapperType > signalClass;
    signalClass.template Func< R (wrapperType::*) (A1) >
            ( "signal", &wrapperType::signal );
    std::string className = "sq_class" + squirrelName;
    Sqrat::RootTable().Bind( className.c_str(), signalClass );
    wrapperType* wrapper = new wrapperType;
    wrapper->setEvent( event );
    Sqrat::RootTable().SetInstance( squirrelName.c_str(), wrapper );
}
////////////////////////////////////////////////////////////////////////////////
template< class R, class A1, class A2 >
void ExposeSignal( switchwire::Event< R (A1, A2) >* event,
                     const std::string& squirrelName,
                     Sqrat::SqratVM& vm )
{
    Sqrat::DefaultVM::Set( vm.getVM() );
    typedef SQEventWrapper< R (A1, A2) > wrapperType;
    Sqrat::Class< wrapperType > signalClass;
    signalClass.template Func< R (wrapperType::*) (A1, A2) >
            ( "signal", &wrapperType::signal );
    std::string className = "sq_class" + squirrelName;
    Sqrat::RootTable().Bind( className.c_str(), signalClass );
    wrapperType* wrapper = new wrapperType;
    wrapper->setEvent( event );
    Sqrat::RootTable().SetInstance( squirrelName.c_str(), wrapper );
}
////////////////////////////////////////////////////////////////////////////////
template< class R, class A1, class A2, class A3 >
void ExposeSignal( switchwire::Event< R (A1, A2, A3) >* event,
                     const std::string& squirrelName,
                     Sqrat::SqratVM& vm )
{
    Sqrat::DefaultVM::Set( vm.getVM() );
    typedef SQEventWrapper< R (A1, A2, A3) > wrapperType;
    Sqrat::Class< wrapperType > signalClass;
    signalClass.template Func< R (wrapperType::*) (A1, A2, A3) >
            ( "signal", &wrapperType::signal );
    std::string className = "sq_class" + squirrelName;
    Sqrat::RootTable().Bind( className.c_str(), signalClass );
    wrapperType* wrapper = new wrapperType;
    wrapper->setEvent( event );
    Sqrat::RootTable().SetInstance( squirrelName.c_str(), wrapper );
}
////////////////////////////////////////////////////////////////////////////////
template< class R, class A1, class A2, class A3, class A4 >
void ExposeSignal( switchwire::Event< R (A1, A2, A3, A4) >* event,
                     const std::string& squirrelName,
                     Sqrat::SqratVM& vm )
{
    Sqrat::DefaultVM::Set( vm.getVM() );
    typedef SQEventWrapper< R (A1, A2, A3, A4) > wrapperType;
    Sqrat::Class< wrapperType > signalClass;
    signalClass.template Func< R (wrapperType::*) (A1, A2, A3, A4) >
            ( "signal", &wrapperType::signal );
    std::string className = "sq_class" + squirrelName;
    Sqrat::RootTable().Bind( className.c_str(), signalClass );
    wrapperType* wrapper = new wrapperType;
    wrapper->setEvent( event );
    Sqrat::RootTable().SetInstance( squirrelName.c_str(), wrapper );
}
////////////////////////////////////////////////////////////////////////////////
template< class R, class A1, class A2, class A3, class A4, class A5 >
void ExposeSignal( switchwire::Event< R (A1, A2, A3, A4, A5) >* event,
                     const std::string& squirrelName,
                     Sqrat::SqratVM& vm )
{
    Sqrat::DefaultVM::Set( vm.getVM() );
    typedef SQEventWrapper< R (A1, A2, A3, A4) > wrapperType;
    Sqrat::Class< wrapperType > signalClass;
    signalClass.template Func< R (wrapperType::*) (A1, A2, A3, A4, A5) >
            ( "signal", &wrapperType::signal );
    std::string className = "sq_class" + squirrelName;
    Sqrat::RootTable().Bind( className.c_str(), signalClass );
    wrapperType* wrapper = new wrapperType;
    wrapper->setEvent( event );
    Sqrat::RootTable().SetInstance( squirrelName.c_str(), wrapper );
}
*/
