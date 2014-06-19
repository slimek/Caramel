// Caramel C++ Library Test - File System - Directory Info Suite

#include "CaramelTestPch.h"

#include <Caramel/FileSystem/DirectoryInfo.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( DirectoryInfoSuite )
{

TEST( DirectoryInfoTest )
{
    DirectoryInfo dir( "temp-dir" );

    if ( dir.Exists() )
    {
        dir.Delete();
    }

    dir.Create();
    dir.Create();  // Try to create an existing directory is Ok.

    CHECK( true == dir.Exists() );

    dir.Delete();

    CHECK( false == dir.Exists() );
}


} // SUITE DirectoryInfoSuite

} // namespace Caramel
