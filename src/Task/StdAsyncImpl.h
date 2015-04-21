// Caramel C++ Library - Task Facility - Std Async Private Header

#ifndef __CARAMEL_TASK_STD_ASYNC_IMPL_H
#define __CARAMEL_TASK_STD_ASYNC_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Object/FacilityLongevity.h"
#include <Caramel/Object/Singleton.h>
#include <Caramel/Task/StdAsync.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Std Async Center
//

class StdAsyncCenter : public Singleton< StdAsyncCenter, FACILITY_LONGEVITY_STD_ASYNC >
{
public:

    void Submit( TaskCore& task );

private:

    StdAsyncProxy m_executor;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_STD_ASYNC_IMPL_H
