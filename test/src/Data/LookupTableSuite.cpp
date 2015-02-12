// Caramel C++ Library Test - Data - Lookup Table Suite

#include "CaramelTestPch.h"

#include <Caramel/Data/LookupTable.h>


namespace Caramel
{

SUITE( LookupTableSuite )
{

enum ImageFormat
{
    IMAGE_UNDEF = 0,
    IMAGE_PNG   = 1,
    IMAGE_JPG   = 2,
    IMAGE_GIF   = 3,
};


TEST( EnumLookupTableTest )
{
    const auto table = LookupTable< ImageFormat >
        ( IMAGE_PNG, "png" )
        ( IMAGE_JPG, "jpg" )
        ( IMAGE_GIF, "gif" );

    ImageFormat temp = IMAGE_UNDEF;

    
    /// Find Enum by Text ///

    CHECK( true == table.FindValueByText( "PNG", temp ));
    CHECK( IMAGE_PNG == temp );

    CHECK( true == table.FindValueByText( "2", temp ));
    CHECK( IMAGE_JPG == temp );

    CHECK( false == table.FindValueByText( "BMP", temp ));


    /// Find Enum by Name ///

    CHECK( true == table.FindValueByName( "Jpg", temp ));
    CHECK( IMAGE_JPG == temp );

    CHECK( false == table.FindValueByName( "3", temp ));
    CHECK( false == table.FindValueByName( "tga", temp ));


    /// Find Enum by Value ///

    CHECK( true == table.FindValueByInt( 1, temp ));
    CHECK( IMAGE_PNG == temp );

    CHECK( false == table.FindValueByInt( 0, temp ));
    CHECK( false == table.FindValueByInt( 4, temp ));


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

    typedef LookupTable< ImageFormat > FormatTable;
    FormatTable m_formatTable;
};


EnumLookupHost::EnumLookupHost()
    : m_formatTable( MakeLookupTable
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
    CHECK( true == m_formatTable.FindValueByName( "gif", format ));
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
    const auto table = LookupTable< ImageFormat >( IMAGE_FORMAT_NAMES );

    std::string name;
    CHECK( true == table.FindName( IMAGE_GIF, name ));
    CHECK( "gif" == name );

    ImageFormat format;
    CHECK( true == table.FindValueByName( "jpg", format ));
    CHECK( IMAGE_JPG == format );

    CHECK( true == table.FindValueByInt( 1, format ));
    CHECK( IMAGE_PNG == format );
}


///////////////////////////////////////////////////////////////////////////////
//
// Int Lookup Table Test.
// - the ValueType is Int
//

TEST( IntLookupTableTest )
{
    const auto itable = LookupTable< Int >
        ( 1, "one" )
        ( 2, "two" )
        ( 3, "three" );

    Int value = 0;

    CHECK( true == itable.FindValueByName( "One", value ));
    CHECK( 1 == value );

    CHECK( true == itable.FindValueByText( "2", value ));
    CHECK( 2 == value );

    CHECK( true == itable.FindValueByInt( 3, value ));
    CHECK( 3 == value );
}


///////////////////////////////////////////////////////////////////////////////
//
// Lookup Table Alias Test
//

TEST( LookupTableAliasTest )
{
    const auto table = LookupTable< ImageFormat >
        ( IMAGE_PNG, "png", "apng" )
        ( IMAGE_JPG, "jpg", "jpeg", "jpe" )
        ( IMAGE_GIF, "gif" );

    ImageFormat image = IMAGE_UNDEF;
    std::string name;

    
    /// Find Value ///

    CHECK( true == table.FindValueByName( "apng", image ));
    CHECK( IMAGE_PNG == image );

    CHECK( true == table.FindValueByName( "jpeg", image ));
    CHECK( IMAGE_JPG == image );

    CHECK( true == table.FindValueByText( "png", image ));
    CHECK( IMAGE_PNG == image );

    CHECK( true == table.FindValueByText( "jpe", image ));
    CHECK( IMAGE_JPG == image );

    CHECK( false == table.FindValueByText( "bmp", image ));

    
    /// Find Name - Always the first name ///

    CHECK( true == table.FindName( IMAGE_PNG, name ));
    CHECK( "png" == name );

    CHECK( true == table.FindName( IMAGE_JPG, name ));
    CHECK( "jpg" == name );

    
    /// Compare : The first name is always to be found ///

    const auto rtable = LookupTable< ImageFormat >
        ( IMAGE_PNG, "apng", "png" )
        ( IMAGE_JPG, "jpe", "jpg", "jpeg" )
        ( IMAGE_GIF, "gif" );

    CHECK( true == rtable.FindName( IMAGE_PNG, name ));
    CHECK( "apng" == name );

    CHECK( true == rtable.FindName( IMAGE_JPG, name ));
    CHECK( "jpe" == name );


    /// MakeLookupTable() with Aliases - just test compiling ///

    const auto table2 = MakeLookupTable
        ( IMAGE_JPG, "jpg", "jpeg", "jpe" )
        ( IMAGE_PNG, "png", "apng" )
        ( IMAGE_GIF, "gif" );

    CHECK( true == table2.FindName( IMAGE_JPG, name ));
    CHECK( "jpg" == name );
}


} // SUITE LookupTableSuite

} // namespace Caramel
