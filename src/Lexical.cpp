// Caramel C++ Library - Lexical Facility - Implementation

#include "CaramelPch.h"

#include <Caramel/Lexical/Boolean.h>
#include <Caramel/Lexical/Floating.h>
#include <Caramel/Lexical/Integer.h>
#include <Caramel/String/Algorithm.h>


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

    // TODO: VC2012 doesn't support C++11 strtof()
    m_value = static_cast< Float >( ::strtod( input.c_str(), &stop ));

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


///////////////////////////////////////////////////////////////////////////////

} // namespace Lexical

} // namespace Caramel