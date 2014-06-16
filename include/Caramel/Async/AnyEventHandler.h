// Caramel C++ Library - Async Facility - Any Event Handler Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_HANDLER_H
#define __CARAMEL_ASYNC_ANY_EVENT_HANDLER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/AnyEventTarget.h>
#include <functional>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Handler
//

class AnyEventHandler
{
public:

    AnyEventHandler( std::function< void( const AnyEvent& ) > hanlder );
    AnyEventHandler( AnyEventTarget& target );

    void operator()( const AnyEvent& event ) const;


private:

    void InitFromTarget( AnyEventTargetPtr target );

    std::function< void( const AnyEvent& ) > m_handler;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_HANDLER_H
