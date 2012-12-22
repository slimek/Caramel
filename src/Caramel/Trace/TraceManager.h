// Caramel C++ Library - Trace Facility - Trace Manager Header

#ifndef __CARAMEL_TRACE_TRACE_MANAGER_H
#define __CARAMEL_TRACE_TRACE_MANAGER_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Object/Singleton.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Trace Manager
//

class TraceManager : public Singleton< TraceManager >
{
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TRACE_TRACE_MANAGER_H
