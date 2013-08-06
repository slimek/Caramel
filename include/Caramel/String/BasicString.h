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

#define DERIVED_THIS  static_cast< Derived* >( this )
#define CDERIVED_THIS static_cast< const Derived* >( this )

template< typename Derived, typename String, typename Traits >
class BasicString
{
public:

    typedef String StringType;
    typedef Traits TraitsType;

    typedef typename TraitsType::CharType CharType;


    /// Properties ///

    Bool IsEmpty() const { return CDERIVED_THIS->m_s.empty(); }
    Uint Length()  const { return CDERIVED_THIS->m_s.length(); }

    const CharType& operator[]( Uint pos ) const { return CDERIVED_THIS->m_s[ pos ]; }


    /// Extractors ///

    Derived Substr( Uint start, Uint length ) const;


    /// Manipulators ///

    void Trim();

};


//
// Implementation
//

//
// Extractors
//

template< typename Derived, typename String, typename Traits >
inline Derived BasicString< Derived, String, Traits >::Substr( Uint start, Uint length ) const
{
    return Derived( CDERIVED_THIS->m_s.substr( start, length ));
}


//
// Manipulators
//

template< typename Derived, typename String, typename Traits >
inline void BasicString< Derived, String, Traits >::Trim()
{
    typedef typename Traits::CoreType Core;
    Core::Trim( DERIVED_THIS->m_s );
}


#undef DERIVED_THIS
#undef CDERIVED_THIS

///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_BASIC_STRING_H
