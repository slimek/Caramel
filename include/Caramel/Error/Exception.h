// Caramel C++ Library - Error Facility - Exception Header

#ifndef __CARAMEL_ERROR_EXCEPTION_H
#define __CARAMEL_ERROR_EXCEPTION_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

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

#define CARAMEL_THROW( what ) \
    throw Exception( __LINE__, __FILE__, __FUNCTION__, what )

#define CARAMEL_INVALID_ARGUMENT() \
    CARAMEL_THROW( "Invalid Argument" )

#define CARAMEL_NOT_IMPLEMENTED() \
    CARAMEL_THROW( "Not Implemented" )


///////////////////////////////////////////////////////////////////////////////

#endif // __CARAMEL_ERROR_EXCEPTION_H
