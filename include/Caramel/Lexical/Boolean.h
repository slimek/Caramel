// Caramel C++ Library - Lexical Facility - Boolean Header

#ifndef __CARAMEL_LEXICAL_BOOLEAN_H
#define __CARAMEL_LEXICAL_BOOLEAN_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


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
    //   True  : "true",  non-Zero integer
    //   False : "false", 0
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
