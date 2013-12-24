// Caramel C++ Library Test - File System - Path Test

#include "CaramelTestPch.h"

#include <Caramel/FileSystem/Path.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( PathSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Path Test
//

TEST( PathTest )
{
    const Path p0( "" );
    const Path p1( "file" );
    const Path p2( "file.ext" );
    const Path p3( "file.note.ext" );
    const Path p4( "dir/file" );
    const Path p5( "dir/file.ext" );
    const Path p6( "dir.sub/file" );
    const Path p7( "dir.sub/file.ext" );

    
    /// Splits ///

    const Path nil( "" );
    const Path file( "file" );
    const Path ext( ".ext" );
    const Path dir( "dir" );
    const Path dsub( "dir.sub" );

    CHECK( nil  == p0.Directory() );
    CHECK( nil  == p0.Stem() );
    CHECK( nil  == p0.Extension() );
    CHECK( nil  == p1.Directory() );
    CHECK( file == p1.Stem() );
    CHECK( nil  == p1.Extension() );
    CHECK( nil  == p2.Directory() );
    CHECK( file == p2.Stem() );
    CHECK( ext  == p2.Extension() );
    CHECK( nil  == p3.Directory() );
    CHECK( Path( "file.note" ) == p3.Stem() );
    CHECK( ext  == p3.Extension() );
    CHECK( dir  == p4.Directory() );
    CHECK( file == p4.Stem() );
    CHECK( nil  == p4.Extension() );
    CHECK( dir  == p5.Directory() );
    CHECK( file == p5.Stem() );
    CHECK( ext  == p5.Extension() );
    CHECK( dsub == p6.Directory() );
    CHECK( file == p6.Stem() );
    CHECK( nil  == p6.Extension() );
    CHECK( dsub == p7.Directory() );
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
}


TEST( PathCombineTest )
{
    const Path p1( "dir" );
    const Path p2( "file" );

    CHECK( Path( "dir/file" ) == p1 / p2 );

    Path p3 = p1;
    p3.Combine( p2 );

    CHECK( Path( "dir/file" ) == p3 );
}


TEST( PathAppendExtensionTest )
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
}


TEST( PathInsertStemSuffixTest )
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


///////////////////////////////////////////////////////////////////////////////

} // SUITE PathSuite

} // namespace Caramel
