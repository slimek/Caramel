// Caramel C++ Library - Lexical Facility - Integer List Header

#ifndef __CARAMEL_LEXICAL_INTEGER_LIST_H
#define __CARAMEL_LEXICAL_INTEGER_LIST_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Lexical/Integer.h>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <deque>
#include <type_traits>


namespace Caramel
{

namespace Lexical
{

///////////////////////////////////////////////////////////////////////////////
//
// Integer List
// - Convert a string into a list of integer values.
//

template< typename Value >
class IntegerList
{
    static_assert( std::is_integral< Value >::value, "Value must be integral" );

    typedef std::deque< Value > ValueList;

public:

    typedef Value ValueType;

    
    /// Properties ///

    Usize Size() const { return m_values.size(); }

    ValueType operator[]( Usize index ) const { return m_values[index]; }


    /// Conversions ///

    // Returns false if the input string is bad format.
    Bool TryParse( const std::string& input, const std::string& separators );


    /// Supports range-based for loop ///

    typedef typename ValueList::const_iterator const_iterator;

    const_iterator begin() const { return m_values.begin(); }
    const_iterator end()   const { return m_values.end(); }


private:

    ValueList m_values;    
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementations
//

template< typename Value >
inline Bool IntegerList< Value >::TryParse(
    const std::string& input, const std::string& separators )
{
    m_values.clear();

    std::deque< std::string > tokens;
    boost::split( tokens, input, boost::is_any_of( separators ), boost::token_compress_on );

    for ( const auto& token : tokens )
    {
        Integer< Value > ivalue;
        if ( !ivalue.TryParse( token ))
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
