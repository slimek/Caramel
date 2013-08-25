// Caramel C++ Library - Trace Facility - Trace Manager Header

#ifndef __CARAMEL_TRACE_TRACE_MANAGER_H
#define __CARAMEL_TRACE_TRACE_MANAGER_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Object/Singleton.h>
#include <Caramel/Trace/ChannelImpl.h>
#include <Caramel/Trace/Listeners.h>
#include <boost/container/flat_map.hpp>
#include <map>


namespace Caramel
{

namespace Trace
{

///////////////////////////////////////////////////////////////////////////////
//
// Trace Manager
//

class TraceManager : public Singleton< TraceManager >
{
public:

    TraceManager();

    void BindListenerToBuiltinChannel( Level level, Listener* listener );
    
    void UnbindListenerFromAllChannels( Listener* listener );

    void WriteToBuiltinChannel( Level level, const std::string& message );


private:

    /// Built-in Channels ///

    BuiltinChannel m_debugChannel;
    BuiltinChannel m_infoChannel;
    BuiltinChannel m_warnChannel;
    BuiltinChannel m_errorChannel;

    typedef boost::container::flat_map< Level, BuiltinChannel* > BuiltinChannelMap;
    BuiltinChannelMap m_builtinChannels;


    /// User-defined Channels - Accessed by names ///

    typedef std::map< std::string, ChannelPtr > NamedChannelMap;
    NamedChannelMap m_namedChannels;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Trace

} // namespace Caramel

#endif // __CARAMEL_TRACE_TRACE_MANAGER_H
