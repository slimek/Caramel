// Caramel C++ Library - Error Facility - Exception Pointer Header

#ifndef __CARAMEL_ERROR_EXCEPTION_PTR_H
#define __CARAMEL_ERROR_EXCEPTION_PTR_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Error/Detail/ExceptionHolders.h>
#include <exception>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Exception Pointer
//
//   A construct to simulate std::exception_ptr.
//
//   TODO: This is a workaround for Android NDK r9x, where GNU C++ 4.8 on ARM
//         doesn't support std::exception_ptr.
//         You may replace this with std::exception_ptr as soon as possible.
//

class ExceptionPtr
{
public:

    ExceptionPtr();

    template< typename E >
    ExceptionPtr( const E& clonee );

    static ExceptionPtr Unknown();


    void Rethrow();


private:

    explicit ExceptionPtr( Detail::ExceptionHolder* holder );

    std::shared_ptr< Detail::ExceptionHolder > m_holder;
};


//
// Auxiliary Functions
//

ExceptionPtr CurrentException();


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline ExceptionPtr::ExceptionPtr()
    : m_holder( nullptr )
{
}


template< typename E >
inline ExceptionPtr::ExceptionPtr( const E& clonee )
    : m_holder( new Detail::ExceptionHolderConcrete< E >( clonee ))
{
}


inline ExceptionPtr::ExceptionPtr( Detail::ExceptionHolder* holder )
    : m_holder( holder )
{
}


inline ExceptionPtr ExceptionPtr::Unknown()
{
    return ExceptionPtr( new Detail::UnknownExceptionHolder );
}


inline void ExceptionPtr::Rethrow()
{
    m_holder->Rethrow();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ERROR_EXCEPTION_PTR_H
