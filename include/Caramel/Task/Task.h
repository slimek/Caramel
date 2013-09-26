// Caramel C++ Library - Task Facility - Task Header

#ifndef __CARAMEL_TASK_TASK_H
#define __CARAMEL_TASK_TASK_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Task/TaskTypes.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Task
//

class TaskImpl;

class Task
{
public:

    Task();
    explicit Task( TaskFunction&& f );


private:

    std::shared_ptr< TaskImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_H
