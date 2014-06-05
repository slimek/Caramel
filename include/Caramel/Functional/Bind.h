// Caramel C++ Library - Functional Amenity - Bind Header

#ifndef __CARAMEL_FUNCTIONAL_BIND_H
#define __CARAMEL_FUNCTIONAL_BIND_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <functional>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Bind 1st
// - Bind any binary function into a unary function.
//

template< typename Function, typename A1 >
inline auto Bind1st( Function&& f, A1&& a1 )
    -> decltype( std::bind( std::forward< Function >( f ), std::forward< A1 >( a1 ), std::placeholders::_1 ))
{
    return std::bind( std::forward< Function >( f ), std::forward< A1 >( a1 ), std::placeholders::_1 );
}


///////////////////////////////////////////////////////////////////////////////
//
// Appendix : Rationale
//
//   Bind1st is designed to simplify the usage of std::bind or lambda.
//   See the below example:
//
//   class Panel
//   {
//   public:
//       void Init();
//   private:
//       void OnClick( Widget* sender );
//   };
//    
//   void Panel::Init()
//   {
//       // lambda
//       m_button->ListenClick( [=] ( Widget* sender ) { OnClick( sender ); });
//    
//       // std::bind
//       m_button->ListenClick( std::bind( &Panel::OnClick, this, std::placeholders::_1 ));
//    
//       // Caramel::Bind1st
//       m_button->ListenClick( Caramel::Bind1st( &Panel::OnClick, this ));
//   }
//
//
//   Not remarkable ... It looks better if you are using Caramel namespace.
//
//   Maybe I write it just for proving "We can do it" :)
//

///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FUNCTIONAL_BIND_H

