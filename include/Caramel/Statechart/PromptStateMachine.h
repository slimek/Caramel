// Caramel C++ Library - Statechart Facility - Prompt State Machine Header

#ifndef __CARAMEL_STATECHART_PROMPT_STATE_MACHINE_H
#define __CARAMEL_STATECHART_PROMPT_STATE_MACHINE_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/AnyEvent.h>
#include <Caramel/Statechart/State.h>
#include <boost/noncopyable.hpp>


namespace Caramel
{

namespace Statechart
{

///////////////////////////////////////////////////////////////////////////////
//
// Prompt State Machine
// - Process the event immedidately.
//   That is, the thread posting an event will also process itself.
//
//   Because this is not an asynchronous component,
//   PromptStateMachine doesn't provide AnyEventTarget interface.
//

class StateMachineImpl;

class PromptStateMachine : public boost::noncopyable
{
public:

    explicit PromptStateMachine( const std::string& name );
    ~PromptStateMachine();


    // Build this state machine.
    // - This function can only be used before calling Initiate().
    State AddState( Int stateId );

    
    // Start this state machine, enter the initial state.
    // - This function submit a task. In the task the enter action
    //   of the initial state would be triggered.
    void Initiate( Int stateId );


    // Post the event to the machine and process it immediately.
    void ProcessEvent( Int eventId );
    void ProcessEvent( Int eventId, const Any& value );
    void ProcessEvent( Int eventId, Any&& value );
    void ProcessEvent( const AnyEvent& event );


    // Plan to Transit to another state.
    // - This function should only be called in an in-state reaction.
    //   It doesn't transit immediately, but will start to transit
    //   after the reaction returns.
    void PlanToTransit( Int stateId );


    /// Properties ///

    Int GetCurrentStateId() const;

    // Return the event to cause the current action.
    // - When you are not in an action handler, this returns a "not an event" event.
    AnyEvent GetActiveEvent() const;


private:

    std::unique_ptr< StateMachineImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Statechart

// PromptStateMachine is not a common name,
// for convenient, you may use it without the namespace Statechart.

using Statechart::PromptStateMachine;


} // namespace Caramel

#endif // __CARAMEL_STATECHART_PROMPT_STATE_MACHINE_H
