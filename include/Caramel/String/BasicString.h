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

    typedef typename TraitsType::CharType CharType;


    /// Properties ///

    Bool IsEmpty() const { return m_string.empty(); }
    Uint Length()  const { return m_string.length(); }

    const CharType& operator[]( Uint pos ) const { return m_string[ pos ]; }


    /// Extractors ///

    Derived Substr( Uint start, Uint length ) const;


    /// Manipulators ///

    void Trim();


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


//
// Extractors
//

template< typename Derived, typename String, typename Traits >
inline Derived BasicString< Derived, String, Traits >::Substr( Uint start, Uint length ) const
{
    return Derived( m_string.substr( start, length ));
}


//
// Manipulators
//

template< typename Derived, typename String, typename Traits >
inline void BasicString< Derived, String, Traits >::Trim()
{
    typedef typename Traits::CoreType Core;
    Core::Trim( m_string );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_BASIC_STRING_H
