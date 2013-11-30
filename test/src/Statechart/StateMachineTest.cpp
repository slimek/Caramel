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

static Bool s_initialEntered = false;
static Bool s_initialExited = false;

enum StateId
{
    S_INITIAL,
    S_WAITING,
};


enum EventId
{
    E_START,
};


TEST( StateMachineTest )
{
    Statechart::StateMachine machine( "Basic" );

    machine.AddState( S_INITIAL )
           .EnterAction( [=] { s_initialEntered = true; } )
           .ExitAction( [=] { s_initialExited = true; } )
           .Transition( E_START, S_WAITING );

    machine.AddState( S_WAITING );

    machine.Initiate( S_INITIAL );
    machine.Process();

    CHECK( true == s_initialEntered );
    CHECK( false == s_initialExited );

    machine.PostEvent( E_START );
    machine.Process();

    CHECK( true == s_initialExited );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE StateMachineSuite

} // namespace Caramel
