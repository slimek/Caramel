// Caramel C++ Library - Trace Facility - Trace Manager Header

#ifndef __CARAMEL_TRACE_TRACE_MANAGER_H
#define __CARAMEL_TRACE_TRACE_MANAGER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Object/FacilityLongevity.h"
#include "Trace/ChannelImpl.h"
#include <Caramel/Object/Singleton.h>
#include <Caramel/Trace/Listeners.h>
#include <boost/container/flat_map.hpp>
#include <boost/bimap/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <map>
#include <mutex>
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


    // You would bind a listener to built-in channels all above the minLevel.
    void BindListenerToBuiltinChannels( Level minLevel, Listener* listener );
    
    void BindListenerToNamedChannel( const std::string& channelName, Listener* listener );

    void UnbindListenerFromAllChannels( Listener* listener );

    void WriteToBuiltinChannel( Level level, const std::string& message );


    /// Managed Listener ///

    void AddManagedListener( Listener* listener );


    /// Named Channels ///

    void AddNamedChannel( ChannelPtr channel );
    void RemoveNamedChannel( ChannelPtr channel );


private:

    /// Built-in Channels ///

    BuiltinChannel m_debugChannel;
    BuiltinChannel m_infoChannel;
    BuiltinChannel m_warnChannel;
    BuiltinChannel m_errorChannel;

    typedef boost::container::flat_map< Level, BuiltinChannel* > BuiltinChannelMap;
    BuiltinChannelMap m_builtinChannels;


    /// User-defined Channels - Accessed by names ///

    mutable std::mutex m_namedChannelsMutex;

    // Boost.Bimap< Name, Channel >
    typedef boost::bimaps::bimap<
        boost::bimaps::set_of< std::string >,
        boost::bimaps::set_of< ChannelPtr >
    > NamedChannelMap;

    typedef NamedChannelMap::value_type NamedChannelEntry;

    NamedChannelMap m_namedChannels;


    /// Managed Listeners ///

    typedef std::set< Listener* > ListenerSet;
    ListenerSet m_managedListeners;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Trace

} // namespace Caramel

#endif // __CARAMEL_TRACE_TRACE_MANAGER_H
