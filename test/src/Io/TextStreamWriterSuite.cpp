// Caramel C++ Library Test - I/O - Text Stream Writer Suite

#include "CaramelTestPch.h"

#include "Utils/WritablePath.h"
#include <Caramel/Io/InputFileStream.h>
#include <Caramel/Io/OutputFileStream.h>
#include <Caramel/Io/TextStreamReader.h>
#include <Caramel/Io/TextStreamWriter.h>


namespace Caramel
{

SUITE( TextStreamWriter )
{

TEST( TextStreamWriterAscii )
{
    const Path tempPath = WritablePath() / "temp.txt";

    OutputFileStream ofile( tempPath );
    TextStreamWriter writer( ofile );

    const std::string text = "Alice is a dollmaster";
    writer.Write( text );

    ofile.Close();

    InputFileStream ifile( tempPath );
    TextStreamReader reader( ifile );

    std::string line;

    CHECK( true == reader.ReadLine( line ));
    CHECK( text == line );
}


TEST( TextStreamWriterChinese )
{
    #if defined ( CARAMEL_SYSTEM_IS_WINDOWS )
    const std::string text = Utf8String( L"愛莉絲是人形使" ).ToString();
    #else
    const std::string text = "愛莉絲是人形使";
    #endif

    const Path tempPath = WritablePath() / "temp.txt";

    OutputFileStream ofile( tempPath );
    TextStreamWriter writer( ofile );

    writer.Write( text );

    ofile.Close();

    InputFileStream ifile( tempPath );
    TextStreamReader reader( ifile );

    std::string line;

    CHECK( true == reader.ReadLine( line ));
    CHECK( text == line );
}


} // SUITE TextStreamWriter

} // namespace Caramel
