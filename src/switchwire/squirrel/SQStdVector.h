#pragma once
#include <vector>
#include <string>

template< typename T >
void BindSQStdVector( const std::string& squirrelClassName )
{
    typedef typename std::vector<T> vecType;
    Sqrat::RootTable().Bind( squirrelClassName.c_str(), Sqrat::Class< vecType >()
                             .template Func< T& (vecType::*)(size_t) >( "at", &vecType::at )
                             .Func( "push_back", &vecType::push_back )
                             .template Func< size_t (vecType::*)() const >( "size", &vecType::size)
                             .Func( "clear", &vecType::clear) );
}
