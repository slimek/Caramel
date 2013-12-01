// Caramel C++ Library - Trace Facility - Trace Types Header

#ifndef __CARAMEL_TRACE_TRACE_TYPES_H
#define __CARAMEL_TRACE_TRACE_TYPES_H
#pragma once

#include <Caramel/Caramel.h>


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
enum Level : Int
{
    LEVEL_SILENT  = 0,  // Set channel to be silent

    LEVEL_VERBOSE = 1,
    LEVEL_DEBUG   = 2,
    LEVEL_INFO    = 3,
    LEVEL_WARN    = 4,
    LEVEL_ERROR   = 5,

    LEVEL_DEAF    = 6,  // Set listener to be deaf

    LEVEL_INVALID = -1,


    /// Aliases ///

    LEVEL_CHANNEL_DISABLED  = LEVEL_SILENT,
    LEVEL_LISTENER_DISABLED = LEVEL_DEAF,
};


/// Supporting Routings ///

//
// EXAMPLE: input DEBUG => output INFO
//   
Level NextLevel( Level lv );


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
