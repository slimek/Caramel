// Caramel C++ Library - Trace Facility - Trace Header

#ifndef __CARAMEL_TRACE_TRACE_H
#define __CARAMEL_TRACE_TRACE_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/String/Format.h>
#include <Caramel/Trace/TraceTypes.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// General Trace Functions
//

template< typename... Args >
void TraceDebug( const std::string& format, Args&&... args );

template< typename... Args >
void TraceInfo( const std::string& format, Args&&... args );

template< typename... Args >
void TraceWarn( const std::string& format, Args&&... args );

template< typename... Args >
void TraceError( const std::string& format, Args&&... args );


///////////////////////////////////////////////////////////////////////////////
//
// Write to Built-in Channels
//

namespace Trace
{

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


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename... Args >
inline void TraceDebug( const std::string& format, Args&&... args )
{
    try
    {
        Trace::WriteToBuiltin(
            Trace::LEVEL_DEBUG, Format( format, std::forward< Args >( args )... ));
    }
    catch ( ... )
    {
        Trace::WriteToBuiltinFailed( format );
    }
}


template< typename... Args >
inline void TraceInfo( const std::string& format, Args&&... args )
{
    try
    {
        Trace::WriteToBuiltin(
            Trace::LEVEL_INFO, Format( format, std::forward< Args >( args )... ));
    }
    catch ( ... )
    {
        Trace::WriteToBuiltinFailed( format );
    }
}


template< typename... Args >
inline void TraceWarn( const std::string& format, Args&&... args )
{
    try
    {
        Trace::WriteToBuiltin(
            Trace::LEVEL_WARN, Format( format, std::forward< Args >( args )... ));
    }
    catch ( ... )
    {
        Trace::WriteToBuiltinFailed( format );
    }
}


template< typename... Args >
inline void TraceError( const std::string& format, Args&&... args )
{
    try
    {
        Trace::WriteToBuiltin(
            Trace::LEVEL_ERROR, Format( format, std::forward< Args >( args )... ));
    }
    catch ( ... )
    {
        Trace::WriteToBuiltinFailed( format );
    }
}


} // namespace Caramel

///////////////////////////////////////////////////////////////////////////////
//
// Trace Macros
//

#define CARAMEL_TRACE_DEBUG( format_message, ... ) \
    Caramel::TraceDebug( format_message, ##__VA_ARGS__ )

#define CARAMEL_TRACE_INFO( format_message, ... ) \
    Caramel::TraceInfo( format_message, ##__VA_ARGS__ )

#define CARAMEL_TRACE_WARN( format_message, ... ) \
    Caramel::TraceWarn( format_message, ##__VA_ARGS__ )

#define CARAMEL_TRACE_ERROR( format_message, ... ) \
    Caramel::TraceError( format_message, ##__VA_ARGS__ )


///////////////////////////////////////////////////////////////////////////////

#endif // __CARAMEL_TRACE_TRACE_H

