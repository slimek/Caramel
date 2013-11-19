// Caramel C++ Library - Lexical Facility - Floating Header

#ifndef __CARAMEL_LEXICAL_FLOATING_H
#define __CARAMEL_LEXICAL_FLOATING_H
#pragma once

#include <Caramel/Caramel.h>
#include <type_traits>


namespace Caramel
{

namespace Lexical
{

///////////////////////////////////////////////////////////////////////////////
//
// Floating
// - Convert numeral strings to floating values.
//   Based on std::strtod()
//

template< typename ValueT >
class Floating
{
    static_assert( std::is_floating_point< ValueT >::value, "ValueT must be floating" );

public:

    typedef ValueT ValueType;

    Floating();


    /// Conversions ///

    operator ValueType() const { return m_value; }


    /// Parsing ///

    // Returns false if the the input is not a valid numeral string
    Bool TryParse( const std::string& input );


private:

    ValueT m_value;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename ValueT >
inline Floating< ValueT >::Floating()
    : m_value( 0 )
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Lexical

} // namespace Caramel

#endif // __CARAMEL_LEXICAL_FLOATING_H
