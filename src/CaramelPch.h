// Caramel C++ Library - Precompiled Header

#ifndef __CARAMEL_CARAMEL_PCH_H
#define __CARAMEL_CARAMEL_PCH_H
#pragma once

#include <Caramel/Setup/Compiler.h>
#include <Caramel/Setup/System.h>


///////////////////////////////////////////////////////////////////////////////
//
// Headers
//

// ANSI C++ Headers
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <type_traits>
#include <vector>

// Windows SDK Headers
#if defined( CARAMEL_SYSTEM_IS_WINDOWS )
#include <Windows.h>
#endif

// Caramel Headers
#include <Caramel/Caramel.h>
#include <Caramel/Error/Assert.h>
#include <Caramel/Error/Exception.h>
#include <Caramel/String/Sprintf.h>
#include <Caramel/Trace/Trace.h>


///////////////////////////////////////////////////////////////////////////////

#endif // __CARAMEL_CARAMEL_PCH_H
