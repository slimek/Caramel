// Caramel C++ Library Test - Statechart - Prompt State Machine Suite

#include "CaramelTestPch.h"

#include <Caramel/Statechart/PromptStateMachine.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( PromptStateMachineSuite )
{

enum StateId
{
    S_INITIAL,
    S_WAITING,
    S_PLAYING,
    S_FINAL,
};

enum EventId
{
    E_START,
    E_NEXT,
    E_FINISH,
};

TEST( PromptStateMachineTest )
{
    PromptStateMachine machine( "PSM-Test1" );

    Bool initFlag = false;
    std::string nextStr;

    machine.AddState( S_INITIAL )
           .EnterAction( [&] { initFlag = true; } )
           .Transition( E_START, S_WAITING );

    machine.AddState( S_WAITING )
           .ExitAction( [&] { nextStr = machine.GetActiveEvent().Value< std::string >(); })
           .Transition( E_NEXT, S_PLAYING );

    machine.AddState( S_PLAYING )
           .Reaction( E_FINISH, [&] { machine.PlanToTransit( S_FINAL ); });

    machine.AddState( S_FINAL );

    machine.Initiate( S_INITIAL );

    CHECK( true == initFlag );


    machine.ProcessEvent( E_START );

    CHECK( S_WAITING == machine.GetCurrentStateId() );


    machine.ProcessEvent( E_NEXT, "Reimu" );

    CHECK( "Reimu" == nextStr );
    CHECK( S_PLAYING == machine.GetCurrentStateId() );


    machine.ProcessEvent( E_FINISH );

    CHECK( S_FINAL == machine.GetCurrentStateId() );
}


} // SUITE PromptStateMachineSuite

} // namespace Caramel
