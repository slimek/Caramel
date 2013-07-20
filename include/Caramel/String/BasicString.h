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

template< typename Derived, typename String, typename Traits >
class BasicString
{
public:

    typedef String StringType;
    typedef Traits TraitsType;


    /// Properties ///

    Bool IsEmpty() const { return m_string.empty(); }


protected:

    BasicString();
    BasicString( const String& s );


    /// Data Members ///

    String m_string;
};


//
// Implementation
//

template< typename Derived, typename String, typename Traits >
inline BasicString< Derived, String, Traits >::BasicString()
{
}


template< typename Derived, typename String, typename Traits >
inline BasicString< Derived, String, Traits >::BasicString( const String& s )
    : m_string( s )
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_BASIC_STRING_H
