// Caramel C++ Library - Error Facility - Catch Exception Header

#ifndef __CARAMEL_ERROR_CATCH_EXCEPTION_H
#define __CARAMEL_ERROR_CATCH_EXCEPTION_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Error/Exception.h>
#include <type_traits>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Exception Catcher
//

template< typename ResultT >
class ExceptionCatcher
{
public:
    
    template< typename Function >
    ExceptionCatcher( Function f );

    
    typedef ResultT ResultType;

    ResultType Result() const { return m_result; }

private:

    ResultType m_result;
};


//
// Stand-aline Function
//

template< typename Function >
inline ExceptionCatcher< typename std::result_of< Function() >::type > CatchException( Function f )
{
    return ExceptionCatcher< typename std::result_of< Function() >::type >( f );
}


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename ResultT >
template< typename Function >
inline ExceptionCatcher< ResultT >::ExceptionCatcher( Function f )
{
    try
    {
        m_result = f();
    }
    catch ( const Caramel::Exception& )
    {
        ;
    }
    catch ( const std::exception& )
    {
        ;
    }
    catch ( ... )
    {
        ;
    }
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ERROR_CATCH_EXCEPTION_H
