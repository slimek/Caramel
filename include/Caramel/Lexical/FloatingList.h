// Caramel C++ Library - Lexical Facility - Floating List Header

#ifndef __CARAMEL_LEXICAL_FLOATING_LIST_H
#define __CARAMEL_LEXICAL_FLOATING_LIST_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Lexical/Floating.h>
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
// Floating List
// - Convert a string into a list of floating values.
//

template< typename Value >
class FloatingList
{
    static_assert( std::is_floating_point< Value >::value, "Value must be floating" );

public:

    typedef Value ValueType;

    
    /// Properties ///

    Usize Size() const { return m_values.size(); }

    ValueType operator[]( Usize index ) const { return m_values[index]; }


    /// Conversions ///

    // Returns false if the input string is bad format.
    Bool TryParse( const std::string& input, const std::string& separators );


private:

    typedef std::deque< Value > ValueList;
    ValueList m_values;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename Value >
inline Bool FloatingList< Value >::TryParse(
    const std::string& input, const std::string& separators )
{
    m_values.clear();

    std::deque< std::string > tokens;
    boost::split( tokens, input, boost::is_any_of( separators ), boost::token_compress_on );

    for ( const auto& token : tokens )
    {
        Floating< Value > fvalue;
        if ( ! fvalue.TryParse( token ))
        {
            return false;
        }
        m_values.push_back( fvalue );
    }

    return true;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Lexical

} // namespace Caramel

#endif // __CARAMEL_LEXICAL_FLOATING_LIST_H
