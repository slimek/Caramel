// Caramel C++ Library - DateTime Facility - Date Time Header

#ifndef __CARAMEL_DATE_TIME_DATE_TIME_H
#define __CARAMEL_DATE_TIME_DATE_TIME_H
#pragma once

#include <Caramel/Caramel.h>
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
// - Immutable.
//

class DateTimeImpl;

class DateTime : public boost::totally_ordered< DateTime >
{
public:

    DateTime(); // Default: "not a datetime"

    DateTime( const Caramel::Date& date, const Caramel::TimeOfDay& time );


    /// Creators ///

    static DateTime Now();

    // Accepted formats:
    //   YYYY-MM-DD hh:mm[:ss]
    static DateTime FromString( const std::string& s );


    /// Properties ///

    Bool IsValid() const;  // False if impl is "not a date time".


    /// Accessors ///

    Int Year()  const;
    Int Month() const;
    Int Day()   const;

    Int Hour()   const;
    Int Minute() const;
    Int Second() const;

    Caramel::Date      Date()      const;
    Caramel::TimeOfDay TimeOfDay() const;

    
    /// Operators ///

    // Comparisons
    Bool operator==( const DateTime& rhs ) const;
    Bool operator< ( const DateTime& rhs ) const;


    //
    // DateTime = DateTime + TimeSpan
    // TimeSpan = DateTime - DateTime
    //
    DateTime operator+( const TimeSpan& rhs ) const;
    TimeSpan operator-( const DateTime& rhs ) const;


    /// Conversions ///

    std::string ToString() const;     // YYYY-MM-DD hh:mm:ss
    std::string ToIsoString() const;  // YYYY-MM-DDThh:mm:ss

    // According to strftime() format.
    std::string Format( const std::string& format ) const;

    Bool TryParse( const std::string& s );


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
