// Caramel C++ Library - Trace Facility Implementation

#include <Caramel/CaramelPch.h>

#include <Caramel/Trace/ChannelImpl.h>
#include <Caramel/Trace/Listeners.h>
#include <Caramel/Trace/Trace.h>
#include <Caramel/Trace/TraceManager.h>
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
//
// < Listeners >
//   Listener
//   StdoutListener
//   Listeners
//

///////////////////////////////////////////////////////////////////////////////
//
// Internal Predicates
//

inline static Bool HasBuiltInChannel( Level level )
{
    return Level::DEBUG <= level && level <= Level::ERROR;
}


///////////////////////////////////////////////////////////////////////////////
//
// Trace Manager
//

TraceManager::TraceManager()
{
    m_builtinChannels.insert( std::make_pair( Level::DEBUG, &m_debugChannel ));
    m_builtinChannels.insert( std::make_pair( Level::INFO,  &m_infoChannel ));
    m_builtinChannels.insert( std::make_pair( Level::WARN,  &m_warnChannel ));
    m_builtinChannels.insert( std::make_pair( Level::ERROR, &m_errorChannel ));
}


TraceManager::~TraceManager()
{
    ListenerSet::const_iterator iml = m_managedListeners.begin();
    for ( ; m_managedListeners.end() != iml; ++ iml )
    {
        Listener* listener = *iml;
        this->UnbindListenerFromAllChannels( listener );
    }
}


void TraceManager::BindListenerToBuiltinChannel( Level level, Listener* listener )
{
    CARAMEL_ASSERT( HasBuiltInChannel( level ));

    BuiltinChannel* channel = m_builtinChannels.find( level )->second;
    channel->RegisterListener( listener );
}


void TraceManager::UnbindListenerFromAllChannels( Listener* listener )
{
    BuiltinChannelMap::const_iterator ibc = m_builtinChannels.begin();
    for ( ; m_builtinChannels.end() != ibc; ++ ibc )
    {
        BuiltinChannel* channel = ibc->second;
        channel->TryUnregisterListener( listener );
    }

    NamedChannelMap::const_iterator inc = m_namedChannels.begin();
    for ( ; m_namedChannels.end() != inc; ++ inc )
    {
        ChannelPtr channel = inc->second;
        channel->TryUnregisterListener( listener );
    }
}


void TraceManager::WriteToBuiltinChannel( Level level, const std::string& message )
{
    CARAMEL_ASSERT( HasBuiltInChannel( level ));

    BuiltinChannel* channel = m_builtinChannels.find( level )->second;
    channel->Write( message );
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

void BuiltinChannel::Write( const std::string& message )
{
    ListenerSet::const_iterator i = m_listeners.begin();
    for ( ; m_listeners.end() != i; ++ i )
    {
        Listener* listener = *i;
        listener->Write( message );
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Write Functions
//

void WriteInfo( const std::string& message )
{
    TraceManager::Instance()->WriteToBuiltinChannel( Level::INFO, message );
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


void Listener::BindChannel( Level level )
{
    if ( ! ( HasBuiltInChannel( level )))
    {
        CARAMEL_THROW( "Not level of built-in channel, level: %d", level );
    }

    TraceManager::Instance()->BindListenerToBuiltinChannel( level, this );

    ++ m_boundCount;
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

void StdoutListener::Write( const std::string& message )
{
    std::cout << message << std::endl;
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
