// Caramel C++ Library - Trace Facility - Channel Private Header

#ifndef __CARAMEL_TRACE_CHANNEL_IMPL_H
#define __CARAMEL_TRACE_CHANNEL_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Concurrent/FlatSet.h>
#include <Caramel/Trace/Channel.h>
#include <Caramel/Trace/Listeners.h>
#include <mutex>


namespace Caramel
{

namespace Trace
{

///////////////////////////////////////////////////////////////////////////////
//
// Channel
//

class ChannelImpl : public std::enable_shared_from_this< ChannelImpl >
{
public:

    void Open( const std::string& name, Level level );

    void Write( const std::string& message );


    /// Listeners ///
    
    void RegisterListener( Listener* listener );
    
    // Returns false if listener not found.
    Bool TryUnregisterListener( Listener* listener );


    /// Properties ///

    std::string GetName() const;

protected:

    mutable std::mutex m_mutex;

    std::string m_name;
    Level m_level { LEVEL_SILENT };

    typedef Concurrent::FlatSetWithSnapshot< Listener* > ListenerSet;
    ListenerSet m_listeners;
};

typedef std::shared_ptr< ChannelImpl > ChannelPtr;


///////////////////////////////////////////////////////////////////////////////
//
// Built-in Channel
// - A built-in channel is also a listener of user-defined channels.
//

class BuiltinChannel : public ChannelImpl
                     , public Listener
{
public:

    /// Implements Listener ///

    void Write( Level level, const std::string& message ) override;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Trace

} // namespace Caramel

#endif // __CARAMEL_TRACE_CHANNEL_IMPL_H
