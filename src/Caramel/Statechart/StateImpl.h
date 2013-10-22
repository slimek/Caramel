// Caramel C++ Library - Statechart Facility - State Private Header

#ifndef __CARAMEL_STATECHART_STATE_IMPL_H
#define __CARAMEL_STATECHART_STATE_IMPL_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Concurrent/Map.h>
#include <Caramel/Statechart/State.h>
#include <Caramel/Statechart/Transition.h>


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

    explicit StateImpl( Int stateId, const std::string& machineName );

    std::string GetName() const { return m_name; }


private:

    /// Data Members ///

    Int m_id;
    std::string m_name;

    Action m_enterAction;
    Action m_exitAction;

    typedef Concurrent::Map< Int, TransitionPtr > TransitionMap;
    TransitionMap m_transitions;

    Ticks m_autoTimerDuration;   // Zero means not enabled
    Action m_timerAction;
};

typedef std::shared_ptr< StateImpl > StatePtr;


///////////////////////////////////////////////////////////////////////////////

} // namespace Statechart

} // namespace Caramel

#endif // __CARAMEL_STATECHART_STATE_IMPL_H
