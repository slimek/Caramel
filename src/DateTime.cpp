// Caramel C++ Library - DateTime Facility - Implementation

#include "CaramelPch.h"

#include "DateTime/DateTimeImpl.h"
#include "DateTime/TimeSpanImpl.h"


namespace Caramel
{

//
// Contents
//
//   DateTime
//   TimeSpan
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
// Operators
//

DateTime DateTime::operator+( const TimeSpan& rhs ) const
{
    return DateTime( std::make_shared< DateTimeImpl >( *m_impl + *rhs.m_impl ));
}


TimeSpan DateTime::operator-( const DateTime& rhs ) const
{
    return TimeSpan( std::make_shared< TimeSpanImpl >( *m_impl - *rhs.m_impl ));
}


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
    return boost::posix_time::to_iso_extended_string( *m_impl );
}


Bool DateTime::TryParse( const std::string& input )
{
    try
    {
        *this = DateTime::FromString( input );
        return true;
    }
    catch ( const boost::bad_lexical_cast& )
    {
        return false;
    }
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
// Time Span
//

TimeSpan::TimeSpan()
    : m_impl( new TimeSpanImpl )
{
}


TimeSpan::TimeSpan( std::shared_ptr< TimeSpanImpl > impl )
    : m_impl( impl )
{
}


//
// Creators
//

TimeSpan TimeSpan::FromString( const std::string& s )
{
    return TimeSpan( std::make_shared< TimeSpanImpl >( boost::posix_time::duration_from_string( s )));
}


//
// Accessors
//

Seconds TimeSpan::TotalSeconds() const
{
    return Seconds( m_impl->total_seconds() );
}


//
// Operators
//

Bool TimeSpan::operator==( const TimeSpan& rhs ) const
{
    return *m_impl == *rhs.m_impl;
}


//
// Conversions
//

std::string TimeSpan::ToString() const
{
    return boost::posix_time::to_simple_string( *m_impl );
}


//
// Implementation
//

TimeSpanImpl::TimeSpanImpl()
{
}


TimeSpanImpl::TimeSpanImpl( boost::posix_time::time_duration&& td )
    : boost::posix_time::time_duration( td )
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
