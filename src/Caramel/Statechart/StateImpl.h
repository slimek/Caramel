// Caramel C++ Library - Statechart Facility - State Private Header

#ifndef __CARAMEL_STATECHART_STATE_IMPL_H
#define __CARAMEL_STATECHART_STATE_IMPL_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Statechart/State.h>


namespace Caramel
{

namespace Statechart
{

///////////////////////////////////////////////////////////////////////////////
//
// State
//

class StateImpl
{
    friend class State;
    friend class StateMachineImpl;

public:

    explicit StateImpl( Int stateId );


private:

    /// Data Members ///

    Int m_id;

    Action m_enterAction;
    Action m_exitAction;

    TickDuration m_autoTimerDuration;   // Zero means not enabled
    Action m_timerAction;
};

typedef std::shared_ptr< StateImpl > StatePtr;


///////////////////////////////////////////////////////////////////////////////

} // namespace Statechart

} // namespace Caramel

#endif // __CARAMEL_STATECHART_STATE_IMPL_H
