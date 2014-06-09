// Caramel C++ Library - Chrono Amenity - Clock Proxy Header

#ifndef __CARAMEL_CHRONO_CLOCK_PROXY_H
#define __CARAMEL_CHRONO_CLOCK_PROXY_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Chrono/Detail/ClockProxyHolder.h>
#include <Caramel/Chrono/TickClock.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Clock Proxy
//

class ClockProxy
{
public:

    template< typename ClockType >
    ClockProxy( ClockType );

    Ticks SinceEpoch();


private:
    std::shared_ptr< Detail::ClockProxyHolder > m_holder;
};


template< typename ClockType >
inline ClockProxy MakeClockProxy()
{
    return ClockProxy( ClockType() );
}


//
// Implementation
//

template< typename ClockType >
inline ClockProxy::ClockProxy( ClockType )
    : m_holder( new Detail::ConcreteClockProxyHolder< ClockType > )
{
}


inline Ticks ClockProxy::SinceEpoch()
{
    return m_holder->SinceEpoch();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CHRONO_CLOCK_PROXY_H
