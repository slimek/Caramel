// Caramel C++ Library - Data Facility - Implementation

#include "CaramelPch.h"

#include <Caramel/Data/Base64.h>
#include <Caramel/String/Algorithm.h>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <sstream>


namespace Caramel
{

//
// Content
//
//   Base64
//

///////////////////////////////////////////////////////////////////////////////
//
// Base64
//

//
// Encoding
//

std::string Base64Encode( const Byte* data, Uint size )
{
    CARAMEL_ASSERT( nullptr != data );

    if ( 0 == size ) { return ""; }

    typedef boost::archive::iterators::base64_from_binary<
        boost::archive::iterators::transform_width< const Byte*, 6, 8 > > Iterator;

    // Copy the data onto a buffer, and pad it with 2 bytes of 0.
    std::vector< Byte > buffer( size + 2, 0 );
    std::copy( data, data + size, buffer.begin() );

    std::ostringstream oss;

    std::copy(
        Iterator( &buffer[0] ), Iterator( &buffer[size] ),
        std::ostream_iterator< Char >( oss )
    );

    switch ( size % 3 )
    {
    case 1: oss << "=="; break;
    case 2: oss << "=";  break;
    }

    return oss.str();
}


std::string Base64Encode( const Void* data, Uint size )
{
    return Base64Encode( static_cast< const Byte* >( data ), size );
}


std::string Base64Encode( const std::string& data )
{
    return Base64Encode( reinterpret_cast< const Byte* >( data.c_str() ), data.length() );
}


//
// Decoding
//

Bool Base64Decode( const std::string& base64, std::string& data )
{
    if ( base64.empty() ) { return true; }

    // Remove the trailing padding
    const std::string input = BeforeFirst( base64, '=' );

    typedef boost::archive::iterators::transform_width<
        boost::archive::iterators::binary_from_base64< std::string::const_iterator >, 8, 6 > Iterator;

    std::ostringstream oss;

    try
    {
        std::copy(
            Iterator( input.begin() ), Iterator( input.end() ),
            std::ostream_iterator< Char >( oss )
        );
    }
    catch ( ... )
    {
        return false;
    }

    data = oss.str();
    return true;
}


Bool Base64Decode( const std::string& base64, SharedArray< Byte >& data )
{
    std::string buffer;
    const Bool result = Base64Decode( base64, buffer );

    data = SharedArray< Byte >( buffer.length() );
    std::copy( buffer.begin(), buffer.end(), data.begin() );

    return true;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
