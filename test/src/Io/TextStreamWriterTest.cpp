﻿// Caramel C++ Library Test - I/O - Text Stream Writer Test

#include "CaramelTestPch.h"

#include <Caramel/Io/InputFileStream.h>
#include <Caramel/Io/OutputFileStream.h>
#include <Caramel/Io/TextStreamReader.h>
#include <Caramel/Io/TextStreamWriter.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( TextStreamWriterSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Text Stream Writer Test
//

TEST( TextStreamWriterAsciiTest )
{
    const std::string text = "Alice is a dollmaster";

    OutputFileStream ofile( "temp.txt" );
    TextStreamWriter writer( ofile );

    writer.Write( text );

    ofile.Close();

    InputFileStream ifile( "temp.txt" );
    TextStreamReader reader( ifile );

    std::string line;

    CHECK( true == reader.ReadLine( line ));
    CHECK( text == line );
}


TEST( TextStreamWriterChineseTest )
{
    #if defined ( CARAMEL_SYSTEM_IS_WINDOWS )
    const std::string text = Utf8String( L"愛莉絲是人形使" ).ToString();
    #else
    const std::string text = "愛莉絲是人形使";
    #endif

    OutputFileStream ofile( "temp.txt" );
    TextStreamWriter writer( ofile );

    writer.Write( text );

    ofile.Close();

    InputFileStream ifile( "temp.txt" );
    TextStreamReader reader( ifile );

    std::string line;

    CHECK( true == reader.ReadLine( line ));
    CHECK( text == line );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE TextStreamWriterSuite

} // namespace Caramel