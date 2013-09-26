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

    explicit TaskImpl( TaskFunction&& f );

private:

    TaskFunction m_function;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_IMPL_H
