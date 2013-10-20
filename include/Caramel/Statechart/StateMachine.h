// Caramel C++ Library - Statechart Facility - State Machine Header

#ifndef __CARAMEL_STATECHART_STATE_MACHINE_H
#define __CARAMEL_STATECHART_STATE_MACHINE_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Statechart/State.h>


namespace Caramel
{

namespace Statechart
{

///////////////////////////////////////////////////////////////////////////////
//
// State Machine
//

class StateMachineImpl;

class StateMachine
{
public:

    explicit StateMachine( const std::string& name );
    ~StateMachine();

    //
    // Build the state machine.
    // - This function can only be used before calling Initiate().
    //
    State AddState( Int stateId );


private:

    std::unique_ptr< StateMachineImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Statechart

} // namespace Caramel

#endif // __CARAMEL_STATECHART_STATE_MACHINE_H
