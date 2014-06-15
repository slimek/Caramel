// Caramel C++ Library - Chrono Amenity - Timed Bool Header

#ifndef __CARAMEL_CHRONO_TIMED_BOOL_H
#define __CARAMEL_CHRONO_TIMED_BOOL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Timed Bool
// - Becomes true when expired.
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

    Duration  GetDuration() const { return m_duration; }
    TimePoint GetDeadline() const { return m_deadline; }


private:

    /// Data Members ///

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
    m_duration = duration;
    this->Restart();
}


template< typename ClockT >
template< typename AnyDuration >
inline void TimedBool< ClockT >::Start( const AnyDuration& duration )
{
    m_duration = Duration( duration );
    this->Restart();
}


template< typename ClockT >
inline void TimedBool< ClockT >::Restart()
{
    const TimePoint now = ClockType::Now();
    if ( TimePoint::MaxValue() - now < m_duration )
    {
        m_deadline = TimePoint::MaxValue();
    }
    else
    {
        m_deadline = now + m_duration;
    }
}


template< typename ClockT >
inline void TimedBool< ClockT >::Continue()
{
    const TimePoint now = ClockType::Now();
    while ( m_deadline < now )
    {
        if ( TimePoint::MaxValue() - now < m_duration )
        {
            m_deadline = TimePoint::MaxValue();
            break;
        }
        else
        {
            m_deadline += m_duration;
        }
    }
}


template< typename ClockT >
inline void TimedBool< ClockT >::ExpireNow()
{
    m_deadline = ClockType::Now();
}


template< typename ClockT >
inline Bool TimedBool< ClockT >::TakeAndRestart()
{
    if ( ! this->ToBool() ) { return false; }

    this->Restart();
    return true;
}


template< typename ClockT >
inline Bool TimedBool< ClockT >::TakeAndContinue()
{
    if ( ! this->ToBool() ) { return false; }

    this->Continue();
    return true;
}


//
// Boolean Conversions
// - These three conversions have the same result.


template< typename ClockT >
inline TimedBool< ClockT >::operator Bool() const
{
    return ClockType::Now() >= m_deadline;
}


template< typename ClockT >
inline Bool TimedBool< ClockT >::ToBool() const
{
    return this->operator Bool();
}


template< typename ClockT >
inline Bool TimedBool< ClockT >::IsExpired() const
{
    return this->operator Bool();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CHRONO_TIMED_BOOL_H
