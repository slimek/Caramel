// Caramel C++ Library - Async Amenity - Flow State Header

#ifndef __CARAMEL_ASYNC_FLOW_STATE_H
#define __CARAMEL_ASYNC_FLOW_STATE_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Chrono/SteadyClock.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Flow State
// - Build a simple state machine, better than switch-case solution.
//

template< typename StateType, typename ClockType = SteadyClock< Float > >
class FlowState
{
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_FLOW_STATE_H
