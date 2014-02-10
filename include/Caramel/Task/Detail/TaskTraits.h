// Caramel C++ Library - Task Facility - Detail - Task Traits Header

#ifndef __CARAMEL_TASK_DETAIL_TASK_TRAITS_H
#define __CARAMEL_TASK_DETAIL_TASK_TRAITS_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Task/Detail/TaskFwd.h>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Task Function Traits
//

template< typename Function, typename AnteResult >
struct ThenFunctionTraits
{
    typedef decltype( std::declval< Function >()( Task< AnteResult >() )) ResultType;
    typedef Task< ResultType > TaskType;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detial

} // namespace Caramel

#endif // __CARAMEL_TASK_DETAIL_TASK_TRAITS_H
