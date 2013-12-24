// Caramel C++ Library - Trace Facility - Listeners Private Header

#ifndef __CARAMEL_TRACE_LISTENERS_IMPL_H
#define __CARAMEL_TRACE_LISTENERS_IMPL_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Concurrent/Queue.h>
#include <Caramel/Trace/Listeners.h>


namespace Caramel
{

namespace Trace
{

///////////////////////////////////////////////////////////////////////////////
//
// Message Queue
//

struct MessageEntry
{
    MessageEntry()
        : level( LEVEL_SILENT )
    {}

    MessageEntry( Level level, const std::string& message )
        : level( level )
        , message( message )
    {}

    Level level;
    std::string message;
};


class MessageQueueImpl
{
    friend class MessageQueue;

    Concurrent::Queue< MessageEntry > m_queue;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Trace

} // namespace Caramel

#endif // __CARAMEL_TRACE_LISTENERS_IMPL_H
