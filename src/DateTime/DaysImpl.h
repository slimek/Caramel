// Caramel C++ Library - DateTime Facility - Days Private Header

#ifndef __CARAMEL_DATE_TIME_DAYS_IMPL_H
#define __CARAMEL_DATE_TIME_DAYS_IMPL_H
#pragma once

#include <Caramel/Caramel.h>
#include <boost/date_time/gregorian/greg_date.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Days
//

class DaysImpl : public boost::gregorian::days
{
public:

    DaysImpl() {}
    DaysImpl( boost::gregorian::days&& days )
        : boost::gregorian::days( days )
    {}
};

typedef std::shared_ptr< DaysImpl > DaysPtr;


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_DATE_TIME_DAYS_IMPL_H
