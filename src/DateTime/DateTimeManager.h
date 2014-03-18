// Caramel C++ Library - DateTime Facility - DateTime Manager Header

#ifndef __CARAMEL_DATE_TIME_DATE_TIME_MANAGER_H
#define __CARAMEL_DATE_TIME_DATE_TIME_MANAGER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Object/FacilityLongevity.h"
#include <Caramel/Object/Singleton.h>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <mutex>
#include <sstream>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// DateTime Manager
//

class DateTimeManager : public Singleton< DateTimeManager, FACILITY_LONGEVITY_DATE_TIME >
{
public:

    DateTimeManager();


    /// Formatters ///

    std::string FormatDate(
        const boost::gregorian::date& date, const std::string& format );

    std::string FormatDateTime(
        const boost::posix_time::ptime& dateTime, const std::string& format );

    std::string FormatTimeDuration(
        const boost::posix_time::time_duration& duration, const std::string& format );


private:

    mutable std::mutex m_mutex;

    std::stringstream m_dateStream;
    std::stringstream m_timeStream;

    typedef boost::gregorian::date_facet DateFacet;
    DateFacet* m_dateFacet;

    typedef boost::posix_time::time_facet TimeFacet;
    TimeFacet* m_timeFacet;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_DATE_TIME_DATE_TIME_MANAGER_H
