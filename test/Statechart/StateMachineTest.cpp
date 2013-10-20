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

TEST( StateMachineTest )
{
    Statechart::StateMachine machine( "Basic" );

    machine.AddState( 1 );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE StateMachineSuite

} // namespace Caramel
