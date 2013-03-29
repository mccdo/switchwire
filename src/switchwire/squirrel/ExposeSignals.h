#pragma once

#include <switchwire/Event.h>

#include <squirrel.h>
#include <sqrat.h>
#include <sqrat/sqratVM.h>

#include <boost/type_traits.hpp>

////////////////////////////////////////////////////////////////////////////////
/// Wrapper class used in ExposeSignal_N function templates.
template< class Signature >
class SQEventWrapper
{
public:
    void setEvent( switchwire::Event< Signature>* event )
    {
        m_event = event;
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
};
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSignal_0( switchwire::Event< T >* event,
                     const std::string& squirrelName,
                     Sqrat::SqratVM& vm )
{
    Sqrat::DefaultVM::Set( vm.getVM() );
    typedef SQEventWrapper< T > wrapperType;
    Sqrat::Class< wrapperType > signalClass;
    signalClass.template Func< typename boost::function_traits< T >::result_type
            (wrapperType::*)( ) >( "signal", &wrapperType::signal );
    std::string className = "sq_class" + squirrelName;
    Sqrat::RootTable().Bind( className.c_str(), signalClass );
    wrapperType* wrapper = new wrapperType;
    wrapper->setEvent( event );
    Sqrat::RootTable().SetInstance( squirrelName.c_str(), wrapper );
}
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSignal_1( switchwire::Event< T >* event,
                     const std::string& squirrelName,
                     Sqrat::SqratVM& vm )
{
    Sqrat::DefaultVM::Set( vm.getVM() );
    typedef SQEventWrapper< T > wrapperType;
    Sqrat::Class< wrapperType > signalClass;
    signalClass.template Func< typename boost::function_traits< T >::result_type
            (wrapperType::*)
            ( typename boost::function_traits< T >::arg1_type ) >
            ( "signal", &wrapperType::signal );
    std::string className = "sq_class" + squirrelName;
    Sqrat::RootTable().Bind( className.c_str(), signalClass );
    wrapperType* wrapper = new wrapperType;
    wrapper->setEvent( event );
    Sqrat::RootTable().SetInstance( squirrelName.c_str(), wrapper );
}
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSignal_2( switchwire::Event< T >* event,
                     const std::string& squirrelName,
                     Sqrat::SqratVM& vm )
{
    Sqrat::DefaultVM::Set( vm.getVM() );
    typedef SQEventWrapper< T > wrapperType;
    Sqrat::Class< wrapperType > signalClass;
    signalClass.template Func< typename boost::function_traits< T >::result_type
            (wrapperType::*)
            ( typename boost::function_traits< T >::arg1_type,
              typename boost::function_traits< T >::arg2_type ) >
            ( "signal", &wrapperType::signal );
    std::string className = "sq_class" + squirrelName;
    Sqrat::RootTable().Bind( className.c_str(), signalClass );
    wrapperType* wrapper = new wrapperType;
    wrapper->setEvent( event );
    Sqrat::RootTable().SetInstance( squirrelName.c_str(), wrapper );
}
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSignal_3( switchwire::Event< T >* event,
                     const std::string& squirrelName,
                     Sqrat::SqratVM& vm )
{
    Sqrat::DefaultVM::Set( vm.getVM() );
    typedef SQEventWrapper< T > wrapperType;
    Sqrat::Class< wrapperType > signalClass;
    signalClass.template Func< typename boost::function_traits< T >::result_type
            (wrapperType::*)
            ( typename boost::function_traits< T >::arg1_type,
              typename boost::function_traits< T >::arg2_type,
              typename boost::function_traits< T >::arg3_type ) >
            ( "signal", &wrapperType::signal );
    std::string className = "sq_class" + squirrelName;
    Sqrat::RootTable().Bind( className.c_str(), signalClass );
    wrapperType* wrapper = new wrapperType;
    wrapper->setEvent( event );
    Sqrat::RootTable().SetInstance( squirrelName.c_str(), wrapper );
}
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSignal_4( switchwire::Event< T >* event,
                     const std::string& squirrelName,
                     Sqrat::SqratVM& vm )
{
    Sqrat::DefaultVM::Set( vm.getVM() );
    typedef SQEventWrapper< T > wrapperType;
    Sqrat::Class< wrapperType > signalClass;
    signalClass.template Func< typename boost::function_traits< T >::result_type
            (wrapperType::*)
            ( typename boost::function_traits< T >::arg1_type,
              typename boost::function_traits< T >::arg2_type,
              typename boost::function_traits< T >::arg3_type,
              typename boost::function_traits< T >::arg4_type ) >
            ( "signal", &wrapperType::signal );
    std::string className = "sq_class" + squirrelName;
    Sqrat::RootTable().Bind( className.c_str(), signalClass );
    wrapperType* wrapper = new wrapperType;
    wrapper->setEvent( event );
    Sqrat::RootTable().SetInstance( squirrelName.c_str(), wrapper );
}
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSignal_5( switchwire::Event< T >* event,
                     const std::string& squirrelName,
                     Sqrat::SqratVM& vm )
{
    Sqrat::DefaultVM::Set( vm.getVM() );
    typedef SQEventWrapper< T > wrapperType;
    Sqrat::Class< wrapperType > signalClass;
    signalClass.template Func< typename boost::function_traits< T >::result_type
            (wrapperType::*)
            ( typename boost::function_traits< T >::arg1_type,
              typename boost::function_traits< T >::arg2_type,
              typename boost::function_traits< T >::arg3_type,
              typename boost::function_traits< T >::arg4_type,
              typename boost::function_traits< T >::arg5_type) >
            ( "signal", &wrapperType::signal );
    std::string className = "sq_class" + squirrelName;
    Sqrat::RootTable().Bind( className.c_str(), signalClass );
    wrapperType* wrapper = new wrapperType;
    wrapper->setEvent( event );
    Sqrat::RootTable().SetInstance( squirrelName.c_str(), wrapper );
}
////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////
template< class TT >
class SetupSignal_0
{
public:
    void Create( const char* signalName, const char* squirrelName )
    {
        switchwire::Event< TT >* ev = new switchwire::Event< TT >;
        std::string name;
        name.assign( signalName );
        switchwire::EventManager::instance()->RegisterSignal( ev, name );
        name.assign( squirrelName );
        ExposeSignal_0< TT >( ev, name, *m_vm );
    }

    void SetVm( Sqrat::SqratVM& vm )
    {
        m_vm = &vm;
    }

    Sqrat::SqratVM* m_vm;
};
////////////////////////////////////////////////////////////////////////////////
template< class TT >
class SetupSignal_1
{
public:
    void Create( const char* signalName, const char* squirrelName )
    {
        switchwire::Event< TT >* ev = new switchwire::Event< TT >;
        std::string name;
        name.assign( signalName );
        switchwire::EventManager::instance()->RegisterSignal( ev, name );
        name.assign( squirrelName );
        ExposeSignal_1< TT >( ev, name, *m_vm );
    }

    void SetVm( Sqrat::SqratVM& vm )
    {
        m_vm = &vm;
    }

    Sqrat::SqratVM* m_vm;
};
////////////////////////////////////////////////////////////////////////////////
template< class TT >
class SetupSignal_2
{
public:
    void Create( const char* signalName, const char* squirrelName )
    {
        switchwire::Event< TT >* ev = new switchwire::Event< TT >;
        std::string name;
        name.assign( signalName );
        switchwire::EventManager::instance()->RegisterSignal( ev, name );
        name.assign( squirrelName );
        ExposeSignal_2< TT >( ev, name, *m_vm );
    }

    void SetVm( Sqrat::SqratVM& vm )
    {
        m_vm = &vm;
    }

    Sqrat::SqratVM* m_vm;
};
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSignalType_0( const std::string& squirrelSignalTypeName,
                         Sqrat::SqratVM& vm )
{
    Sqrat::DefaultVM::Set(vm.getVM());
    typedef SetupSignal_0< T > setupType;
    Sqrat::RootTable().Bind( squirrelSignalTypeName.c_str(), Sqrat::Class< setupType >()
                             .Func( "RegisterSignal", &setupType::Create ) );

    setupType* setup = new setupType;
    setup->SetVm( vm );
    Sqrat::RootTable().SetInstance( squirrelSignalTypeName.c_str(), setup );
}
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSignalType_1( const std::string& squirrelSignalTypeName,
                         Sqrat::SqratVM& vm )
{
    Sqrat::DefaultVM::Set(vm.getVM());
    typedef SetupSignal_1< T > setupType;
    Sqrat::RootTable().Bind( squirrelSignalTypeName.c_str(), Sqrat::Class< setupType >()
                             .Func( "RegisterSignal", &setupType::Create ) );

    setupType* setup = new setupType;
    setup->SetVm( vm );
    Sqrat::RootTable().SetInstance( squirrelSignalTypeName.c_str(), setup );
}
////////////////////////////////////////////////////////////////////////////////
template< typename T >
void ExposeSignalType_2( const std::string& squirrelSignalTypeName,
                         Sqrat::SqratVM& vm )
{
    Sqrat::DefaultVM::Set(vm.getVM());
    typedef SetupSignal_2< T > setupType;
    Sqrat::RootTable().Bind( squirrelSignalTypeName.c_str(), Sqrat::Class< setupType >()
                             .Func( "RegisterSignal", &setupType::Create ) );

    setupType* setup = new setupType;
    setup->SetVm( vm );
    Sqrat::RootTable().SetInstance( squirrelSignalTypeName.c_str(), setup );
}
