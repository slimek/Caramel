// Caramel C++ Library - Program Facility - Console Application Private Header

#ifndef __CARAMEL_PROGRAM_CONSOLE_APPLICATION_IMPL_H
#define __CARAMEL_PROGRAM_CONSOLE_APPLICATION_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Program/ConsoleApplication.h>
#include <Caramel/Trace/Listeners.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Console Application
//

class ConsoleApplicationImpl
{
public:

    ConsoleApplicationImpl();

    void BuildArguments( Int argc, Char* argv[] );

    std::vector< std::string > GetArguments() const { return m_arguments; }


private:

    std::vector< std::string > m_arguments;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_PROGRAM_CONSOLE_APPLICATION_IMPL_H
