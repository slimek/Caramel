// Caramel C++ Library - Lexical Facility - Implementation

#include "CaramelPch.h"

#include <Caramel/Lexical/Boolean.h>
#include <Caramel/Lexical/Integer.h>
#include <regex>


namespace Caramel
{

namespace Lexical
{

//
// Contents
//
//   Boolean
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

    const std::regex isTrue( "true", std::regex::icase );
    if ( std::regex_match( input, isTrue ))
    {
        m_value = true;
        return true;
    }

    const std::regex isFalse( "false", std::regex::icase );
    if ( std::regex_match( input, isFalse ))
    {
        m_value = false;
        return true;
    }


    // Then, the input can not be parsed to a boolean.
    return false;
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

    const std::regex isHex( "0[xX][[:xdigit:]]+" );
    const Int radix = std::regex_match( input, isHex )
                    ? 16 : 10;

    Char* stop = nullptr;
    m_value = static_cast< Int32 >( ::strtol( input.c_str(), &stop, radix ));
    
    return stop == ( input.data() + input.length() );
}


template<>
Bool Integer< Uint32 >::TryParse( const std::string& input )
{
    if ( input.empty() ) { return false; }

    Char* stop = nullptr;
    m_value = static_cast< Uint32 >( ::strtoul( input.c_str(), &stop, 10 ));
    
    return stop == ( input.data() + input.length() );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Lexical

} // namespace Caramel