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

    /// Double ///
    {
        const Double vLower = 0;
        const Double vUpper = 1;

        const Double gap = 1e-6;

        const Double vLowerThreshold = vLower + gap;
        const Double vUpperThreshold = vUpper - gap;

        Bool metLower = false;
        Bool metUpper = false;

        SecondClock clock;
        Uint count = 0;

        for ( ;; )
        {
            const Double value = GenRandomDouble( vLower, vUpper );
            ++ count;

            if ( vLowerThreshold > value ) { metLower = true; }
            if ( vUpperThreshold < value ) { metUpper = true; }

            if ( metLower && metUpper ) { break; }
        }

        CARAMEL_TRACE_DEBUG( "Test GenRandomDouble() count: %u, elapsed: %f", count, clock.Elapsed() );
    }
}


TEST( GenRandomBoolTest )
{
    Int trues = 0;
    const Int total = 1000000;

    SecondClock clock;

    for ( Int i = 0; i < total; ++ i )
    {
        if ( GenRandomBool( 0.25 ))
        {
            ++ trues;
        }
    }

    const Double ratio = static_cast< Double >( trues ) / total;

    CHECK_CLOSE( 0.25, ratio, 0.05 );

    CARAMEL_TRACE_DEBUG( "Test GenRandomBool() count: %u, elapsed: %f, ratio: %f", 
                         total, clock.Elapsed(), ratio );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE RandomSuite

} // namespace Caramel
