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
//   Concept of ClockT:
//   - Has typedefs of Duration, TimePoint
//     Has static function Now()
//     Its Duration and TimePoint have static function MaxValue().
//

template< typename ClockT >
class TimedBool : public boost::noncopyable
{
public:

    typedef ClockT ClockType;
    typedef typename ClockType::TimePoint TimePoint;
    typedef typename ClockType::Duration  Duration;


    TimedBool();
    explicit TimedBool( const Duration& duration );

    template< typename AnyDuration >
    explicit TimedBool( const AnyDuration& duration );


    /// Manipulators ///

    void Start( const Duration& duration );

    template< typename AnyDuration >
    void Start( const AnyDuration& duration );


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

template< typename ClockT >
inline TimedBool< ClockT >::TimedBool()
    : m_duration( Duration::MaxValue() )
    , m_deadline( TimePoint::MaxValue() )
{
}


template< typename ClockT >
inline TimedBool< ClockT >::TimedBool( const Duration& duration )
{
    this->Start( duration );
}


template< typename ClockT >
template< typename AnyDuration >
inline TimedBool< ClockT >::TimedBool( const AnyDuration& duration )
{
    this->Start( duration );
}


//
// Manipulators
//

template< typename ClockT >
inline void TimedBool< ClockT >::Start( const Duration& duration )
{
    const auto now = ClockT::Now();

    LockGuard lock( m_mutex );
    this->Start_Locked( now, duration );
}


template< typename ClockT >
template< typename AnyDuration >
inline void TimedBool< ClockT >::Start( const AnyDuration& anyDuration )
{
    const auto now = ClockT::Now();
    const Duration duration( anyDuration );

    LockGuard lock( m_mutex );
    this->Start_Locked( now, duration );
}


template< typename ClockT >
inline void TimedBool< ClockT >::Restart()
{
    const auto now = ClockT::Now();

    LockGuard lock( m_mutex );
    this->Restart_Locked( now );
}


template< typename ClockT >
inline void TimedBool< ClockT >::Continue()
{
    const auto now = ClockT::Now();

    LockGuard lock( m_mutex );
    this->Continue_Locked( now );
}


template< typename ClockT >
inline void TimedBool< ClockT >::ExpireNow()
{
    const auto now = ClockT::Now();

    LockGuard lock( m_mutex );
    m_deadline = now;
}


template< typename ClockT >
inline Bool TimedBool< ClockT >::TakeAndRestart()
{
    const auto now = ClockT::Now();

    LockGuard lock( m_mutex );

    if ( ! this->IsExpired_Locked( now )) { return false; }

    this->Restart_Locked( now );
    return true;
}


template< typename ClockT >
inline Bool TimedBool< ClockT >::TakeAndContinue()
{
    const auto now = ClockT::Now();

    LockGuard lock( m_mutex );

    if ( ! this->IsExpired_Locked( now ) ) { return false; }

    this->Continue_Locked( now );
    return true;
}


//
// Boolean Conversions
// - These three conversions have the same result.


template< typename ClockT >
inline TimedBool< ClockT >::operator Bool() const
{
    return this->IsExpired();
}


template< typename ClockT >
inline Bool TimedBool< ClockT >::ToBool() const
{
    return this->IsExpired();
}


template< typename ClockT >
inline Bool TimedBool< ClockT >::IsExpired() const
{
    const auto now = ClockT::Now();

    LockGuard lock( m_mutex );
    return this->IsExpired_Locked( now );
}


//
// Properties
//

template< typename ClockT >
inline auto TimedBool< ClockT >::GetDuration() const -> Duration
{
    LockGuard lock( m_mutex );
    return m_duration;
}


template< typename ClockT >
inline auto TimedBool< ClockT >::GetDeadline() const -> TimePoint
{
    LockGuard lock( m_mutex );
    return m_deadline;
}


//
// Locked Internal Functions
//

template< typename ClockT >
inline void TimedBool< ClockT >::Start_Locked( const TimePoint& now, const Duration& duration )
{
    m_duration = duration;
    this->Restart_Locked( now );
}


template< typename ClockT >
inline void TimedBool< ClockT >::Restart_Locked( const TimePoint& now )
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


template< typename ClockT >
inline void TimedBool< ClockT >::Continue_Locked( const TimePoint& now )
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


template< typename ClockT >
inline Bool TimedBool< ClockT >::IsExpired_Locked( const TimePoint& now ) const
{
    return now >= m_deadline;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CHRONO_TIMED_BOOL_H
