// Caramel C++ Library - Trace Facility - Trace Header

#ifndef __CARAMEL_TRACE_TRACE_H
#define __CARAMEL_TRACE_TRACE_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Thread/Mutex.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Built-in Trace Channels
//

enum TraceChannelId : Int
{
    TRACE_CHANNEL_FAIL    = 1,
    TRACE_CHANNEL_WARNING = 2,
    TRACE_CHANNEL_INFO    = 3,
    TRACE_CHANNEL_VERBOSE = 4,
};


///////////////////////////////////////////////////////////////////////////////
//
// Trace Output Functions
//

void TraceWrite( Int channelId, const std::string& message );

void TraceWriteHere( Int channelId, const std::string& function, const std::string& message );


//
// External Mutex
// - Locks the Trace for writing a block of messages.
//

Mutex& GetTraceMutex();


} // namespace Caramel

///////////////////////////////////////////////////////////////////////////////
//
// Trace Macros
//

#define CARAMEL_TRACE_LOCK() \
    Caramel::Mutex::UniqueLock traceLock( Caramel::GetTraceMutex() )
    

#define CARAMEL_TRACE_FAIL_HERE( failMsg ) \
    CARAMEL_TRACE_LOCK(); \
    Caramel::TraceWriteHere( Caramel::TRACE_CHANNEL_FAIL, __FUNCTION__, failMsg )


///////////////////////////////////////////////////////////////////////////////

#endif // __CARAMEL_TRACE_TRACE_H

