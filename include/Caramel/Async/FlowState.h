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
#include <boost/operators.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Flow State
// - Build a simple state machine, better than bare switch-case solution.
//   NOT thread-safe.
//
// USAGE:
//   Usually we call its Update() in a timer or main loop function, with switch-case:
//
//   switch ( m_state.Update() )
//   {
//   case STATE_INITIAL:
//       ...
//       m_state = STATE_RUNNING;
//       break;
//

template< typename StateType, typename ClockType = SteadyClock< Float > >
class FlowState
    : public NumberConvertible< FlowState< StateType, ClockType >
                              , typename NumberTraits< StateType >::NumberType >
    , public boost::totally_ordered< FlowState< StateType, ClockType >
                                   , StateType >
{
public:
    
    explicit FlowState( StateType initialState );


    //
    // Assign the next state
    //
    void operator=( StateType newState );


    //
    // Update
    // - Move m_nextState to m_currentState, and change properties.
    //
    StateType Update();


    //
    // Current State
    // - REMARKS: Don't provide cast to StateType or Int implicityly,
    //            otherwise people may misuse it in switch statement.
    //        

    StateType Current() const { return m_currentState; }

    NumberType ToNumber() const { return static_cast< NumberType >( m_currentState ); }


    //
    // Is Entering
    // - In the last Update() the state is transitted.,
    //   NOTES: Even if the prev and next states are the same,
    //          It still counts as a transit, therefore it entering a "new" state.
    //
    Bool IsEntering() const { return m_entering; }


    //
    // Elapsed
    // - The duration since the last transit.
    //

    typedef typename ClockType::UnitType TimeUnit;

    TimeUnit Elapsed() const { return ClockType::Now() - m_transitTime; }


    //
    // Operators
    // - Three operators are required by boost::totally_ordered< T, U >.
    //

    Bool operator==( StateType state ) const { return m_currentState == state; }
    Bool operator< ( StateType state ) const { return m_currentState < state; }
    Bool operator> ( StateType state ) const { return m_currentState > state; }


private:

    //
    // Data Members
    //

    StateType m_currentState;
    StateType m_nextState;

    TimeUnit m_transitTime;

    Bool m_toTransit;
    Bool m_entering;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename StateType, typename ClockType >
inline FlowState< StateType, ClockType >::FlowState( StateType initialState )
    : m_currentState( initialState )
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


template< typename StateType, typename ClockType >
inline StateType FlowState< StateType, ClockType >::Update()
{
    if ( m_toTransit )
    {
        m_currentState = m_nextState;
        m_transitTime = ClockType::Now();
        m_toTransit = false;
        m_entering = true;
    }
    else
    {
        m_entering = false;
    }

    return m_currentState;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_FLOW_STATE_H
