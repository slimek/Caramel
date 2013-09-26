// Caramel C++ Library - Task Facility - Workpile Private Header

#ifndef __CARAMEL_TASK_WORKPILE_IMPL_H
#define __CARAMEL_TASK_WORKPILE_IMPL_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Concurrent/PriorityQueue.h>
#include <Caramel/Task/Workpile.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Workpile
//

class WorkpileImpl
{
    friend class Workpile;

public:

private:

    typedef Concurrent::PriorityQueue< Int, Task > DelayedTaskQueue;
    DelayedTaskQueue m_delayedTasks;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_WORKPILE_IMPL_H
