// Caramel C++ Library - DateTime Facility - Date Private Header

#ifndef __CARAMEL_DATE_TIME_DATE_IMPL_H
#define __CARAMEL_DATE_TIME_DATE_IMPL_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/DateTime/Date.h>
#include <boost/date_time/gregorian/greg_date.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Date
//

class DateImpl : public boost::gregorian::date
{
public:

    DateImpl();
    DateImpl( boost::gregorian::date&& date );
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_DATE_TIME_DATE_IMPL_H
