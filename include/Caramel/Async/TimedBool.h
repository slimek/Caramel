// Caramel C++ Library - Async Amenity - Timed Bool Header

#ifndef __CARAMEL_ASYNC_TIMED_BOOL_H
#define __CARAMEL_ASYNC_TIMED_BOOL_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Chrono/TickClock.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Timed Bool
// - Becomes true when expired.
//
//   Time precision is a tick, aka milliseconds.
//   Representation unit is Uint64.
//
//   If the duration is negative, it would expired at once.
//
//   NOT thread-safe.
//

class TimedBool
{
public:

    TimedBool();
    explicit TimedBool( const TickDuration& duration );


    //
    // Manipulators
    //

    void Start( const TickDuration& duration );

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

    TickDuration Duration() const { return m_duration; }
    TickPoint    Deadline() const { return m_deadline; }


private:

    /// Data Members ///

    TickDuration m_duration;
    TickPoint    m_deadline;

};


//
// Implementation
//

inline TimedBool::TimedBool()
    : m_duration( TickDuration::MaxValue() )
    , m_deadline( TickPoint::MaxValue() )
{
}


inline TimedBool::TimedBool( const TickDuration& duration )
    : m_duration( duration )
    , m_deadline( TickClock::Now() + duration )
{
}


//
// Manipulators
//

inline void TimedBool::Start( const TickDuration& duration )
{
    m_duration = duration;
    m_deadline = TickClock::Now() + duration;
}


inline void TimedBool::Restart()
{
    m_deadline = TickClock::Now() + m_duration;
}


inline void TimedBool::Continue()
{
    const TickPoint now = TickClock::Now();
    while ( m_deadline < now )
    {
        m_deadline += m_duration;
    }
}


inline void TimedBool::ExpireNow()
{
    m_deadline = TickClock::Now();
}


inline TimedBool::operator Bool() const
{
    return TickClock::Now() >= m_deadline;
}


inline Bool TimedBool::ToBool() const
{
    return TickClock::Now() >= m_deadline;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_TIMED_BOOL_H
