// Caramel C++ Library - DateTime Facility - Time Span Header

#ifndef __CARAMEL_DATE_TIME_TIME_SPAN_H
#define __CARAMEL_DATE_TIME_TIME_SPAN_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/DateTime/Detail/DateTimeFwd.h>
#include <Caramel/Chrono/SecondClock.h>
#include <boost/operators.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Time Span
// - Represents the duration between two DateTime values.
//

class TimeDuration;

class TimeSpan : public boost::totally_ordered< TimeSpan >
               , public boost::totally_ordered< TimeSpan, Caramel::Seconds >
               , public boost::additive< TimeSpan >
{
    friend class DateTime;
    friend class Hours;
    friend class Seconds;

public:

    TimeSpan();  // Default: 0h 0m 0s

    TimeSpan( Int hours, Int minutes, Int seconds );

    TimeSpan( const Caramel::Seconds& seconds );


    /// Creators///

    static TimeSpan MinValue();
    static TimeSpan MaxValue();

    // Accepted formats:
    //   hh
    //   hh:mm
    //   hh:mm:ss
    static TimeSpan FromString( const std::string& s );


    /// Accessors ///

    //
    // Components
    //
    Int32 Days()    const;
    Int32 Hours()   const;  // 0 - 23
    Int32 Minutes() const;  // 0 - 59
    Int32 Seconds() const;  // 0 - 59


    //
    // Total Durations
    //
    Double TotalDays()    const;
    Double TotalHours()   const;
    Double TotalMinutes() const;
    Double TotalSeconds() const;


    /// Operators ///

    Bool operator==( const TimeSpan& rhs ) const;
    Bool operator< ( const TimeSpan& rhs ) const;

    Bool operator==( const Caramel::Seconds& rhs ) const;
    Bool operator< ( const Caramel::Seconds& rhs ) const;

    TimeSpan& operator+=( const TimeSpan& rhs );
    TimeSpan& operator-=( const TimeSpan& rhs );

    TimeSpan operator-() const;


    /// Conversions ///

    std::string ToString() const;

    // This function is based on FromString().
    Bool TryParse( const std::string& s );

    operator Caramel::Seconds() const;


protected:

    explicit TimeSpan( std::shared_ptr< TimeDuration > impl );

    std::shared_ptr< TimeDuration > m_impl;
};


//
// Helper Classes to Make TimeSpan
//

class Hours : public TimeSpan
{
public:
    explicit Hours( Int32 hours );
};


class Minutes : public TimeSpan
{
public:
    explicit Minutes( Int32 minutes );
};


// NOTES: Seconds( n ) would make a duration of SecondClock,
//        but it can convert to TimeSpan implicitly.


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_DATE_TIME_TIME_SPAN_H
