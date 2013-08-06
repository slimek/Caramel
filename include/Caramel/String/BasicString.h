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


    /// Predicates ///

    Bool EndsWith( CharType c ) const;


    /// Extractors ///

    Derived Substr( Uint start ) const;
    Derived Substr( Uint start, Uint length ) const;

    Derived BeforeFirst( CharType c ) const;
    Derived AfterFirst( CharType c ) const;


    /// Manipulators ///

    void Trim();

};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

//
// Predicates
//

template< typename Derived, typename String, typename Traits >
inline Bool BasicString< Derived, String, Traits >::EndsWith( CharType c ) const
{
    const std::string& s = CDERIVED_THIS->m_s;
    if ( s.empty() ) { return false; }
    return c == s[ s.length() - 1 ];
}


//
// Extractors
//

template< typename Derived, typename String, typename Traits >
inline Derived BasicString< Derived, String, Traits >::Substr( Uint start ) const
{
    return Derived( CDERIVED_THIS->m_s.substr( start ));
}


template< typename Derived, typename String, typename Traits >
inline Derived BasicString< Derived, String, Traits >::Substr( Uint start, Uint length ) const
{
    return Derived( CDERIVED_THIS->m_s.substr( start, length ));
}


template< typename Derived, typename String, typename Traits >
inline Derived BasicString< Derived, String, Traits >::BeforeFirst( CharType c ) const
{
    const std::string& s = CDERIVED_THIS->m_s;
    const Uint pos = s.find_first_of( c );
    return std::string::npos == pos ? Derived( s )
                                    : this->Substr( 0, pos );
}


template< typename Derived, typename String, typename Traits >
inline Derived BasicString< Derived, String, Traits >::AfterFirst( CharType c ) const
{
    const std::string& s = CDERIVED_THIS->m_s;
    const Uint pos = s.find_first_of( c );
    return std::string::npos == pos ? Derived()
                                    : this->Substr( pos + 1 );
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
