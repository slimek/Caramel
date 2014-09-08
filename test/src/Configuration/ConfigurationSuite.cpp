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


TEST( ConfigValuesTest )
{
    CHECK( false == cv_flagTrue );

    IniDocument ini( "..\\src\\Configuration\\values.ini" );

    ConfigRoot root;
    root.Load( MakeConfigSectionMap( ini ));

    CHECK( true == cv_flagTrue );
}

} // SUITE ConfigurationSuite

} // namespace Caramel
