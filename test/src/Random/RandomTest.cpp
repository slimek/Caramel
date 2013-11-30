// Caramel C++ Library Test - Random - Random Test

#include "CaramelTestPch.h"

#include <Caramel/Chrono/SecondClock.h>
#include <Caramel/Random/UniformRandom.h>
#include <UnitTest++/UnitTest++.h>
#include <cfloat>


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
    /// Int ///
    {
        const Int vMin = -32768;
        const Int vMax = 32767;

        Bool metMin = false;
        Bool metMax = false;

        SecondClock clock;
        Uint count = 0;

        for ( ;; )
        {
            const Int value = GenRandomInt( vMin, vMax );
            ++ count;

            if ( vMin == value ) { metMin = true; }
            if ( vMax == value ) { metMax = true; }

            if ( metMin && metMax ) { break; }
        }

        CARAMEL_TRACE_DEBUG( "Test GenRandomInt() count: %u, elapsed: %f", count, clock.Elapsed() );
    }

    /// Uint ///
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

        CARAMEL_TRACE_DEBUG( "Test GenRandomUint() count: %u, elapsed: %f", count, clock.Elapsed() );
    }

    /// Float ///
    {
        const Float vLower = 0;
        const Float vUpper = 1;

        const Float gap = FLT_EPSILON * 16;

        const Float vLowerThreshold = vLower + gap;
        const Float vUpperThreshold = vUpper - gap;

        Bool metLower = false;
        Bool metUpper = false;

        SecondClock clock;
        Uint count = 0;

        for ( ;; )
        {
            const Float value = GenRandomFloat( vLower, vUpper );
            ++ count;

            if ( vLowerThreshold > value ) { metLower = true; }
            if ( vUpperThreshold < value ) { metUpper = true; }

            if ( metLower && metUpper ) { break; }
        }

        CARAMEL_TRACE_DEBUG( "Test GenRandomFloat() count: %u, elapsed: %f", count, clock.Elapsed() );
    }
}

///////////////////////////////////////////////////////////////////////////////

} // SUITE RandomSuite

} // namespace Caramel
