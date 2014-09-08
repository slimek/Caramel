// Caramel C++ Library Test - Configuration - Configuration Suite

#include "CaramelTestPch.h"

#include <Caramel/Configuration/ConfigFromIni.h>
#include <Caramel/Configuration/ConfigRoot.h>
#include <Caramel/Configuration/ConfigValues.h>
#include <Caramel/Document/IniDocument.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( ConfigurationSuite )
{

static ConfigSection cs_t( "Values" );

static ConfigBool cv_flagTrue( cs_t, "FlagTrue" );
static ConfigBool cv_flagFalse( cs_t, "FlagFalse", true );

static ConfigInt cv_int0( cs_t, "Int0" );
static ConfigInt cv_int42( cs_t, "Int42", -1 );

static ConfigString cv_name( cs_t, "Name" );
static ConfigString cv_role( cs_t, "Role", "Mage" );


TEST( ConfigValuesTest )
{
    /// Default values ///

    CHECK( false  == cv_flagTrue );
    CHECK( true   == cv_flagFalse );
    CHECK( 0      == cv_int0 );
    CHECK( -1     == cv_int42 );
    CHECK( ""     == cv_name );
    CHECK( "Mage" == cv_role );


    /// Load the INI ///

    IniDocument ini( "..\\src\\Configuration\\values.ini" );

    ConfigRoot root;
    root.Load( MakeConfigSectionMap( ini ));

    
    /// Booleans ///

    CHECK( true  == cv_flagTrue );
    CHECK( false == cv_flagFalse );

    /// Integers ///

    CHECK( 0  == cv_int0 );
    CHECK( 42 == cv_int42 );

    /// String - Testing Comparable ///

    CHECK( "Alice" == cv_name );
    CHECK( "Thief" != cv_role );
}


} // SUITE ConfigurationSuite

} // namespace Caramel
