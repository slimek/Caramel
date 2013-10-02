// Caramel C++ Library Test - Concurrent - Priority Queue Test

#include "CaramelTestPch.h"

#include <Caramel/Concurrent/PriorityQueue.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Priority Queue Test
//

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
        typedef Concurrent::PriorityQueue< Int, std::string, std::greater< Int > > QueueType;
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
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
