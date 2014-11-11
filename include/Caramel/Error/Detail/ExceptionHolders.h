// Caramel C++ Library - Error Facility - Detail - Exception Holders Header

#ifndef __CARAMEL_ERROR_DETAIL_EXCEPTION_HOLDERS_H
#define __CARAMEL_ERROR_DETAIL_EXCEPTION_HOLDERS_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Error/AnyFailure.h>
#include <Caramel/Error/Exception.h>
#include <exception>


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

    virtual void Rethrow() const = 0;

    // Message to be output to Trace.
    virtual std::string TracingMessage() const = 0;
};


//
// Concrete Holders
//

class CaramelExceptionHolder : public ExceptionHolder
{
public:
    
    explicit CaramelExceptionHolder( const Caramel::Exception& e )
        : m_exception( e )
    {}

    void Rethrow() const override { throw m_exception; }

    std::string TracingMessage() const override;

private:

    Caramel::Exception m_exception;
};


class CaramelAnyFailureHolder : public ExceptionHolder
{
public:

    explicit CaramelAnyFailureHolder( const Caramel::AnyFailure& exception )
        : m_exception( exception )
    {}

    void Rethrow() const override { throw m_exception; }

    std::string TracingMessage() const override;

    const Caramel::AnyFailure* GetPointer() const { return &m_exception; }


private:

    Caramel::AnyFailure m_exception;
};


class StdExceptionHolder : public ExceptionHolder
                         , public std::exception
{
public:

    explicit StdExceptionHolder( const std::exception& e )
        : m_what( e.what() )
    {}

    void Rethrow() const override { throw *this; }

    const Char* what() const CARAMEL_NOEXCEPT override { return m_what.c_str(); }

    std::string TracingMessage() const override;

private:

    std::string m_what;
};


//
// Unknown Holder
//

class UnknownExceptionHolder : public ExceptionHolder
{
public:

    void Rethrow() const override;

    std::string TracingMessage() const override;
};


#if defined( CARAMEL_COMPILER_IS_MSVC )

//
// Windows Exceptoin Holder
// - The SEH exceptions, including Access Violation, Stack Overflow, etc.
//

class WindowsExceptionHolder : public ExceptionHolder
{
public:

    WindowsExceptionHolder( Uint32 exceptionCode )
        : m_code( exceptionCode )
    {}

    void Rethrow() const override;

    std::string TracingMessage() const override;

    std::string What() const;

private:

    Uint32 m_code; // Windows exception code
};

#endif


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_ERROR_DETAIL_EXCEPTION_HOLDERS_H
