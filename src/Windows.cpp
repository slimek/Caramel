// Caramel C++ Library - Windows Facility - Implementation

#include "CaramelPch.h"


#include "Windows/RegistryImpl.h"
#include <Caramel/Windows/CrtDebug.h>
#include <Caramel/Windows/DebuggerTraceAdapter.h>
#include <Caramel/Windows/FileInfo.h>
#include <Caramel/Windows/WideString.h>
#include <crtdbg.h>
#include <windows.h>


namespace Caramel
{

namespace Windows
{

//
// Contents
//
//   CrtDebug
//   DebuggerTraceAdapter
//   FileInfo
//   Registry
//   WideString
//

///////////////////////////////////////////////////////////////////////////////
//
// CRT Debug
//

void EnableMemoryLeakCheckAtExit()
{
    Int flags = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );
    flags |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag( flags );
}


///////////////////////////////////////////////////////////////////////////////
//
// Debugger Trace Listener
//

void DebuggerTraceAdapter::Write( Trace::Level, const std::string& message )
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

    const DWORD shortConverted = ::GetShortPathNameW(
        wpath.c_str(), &shortBuffer[0], static_cast< DWORD >( shortBuffer.size() ));
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

    const DWORD longConverted = ::GetLongPathNameW(
        shortPath.c_str(), &longBuffer[0], static_cast< DWORD >( longBuffer.size() ));
    if ( ! longConverted )
    {
        CARAMEL_THROW( "GetLongPathName() convert failed" );
    }

    const std::wstring longPath( &longBuffer[0] );

    return Path( longPath );
}


///////////////////////////////////////////////////////////////////////////////
//
// Registry
//

Registry Registry::LocalMachine()
{
    return Registry( std::make_shared< RegistryImpl >( HKEY_LOCAL_MACHINE, "LOCAL_MACHINE" ));
}


Registry::Registry( std::shared_ptr< RegistryImpl > impl )
    : m_impl( impl )
{
}


//
// Get Values
//

Bool Registry::GetStringValue(
    const Utf8String& keyPath, const Utf8String& valueName, Utf8String& value ) const
{
    HKEY key = NULL;
    const std::string keyFullPath = m_impl->Name() + "\\" + keyPath.ToString();

    const std::wstring keyWsPath = keyPath.ToWstring();

    const LONG keyResult = ::RegOpenKeyExW(
        m_impl->Handle(), keyPath.ToWstring().c_str(), 0, KEY_READ | KEY_WOW64_64KEY,
        &key
    );

    if ( keyResult != ERROR_SUCCESS )
    {
        if ( keyResult == ERROR_FILE_NOT_FOUND )
        {
            return false;
        }
        else
        {
            CARAMEL_THROW( "Open registry key \"{0}\" failed, error: {1}", keyFullPath, keyResult );
        }
    }

    return RegistryImpl( key, keyFullPath ).GetStringValue( valueName, value );
}


Bool Registry::GetStringValue(
    const std::string& keyPath, const std::string& valueName, std::string& value ) const
{
    CARAMEL_CHECK_UTF8_ARGUMENT( u8KeyPath, keyPath );
    CARAMEL_CHECK_UTF8_ARGUMENT( u8ValueName, valueName );

    Utf8String u8Value;

    const Bool ok = this->GetStringValue( u8KeyPath, u8ValueName, u8Value );

    value = u8Value.ToString();
    return ok;
}


//
// Implementation
//

RegistryImpl::RegistryImpl( HKEY key, const std::string& name )
    : m_key( key )
    , m_name( name )
{
}


RegistryImpl::~RegistryImpl()
{
    ::RegCloseKey( m_key );
}


Bool RegistryImpl::GetStringValue( const Utf8String& valueName, Utf8String& value ) const
{
    const std::wstring valueWsName = valueName.ToWstring();

    if ( ! this->HasValue( valueWsName )) { return false; }

    auto valueInfo = this->GetValueInfo( valueWsName );

    if ( valueInfo.size == 0 )
    {
        value = Utf8String();  // this value is an empty string.
    }

    DWORD size = valueInfo.size;
    std::vector< Wchar > buffer( size + 1, 0 );

    const LONG result = ::RegQueryValueExW(
        m_key, valueWsName.c_str(), NULL, NULL,
        reinterpret_cast< Byte* >( &buffer[0] ), &size
    );

    if ( result != ERROR_SUCCESS )
    {
        CARAMEL_THROW( "RegQueryValueExW() failed, value: \"{0}/{1}\"", m_name, valueName );
    }

    value = Utf8String( std::wstring( &buffer[0] ));
    return true;
}


Bool RegistryImpl::HasValue( const std::wstring& valueName ) const
{
    //return ERROR_SUCCESS ==
    //    ::RegQueryValueExW( m_key, valueName.c_str(), NULL, NULL, NULL, NULL );

    const LONG result = ::RegQueryValueExW( m_key, valueName.c_str(), NULL, NULL, NULL, NULL );
    return ERROR_SUCCESS == result;
}


RegistryImpl::ValueInfo RegistryImpl::GetValueInfo( const std::wstring& valueName ) const
{
    ValueInfo info;

    const LONG result =
        ::RegQueryValueExW( m_key, valueName.c_str(), NULL, &info.type, NULL, &info.size );

    CARAMEL_CHECK( result == ERROR_SUCCESS );

    return info;
}


///////////////////////////////////////////////////////////////////////////////
//
// Wide String
//

WideString::WideString()
{
}


WideString::WideString( const std::wstring& s )
    : m_s( s )
{
}


WideString::WideString( const std::string& input, TextEncoding encoding )
{
    if ( ! this->TryParse( input, encoding ))
    {
        CARAMEL_THROW( "Convert to UTF-16 failed, input: \"{0}\", encoding: {1}", input, encoding );
    }
}


WideString WideString::FromUtf8( const std::string& input )
{
    return WideString( input, TEXT_ENCODING_UTF8 );
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
            static_cast< Int >( input.length() ),
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
            static_cast< Int >( input.length() ),
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
            static_cast< Int >( input.length() + 1 ),  // including the terminating '\0'
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
            static_cast< Int >( m_s.length() + 1 ),  // including the terminating '\0'
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


std::string WideString::ToUtf8() const
{
    return this->ToNarrow( TEXT_ENCODING_UTF8 );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Windows

} // namespace Caramel
