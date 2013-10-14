// Caramel C++ Library - Error Facility - Catch Exception Header

#ifndef __CARAMEL_ERROR_CATCH_EXCEPTION_H
#define __CARAMEL_ERROR_CATCH_EXCEPTION_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

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
// Stand-aline Function
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


#endif // CARAMEL_SYSTEM_IS_WINDOWS

///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ERROR_CATCH_EXCEPTION_H
