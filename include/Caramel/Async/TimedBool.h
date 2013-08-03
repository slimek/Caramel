// Caramel C++ Library - Async Amenity - Timed Bool Header

#ifndef __CARAMEL_ASYNC_TIMED_BOOL_H
#define __CARAMEL_ASYNC_TIMED_BOOL_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Chrono/SteadyClock.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Timed Bool
// - Becomes true when expired.
//   NOT thread-safe.
//

template< typename ClockType = SteadyClock< Float > >
class TimedBool
{
public:

    typedef typename ClockType::UnitType UnitType;

    TimedBool();
    explicit TimedBool( UnitType duration );


    //
    // Manipulators
    //

    void Start( UnitType duration );

    //
    // Restart
    // - Start this time with previous duration.
    //
    void Restart();

    //
    // Continue
    // - Advance the deadline with the duration until it is later than now.
    //   This produce stable intervals.
    //
    void Continue();

    //
    // Expire Now
    // - Immediate expire this timer.
    //
    void ExpireNow();


    //
    // Boolean Accessors
    //

    operator Bool() const;

    Bool ToBool() const;
    

    //
    // Properties
    //

    UnitType Duration() const { return m_duration; }
    UnitType Deadline() const { return m_deadline; }


private:

    /// Data Members ///

    UnitType m_duration;
    UnitType m_deadline;

};


//
// Implementation
//

template< typename ClockType >
inline TimedBool< ClockType >::TimedBool()
    : m_duration( ClockType::MaxValue() )
    , m_deadline( ClockType::MaxValue() )
{
}


template< typename ClockType >
inline TimedBool< ClockType >::TimedBool( UnitType duration )
    : m_duration( duration )
    , m_deadline( ClockType::Now() + duration )
{
}


//
// Manipulators
//

template< typename ClockType >
inline void TimedBool< ClockType >::Start( UnitType duration )
{
    m_duration = duration;
    m_deadline = ClockType::Now() + duration;
}


template< typename ClockType >
inline void TimedBool< ClockType >::Restart()
{
    m_deadline = ClockType::Now() + m_duration;
}


template< typename ClockType >
inline void TimedBool< ClockType >::Continue()
{
    const UnitType now = ClockType::Now();
    while ( m_deadline < now )
    {
        m_deadline += m_duration;
    }
}


template< typename ClockType >
inline void TimedBool< ClockType >::ExpireNow()
{
    m_deadline = ClockType::Now();
}


template< typename ClockType >
inline TimedBool< ClockType >::operator Bool() const
{
    return ClockType::Now() >= m_deadline;
}


template< typename ClockType >
inline Bool TimedBool< ClockType >::ToBool() const
{
    return ClockType::Now() >= m_deadline;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_TIMED_BOOL_H
