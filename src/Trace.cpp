// Caramel C++ Library - Trace Facility Implementation

#include "CaramelPch.h"

#include "Trace/ChannelImpl.h"
#include "Trace/ListenersImpl.h"
#include "Trace/TraceManager.h"
#include <Caramel/Trace/Listeners.h>
#include <Caramel/Trace/Trace.h>
#include <iostream>


namespace Caramel
{

namespace Trace
{

//
// Contents
//
//   TraceManager
//   Channel
//   BuiltinChannel
//   Write functions
//   Level
//
// < Listeners >
//   Listener
//   StdoutAdapter
//   MessageQueue
//   Listeners
//

///////////////////////////////////////////////////////////////////////////////
//
// Trace Manager
//

TraceManager::TraceManager()
{
    m_builtinChannels.insert( std::make_pair( LEVEL_DEBUG, &m_debugChannel ));
    m_builtinChannels.insert( std::make_pair( LEVEL_INFO,  &m_infoChannel ));
    m_builtinChannels.insert( std::make_pair( LEVEL_WARN,  &m_warnChannel ));
    m_builtinChannels.insert( std::make_pair( LEVEL_ERROR, &m_errorChannel ));
}


TraceManager::~TraceManager()
{
    for ( Listener* listener : m_managedListeners )
    {
        listener->UnbindAllChannels();
        delete listener;
    }
}


void TraceManager::BindListenerToBuiltinChannels( Level minLevel, Listener* listener )
{
    CARAMEL_ASSERT( ExistsBuiltinChannel( minLevel ));

    Level level = minLevel;
    while ( LEVEL_ERROR >= level )
    {
        BuiltinChannel* channel = m_builtinChannels.find( level )->second;
        channel->RegisterListener( listener );

        level = NextLevel( level );
    }
}


void TraceManager::UnbindListenerFromAllChannels( Listener* listener )
{
    for ( const auto& ibc : m_builtinChannels )
    {
        BuiltinChannel* channel = ibc.second;
        channel->TryUnregisterListener( listener );
    }

    for ( const auto& inc : m_namedChannels )
    {
        ChannelPtr channel = inc.second;
        channel->TryUnregisterListener( listener );
    }
}


void TraceManager::WriteToBuiltinChannel( Level level, const std::string& message )
{
    CARAMEL_ASSERT( ExistsBuiltinChannel( level ));

    BuiltinChannel* channel = m_builtinChannels.find( level )->second;
    channel->Write( level, message );
}


void TraceManager::AddManagedListener( Listener* listener )
{
    const Bool inserted = m_managedListeners.insert( listener ).second;
    if ( ! inserted )
    {
        CARAMEL_THROW( "Listener is duplicate" );
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Channel
//

Channel::Channel()
    : m_impl( new ChannelImpl )
{
}


void Channel::Open( const std::string& name, Trace::Level level )
{
    CARAMEL_NOT_IMPLEMENTED();
}


void Channel::Write( const std::string& message )
{
    CARAMEL_NOT_IMPLEMENTED();
}


//
// Implementation
//

void ChannelImpl::RegisterListener( Listener* listener )
{
    const Bool inserted = m_listeners.insert( listener ).second;
    if ( ! inserted )
    {
        CARAMEL_THROW( "Listener is duplicate" );
    }
}


Bool ChannelImpl::TryUnregisterListener( Listener* listener )
{
    ListenerSet::iterator i = m_listeners.find( listener );
    if ( m_listeners.end() == i )
    {
        return false;
    }
    else
    {
        m_listeners.erase( i );
        return true;
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Built-in Channel
//

void BuiltinChannel::Write( Level level, const std::string& message )
{
    for ( Listener* listener : m_listeners )
    {
        listener->Write( level, message );
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Write Functions
//

void WriteToBuiltin( Level level, const std::string& message )
{
    // Built-in channels don't accept level lower than DEBUG.
    if ( LEVEL_DEBUG > level ) { return; }

    // Treats level greater than ERROR as ERROR.
    if ( LEVEL_ERROR < level )
    {
        level = LEVEL_ERROR;
    }

    TraceManager::Instance()->WriteToBuiltinChannel( level, message );
}


void WriteToBuiltinFailed( const std::string& message )
{
    TraceManager::Instance()->WriteToBuiltinChannel( LEVEL_WARN, message + " (Trace::Write() failed)" );
}


///////////////////////////////////////////////////////////////////////////////
//
// Level
//

Level NextLevel( Level inputLevel )
{
    if ( ! ( LEVEL_SILENT <= inputLevel && inputLevel < LEVEL_DEAF ))
    {
        return LEVEL_INVALID;
    }

    if ( LEVEL_DEAF == inputLevel )
    {
        return LEVEL_DEAF;
    }

    return static_cast< Level >( static_cast< Int >( inputLevel ) + 1 );

}


Bool ExistsBuiltinChannel( Level level )
{
    return LEVEL_DEBUG <= level && level <= LEVEL_ERROR;
}


///////////////////////////////////////////////////////////////////////////////
//
// Listener
//

Listener::Listener()
    : m_boundCount( 0 )
{
}


Listener::~Listener()
{
    if ( 0 < m_boundCount )
    {
        CARAMEL_THROW( "Listener doesn't unbind all channels before destroyed" );
    }
}


void Listener::BindBuiltinChannels( Level minLevel )
{
    if ( ! ( ExistsBuiltinChannel( minLevel )))
    {
        CARAMEL_THROW( "Not level of built-in channel, minLevel: %d", minLevel );
    }

    TraceManager::Instance()->BindListenerToBuiltinChannels( minLevel, this );

    ++ m_boundCount;
}


void Listener::BindChannelByName( const std::string& channelName )
{
}


void Listener::BindChannel( Channel& channel )
{
    
}


void Listener::UnbindAllChannels()
{
    TraceManager::Instance()->UnbindListenerFromAllChannels( this );

    m_boundCount = 0;
}


///////////////////////////////////////////////////////////////////////////////
//
// Stdout Listener
//

void StdoutAdapter::Write( Level, const std::string& message )
{
    std::cout << message << std::endl;
}


///////////////////////////////////////////////////////////////////////////////
//
// Message Queue
//

MessageQueue::MessageQueue()
    : m_impl( new MessageQueueImpl )
{
}


void MessageQueue::Write( Level level, const std::string& message )
{
    m_impl->m_queue.Push( MessageEntry( level, message ));
}


Bool MessageQueue::TryPop( Level& level, std::string& message )
{
    MessageEntry entry;
    if ( m_impl->m_queue.TryPop( entry ))
    {
        level = entry.level;
        message = entry.message;
        return true;
    }
    else
    {
        return false;
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Listeners
//

void Listeners::AddManaged( Listener* listener )
{
    TraceManager::Instance()->AddManagedListener( listener );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Trace

} // namespace Caramel
