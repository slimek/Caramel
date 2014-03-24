// Caramel C++ Library - Value Facility - Any Header

#ifndef __CARAMEL_VALUE_ANY_H
#define __CARAMEL_VALUE_ANY_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Value/Detail/AnyCasters.h>
#include <Caramel/Value/Detail/AnyHolders.h>
#include <boost/utility/enable_if.hpp>
#include <type_traits>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any
// - This class allow you to transfer "any" type of data.
//
//   The input and output types may be different for some numeric types.
//   Convertion may throw exception if the output type can't represent
//   the input value exactly.
//
//     Output   |   Input Categories   |  Input Types
//   ------------------------------------------------------
//     Boolean  <=  Boolean            |  Bool 
//     Integer  <=  Integer / Enum     |  Int/Uint, any enums
//     Floating <=  Floating / Integer |  Float/Double, Int/Uint
//     String   <=  String             |  std::string, Char*
//     Enum     <=  Enum               |  enum
//     Object   <=  Object             |  other types
//

class Any
{
public:

    Any() {}

    Any( const Any& rhs );
    Any( Any&& rhs );

    template< typename T >
    Any( const T& value );


    //
    // Construct by r-value
    // - Use SFINAE to prevent ambiguous with move constructor.
    //
    template< typename T >
    Any(
        T&& value,
        typename boost::disable_if< std::is_same< Any&, T > >::type* = nullptr
    );

    
    //
    // Assignment
    // - Use copy-and-swap idiom.
    //   NOTES: C++11 requires an explicit assignment when you declare a move constructor.
    //          But Visual C++ ingores this rule.
    //

    Any& operator=( Any rhs );
    
    friend void swap( Any& x, Any& y );


    /// Retrieve Value ///

    template< typename T >
    T As() const;


    /// Properties ///

    Bool IsEmpty() const { return ! m_holder; }


private:
    std::shared_ptr< Detail::AnyHolder > m_holder;
        
};


//
// Stand-alone Creators
// - For polymorphic work-around. Example:
//
//   auto any = MakeAny< Base >( derived );
//

template< typename T >
inline Any MakeAny( const T& value )
{
    return Any( value );
}


//
// Swap
// - Compatible with std::swap().
//

inline void swap( Any& x, Any& y )
{
    x.m_holder.swap( y.m_holder );
}


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline Any::Any( const Any& rhs )
    : m_holder( rhs.m_holder )
{
}


inline Any::Any( Any&& rhs )
    : m_holder( std::move( rhs.m_holder ))
{
}


template< typename T >
inline Any::Any( const T& value )
    : m_holder( new typename Detail::AnyHolderSelect< T >::Type( value ))
{
}


template< typename T >
inline Any::Any(
    T&& value,
    typename boost::disable_if< std::is_same< Any&, T > >::type*
)
    : m_holder( new typename Detail::AnyHolderSelect<
        typename std::remove_reference< T >::type >::Type( static_cast< T&& >( value )))
{
}


//
// Assignment
//

inline Any& Any::operator=( Any rhs )
{
    swap( *this, rhs );
    return *this;
}



//
// Retrieve Value
//

template< typename T >
inline T Any::As() const
{
    typedef typename Detail::AnyCasterSelect< T >::Type Caster;
    return Caster::template CastTo< T >( m_holder.get() );
}


///////////////////////////////////////////////////////////////////////////////
//
// Appendix : Rationale
//
//   Why we don't use boost::any ?
//   Because boost::any can't do this:
//
//     boost::any anyInt( 1 );
//     ...
//     Uint value = boost::get< Uint >( anyInt ); // Throws ! '1' is not an Uint.
//                                                // You must use '1u' above.
//
//   And it can't do this, neither:
//
//     boost::any anyText( "Alice" );  // Compiler error !
//                                     // boost::any doesn't accept array.
// 

///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_VALUE_ANY_H
