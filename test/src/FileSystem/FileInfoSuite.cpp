// Caramel C++ Library Test - File System - File Info Suite

//
// Notes: This test suite can only be run on a Desktop platform.
//

#include "CaramelTestPch.h"

#include <Caramel/FileSystem/FileInfo.h>


namespace Caramel
{

SUITE( FileInfo )
{

TEST( FileInfo )
{
    FileInfo test1( "../assets/test1.ini" );
    CHECK( test1.Exists() );

    FileInfo noFile( "../assets/noFile.txt" );
    CHECK( ! noFile.Exists() );

    FileInfo size5( "../assets/size5.txt" );
    CHECK( size5.Exists() );
    CHECK( 5 == size5.Size() );
}

} // SUITE FileInfo

} // namespace Caramel
