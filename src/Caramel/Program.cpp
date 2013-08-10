// Caramel C++ Library - Program Facility - Implementation

#include <Caramel/CaramelPch.h>

#include <Caramel/Error/CatchException.h>
#include <Caramel/Program/ConsoleApplication.h>

#include <functional>


namespace Caramel
{

//
// Contents
//
//   ConsoleApplication
//

///////////////////////////////////////////////////////////////////////////////
//
// Console Application
//

Int ConsoleApplication::Run()
{
    auto xc = CatchException( [ this ] { return this->Main(); } );
    return xc.Result();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
