// Caramel C++ Library Test - String - Algorithm Test

#include "CaramelTestPch.h"

#include <Caramel/String/Algorithm.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( StringAlgorithmSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// String Algorithm Test
//

TEST( StringPredicateTest )
{
    /// String : Char ///

    CHECK( true  == Contains( "Alice", 'A' ));
    CHECK( true  == Contains( "Alice", 'i' ));
    CHECK( true  == Contains( "Alice", 'e' ));
    CHECK( false == Contains( "Alice", 'f' ));
    CHECK( false == Contains( "",      'a' ));

    CHECK( true  == EndsWith( "Alice", 'e' ));
    CHECK( false == EndsWith( "Alice", 'c' ));
    CHECK( false == EndsWith( "",      'f' ));


    //
    // Case Insensitive
    //

    /// String : String ///

    CHECK( true  == CainStartsWith( "Alice", "Ali" ));
    CHECK( true  == CainStartsWith( "aLIce", "ali" ));
    CHECK( false == CainStartsWith( "Alice", "bad" ));
    CHECK( false == CainStartsWith( "",      "ali" ));

    CHECK( true  == CainEquals( "Alice", "Alice" ));
    CHECK( true  == CainEquals( "ALICE", "alice" ));
    CHECK( false == CainEquals( "Alice", "alic" ));
    CHECK( false == CainEquals( "Alice", "alicf" ));
    CHECK( false == CainEquals( "Alice", "alice1" ));
    CHECK( false == CainEquals( "",      "alice" ));
    CHECK( false == CainEquals( "Alice", "" ));
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE StringAlgorithm

} // namespace Caramel
