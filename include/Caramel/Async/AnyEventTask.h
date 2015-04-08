// Caramel C++ Library - Async Facility - Any Event Task Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_TASK_H
#define __CARAMEL_ASYNC_ANY_EVENT_TASK_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/AnyEvent.h>
#include <Caramel/Async/AnyEventTarget.h>
#include <Caramel/Task/Task.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Task
// - A specialized task with resulf of AnyEvent.
//   You may use Then() to give it a continuation task,
//   or use Link() to link an AnyEventTarget.
//

class AnyEventTask : public Task< AnyEvent >
{
public:
    
    typedef std::function< AnyEvent() > AnyEventFunction;

    AnyEventTask();
    AnyEventTask( Task< AnyEvent > task );

    // When the task is completed, send an event to the target.
    void Link( AnyEventTarget& target );


    //
    // Access the Event
    // - These functions are based on Task::GetResult(). For this reason :
    //
    //   1. They block the thread if the task is not completed yet.
    //   2. They throw exceptions if the task is fault or canceled.
    //              

    Int Id() const;

    template< typename T >
    T Value() const;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename T >
inline T AnyEventTask::Value() const
{
    return this->GetResult().Value< T >();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_TASK_H
