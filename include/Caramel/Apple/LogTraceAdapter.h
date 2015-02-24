// Caramel C++ Library - Apple Facility - Log Trace Adapter Header

#ifndef __CARAMEL_APPLE_LOG_TRACE_ADAPTER_H
#define __CARAMEL_APPLE_LOG_TRACE_ADAPTER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Trace/Listeners.h>


namespace Caramel
{

namespace Apple
{

///////////////////////////////////////////////////////////////////////////////
//
// Log Trace Adapter
// - By-pass trace message to NSLog.
//

class LogTraceAdapter : public Trace::Listener
{
public:

    void Write( Trace::Level level, const std::string& messgae ) override;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Apple

} // namespace Caramel

#endif // __CARAMEL_APPLE_LOG_TRACE_ADAPTER_H
