// Caramel C++ Library Test - Async - Flow State Test

#include "CaramelTestPch.h"

#include <Caramel/Async/FlowState.h>
#include <UnitTest++/UnitTest++.h>


///////////////////////////////////////////////////////////////////////////////
//
// Flow State Test
//

SUITE( FlowStateSuite )
{

TEST( FlowStateTest )
{
    FlowState< Int > state( 0 );

    CHECK( 0 == state.Current() );

    state = 1;

    CHECK( 0 == state.Current() );

    state.Update();

    CHECK( 1 == state.Current() );
    CHECK( true == state.IsEntering() );

    state.Update();

    CHECK( false == state.IsEntering() );
}

}  // FlowStateSuite

///////////////////////////////////////////////////////////////////////////////
