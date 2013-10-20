// Caramel C++ Library - Statechart Facility - Implementation

#include <Caramel/CaramelPch.h>

#include <Caramel/Statechart/StateImpl.h>
#include <Caramel/Statechart/StateMachineImpl.h>
#include <Caramel/Task/TaskPoller.h>


namespace Caramel
{

namespace Statechart
{

//
// Contents
//
//   StateMachine
//   State
//

///////////////////////////////////////////////////////////////////////////////
//
// State Machine
//

StateMachine::StateMachine( const std::string& name )
    : m_impl( new StateMachineImpl( name ))
{
}


StateMachine::~StateMachine()
{
}


//
// Operations
//

State StateMachine::AddState( Int stateId )
{
    StatePtr newState = std::make_shared< StateImpl >( stateId );
    return State( newState );
}


//
// Implementation
//

StateMachineImpl::StateMachineImpl( const std::string& name )
    : m_name( name )
    , m_taskExecutor( new TaskPoller )
{
}


///////////////////////////////////////////////////////////////////////////////
//
// State
//

State::State( StatePtr impl )
    : m_impl( impl )
{
}


//
// Implementation
//

StateImpl::StateImpl( Int stateId )
    : m_id( stateId )
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Statechart

} // namespace Caramel
