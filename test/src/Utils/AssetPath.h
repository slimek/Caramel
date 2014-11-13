// Caramel C++ Library Test - Utilits - Asset Path Header

#ifndef __CARAMEL_TEST_UTILS_ASSET_PATH_H
#define __CARAMEL_TEST_UTILS_ASSET_PATH_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/FileSystem/Path.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Asset Path
// - A path to the assets directory. The implementation depends on each system.
//   Windows: RunTest.cpp
//

Path AssetPath( const std::string& fileName );


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TEST_UTILS_ASSET_PATH_H
