// Caramel C++ Library - String Facility - Basic String Header

#ifndef __CARAMEL_STRING_BASIC_STRING_H
#define __CARAMEL_STRING_BASIC_STRING_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Basic String
//

template< typename StringType, typename TraitsType >
class BasicString : public StringType
{
protected:

    /// Constructors ///

    BasicString() {}

    BasicString( const StringType& s )
        : StringType( s )
    {}
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_BASIC_STRING_H
