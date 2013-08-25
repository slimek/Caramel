// Caramel C++ Library - Trace Facility - Channel Private Header

#ifndef __CARAMEL_TRACE_CHANNEL_IMPL_H
#define __CARAMEL_TRACE_CHANNEL_IMPL_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Trace/Channel.h>
#include <Caramel/Trace/Listeners.h>
#include <boost/container/flat_set.hpp>


namespace Caramel
{

namespace Trace
{

///////////////////////////////////////////////////////////////////////////////
//
// Channel
//

class ChannelImpl
{
public:

    void RegisterListener( Listener* listener );
    
    // Returns false if listener not found.
    Bool TryUnregisterListener( Listener* listener );


protected:

    typedef boost::container::flat_set< Listener* > ListenerSet;
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

    void Write( const std::string& message );
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Trace

} // namespace Caramel

#endif // __CARAMEL_TRACE_CHANNEL_IMPL_H
