// Caramel C++ Library Test - Lexical - Lexical Version Suite

#include "CaramelTestPch.h"

#include <Caramel/Lexical/Version.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

using Lexical::Version;

SUITE( LexicalVersionSuite )
{

TEST( LexicalVersionTrivialTest )
{
    Version v0;

    CHECK( 0 == v0.Major() );
    CHECK( 0 == v0.Minor() );
    CHECK( 0 == v0.Build() );
    CHECK( 0 == v0.Revision() );
    CHECK( "0.0.0.0" == v0.ToString() );

    Version v1( 1 );

    CHECK( 1 == v1.Major() );
    CHECK( 0 == v1.Minor() );
    CHECK( 0 == v1.Build() );
    CHECK( 0 == v1.Revision() );
    CHECK( "1.0.0.0" == v1.ToString() );

    Version v2( 1, 2 );

    CHECK( 1 == v2.Major() );
    CHECK( 2 == v2.Minor() );
    CHECK( 0 == v2.Build() );
    CHECK( 0 == v2.Revision() );
    CHECK( "1.2.0.0" == v2.ToString() );

    Version v3( 1, 2, 3 );

    CHECK( 1 == v3.Major() );
    CHECK( 2 == v3.Minor() );
    CHECK( 3 == v3.Build() );
    CHECK( 0 == v3.Revision() );
    CHECK( "1.2.3.0" == v3.ToString() );

    Version v4( 1, 2, 3, 4 );

    CHECK( 1 == v4.Major() );
    CHECK( 2 == v4.Minor() );
    CHECK( 3 == v4.Build() );
    CHECK( 4 == v4.Revision() );
    CHECK( "1.2.3.4" == v4.ToString() );

    /// Comparison ///

    CHECK( v0 < v1 );
    CHECK( v1 < v2 );
    CHECK( v2 < v3 );
    CHECK( v3 < v4 );
    CHECK( v0 != v1 );

    Version vz( 0, 0, 0, 0 );

    CHECK( v0 == vz );

    /// Partial components to String ///

    CHECK( ""        == v4.ToString( 0 ));
    CHECK( "1"       == v4.ToString( 1 ));
    CHECK( "1.2"     == v4.ToString( 2 ));
    CHECK( "1.2.3"   == v4.ToString( 3 ));
    CHECK( "1.2.3.4" == v4.ToString( 4 ));
    CHECK_THROW( v4.ToString( 5 ), Caramel::Exception );
}


TEST( LexicalVersionParseTest )
{
    Version ver;

    CHECK( false == ver.TryParse( "" ));
    
    CHECK( true == ver.TryParse( "1" ));
    CHECK( "1.0.0.0" == ver.ToString() );

    CHECK( true == ver.TryParse( "2.34.567.890" ));
    CHECK( "2.34.567.890" == ver.ToString() );

    // Padding 0s are omitted
    CHECK( true == ver.TryParse( "1.08.0024" ));
    CHECK( "1.8.24.0" == ver.ToString() );

    // Too many components
    CHECK( false == ver.TryParse( "3.4.5.18.96" ));

    // Not a version string
    CHECK( false == ver.TryParse( "The Ultimate Question" ));

    // Non-number is not allowed
    CHECK( false == ver.TryParse( "9.20b" ));


    /// From String ///

    auto v1 = Version::FromString( "3.1.4" );
    CHECK( "3.1.4.0" == v1.ToString() );

    auto v2 = Version::FromString( "3.01.4.0" );
    CHECK( v1 == v2 );

    CHECK_THROW( Version::FromString( "not a version" ), Caramel::Exception );
}


} // SUITE LexicalVersionSuite

} // namespace Caramel
