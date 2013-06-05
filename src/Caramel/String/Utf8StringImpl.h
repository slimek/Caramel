// Caramel C++ Library - String Facility - UTF-8 String Private Header

#ifndef __CARAMEL_STRING_UTF8_STRING_IMPL_H
#define __CARAMEL_STRING_UTF8_STRING_IMPL_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Object/Singleton.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// UTF-8 String Manager
// - Provides the UTF-8 coding validation.
// 

class Utf8StringManager : public Singleton< Utf8StringManager >
{
public:
    
    Bool Validate( const std::string& input );

private:

    
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_UTF8_STRING_IMPL_H
