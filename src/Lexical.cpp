// Caramel C++ Library - Lexical Facility - Implementation

#include "CaramelPch.h"

#include <Caramel/Lexical/Boolean.h>
#include <Caramel/Lexical/Floating.h>
#include <Caramel/Lexical/Integer.h>
#include <Caramel/Lexical/Version.h>
#include <Caramel/String/Algorithm.h>
#include <boost/tokenizer.hpp>


namespace Caramel
{

namespace Lexical
{

//
// Contents
//
//   Boolean
//   Floating
//   Integer
//   Version
//

///////////////////////////////////////////////////////////////////////////////
//
// Boolean
// - Convert strings to booleans
//

Bool Boolean::TryParse( const std::string& input )
{
    // Test if the input is an integer.
    
    Integer< Int > integer;
    if ( integer.TryParse( input ))
    {
        m_value = ( 0 != integer );
        return true;
    }


    // Test if the input is a boolean string

    if ( CainEquals( input, "true" ))
    {
        m_value = true;
        return true;
    }

    if ( CainEquals( input, "false" ))
    {
        m_value = false;
        return true;
    }


    // Then, the input can not be parsed to a boolean.
    return false;
}


///////////////////////////////////////////////////////////////////////////////
//
// Floating
// - Convert strings to floatings.
//

template<>
Bool Floating< Float >::TryParse( const std::string& input )
{
    if ( input.empty() ) { return false; }

    Char* stop = nullptr;

    m_value = ::strtof( input.c_str(), &stop );

    return stop == ( input.data() + input.length() );
}


template<>
Bool Floating< Double >::TryParse( const std::string& input )
{
    if ( input.empty() ) { return false; }

    Char* stop = nullptr;
    m_value = ::strtod( input.c_str(), &stop );

    return stop == ( input.data() + input.length() );
}




///////////////////////////////////////////////////////////////////////////////
//
// Integer
// - Convert strings to integers.
//

template<>
Bool Integer< Int32 >::TryParse( const std::string& input )
{
    if ( input.empty() ) { return false; }

    Char* stop = nullptr;

    if ( CainStartsWith( input, "0x" ))
    {
        m_value = static_cast< Int32 >( ::strtoul( input.c_str(), &stop, 16 ));
    }
    else
    {
        m_value = static_cast< Int32 >( ::strtol( input.c_str(), &stop, 10 ));
    }
    
    return stop == ( input.data() + input.length() );
}


template<>
Bool Integer< Uint32 >::TryParse( const std::string& input )
{
    if ( input.empty() ) { return false; }

    Char* stop = nullptr;

    if ( CainStartsWith( input, "0x" ))
    {
        m_value = static_cast< Uint32 >( ::strtoul( input.c_str(), &stop, 16 ));
    }
    else
    {
        m_value = static_cast< Uint32 >( ::strtoul( input.c_str(), &stop, 10 ));    
    }
    
    return stop == ( input.data() + input.length() );
}


//
// Convert Int64 to String
// - Visual C++ doesn't support strtoull() until 2013.
//

#if defined( CARAMEL_COMPILER_IS_MSVC )
#define CARAMEL_STRTOLL  _strtoi64
#define CARAMEL_STRTOULL _strtoui64
#else
#define CARAMEL_STRTOLL  strtoll
#define CARAMEL_STRTOULL strtoull
#endif

template<>
Bool Integer< Int64 >::TryParse( const std::string& input )
{
    if ( input.empty() ) { return false; }

    Char* stop = nullptr;

    if ( CainStartsWith( input, "0x" ))
    {
        m_value = static_cast< Int64 >( CARAMEL_STRTOULL( input.c_str(), &stop, 16 ));
    }
    else
    {
        m_value = static_cast< Int64 >( CARAMEL_STRTOLL( input.c_str(), &stop, 10 ));
    }
    
    return stop == ( input.data() + input.length() );
}


template<>
Bool Integer< Uint64 >::TryParse( const std::string& input )
{
    if ( input.empty() ) { return false; }

    Char* stop = nullptr;

    if ( CainStartsWith( input, "0x" ))
    {
        m_value = static_cast< Uint64 >( CARAMEL_STRTOULL( input.c_str(), &stop, 16 ));
    }
    else
    {
        m_value = static_cast< Uint64 >( CARAMEL_STRTOULL( input.c_str(), &stop, 10 ));
    }
    
    return stop == ( input.data() + input.length() );
}


//
// Parse Hexidecimal Number
//

template<>
Bool Integer< Uint32 >::TryParseHex( const std::string& input )
{
    if ( input.empty() ) { return false; }

    if ( CainStartsWith( input, "0x" )) { return false; }

    Char* stop = nullptr;
    m_value = static_cast< Uint32 >( ::strtoul( input.c_str(), &stop, 16 ));
    
    return stop == ( input.data() + input.length() );
}


///////////////////////////////////////////////////////////////////////////////
//
// Version
//

Version::Version( Uint32 major, Uint32 minor, Uint32 build, Uint32 revision )
{
    m_majorMinor    = ( static_cast< Uint64 >( major ) << 32 ) | static_cast< Uint64 >( minor );
    m_buildRevision = ( static_cast< Uint64 >( build ) << 32 ) | static_cast< Uint64 >( revision );
}


Version Version::FromString( const std::string& versionString )
{
    Version ver;
    if ( ! ver.TryParse( versionString ))
    {
        CARAMEL_THROW( "\"%s\" is not a version string", versionString );
    }
    return ver;
}


//
// Properties
//

Uint32 Version::Major() const
{
    return static_cast< Uint32 >( m_majorMinor >> 32 );
}


Uint32 Version::Minor() const
{
    return static_cast< Uint32 >( m_majorMinor & 0xFFFFFFFFULL );
}


Uint32 Version::Build() const
{
    return static_cast< Uint32 >( m_buildRevision >> 32 );
}


Uint32 Version::Revision() const
{
    return static_cast< Uint32 >( m_buildRevision & 0xFFFFFFFFULL );
}


//
// Operators
//

Bool Version::operator==( const Version& rhs ) const
{
    return m_majorMinor == rhs.m_majorMinor && m_buildRevision == rhs.m_buildRevision;
}


Bool Version::operator<( const Version& rhs ) const
{
    if ( m_majorMinor == rhs.m_majorMinor )
    {
        return m_buildRevision < rhs.m_buildRevision;
    }
    else
        return m_majorMinor < rhs.m_majorMinor;
}


//
// Conversion
//

std::string Version::ToString() const
{
    return Format( "{0}.{1}.{2}.{3}",
                   this->Major(), this->Minor(), this->Build(), this->Revision() );
}


std::string Version::ToString( Uint numComponents ) const
{
    switch ( numComponents )
    {
    case 1: return Format( "{0}", this->Major() );
    case 2: return Format( "{0}.{1}", this->Major(), this->Minor() );
    case 3: return Format( "{0}.{1}.{2}", this->Major(), this->Minor(), this->Build() );
    case 4: return this->ToString();

    default:
        CARAMEL_THROW( "Invalid number of components: %u", numComponents );
    }
}


//
// Parsing
//

Bool Version::TryParse( const std::string& input )
{
    if ( input.empty() ) { return false; }

    typedef boost::tokenizer< boost::char_separator< Char >> Tokens;

    const boost::char_separator< Char > sep( "." );
    const Tokens tokzer( input, sep );
    const std::vector< std::string > tokens( tokzer.begin(), tokzer.end() );

    if ( tokens.empty() )
    {
        CARAMEL_TRACE_DEBUG( "No components found: \"%s\"", input );
        return false;
    }

    if ( tokens.size() > 4 )
    {
        CARAMEL_TRACE_DEBUG( "Too many components found: \"%s\"", input );
        return false;
    }

    Uint32 comps[4] = { 0 };

    for ( Uint i = 0; i < tokens.size(); ++ i )
    {
        Integer< Uint32 > value;
        if ( ! value.TryParse( tokens[i] ))
        {
            CARAMEL_TRACE_DEBUG( "Invalid version string: \"%s\"", input );
            return false;
        }

        comps[i] = value;
    }

    m_majorMinor    = ( static_cast< Uint64 >( comps[0] ) << 32 ) | static_cast< Uint64 >( comps[1] );
    m_buildRevision = ( static_cast< Uint64 >( comps[2] ) << 32 ) | static_cast< Uint64 >( comps[3] );

    return true;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Lexical

} // namespace Caramel