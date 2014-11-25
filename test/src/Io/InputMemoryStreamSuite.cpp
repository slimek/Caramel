// Caramel C++ Library Test - I/O - Input Memory Stream Suite

#include "CaramelTestPch.h"

#include <Caramel/Io/InputMemoryStream.h>
#include <Caramel/Io/TextStreamReader.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( InputMemoryStreamSuite )
{

TEST( InputMemoryStreamSeekTellTest )
{
    Char buffer[128] = { 0 };
    InputMemoryStream stream( buffer );

    CHECK( 128 == stream.Length() );
    CHECK( 0 == stream.Tell() );

    stream.Seek( 12 );
    CHECK( 12 == stream.Tell() );

    stream.Seek( -7 );
    CHECK( 5 == stream.Tell() );

    // Seek under zero
    stream.Seek( -31 );
    CHECK( 0 == stream.Tell() );

    // Seek over length
    stream.Seek( 192 );
    CHECK( 128 == stream.Tell() );
    CHECK( true == stream.IsEof() );
}


TEST( InputMemoryStreamTextReaderTest )
{
    Char alice[] = "Alice\nis a\nDollmaster";
    InputMemoryStream stream( alice );
    TextStreamReader reader( stream );

    std::string line;

    CHECK( true == reader.ReadLine( line ));
    CHECK( "Alice" == line );

    CHECK( true == reader.ReadLine( line ));
    CHECK( "is a" == line );

    CHECK( true == reader.ReadLine( line ));
    CHECK( "Dollmaster" == line );

    CHECK( false == reader.ReadLine( line ));
}


} // SUITE InputMemoryStreamSuite

} // namespace Caramel
