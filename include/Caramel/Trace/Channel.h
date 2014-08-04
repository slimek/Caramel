// Caramel C++ Library - Trace Facility - Channel Header

#ifndef __CARAMEL_TRACE_CHANNEL_H
#define __CARAMEL_TRACE_CHANNEL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/String/Sprintf.h>
#include <Caramel/Trace/TraceTypes.h>


namespace Caramel
{

namespace Trace
{

///////////////////////////////////////////////////////////////////////////////
//
// Channel
//

class ChannelImpl;

class Channel
{
    friend class Listener;

public:

    Channel();


    void Open( const std::string& name, Level level );

    void Write( const std::string& message );

    template< typename... Args >
    void Write( const std::string& format, Args&&... args );


private:

    std::shared_ptr< ChannelImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename... Args >
inline void Channel::Write( const std::string& format, Args&&... args )
{
    this->Write( Sprintf( format, std::forward< Args >( args )... ));
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Trace

} // namespace Caramel

#endif // __CARAMEL_TRACE_CHANNEL_H
