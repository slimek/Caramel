// Caramel C++ Library - Program Facility - Implementation

#include <Caramel/CaramelPch.h>

#include <Caramel/Error/CatchException.h>
#include <Caramel/Program/ConsoleApplication.h>
#include <functional>
#include <iostream>


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
    if ( xc )
    {
        std::cout << std::endl
                  << "Program caught an exception and exit abnormally." << std::endl;
        std::cin.get();
    }
    return xc.Result();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
