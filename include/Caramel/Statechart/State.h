// Caramel C++ Library - Statechart Facility - State Header

#ifndef __CARAMEL_STATECHART_STATE_H
#define __CARAMEL_STATECHART_STATE_H
#pragma once

#include <Caramel/Caramel.h>
#include <functional>


namespace Caramel
{

namespace Statechart
{

///////////////////////////////////////////////////////////////////////////////
//
// State
//

class StateImpl;
typedef std::function< void() > Action;

class State
{
    friend class StateMachine;

public:

    //
    // Called when entering or exiting this state.
    //
    State& EnterAction( Action action );
    State& ExitAction ( Action action );


    //
    // When the event triggered, transit to the target state.
    //
    State& Transition( Int eventId, Int targetStateId, Action action = Action() );


private:

    explicit State( std::shared_ptr< StateImpl > impl );
    
    std::shared_ptr< StateImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Statechart

} // namespace Caramel

#endif // __CARAMEL_STATECHART_STATE_H
