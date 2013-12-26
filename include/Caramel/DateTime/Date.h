// Caramel C++ Library - DateTime Facility - Date Header

#ifndef __CARAMEL_DATE_TIME_DATE_H
#define __CARAMEL_DATE_TIME_DATE_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/DateTime/Detail/DateTimeFwd.h>
#include <Caramel/DateTime/Days.h>
#include <boost/operators.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Date
// - A specific date in Gregorian Calendar.
//   Based on boost::gregorian::date
//

class DateImpl;

class Date : public boost::totally_ordered< Date >
           , public boost::additive< Date, Days >
{
    friend class DateTime;

public:

    Date(); // Default: "not a date"

    Date( Int year, Int month, Int day );

    
    /// Creators ///

    static Date Today();

    // Accepted formats:
    //   YYYY-MM-DD
    //   YYYY/MM/DD
    static Date FromString( const std::string& s );

    // The parameter should be ANSI C pre-defined __DATE__
    static Date FromMacro( const Char* date );
    

    /// Properties ///

    Bool IsValid() const;  // False if impl is "not a date".


    /// Accessors ///

    Int Year()  const;
    Int Month() const;
    Int Day()   const;


    /// Operators ///

    Bool operator==( const Date& rhs ) const;
    Bool operator< ( const Date& rhs ) const;

    // Date = Date + Days
    // Date = Date - Days
    Date& operator+=( const Days& rhs );
    Date& operator-=( const Days& rhs );

    // Days = Date - Date
    Days operator-( const Date& rhs ) const;


    /// Conversions ///

    std::string ToString() const;  // YYYY-MM-DD

    // According to strftime() format.
    std::string Format( const std::string& format ) const;


private:

    explicit Date( std::shared_ptr< DateImpl > impl );

    std::shared_ptr< DateImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_DATE_TIME_DATE_H
