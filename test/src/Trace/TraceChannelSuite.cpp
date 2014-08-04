// Caramel C++ Library Test - Trace - Trace Channel Suite

#include "CaramelTestPch.h"

#include <Caramel/Trace/Channel.h>
#include <Caramel/Trace/Listeners.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( TraceChannelSuite )
{

TEST( ChannelTest )
{
    Trace::Channel channel;
    channel.Open( "Test", Trace::LEVEL_DEBUG );

    Trace::MessageQueue queue;
    queue.BindChannel( channel );

    const std::string alice( "Alice is a dollmaster" );

    channel.Write( alice );

    Trace::Level level = Trace::LEVEL_SILENT;
    std::string msg;
    
    CHECK( true == queue.TryPop( level, msg ));
    CHECK( msg == alice );
}

} // SUITE TraceChannelSuite

} // namespace Caramel
