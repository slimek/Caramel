// Caramel C++ Library - Error Facility - Detail - Exception Catcher Core Header

#ifndef __CARAMEL_ERROR_DETAIL_EXCEPTION_CATCHER_CORE_H
#define __CARAMEL_ERROR_DETAIL_EXCEPTION_CATCHER_CORE_H
#pragma once

#include <Caramel/Caramel.h>
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
//

class ExceptionCatcherCore
{
public:

    operator Bool() const { return m_exception; }
    Bool IsCaught() const { return m_exception; }

    ExceptionPtr Exception() const { return m_exception; }


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

    ExceptionPtr m_exception;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_ERROR_DETAIL_EXCEPTION_CATCHER_CORE_H
