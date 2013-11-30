// Caramel C++ Library Test - Trace - Trace Test

#include "CaramelTestPch.h"

#include <Caramel/Functional/ScopeExit.h>
#include <Caramel/Trace/Listeners.h>
#include <Caramel/Trace/Trace.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( TraceSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Trace Test
//

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


TEST( TraceTest )
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

    CARAMEL_TRACE_DEBUG( "Debug:%d", 1 );
    CHECK( "Debug:1" == lis.Msg() );
    CHECK( Trace::LEVEL_DEBUG == lis.Lv() );

    CARAMEL_TRACE_INFO( "Info:%.1f", 1.0f );
    CHECK( "Info:1.0" == lis.Msg() );
    CHECK( Trace::LEVEL_INFO == lis.Lv() );

    CARAMEL_TRACE_WARN( "Warn:%x", 15 );
    CHECK( "Warn:f" == lis.Msg() );
    CHECK( Trace::LEVEL_WARN == lis.Lv() );

    CARAMEL_TRACE_ERROR( "Error:%s", "wow" );
    CHECK( "Error:wow" == lis.Msg() );
    CHECK( Trace::LEVEL_ERROR == lis.Lv() );


    /// Message with hosting function name ///

    CARAMEL_TRACE_DEBUG_HERE( "Debug" );
    CHECK( __FUNCTION__ " - Debug" == lis.Msg() );
    CHECK( Trace::LEVEL_DEBUG == lis.Lv() );

    CARAMEL_TRACE_INFO_HERE( "Info" );
    CHECK( __FUNCTION__ " - Info" == lis.Msg() );
    CHECK( Trace::LEVEL_INFO == lis.Lv() );

    CARAMEL_TRACE_WARN_HERE( "Warn" );
    CHECK( __FUNCTION__ " - Warn" == lis.Msg() );
    CHECK( Trace::LEVEL_WARN == lis.Lv() );

    CARAMEL_TRACE_ERROR_HERE( "Error" );
    CHECK( __FUNCTION__ " - Error" == lis.Msg() );
    CHECK( Trace::LEVEL_ERROR == lis.Lv() );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE TraceSuite

} // namespace Caramel
