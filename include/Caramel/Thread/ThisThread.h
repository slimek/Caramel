// Caramel C++ Library - Thread Facility - This Thread Header

#ifndef __CARAMEL_THREAD_THIS_THREAD_H
#define __CARAMEL_THREAD_THIS_THREAD_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Chrono/TickClock.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// This Thread
//

class ThisThread
{
public:

    static void SleepFor( const TickDuration& duration );
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_THREAD_THIS_THREAD_H
