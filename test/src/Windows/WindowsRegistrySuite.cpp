// Caramel C++ Library Test - Windows - Windows Registry Suite

#include "CaramelTestPch.h"

#include <Caramel/Windows/Registry.h>


namespace Caramel
{

SUITE( WindowsRegistrySuite )
{

TEST( WindowsRegistryTest )
{
    // Try to read the Windows machine GUID, which should be set when the Windows installed.

    auto registry = Windows::Registry::LocalMachine();

    Utf8String u8MachineGuid;
    CHECK( true == registry.GetStringValue(
        Utf8String( "SOFTWARE\\Microsoft\\Cryptography" ),
        Utf8String( "MachineGuid" ),
        u8MachineGuid
    ));

    std::string machineGuid;
    CHECK( true == registry.GetStringValue(
        "SOFTWARE\\Microsoft\\Cryptography",
        "MachineGuid",
        machineGuid
    ));

    std::string exist;
    CHECK( false == registry.GetStringValue( "THIS\\DoesNot", "Exist", exist ));
}

} // SUITE WindowsRegistrySuite

} // namespace Caramel
