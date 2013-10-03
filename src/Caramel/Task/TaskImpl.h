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


    /// Properties ///

    Bool IsDelayed() const;

    TickDuration GetDelayDuration() const;


private:

    std::string  m_name;
    TaskFunction m_function;

};

typedef std::shared_ptr< TaskImpl > TaskPtr;


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_IMPL_H
