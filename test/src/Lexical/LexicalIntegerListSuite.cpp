// Caramel C++ Library Test - Lexical - Lexical Integer List Suite

#include "CaramelTestPch.h"

#include <Caramel/Lexical/IntegerList.h>


namespace Caramel
{

SUITE( LexicalIntegerList )
{

TEST( LexicalIntegerList )
{
    Lexical::IntegerList< Int > ilist;
    
    CHECK( 0 == ilist.Size() );
    
    CHECK( true == ilist.TryParse( "51 235, 60,78", ", " ));
    
    CHECK( 4   == ilist.Size() );
    CHECK( 51  == ilist[0] );
    CHECK( 235 == ilist[1] );
    CHECK( 60  == ilist[2] );
    CHECK( 78  == ilist[3] );

    // Range-based for loop

    Int answers[] = { 51, 235, 60, 78 };
    Int i = 0;
    for ( Int v : ilist )
    {
        CHECK( v == answers[i++] );
    }


    // Only one element

    CHECK( true == ilist.TryParse( "42", ", " ));

    CHECK( 1  == ilist.Size() );
    CHECK( 42 == ilist[0] );


    // Parse failed

    CHECK( false == ilist.TryParse( "Reimu Yukari", ", " ));

    // After a failed parsing, the list should be cleared.
    CHECK( 0 == ilist.Size() );
}


TEST( LexicalIntegerListOutOfRange )
{
    // If any of the value is out of range, the whole list is failed.

    Lexical::IntegerList< Int16 > ilist;

    CHECK( false == ilist.TryParse( "42 6107 65000 -51", " " ));  // the 3rd value is out of range.
    CHECK( 0 == ilist.Size() );
}


} // SUITE LexicalIntegerList

} // namespace Caramel
