// Caramel C++ Library Test - Task - When All Suite

#include "CaramelTestPch.h"

#include <Caramel/Task/StdAsync.h>
#include <Caramel/Task/WhenAll.h>
#include <Caramel/Thread/WaitableBool.h>
#include <atomic>
#include <vector>


namespace Caramel
{

SUITE( WhenAll )
{

TEST( WhenAll )
{
    /// 16 Tasks - 100 Repeats ///

    std::vector< Task< void > > tasks;

    WaitableBool done;
    std::atomic< Uint > count( 0 );

    for ( Uint pass = 0; pass < 100; ++ pass )
    {
        done = false;
        count = 0;
        Int countInWhenAll = 0;

        tasks.clear();

        for ( Uint i = 0; i < 16; ++ i )
        {
            auto task = MakeTask( "Task", [&] { ++ count; } );
            tasks.push_back( task );
            StdAsync::Submit( task );
        }

        WhenAll( "When-16-Tasks", tasks,
        [&] ( const Task< void >& t )
        {
            countInWhenAll = count.load();
            done = true;
        });

        done.Wait();

        CHECK( 16 == countInWhenAll );
    }

    /// No Task ///

    tasks.clear();

    CHECK_THROW(
        WhenAll( "When-0-Tasks", tasks, [&] ( const Task< void >& task ) {} ),
        Caramel::Exception
    );


    /// Only 1 Task ///

    auto task1 = MakeTask( "Task1", [&] { ++ count; } );
    tasks.push_back( task1 );
    done = false;

    WhenAll( "When-1-Task", tasks,
    [&] ( const Task< void >& t )
    {
        done = true;
    });

    StdAsync::Submit( task1 );

    done.Wait();

    CHECK( 17 == count.load() );


    /// Task which faulted ///

    for ( Uint i = 0; i < 16; ++ i )
    {
        Task< void > task;
        
        if ( i == 7 )
        {
            task = MakeTask( "Task-Bad", [] { CARAMEL_THROW( "Bad task" ); } );
        }
        else
        {
            task = MakeTask( "Task-Normal", [&] {} );
        }

        tasks.push_back( task );
        StdAsync::Submit( task );
    }

    done = false;
    count = 0;
    Bool faulted = false;

    WhenAll( "When-Fault", tasks,
    [&] ( const Task< void >& t )
    {
        faulted = t.IsFaulted();
        ++ count;
        done = true;
    });

    done.Wait();

    CHECK( 1    == count );
    CHECK( true == faulted );
}


} // SUITE WhenAll

} // namespace Caramel
