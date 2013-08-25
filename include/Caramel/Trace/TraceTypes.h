// Caramel C++ Library - Trace Facility - Trace Types Header

#ifndef __CARAMEL_TRACE_TRACE_TYPES_H
#define __CARAMEL_TRACE_TRACE_TYPES_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


namespace Caramel
{

namespace Trace
{

///////////////////////////////////////////////////////////////////////////////
//
// Enumerations
//

//
// Level of Severity
// - The higher value, the more important.
//
enum class Level : Int
{
    SILENT  = 0,  // Set channel to be silent

    VERBOSE = 1,
    DEBUG   = 2,
    INFO    = 3,
    WARN    = 4,
    ERROR   = 5,

    DEAF    = 6,  // Set listener to be deaf


    /// Aliases ///

    CHANNEL_DISABLED  = SILENT,
    LISTENER_DISABLED = DEAF,
};


///////////////////////////////////////////////////////////////////////////////
//
// Forwards Declaration
//

class Channel;
class Listener;


///////////////////////////////////////////////////////////////////////////////

} // namespace Trace

} // namespace Caramel

#endif // __CARAMEL_TRACE_TRACE_TYPES_H
