// Caramel C++ Library - Thread Facility - This Thread Header

#ifndef __CARAMEL_THREAD_THIS_THREAD_H
#define __CARAMEL_THREAD_THIS_THREAD_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Thread/ThreadId.h>

#if defined( CARAMEL_SYSTEM_IS_WINDOWS )
// Remove the evil define in WinBase.h !
#undef Yield
#endif


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// This Thread
//

class ThisThread
{
public:

    static ThreadId GetId();

    static void SleepFor( const Ticks& duration );

    // Hint to reschedule threads, to allow other threads run.
    static void Yield();

    // Set the handler when the thread exits.
    // - If this thread is not a Caramel thread, this function do nothing.
    //   You can only set 1 exit routines for each thread.
    static void AtThreadExit( std::function< void() > atExit );
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_THREAD_THIS_THREAD_H
