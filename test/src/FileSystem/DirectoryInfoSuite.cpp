// Caramel C++ Library Test - File System - Directory Info Suite

#include "CaramelTestPch.h"

#include <Caramel/FileSystem/DirectoryInfo.h>
#include <Caramel/FileSystem/FileInfo.h>
#include <Caramel/Io/OutputFileStream.h>
#include <Caramel/Io/TextStreamWriter.h>
#include <boost/filesystem/operations.hpp>


namespace Caramel
{

SUITE( DirectoryInfo )
{

TEST( DirectoryInfo )
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

    // Throws if delete an absent directory
    CHECK_THROW( dir.Delete(), Caramel::Exception );


    /// Delete All - Recursively ///

    dir.Create();
    
    FileInfo fi( dir.GetPath() / "temp.txt" );

    OutputFileStream file( fi.GetPath() );
    TextStreamWriter writer( file );
    writer.WriteLine( "Hello World!" );
    file.Close();

    CHECK( true == fi.Exists() );

    // Throws if delete a non-empty directory
    CHECK_THROW( dir.Delete(), boost::filesystem::filesystem_error );

    // Recursively delete is Ok
    dir.DeleteAll();

    CHECK( false == fi.Exists() );
    CHECK( false == dir.Exists() );

    // Throws if delete an absent directory
    CHECK_THROW( dir.DeleteAll(), Caramel::Exception );
}


} // SUITE DirectoryInfo

} // namespace Caramel
