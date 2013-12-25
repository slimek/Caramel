// Caramel C++ Library - DateTime Facility - Days Header

#ifndef __CARAMEL_DATE_TIME_DAYS_H
#define __CARAMEL_DATE_TIME_DAYS_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/DateTime/DateTimeFwd.h>
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
public:

    Days();  // Default: 0 days
    
    explicit Days( Int days );


    /// Operators ///

    Bool operator==( const Days& rhs ) const;
    Bool operator< ( const Days& rhs ) const;

    Days& operator+=( const Days& rhs );
    Days& operator-=( const Days& rhs );


    /// Conversions ///

    Int ToInt() const;

    operator TimeSpan() const;


private:

    std::shared_ptr< DaysImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_DATE_TIME_DAYS_H
