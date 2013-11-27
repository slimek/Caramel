// Caramel C++ Library - DateTime Facility - Date Time Header

#ifndef __CARAMEL_DATE_TIME_DATE_TIME_H
#define __CARAMEL_DATE_TIME_DATE_TIME_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/DateTime/TimeOfDay.h>
#include <Caramel/DateTime/TimeSpan.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Date Time
// - Immutable.
//

class DateTimeImpl;

class DateTime
{
public:

    DateTime();


    /// Creators ///

    static DateTime Now();
    static DateTime FromString( const std::string& s );


    /// Accessors ///

    Int Year()  const;
    Int Month() const;
    Int Day()   const;

    Int Hour()   const;
    Int Minute() const;
    Int Second() const;

    Caramel::TimeOfDay TimeOfDay() const;

    
    /// Operators ///

    //
    // DateTime = DateTime + TimeSpan
    // TimeSpan = DateTime - DateTime
    //
    DateTime operator+( const TimeSpan& rhs ) const;
    TimeSpan operator-( const DateTime& rhs ) const;


    /// Conversions ///

    std::string ToString() const;
    std::string ToIsoString() const;

    Bool TryParse( const std::string& s );


private:

    explicit DateTime( std::shared_ptr< DateTimeImpl > impl );

    std::shared_ptr< DateTimeImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_DATE_TIME_DATE_TIME_H
