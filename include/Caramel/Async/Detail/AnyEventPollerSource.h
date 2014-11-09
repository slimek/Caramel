// Caramel C++ Library - Async Facility - Detail - Any Event Poller Source Header

#ifndef __CARAMEL_ASYNC_DETAIL_ANY_EVENT_POLLER_SOURCE_H
#define __CARAMEL_ASYNC_DETAIL_ANY_EVENT_POLLER_SOURCE_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/AnyEventTarget.h>
#include <functional>


namespace Caramel
{

// Forwards declaration
class AnyEventPoller;

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Poller source
//

class AnyEventPollerSource : public AnyEventTarget
{
    friend class Caramel::AnyEventPoller;

public:

    ~AnyEventPollerSource();


    /// AnyEventTarget operations ///

    // Unlink from all dispatchers.
    // But since the source doesn't store events, there is nothing to clear.
    void Reset() override;

private:

    class Impl;
    
    AnyEventPollerSource( std::shared_ptr< Impl > impl );

    AnyEventTargetPtr GetTargetImpl() const override;


    /// Data Members ///

    std::shared_ptr< Impl > m_impl;

    // the reference counting of this Source.
    std::shared_ptr< std::nullptr_t > m_null;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_ASYNC_DETAIL_ANY_EVENT_POLLER_SOURCE_H
