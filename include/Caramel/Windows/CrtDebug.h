// Caramel C++ Library - Windows Facility - CRT Debug Header

#ifndef __CARAMEL_WINDOWS_CRT_DEBUG_H
#define __CARAMEL_WINDOWS_CRT_DEBUG_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


#if defined( CARAMEL_SYSTEM_IS_WINDOWS )


namespace Caramel
{

namespace Windows
{

///////////////////////////////////////////////////////////////////////////////
//
// Stand-alone Functions
//

void EnableMemoryLeakCheckAtExit();


///////////////////////////////////////////////////////////////////////////////

} // namespace Windows

} // namespace Caramel

#endif // CARAMEL_SYSTEM_IS_WINDOWS

#endif // __CARAMEL_WINDOWS_CRT_DEBUG_H
