// Caramel C++ Library Test - Configuration - Configuration Suite

#include "CaramelTestPch.h"

#include "Utils/AssetReader.h"
#include <Caramel/Configuration/ConfigFromIni.h>
#include <Caramel/Configuration/ConfigRoot.h>
#include <Caramel/Configuration/ConfigValues.h>
#include <Caramel/Document/IniDocument.h>


namespace Caramel
{

SUITE( ConfigurationSuite )
{

static ConfigSection cs_vs( "Values" );

static ConfigBool cv_flagTrue( cs_vs, "FlagTrue" );
static ConfigBool cv_flagFalse( cs_vs, "FlagFalse", true );

static ConfigInt cv_int0( cs_vs, "Int0" );
static ConfigInt cv_int42( cs_vs, "Int42", -1 );

static ConfigString cv_name( cs_vs, "Name" );
static ConfigString cv_role( cs_vs, "Role", "Mage" );


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

    IniDocument ini;
    ini.LoadFromText( AssetReader( "values.ini" ));

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


static ConfigSection cs_p( "Items", "Potion" );

static ConfigInt cv_id( cs_p, "Id" );
static ConfigString cv_desc( cs_p, "Desc" );

TEST( ConfigRootTest )
{
    /// Load the INI into a named Root ///

    IniDocument ini;
    ini.LoadFromText( AssetReader( "items.ini" ));

    ConfigRoot root( "Items" );
    root.Load( MakeConfigSectionMap( ini ));

    CHECK( 15     == cv_id );
    CHECK( "Heal" == cv_desc );
}


} // SUITE ConfigurationSuite

} // namespace Caramel
