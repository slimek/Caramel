// Caramel C++ Library Test - File System - Path Suite

#include "CaramelTestPch.h"

#include <Caramel/FileSystem/Path.h>


namespace Caramel
{

SUITE( Path )
{

TEST( PathDecomposition )
{
    const Path nil( "" );
    const Path file( "file" );
    const Path ext( ".ext" );
    const Path fext( "file.ext" );
    const Path dir( "dir" );
    const Path dsub( "dir.sub" );

    const Path p0( "" );
    CHECK( nil  == p0.Directory() );
    CHECK( nil  == p0.Filename() );
    CHECK( nil  == p0.Stem() );
    CHECK( nil  == p0.Extension() );

    const Path p1( "file" );
    CHECK( nil  == p1.Directory() );
    CHECK( file == p1.Filename() );
    CHECK( file == p1.Stem() );
    CHECK( nil  == p1.Extension() );

    const Path p2( "file.ext" );
    CHECK( nil  == p2.Directory() );
    CHECK( fext == p2.Filename() );
    CHECK( file == p2.Stem() );
    CHECK( ext  == p2.Extension() );

    const Path p3( "file.note.ext" );
    CHECK( nil  == p3.Directory() );
    CHECK( p3   == p3.Filename() );
    CHECK( Path( "file.note" ) == p3.Stem() );
    CHECK( ext  == p3.Extension() );

    const Path p4( "dir/file" );
    CHECK( dir  == p4.Directory() );
    CHECK( file == p4.Filename() );
    CHECK( file == p4.Stem() );
    CHECK( nil  == p4.Extension() );

    const Path p5( "dir/file.ext" );
    CHECK( dir  == p5.Directory() );
    CHECK( fext == p5.Filename() );
    CHECK( file == p5.Stem() );
    CHECK( ext  == p5.Extension() );

    const Path p6( "dir.sub/file" );
    CHECK( dsub == p6.Directory() );
    CHECK( file == p6.Filename() );
    CHECK( file == p6.Stem() );
    CHECK( nil  == p6.Extension() );

    const Path p7( "dir.sub/file.ext" );
    CHECK( dsub == p7.Directory() );
    CHECK( fext == p7.Filename() );
    CHECK( file == p7.Stem() );
    CHECK( ext  == p7.Extension() );
    

    /// Has Extensions ///

    CHECK( false == p0.HasExtension() );
    CHECK( false == p1.HasExtension() );
    CHECK( true  == p2.HasExtension() );
    CHECK( true  == p3.HasExtension() );
    CHECK( false == p4.HasExtension() );
    CHECK( true  == p5.HasExtension() );
    CHECK( false == p6.HasExtension() );
    CHECK( true  == p7.HasExtension() );


    /// Combination - How to get the direct parent directory ///

    const Path p8( "root/dir1/dir2/file" );

    CHECK( Path( "dir2" ) == p8.Directory().Stem() );
    CHECK( Path( "dir1" ) == p8.Directory().Directory().Stem() );
}


TEST( PathCombine )
{
    const Path p1( "dir" );
    const Path p2( "file" );
    const Path answer( "dir/file" );

    CHECK( answer == p1 / p2 );

    Path p3 = p1;
    p3.Combine( p2 );

    CHECK( answer == p3 );


    /// boost::path would automatically merge the '/' ///

    const Path p4( "dir/" );
    const Path p5( "/file" );

    CHECK( answer == p4 / p2 );  //  dir//file ?
    CHECK( answer == p1 / p5 );  //  dir//file ?
    CHECK( answer == p4 / p5 );  //  dir///file ?
}


TEST( PathAppendExtension )
{
    const Path p1( "file" );
    const Path p2( "file.ini" );

    Path p11 = p1;
    p11.AppendExtension( "bak" );
    CHECK( Path( "file.bak" ) == p11 );

    Path p12 = p1;
    p12.AppendExtension( ".bak" );
    CHECK( Path( "file.bak" ) == p12 );

    Path p21 = p2;
    p21.AppendExtension( "bak" );
    CHECK( Path( "file.ini.bak" ) == p21 );

    Path p22 = p2;
    p22.AppendExtension( ".bak" );
    CHECK( Path( "file.ini.bak" ) == p22 );

    
    /// Opertors ///

    CHECK( Path( "file.bak" ) == p1 % "bak" );
    CHECK( Path( "file.bak" ) == p1 % ".bak" );
    CHECK( Path( "file.ini.bak" ) == p2 % "bak" );
    CHECK( Path( "file.ini.bak" ) == p2 % ".bak" );
}


TEST( PathInsertStemSuffix )
{
    Path p1( "file" );
    p1.InsertStemSuffix( "_en" );
    CHECK( Path( "file_en" ) == p1 );

    Path p2( "file.ini" );
    p2.InsertStemSuffix( "_en" );
    CHECK( Path( "file_en.ini" ) == p2 );

    Path p3( "file.ini.bak" );
    p3.InsertStemSuffix( "_en" );
    CHECK( Path( "file.ini_en.bak" ) == p3 );
}


} // SUITE Path

} // namespace Caramel
