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

#define CARAMEL_ASSERT( expr ) ( (void)0 )

#define CARAMEL_VERIFY( expr ) ( expr )

#else  // NDEBUG

#define CARAMEL_ASSERT( expr ) \
    if ( !( expr )) { CARAMEL_THROW1( "Assertion failed : \"" #expr "\"" ); }

#define CARAMEL_VERIFY( expr ) CARAMEL_ASSERT( expr )

#endif // NDEBUG 


//
// Check Macros - Always on even in Release build
//

#define CARAMEL_CHECK( expr ) \
    if ( !( expr )) { CARAMEL_THROW1( "Checking failed : \"" #expr "\"" ); }


///////////////////////////////////////////////////////////////////////////////

#endif // __CARAMEL_ERROR_ASSERT_H
