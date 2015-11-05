// Caramel C++ Library Test - Chrono - Tick Clock Suite

#include "CaramelTestPch.h"

#include <Caramel/Chrono/TickClock.h>
#include <thread>


namespace Caramel
{

SUITE( TickClock )
{

TEST( TickClock )
{
    const TickPoint now1 = TickClock::Now();
    TickWatch watch;

    std::this_thread::sleep_for( std::chrono::seconds( 1 ));

    const TickPoint now2 = TickClock::Now();
    const Ticks delta = now2 - now1;
    
    CHECK_CLOSE( 1000, delta.ToNumber(), 50 );

    const Ticks elapsed = watch.Elapsed();
    const Ticks slice   = watch.Slice();
    const Ticks reseted = watch.Elapsed();

    CHECK_CLOSE( Ticks( 1000 ), elapsed, Ticks( 50 ));
    CHECK_CLOSE( Ticks( 1000 ), slice,   Ticks( 50 ));
    CHECK_CLOSE( Ticks( 0 ),    reseted, Ticks( 50 ));


    /// Default Values of Ticks ///

    const Ticks dur0;
    CHECK( 0 == dur0.ToInt64() );


    /// Numeric Convertible ///

    const Ticks t42( 42 );
    CHECK( "42" == Format( "{0}", t42 ));
}


TEST( TicksDivide )
{
    /// Operators ///
    {
        const Ticks n1( 853 );
        const Ticks d1( 200 );

        CHECK( 4 == ( n1 / d1 ));
        // NOTES: The representation of Ticks is Int64,
        //        therefore the quotient is also Int64.

        CHECK( Ticks( 426 ) == n1 / 2 );
        CHECK( Ticks( 53 )  == n1 % d1 );

        CHECK( Ticks( 341 ) != n1 / 2.5 );
        CHECK( Ticks( 341 ) == Ticks( n1 / 2.5 ));
        // NOTES: ( n1 / 2.5 ) will return a std::chrono::duration< double >.
        //        It has fraction and can't be equal to Ticks( 341 ).


        const Ticks n2( 9313 );
        const Ticks d2( 67 );

        CHECK( 139           == n2 / d2 );
        CHECK( Ticks::Zero() == n2 % d2 );
    }

    /// Divide By ///
    {
        const Ticks n1( 853 );
        const Ticks d1( 200 );

        const auto r1 = n1.DivideBy( d1 );

        CHECK( 4 == r1.quotient );
        CHECK( Ticks( 53 ) == r1.remainder );


        const Ticks n2( 9313 );
        const Ticks d2( 67 );

        const auto r2 = n2.DivideBy( d2 );

        CHECK( 139 == r2.quotient );
        CHECK( Ticks::Zero() == r2.remainder );
    }
}


TEST( TicksBool )
{
    /// Default Value ///

    TicksBool tbx;  // never expired

    CHECK( false == tbx );
    CHECK( Ticks::MaxValue() == tbx.GetDuration() );
    CHECK( TickPoint::MaxValue()== tbx.GetDeadline() );


    /// Restart and Continue ///

    TicksBool tb1( 50 );
    TicksBool tb2( Ticks( 50 ));

    CHECK( false == tb1 );
    CHECK( false == tb2 );

    tb1.ExpireNow();  // immediately expire

    CHECK( true == tb1 );

    std::this_thread::sleep_for( std::chrono::milliseconds( 90 ));

    CHECK( true == tb2 );

    tb1.Restart();
    tb2.Continue();

    CHECK( false == tb1 );
    CHECK( false == tb2 );

    std::this_thread::sleep_for( std::chrono::milliseconds( 20 ));

    CHECK( false == tb1 );
    CHECK( true  == tb2 );

    std::this_thread::sleep_for( std::chrono::milliseconds( 40 ));

    CHECK( true == tb1 );
    

    // Boolean Conversion ///

    CHECK( true == tb2.ToBool() );
    CHECK( true == tb2.IsExpired() );

    CHECK( false == tbx.ToBool() );
    CHECK( false == tbx.IsExpired() );
}


} // SUITE TickClock

} // namespace Caramel
