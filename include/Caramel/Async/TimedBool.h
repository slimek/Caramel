// Caramel C++ Library - Async Amenity - Timed Bool Header

#ifndef __CARAMEL_ASYNC_TIMED_BOOL_H
#define __CARAMEL_ASYNC_TIMED_BOOL_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Timed Bool
// - Becomes true when expired.
//   If the duration is negative, it would expired at once.
//
//   NOT thread-safe.
//
//   Concept of ClockT:
//   - Has typedefs of Duration, TimePoint
//     Has static function Now()
//     Its Duration and TimePoint have static function MaxValue().
//

template< typename ClockT >
class TimedBool
{
public:

    typedef ClockT ClockType;
    typedef typename ClockType::TimePoint TimePoint;
    typedef typename ClockType::Duration  DurationType;


    TimedBool();
    explicit TimedBool( const DurationType& duration );

    template< typename AnyDuration >
    explicit TimedBool( const AnyDuration& duration );


    //
    // Manipulators
    //

    void Start( const DurationType& duration );

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

    DurationType Duration() const { return m_duration; }
    TimePoint    Deadline() const { return m_deadline; }


private:

    /// Data Members ///

    DurationType m_duration;
    TimePoint    m_deadline;

};


//
// Implementation
//

template< typename ClockT >
inline TimedBool< ClockT >::TimedBool()
    : m_duration( DurationType::MaxValue() )
    , m_deadline( TimePoint::MaxValue() )
{
}


template< typename ClockT >
inline TimedBool< ClockT >::TimedBool( const DurationType& duration )
    : m_duration( duration )
    , m_deadline( ClockType::Now() + duration )
{
}


template< typename ClockT >
template< typename AnyDuration >
inline TimedBool< ClockT >::TimedBool( const AnyDuration& duration )
    : m_duration( duration )
    , m_deadline( ClockType::Now() + m_duration )
{
}


//
// Manipulators
//

template< typename ClockT >
inline void TimedBool< ClockT >::Start( const DurationType& duration )
{
    m_duration = duration;
    m_deadline = ClockType::Now() + duration;
}


template< typename ClockT >
inline void TimedBool< ClockT >::Restart()
{
    m_deadline = ClockType::Now() + m_duration;
}


template< typename ClockT >
inline void TimedBool< ClockT >::Continue()
{
    const TimePoint now = ClockType::Now();
    while ( m_deadline < now )
    {
        m_deadline += m_duration;
    }
}


template< typename ClockT >
inline void TimedBool< ClockT >::ExpireNow()
{
    m_deadline = ClockType::Now();
}


template< typename ClockT >
inline TimedBool< ClockT >::operator Bool() const
{
    return ClockType::Now() >= m_deadline;
}


template< typename ClockT >
inline Bool TimedBool< ClockT >::ToBool() const
{
    return ClockType::Now() >= m_deadline;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_TIMED_BOOL_H
