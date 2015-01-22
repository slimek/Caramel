// Caramel C++ Library - String Facility - Number Format Header

#ifndef __CARAMEL_STRING_NUMBER_FORMAT_H
#define __CARAMEL_STRING_NUMBER_FORMAT_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Number Format
// - Used for arithmetic types. Parse the format string to extract
//   the specifier and the precision.
//

class NumberFormat
{
public:
    
    explicit NumberFormat( const std::string& format );

    Char Specifier() const { return m_specifier; }

    Uint Precision( Uint defaultPrecision ) const;


private:

    Char m_specifier { '\0' };
    Uint m_precision { 0 };
    Bool m_hasPrecision { false };
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_NUMBER_FORMAT_H
