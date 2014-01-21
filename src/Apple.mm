// Caramel C++ Library - Apple Facility - Implementation
// - This source file is for OS X and iOS

#include "CaramelPch.h"


#if defined( CARAMEL_SYSTEM_OF_APPLE )

#include <Caramel/Apple/LogTraceAdapter.h>
#import <Foundation/NSObjCRuntime.h>


namespace Caramel
{

namespace Apple
{

//
// Contents
//
//   LogTraceAdapter
//

///////////////////////////////////////////////////////////////////////////////
//
// Log Trace Adapter
//

void LogTraceAdapter::Write( Caramel::Trace::Level level, const std::string& message )
{
    NSLog( @"%s", message.c_str() );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Apple

} // namespace Caramel

#endif // CARAMEL_SYSTEM_OF_APPLE
