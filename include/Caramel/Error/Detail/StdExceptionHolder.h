// Caramel C++ Library - Error Facility - Detail - std::exception Holder Header

#ifndef __CARAMEL_ERROR_DETAIL_STD_EXCEPTION_HOLDER_H
#define __CARAMEL_ERROR_DETAIL_STD_EXCEPTION_HOLDER_H
#pragma once

#include <Caramel/Caramel.h>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Std Exception Holder
//

class StdExceptionHolder
{
public:
    
    virtual ~StdExceptionHolder() {}

    virtual void Rethrow() = 0;
};


//
// Concrete Holder
//

template< typename E >
class StdExceptionHolderConcrete : public StdExceptionHolder
{
public:

    typedef E ExceptionType;

    explicit StdExceptionHolderConcrete( const E& e )
        : m_exception( e )
    {}
    
    void Rethrow() override { throw m_exception; }


private:

    ExceptionType m_exception;
};


//
// Unknown Holder
//

class UnknownExceptionHolder : public StdExceptionHolder
{
public:

    void Rethrow() override;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_ERROR_DETAIL_STD_EXCEPTION_HOLDER_H
