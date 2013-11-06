// Caramel C++ Library - Error Facility - Implementation

#include "CaramelPch.h"

#include <Caramel/Error/Detail/ExceptionCatcherCore.h>
#include <Caramel/Error/Exception.h>


namespace Caramel
{

//
// Contents
//
//   Exception
//   Detail::ExceptionCatcherCore
//

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

} // namespace Caramel