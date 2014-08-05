// Caramel C++ Library Test - Arithmetic - Power of Two Suite

#include "CaramelTestPch.h"

#include <Caramel/Arithmetic/PowerOfTwo.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( PowerOfTwoSuite )
{

TEST( IsPowerOfTwoTest )
{
    /// Compile-time Expression ///

    CHECK( false == IsPowerOfTwoN< 0 >::VALUE );

    CHECK( true  == IsPowerOfTwoN< 1 >::VALUE );
    CHECK( true  == IsPowerOfTwoN< 2 >::VALUE );
    CHECK( true  == IsPowerOfTwoN< 256 >::VALUE );
    CHECK( true  == IsPowerOfTwoN< 0x80000000 >::VALUE );

    CHECK( false == IsPowerOfTwoN< 3 >::VALUE );
    CHECK( false == IsPowerOfTwoN< 42 >::VALUE );
    CHECK( false == IsPowerOfTwoN< 0x7FFFFFFF >::VALUE );
    CHECK( false == IsPowerOfTwoN< (Uint)-1 >::VALUE );


    /// Runtime Function ///

    CHECK( false == IsPowerOfTwo( 0 ));
    
    CHECK( true  == IsPowerOfTwo( 1 ));
    CHECK( true  == IsPowerOfTwo( 2 ));
    CHECK( true  == IsPowerOfTwo( 256 ));
    CHECK( true  == IsPowerOfTwo( 0x80000000 ));

    CHECK( false == IsPowerOfTwo( 3 ));
    CHECK( false == IsPowerOfTwo( 42 ));
    CHECK( false == IsPowerOfTwo( 0x7FFFFFFF ));
    CHECK( false == IsPowerOfTwo( -1 ));
}


} // SUITE PowerOfTwoSuite

} // namespace Caramel
