// Caramel C++ Library - Chrono Amenity - Detail Clock Proxy Holder Header

#ifndef __CARAMEL_CHRONO_DETAIL_CLOCK_PROXY_HOLDER_H
#define __CARAMEL_CHRONO_DETAIL_CLOCK_PROXY_HOLDER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Chrono/TickClock.h>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Clock Proxy Holder
//

class ClockProxyHolder
{
public:
    virtual ~ClockProxyHolder() {}

    virtual Ticks SinceEpoch() const = 0;
};


template< typename ClockType >
class ConcreteClockProxyHolder : public ClockProxyHolder
{
public:

    Ticks SinceEpoch() const
    {
        const auto now = ClockType::Now();
        return Ticks( now.time_since_epoch() );
    }
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_CHRONO_DETAIL_CLOCK_PROXY_HOLDER_H
