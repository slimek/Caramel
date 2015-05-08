// Caramel C++ Library Test - String - Algorithm Suite

#include "CaramelTestPch.h"

#include "Utils/StdVectorUtils.h"
#include <Caramel/String/Algorithm.h>


namespace Caramel
{

SUITE( StringAlgorithm )
{

TEST( StringPredicate )
{
    /// String : Char ///

    CHECK( true  == Contains( "Alice", 'A' ));
    CHECK( true  == Contains( "Alice", 'i' ));
    CHECK( true  == Contains( "Alice", 'e' ));
    CHECK( false == Contains( "Alice", 'f' ));
    CHECK( false == Contains( "",      'a' ));

    CHECK( true  == StartsWith( "Alice", 'A' ));
    CHECK( false == StartsWith( "Alice", 'a' ));
    CHECK( false == StartsWith( "Alice", 'l' ));
    CHECK( false == StartsWith( "",      'f' ));

    CHECK( true  == EndsWith( "Alice", 'e' ));
    CHECK( false == EndsWith( "Alice", 'E' ));
    CHECK( false == EndsWith( "Alice", 'c' ));
    CHECK( false == EndsWith( "",      'f' ));

    /// String : String ///

    CHECK( true  == StartsWith( "Alice", "A" ));
    CHECK( true  == StartsWith( "Alice", "Ali" ));
    CHECK( true  == StartsWith( "Alice", "Alice" ));
    CHECK( true  == StartsWith( "Alice", "" ));
    CHECK( false == StartsWith( "Alice", "ali" ));
    CHECK( false == StartsWith( "Alice", "bad" ));
    CHECK( false == StartsWith( "Alice", "Alice3" ));
    CHECK( false == StartsWith( "",      "Ali" ));

    CHECK( true  == EndsWith( "Alice", "e" ));
    CHECK( true  == EndsWith( "Alice", "ice" ));
    CHECK( true  == EndsWith( "Alice", "Alice" ));
    CHECK( true  == EndsWith( "Alice", "" ));
    CHECK( false == EndsWith( "Alice", "E" ));
    CHECK( false == EndsWith( "Alice", "bad" ));
    CHECK( false == EndsWith( "Alice", "Alice3" ));
    CHECK( false == EndsWith( "",      "ice" ));


    //
    // Case Insensitive
    //

    /// String : c ///

    CHECK( true  == CainStartsWith( "Alice", 'A' ));
    CHECK( true  == CainStartsWith( "Alice", 'a' ));
    CHECK( false == CainStartsWith( "Alice", 'l' ));
    CHECK( false == CainStartsWith( "",      'a' ));

    CHECK( true  == CainEndsWith( "Alice", 'E' ));
    CHECK( true  == CainEndsWith( "Alice", 'e' ));
    CHECK( false == CainEndsWith( "Alice", 'c' ));
    CHECK( false == CainEndsWith( "",      'e' ));


    /// String : String ///

    CHECK( true  == CainStartsWith( "Alice", "Ali" ));
    CHECK( true  == CainStartsWith( "aLIce", "ali" ));
    CHECK( true  == CainStartsWith( "Alice", "" ));
    CHECK( false == CainStartsWith( "Alice", "bad" ));
    CHECK( false == CainStartsWith( "",      "ali" ));

    CHECK( true  == CainEndsWith( "Alice", "Ice" ));
    CHECK( true  == CainEndsWith( "Alice", "ICE" ));
    CHECK( true  == CainEndsWith( "Alice", "" ));
    CHECK( false == CainEndsWith( "Alice", "bad" ));
    CHECK( false == CainEndsWith( "",      "ice" ));

    CHECK( true  == CainEquals( "Alice", "Alice" ));
    CHECK( true  == CainEquals( "ALICE", "alice" ));
    CHECK( false == CainEquals( "Alice", "alic" ));
    CHECK( false == CainEquals( "Alice", "alicf" ));
    CHECK( false == CainEquals( "Alice", "alice1" ));
    CHECK( false == CainEquals( "",      "alice" ));
    CHECK( false == CainEquals( "Alice", "" ));
}


TEST( StringExtractor )
{
    /// String : Char ///

    CHECK( "Al"    == BeforeFirst( "Alice", 'i' ));
    CHECK( ""      == BeforeFirst( "Alice", 'A' ));
    CHECK( "Alic"  == BeforeFirst( "Alice", 'e' ));
    CHECK( "Alice" == BeforeFirst( "Alice", 'f' ));  // Returns whole string if not found.
    CHECK( ""      == BeforeFirst( "",      'f' ));

    CHECK( "ce"    == AfterFirst( "Alice", 'i' ));
    CHECK( "lice"  == AfterFirst( "Alice", 'A' ));
    CHECK( ""      == AfterFirst( "Alice", 'e' ));
    CHECK( ""      == AfterFirst( "Alice", 'f' ));  // Returns empty string if not found.
    CHECK( ""      == AfterFirst( "",      'f' ));
}


TEST( StringJoin )
{
    CHECK( "reimu,marisa,alice" == Join( std::vector< std::string >{ "reimu", "marisa", "alice" }, "," ));
    CHECK( "" == Join( std::vector< std::string >(), "," ));
}


TEST( StringTrim )
{
    std::string marisa = "  Marisa  ";

    Trim( marisa );
    CHECK( "Marisa" == marisa );

    // Trim may do nothing
    Trim( marisa );
    CHECK( "Marisa" == marisa );


    /// Trim the Copy ///

    CHECK( "Alice" == TrimCopy( "Alice" ));
    CHECK( "Alice" == TrimCopy( "  Alice" ));
    CHECK( "Alice" == TrimCopy( "Alice  " ));
    CHECK( "Alice" == TrimCopy( "\tAlice\n" ));
}


} // SUITE StringAlgorithm

} // namespace Caramel
