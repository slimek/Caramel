// Caramel C++ Library Test - String - To-String Suite

#include "CaramelTestPch.h"

#include <Caramel/String/ToString.h>
#include <Caramel/String/Utf8String.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( StringToStringSuite )
{

TEST( StringToStringTest )
{
    CHECK( "false" == ToString( false ));
    CHECK( "true"  == ToString( true ));


    /// Integers ///
    {
        CHECK( "0" == ToString( 0 ));
        CHECK( "1" == ToString( 1 ));
        CHECK( "65535" == ToString( 65535 ));
        CHECK( "-256" == ToString( -256 ));

        CHECK( "0" == ToString( 0u ));
        CHECK( "1" == ToString( 1u ));
        CHECK( "4294967295" == ToString( UINT_MAX ));

        const Int64 i64z = 0;
        const Uint64 u64z = 0;
        const Int64 i64max = INT64_MAX;
        const Uint64 u64max = UINT64_MAX;

        CHECK( "0" == ToString( i64z ));
        CHECK( "0" == ToString( u64z ));
        CHECK( "9223372036854775807"  == ToString( i64max ));
        CHECK( "18446744073709551615" == ToString( u64max ));

        const Int16 i16z = 0;
        const Uint16 u16z = 0;
        const Int16 i16min = INT16_MIN;
        const Int16 i16max = INT16_MAX;
        const Uint16 u16max = UINT16_MAX;

        CHECK( "0" == ToString( i16z ));
        CHECK( "0" == ToString( u16z ));
        CHECK( "-32768" == ToString( i16min ));
        CHECK( "32767" == ToString( i16max ));
        CHECK( "65535" == ToString( u16max ));

        const Long lz = 0;
        const Ulong ulz = 0;
        const Long lmin = LONG_MIN;
        const Long lmax = LONG_MAX;
        const Ulong ulmax = ULONG_MAX;

        CHECK( "0" == ToString( lz ));
        CHECK( "0" == ToString( ulz ));
        CHECK( "-2147483648" == ToString( lmin ));
        CHECK( "2147483647"  == ToString( lmax ));
        CHECK( "4294967295"  == ToString( ulmax ));
    }

    /// Floatings ///
    {
        CHECK( "0"       == ToString( 0.0 ));
        CHECK( "1"       == ToString( 1.0 ));
        CHECK( "1.5"     == ToString( 1.5 ));
        CHECK( "-625.33" == ToString( -625.33 ));

        CHECK( "0"       == ToString( 0.0f ));
        CHECK( "1"       == ToString( 1.0f ));
        CHECK( "1.5"     == ToString( 1.5f ));
        CHECK( "-625.33" == ToString( -625.33f ));
    }

    /// String Convertible ///
    {
        const Utf8String u8s( "Hello world!" );
        CHECK( "Hello world!" == ToString( u8s ));
    }
}


static Bool IsRvalue( const std::string& s ) { return false; }
static Bool IsRvalue( std::string&& s )      { return true; }

TEST( StringToStringTrivialTest )
{
    const std::string alice( "Alice" );
    const Char* reimu = "Reimu";
    const Char marisa[7] = "Marisa";

    CHECK( "Alice"  == ToString( alice ));
    CHECK( "Pache"  == ToString( "Pache" ));
    CHECK( "Reimu"  == ToString( reimu ));
    CHECK( "Marisa" == ToString( marisa ));

    // Rvalue Test
    CHECK( false == IsRvalue( ToString( alice )));
    CHECK( true  == IsRvalue( ToString( std::string( "Alice" ))));
    CHECK( true  == IsRvalue( ToString( "Alice" )));
}


TEST( StringToStringWithFormatTest )
{
    /// Integers ///

    CHECK( "0.00"      == ToString( 0, "F" ));
    CHECK( "123,456.0" == ToString( 123456, "N1" ));
    CHECK( "7b36a5"    == ToString( 8074917, "x" ));
    CHECK( "-258.000"  == ToString( -258, "F3" ));
    CHECK( "0051"      == ToString( 51, "D4" ));

    const Int16  i16max = INT16_MAX;
    const Uint16 u16max = UINT16_MAX;
    const Int32  i32max = INT32_MAX;
    const Uint32 u32max = UINT32_MAX;
    const Long   lz     = 0;
    const Ulong  ulu    = 1;
    const Int64  i64max = INT64_MAX;
    const Uint64 u64v   = 538314;

    CHECK( "32767.0" == ToString( i16max, "f1" ));
    CHECK( "FFFF"    == ToString( u16max, "X" ));    
    CHECK( "2,147,483,647"  == ToString( i32max, "N0" ));
    CHECK( "4294967295.000" == ToString( u32max, "F3" ));
    CHECK( "00000000" == ToString( lz, "x8" ));
    CHECK( "1.00000"  == ToString( ulu, "n5" ));
    CHECK( "7fffffffffffffff" == ToString( i64max, "x" ));
    CHECK( "538,314.000" == ToString( u64v, "N3" ));


    /// Floatings ///

    CHECK( "0.00" == ToString( 0.0f, "F" ));
    CHECK( "234,765,098.45123" == ToString( 234765098.45123, "N5" ));
    CHECK( "-371" == ToString( -371.28f, "f0" ));
}


TEST( StringToStringTTest )
{
    CHECK( "Bool"   == ToStringT< Bool >() );
    CHECK( "Char"   == ToStringT< Char >() );
    CHECK( "Byte"   == ToStringT< Byte >() );
    CHECK( "Int16"  == ToStringT< Int16 >() );
    CHECK( "Uint16" == ToStringT< Uint16 >() );
    CHECK( "Int32"  == ToStringT< Int32 >() );
    CHECK( "Uint32" == ToStringT< Uint32 >() );
    CHECK( "Long"   == ToStringT< Long >() );
    CHECK( "Ulong"  == ToStringT< Ulong >() );
    CHECK( "Int64"  == ToStringT< Int64 >() );
    CHECK( "Uint64" == ToStringT< Uint64 >() );

    CHECK( "Float"  == ToStringT< Float >() );
    CHECK( "Double" == ToStringT< Double >() );
}


} // SUITE StringToStringSuite

} // namespace Caramel
