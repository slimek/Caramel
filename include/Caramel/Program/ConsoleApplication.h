// Caramel C++ Library - Program Facility - Console Application Header

#ifndef __CARAMEL_PROGRAM_CONSOLE_APPLICATION_H
#define __CARAMEL_PROGRAM_CONSOLE_APPLICATION_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Console Application
//

class ConsoleApplicationImpl;

class ConsoleApplication
{
public:

    ConsoleApplication();
    ~ConsoleApplication();

    Int Run();

private:

    virtual Int Main() = 0;

    std::unique_ptr< ConsoleApplicationImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_PROGRAM_CONSOLE_APPLICATION_H
