// Caramel C++ Library - Task Facility - Task Private Header

#ifndef __CARAMEL_TASK_TASK_IMPL_H
#define __CARAMEL_TASK_TASK_IMPL_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Task/Task.h>


namespace Caramel
{

class StrandImpl;
typedef std::shared_ptr< StrandImpl > StrandPtr;

///////////////////////////////////////////////////////////////////////////////
//
// Task
//

class TaskImpl : public std::enable_shared_from_this< TaskImpl >
{
    friend class Task;

public:

    TaskImpl();  // Not-a-task

    TaskImpl( const std::string& name, TaskFunction&& f );


    /// Operations ///

    void DelayFor( const Ticks& duration );
    void Schedule( const StrandPtr& strand );

    void PushToStrand( TaskExecutor* executor );
    void Run();


    /// State Transition ///

    Bool TransitToDelayed();
    Bool TransitToBlocked();
    Bool TransitToReady();


    /// Properties ///

    Bool  IsValid() const { return m_function; }
    Task* GetHost() const { return m_host; }


private:

    std::string  m_name;
    TaskFunction m_function;

    Task* m_host;

    /// State ///

    enum State
    {
        TASK_S_INITIAL          = 0x01,
        TASK_S_DELAYING         = 0x02,
        TASK_S_WAITING          = 0x04,
        TASK_S_READY            = 0x08,
        TASK_S_RUNNING          = 0x10,
        TASK_S_RAN_TO_COMPLETE  = 0x20,
    
    } m_state;

    std::mutex m_stateMutex;

    
    /// Delay ///

    Bool  m_hasDelay;
    Ticks m_delayDuration;


    /// Schedule and Run ///

    StrandPtr     m_strand;
    TaskExecutor* m_executor;

};

typedef std::shared_ptr< TaskImpl > TaskPtr;


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_IMPL_H
