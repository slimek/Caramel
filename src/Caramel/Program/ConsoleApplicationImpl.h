// Caramel C++ Library - Program Facility - Console Application Private Header

#ifndef __CARAMEL_PROGRAM_CONSOLE_APPLICATION_IMPL_H
#define __CARAMEL_PROGRAM_CONSOLE_APPLICATION_IMPL_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

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

private:

    // The ownership of this listener would be passed to Trace facility.
    Trace::StdoutListener* m_stdoutListener;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_PROGRAM_CONSOLE_APPLICATION_IMPL_H
