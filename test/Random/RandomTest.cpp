// Caramel C++ Library Test - Random - Random Test

#include "CaramelTestPch.h"

#include <Caramel/Chrono/SecondClock.h>
#include <Caramel/Random/UniformRandom.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( RandomSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Uniform Random Test
//

TEST( UniformRandomTest )
{
    const Uint vMin = 0;
    const Uint vMax = 65536;

    Bool metMin = false;
    Bool metMax = false;

    SecondClock clock;
    Uint count = 0;

    for ( ;; )
    {
        const Uint value = GenRandomUint( vMin, vMax );
        ++ count;

        if ( vMin == value ) { metMin = true; }
        if ( vMax == value ) { metMax = true; }

        if ( metMin && metMax ) { break; }
    }

    CARAMEL_TRACE_INFO( "Test GenRandomUint() count: %u, elapsed: %f", count, clock.Elapsed() );
}

///////////////////////////////////////////////////////////////////////////////

} // SUITE RandomSuite

} // namespace Caramel
