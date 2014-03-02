// Caramel C++ Library - Error Facility - Detail - Exception Holders Header

#ifndef __CARAMEL_ERROR_DETAIL_EXCEPTION_HOLDERS_H
#define __CARAMEL_ERROR_DETAIL_EXCEPTION_HOLDERS_H
#pragma once

#include <Caramel/Caramel.h>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Exception Holder
//

class ExceptionHolder
{
public:
    
    virtual ~ExceptionHolder() {}

    virtual void Rethrow() = 0;
};


//
// Concrete Holder
//

template< typename E >
class ExceptionHolderConcrete : public ExceptionHolder
{
public:

    typedef E ExceptionType;

    explicit ExceptionHolderConcrete( const E& e )
        : m_exception( e )
    {}
    
    void Rethrow() override { throw m_exception; }


private:

    ExceptionType m_exception;
};


//
// Unknown Holder
//

class UnknownExceptionHolder : public ExceptionHolder
{
public:

    void Rethrow() override;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_ERROR_DETAIL_EXCEPTION_HOLDERS_H
