// Caramel C++ Library Test - String - To-String Test

#include "CaramelTestPch.h"

#include <Caramel/String/ToString.h>
#include <Caramel/String/Utf8String.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( StringToStringSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// To-String Test
//

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


///////////////////////////////////////////////////////////////////////////////

} // SUITE StringToStringSuite

} // namespace Caramel
