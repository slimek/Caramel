// Caramel C++ Library Test - Statechart - State Machine Suite

#include "CaramelTestPch.h"

#include <Caramel/Async/AnyEventDispatcher.h>
#include <Caramel/Statechart/StateMachine.h>
#include <Caramel/Task/TaskPoller.h>
#include <Caramel/Task/WorkerThread.h>
#include <Caramel/Thread/ThisThread.h>
#include <Caramel/Thread/WaitableBool.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( StateMachineSuite )
{

enum StateId
{
    S_INITIAL,
    S_WAITING,
    S_FINAL,
};

enum EventId
{
    E_START,
    E_NEXT,
    E_STRING,
    E_TIMER,
};


TEST( StateMachineTest )
{
    Statechart::StateMachine machine( "Basic" );

    Bool initialEntered = false;
    Bool initialExited  = false;
    Bool waitingEntered = false;

    machine.AddState( S_INITIAL )
           .EnterAction( [&] { initialEntered = true; } )
           .ExitAction( [&] { initialExited = true; } )
           .Transition( E_START, S_WAITING );

    machine.AddState( S_WAITING )
           .EnterAction( [&] { waitingEntered = true; } );

    machine.Initiate( S_INITIAL );

    CHECK( false == initialEntered );
    CHECK( false == initialExited );
    CHECK( false == waitingEntered );

    machine.Process();  // process the initiate task

    CHECK( true  == initialEntered );
    CHECK( false == initialExited );
    CHECK( false == waitingEntered );

    machine.PostEvent( E_START );
    machine.Process();

    CHECK( true  == initialExited );
    CHECK( true  == waitingEntered );
}


TEST( StateMachineStateVariableTest )
{
    Statechart::StateMachine machine( "StateVariable" );

    Bool initialExited = false;
    Bool transited = false;
    Bool waitingEntered = false;

    Statechart::State initial = machine.AddState( S_INITIAL );
    Statechart::State waiting = machine.AddState( S_WAITING );

    initial.ExitAction ( [&] { initialExited = true; } )
           .Transition( E_START, S_WAITING, [&] { transited = true; } );
     
    waiting.EnterAction( [&] { waitingEntered = true; } );

    machine.Initiate( S_INITIAL );
    machine.Process();

    machine.PostEvent( E_START );
    machine.Process();

    CHECK( true == initialExited );
    CHECK( true == transited );
    CHECK( true == waitingEntered );
}


TEST( StateMachineEventTest )
{
    Statechart::StateMachine machine( "Event" );

    std::string buffer;
    Int enterCount = 0;
    Int exitCount = 0;

    machine.AddState( S_WAITING )
           .Transition( E_STRING, S_WAITING, [&]
                {
                    const auto evt = machine.GetActiveEvent();
                    buffer = evt.Value< std::string >();
                })
           .EnterAction( [&] { ++ enterCount; } )
           .ExitAction( [&] { ++ exitCount; } );

    machine.Initiate( S_WAITING );
    machine.Process();

    CHECK( 1 == enterCount );
    CHECK( 0 == exitCount );
    
    machine.PostEvent( E_STRING, "Alice" );
    machine.Process();

    CHECK( "Alice" == buffer );
    CHECK( 2 == enterCount );
    CHECK( 1 == exitCount );
}


TEST( StateMachineBuildFailedTest )
{
    Statechart::StateMachine machine( "BuildFailed" );

    Int count = 0;

    machine.AddState( S_FINAL );

    // Duplicate states
    CHECK_THROW( machine.AddState( S_FINAL ), Caramel::Exception );

    // Duplicate enter actions
    CHECK_THROW(
        machine.AddState( S_FINAL + 1 )
               .EnterAction( [&] { ++ count; } )
               .EnterAction( [&] { -- count; } ),
        Caramel::Exception
    );

    // Duplicate exit actions
    CHECK_THROW(
        machine.AddState( S_FINAL + 2 )
               .ExitAction( [&] { ++ count; } )
               .ExitAction( [&] { -- count; } ),
        Caramel::Exception
    );

    // Duplicate events for transition
    CHECK_THROW(
        machine.AddState( S_FINAL + 3 )
               .Transition( E_STRING, S_FINAL )
               .Transition( E_STRING, S_FINAL + 1 ),
        Caramel::Exception
    );
}


TEST( StateMachineRunFailedTest )
{
    Statechart::StateMachine machine( "RunFailed" );;

    machine.AddState( S_INITIAL )
           .Transition( E_START, S_WAITING );

    // Post events before initiated
    CHECK_THROW( machine.PostEvent( E_START ), Caramel::Exception );

    // Process before initiated
    CHECK_THROW( machine.Process(), Caramel::Exception );

    // Initiate at an unknown state
    CHECK_THROW( machine.Initiate( S_FINAL ), Caramel::Exception );

    // Initiate failed because a target state 'S_WAITING' doesn't exist.
    CHECK_THROW( machine.Initiate( S_INITIAL ), Caramel::Exception );

    machine.AddState( S_WAITING );
    machine.Initiate( S_INITIAL );

    // Initiate twice
    CHECK_THROW( machine.Initiate( S_INITIAL ), Caramel::Exception );
}


TEST( StateMachineAsAnyEventTargetTest )
{
    AnyEventDispatcher disp;
    Statechart::StateMachine machine( "AnyEventTarget" );

    machine.AddState( S_INITIAL )
           .Transition( E_START, S_WAITING );

    machine.AddState( S_WAITING );

    disp.LinkTarget( machine );
    
    machine.Initiate( S_INITIAL );
    machine.Process();

    disp.DispatchEvent( E_START );
    machine.Process();

    CHECK( S_WAITING == machine.GetCurrentStateId() );
}


TEST( StateMachineReactionTest )
{
    Statechart::StateMachine machine( "Reaction" );

    Bool flag = false;

    machine.AddState( S_INITIAL )
        .Reaction( E_START, [&]
        {
            machine.PlanToTransit( S_WAITING );
        });

    machine.AddState( S_WAITING )
        .Reaction( E_START, [&]
        {
            if ( flag )
            {
                machine.PlanToTransit( S_FINAL );
            }
        });

    machine.AddState( S_FINAL );

    machine.Initiate( S_INITIAL );
    machine.Process();

    machine.PostEvent( E_START );
    machine.Process();

    CHECK( S_WAITING == machine.GetCurrentStateId() );

    machine.PostEvent( E_START );
    machine.Process();

    CHECK( S_WAITING == machine.GetCurrentStateId() );

    flag = true;
    machine.PostEvent( E_START );
    machine.Process();

    CHECK( S_FINAL == machine.GetCurrentStateId() );
}


TEST( StateMachineReactionFailedTest )
{
    Statechart::StateMachine machine( "ReactionFailed" );
    
    Statechart::State initial = machine.AddState( S_INITIAL );
    initial.Transition( E_START, S_WAITING );

    // Reaction conflicts with a transition.
    CHECK_THROW( initial.Reaction( E_START, [] {} ), Caramel::Exception );

    Statechart::State waiting = machine.AddState( S_WAITING );

    waiting.Reaction( E_START, [] {} );

    waiting.Transition( E_NEXT, S_FINAL, [&]
    {
        // Call PlanToTransit() out of a reaction (even if it is in an action ).
        CHECK_THROW( machine.PlanToTransit( S_FINAL ), Caramel::Exception );
    });

    // Transition conflicts with a reaction
    CHECK_THROW( waiting.Transition( E_START, S_FINAL ), Caramel::Exception );

    machine.AddState( S_FINAL );

    machine.Initiate( S_INITIAL );
    machine.Process();

    // Call PlanToTransit() out of a reaction.
    CHECK_THROW( machine.PlanToTransit( S_FINAL ), Caramel::Exception );

    machine.PostEvent( E_START );  // Transit to WAITING
    machine.Process();

    machine.PostEvent( E_NEXT );
    machine.Process();
}


TEST( StateMachineExternalTaskPollerTest )
{
    TaskPoller poller;
    Statechart::StateMachine machine( "ExternalTaskPoller", poller );
    Bool flag = false;

    machine.AddState( S_INITIAL )
           .Transition( E_NEXT, S_WAITING );

    machine.AddState( S_WAITING )
           .EnterAction( [&] { flag = true; } );

    machine.Initiate( S_INITIAL );

    machine.PostEvent( E_NEXT );
    poller.PollFor( Ticks( 10 ));

    CHECK( S_WAITING == machine.GetCurrentStateId() );
    CHECK( true == flag );

    CHECK_THROW( machine.Process(), Caramel::Exception );
}


TEST( StateMachineExternalWorkerThreadTest )
{
    WorkerThread worker( "StateMachine" );
    Statechart::StateMachine machine( "ExternalWorkerThread", worker );
    WaitableBool flag;

    machine.AddState( S_INITIAL )
           .Transition( E_NEXT, S_WAITING );

    machine.AddState( S_WAITING )
           .EnterAction( [&] { flag = true; } );

    machine.Initiate( S_INITIAL );

    machine.PostEvent( E_NEXT );

    flag.Wait();

    CHECK( S_WAITING == machine.GetCurrentStateId() );
    CHECK( true == flag );

    CHECK_THROW( machine.Process(), Caramel::Exception );

    worker.Stop();
}


TEST( StateMachinePollerTimerTest )
{
    TaskPoller poller;
    Statechart::StateMachine machine( "Timer", poller ); 
    Bool flag = false;

    machine.AddState( S_INITIAL )
           .EnterAction( [&] { machine.StartTimer( Ticks( 50 ), E_TIMER ); } )
           .Transition( E_TIMER, S_WAITING )
           .Transition( E_NEXT, S_FINAL );

    machine.AddState( S_WAITING )
           .EnterAction( [&] { flag = true; } )
           .Transition( E_NEXT, S_INITIAL );

    machine.AddState( S_FINAL )
           .Transition( E_TIMER, S_WAITING );  // If the timer in S_INITIAL expires here...

    machine.Initiate( S_INITIAL );
    
    poller.PollOne();
    
    CHECK( false == flag );

    ThisThread::SleepFor( Ticks( 60 ));

    poller.PollOne();

    CHECK( true == flag );
    CHECK( S_WAITING == machine.GetCurrentStateId() );


    // Cancel the timer when exit the state

    machine.PostEvent( E_NEXT );
    poller.PollOne();  // transit to S_INITIAL, timer starts.
    
    machine.PostEvent( E_NEXT );
    poller.PollOne();

    CHECK( S_FINAL == machine.GetCurrentStateId() );

    ThisThread::SleepFor( Ticks( 60 ));
    poller.PollOne();

    CHECK( S_FINAL == machine.GetCurrentStateId() );  // Failed if the timer in S_INITIAL not canceled.
}


} // SUITE StateMachineSuite

} // namespace Caramel
