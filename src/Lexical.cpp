// Caramel C++ Library - Lexical Facility - Implementation

#include "CaramelPch.h"

#include <Caramel/Lexical/Boolean.h>
#include <Caramel/Lexical/Floating.h>
#include <Caramel/Lexical/Integer.h>
#include <boost/regex.hpp>


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

    const boost::regex isTrue( "true", boost::regex::icase );
    if ( boost::regex_match( input, isTrue ))
    {
        m_value = true;
        return true;
    }

    const boost::regex isFalse( "false", boost::regex::icase );
    if ( boost::regex_match( input, isFalse ))
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

    const boost::regex isHex( "0[xX][[:xdigit:]]+" );
    if ( boost::regex_match( input, isHex ))
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

    const boost::regex isHex( "0[xX][[:xdigit:]]+" );
    if ( boost::regex_match( input, isHex ))
    {
        m_value = static_cast< Uint32 >( ::strtoul( input.c_str(), &stop, 16 ));
    }
    else
    {
        m_value = static_cast< Uint32 >( ::strtoul( input.c_str(), &stop, 10 ));    
    }
    
    return stop == ( input.data() + input.length() );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Lexical

} // namespace Caramel