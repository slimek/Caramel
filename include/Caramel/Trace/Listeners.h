// Caramel C++ Library - Trace Facility - Listeners Header

#ifndef __CARAMEL_TRACE_LISTENERS_H
#define __CARAMEL_TRACE_LISTENERS_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Trace/TraceTypes.h>


namespace Caramel
{

namespace Trace
{

///////////////////////////////////////////////////////////////////////////////
//
// Listener
// - Abstract class
//

class ListenerImpl;

class Listener
{
public:

    Listener();
    virtual ~Listener();

    virtual void Write( Level level, const std::string& message ) = 0;


    //
    // Bind listener to channels
    //

    // Bind to built-in channels all above the level.
    void BindBuiltinChannels( Level minLevel );

    void BindChannelByName( const std::string& channelName );

    // Bind to channel directly
    void BindChannel( Channel& channel );

    // Must be called before destroyed.
    void UnbindAllChannels();


private:

    Int m_boundCount;
};


///////////////////////////////////////////////////////////////////////////////
//
// Stdout Listener
// - Output trace to std::cout.
//

class StdoutListener : public Listener
{
public:

    void Write( Level level, const std::string& message ) override;
};


///////////////////////////////////////////////////////////////////////////////
//
// Listeners
// - The listeners management of the whole facility.
//

class Listeners
{
public:
    
    static void AddManaged( Listener* listener );
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Trace

} // namespace Caramel

#endif // __CARAMEL_TRACE_LISTENERS_H
