// Caramel C++ Library Test - Trace - Trace Suite

#include "CaramelTestPch.h"

#include <Caramel/Functional/ScopeExit.h>
#include <Caramel/Trace/Listeners.h>
#include <Caramel/Trace/Trace.h>


namespace Caramel
{

SUITE( Trace )
{

class LocalListener : public Trace::Listener
{
public:
    void Write( Trace::Level lv, const std::string& message )
    {
        m_level = lv;
        m_message = message;
    }

    Trace::Level Lv()  const { return m_level; }
    std::string  Msg() const { return m_message; }

private:
    Trace::Level m_level;
    std::string m_message;
};


TEST( TraceMacroStyle )
{
    LocalListener lis;
    lis.BindBuiltinChannels( Trace::LEVEL_DEBUG );
    auto guard = ScopeExit( [&] { lis.UnbindAllChannels(); } );

    /// Message with no argument ///

    CARAMEL_TRACE_DEBUG( "Debug" );
    CHECK( "Debug" == lis.Msg() );
    CHECK( Trace::LEVEL_DEBUG == lis.Lv() );

    CARAMEL_TRACE_INFO( "Info" );
    CHECK( "Info" == lis.Msg() );
    CHECK( Trace::LEVEL_INFO == lis.Lv() );

    CARAMEL_TRACE_WARN( "Warn" );
    CHECK( "Warn" == lis.Msg() );
    CHECK( Trace::LEVEL_WARN == lis.Lv() );

    CARAMEL_TRACE_ERROR( "Error" );
    CHECK( "Error" == lis.Msg() );
    CHECK( Trace::LEVEL_ERROR == lis.Lv() );


    /// Message with one argument ///

    CARAMEL_TRACE_DEBUG( "Debug:{0}", 1 );
    CHECK( "Debug:1" == lis.Msg() );
    CHECK( Trace::LEVEL_DEBUG == lis.Lv() );

    CARAMEL_TRACE_INFO( "Info:{0:F1}", 1.0f );
    CHECK( "Info:1.0" == lis.Msg() );
    CHECK( Trace::LEVEL_INFO == lis.Lv() );

    CARAMEL_TRACE_WARN( "Warn:{0:x}", 15 );
    CHECK( "Warn:f" == lis.Msg() );
    CHECK( Trace::LEVEL_WARN == lis.Lv() );

    CARAMEL_TRACE_ERROR( "Error:{0}", "wow" );
    CHECK( "Error:wow" == lis.Msg() );
    CHECK( Trace::LEVEL_ERROR == lis.Lv() );
}


TEST( TraceFunctionStyle )
{
    LocalListener lis;
    lis.BindBuiltinChannels( Trace::LEVEL_DEBUG );
    auto guard = ScopeExit( [&] { lis.UnbindAllChannels(); } );

    /// Message with no argument ///

    TraceDebug( "Debug" );
    CHECK( "Debug" == lis.Msg() );
    CHECK( Trace::LEVEL_DEBUG == lis.Lv() );

    TraceInfo( "Info" );
    CHECK( "Info" == lis.Msg() );
    CHECK( Trace::LEVEL_INFO == lis.Lv() );

    TraceWarn( "Warn" );
    CHECK( "Warn" == lis.Msg() );
    CHECK( Trace::LEVEL_WARN == lis.Lv() );

    TraceError( "Error" );
    CHECK( "Error" == lis.Msg() );
    CHECK( Trace::LEVEL_ERROR == lis.Lv() );


    /// Message with arguments ///

    TraceDebug( "Debug:{0}", 1 );
    CHECK( "Debug:1" == lis.Msg() );
    CHECK( Trace::LEVEL_DEBUG == lis.Lv() );

    TraceInfo( "Info:{0:F1} {1:F2}", 1.0f, 0.75f );
    CHECK( "Info:1.0 0.75" == lis.Msg() );
    CHECK( Trace::LEVEL_INFO == lis.Lv() );

    TraceWarn( "Warn:{0:x}", 15 );
    CHECK( "Warn:f" == lis.Msg() );
    CHECK( Trace::LEVEL_WARN == lis.Lv() );

    TraceError( "Error:{0} {1}", "Alice", "Marisa" );
    CHECK( "Error:Alice Marisa" == lis.Msg() );
    CHECK( Trace::LEVEL_ERROR == lis.Lv() );
}


TEST( TraceMessageQueue )
{
    using namespace Trace;

    MessageQueue queue;
    queue.BindBuiltinChannels( LEVEL_DEBUG );
    auto guard = ScopeExit( [&] { queue.UnbindAllChannels(); } );

    Level level = LEVEL_SILENT;
    std::string message;

    CHECK( false == queue.TryPop( level, message ));

    CARAMEL_TRACE_INFO( "Alice" );

    CHECK( true == queue.TryPop( level, message ));
    CHECK( LEVEL_INFO == level && "Alice" == message );
    CHECK( false == queue.TryPop( level, message ));

    CARAMEL_TRACE_ERROR( "Reimu" );
    CARAMEL_TRACE_WARN( "Marisa" );

    CHECK( true == queue.TryPop( level, message ));
    CHECK( LEVEL_ERROR == level && "Reimu" == message );
    CHECK( true == queue.TryPop( level, message ));
    CHECK( LEVEL_WARN == level && "Marisa" == message );
    CHECK( false == queue.TryPop( level, message ));
}


} // SUITE Trace

} // namespace Caramel
