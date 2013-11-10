// Caramel C++ Library - DateTime Facility - Time Span Private Header

#ifndef __CARAMEL_DATE_TIME_TIME_SPAN_IMPL_H
#define __CARAMEL_DATE_TIME_TIME_SPAN_IMPL_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/DateTime/TimeSpan.h>
#include <boost/date_time/posix_time/posix_time.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Time Span
//

class TimeSpanImpl : public boost::posix_time::time_duration
{
public:

    TimeSpanImpl();
    TimeSpanImpl( boost::posix_time::time_duration&& td );
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_DATE_TIME_TIME_SPAN_IMPL_H
