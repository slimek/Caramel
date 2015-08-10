// Caramel C++ Library Test - Algorithm - Linear Resampler Suite

#include "CaramelTestPch.h"

#include "Utils/SharedArrayUtils.h"
#include <Caramel/Algorithm/LinearResampler.h>


namespace Caramel
{

SUITE( LinearResampler )
{

TEST( LinerResamplerShrink )
{
    LinearResampler< Int16 > resampler1( 5.f / 9.f );

    SharedArray< Int16 > samples1{ 10, 20, 30, 40, 50, 60, 70, 80, 90 };

    auto result1 = resampler1.Convert( samples1 );

    CHECK(( result1 == SharedArray< Int16 >{ 14, 32, 50, 67, 85 } ));


    // Splice { 35, 15, 25, 30, 40 } into 2 pieces
    // - result should be { 26, 25 }

    auto result2 = resampler1.Convert( SharedArray< Int16 >{ 35, 15, 25 });
    CHECK( result2[0] == 26 );

    auto result3 = resampler1.Convert( SharedArray< Int16 >{ 30, 40 });
    CHECK( result3[0] == 25 );


    // Even lower ratio

    LinearResampler< Int16 > resampler2( 1.f / 5.5f );

    const Int16 samples2[] = { 30, 40, 50, 60, 70, 80, 85, 90, 95, 100, 110 };

    // with iterator and count
    auto result4 = resampler2.Convert( samples2, 11 );

    CHECK(( result4 == SharedArray< Int16 >{ 52, 94 } ));


    // When ratio is 1

    LinearResampler< Int16 > resampler3( 1 );

    std::vector< Int16 > samples3{ 42, 7, 51, 83 };

    auto result5 = resampler3.Convert( samples3 );

    CHECK(( result5 == SharedArray< Int16 >{ 42, 7, 51, 83 } ));
}


TEST( LinerResamplerExpand )
{
    LinearResampler< Int16 > resampler1( 9.f / 5.f );

    std::vector< Int16 > samples1{ 10, 20, 30, 40, 50 };

    auto result1 = resampler1.Convert( samples1 );

    // NOTES: Because of precision lost, it cannot generate 9 values here.
    CHECK(( result1 == SharedArray< Int16 >{ 10, 12, 20, 24, 30, 36, 40, 48 } ));


    // Splice samples into 2 pieces

    LinearResampler< Int16 > resampler2( 9.f / 5.f );

    auto result2a = resampler2.Convert( SharedArray< Int16 >{ 10, 20 });
    auto result2b = resampler2.Convert( SharedArray< Int16 >{ 30 });

    CHECK(( result2a == SharedArray< Int16 >{ 10, 12, 20 } ));
    CHECK(( result2b == SharedArray< Int16 >{ 24, 30 } ));


    // Even higher ratio

    LinearResampler< Int16 > resampler3( 5.5f / 1.f );

    auto result3 = resampler3.Convert( SharedArray< Int16 >{ 10, 20 });

    CHECK(( result3 == SharedArray< Int16 >{ 10, 10, 10, 10, 10, 15, 20, 20, 20 ,20 } ));
}


} // SUITE LinearResampler

} // namespace Caramel
