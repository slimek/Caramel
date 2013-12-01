// Caramel C++ Library - Lexical Facility - Integer List Header

#ifndef __CARAMEL_LEXICAL_INTEGER_LIST_H
#define __CARAMEL_LEXICAL_INTEGER_LIST_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Lexical/Integer.h>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <deque>


namespace Caramel
{

namespace Lexical
{

///////////////////////////////////////////////////////////////////////////////
//
// Integer List
//

template< typename ValueType >
class IntegerList
{
public:

    /// Properties ///

    Uint Size() const { return m_values.size(); }

    ValueType operator[]( Uint index ) const { return m_values[index]; }


    //
    // Try Parse
    // - Returns false if the input string is bad format.
    //
    Bool TryParse( const std::string& input, const std::string& separators );


private:
    typedef std::deque< ValueType > ValueList;
    ValueList m_values;    
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementations
//

template< typename ValueType >
inline Bool IntegerList< ValueType >::TryParse( const std::string& input, const std::string& separators )
{
    std::deque< std::string > tokens;
    boost::split( tokens, input, boost::is_any_of( separators ));

    for ( Uint i = 0; i < tokens.size(); ++ i )
    {
        Integer< ValueType > ivalue;
        if ( !ivalue.TryParse( tokens[i] ))
        {
            return false;
        }
        m_values.push_back( ivalue );
    }

    return true;
}


///////////////////////////////////////////////////////////////////////////////


} // namespace Lexical

} // namespace Caramel

#endif // __CARAMEL_LEXICAL_INTEGER_LIST_H
