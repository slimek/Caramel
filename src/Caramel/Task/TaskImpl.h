// Caramel C++ Library - Task Facility - Task Private Header

#ifndef __CARAMEL_TASK_TASK_IMPL_H
#define __CARAMEL_TASK_TASK_IMPL_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Task/Task.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Task
//

class TaskImpl
{
public:

    TaskImpl( const std::string& name, TaskFunction&& f );


    /// Operations ///

    void DelayFor( const TickDuration& duration );

    void Run();


    /// Properties ///

    Bool IsDelayed() const { return m_delayed; }

    TickDuration GetDelayDuration() const { return m_delayDuration; }


private:

    std::string  m_name;
    TaskFunction m_function;

    
    /// Delay ///

    Bool m_delayed;
    TickDuration m_delayDuration;

};

typedef std::shared_ptr< TaskImpl > TaskPtr;


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_IMPL_H
