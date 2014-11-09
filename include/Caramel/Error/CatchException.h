// Caramel C++ Library - Error Facility - Catch Exception Header

#ifndef __CARAMEL_ERROR_CATCH_EXCEPTION_H
#define __CARAMEL_ERROR_CATCH_EXCEPTION_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Error/Detail/ExceptionCatcherCore.h>
#include <Caramel/Error/ExceptionPtr.h>
#include <type_traits>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Catch Exception & Exception Catcher
//
// USAGE:
//
//   std::string MyServer::FindUserName( Int userId )
//   {
//       const auto xc = CatchException( [] { m_db->FindUserData( userId ); } );
//       if ( xc )
//       {
//            // Handle exception here, you may:
//            // - Log more detail information.
//            // - Do some workaround or fallback.
//            // - Throw another exception, or re-throw the catched exception.
//
//            LOG( "FindUserName() : user id {0} not found, error: {1}",
//                 userId, xc.TracingMessage() );
//            xc.Rethrow();
//       }
//      
//       // If the function succeeded, call Result() to get the return value.
//       return xc.Result();
//   }
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

    #if defined( CARAMEL_COMPILER_IS_MSVC )

    template< typename Function >
    void DoInvoke( const Function& f );

    #endif


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
    catch ( const Caramel::AnyFailure& e )
    {
        this->OnCatchCaramelAnyFailure( e );
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
    catch ( const Caramel::AnyFailure& e )
    {
        this->OnCatchCaramelAnyFailure( e );
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
// - Only Visual C++ supports this syntax.
//

#if defined( CARAMEL_COMPILER_IS_MSVC )

template< typename ResultT >
template< typename Function >
inline void ExceptionCatcher< ResultT >::Invoke( const Function& f )
{
    __try
    {
        this->DoInvoke( f );
    }
    __except ( this->ExceptionFilter( GetExceptionInformation(), GetExceptionCode() ))
    {
        ;  // Do nothing
    }
}


template< typename ResultT >
template< typename Function >
inline void ExceptionCatcher< ResultT >::DoInvoke( const Function& f )
{
    m_result = f();
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
        ;  // Do nothing
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
    
#endif // CARAMEL_COMPILER_IS_MSVC

///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ERROR_CATCH_EXCEPTION_H
