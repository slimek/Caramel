// Caramel C++ Library - DateTime Facility - Date Time Header

#ifndef __CARAMEL_DATE_TIME_DATE_TIME_H
#define __CARAMEL_DATE_TIME_DATE_TIME_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/DateTime/Detail/DateTimeFwd.h>
#include <Caramel/DateTime/Date.h>
#include <Caramel/DateTime/TimeOfDay.h>
#include <Caramel/DateTime/TimeSpan.h>
#include <boost/operators.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Date Time
//
//   This class supports two string formats:
//
//     Normal   : YYYY-MM-DD hh:mm[:ss]
//     ISO 8601 : YYYY-MM-DDThh:mm[:ss][Z] -> Compatible with Json.NET
//

class DateTimeImpl;

class DateTime : public boost::totally_ordered< DateTime >
               , public boost::additive< DateTime, TimeSpan >
{
public:

    DateTime(); // Default: "not a datetime"

    DateTime( const Caramel::Date& date, const Caramel::TimeOfDay& time );


    //
    // Time from System Clock.
    // - The precision of both functions are in seconds.
    //

    static DateTime Now();     // Local timezone
    static DateTime UtcNow();  // UTC                   


    /// Limit Values ///

    static DateTime MinValue();
    static DateTime MaxValue();

    //
    // Parse a string to get a DateTime.
    // - Accepted formats:
    //     YYYY-MM-DD hh:mm[:ss]
    //     YYYY/MM/DD hh:mm[:ss]
    //     YYYY-MM-DDThh:mm[:ss][.ff][Z] - ISO 8601, Compatible with Json.NET
    //
    //   NOTES: ISO 8601 format with time zone is not supported.
    //          i.e. suffixed with +/-hh:mm
    //
    static DateTime FromString( const std::string& s );


    /// Properties ///

    Bool IsValid() const;  // False if impl is "not a date time".


    /// Accessors ///

    Int Year()  const;
    Int Month() const;
    Int Day()   const;

    Int Hour()        const;
    Int Minute()      const;
    Int Second()      const;
    Int Millisecond() const;

    Caramel::Date      Date()      const;
    Caramel::TimeOfDay TimeOfDay() const;

    
    /// Operators ///

    // Comparisons
    Bool operator==( const DateTime& rhs ) const;
    Bool operator< ( const DateTime& rhs ) const;


    // DateTime = DateTime + TimeSpan
    // DateTime = DateTime - TimeSpan
    DateTime& operator+=( const TimeSpan& rhs );
    DateTime& operator-=( const TimeSpan& rhs );

    // TimeSpan = DateTime - DateTime
    TimeSpan operator-( const DateTime& rhs ) const;


    /// Conversions ///

    std::string ToString() const;     // YYYY-MM-DD hh:mm:ss
    std::string ToIsoString() const;  // YYYY-MM-DDThh:mm:ss

    // Returns ISO 8601 basic format. Less readable.
    std::string ToIsoBasicString() const;  // YYYYMMDDThhmmss

    // According to the ANSI C strftime() format.
    std::string Format( const std::string& format ) const;

    // This function is based on FromString().
    Bool TryParse( const std::string& s );

    
    // Convert from UTC to system local timezone
    static DateTime UtcToLocal( const DateTime& utcTime );


private:

    explicit DateTime( std::shared_ptr< DateTimeImpl > impl );

    std::shared_ptr< DateTimeImpl > m_impl;
};


//
// Stand-alone Operators
//

inline DateTime operator+( const Date& date, const TimeOfDay& time )
{
    return DateTime( date, time );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_DATE_TIME_DATE_TIME_H
