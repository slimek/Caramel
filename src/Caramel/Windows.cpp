// Caramel C++ Library - Windows Facility - Implementation

#include <Caramel/CaramelPch.h>


#if defined( CARAMEL_SYSTEM_IS_WINDOWS )

#include <Caramel/Windows/DebuggerTraceListener.h>
#include <Caramel/Windows/FileInfo.h>
#include <Caramel/Windows/WideString.h>
#include <windows.h>


namespace Caramel
{

namespace Windows
{

//
// Contents
//
//   DebuggerTraceListener
//   FileInfo
//   WideString
//

///////////////////////////////////////////////////////////////////////////////
//
// Debugger Trace Listener
//

void DebuggerTraceListener::Write( Trace::Level, const std::string& message )
{
    Utf8String u8msg;
    if ( u8msg.TryParse( message ))
    {
        ::OutputDebugStringW( u8msg.ToWstring().c_str() );
        ::OutputDebugStringW( L"\n" );
    }
    else
    {
        ::OutputDebugStringA( message.c_str() );
        ::OutputDebugStringA( "\n" );
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// File Info
//

FileInfo::FileInfo( const Path& path )
    : Caramel::FileInfo( path )
{
}


Path FileInfo::GetExactPath() const
{
    const std::wstring wpath = this->GetPath().ToWstring();

    /// Step 1 : Convert original path to short path.

    const DWORD shortSize = ::GetShortPathNameW( wpath.c_str(), NULL, 0 );
    if ( 0 == shortSize )
    {
        CARAMEL_THROW( "GetShortPathName() get buffer size failed" );
    }

    std::vector< Wchar > shortBuffer( shortSize + 1, 0 );

    const DWORD shortConverted = ::GetShortPathNameW( wpath.c_str(), &shortBuffer[0], shortBuffer.size() );
    if ( ! shortConverted )
    {
        CARAMEL_THROW( "GetShortPathName() convert failed" );
    }

    const std::wstring shortPath( &shortBuffer[0] );


    /// Step 2 : Convert short path to long path.

    const DWORD longSize = ::GetLongPathNameW( shortPath.c_str(), NULL, 0 );
    if ( 0 == longSize )
    {
        CARAMEL_THROW( "GetLongPathName() get buffer size failed" );
    }

    std::vector< Wchar > longBuffer( longSize + 1, 0 );

    const DWORD longConverted = ::GetLongPathNameW( shortPath.c_str(), &longBuffer[0], longBuffer.size() );
    if ( ! longConverted )
    {
        CARAMEL_THROW( "GetLongPathName() convert failed" );
    }

    const std::wstring longPath( &longBuffer[0] );

    return Path( longPath );
}


///////////////////////////////////////////////////////////////////////////////
//
// Wide String
//

WideString::WideString()
{
}


WideString::WideString( const std::string& input, TextEncoding encoding )
{
    if ( ! this->TryParse( input, encoding ))
    {
        CARAMEL_THROW( "Convert to UTF-16 failed, input: %s, encoding: %u", input, encoding );
    }
}


Bool WideString::TryParse( const std::string& input, TextEncoding encoding )
{
    if ( input.empty() )
    {
        m_s.assign( std::wstring() );
        return true;
    }

    if ( TEXT_ENCODING_UTF16_LE == encoding )
    {
        const Wchar* winput = reinterpret_cast< const Wchar* >( input.c_str() );
        m_s.assign( winput, winput + input.length() / 2  );
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

    m_s.assign( &buffer[0] );
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

    if ( m_s.empty() ) { return std::string(); }

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
            m_s.c_str(),
            m_s.length() + 1,  // including the terminating '\0'
            NULL, 0, NULL, NULL
        );

    if ( 0 == requiredSize )
    {
        CARAMEL_THROW( "Compute required size failed" );
    }

    std::string result;

    DWORD errorCode = WideString_Encode( result, m_s, encoding, requiredSize );
    if ( ERROR_INSUFFICIENT_BUFFER == errorCode )
    {
        // Double the buffer and try again.
        
        errorCode = WideString_Encode( result, m_s, encoding, requiredSize * 2 );
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
