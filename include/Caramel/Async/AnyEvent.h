// Caramel C++ Library - Async Amenity - Any Event Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_H
#define __CARAMEL_ASYNC_ANY_EVENT_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Value/Any.h>
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


    /// Properties ///

    Int Id() const { return m_id; }

    template< typename T >
    T Value() const;


private:

    Int m_id;
    Any m_value;

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


template< typename T >
inline T AnyEvent::Value() const
{
    return m_value.template As< T >();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_H
