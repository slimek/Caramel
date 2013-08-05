// Caramel C++ Library - Lexical Facility - Integer Header

#ifndef __CARAMEL_LEXICAL_INTEGER_H
#define __CARAMEL_LEXICAL_INTEGER_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/String/Utf8String.h>
#include <type_traits>


namespace Caramel
{

namespace Lexical
{

///////////////////////////////////////////////////////////////////////////////
//
// Integer
// - Convert numeral strings to integral values.
//   String must be decimal number.
//

template< typename ValueT >
class Integer
{
    static_assert( std::is_integral< ValueT >::value, "ValueT must be integral" );

public:

    typedef ValueT ValueType;

    Integer();
    explicit Integer( ValueType defaultValue );


    /// Properties ///

    operator ValueType() const { return m_value; }

    Bool IsOutOfRange() const { return m_outOfRange; }


    //
    // Try Parse
    // - returns false if input is not valid numeral string,
    //   or it is out of range.
    //
    Bool TryParse( const std::string& input );
    Bool TryParse( const Utf8String& input );


private:
    ValueType m_value;
    Bool      m_outOfRange;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementations
//

template< typename ValueT >
inline Integer< ValueT >::Integer()
    : m_value( 0 )
    , m_outOfRange( false )
{
}


template< typename ValueT >
inline Integer< ValueT >::Integer( ValueT defaultValue )
    : m_value( defaultValue )
    , m_outOfRange( false )
{
}


template< typename ValueT >
inline Bool Integer< ValueT >::TryParse( const Utf8String& input )
{
    return this->TryParse( input.ToString() );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Lexical

} // namespace Caramel

#endif // __CARAMEL_LEXICAL_INTEGER_H
