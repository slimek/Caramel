// Caramel C++ Library - DateTime Facility - Date Header

#ifndef __CARAMEL_DATE_TIME_DATE_H
#define __CARAMEL_DATE_TIME_DATE_H
#pragma once

#include <Caramel/Caramel.h>
#include <boost/operators.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Date
// - Immutable
//

class DateImpl;

class Date : public boost::totally_ordered< Date >
{
public:

    Date();

    
    /// Properties ///

    Bool IsValid() const;  // False if impl is "not a date".


    /// Creators ///

    static Date Today();
    static Date FromYMD( Int year, Int month, Int day );

    // Accepted formats:
    //   YYYY-MM-DD
    //   YYYY/MM/DD
    static Date FromString( const std::string& s );

    // The parameter should be ANSI C pre-defined __DATE__
    static Date FromMacro( const Char* date );
    

    /// Accessors ///

    Int Year()  const;
    Int Month() const;
    Int Day()   const;


    /// Operators ///

    Bool operator==( const Date& rhs ) const;
    Bool operator< ( const Date& rhs ) const;


    /// Conversions ///

    std::string ToString()    const;  // YYYY-MM-DD
    std::string ToIsoString() const;  // YYYYMMDD

    // According to strftime() format.
    std::string Format( const std::string& format ) const;


private:

    explicit Date( std::shared_ptr< DateImpl > impl );

    std::shared_ptr< DateImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_DATE_TIME_DATE_H
