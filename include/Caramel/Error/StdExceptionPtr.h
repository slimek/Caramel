// Caramel C++ Library - Error Facility - std::exception Pointer Header

#ifndef __CARAMEL_ERROR_STD_EXCEPTION_PTR_H
#define __CARAMEL_ERROR_STD_EXCEPTION_PTR_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Error/Detail/StdExceptionHolder.h>
#include <exception>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Std Exception Pointer
//
//   A construct to simulate std::exception_ptr.
//
//   TODO: This is a workaround for Android NDK r9x, where GNU C++ 4.8 on ARM
//         doesn't support std::exception_ptr.
//         You may replace this with std::exception_ptr as soon as possible.
//

class StdExceptionPtr
{
public:

    StdExceptionPtr();

    template< typename E >
    StdExceptionPtr( const E& clonee );

    static StdExceptionPtr Unknown();


    void Rethrow();


private:

    explicit StdExceptionPtr( Detail::StdExceptionHolder* holder );

    std::shared_ptr< Detail::StdExceptionHolder > m_holder;
};


//
// Auxiliary Functions
//

StdExceptionPtr CurrentStdException();


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline StdExceptionPtr::StdExceptionPtr()
    : m_holder( nullptr )
{
}


template< typename E >
inline StdExceptionPtr::StdExceptionPtr( const E& clonee )
    : m_holder( new Detail::StdExceptionHolderConcrete< E >( clonee ))
{
}


inline StdExceptionPtr::StdExceptionPtr( Detail::StdExceptionHolder* holder )
    : m_holder( holder )
{
}


inline StdExceptionPtr StdExceptionPtr::Unknown()
{
    return StdExceptionPtr( new Detail::UnknownExceptionHolder );
}


inline void StdExceptionPtr::Rethrow()
{
    m_holder->Rethrow();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ERROR_STD_EXCEPTION_PTR_H
