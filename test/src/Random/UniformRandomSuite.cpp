// Caramel C++ Library Test - Random - Uniform Random Suite

#include "CaramelTestPch.h"

#include <Caramel/Chrono/SecondClock.h>
#include <Caramel/Random/UniformRandom.h>
#include <cfloat>


namespace Caramel
{

SUITE( UniformRandomSuite )
{

TEST( UniformRandomTest )
{
    /// Int ///
    {
        const Int vMin = -32768;
        const Int vMax = 32767;

        Bool metMin = false;
        Bool metMax = false;

        SecondWatch watch;
        Uint count = 0;

        for ( ;; )
        {
            const Int value = GenRandomInt( vMin, vMax );
            ++ count;

            if ( vMin == value ) { metMin = true; }
            if ( vMax == value ) { metMax = true; }

            if ( metMin && metMax ) { break; }
        }

        TraceDebug( "Test GenRandomInt() count: {0}, elapsed: {1}", count, watch.Elapsed() );
    }

    /// Uint ///
    {
        const Uint vMin = 0;
        const Uint vMax = 65536;

        Bool metMin = false;
        Bool metMax = false;

        SecondWatch watch;
        Uint count = 0;

        for ( ;; )
        {
            const Uint value = GenRandomUint( vMin, vMax );
            ++ count;

            if ( vMin == value ) { metMin = true; }
            if ( vMax == value ) { metMax = true; }

            if ( metMin && metMax ) { break; }
        }

        TraceDebug( "Test GenRandomUint() count: {0}, elapsed: {1}", count, watch.Elapsed() );
    }

    /// Uint64 - Simplified Test ///
    {
        Bool metSmall = false;
        Bool metBig = false;

        for ( ;; )
        {
            const Uint64 value = GenRandomUint64( 0, UINT64_MAX );

            if ( value < 0x1000000000000000ull ) { metSmall = true; }
            if ( value > 0xF000000000000000ull ) { metBig = true; }

            if ( metSmall && metBig ) { break; }
        }
    }

    /// Usize - Simplified Test ///
    {
        Bool metSmall = false;
        Bool metBig = false;

        for ( ;; )
        {
            const Usize value = GenRandomUsize( 0, SIZE_MAX );

            #if defined( CARAMEL_SYSTEM_IS_64_BIT )
            {
                if ( value < 0x1000000000000000ull ) { metSmall = true; }
                if ( value > 0xF000000000000000ull ) { metBig = true; }
            }
            #else
            {
                if ( value < 0x10000000 ) { metSmall = true; }
                if ( value > 0xF0000000 ) { metBig = true; }
            }
            #endif

            if ( metSmall && metBig ) { break; }
        }
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

        SecondWatch watch;
        Uint count = 0;

        for ( ;; )
        {
            const Float value = GenRandomFloat( vLower, vUpper );
            ++ count;

            if ( vLowerThreshold > value ) { metLower = true; }
            if ( vUpperThreshold < value ) { metUpper = true; }

            if ( metLower && metUpper ) { break; }
        }

        TraceDebug( "Test GenRandomFloat() count: {0}, elapsed: {1}", count, watch.Elapsed() );
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

        SecondWatch watch;
        Uint count = 0;

        for ( ;; )
        {
            const Double value = GenRandomDouble( vLower, vUpper );
            ++ count;

            if ( vLowerThreshold > value ) { metLower = true; }
            if ( vUpperThreshold < value ) { metUpper = true; }

            if ( metLower && metUpper ) { break; }
        }

        TraceDebug( "Test GenRandomDouble() count: {0}, elapsed: {1}", count, watch.Elapsed() );
    }
}


TEST( GenRandomBoolTest )
{
    Int trues = 0;
    const Int total = 1000000;

    SecondWatch watch;

    for ( Int i = 0; i < total; ++ i )
    {
        if ( GenRandomBool( 0.25 ))
        {
            ++ trues;
        }
    }

    const Double ratio = static_cast< Double >( trues ) / total;

    CHECK_CLOSE( 0.25, ratio, 0.05 );

    TraceDebug( "Test GenRandomBool() count: {0}, elapsed: {1}, ratio: {2}", 
                total, watch.Elapsed(), ratio );
}


} // SUITE UniformRandomSuite

} // namespace Caramel
