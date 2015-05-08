// Caramel C++ Library Test - Async - Flow State Suite

#include "CaramelTestPch.h"

#include <Caramel/Async/FlowState.h>


namespace Caramel
{

SUITE( FlowState )
{

TEST( FlowState )
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

} // SUITE FlowState

} // namespace Caramel
