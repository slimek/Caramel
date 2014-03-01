// Caramel C++ Library - Error Facility - Failure Header

#ifndef __CARAMEL_ERROR_FAILURE_H
#define __CARAMEL_ERROR_FAILURE_H
#pragma once

#include <Caramel/Caramel.h>
#include <exception>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Failure
//  - An exception that usually is expected to be handled.
//

class Failure : public std::exception
{
public:

    //
    // Specify a failure code.
    // Its meaning depends on the application.
    //
    explicit Failure( Int code );

    //
    // Specify a failure code and a what message to describe it.
    //
    Failure( Int failureCode, const std::string& what );
    Failure( Int failureCode, std::string&& what );


    /// Properties ///

    Int         Code() const { return m_code; }
    std::string What() const { return m_what; }


    /// Overrides std::exception ///

    const Char* what() const CARAMEL_NOEXCEPT override { return m_what.c_str(); }


private:

    Int m_code;
    std::string m_what;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ERROR_FAILURE_H

