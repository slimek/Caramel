// Caramel C++ Library - Error Facility - Assert Header

#ifndef __CARAMEL_ERROR_ASSERT_H
#define __CARAMEL_ERROR_ASSERT_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Error/Alert.h>
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
    if ( !( expr )) \
    { \
        Caramel::Alert( __LINE__, __FILE__, __FUNCTION__, #expr ); \
    }

#define CARAMEL_VERIFY( expr ) CARAMEL_ASSERT( expr )

#endif // NDEBUG 


//
// Check Macros - Always on even in Release build
//

#define CARAMEL_CHECK( expr ) \
    if ( !( expr )) { CARAMEL_THROW1( "Checking failed : \"" #expr "\"" ); }

#define CARAMEL_CHECK_MSG( expr, ... ) \
    if ( !( expr )) { CARAMEL_THROW( __VA_ARGS__ ); }


///////////////////////////////////////////////////////////////////////////////

#endif // __CARAMEL_ERROR_ASSERT_H
