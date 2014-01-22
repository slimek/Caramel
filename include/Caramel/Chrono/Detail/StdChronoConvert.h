// Caramel C++ Library - Chrono Amenity - Deteail - std::chrono Convert Header
//
// Caramel.Chrono is based on Boost.Chrono .
// In some case (for example, std::thread), we need to provide std::chrono as function arguments.
// Here is the conversion for this issue.
//
// TODO: In later implementation, when we migrate from Boost.Chrono to std::chrono,
//       These conversion would be removed.
//

#ifndef __CARAMEL_CHRONO_DETAIL_STD_CHRONO_CONVERT_H
#define __CARAMEL_CHRONO_DETAIL_STD_CHRONO_CONVERT_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Chrono/TickClock.h>
#include <chrono>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Convert Duration
//

inline std::chrono::duration< Int64, std::milli > StdChronoDuration( const Ticks& ticks )
{
    return std::chrono::duration< Int64, std::milli >( ticks.count() );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_CHRONO_DETAIL_STD_CHRONO_CONVERT_H
