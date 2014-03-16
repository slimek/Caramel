// Caramel C++ Library - Trace Facility - Channel Header

#ifndef __CARAMEL_TRACE_CHANNEL_H
#define __CARAMEL_TRACE_CHANNEL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
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
public:

    Channel();


    void Open( const std::string& name, Level level );

    void Write( const std::string& message );


private:

    std::shared_ptr< ChannelImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Trace

} // namespace Caramel

#endif // __CARAMEL_TRACE_CHANNEL_H
