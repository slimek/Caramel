// Caramel C++ Library Test - Concurrent - Vector Suite

#include "CaramelTestPch.h"

#include <Caramel/Concurrent/Vector.h>
#include <Caramel/Random/UniformRandom.h>
#include <Caramel/Thread/LoopThreadGroup.h>
#include <Caramel/Thread/ThisThread.h>


namespace Caramel
{

SUITE( ConcurrentVector )
{

using Concurrent::Vector;

TEST( ConcurrentVectorTrivial )
{
    Vector< Int > vec;

    CHECK( true == vec.IsEmpty() );
    CHECK( 0    == vec.Size() );

    vec.PushBack( 42 );

    CHECK( false == vec.IsEmpty() );
    CHECK( 1     == vec.Size() );

    vec.PushBack( 51 );

    CHECK( 2 == vec.Size() );

    /// Access Elements ///

    Int value = 0;
    CHECK( true == vec.TryGetAt( 0, value ));
    CHECK( 42 == value );

    CHECK( false == vec.TryGetAt( 3, value ));

    const auto rv1 = vec[1];
    CHECK( false == !rv1 );
    CHECK( 51 == rv1.value() );

    const auto rv2 = vec[3];
    CHECK( true == !rv2 );


    vec.Clear();

    CHECK( true == vec.IsEmpty() );
    CHECK( 0    == vec.Size() );
}


TEST( ConcurrentVectorInitialize )
{
    // Initializer list
    Vector< Int > vec1 { 5, 7, 9 };

    CHECK( 3 == vec1.Size() );

    auto snap1 = vec1.GetSnapshot();
    
    CHECK( 3 == snap1.Size() );
    CHECK( 5 == snap1[0] );
    CHECK( 9 == snap1[2] );

    // Copy
    Vector< Int > vec2( vec1 );

    const auto snap2 = vec2.GetSnapshot();

    CHECK( 3 == snap2.Size() );
    CHECK( 5 == snap1[0] );
    CHECK( 7 == snap1[1] );

    // Move
    Vector< Int > vec3( Vector< Int > { 2, 4, 8, 16 } );

    const auto snap3 = vec3.GetSnapshot();

    CHECK( 4 == snap3.Size() );
    CHECK( 2 == snap3[0] );
    CHECK( 8 == snap3[2] );

    // From std::vector, Copy
    std::vector< Int > v4 { 19, 42, 51 };

    Vector< Int > vec4( v4 );

    const auto snap4 = vec4.GetSnapshot();

    CHECK( 3  == snap4.Size() );
    CHECK( 19 == snap4[0] );
    CHECK( 51 == snap4[2] );

    // From std::vector, Move
    Vector< Int > vec5( std::vector< Int > { 135, 246 } );

    const auto snap5 = vec5.GetSnapshot();

    CHECK( 2   == snap5.Size() );
    CHECK( 135 == snap5[0] );
    CHECK( 246 == snap5[1] );
}


TEST( ConcurrentVectorAssignment )
{
    Vector< Int > vec;

    // Initializer list
    vec = { 2, 3, 5, 7, 11 };

    const auto snap1 = vec.GetSnapshot();

    CHECK( 5  == snap1.Size() );
    CHECK( 3  == snap1[1] );
    CHECK( 11 == snap1[4] );


    // Copy
    Vector< Int > vec2 { 1, 11, 111 };
    vec = vec2;

    const auto snap2 = vec.GetSnapshot();

    CHECK( 3  == snap2.Size() );
    CHECK( 1  == snap2[0] );
    CHECK( 11 == snap2[1] );


    // Move
    vec = Vector< Int > { 7, 19, 31, 37 };

    const auto snap3 = vec.GetSnapshot();

    CHECK( 4  == snap3.Size() );
    CHECK( 7  == snap3[0] );
    CHECK( 37 == snap3[3] );


    // From std::vector, Copy
    std::vector< Int > v4 { 42, 51, 77 };
    vec = v4;

    const auto snap4 = vec.GetSnapshot();

    CHECK( 3  == snap4.Size() );
    CHECK( 42 == snap4[0] );
    CHECK( 77 == snap4[2] );


    // From std::vector, Move
    vec = std::vector< Int > { 2, 4, 8, 16 };

    const auto snap5 = vec.GetSnapshot();

    CHECK( 4  == snap5.Size() );
    CHECK( 2  == snap5[0] );
    CHECK( 16 == snap5[3] );
}


struct User
{
    Int id;
    std::string name;
};


TEST( ConcurrentVectorFind )
{
    Vector< User > users = {
        { 2, "Reimu" }, { 7, "Alice" }, { 8, "Marisa" }
    };

    auto pred = [] ( const User& u ) { return u.id == 7; };

    User user;
    CHECK( true == users.Find( user, pred ));
    CHECK( "Alice" == user.name );

    CHECK( false == users.Find( user, [] ( const User& u ) { return u.id == 13; } ));
}


TEST( ConcurrentVectorStress )
{
    Vector< std::string > svec;

    const auto work = [&]
    {
        switch ( GenRandomUint( 1, 6 ))
        {
        case 1:
            svec = Vector< std::string > { "Reisen", "Enrin", "Kaguya" };
            break;

        case 2:
            svec.PushBack( "Tewi" );
            break;

        case 3:
        {
            const auto vec = svec.ToVector();
            break;
        }

        case 4:
        {
            const auto rv = svec[4];
            break;
        }

        case 5:
        {
            const auto snap = svec.GetSnapshot();
            break;
        }

        case 6:
            svec.Clear();
            break;
        }
    };

    LoopThreadGroup threads;
    for ( Usize i = 0; i < 4; ++ i )
    {
        threads.Start( "Stress", Ticks::Zero(), work );
    }

    ThisThread::SleepFor( Ticks( 100 ));
    threads.StopAll();
}


} // SUITE ConcurrentVector

} // namespace Caramel
