// Caramel C++ Library - Lexical Facility - Boolean Header

#ifndef __CARAMEL_LEXICAL_BOOLEAN_H
#define __CARAMEL_LEXICAL_BOOLEAN_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


namespace Caramel
{

namespace Lexical
{

///////////////////////////////////////////////////////////////////////////////
//
// Boolean
// - Convert string into boolean.
//

class Boolean
{
public:
    Boolean();
    explicit Boolean( Bool defaultValue );


    /// Properties ///

    operator Bool() const { return m_value; }


    //
    // Try Parse
    // - Returns true if the input string is the followin format,
    //   case insensitive:
    //
    //   True  : "true", "t", "yes", "ok", integers not 0
    //   False : "false", "f", "no", "0"
    //
    //   Otherwise returns false
    //
    Bool TryParse( const std::string& input );


private:
    Bool m_value;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline Boolean::Boolean()
    : m_value( false )
{
}


inline Boolean::Boolean( Bool defaultValue )
    : m_value( defaultValue )
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Lexical

} // namespace Caramel

#endif // __CARAMEL_LEXICAL_BOOLEAN_H
