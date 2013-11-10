// Caramel C++ Library - DateTime Facility - Date Time Header

#ifndef __CARAMEL_DATE_TIME_DATE_TIME_H
#define __CARAMEL_DATE_TIME_DATE_TIME_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Date Time
// - Immutable
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


    /// Conversions ///

    std::string ToString() const;
    std::string ToIsoString() const;


private:

    explicit DateTime( std::shared_ptr< DateTimeImpl > impl );

    std::shared_ptr< DateTimeImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_DATE_TIME_DATE_TIME_H
