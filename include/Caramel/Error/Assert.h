// Caramel C++ Library - Error Facility - Assert Header

#ifndef __CARAMEL_ERROR_ASSERT_H
#define __CARAMEL_ERROR_ASSERT_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Error/Exception.h>


///////////////////////////////////////////////////////////////////////////////
//
// Assertion Macros
//

#if defined( NDEBUG )

#define CARAMEL_ASSERT( expr ) ((void)0)

#else  // NDEBUG

#define CARAMEL_ASSERT( expr ) \
    if ( !( expr )) { CARAMEL_THROW( "Assertion failed : \"" #expr "\"" );  }

#endif // NDEBUG 


///////////////////////////////////////////////////////////////////////////////

#endif // __CARAMEL_ERROR_ASSERT_H
