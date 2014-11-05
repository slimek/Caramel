// Caramel C++ Library - Async Facility - Any Event Poller Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_POLLER_H
#define __CARAMEL_ASYNC_ANY_EVENT_POLLER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/Detail/AnyEventPollerSource.h>
#include <Caramel/Async/AnyEvent.h>
#include <boost/noncopyable.hpp>
#include <functional>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Poller
// - The class provides the mechanism:
//
//   1. Start an asynchronous action, and assign a completion handler to it.
//   2. When the action is done, the background thread put the event and its handler
//      into the Poller.
//   3. A user thread polls the events and calls their own handler.
//

class AnyEventPollerImpl;

class AnyEventPoller : public boost::noncopyable
{
public:

    AnyEventPoller();
    ~AnyEventPoller();


    // Provide the source to emit events.
    Detail::AnyEventPollerSource Receive( std::function< void( const AnyEvent& ) > handler );

    // Polling the enqueued events, and call the receiving handler with polled events.
    void PollOne();

    // Unlink from all sources, and clear the event queue.
    void Reset();


private:

    /// Data Members ///

    std::shared_ptr< AnyEventPollerImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_POLLER_H
