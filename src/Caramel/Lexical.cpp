// Caramel C++ Library - Lexical Facility - Implementation

#include <Caramel/CaramelPch.h>

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


    // Test if the input is a boolean-like string

    const std::regex isTrue( "(t|true|yes|ok)", std::regex::icase );
    if ( std::regex_match( input, isTrue ))
    {
        m_value = true;
        return true;
    }

    const std::regex isFalse( "(f|false|no)", std::regex::icase );
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

    Char* stop = NULL;
    m_value = ::strtol( input.c_str(), &stop, 10 );
    
    return stop == ( input.data() + input.length() );
}


template<>
Bool Integer< Uint32 >::TryParse( const std::string& input )
{
    if ( input.empty() ) { return false; }

    Char* stop = NULL;
    m_value = ::strtoul( input.c_str(), &stop, 10 );
    
    return stop == ( input.data() + input.length() );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Lexical

} // namespace Caramel