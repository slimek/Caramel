// Caramel C++ Library - Statechart Facility - State Private Header

#ifndef __CARAMEL_STATECHART_STATE_IMPL_H
#define __CARAMEL_STATECHART_STATE_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Statechart/Transition.h"
#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Concurrent/HashMap.h>
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

    explicit StateImpl( Int stateId, const std::string& machineName );

    Int         GetId()   const { return m_id; }
    std::string GetName() const { return m_name; }


private:

    /// Data Members ///

    Int m_id;
    std::string m_name;

    Action m_enterAction;
    Action m_exitAction;

    typedef Concurrent::HashMapWithSnapshot< Int, TransitionPtr > TransitionMap;
    TransitionMap m_transitions;

    typedef Concurrent::HashMap< Int, Action > ActionMap;
    ActionMap m_reactions;
};

typedef std::shared_ptr< StateImpl > StatePtr;


///////////////////////////////////////////////////////////////////////////////

} // namespace Statechart

} // namespace Caramel

#endif // __CARAMEL_STATECHART_STATE_IMPL_H
