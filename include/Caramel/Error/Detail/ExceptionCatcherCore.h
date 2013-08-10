// Caramel C++ Library - Error Facility - Detail - Exception Catcher Core Header

#ifndef __CARAMEL_ERROR_DETAIL_EXCEPTION_CATCHER_CORE_H
#define __CARAMEL_ERROR_DETAIL_EXCEPTION_CATCHER_CORE_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Error/Exception.h>
#include <exception>

#if defined( CARAMEL_SYSTEM_IS_WINDOWS )
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

    operator Bool() const { return m_caught; }
    
    Bool IsCaught() const { return m_caught; }


protected: 
    
    ExceptionCatcherCore();

    
    /// Handler Functions ///

    void OnCatchCaramelException( const Caramel::Exception& e );
    void OnCatchStdException( const std::exception& e );
    void OnCatchUnknown();

    #if defined( CARAMEL_SYSTEM_IS_WINDOWS )
    LONG ExceptionFilter( EXCEPTION_POINTERS* exception, DWORD exceptionCode );
    #endif
    

    /// Data Members ///

    Bool m_caught;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_ERROR_DETAIL_EXCEPTION_CATCHER_CORE_H
