// Caramel C++ Library - Task Facility - Workpile Header

#ifndef __CARAMEL_TASK_WORKPILE_H
#define __CARAMEL_TASK_WORKPILE_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Task/TaskExecutor.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Workpile
//

class WorkpileImpl;

class Workpile : public TaskExecutor
{
public:

    Workpile();

    void Submit( const Task& task ) override;

    void PollOne();


private:

    std::shared_ptr< WorkpileImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_WORKPILE_H
