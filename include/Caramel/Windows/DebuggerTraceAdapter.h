// Caramel C++ Library - Windows Facility - Debugger Trace Adapter Header

#ifndef __CARAMEL_WINDOWS_DEBUGGER_TRACE_ADAPTER_H
#define __CARAMEL_WINDOWS_DEBUGGER_TRACE_ADAPTER_H
#pragma once

#include <Caramel/Caramel.h>


#if defined( CARAMEL_SYSTEM_IS_WINDOWS )

#include <Caramel/Trace/Listeners.h>


namespace Caramel
{

namespace Windows
{

///////////////////////////////////////////////////////////////////////////////
//
// Debugger Trace Listener
//

class DebuggerTraceAdapter : public Trace::Listener
{
public:

    void Write( Trace::Level level, const std::string& message ) override;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Windows

} // namespace Caramel

#endif // CARAMEL_SYSTEM_IS_WINDOWS

#endif // __CARAMEL_WINDOWS_DEBUGGER_TRACE_ADAPTER_H
