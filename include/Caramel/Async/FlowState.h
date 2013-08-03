// Caramel C++ Library - Async Amenity - Flow State Header

#ifndef __CARAMEL_ASYNC_FLOW_STATE_H
#define __CARAMEL_ASYNC_FLOW_STATE_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Chrono/SteadyClock.h>
#include <Caramel/Numeric/NumberConvertible.h>
#include <Caramel/Numeric/NumberTraits.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Flow State
// - Build a simple state machine, better than switch-case solution.
//   NOT thread-safe.
//

template< typename StateType, typename ClockType = SteadyClock< Float > >
class FlowState
    : public NumberConvertible< FlowState< StateType, ClockType >
                              , typename NumberTraits< StateType >::NumberType >
{
public:
    
    explicit FlowState( StateType initialState );


    //
    // Assign the next state
    //
    void operator=( StateType newState );


    //
    // Properties
    //

    Bool IsEntering() const { return m_entering; }


    /// Current States ///

    StateType CurrentState() const { return m_currentState; }

    NumberType ToNumber() const { return static_cast< NumberType >( m_currentState ); }


    /// Elapsed Type ///

    typedef typename ClockType::ValueType TimeValueType;


private:

    //
    // Data Members
    //

    StateType m_initialState;

    StateType m_currentState;
    StateType m_nextState;

    TimeValueType m_transitTime;

    Bool m_toTransit;
    Bool m_entering;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename StateType, typename ClockType >
inline FlowState< StateType, ClockType >::FlowState( StateType initialState )
    : m_initialState( initialState )
    , m_currentState( initialState )
    , m_nextState( initialState )
    , m_transitTime( ClockType::Now() )
    , m_toTransit( true )  // have the m_entering to become true in the first Update().
    , m_entering( false )
{
}


template< typename StateType, typename ClockType >
inline void FlowState< StateType, ClockType >::operator=( StateType newState )
{
    m_nextState = newState;
    m_toTransit = true;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_FLOW_STATE_H
