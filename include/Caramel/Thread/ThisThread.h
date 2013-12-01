// Caramel C++ Library - Thread Facility - This Thread Header

#ifndef __CARAMEL_THREAD_THIS_THREAD_H
#define __CARAMEL_THREAD_THIS_THREAD_H
#pragma once

#include <Caramel/Caramel.h>
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

    static Uint GetThreadId();

    static void SleepFor( const Ticks& duration );
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_THREAD_THIS_THREAD_H
