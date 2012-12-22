// Caramel C++ Library - Trace Facility Implementation

#include <Caramel/CaramelPch.h>

#include <Caramel/Object/Singleton.h>
#include <Caramel/Trace/Trace.h>
#include <Caramel/Trace/TraceManager.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Trace Functions
//

void TraceWrite( Int channelId, const std::string& message )
{
}


void TraceWriteHere( Int channelId, const std::string& function, const std::string& message )
{
}


Mutex& GetTraceMutex()
{
    static Mutex s_mutex;
    return s_mutex;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
