// Caramel C++ Library - Chrono Amenity - Timed Bool Header

#ifndef __CARAMEL_CHRONO_TIMED_BOOL_H
#define __CARAMEL_CHRONO_TIMED_BOOL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Thread/MutexLocks.h>
#include <boost/noncopyable.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Timed Bool
// - Becomes true when expired.
//
//   This class is thread-safe.
//
//   Concept of Clock:
//   - Has typedefs of Duration, TimePoint
//     Has static function Now()
//     Its Duration and TimePoint have static function MaxValue().
//

template< typename Clock >
class TimedBool : public boost::noncopyable
{
public:

    typedef Clock ClockType;
    typedef typename Clock::TimePoint TimePoint;
    typedef typename Clock::Duration  Duration;


    TimedBool();  // default: never expired i.e. is always false.

    explicit TimedBool( const Duration& duration );
    explicit TimedBool( typename Duration::Rep duration );


    /// Manipulators ///

    void Start( const Duration& duration );
    void Start( typename Duration::Rep duration );


    // Start this timer with previous duration.
    void Restart();

    // Advance the deadline with the duration until it is later than now.
    // This produces stable intervals (fixed-rate).
    void Continue();

    // Immediate expire this timer.
    void ExpireNow();

    // Take combo functions
    // - If expires, returns true and restart/continue the next duration.
    Bool TakeAndRestart();
    Bool TakeAndContinue();


    /// Boolean Conversions ///

    operator Bool() const;

    Bool ToBool()    const;
    Bool IsExpired() const;
    

    /// Properties ///

    Duration  GetDuration() const;
    TimePoint GetDeadline() const;


private:

    /// Locked Internal Functions ///

    void Start_Locked( const TimePoint& now, const Duration& duration );
    void Restart_Locked( const TimePoint& now );
    void Continue_Locked( const TimePoint& now );
    Bool IsExpired_Locked( const TimePoint& now ) const;


    /// Data Members ///

    mutable std::mutex m_mutex;

    Duration  m_duration;
    TimePoint m_deadline;
};


//
// Implementation
//

template< typename Clock >
inline TimedBool< Clock >::TimedBool()
    : m_duration( Duration::MaxValue() )
    , m_deadline( TimePoint::MaxValue() )
{
}


template< typename Clock >
inline TimedBool< Clock >::TimedBool( const Duration& duration )
{
    this->Start( duration );
}


template< typename Clock >
inline TimedBool< Clock >::TimedBool( typename Duration::Rep duration )
{
    this->Start( duration );
}


//
// Manipulators
//

template< typename Clock >
inline void TimedBool< Clock >::Start( const Duration& duration )
{
    const auto now = Clock::Now();

    LockGuard lock( m_mutex );
    this->Start_Locked( now, duration );
}


template< typename Clock >
inline void TimedBool< Clock >::Start( typename Duration::Rep duration )
{
    const auto now = Clock::Now();
    const Duration dur( duration );

    LockGuard lock( m_mutex );
    this->Start_Locked( now, dur );
}


template< typename Clock >
inline void TimedBool< Clock >::Restart()
{
    const auto now = Clock::Now();

    LockGuard lock( m_mutex );
    this->Restart_Locked( now );
}


template< typename Clock >
inline void TimedBool< Clock >::Continue()
{
    const auto now = Clock::Now();

    LockGuard lock( m_mutex );
    this->Continue_Locked( now );
}


template< typename Clock >
inline void TimedBool< Clock >::ExpireNow()
{
    const auto now = Clock::Now();

    LockGuard lock( m_mutex );
    m_deadline = now;
}


template< typename Clock >
inline Bool TimedBool< Clock >::TakeAndRestart()
{
    const auto now = Clock::Now();

    LockGuard lock( m_mutex );

    if ( ! this->IsExpired_Locked( now )) { return false; }

    this->Restart_Locked( now );
    return true;
}


template< typename Clock >
inline Bool TimedBool< Clock >::TakeAndContinue()
{
    const auto now = Clock::Now();

    LockGuard lock( m_mutex );

    if ( ! this->IsExpired_Locked( now ) ) { return false; }

    this->Continue_Locked( now );
    return true;
}


//
// Boolean Conversions
// - These three conversions have the same result.


template< typename Clock >
inline TimedBool< Clock >::operator Bool() const
{
    return this->IsExpired();
}


template< typename Clock >
inline Bool TimedBool< Clock >::ToBool() const
{
    return this->IsExpired();
}


template< typename Clock >
inline Bool TimedBool< Clock >::IsExpired() const
{
    const auto now = Clock::Now();

    LockGuard lock( m_mutex );
    return this->IsExpired_Locked( now );
}


//
// Properties
//

template< typename Clock >
inline auto TimedBool< Clock >::GetDuration() const -> Duration
{
    LockGuard lock( m_mutex );
    return m_duration;
}


template< typename Clock >
inline auto TimedBool< Clock >::GetDeadline() const -> TimePoint
{
    LockGuard lock( m_mutex );
    return m_deadline;
}


//
// Locked Internal Functions
//

template< typename Clock >
inline void TimedBool< Clock >::Start_Locked( const TimePoint& now, const Duration& duration )
{
    m_duration = duration;
    this->Restart_Locked( now );
}


template< typename Clock >
inline void TimedBool< Clock >::Restart_Locked( const TimePoint& now )
{
    const auto maxTime = TimePoint::MaxValue();

    if ( maxTime - now < m_duration )
    {
        m_deadline = maxTime;
    }
    else
    {
        m_deadline = now + m_duration;
    }
}


template< typename Clock >
inline void TimedBool< Clock >::Continue_Locked( const TimePoint& now )
{
    const auto maxTime = TimePoint::MaxValue();

    while ( m_deadline < now )
    {
        if ( maxTime - now < m_duration )
        {
            m_deadline = maxTime;
            break;
        }
        else
        {
            m_deadline += m_duration;
        }
    }
}


template< typename Clock >
inline Bool TimedBool< Clock >::IsExpired_Locked( const TimePoint& now ) const
{
    return now >= m_deadline;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CHRONO_TIMED_BOOL_H
