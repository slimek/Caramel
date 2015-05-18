// Caramel C++ Library Test - Windows - Wide String Suite

#include "CaramelTestPch.h"

#include <Caramel/Windows/WideString.h>
#include <iostream>


namespace Caramel
{

SUITE( WideString )
{

TEST( WideStringUtf8 )
{
    const std::string cat = "\xE8\xB2\x93";  // Chinese "cat"
    const auto wcat = Windows::WideString::FromUtf8( cat );

    CHECK( L"¿ß" == wcat.ToString() );

    const Windows::WideString wdog( L"ª¯" );

    CHECK( "\xE7\x8B\x97" == wdog.ToUtf8() );  // Chinese "dog"
}


} // SUITE WideString

} // namespace Caramel

