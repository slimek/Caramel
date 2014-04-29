// Caramel C++ Library - Statechart Facility - State Header

#ifndef __CARAMEL_STATECHART_STATE_H
#define __CARAMEL_STATECHART_STATE_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
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
    State& EnterAction( const Action& action );
    State& ExitAction ( const Action& action );


    //
    // When the event triggered, transit to the target state.
    //
    State& Transition( Int eventId, Int targetStateId, const Action& action = Action() );


    //
    // When the event triggered, call this action.
    // You may transit to other states by conditions.
    //
    State& Reaction( Int eventId, const Action& action );


private:

    explicit State( std::shared_ptr< StateImpl > impl );
    
    std::shared_ptr< StateImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Statechart

} // namespace Caramel

#endif // __CARAMEL_STATECHART_STATE_H
