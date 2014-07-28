// Caramel C++ Library - Error Facility - Implementation

#include "CaramelPch.h"

#include "Error/ErrorManager.h"
#include <Caramel/Async/AnyEvent.h>
#include <Caramel/Error/Detail/ExceptionCatcherCore.h>
#include <Caramel/Error/AnyFailure.h>
#include <Caramel/Error/CatchException.h>
#include <Caramel/Error/Exception.h>
#include <Caramel/Error/ExceptionPtr.h>
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
//   AnyFailure
//   Detail::ExceptionCatcherCore
//   ExceptionPtr
//     Exception holders
//   AnyFailurePtr
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
    LockGuard lock( m_mutex );
    const AlertHandler oldHandler = m_alertHandler;
    m_alertHandler = newHandler;    
    return oldHandler;
}


AlertHandler ErrorManager::GetAlertHandler() const
{
    LockGuard lock( m_mutex );
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
// Any Failure
//

AnyFailure::AnyFailure( Int code )
    : m_code( code )
    , m_customWhat( false )
{
    this->Init();
}


AnyFailure::AnyFailure( Int code, const Any& value )
    : m_code( code )
    , m_value( value )
    , m_customWhat( false )
{
    this->Init();
}


AnyFailure::AnyFailure( Int code, Any&& value )
    : m_code( code )
    , m_value( std::move( value ))
    , m_customWhat( false )
{
    this->Init();
}


void AnyFailure::Init()
{
    m_what = Format( "AnyFailure[code:{0}]", m_code );
}


//
// Add What Message
//

AnyFailure& AnyFailure::What( const std::string& what )
{
    m_what = what;
    m_customWhat = true;
    return *this;
}


AnyFailure& AnyFailure::What( std::string&& what )
{
    m_what = std::move( what );
    m_customWhat = true;
    return *this;
}


///////////////////////////////////////////////////////////////////////////////
//
// Exception Catcher Core
//

namespace Detail
{

void ExceptionCatcherCore::OnCatchCaramelException( const Caramel::Exception& e )
{
    m_exception = ExceptionPtr( e );
}


void ExceptionCatcherCore::OnCatchCaramelAnyFailure( const Caramel::AnyFailure& e )
{
    m_exception = ExceptionPtr( e );
}


void ExceptionCatcherCore::OnCatchStdException( const std::exception& e )
{
    m_exception = ExceptionPtr::Clone( e );
}


void ExceptionCatcherCore::OnCatchUnknown()
{
    m_exception = ExceptionPtr::Unknown();

    CARAMEL_TRACE_ERROR( "Unknown exception caught" );
}


//
// Windows Structured Exception Handling (SEH)
//

#if defined( CARAMEL_COMPILER_IS_MSVC )

LONG ExceptionCatcherCore::ExceptionFilter( EXCEPTION_POINTERS* exception, DWORD exceptionCode )
{
    if ( 0xE06D7363 == exceptionCode )
    {
        // E0 + "msc", this is a Visual C++ exception.
    
        return EXCEPTION_CONTINUE_SEARCH;
    }

    // TODO: Add stack walker to Windows Exception Holder ?

    m_exception = ExceptionPtr( new Detail::WindowsExceptionHolder( exceptionCode ));

    return EXCEPTION_EXECUTE_HANDLER;
}


#endif // CARAMEL_SYSTEM_IS_WINDOWS

} // namespace Detail


///////////////////////////////////////////////////////////////////////////////
//
// Exception Ptr
//

ExceptionPtr::ExceptionPtr( const Caramel::Exception& e )
    : m_holder( new Detail::CaramelExceptionHolder( e ))
{
}


ExceptionPtr::ExceptionPtr( const Caramel::AnyFailure& e )
    : m_holder( new Detail::CaramelAnyFailureHolder( e ))
{
}


ExceptionPtr::ExceptionPtr( const std::shared_ptr< Detail::ExceptionHolder >& holder )
    : m_holder( holder )
{
}


std::string ExceptionPtr::TracingMessage() const
{
    return m_holder->TracingMessage();
}


ExceptionPtr CurrentException()
{
    return CatchException( [] { throw; } ).Exception();
}


namespace Detail
{

//
// Caramel::Exceptoin
//

std::string CaramelExceptionHolder::TracingMessage() const
{
    return Format( "Caramel::Exception caught\nfunction: {0}\nwhat: {1}\nin file: {2}, line: {3}",
                   m_exception.Function(), m_exception.What(), m_exception.File(), m_exception.Line() );
}


//
// Caramel::AnyException
//

std::string CaramelAnyFailureHolder::TracingMessage() const
{
    if ( m_exception.HasCustomWhat() )
    {
        return Format( "Caramel::AnyFailure caught, code: {0}, what: {1}",
                       m_exception.Code(), m_exception.What() );
    }
    else
    {
        return Format( "Caramel::AnyFailure caught, code: {0}", m_exception.Code() );
    }
}


//
// std::exception
//

std::string GetStdExceptionTracingMessage( const std::exception& e )
{
    return Format( "std::exception caught, what: {0}", e.what() );
}


//
// Unknown Exceptoin
//

void UnknownExceptionHolder::Rethrow() const
{
    throw std::runtime_error( "Unknown exception (can't be determined by Caramel)" );
}


std::string UnknownExceptionHolder::TracingMessage() const
{
    return "Unknown exception caught";
}


//
// Windows Exception
//

#if defined( CARAMEL_COMPILER_IS_MSVC )

void WindowsExceptionHolder::Rethrow() const
{
    throw std::runtime_error( this->What() );
}


std::string WindowsExceptionHolder::TracingMessage() const
{
    return Format( "Windows exception caught: {0}", this->What() );
}


std::string WindowsExceptionHolder::What() const
{
    switch ( m_code )
    {
    case EXCEPTION_ACCESS_VIOLATION: return "Access Violation";
    case EXCEPTION_STACK_OVERFLOW:   return "Stack Overflow";
    default: return "Undetermined";
    }    
}


#endif  // CARAMEL_COMPILER_IS_MSVC


} // namespace Detail


///////////////////////////////////////////////////////////////////////////////
//
// Any Failure Pointer
//

AnyFailurePtr::AnyFailurePtr()
{
}


AnyFailurePtr::AnyFailurePtr( const std::shared_ptr< Detail::CaramelAnyFailureHolder >& holder )
    : ExceptionPtr( holder )
{
}


AnyFailurePtr AnyFailurePtr::CastFrom( const ExceptionPtr& e )
{
    const auto anyFailure =
        std::dynamic_pointer_cast< Detail::CaramelAnyFailureHolder >( e.m_holder );

    // Returns null if e.m_holder is not an AnyFailure.           
    return AnyFailurePtr( anyFailure );
}


const AnyFailure* AnyFailurePtr::operator->() const
{
    const auto failure = std::dynamic_pointer_cast< Detail::CaramelAnyFailureHolder >( m_holder );

    return failure ? failure->GetPointer()
                   : nullptr;
}


///////////////////////////////////////////////////////////////////////////////
//
// Alert
//

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
        return;

    default:
        CARAMEL_TRACE_WARN( "Invalid result: %d", result );
        // Pass through

    case ALERT_RESULT_ABORT:
        CARAMEL_TRACE_INFO( "Program aborts by alert result" );
        ::abort();
        return;

    case ALERT_RESULT_CONTINUE_ONCE:
        CARAMEL_NOT_IMPLEMENTED();
    }
}


//
// Handlers
//

AlertHandler SetAlertHandler( AlertHandler newHandler )
{
    return ErrorManager::Instance()->SetAlertHandler( newHandler );
}


#if defined( NDEBUG )

AlertResult DefaultAlertHandler(
    Int line, const std::string& file, const std::string& function,
    const std::string& message )
{
    return TraceAlertHandler( line, file, function, message );
}

#else

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
    #elif defined( CARAMEL_SYSTEM_IS_IOS )
    {
        ; // TODO: Add iOS assert() implementation
    }
    #else
    {
        ThrowAlertHandler( line, file, function, message );
    }
    #endif

    return ALERT_RESULT_CONTINUE_ALL;
}

#endif // NDEBUG


AlertResult TraceAlertHandler(
    Int line, const std::string& file, const std::string& function,
    const std::string& message )
{
    CARAMEL_TRACE_WARN(
        "ALERT WARNING: \"%s\" line %d, function: \"%s\"\n%s",
        file, line, function, message
    );

    return ALERT_RESULT_CONTINUE_ALL;
}


AlertResult ThrowAlertHandler(
    Int line, const std::string& file, const std::string& function,
    const std::string& message )
{
    throw Exception( line, file, function, "Assert failed: " + message );

    // No return value.
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel