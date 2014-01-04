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
        ( IMAGE_PNG, "png" )
        ( IMAGE_JPG, "jpg" )
        ( IMAGE_GIF, "gif" );

    ImageFormat temp = IMAGE_UNDEF;

    
    /// Find Enum by Text ///

    CHECK( true == table.FindEnumByText( "PNG", temp ));
    CHECK( IMAGE_PNG == temp );

    CHECK( true == table.FindEnumByText( "2", temp ));
    CHECK( IMAGE_JPG == temp );

    CHECK( false == table.FindEnumByText( "BMP", temp ));


    /// Find Enum by Name ///

    CHECK( true == table.FindEnumByName( "Jpg", temp ));
    CHECK( IMAGE_JPG == temp );

    CHECK( false == table.FindEnumByName( "3", temp ));
    CHECK( false == table.FindEnumByName( "tga", temp ));


    /// Find Enum by Value ///

    CHECK( true == table.FindEnumByValue( 1, temp ));
    CHECK( IMAGE_PNG == temp );

    CHECK( false == table.FindEnumByValue( 0, temp ));
    CHECK( false == table.FindEnumByValue( 4, temp ));


    /// Find Name ///

    std::string name;
    CHECK( true == table.FindName( IMAGE_PNG, name ));
    CHECK( "png" == name );

    CHECK( true == table.FindName( IMAGE_GIF, name ));
    CHECK( "gif" == name );

    CHECK( false == table.FindName( IMAGE_UNDEF, name ));


    /// Contains - Value ///

    CHECK( true == table.ContainsValue( 3 ));
    CHECK( false == table.ContainsValue( 4 ));

    
    /// Contains - Name ///

    // Case Insensitive
    CHECK( true == table.ContainsName( "GIF" ));
    CHECK( true == table.ContainsName( "Gif" ));
    CHECK( true == table.ContainsName( "gif" ));

    CHECK( false == table.ContainsName( "bmp" ));
    CHECK( false == table.ContainsName( "" ));
}


class EnumLookupHost
{
public:

    EnumLookupHost();

    void Test();

    typedef EnumLookupTable< ImageFormat > FormatTable;
    FormatTable m_formatTable;
};


EnumLookupHost::EnumLookupHost()
    : m_formatTable( EnumLookupChain
        ( IMAGE_PNG, "png" )
        ( IMAGE_JPG, "jpg" )
        ( IMAGE_GIF, "gif" )
    )
{
}


void EnumLookupHost::Test()
{
    std::string name;
    CHECK( true == m_formatTable.FindName( IMAGE_PNG, name ));
    CHECK( "png" == name );

    ImageFormat format;
    CHECK( true == m_formatTable.FindEnumByName( "gif", format ));
    CHECK( IMAGE_GIF == format );
}


TEST( EnumLookupTableInClassTest )
{
    EnumLookupHost host;
    host.Test();
}


static const PlainPair< ImageFormat, const Char* > IMAGE_FORMAT_NAMES[] =
{
    { IMAGE_PNG, "png" },
    { IMAGE_JPG, "jpg" },
    { IMAGE_GIF, "gif" },
};


TEST( EnumLookupTableFromArrayTest )
{
    auto table = EnumLookupTable< ImageFormat >( IMAGE_FORMAT_NAMES );

    std::string name;
    CHECK( true == table.FindName( IMAGE_GIF, name ));
    CHECK( "gif" == name );

    ImageFormat format;
    CHECK( true == table.FindEnumByName( "jpg", format ));
    CHECK( IMAGE_JPG == format );

    CHECK( true == table.FindEnumByValue( 1, format ));
    CHECK( IMAGE_PNG == format );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE EnumLookupSuite

} // namespace Caramel
