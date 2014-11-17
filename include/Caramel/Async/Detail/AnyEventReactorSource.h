// Caramel C++ Library - Async Facility - Detail - Any Event Reactor Source Header

#ifndef __CARAMEL_ASYNC_DETAIL_ANY_EVENT_REACTOR_SOURCE_H
#define __CARAMEL_ASYNC_DETAIL_ANY_EVENT_REACTOR_SOURCE_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/AnyEventTarget.h>
#include <functional>


namespace Caramel
{

// Forwards declaration
class AnyEventReactor;

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Reactor Source
//

class AnyEventReactorSource : public AnyEventTarget
{
    friend class Caramel::AnyEventReactor;

public:

    ~AnyEventReactorSource();


    /// AnyEventTarget operations ///

    // Unlink from all dispatchers.
    // But since the source doesn't store events, there is nothing to clear.
    void Reset() override;

private:

    class Impl;
    
    AnyEventReactorSource( std::shared_ptr< Impl > impl );

    AnyEventTargetPtr GetTargetImpl() const override;


    /// Data Members ///

    std::shared_ptr< Impl > m_impl;

    // the reference counting of this Source.
    std::shared_ptr< std::nullptr_t > m_null;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_ASYNC_DETAIL_ANY_EVENT_REACTOR_SOURCE_H
