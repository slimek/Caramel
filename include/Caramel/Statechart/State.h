// Caramel C++ Library - Statechart Facility - State Header

#ifndef __CARAMEL_STATECHART_STATE_H
#define __CARAMEL_STATECHART_STATE_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

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
    // Enter / Exit Actions
    // - Called when entering or exiting this state.
    //
    State& EnterAction( Action action );
    State& ExitAction ( Action action );


private:

    explicit State( std::shared_ptr< StateImpl > impl );
    
    std::shared_ptr< StateImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Statechart

} // namespace Caramel

#endif // __CARAMEL_STATECHART_STATE_H
