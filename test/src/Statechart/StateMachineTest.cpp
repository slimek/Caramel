// Caramel C++ Library Test - Statechart - State Machine Test

#include "CaramelTestPch.h"

#include <Caramel/Statechart/StateMachine.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( StateMachineSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// State Machine Test
//

enum StateId
{
    S_INITIAL,
    S_WAITING,
    S_FINAL,
};

enum EventId
{
    E_START,
    E_STRING,
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

    machine.PostEvent( E_START );
    machine.Process();

    CHECK( false == initialEntered );
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
    
    machine.PostEvent( E_STRING, "Alice" );
    machine.Process();

    CHECK( "Alice" == buffer );
    CHECK( 1 == enterCount );
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

    machine.Initiate( S_INITIAL );

    // Initiate twice
    CHECK_THROW( machine.Initiate( S_INITIAL ), Caramel::Exception );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE StateMachineSuite

} // namespace Caramel
