// Caramel C++ Library - Error Facility - Exception Header

#ifndef __CARAMEL_ERROR_EXCEPTION_H
#define __CARAMEL_ERROR_EXCEPTION_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/String/Sprintf.h>
#include <exception>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Exception
//

class Exception : public std::exception
{
public:
    Exception(                        // < default values >
        Uint line,                    //   __LINE__
        const std::string& file,      //   __FILE__ 
        const std::string& function,  //   __FUNCTION__
        const std::string& what
    );

    virtual ~Exception() {}


    /// Accessors ///

    Uint        Line()     const { return m_line; }
    std::string File()     const { return m_file; }
    std::string Function() const { return m_function; }
    std::string What()     const { return m_what; }


    /// Overrides std::exception ///

    const Char* what() const CARAMEL_NOEXCEPT override { return m_what.c_str(); }


private:
    Uint m_line;
    std::string m_file;
    std::string m_function;
    std::string m_what;
};


} // namespace Caramel

///////////////////////////////////////////////////////////////////////////////
//
// Throw Exception Macros
//

#define CARAMEL_THROW( ... ) \
    throw CARAMEL_MAKE_EXCEPTION( __VA_ARGS__ )

#define CARAMEL_MAKE_EXCEPTION( ... ) \
    Caramel::Exception( __LINE__, __FILE__, __FUNCTION__, Caramel::Sprintf( __VA_ARGS__ ))


//
// Specific Exceptions
// - The below macros have only 1 argument and don't use Sprintf().
//

#define CARAMEL_THROW1( msg ) \
    throw Caramel::Exception( __LINE__, __FILE__, __FUNCTION__, msg )

#define CARAMEL_INVALID_ARGUMENT() \
    CARAMEL_THROW1( "Invalid Argument" )

#define CARAMEL_NOT_IMPLEMENTED() \
    CARAMEL_THROW1( "Not Implemented" )

#define CARAMEL_NOT_REACHED() \
    CARAMEL_THROW1( "Not reached" )


///////////////////////////////////////////////////////////////////////////////

#endif // __CARAMEL_ERROR_EXCEPTION_H
