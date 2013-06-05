// Caramel C++ Library - Error Facility - Implementation

#include <Caramel/CaramelPch.h>

#include <Caramel/Error/Exception.h>


namespace Caramel
{

//
// Contents
//
// 1. Exception
//

///////////////////////////////////////////////////////////////////////////////
//
// Exception
//

Exception::Exception(
    Uint line, const std::string& file, const std::string& function, const std::string& what )
  : m_line( line )
  , m_file( file )
  , m_function( function )
  , m_what( what )
{}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel