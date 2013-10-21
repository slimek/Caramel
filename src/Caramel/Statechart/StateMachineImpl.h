// Caramel C++ Library - Statechart Facility - State Machine Private Header

#ifndef __CARAMEL_STATECHART_STATE_MACHINE_IMPL_H
#define __CARAMEL_STATECHART_STATE_MACHINE_IMPL_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Concurrent/Map.h>
#include <Caramel/Statechart/StateMachine.h>
#include <Caramel/Task/TaskExecutor.h>


namespace Caramel
{

namespace Statechart
{

///////////////////////////////////////////////////////////////////////////////
//
// State Machine
//

class StateImpl;
typedef std::shared_ptr< StateImpl > StatePtr;

class StateMachineImpl
{
    friend class StateMachine;

public:

    explicit StateMachineImpl( const std::string& name );

    void ProcessInitiate( StatePtr initialState );


private:

    /// Data Members ///

    std::string m_name;

    std::unique_ptr< TaskExecutor > m_taskExecutor;

    typedef Concurrent::Map< Int, StatePtr > StateMap;
    StateMap m_states;

    Uint m_actionThreadId;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Statechart

} // namespace Caramel

#endif // __CARAMEL_STATECHART_STATE_MACHINE_IMPL_H
