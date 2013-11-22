// Caramel C++ Library - DateTime Facility - Time Span Header

#ifndef __CARAMEL_DATE_TIME_TIME_SPAN_H
#define __CARAMEL_DATE_TIME_TIME_SPAN_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Chrono/SecondClock.h>
#include <boost/operators.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Time Span
// - Represents the duration between two DateTime values.
//   Immutable.
//

class TimeSpanImpl;

class TimeSpan : public boost::equality_comparable< TimeSpan >
{
    friend class DateTime;

public:

    TimeSpan();


    /// Creators///

    static TimeSpan FromString( const std::string& s );


    /// Accessors ///


    //
    // Total Durations
    // - Seconds can cooperate with SecondClock.
    //
    Double  TotalHours()   const;
    Seconds TotalSeconds() const;


    /// Operators ///

    Bool operator==( const TimeSpan& rhs ) const;


    /// Conversions ///

    std::string ToString() const;


private:

    explicit TimeSpan( std::shared_ptr< TimeSpanImpl > impl );

    std::shared_ptr< TimeSpanImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_DATE_TIME_TIME_SPAN_H
