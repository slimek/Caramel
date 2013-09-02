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

class ConsoleApplication
{
public:

    ConsoleApplication();

    Int Run();

private:

    virtual Int Main() = 0;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_PROGRAM_CONSOLE_APPLICATION_H
