// Caramel C++ Library - Async Facility - Any Event Handler Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_HANDLER_H
#define __CARAMEL_ASYNC_ANY_EVENT_HANDLER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/AnyEventTarget.h>
#include <boost/utility/enable_if.hpp>
#include <functional>
#include <type_traits>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Handler
// - This is a wrapper of two types of "handlers":
//   
//   1. The derived classes of AnyEventTarget.
//   2. Any callable convertible to std::function< void( const AnyEvent& ) >.
//
//   USAGE:
//   
//   Suppose we have a MyResponse class which post an AnyEvent to reply data:
//
//   class MyResponse
//   {
//   public:
//       MyResponse( AnyEventHandler handler );
//       // ...
//   };
//
//   Then you may do the below either:
//
//      auto response = MyResponse( [=] ( const AnyEvent& e ) { ... }; );
//  
//   or
//
//      AnyEventQueue queue;
//      auto response = MyResponse( queue );
//

class AnyEventHandler
{
public:

    // "Not a function"
    AnyEventHandler();
    AnyEventHandler( std::nullptr_t );

    AnyEventHandler( const AnyEventHandler& other );
    AnyEventHandler( AnyEventHandler&& other );

    // Construct by r-value
    // - Use SFINAE to prevent ambiguous with move constructor.
    template< typename HandlerT >
    AnyEventHandler(
        HandlerT&& handler,
        typename boost::disable_if< std::is_same< AnyEventHandler&, HandlerT > >::type* = nullptr
    );

    void operator()( const AnyEvent& event ) const;

    // Check if a valid function exists.
    operator Bool() const { return static_cast< Bool >( m_handler ); }


private:

    template< typename HandlerT >
    void Init( HandlerT&& handler, std::true_type );   // AnyRenderTarget

    template< typename HandlerT >
    void Init( HandlerT&& handler, std::false_type );  // Other types, should be function.

    void InitFromTarget( AnyEventTarget& target );

    std::function< void( const AnyEvent& ) > m_handler;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename HandlerT >
inline AnyEventHandler::AnyEventHandler(
    HandlerT&& handler,
    typename boost::disable_if< std::is_same< AnyEventHandler&, HandlerT > >::type*
 )
{
    this->Init(
        std::forward< HandlerT >( handler ),
        std::is_base_of< AnyEventTarget, typename std::remove_reference< HandlerT >::type >()
    );
}


template< typename HandlerT >
inline void AnyEventHandler::Init( HandlerT&& target, std::true_type )
{
    this->InitFromTarget( static_cast< AnyEventTarget& >( target ));
}


template< typename HandlerT >
inline void AnyEventHandler::Init( HandlerT&& handler, std::false_type )
{
    m_handler = std::forward< HandlerT >( handler );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_HANDLER_H
