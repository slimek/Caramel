// Caramel C++ Library - Libary Setup - Version Desination

#ifndef __CARAMEL_SETUP_VERSION_H
#define __CARAMEL_SETUP_VERSION_H


//
// Current Version
//

#define CARAMEL_VERSION_MAJOR 1
#define CARAMEL_VERSION_MINOR 2
#define CARAMEL_VERSION_BUILD 0


//
// Version Validation Example
// - In Debug, minor version should be backwards compatibility.
//   In Release, all numbers must be matched.
//
// #if defined( NDEBUG )
//
// static_assert(
//   CARAMEL_VERSION_MAJOR == 1 &&
//   CARAMEL_VERSION_MINOR == 0 &&
//   CARAMEL_VERSION_BUILD == 0,
//   "Caramel version not matched" );
//
// #else
//
// static_assert(
//   CARAMEL_VERSION_MAJOR == 1 &&
//   CARAMEL_VERSION_MINOR >= 0,
//   "Caramel version not compatible );
//
// #endif // NDEBUG
//


#endif // __CARAMEL_SETUP_VERSION_H
