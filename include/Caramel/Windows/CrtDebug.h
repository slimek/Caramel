// Caramel C++ Library - Windows Facility - CRT Debug Header

#ifndef __CARAMEL_WINDOWS_CRT_DEBUG_H
#define __CARAMEL_WINDOWS_CRT_DEBUG_H
#pragma once

#include <Caramel/Caramel.h>


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
