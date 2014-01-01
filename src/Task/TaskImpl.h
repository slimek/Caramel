// Caramel C++ Library - Task Facility - Task Private Header

#ifndef __CARAMEL_TASK_TASK_IMPL_H
#define __CARAMEL_TASK_TASK_IMPL_H
#pragma once

#include <Caramel/Caramel.h>
#include "Task/StrandImpl.h"
#include <Caramel/Task/Task.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Task
//

class TaskImpl
{
    friend class Task;

public:

    TaskImpl();  // Not-a-task

    TaskImpl( const std::string& name, TaskFunction&& f );


    /// Operations ///

    void DelayFor( const Ticks& duration );
    void Schedule( const StrandPtr& strand );

    void Run();


    /// Properties ///

    Bool IsValid() const { return m_function; }


private:

    std::string  m_name;
    TaskFunction m_function;

    
    /// Delay ///

    Bool m_hasDelay;
    Ticks m_delayDuration;


    /// Strand ///

    StrandPtr m_strand;

};

typedef std::shared_ptr< TaskImpl > TaskPtr;


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_IMPL_H
