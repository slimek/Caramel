// Caramel C++ Library Test - Utilits - Writable Path Header

#ifndef __CARAMEL_TEST_UTILS_WRITABLE_PATH_H
#define __CARAMEL_TEST_UTILS_WRITABLE_PATH_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/FileSystem/DirectoryInfo.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Writable Path
//

#if defined( CARAMEL_SYSTEM_OF_DESKTOP )

// Desktop: working directory
inline Path WritablePath()
{
    return DirectoryInfo::Current().GetPath();
}

#elif defined( CARAMEL_SYSTEM_IS_ANDROID )

// Android: Files directory
Path WritablePath();

#else

// Other systems are not implemented yet.

#endif



///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TEST_UTILS_WRITABLE_PATH_H

