// Caramel C++ Library Test - Android - Input Asset Stream Suite

#include "CaramelTestPch.h"

#include "Utils/AndroidUtils.h"
#include <Caramel/Android/InputAssetStream.h>


namespace Caramel
{

namespace Android
{

SUITE( InputAssetStream )
{

TEST( InputAssetStream )
{
    InputAssetStream s1( GetAssetManager(), "size5.txt" );

    CHECK( 5 == s1.Length() );
    CHECK( 0 == s1.Tell() );
    CHECK( false == s1.IsEof() );

    Char buffer[6] = { 0 };

    CHECK( 5 == s1.Read( buffer, 5 ));
    CHECK( "12345" == std::string( buffer ));
    
    CHECK( 5 == s1.Tell() );
    CHECK( false == s1.IsEof() );

    // Read over the end
    CHECK( 0 == s1.Read( buffer, 1 ));

    CHECK( 5 == s1.Tell() );
    CHECK( true == s1.IsEof() );
}


} // SUITE InputAssetStream

} // namespace Android

} // namespace Caramel
