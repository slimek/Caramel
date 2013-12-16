// Caramel C++ Library - Async Amenity - Any Event Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_H
#define __CARAMEL_ASYNC_ANY_EVENT_H
#pragma once

#include <Caramel/Caramel.h>
#include <boost/any.hpp>
#include <type_traits>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event
//

class AnyEvent
{
public:
    // Make an Event without value
    explicit AnyEvent( Int id );

    // Make an Event with value
    // - But the T can't be a pointer.
    template< typename T >
    AnyEvent( Int id, const T& value );

    // Special case
    // - const Char* is converted to std::string automatically.
    AnyEvent( Int id, const Char* value );


    /// Properties ///

    Int Id() const { return m_id; }

    template< typename T >
    T Value() const;


private:

    Int m_id;
    boost::any m_value;

};


//
// Implementation
//

inline AnyEvent::AnyEvent( Int id )
    : m_id( id )
{
}


template< typename T >
inline AnyEvent::AnyEvent( Int id, const T& value )
    : m_id( id )
    , m_value( value )
{
    static_assert( ! std::is_pointer< T >::value,
        "Pass a raw pointer into the asynchronous AnyEvent is dangerous" );
}


inline AnyEvent::AnyEvent( Int id, const Char* value )
    : m_id( id )
    , m_value( std::string( value ))
{
}


template< typename T >
inline T AnyEvent::Value() const
{
    return boost::any_cast< T >( m_value );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_H
