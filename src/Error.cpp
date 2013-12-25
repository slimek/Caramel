// Caramel C++ Library - Error Facility - Implementation

#include "CaramelPch.h"

#include "Error/ErrorManager.h"
#include <Caramel/Error/Detail/ExceptionCatcherCore.h>
#include <Caramel/Error/Exception.h>
#include <Caramel/String/Utf8String.h>
#include <Caramel/Thread/MutexLocks.h>
#include <cassert>

#if defined( CARAMEL_SYSTEM_IS_WINDOWS )
#include <Windows.h>
#endif



namespace Caramel
{

//
// Contents
//
//   ErrorManager
//   Exception
//   Detail::ExceptionCatcherCore
//   Alert
//

///////////////////////////////////////////////////////////////////////////////
//
// Error Manager
//

ErrorManager::ErrorManager()
    : m_alertHandler( &DefaultAlertHandler )
{
}


AlertHandler ErrorManager::SetAlertHandler( AlertHandler newHandler )
{
    auto ulock = UniqueLock( m_mutex );
    
    const AlertHandler oldHandler = m_alertHandler;
    m_alertHandler = newHandler;    
    return oldHandler;
}


AlertHandler ErrorManager::GetAlertHandler() const
{
    auto ulock = UniqueLock( m_mutex );

    return m_alertHandler;
}


///////////////////////////////////////////////////////////////////////////////
//
// Exception
//

Exception::Exception(
    Uint line, const std::string& file, const std::string& function, const std::string& what
)
    : m_line( line )
    , m_file( file )
    , m_function( function )
    , m_what( what )
{}


///////////////////////////////////////////////////////////////////////////////
//
// Exception Catcher Core
//

namespace Detail
{

ExceptionCatcherCore::ExceptionCatcherCore()
    : m_caught( false )
{
}


void ExceptionCatcherCore::OnCatchCaramelException( const Exception& e )
{
    m_caught = true;

    CARAMEL_TRACE_ERROR( "Caramel::Exception caught, what: %s", e.What() );
}


void ExceptionCatcherCore::OnCatchStdException( const std::exception& e )
{
    m_caught = true;

    CARAMEL_TRACE_ERROR( "std::exception caught, what: %s", e.what() );
}


void ExceptionCatcherCore::OnCatchUnknown()
{
    m_caught = true;

    CARAMEL_TRACE_ERROR( "Unknown exception caught" );
}


//
// Windows Structured Exception Handling (SEH)
//

#if defined( CARAMEL_SYSTEM_IS_WINDOWS )

LONG ExceptionCatcherCore::ExceptionFilter( EXCEPTION_POINTERS* exception, DWORD exceptionCode )
{
    if ( 0xE06D7363 == exceptionCode )
    {
        // E0 + "msc", this is a Visual C++ exception.
    
        return EXCEPTION_CONTINUE_SEARCH;
    }

    switch ( exceptionCode )
    {
    case EXCEPTION_ACCESS_VIOLATION:
        // TODO: trace access violation and stack walker
        return EXCEPTION_EXECUTE_HANDLER;

    case EXCEPTION_STACK_OVERFLOW:
        // TODO: trace stack overflow
        return EXCEPTION_EXECUTE_HANDLER;

    default:
        // TODO: trace exception code
        ;
    }

    return EXCEPTION_CONTINUE_SEARCH;
}


#endif // CARAMEL_SYSTEM_IS_WINDOWS

} // namespace Detail


///////////////////////////////////////////////////////////////////////////////
//
// Alert
//

AlertResult DefaultAlertHandler(
    Int line, const std::string& file, const std::string& function,
    const std::string& message )
{
    // Use ASNI C assert mechanism
    // - It depends on the platform implementation.
    //   Usually it can abort or break program itself.

    #if defined( CARAMEL_SYSTEM_IS_WINDOWS )
    {
        const Utf8String file( file );
        const Utf8String message( message );

        _wassert( message.ToWstring().c_str(), file.ToWstring().c_str(), line );
    }
    #elif defined( CARAMEL_SYSTEM_IS_ANDROID )
    {
        __assert2( file.c_str(), line, function.c_str(), message.c_str() );
    }
    #else
    {
        throw Exception( line, file, function, "Assert failed: " + message );
    }
    #endif

    return ALERT_RESULT_CONTINUE_ALL;
}


void Alert(
    Int line, const std::string& file, const std::string& function,
    const std::string& message )
{
    const AlertResult result =
        ErrorManager::Instance()->GetAlertHandler()( line, file, function, message );

    switch ( result )
    {
    case ALERT_RESULT_CONTINUE_ALL:
        return;

    case ALERT_RESULT_BREAK:
        #if defined( CARAMEL_SYSTEM_IS_WINDOWS )
        {
            ::DebugBreak();
        }
        #else
        {
            CARAMEL_NOT_IMPLEMENTED();
        }
        #endif

    case ALERT_RESULT_ABORT:
        abort();

    case ALERT_RESULT_CONTINUE_ONCE:
        CARAMEL_NOT_IMPLEMENTED();

    default:
        CARAMEL_NOT_REACHED();
    }
}


AlertHandler SetAlertHandler( AlertHandler newHandler )
{
    return ErrorManager::Instance()->SetAlertHandler( newHandler );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel