// Caramel C++ Library Test - Concurrent - Queue Suite

#include "CaramelTestPch.h"

#include <Caramel/Concurrent/BoundedQueue.h>


namespace Caramel
{

namespace Concurrent
{

SUITE( ConcurrentBoundedQueue )
{

TEST( ConcurrentBoundedQueue )
{
    // Queue with capacity 1
    {
        BoundedQueue< Int > bqueue( 1 );

        CHECK( true == bqueue.IsEmpty() );
        CHECK( 0 == bqueue.Size() );

        CHECK( true == bqueue.TryPush( 7 ));
        CHECK( false == bqueue.IsEmpty() );
        CHECK( 1 == bqueue.Size() );

        CHECK( false == bqueue.TryPush( 13 ));
        CHECK( false == bqueue.IsEmpty() );
        CHECK( 1 == bqueue.Size() );

        Int value = 0;
        CHECK( true == bqueue.TryPop( value ));
        CHECK( value == 7 );
        CHECK( true == bqueue.IsEmpty() );
        CHECK( 0 == bqueue.Size() );
        CHECK( false == bqueue.TryPop( value ));
    }

    // Queue with capacity 3
    {
        BoundedQueue< std::string > bqueue( 3 );

        CHECK( true == bqueue.TryPush( "Reimu" ));
        CHECK( true == bqueue.ForcePush( "Marisa" ));
        CHECK( true == bqueue.TryPush( "Sakuya" ));
        CHECK( false == bqueue.TryPush( "Cirno" ));
        CHECK( false == bqueue.ForcePush( "Alice" ));  // Discard "Reimu"

        CHECK( 3 == bqueue.Size() );

        std::string value;
        
        CHECK( true == bqueue.TryPop( value ));
        CHECK( "Marisa" == value );

        CHECK( true == bqueue.TryPop( value ));
        CHECK( "Sakuya" == value );

        CHECK( true == bqueue.TryPop( value ));
        CHECK( "Alice" == value );

        CHECK( false == bqueue.TryPop( value ));


        // L-value references

        const std::string chen   = "Chen";
        const std::string yuyuko = "Yuyuko";
        const std::string youmu  = "Youmu";
        const std::string ran    = "Ran";
        const std::string yukari = "Yukari";

        CHECK( true == bqueue.TryPush( chen ));
        CHECK( true == bqueue.TryPush( yuyuko ));
        CHECK( true == bqueue.ForcePush( youmu ));
        CHECK( false == bqueue.TryPush( ran ));
        CHECK( false == bqueue.ForcePush( yukari ));  // Discards Chen

        CHECK( true == bqueue.TryPop( value ));
        CHECK( yuyuko == value );

        CHECK( true == bqueue.TryPop( value ));
        CHECK( youmu == value );

        CHECK( true == bqueue.TryPop( value ));
        CHECK( yukari == value );

        CHECK( false == bqueue.TryPop( value ));
    }
}

} // SUITE ConcurrentBoundedQueue

} // namespace Concurrent

} // namespace Caramel
