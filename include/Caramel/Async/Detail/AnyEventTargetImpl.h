// Caramel C++ Library - Async Amenity - Detail - Any Event Target Private Header

#ifndef __CARAMEL_ASYNC_DETAIL_ANY_EVENT_TARGET_IMPL_H
#define __CARAMEL_ASYNC_DETAIL_ANY_EVENT_TARGET_IMPL_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Async/AnyEvent.h>
#include <Caramel/Error/Assert.h>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Target
//

class AnyEventTargetImpl
{
public:

    AnyEventTargetImpl();
    virtual ~AnyEventTargetImpl() {}

    virtual void Send( const AnyEvent& evt ) = 0;


    /// Target Destroyed ///

    void Destroy();

    Bool IsDestroyed() const { return m_destroyed; }


private:

    Bool m_destroyed;
};

typedef std::shared_ptr< AnyEventTargetImpl > AnyEventTargetPtr;


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline AnyEventTargetImpl::AnyEventTargetImpl()
    : m_destroyed( false )
{
}


inline void AnyEventTargetImpl::Destroy()
{
    CARAMEL_ASSERT( ! m_destroyed );
    m_destroyed = true;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_ASYNC_DETAIL_ANY_EVENT_TARGET_IMPL_H
