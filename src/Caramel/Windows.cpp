// Caramel C++ Library - Windows Facility - Implementation

#include <Caramel/CaramelPch.h>


#if defined( CARAMEL_SYSTEM_IS_WINDOWS )

#include <Caramel/Windows/WideString.h>
#include <windows.h>


namespace Caramel
{

namespace Windows
{

//
// Contents
//
// 1. WideString
//

///////////////////////////////////////////////////////////////////////////////
//
// Wide String
//

Bool WideString::TryParse( const std::string& input, TextEncoding encoding )
{
    if ( input.empty() )
    {
        this->assign( std::wstring() );
        return true;
    }

    if ( TEXT_ENCODING_UTF16_LE == encoding )
    {
        const Wchar* winput = reinterpret_cast< const Wchar* >( input.c_str() );
        this->assign( winput, winput + input.length() / 2  );
        return true;
    }

    if ( TEXT_ENCODING_WINDOWS_ACP == encoding )
    {
        encoding = static_cast< TextEncoding >( ::GetACP() );
    }


    //
    // 1. Computer the required buffer size.
    // 2. Try to decode the string.
    //

    const Int requiredSize =
        ::MultiByteToWideChar(
            encoding,
            0,
            input.c_str(),
            input.length(),
            NULL, 0
        );

    if ( 0 == requiredSize )
    {
        // TODO: Trace warning?
        return false;
    }

    std::vector< Wchar > buffer( requiredSize + 1, 0 );

    const Int converted =
        ::MultiByteToWideChar(
            encoding,
            0,
            input.c_str(),
            input.length(),
            &buffer[0],
            requiredSize
        );

    if ( 0 == converted )
    {
        // TODO: Trace warning?
        return false;
    }

    this->assign( &buffer[0] );
    return true;
}


static DWORD WideString_Encode(
    std::string& result, const std::wstring& input, TextEncoding encoding, Uint requiredSize )
{
    std::vector< Char > buffer( requiredSize + 1, '\0' );

    const Int converted =
        ::WideCharToMultiByte(
            encoding,            // code page
            0,
            input.c_str(),
            input.length() + 1,  // including the terminating '\0'
            &buffer[0],
            requiredSize,
            NULL, NULL
        );

    if ( 0 == converted )
    {
        return ::GetLastError();
    }
    else
    {
        result.assign( &buffer[0] );
        return S_OK;
    }
}


std::string WideString::ToNarrow( TextEncoding encoding ) const
{
    CARAMEL_ASSERT( TEXT_ENCODING_UTF16_LE != encoding );

    if ( this->empty() ) { return std::string(); }

    if ( TEXT_ENCODING_WINDOWS_ACP == encoding )
    {
        encoding = static_cast< TextEncoding >( ::GetACP() );
    }


    //
    // 1. Computer the required buffer size.
    // 2. Try to encode the string.
    // 3. If the buffer is insufficient, double the buffer and try again.
    //

    const Int requiredSize =
        ::WideCharToMultiByte(
            encoding,            // code page
            0,
            this->c_str(),
            this->length() + 1,  // including the terminating '\0'
            NULL, 0, NULL, NULL
        );

    if ( 0 == requiredSize )
    {
        CARAMEL_THROW( "Compute required size failed" );
    }

    std::string result;

    DWORD errorCode = WideString_Encode( result, *this, encoding, requiredSize );
    if ( ERROR_INSUFFICIENT_BUFFER == errorCode )
    {
        // Double the buffer and try again.
        
        errorCode = WideString_Encode( result, *this, encoding, requiredSize * 2 );
    }

    if ( S_OK != errorCode )
    {
        // TODO: Trace some error
        CARAMEL_THROW( "Encode string failed" );
    }

    return result;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Windows

} // namespace Caramel

#endif // CARAMEL_SYSTEM_IS_WINDOWS
