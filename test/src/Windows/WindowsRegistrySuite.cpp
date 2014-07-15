// Caramel C++ Library Test - Windows - Windows Registry Suite

#include "CaramelTestPch.h"

#include <Caramel/Windows/Registry.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( WindowsRegistrySuite )
{

TEST( WindowsRegistryTest )
{
    // Try to read the Windows machine GUID, which should be set when the Windows installed.

    auto registry = Windows::Registry::LocalMachine();

    Utf8String machineGuid;
    CHECK( true == registry.GetStringValue(
        Utf8String( "SOFTWARE\\Microsoft\\Cryptography" ),
        Utf8String( "MachineGuid" ),
        machineGuid
    ));
}

} // SUITE WindowsRegistrySuite

} // namespace Caramel
