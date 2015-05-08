// Caramel C++ Library Test - String - UTF-8 String Suite

#include "CaramelTestPch.h"

#include <Caramel/String/Utf8String.h>


namespace Caramel
{

SUITE( Utf8String )
{

TEST( Utf8Validate )
{
    CHECK( true == Utf8String::Validate( "" ));
    CHECK( true == Utf8String::Validate( "ABCabc" ));
    CHECK( true == Utf8String::Validate( "\xD7\x90" ));     // Hebrew Alpha
    CHECK( true == Utf8String::Validate( "\xE8\xB2\x93" )); // Chinese "cat"

    // Impossible byte in UTF-8
    CHECK( false == Utf8String::Validate( "\xC0" ));

    // Incomplete Hebrew Alpha 
    CHECK( false == Utf8String::Validate( "\xD7" ));        

    // Incomplete Chinese "cat"
    CHECK( false == Utf8String::Validate( "\xE8\xB2" ));
    CHECK( false == Utf8String::Validate( "\xB2\x93" ));
}


TEST( Utf8StringMove )
{
    Utf8String source( "Alice" );
    std::string target;

    target = source.MoveString();

    CHECK( "Alice" == target );
    CHECK( "" == source.ToString() );
}


} // SUITE Utf8String

} // namespace Caramel
