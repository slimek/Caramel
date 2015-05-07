// Caramel C++ Library Test - Lexical - Lexical Floating List Suite

#include "CaramelTestPch.h"

#include <Caramel/Lexical/FloatingList.h>


namespace Caramel
{

SUITE( LexicalFloatingList )
{

TEST( LexicalFloatingList )
{
    Lexical::FloatingList< Float > flist;

    CHECK( 0 == flist.Size() );

    CHECK( true == flist.TryParse( "320 12.5, 75", ", " ));
    
    CHECK( 3     == flist.Size() );
    CHECK( 320   == flist[0] );
    CHECK( 12.5f == flist[1] );
    CHECK( 75    == flist[2] );

    CHECK( true == flist.TryParse( "42", ", " ));
    
    CHECK( 1  == flist.Size() );
    CHECK( 42 == flist[0] );

    CHECK( false == flist.TryParse( "Alice Marisa", ", " ));

    // After a failed parsing, the list should be cleared.
    CHECK( 0 == flist.Size() );
}


} // SUITE LexicalFloatingList

} // namespace Caramel
