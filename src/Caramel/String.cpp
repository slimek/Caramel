// Caramel C++ Library - String Facility - Implementation

#include <Caramel/CaramelPch.h>

#include <Caramel/String/Sprintf.h>
#include <Caramel/String/Utf8String.h>


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
    : Inherited( u8Text )
{
    if ( !this->TryParse( u8Text ))
    {
        CARAMEL_THROW( "Input text is not UTF-8 encoded" );
    }
}


//
// Validation
//

inline static Int Utf8String_CalculateNumTrails( Byte lead )
{
    if ( 0 == ( lead & 0x80 ))  //  0dddddddd
    {
        return 0;
    }
    else if ( 0xC0 == ( lead & 0xE0 ))  // 110ddddd
    {
        return 1;
    }
    else if ( 0xE0 == ( lead & 0xF0 ))  // 1110dddd
    {
        return 2;
    }
    else if ( 0xF0 == ( lead & 0xF8 ))  // 11110ddd
    {
        return 3;
    }
    else
        return -1;
}


inline static Bool Utf8String_IsTrail( Byte b )
{
    return ( 0x80 == ( b & 0xC0 ));  // 10dddddd
}


Bool Utf8String::TryParse( const std::string& u8Text )
{
    Uint pos = 0;

    while ( u8Text.length() > pos )
    {
        Int num = Utf8String_CalculateNumTrails( static_cast< Byte >( u8Text[ pos ++ ] ));
        
        // not valid leading character
        if ( 0 > num ) { return false; }
        
        // not enough length
        if ( u8Text.length() < pos + num ) { return false; }

        while ( 0 < num -- )
        {
            // not trailing character
            if ( ! Utf8String_IsTrail( static_cast< Byte >( u8Text[ pos ++ ] ))) { return false; }
        }
    }

    this->assign( u8Text );
    return true;
}


Bool Utf8String::TryParse( const Byte* data, Uint length )
{
    CARAMEL_NOT_IMPLEMENTED();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
