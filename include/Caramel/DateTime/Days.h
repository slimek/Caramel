// Caramel C++ Library - DateTime Facility - Days Header

#ifndef __CARAMEL_DATE_TIME_DAYS_H
#define __CARAMEL_DATE_TIME_DAYS_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/DateTime/Detail/DateTimeFwd.h>
#include <boost/operators.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Days
// - A duration type of Days. Represents in integers.
//

class DaysImpl;

class Days : public boost::totally_ordered< Days >
           , public boost::additive< Days >
{
    friend class Date;

public:

    Days();  // Default: 0 days
    
    explicit Days( Int days );


    /// Creators ///

    static Days MaxValue();


    /// Operators ///

    Bool operator==( const Days& rhs ) const;
    Bool operator< ( const Days& rhs ) const;

    Days& operator+=( const Days& rhs );
    Days& operator-=( const Days& rhs );


    /// Conversions ///

    Int ToInt() const;

    operator TimeSpan() const;


private:

    explicit Days( std::shared_ptr< DaysImpl > impl );

    std::shared_ptr< DaysImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_DATE_TIME_DAYS_H
