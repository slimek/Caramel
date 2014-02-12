// Caramel C++ Library - Error Facility - Catch Exception Header

#ifndef __CARAMEL_ERROR_CATCH_EXCEPTION_H
#define __CARAMEL_ERROR_CATCH_EXCEPTION_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Error/Detail/ExceptionCatcherCore.h>
#include <Caramel/Error/Exception.h>
#include <type_traits>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Catch Exception & Exception Catcher
//

template< typename ResultT >
class ExceptionCatcher : public Detail::ExceptionCatcherCore
{
public:
    
    template< typename Function >
    ExceptionCatcher( const Function& f );

    
    typedef ResultT ResultType;

    ResultType Result() const { return m_result; }

private:

    template< typename Function >
    void Invoke( const Function& f );

    ResultType m_result;
};


// Specialization of void Functions

template<>
class ExceptionCatcher< void > : public Detail::ExceptionCatcherCore
{
public:

    template< typename Function >
    ExceptionCatcher( const Function& f );

private:

    template< typename Function >
    void Invoke( const Function& f );
};


//
// Stand-alone Function
//

template< typename Function >
inline ExceptionCatcher< typename std::result_of< Function() >::type > CatchException( const Function& f )
{
    return ExceptionCatcher< typename std::result_of< Function() >::type >( f );
}


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename ResultT >
template< typename Function >
inline ExceptionCatcher< ResultT >::ExceptionCatcher( const Function& f )
{
    try
    {
        this->Invoke( f );
    }
    catch ( const Caramel::Exception& e )
    {
        this->OnCatchCaramelException( e );
    }
    catch ( const std::exception& e )
    {
        this->OnCatchStdException( e );
    }
    catch ( ... )
    {
        this->OnCatchUnknown();
    }
}


template< typename Function >
inline ExceptionCatcher< void >::ExceptionCatcher( const Function& f )
{
    try
    {
        this->Invoke( f );
    }
    catch ( const Caramel::Exception& e )
    {
        this->OnCatchCaramelException( e );
    }
    catch ( const std::exception& e )
    {
        this->OnCatchStdException( e );
    }
    catch ( ... )
    {
        this->OnCatchUnknown();
    }
}


//
// Windows Structured Exception Handling (SEH)
//

#if defined( CARAMEL_SYSTEM_IS_WINDOWS )

template< typename ResultT >
template< typename Function >
inline void ExceptionCatcher< ResultT >::Invoke( const Function& f )
{
    __try
    {
        m_result = f();
    }
    __except ( this->ExceptionFilter( GetExceptionInformation(), GetExceptionCode() ))
    {
        m_caught = true;
    }
}


template< typename Function >
inline void ExceptionCatcher< void >::Invoke( const Function& f )
{
    __try
    {
        f();
    }
    __except ( this->ExceptionFilter( GetExceptionInformation(), GetExceptionCode() ))
    {
        m_caught = true;
    }
}


#else
    
template< typename ResultT >
template< typename Function >
inline void ExceptionCatcher< ResultT >::Invoke( const Function& f )
{
    m_result = f();
}


template< typename Function >
inline void ExceptionCatcher< void >::Invoke( const Function& f )
{
    f();
}
    
#endif // CARAMEL_SYSTEM_IS_WINDOWS

///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ERROR_CATCH_EXCEPTION_H
