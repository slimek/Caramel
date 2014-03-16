// Caramel C++ Library - DateTime Facility - Date Time Private Header

#ifndef __CARAMEL_DATE_TIME_DATE_TIME_IMPL_H
#define __CARAMEL_DATE_TIME_DATE_TIME_IMPL_H
#pragma once

#include <Caramel/DateTime/DateTime.h>
#include <boost/date_time/posix_time/posix_time.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Date Time
//

class DateTimeImpl : public boost::posix_time::ptime
{
public:

    DateTimeImpl();
    DateTimeImpl( boost::posix_time::ptime&& pt );
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_DATE_TIME_DATE_TIME_IMPL_H
