// Caramel C++ Library Test - Enum - Enum Lookup Test

#include "CaramelTestPch.h"

#include <Caramel/Enum/EnumLookupTable.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( EnumLookupSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Enum Lookup Test
//

enum ImageFormat
{
    IMAGE_UNDEF = 0,
    IMAGE_PNG   = 1,
    IMAGE_JPG   = 2,
    IMAGE_GIF   = 3,
};


TEST( EnumLookupTest )
{
    auto table = EnumLookupTable< ImageFormat >
        ( "png", IMAGE_PNG )
        ( "jgp", IMAGE_JPG )
        ( "gif", IMAGE_GIF );

    ImageFormat temp = IMAGE_UNDEF;

    CHECK( true == table.Find( "PNG", temp ));
    CHECK( IMAGE_PNG == temp );

    CHECK( true == table.Find( "2", temp ));
    CHECK( IMAGE_JPG == temp );

    CHECK( false == table.Find( "BMP", temp ));

    CHECK( true == table.ContainsValue( 3 ));
    CHECK( false == table.ContainsValue( 4 ));

    // Case Insensitive
    CHECK( true == table.ContainsName( "GIF" ));
    CHECK( true == table.ContainsName( "Gif" ));
    CHECK( true == table.ContainsName( "gif" ));

    CHECK( false == table.ContainsName( "bmp" ));
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE EnumLookupSuite

} // namespace Caramel
