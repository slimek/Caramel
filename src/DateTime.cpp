// Caramel C++ Library - DateTime Facility - Implementation

#include "CaramelPch.h"

#include "DateTime/DaysImpl.h"
#include "DateTime/DateImpl.h"
#include "DateTime/DateTimeImpl.h"
#include "DateTime/DateTimeManager.h"
#include "DateTime/TimeDuration.h"
#include <Caramel/DateTime/TimeOfDay.h>
#include <Caramel/DateTime/TimeSpan.h>
#include <Caramel/Memory/SharedPtrUtils.h>
#include <Caramel/Thread/MutexLocks.h>
#include <boost/xpressive/xpressive_dynamic.hpp>


namespace Caramel
{

//
// Contents
//
//   Date
//   Days
//   DateTime
//   TimeSpan
//   TimeOfDay
//   DateTimeManager
//

///////////////////////////////////////////////////////////////////////////////
//
// Date
//

Date::Date()
    : m_impl( new DateImpl )
{
}


Date::Date( Int year, Int month, Int day )
    : m_impl( new DateImpl( boost::gregorian::date( year, month, day )))
{
}


Date::Date( std::shared_ptr< DateImpl > impl )
    : m_impl( impl )
{
}


//
// Creators
//

Date Date::Today()
{
    return Date( std::make_shared< DateImpl >( boost::gregorian::day_clock::local_day() ));   
}


Date Date::FromString( const std::string& s )
{
    return Date( std::make_shared< DateImpl >( boost::gregorian::from_string( s )));
}


Date Date::FromMacro( const Char* inputDate )
{
    CARAMEL_ASSERT( inputDate );

    using namespace boost::xpressive;

    const std::string sdate = inputDate;

    // The ANSI C __DATE__ macro is in "Mmm dd yyyy" format

    smatch matches;
    static const sregex spec = sregex::compile( "(\\w{3})\\s+(\\d{1,2})\\s+(\\d{4})" );

    if ( ! regex_match( sdate, matches, spec ))
    {
        CARAMEL_THROW( "Not match ANSI C __DATE__ format: %s", sdate );
    }

    const std::string smonth = matches[1].str();
    const std::string sday   = matches[2].str();
    const std::string syear  = matches[3].str();

    return FromString( Sprintf( "%s-%s-%s", syear, smonth, sday ));
}


//
// Properties
//

Bool Date::IsValid() const
{
    return ! m_impl->is_not_a_date();
}


//
// Accessors
//

Int Date::Year()  const { return m_impl->year(); }
Int Date::Month() const { return m_impl->month(); }
Int Date::Day()   const { return m_impl->day(); }


//
// Operators
//

Bool Date::operator==( const Date& rhs ) const { return *m_impl == *rhs.m_impl; }
Bool Date::operator< ( const Date& rhs ) const { return *m_impl <  *rhs.m_impl; }

Date& Date::operator+=( const Days& rhs )
{
    AddAssign( m_impl, rhs.m_impl );
    return *this;
}

Date& Date::operator-=( const Days& rhs )
{
    SubstractAssign( m_impl, rhs.m_impl );
    return *this;
}

Days Date::operator-( const Date& rhs ) const
{
    return Days( std::make_shared< DaysImpl >( *m_impl - *rhs.m_impl ));
}


//
// Conversions
//

std::string Date::ToString() const
{
    return boost::gregorian::to_iso_extended_string( *m_impl );
}


std::string Date::Format( const std::string& format ) const
{
    return DateTimeManager::Instance()->FormatDate( *m_impl, format );
}


//
// Implementation
//

DateImpl::DateImpl()
{
}


DateImpl::DateImpl( boost::gregorian::date&& date )
    : boost::gregorian::date( date )
{
}


///////////////////////////////////////////////////////////////////////////////
//
// Days
//

Days::Days()
    : m_impl( new DaysImpl )
{
}


Days::Days( Int days )
    : m_impl( new DaysImpl( boost::gregorian::days( days )))
{
}


Days::Days( std::shared_ptr< DaysImpl > impl )
    : m_impl( impl )
{
}


//
// Creators
//

Days Days::MaxValue()
{
    return Days( std::make_shared< DaysImpl >( boost::gregorian::days( INT_MAX )));
}


//
// Operators
//

Bool Days::operator==( const Days& rhs ) const { return *m_impl == *rhs.m_impl; }
Bool Days::operator< ( const Days& rhs ) const { return *m_impl <  *rhs.m_impl; }

Days& Days::operator+=( const Days& rhs )
{
    AddAssign( m_impl, rhs.m_impl );
    return *this;
}

Days& Days::operator-=( const Days& rhs )
{
    SubstractAssign( m_impl, rhs.m_impl );
    return *this;
}


//
// Conversions
//

Int Days::ToInt() const { return static_cast< Int >( m_impl->days() ); }


Days::operator TimeSpan() const
{
    const Int MAX_DAYS_TO_TIME_SPAN = INT_MAX / 24;
    const Int days = this->ToInt();

    if ( MAX_DAYS_TO_TIME_SPAN < days )
    {
        CARAMEL_THROW( "Out of convertible range, days: %d", days );
    }

    return Hours( days * 24 );
}


///////////////////////////////////////////////////////////////////////////////
//
// Date Time
//

DateTime::DateTime()
    : m_impl( new DateTimeImpl )
{
}


DateTime::DateTime( const Caramel::Date& date, const Caramel::TimeOfDay& time )
    : m_impl( std::make_shared< DateTimeImpl >( boost::posix_time::ptime( *date.m_impl, *time.m_impl )))
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
    return DateTime( std::make_shared< DateTimeImpl >(
        boost::posix_time::second_clock::local_time() ));
}


DateTime DateTime::MinValue()
{
    return DateTime( std::make_shared< DateTimeImpl >(
        boost::posix_time::ptime( boost::posix_time::min_date_time )));
}


DateTime DateTime::MaxValue()
{
    return DateTime( std::make_shared< DateTimeImpl >(
        boost::posix_time::ptime( boost::posix_time::max_date_time )));
}


DateTime DateTime::FromString( const std::string& s )
{
    return DateTime( std::make_shared< DateTimeImpl >( boost::posix_time::time_from_string( s )));
}


//
// Properties
//

Bool DateTime::IsValid() const { return ! m_impl->is_not_a_date_time(); }


//
// Accessors
//

Int DateTime::Year()  const { return m_impl->date().year(); }
Int DateTime::Month() const { return m_impl->date().month(); }
Int DateTime::Day()   const { return m_impl->date().day(); }

Int DateTime::Hour()   const { return m_impl->time_of_day().hours(); }
Int DateTime::Minute() const { return m_impl->time_of_day().minutes(); }
Int DateTime::Second() const { return m_impl->time_of_day().seconds(); }


Date DateTime::Date() const
{
    return Caramel::Date( std::make_shared< DateImpl >( m_impl->date() ));
}


TimeOfDay DateTime::TimeOfDay() const
{
    return Caramel::TimeOfDay( std::make_shared< TimeDuration >( m_impl->time_of_day() ));
}


//
// Operators
//

Bool DateTime::operator==( const DateTime& rhs ) const { return *m_impl == *rhs.m_impl; }
Bool DateTime::operator< ( const DateTime& rhs ) const { return *m_impl <  *rhs.m_impl; }


DateTime& DateTime::operator+=( const TimeSpan& rhs )
{
    AddAssign( m_impl, rhs.m_impl );
    return *this;
}


DateTime& DateTime::operator-=( const TimeSpan& rhs )
{
    SubstractAssign( m_impl, rhs.m_impl );
    return *this;
}


TimeSpan DateTime::operator-( const DateTime& rhs ) const
{
    return TimeSpan( std::make_shared< TimeDuration >( *m_impl - *rhs.m_impl ));
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


std::string DateTime::Format( const std::string& format ) const
{
    return DateTimeManager::Instance()->FormatDateTime( *m_impl, format );
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
    : m_impl( new TimeDuration )
{
}


TimeSpan::TimeSpan( Int hours, Int minutes, Int seconds )
    : m_impl( new TimeDuration( boost::posix_time::time_duration( hours, minutes, seconds )))
{
}


TimeSpan::TimeSpan( const Caramel::Seconds& seconds )
{
    CARAMEL_ASSERT( LONG_MAX >= seconds.ToDouble() );

    m_impl.reset( new TimeDuration(
        boost::posix_time::seconds( static_cast< Long >( seconds.ToDouble() ))));
}


TimeSpan::TimeSpan( std::shared_ptr< TimeDuration > impl )
    : m_impl( impl )
{
}


//
// Creators
//

TimeSpan TimeSpan::MinValue()
{
    const auto minImpl = boost::posix_time::time_duration::impl_type::min().as_number();

    return TimeSpan( std::make_shared< TimeDuration >(
        boost::posix_time::time_duration( 0, 0, 0, minImpl )));
}


TimeSpan TimeSpan::MaxValue()
{
    const auto maxImpl = boost::posix_time::time_duration::impl_type::max().as_number();

    return TimeSpan( std::make_shared< TimeDuration >(
        boost::posix_time::time_duration( 0, 0, 0, maxImpl )));
}


TimeSpan TimeSpan::FromString( const std::string& s )
{
    return TimeSpan( std::make_shared< TimeDuration >(
        boost::posix_time::duration_from_string( s )));
}


//
// Accessors
//

Int32 TimeSpan::Days()    const { return m_impl->hours() / 24; }
Int32 TimeSpan::Hours()   const { return m_impl->hours() % 24; }
Int32 TimeSpan::Minutes() const { return m_impl->minutes(); }
Int32 TimeSpan::Seconds() const { return m_impl->seconds(); }

Double TimeSpan::TotalDays()    const { return this->TotalSeconds() / 86400; }
Double TimeSpan::TotalHours()   const { return this->TotalSeconds() / 3600; }
Double TimeSpan::TotalMinutes() const { return this->TotalSeconds() / 60; }

Double TimeSpan::TotalSeconds() const
{
    return static_cast< Double >( m_impl->ticks() )
         / boost::posix_time::time_duration::ticks_per_second();
}


//
// Operators
//

Bool TimeSpan::operator==( const TimeSpan& rhs ) const
{
    return *m_impl == *rhs.m_impl;
}


Bool TimeSpan::operator<( const TimeSpan& rhs ) const
{
    return *m_impl < *rhs.m_impl;
}


Bool TimeSpan::operator==( const Caramel::Seconds& rhs ) const
{
    return *this == TimeSpan( rhs );
}


Bool TimeSpan::operator<( const Caramel::Seconds& rhs ) const
{
    return *this < TimeSpan( rhs );
}


TimeSpan& TimeSpan::operator+=( const TimeSpan& rhs )
{
    AddAssign( m_impl, rhs.m_impl );
    return *this;
}


TimeSpan& TimeSpan::operator-=( const TimeSpan& rhs )
{
    SubstractAssign( m_impl, rhs.m_impl );
    return *this;
}


TimeSpan TimeSpan::operator-() const
{
    return TimeSpan( std::make_shared< TimeDuration >( - *m_impl ));
}


//
// Conversions
//

std::string TimeSpan::ToString() const
{
    return boost::posix_time::to_simple_string( *m_impl );
}


TimeSpan::operator Caramel::Seconds() const
{
    return Caramel::Seconds( this->TotalSeconds() );
}



//
// Helper Classes
//

Hours::Hours( Int32 hours )
    : TimeSpan( std::make_shared< TimeDuration >(
        boost::posix_time::hours( static_cast< Long >( hours ))))
{
}


Minutes::Minutes( Int32 minutes )
    : TimeSpan( std::make_shared< TimeDuration >(
        boost::posix_time::minutes( static_cast< Long >( minutes ))))
{
}


///////////////////////////////////////////////////////////////////////////////
//
// Time of Day
//

TimeOfDay::TimeOfDay()
    : m_impl( new TimeDuration )
{
}


TimeOfDay::TimeOfDay( Int hour, Int minute, Int second )
{
    auto tdur = std::make_shared< TimeDuration >(
        boost::posix_time::time_duration( hour, minute, second ));

    if ( tdur->is_negative() || 24 <= tdur->hours() )
    {
        CARAMEL_THROW( "Out of range, %d:%d:%d", hour, minute, second );
    }

    m_impl = tdur;
}



TimeOfDay::TimeOfDay( std::shared_ptr< TimeDuration > impl )
    : m_impl( impl )
{
}


//
// Creators
//

TimeOfDay TimeOfDay::Now()
{
    return TimeOfDay( std::make_shared< TimeDuration >(
        boost::posix_time::second_clock::local_time().time_of_day() ));
}


TimeOfDay TimeOfDay::FromString( const std::string& s )
{
    auto tdur = std::make_shared< TimeDuration >( boost::posix_time::duration_from_string( s ));

    if ( tdur->is_negative() || 24 <= tdur->hours() )
    {
        CARAMEL_THROW( "Out of range, input: %s", s );
    }

    return TimeOfDay( tdur );
}


//
// Accessors
//

Int TimeOfDay::Hour()   const { return m_impl->hours(); }
Int TimeOfDay::Minute() const { return m_impl->minutes(); }
Int TimeOfDay::Second() const { return m_impl->seconds(); }


//
// Operators
//

Bool TimeOfDay::operator==( const TimeOfDay& rhs ) const
{
    return *m_impl == *rhs.m_impl;
}


Bool TimeOfDay::operator<( const TimeOfDay& rhs ) const
{
    return *m_impl < *rhs.m_impl;
}


//
// Conversions
//

std::string TimeOfDay::ToString() const
{
    return boost::posix_time::to_simple_string( *m_impl );
}


///////////////////////////////////////////////////////////////////////////////
//
// DateTime Manager
//

DateTimeManager::DateTimeManager()
    : m_dateFacet( new DateFacet )
    , m_timeFacet( new TimeFacet )
{
    m_dateStream.imbue( std::locale( std::locale::classic(), m_dateFacet ));
    m_timeStream.imbue( std::locale( std::locale::classic(), m_timeFacet ));
}


std::string DateTimeManager::FormatDate(
    const boost::gregorian::date& date, const std::string& format )
{
    auto ulock = UniqueLock( m_mutex );

    m_dateFacet->format( format.c_str() );
    m_dateStream.str( "" );
    m_dateStream << date;
    return m_dateStream.str();
}


std::string DateTimeManager::FormatDateTime(
    const boost::posix_time::ptime& dateTime, const std::string& format )
{
    auto ulock = UniqueLock( m_mutex );

    m_timeFacet->format( format.c_str() );
    m_timeStream.str( "" );
    m_timeStream << dateTime;
    return m_timeStream.str();
}


///////////////////////////////////////////////////////////////////////////////
//
// Validations
//

static_assert(
    std::is_same< boost::gregorian::greg_year::value_type, Uint16 >::value,
    "Type of greg_year should be Uint16" );

static_assert(
    std::is_same< boost::gregorian::greg_month::value_type, Uint16 >::value,
    "Type of greg_month should be Uint16" );

static_assert(
    std::is_same< boost::gregorian::greg_day::value_type, Uint16 >::value,
    "Type of greg_day should be Uint16" );

static_assert(
    std::is_same< boost::posix_time::time_duration::hour_type, Int32 >::value,
    "Type of hour_type should be Int32" );

static_assert(
    std::is_same< boost::posix_time::time_duration::min_type, Int32 >::value,
    "Type of min_type should be Int32" );

static_assert(
    std::is_same< boost::posix_time::time_duration::sec_type, Int32 >::value,
    "Type of sec_type should be Int32" );

    

///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
