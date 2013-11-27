// Caramel C++ Library - DateTime Facility - Time Duration Header

#ifndef __CARAMEL_DATE_TIME_TIME_DURATION_H
#define __CARAMEL_DATE_TIME_TIME_DURATION_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <boost/date_time/posix_time/posix_time.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Time Duration
//

class TimeDuration : public boost::posix_time::time_duration
{
public:

    TimeDuration() {}
    TimeDuration( boost::posix_time::time_duration&& td )
        : boost::posix_time::time_duration( td )
    {}
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_DATE_TIME_TIME_DURATION_H
