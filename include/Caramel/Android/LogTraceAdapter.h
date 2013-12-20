// Caramel C++ Library - Android Facility - Log Trace Adapter Header

#ifndef __CARAMEL_ANDROID_LOG_TRACE_ADAPTER_H
#define __CARAMEL_ANDROID_LOG_TRACE_ADAPTER_H
#pragma once

#include <Caramel/Caramel.h>


#if defined( CARAMEL_SYSTEM_IS_ANDROID )

#include <Caramel/Trace/Listeners.h>


namespace Caramel
{

namespace Android
{

///////////////////////////////////////////////////////////////////////////////
//
// Log Trace Adapter
// - By-pass trace message to Android logging.
//

class LogTraceAdapter : public Trace::Listener
{
public:

    explicit LogTraceAdapter( const std::string& tagName );

    void Write( Trace::Level level, const std::string& messgae ) override;

private:

    std::string m_tagName;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Android

} // namespace Caramel

#endif // CARAMEL_SYSTEM_IS_ANDROID

#endif // __CARAMEL_ANDROID_LOG_TRACE_ADAPTER_H
