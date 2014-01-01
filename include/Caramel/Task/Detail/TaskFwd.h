// Caramel C++ Library - Task Facility - Detail - Forwards Header

#ifndef __CARAMEL_TASK_DETAIL_TASK_FWD_H
#define __CARAMEL_TASK_DETAIL_TASK_FWD_H
#pragma once

#include <Caramel/Caramel.h>
#include <functional>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Typedefs
//

typedef std::function< void() > TaskFunction;


///////////////////////////////////////////////////////////////////////////////
//
// Forwards Declaration
//

class Strand;
class Task;
class TaskExecutor;
class TaskPoller;


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_DETAIL_TASK_FWD_H
