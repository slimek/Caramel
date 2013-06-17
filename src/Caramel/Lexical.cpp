// Caramel C++ Library - Lexical Facility - Implementation

#include <Caramel/CaramelPch.h>

#include <Caramel/Lexical/Integer.h>


namespace Caramel
{

namespace Lexical
{

//
// Contents
//
// 1. Integer
//

///////////////////////////////////////////////////////////////////////////////
//
// Integer
// - Convert string to integers.
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