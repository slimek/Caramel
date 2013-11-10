// Caramel C++ Library - DateTime Facility - Implementation

#include "CaramelPch.h"

#include "DateTime/DateTimeImpl.h"


namespace Caramel
{

//
// Contents
//
//   DateTime
//

///////////////////////////////////////////////////////////////////////////////
//
// Date Time
//

DateTime::DateTime()
    : m_impl( new DateTimeImpl )
{
}


DateTime::DateTime( std::shared_ptr< DateTimeImpl > impl )
    : m_impl( impl )
{
}


//
// Creators
//

DateTime DateTime::Now()
{
    return DateTime( std::make_shared< DateTimeImpl >( boost::posix_time::second_clock::local_time() ));
}


DateTime DateTime::FromString( const std::string& s )
{
    return DateTime( std::make_shared< DateTimeImpl >( boost::posix_time::time_from_string( s )));
}


//
// Accessors
//

Int DateTime::Year()  const { return m_impl->date().year(); }
Int DateTime::Month() const { return m_impl->date().month(); }
Int DateTime::Day()   const { return m_impl->date().day(); }

Int DateTime::Hour()   const { return m_impl->time_of_day().hours(); }
Int DateTime::Minute() const { return m_impl->time_of_day().minutes(); }
Int DateTime::Second() const { return m_impl->time_of_day().seconds(); }


//
// Conversions
//

std::string DateTime::ToString() const
{
    return boost::gregorian::to_iso_extended_string( m_impl->date() )
         + " "
         + boost::posix_time::to_simple_string( m_impl->time_of_day() );
}


std::string DateTime::ToIsoString() const
{
    return boost::posix_time::to_iso_string( *m_impl );
}


//
// Implementation
//

DateTimeImpl::DateTimeImpl()
{
}


DateTimeImpl::DateTimeImpl( boost::posix_time::ptime&& pt )
    : boost::posix_time::ptime( pt )
{
}


///////////////////////////////////////////////////////////////////////////////
//
// Validations
//

static_assert(
    std::is_same< boost::gregorian::greg_year::value_type, Uint16 >::value,
    "Type of greg_year is Uint16" );

static_assert(
    std::is_same< boost::gregorian::greg_month::value_type, Uint16 >::value,
    "Type of greg_month is Uint16" );

static_assert(
    std::is_same< boost::gregorian::greg_day::value_type, Uint16 >::value,
    "Type of greg_day is Uint16" );

static_assert(
    std::is_same< boost::posix_time::time_duration::hour_type, Int32 >::value,
    "Type of hour_type is Int32" );

static_assert(
    std::is_same< boost::posix_time::time_duration::min_type, Int32 >::value,
    "Type of min_type is Int32" );

static_assert(
    std::is_same< boost::posix_time::time_duration::sec_type, Int32 >::value,
    "Type of sec_type is Int32" );

    

///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
