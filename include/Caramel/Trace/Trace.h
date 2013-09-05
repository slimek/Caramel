// Caramel C++ Library - Trace Facility - Trace Header

#ifndef __CARAMEL_TRACE_TRACE_H
#define __CARAMEL_TRACE_TRACE_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

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

void WriteDebug( const std::string& message );
void WriteInfo ( const std::string& message );
void WriteWarn ( const std::string& message );
void WriteError( const std::string& message );

//
// Level of bulit-in channels are DEBUG, INFO, WARN and ERROR.
//
void WriteToBuiltin( Level level, const std::string& message );


} // namespace Trace

} // namespace Caramel

///////////////////////////////////////////////////////////////////////////////
//
// Trace Macros
//

#define CARAMEL_TRACE_INFO( format_message, ... ) \
    Caramel::Trace::WriteInfo( Sprintf( format_message, __VA_ARGS__ ))


///////////////////////////////////////////////////////////////////////////////



#endif // __CARAMEL_TRACE_TRACE_H

