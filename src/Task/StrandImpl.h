// Caramel C++ Library - Task Facility - Strand Private Header

#ifndef __CARAMEL_TASK_STRAND_IMPL_H
#define __CARAMEL_TASK_STRAND_IMPL_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Task/Strand.h>
#include <deque>


namespace Caramel
{

class TaskImpl;
typedef std::shared_ptr< TaskImpl > TaskPtr;

///////////////////////////////////////////////////////////////////////////////
//
// Strand
//

class StrandImpl
{
public:

    void PushTask( const TaskPtr& task );
    void PopFront( const TaskPtr& callingTask );

    Bool PeekFrontIfReady( TaskPtr& task );


private:

    std::mutex m_queueMutex;

    typedef std::deque< TaskPtr > TaskQueue;
    TaskQueue m_blockedTasks;
};

typedef std::shared_ptr< StrandImpl > StrandPtr;


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_STRAND_IMPL_H
