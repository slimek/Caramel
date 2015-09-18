// Caramel C++ Library - Task Facility - Async Submit Private Header

#ifndef __CARAMEL_TASK_ASYNC_SUBMIT_IMPL_H
#define __CARAMEL_TASK_ASYNC_SUBMIT_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Object/FacilityLongevity.h"
#include <Caramel/Object/Singleton.h>
#include <Caramel/Task/AsyncSubmit.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Async Submit Center
//

class AsyncSubmitCenter : public TaskExecutor
                        , public Singleton< AsyncSubmitCenter, FACILITY_LONGEVITY_TASK >
{
public:

    void Submit( TaskCore& task ) override;

    void AddReadyTask( TaskCore& task ) override;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_ASYNC_SUBMIT_IMPL_H

