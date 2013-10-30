// Caramel C++ Library - Trace Facility - Trace Manager Header

#ifndef __CARAMEL_TRACE_TRACE_MANAGER_H
#define __CARAMEL_TRACE_TRACE_MANAGER_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include "Object/FacilityLongevity.h"
#include "Trace/ChannelImpl.h"
#include <Caramel/Object/Singleton.h>
#include <Caramel/Trace/Listeners.h>
#include <boost/container/flat_map.hpp>
#include <map>
#include <set>


namespace Caramel
{

namespace Trace
{

///////////////////////////////////////////////////////////////////////////////
//
// Trace Manager
//

class TraceManager : public Singleton< TraceManager, FACILITY_LONGEVITY_TRACE >
{
public:

    TraceManager();
    ~TraceManager();

    //
    // You would bind a listener to built-in channels all above the level.
    //
    void BindListenerToBuiltinChannels( Level minLevel, Listener* listener );
    
    void UnbindListenerFromAllChannels( Listener* listener );

    void WriteToBuiltinChannel( Level level, const std::string& message );

    void AddManagedListener( Listener* listener );


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


    /// Managed Listeners ///

    typedef std::set< Listener* > ListenerSet;
    ListenerSet m_managedListeners;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Trace

} // namespace Caramel

#endif // __CARAMEL_TRACE_TRACE_MANAGER_H
