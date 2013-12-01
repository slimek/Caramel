// Caramel C++ Library - Async Amenity - Flow State Header

#ifndef __CARAMEL_ASYNC_FLOW_STATE_H
#define __CARAMEL_ASYNC_FLOW_STATE_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Chrono/SecondClock.h>
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

template< typename StateT, typename ClockType = SecondClock >
class FlowState
    : public NumberConvertible< FlowState< StateT, ClockType >
                              , typename NumberTraits< StateT >::NumberType >
    , public boost::totally_ordered< FlowState< StateT, ClockType >
                                   , StateT >
{
public:
    
    typedef StateT StateType;

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

    typedef typename NumberTraits< StateT >::NumberType NumberType;

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

    typedef typename ClockType::Duration Duration;
    Duration Elapsed() const { return ClockType::Now() - m_transitTime; }


    //
    // Operators
    // - Three operators are required for boost::totally_ordered< T, U >.
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

    typedef typename ClockType::TimePoint TimePoint;
    TimePoint m_transitTime;

    Bool m_toTransit;
    Bool m_entering;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename StateT, typename ClockType >
inline FlowState< StateT, ClockType >::FlowState( StateType initialState )
    : m_currentState( initialState )
    , m_nextState( initialState )
    , m_transitTime( ClockType::Now() )
    , m_toTransit( true )  // have the m_entering to become true in the first Update().
    , m_entering( false )
{
}


template< typename StateT, typename ClockType >
inline void FlowState< StateT, ClockType >::operator=( StateType newState )
{
    m_nextState = newState;
    m_toTransit = true;
}


template< typename StateT, typename ClockType >
inline StateT FlowState< StateT, ClockType >::Update()
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
