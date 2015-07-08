// Caramel C++ Library Test - I/O - Output Memory Stream Suite

#include "CaramelTestPch.h"

#include <Caramel/Io/OutputMemoryStream.h>
#include <Caramel/Io/TextStreamWriter.h>


namespace Caramel
{

SUITE( OutputMemoryStream )
{

TEST( OutputMemoryStream )
{
    Char buffer[12] = { 0 };
    OutputMemoryStream stream( &buffer[0], 12 );

    CHECK( 12 == stream.Length() );
    CHECK( 0 == stream.Position() );

    TextStreamWriter writer( stream );
    writer.Write( "Alice" );

    // Remarks: TextStreamWriter would write a BOM at the beginning...
    CHECK( 8 == stream.Position() );

    std::string alice( &buffer[3] );
    CHECK( "Alice" == alice );

    // Write to out of the stream.
    CHECK_THROW( writer.Write( "Many many dolls..." ), Caramel::Exception );
}

} // SUITE OutputMemoryStream

} // namespace Caramel
