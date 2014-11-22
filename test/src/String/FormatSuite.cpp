// Caramel C++ Library Test - String - Format Suite

#include "CaramelTestPch.h"

#include <Caramel/Chrono/SecondClock.h>
#include <Caramel/Chrono/TickClock.h>
#include <Caramel/String/Format.h>
#include <Caramel/Value/Scalar.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( FormatSuite )
{

TEST( FormatTrivialTest )
{
    CHECK( "" == Format( "" ));

    const Char alice1[] = "Alice";
    const Char* alice2 = "Alice";
    const std::string alice3( "Alice" );

    CHECK( "Alice" == Format( "Alice" ));
    CHECK( "Alice" == Format( alice1 ));
    CHECK( "Alice" == Format( alice2 ));
    CHECK( "Alice" == Format( alice3 ));
}


TEST( FormatIntegerTest )
{
    CHECK( "Score 0" == Format( "Score {0}", 0 ));
    CHECK( "Answer -1:42" == Format( "Answer {0}:{1}", -1, 42 ));
    CHECK( "2014/1/1 Happy NY!" == Format( "{0}/{1}/{2} Happy NY!", 2014, 1u, 1u ));
    CHECK( "Version 1.4.16.256" == Format( "Version {3}.{2}.{1}.{0}", 256, 16, 4, 1 ));

    const Int64 bigInt = 123456789012;

    CHECK( "BigInt 123456789012" == Format( "BigInt {0}", bigInt ));
}


TEST( FormatFloatingTest )
{
    CHECK( "Score 0" == Format( "Score {0}", 0.0 ));
    CHECK( "Score 0" == Format( "Score {0}", 0.0f ));

    CHECK( "Answer 51.42" == Format( "Answer {0}", 51.42 ));
    CHECK( "65535 Years" == Format( "{0} Years", 65535.f ));
}


TEST( FormatStringTest )
{
    CHECK( "Miko: Reimu" == Format( "Miko: {0}", "Reimu" ));
    CHECK( "Ah Ha Ha Ha!" == Format( "{1} {0} {0} {0}!", "Ha", "Ah" ));

    auto text0 = "Perfect";
    const Char text1[] = "Cherry";
    const Char* text2 = "Blossom";

    CHECK( "Perfect Cherry Blossom" == Format( "{0} {1} {2}", text0, text1, text2 ));
}


TEST( FormatFailureTest )
{
    CHECK( "Score 0" == Format( "Score 0", 42 ));
    CHECK( "Score {0" == Format( "Score {0", 42 ));
    CHECK( "Score 0}" == Format( "Score 0}", 42 ));
    CHECK( "Score {}" == Format( "Score {}", 42 ));
}


TEST( FormatStringConvertibleTest )
{
    // Scalar is StringConvertible

    Scalar s0( 77 );
    Scalar s1( "Alice" );
    
    CHECK( "Alice has 77 dolls" == Format( "{1} has {0} dolls", s0, s1 ));
}


TEST( FormatNumberConvertibleTest )
{
    // Ticks and Seconds are NumberConvertible

    Ticks ticks( 512 );
    Seconds secs( 3.14 );

    CHECK( "512 3.14" == Format( "{0} {1}", ticks, secs ));
}


} // SUITE FormatSuite

} // namespace Caramel
