// Caramel C++ Library - Windows Facility - Debugger Trace Listener Header

#ifndef __CARAMEL_WINDOWS_DEBUGGER_TRACE_LISTENER_H
#define __CARAMEL_WINDOWS_DEBUGGER_TRACE_LISTENER_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


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

class DebuggerTraceListener : public Trace::Listener
{
public:

    void Write( Trace::Level level, const std::string& message );
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Windows

} // namespace Caramel

#endif // CARAMEL_SYSTEM_IS_WINDOWS

#endif // __CARAMEL_WINDOWS_DEBUGGER_TRACE_LISTENER_H
