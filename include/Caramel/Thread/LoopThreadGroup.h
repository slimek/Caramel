// Caramel C++ Library - Thread Facility - Loop Thread Group Header

#ifndef __CARAMEL_THREAD_LOOP_THREAD_GROUP_H
#define __CARAMEL_THREAD_LOOP_THREAD_GROUP_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Thread/ThreadTypes.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Loop Thread Group
//

class LoopThreadGroupImpl;

class LoopThreadGroup
{
public:

    LoopThreadGroup();
    ~LoopThreadGroup();

    // The first execute is delayed for an interval.
    void Start( const std::string& name, WorkFunction work, const Ticks& interval );

    void StopAll();


private:

    std::unique_ptr< LoopThreadGroupImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_THREAD_LOOP_THREAD_GROUP_H
