// Caramel C++ Library Test - Document - INI Document Test

#include "CaramelTestPch.h"

#include <Caramel/Document/IniDocument.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( IniDocumentSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// INI Document Test
//

TEST( IniDocumentTest )
{
}

TEST( IniDocumentBoolTest )
{
    IniDocument iniDoc( "Document\\test1.ini" );

    auto values = iniDoc.GetSection( "Values" );

    CHECK( true == values.GetBoolValue( "BoolTrue1" ));
    CHECK( true == values.GetBoolValue( "BoolTrue2" ));
    CHECK( true == values.GetBoolValue( "BoolTrue3" ));
    CHECK( true == values.GetBoolValue( "BoolTrue4" ));
    CHECK( true == values.GetBoolValue( "BoolTrue5" ));
    CHECK( false == values.GetBoolValue( "BoolFalse1" ));
    CHECK( false == values.GetBoolValue( "BoolFalse2" ));
    CHECK( false == values.GetBoolValue( "BoolFalse3" ));
    CHECK( false == values.GetBoolValue( "BoolFalse4" ));

    CHECK_THROW( values.GetBoolValue( "BoolBad" ), Caramel::Exception );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE IniDocumentSuite

} // namespace Caramel
