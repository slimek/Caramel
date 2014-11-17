// Caramel C++ Library - Async Facility - Any Event Reactor Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_REACTOR_H
#define __CARAMEL_ASYNC_ANY_EVENT_REACTOR_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/Detail/AnyEventReactorSource.h>
#include <Caramel/Async/AnyEvent.h>
#include <boost/noncopyable.hpp>
#include <functional>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Reactor
// - The class provides the mechanism:
//
//   1. Start an asynchronous action, and assign a completion handler to it.
//   2. When the action is done, the background thread put the event and its handler
//      into the Reactor.
//   3. A user thread polls the events and calls their own handler.
//

class AnyEventReactorImpl;

class AnyEventReactor : public boost::noncopyable
{
public:

    AnyEventReactor();
    ~AnyEventReactor();


    // Provide the source to emit events.
    Detail::AnyEventReactorSource Receive( std::function< void( const AnyEvent& ) > handler );

    // Polling the enqueued events, and call the receiving handler with polled events.
    void PollOne();

    // Unlink from all sources, and clear the event queue.
    void Reset();


private:

    /// Data Members ///

    std::shared_ptr< AnyEventReactorImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_REACTOR_H
