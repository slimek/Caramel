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

static Bool s_state1Entered = false;

TEST( StateMachineTest )
{
    Statechart::StateMachine machine( "Basic" );

    machine.AddState( 1 )
           .EnterAction( [=] { s_state1Entered = true; } );

    machine.Initiate( 1 );

    //machine.Process();
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE StateMachineSuite

} // namespace Caramel
