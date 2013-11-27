// Caramel C++ Library - DateTime Facility - Time Of Day Header

#ifndef __CARAMEL_DATE_TIME_TIME_OF_DAY_H
#define __CARAMEL_DATE_TIME_TIME_OF_DAY_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/DateTime/TimeSpan.h>
#include <boost/operators.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Time of Day
// - Represents a time point in a day.
//   Valid range is from 00:00:00 to 23:59:59.
//   Immutable.
//

class TimeDuration;

class TimeOfDay : public boost::totally_ordered< TimeOfDay >
{
    friend class DateTime;

public:

    TimeOfDay();


    /// Creators ///

    static TimeOfDay Now();
    static TimeOfDay FromHMS( Int hour, Int minute, Int second );
    static TimeOfDay FromString( const std::string& s );


    /// Accessors ///

    Int Hour()   const;
    Int Minute() const;
    Int Second() const;


    /// Operators ///

    Bool operator==( const TimeOfDay& rhs ) const;
    Bool operator< ( const TimeOfDay& rhs ) const;


    /// Conversions ///

    std::string ToString() const;


private:

    explicit TimeOfDay( std::shared_ptr< TimeDuration > impl );

    std::shared_ptr< TimeDuration > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_DATE_TIME_TIME_OF_DAY_H
