// Caramel C++ Library - Program Facility - Console Application Header

#ifndef __CARAMEL_PROGRAM_CONSOLE_APPLICATION_H
#define __CARAMEL_PROGRAM_CONSOLE_APPLICATION_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <vector>


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
    Int Run( Int argc, Char* argv[] );

    std::vector< std::string > GetArguments() const;


private:

    virtual Int Main() = 0;

    std::unique_ptr< ConsoleApplicationImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_PROGRAM_CONSOLE_APPLICATION_H
