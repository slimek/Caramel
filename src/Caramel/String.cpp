// Caramel C++ Library - String Facility - Implementation

#include <Caramel/CaramelPch.h>

#include <Caramel/String/Sprintf.h>
#include <Caramel/String/Utf8String.h>
#include <Caramel/String/Utf8StringImpl.h>


namespace Caramel
{

//
// Contents
//
// 1. Sprintf
// 2. Utf8String
//

///////////////////////////////////////////////////////////////////////////////
//
// Sprintf
//

///////////////////////////////////////////////////////////////////////////////
//
// UTF-8 String
//

Utf8String::Utf8String( const std::string& u8Text )
    : CodedString( TEXT_ENCODING_UTF8 )
{
    if ( !this->TryParse( u8Text ))
    {
        CARAMEL_THROW( "Input text is not UTF-8 encoded" );
    }
}


Bool Utf8String::TryParse( const std::string& u8Text )
{
    // TODO: check if 'u8Text' is UTF-8 encoded.

    this->assign( u8Text );
    return true;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
