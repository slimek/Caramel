// Caramel C++ Library Test - I/O - Input Memory Stream Suite

#include "CaramelTestPch.h"

#include <Caramel/Io/InputMemoryStream.h>
#include <Caramel/Io/TextStreamReader.h>


namespace Caramel
{

SUITE( InputMemoryStream )
{

TEST( InputMemoryStreamSeekTell )
{
    Byte buffer[128] = { 0 };
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

    // Back to the beginning
    stream.Rewind();
    CHECK( 0 == stream.Tell() );
    CHECK( false == stream.IsEof() );
}


TEST( InputMemoryStreamTextReader )
{
    Char alice[] = "Alice\nis a\nDollmaster";
    InputMemoryStream stream( alice );
    TextStreamReader reader( stream, TEXT_ENCODING_UTF8 );

    std::string line;

    CHECK( true == reader.ReadLine( line ));
    CHECK( "Alice" == line );

    CHECK( true == reader.ReadLine( line ));
    CHECK( "is a" == line );

    CHECK( true == reader.ReadLine( line ));
    CHECK( "Dollmaster" == line );

    CHECK( false == reader.ReadLine( line ));


    #if defined( CARAMEL_SYSTEM_IS_WINDOWS )

    // The default encoding on Windows is ACP
    // i.e. If you write:
    //
    //   TextStreamReader reader( stream );
    //
    // The reader would assume to use TEXT_ENCODING_DEFAULT, which is ACP on Windows.

    stream.Rewind();
    TextStreamReader acpReader( stream, TEXT_ENCODING_WINDOWS_ACP );

    CHECK( true == acpReader.ReadLine( line ));
    CHECK( "Alice" == line );

    CHECK( true == acpReader.ReadLine( line ));
    CHECK( "is a" == line );

    CHECK( true == acpReader.ReadLine( line ));
    CHECK( "Dollmaster" == line );

    CHECK( false == acpReader.ReadLine( line ));

    #endif
}


} // SUITE InputMemoryStream

} // namespace Caramel
