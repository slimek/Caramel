// Caramel C++ Library Test - Data - Base64 Suite

#include "CaramelTestPch.h"

#include "Utils/StdVectorUtils.h"
#include <Caramel/Data/Base64.h>


namespace Caramel
{

SUITE( Base64 )
{

TEST( Base64Trivial )
{
    const auto e64 = Base64Encode( "" );
    CHECK( "" == e64 );
    
    std::string d64;
    CHECK( true == Base64Decode( "", d64 ));
    CHECK( "" == d64 );
}


TEST( Base64String )
{
    const auto alice   = Base64Encode( "Alice" );
    const auto marisa  = Base64Encode( "Marisa" );
    const auto patchou = Base64Encode( "Patchou" );

    CHECK( "QWxpY2U="       == alice );
    CHECK( "TWFyaXNh"       == marisa );
    CHECK( "UGF0Y2hvdQ=="   == patchou );

    std::string buffer;

    CHECK( true == Base64Decode( alice, buffer ));
    CHECK( "Alice" == buffer );

    CHECK( true == Base64Decode( marisa, buffer ));
    CHECK( "Marisa" == buffer );

    CHECK( true == Base64Decode( patchou, buffer ));
    CHECK( "Patchou" == buffer );
}


TEST( Base64Binary )
{
    const std::vector< Int > data = MakeRandomVector( 64, 0, 0x7FFFFFFF );

    const auto base64 = Base64Encode( &data[0], data.size() * sizeof( Int ));

    SharedArray< Byte > buffer;

    CHECK( true == Base64Decode( base64, buffer ));

    std::vector< Int > result( data.size() );

    std::copy( buffer.Begin(), buffer.End(), reinterpret_cast< Byte* >( &result[0] ));

    CHECK( result == data );
}


} // SUITE Base64

} // namespace Caramel
