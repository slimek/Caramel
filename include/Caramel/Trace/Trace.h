// Caramel C++ Library - Trace Facility - Trace Header

#ifndef __CARAMEL_TRACE_TRACE_H
#define __CARAMEL_TRACE_TRACE_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/String/Sprintf.h>
#include <Caramel/Trace/TraceTypes.h>


namespace Caramel
{

namespace Trace
{

///////////////////////////////////////////////////////////////////////////////
//
// Write to Built-in Channels
//

//
// Level of bulit-in channels are DEBUG, INFO, WARN and ERROR.
//
void WriteToBuiltin( Level level, const std::string& message );


//
// Write failed usually caused by invalid Sprintf() parameters.
// This message would be WARN level.
//
void WriteToBuiltinFailed( const std::string& message );


} // namespace Trace

} // namespace Caramel

///////////////////////////////////////////////////////////////////////////////
//
// Trace Macros
//

#define CARAMEL_TRACE_WRITE_TO_BUILTIN( level, format_message, ... ) \
    { \
        try { \
            Caramel::Trace::WriteToBuiltin( level, Caramel::Sprintf( format_message, ##__VA_ARGS__ )); \
        } catch ( ... ) { \
            Caramel::Trace::WriteToBuiltinFailed( format_message ); \
        } \
    }


#define CARAMEL_TRACE_DEBUG( format_message, ... ) \
    CARAMEL_TRACE_WRITE_TO_BUILTIN( Caramel::Trace::LEVEL_DEBUG, format_message, ##__VA_ARGS__ )

#define CARAMEL_TRACE_INFO( format_message, ... ) \
    CARAMEL_TRACE_WRITE_TO_BUILTIN( Caramel::Trace::LEVEL_INFO, format_message, ##__VA_ARGS__ )

#define CARAMEL_TRACE_WARN( format_message, ... ) \
    CARAMEL_TRACE_WRITE_TO_BUILTIN( Caramel::Trace::LEVEL_WARN, format_message, ##__VA_ARGS__ )

#define CARAMEL_TRACE_ERROR( format_message, ... ) \
    CARAMEL_TRACE_WRITE_TO_BUILTIN( Caramel::Trace::LEVEL_ERROR, format_message, ##__VA_ARGS__ )


//
// Write Trace with Location
// - The format_message must be string literal.
//

#define CARAMEL_TRACE_DEBUG_HERE( format_message, ... ) \
    CARAMEL_TRACE_WRITE_TO_BUILTIN( Caramel::Trace::LEVEL_DEBUG, "%s - " format_message, __FUNCTION__, ##__VA_ARGS__ )

#define CARAMEL_TRACE_INFO_HERE( format_message, ... ) \
    CARAMEL_TRACE_WRITE_TO_BUILTIN( Caramel::Trace::LEVEL_INFO, "%s - " format_message, __FUNCTION__, ##__VA_ARGS__ )

#define CARAMEL_TRACE_WARN_HERE( format_message, ... ) \
    CARAMEL_TRACE_WRITE_TO_BUILTIN( Caramel::Trace::LEVEL_WARN, "%s - " format_message, __FUNCTION__, ##__VA_ARGS__ )

#define CARAMEL_TRACE_ERROR_HERE( format_message, ... ) \
    CARAMEL_TRACE_WRITE_TO_BUILTIN( Caramel::Trace::LEVEL_ERROR, "%s - " format_message, __FUNCTION__, ##__VA_ARGS__ )


///////////////////////////////////////////////////////////////////////////////



#endif // __CARAMEL_TRACE_TRACE_H

