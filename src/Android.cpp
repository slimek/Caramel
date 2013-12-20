// Caramel C++ Library - Android Facility - Implementation

#include "CaramelPch.h"


#if defined( CARAMEL_SYSTEM_IS_ANDROID )

#include <Caramel/Android/LogTraceAdapter.h>
#include <android/log.h>


namespace Caramel
{

namespace Android
{

//
// Contents
//
//   LogTraceAdapter
//

///////////////////////////////////////////////////////////////////////////////
//
// Log Trace Adapter
//

LogTraceAdapter::LogTraceAdapter( const std::string& tagName )
    : m_tagName( tagName )
{
}


void LogTraceAdapter::Write( Trace::Level level, const std::string& message )
{
    CARAMEL_ASSERT( Trace::LEVEL_VERBOSE <= level && level <= Trace::LEVEL_ERROR );

    const auto priority = static_cast< android_LogPriority >( static_cast< Int >( level ) + 1 );

    __android_log_write( priority, m_tagName.c_str(), message.c_str() );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Android

} // namespace Caramel

#endif // CARAMEL_SYSTEM_IS_ANDROID
