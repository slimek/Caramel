// Caramel C++ Library Test - Trace - Trace Channel Suite

#include "CaramelTestPch.h"

#include <Caramel/Trace/Channel.h>
#include <Caramel/Trace/Listeners.h>


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
    CHECK( level = Trace::LEVEL_DEBUG );

    
    /// Write with Sprintf ///

    channel.Write( "Youmu has {0} katanas", 2 );

    CHECK( true == queue.TryPop( level, msg ));
    CHECK( "Youmu has 2 katanas" == msg );

    channel.Write( "{0} and {1} are both Witches", "Alice", "Marisa" );

    CHECK( true == queue.TryPop( level, msg ));
    CHECK( "Alice and Marisa are both Witches" );
}


TEST( BindChannelByNameTest )
{
    Trace::Channel channel;
    channel.Open( "ByName", Trace::LEVEL_DEBUG );


    /// Bind a channel by name ///

    Trace::MessageQueue queue;
    queue.BindChannelByName( "ByName" );

    const std::string reimu( "Reimu is a miko" );
    channel.Write( reimu );

    Trace::Level level = Trace::LEVEL_SILENT;
    std::string msg;

    CHECK( true == queue.TryPop( level, msg ));
    CHECK( msg == reimu );
}


} // SUITE TraceChannelSuite

} // namespace Caramel
