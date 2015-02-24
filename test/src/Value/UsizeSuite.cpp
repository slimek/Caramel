// Caramel C++ Library Test - Value - Usize Suite

#include "CaramelTestPch.h"

#include <Caramel/Value/Usize.h>


namespace Caramel
{

SUITE( UsizeSuite )
{

TEST( UsizeTest )
{
    /// Valid Integers ///

    CHECK( 0 == Usize( 0 ));
    CHECK( 0xFFFFFFFF == Usize( 0xFFFFFFFF ));

    {
        const Long  l    = 328;
        const Ulong ul   = 51;
        const Int64 i64  = 96296;
        const Uint64 u64 = 134340;

        CHECK( 328    == Usize( l ));
        CHECK( 51     == Usize( ul ));
        CHECK( 96296  == Usize( i64 ));
        CHECK( 134340 == Usize( u64 ));

        const Int16  s = 42;
        const Uint16 w = 729;

        CHECK( 42  == Usize( s ));
        CHECK( 729 == Usize( w ));
    }


    /// Out of Range ///
    {
        CHECK_THROW( Usize( -1 ), Caramel::Exception );
        CHECK_THROW( Usize( INT64_MAX ), Caramel::Exception );
    }


    /// Boolean and Floating are not allowed ///

    // Usize( 7.25f );
    // Usize( 9.8 );
    // Usize( true );
}


} // SUITE UsizeSuite

} // namespace Caramel
