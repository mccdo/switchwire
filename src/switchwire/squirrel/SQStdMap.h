#pragma once

#include <map>
#include <string>

template< class K, class V >
class SQStdMap
{
public:
    void add( K key, V value )
    {
        m_map[ key ] = value;
    }

    V get( K key )
    {
        return m_map[ key ];
    }

    V find( K key )
    {
        typename std::map< K, V >::const_iterator it = m_map.find( key );
        if( it != m_map.end() )
        {
            return it->second;
        }
        else
        {
            return V();
        }
    }

    void clear()
    {
        m_map.clear();
    }

    size_t count( K key )
    {
        return m_map.count( key );
    }

    bool empty()
    {
        return m_map.empty();
    }

    void erase( K key )
    {
        m_map.erase( key );
    }

private:
    typename std::map< K, V > m_map;
};
////////////////////////////////////////////////////////////////////////////////
template< typename K, typename V >
void BindSQStdMap( const std::string& squirrelClassName )
{
    typedef SQStdMap< K, V > mapType;
    Sqrat::RootTable().Bind( squirrelClassName.c_str(), Sqrat::Class< mapType >()
                             .Func( "add", &mapType::add )
                             .Func( "get", &mapType::get )
                             .Func( "find", &mapType::find )
                             .Func( "erase", &mapType::erase )
                             .Func( "empty", &mapType::empty )
                             .Func( "count", &mapType::count )
                             .Func( "clear", &mapType::clear) );
}
