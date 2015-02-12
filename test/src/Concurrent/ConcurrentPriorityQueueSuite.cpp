// Caramel C++ Library Test - Concurrent - Priority Queue Suite

#include "CaramelTestPch.h"

#include <Caramel/Concurrent/PriorityQueue.h>


namespace Caramel
{

SUITE( ConcurrentPriorityQueueSuite )
{

TEST( PriorityQueueTest )
{
    // Largest first
    {
        typedef Concurrent::PriorityQueue< Int, std::string > QueueType;
        QueueType queue;

        queue.Push( 1, "one" );
        queue.Push( 3, "three" );
        queue.Push( 2, "two" );

        std::string value;

        CHECK( queue.TryPop( value ));
        CHECK( "three" == value );

        CHECK( queue.TryPop( value ));
        CHECK( "two" == value );

        CHECK( queue.TryPop( value ));
        CHECK( "one" == value );

        CHECK( false == queue.TryPop( value ));
    }

    // Smallest first
    {
        typedef Concurrent::ReversePriorityQueue< Int, std::string > QueueType;
        QueueType queue;

        queue.Push( 1, "one" );
        queue.Push( 3, "three" );
        queue.Push( 2, "two" );

        std::string value;

        CHECK( queue.TryPop( value ));
        CHECK( "one" == value );

        CHECK( queue.TryPop( value ));
        CHECK( "two" == value );

        CHECK( queue.TryPop( value ));
        CHECK( "three" == value );

        CHECK( false == queue.TryPop( value ));
    }

    // Peek top key
    {
        typedef Concurrent::PriorityQueue< Int, std::string > QueueType;
        QueueType queue;

        Int key = 0;
        std::string value;

        CHECK( false == queue.PeekTopKey( key ));

        queue.Push( 1, "one" );

        CHECK( true == queue.PeekTopKey( key ));
        CHECK( 1 == key );

        queue.Push( 2, "two" );

        CHECK( true == queue.PeekTopKey( key ));
        CHECK( 2 == key );

        queue.TryPop( value );

        CHECK( "two" == value );

        CHECK( true == queue.PeekTopKey( key ));
        CHECK( 1 == key );

        queue.TryPop( value );

        CHECK( "one" == value );

        CHECK( false == queue.PeekTopKey( key ));
    }
}


} // SUITE ConcurrentPriorityQueueSuite

} // namespace Caramel
