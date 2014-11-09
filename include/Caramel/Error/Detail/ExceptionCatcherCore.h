// Caramel C++ Library - Error Facility - Detail - Exception Catcher Core Header

#ifndef __CARAMEL_ERROR_DETAIL_EXCEPTION_CATCHER_CORE_H
#define __CARAMEL_ERROR_DETAIL_EXCEPTION_CATCHER_CORE_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Error/AnyFailure.h>
#include <Caramel/Error/Exception.h>
#include <Caramel/Error/ExceptionPtr.h>
#include <exception>

#if defined( CARAMEL_COMPILER_IS_MSVC )
#include <Windows.h>
#endif


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Exception Catcher Core
// - When an AnyFailure is caught, both m_anyFailure and m_exception exist.
//   For other exceptions, m_anyFailure is null and only m_exception exists.
//

class ExceptionCatcherCore
{
public:

    explicit operator Bool() const { return static_cast< Bool >( m_exception ); }
    Bool IsCaught()          const { return static_cast< Bool >( m_exception ); }

    AnyFailurePtr AnyFailure() const { return m_anyFailure; }
    ExceptionPtr  Exception()  const { return m_exception; }

    std::string TracingMessage() const { return m_exception.TracingMessage(); }

    void Rethrow() { m_exception.Rethrow(); }


protected: 
    
    /// Handler Functions ///

    void OnCatchCaramelException( const Caramel::Exception& e );
    void OnCatchCaramelAnyFailure( const Caramel::AnyFailure& e );
    void OnCatchStdException( const std::exception& e );
    void OnCatchUnknown();

    #if defined( CARAMEL_COMPILER_IS_MSVC )
    LONG ExceptionFilter( EXCEPTION_POINTERS* exception, DWORD exceptionCode );
    #endif
    

    /// Data Members ///

    AnyFailurePtr m_anyFailure;
    ExceptionPtr  m_exception;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_ERROR_DETAIL_EXCEPTION_CATCHER_CORE_H
