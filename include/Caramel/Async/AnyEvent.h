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

    // Make an Event with any value
    AnyEvent( Int id, const Any& value );
    AnyEvent( Int id, Any&& value );


    /// Properties ///

    Int Id() const { return m_id; }

    template< typename T >
    T Value() const;

    Bool HasValue() const { return ! m_value.IsEmpty(); }


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


inline AnyEvent::AnyEvent( Int id, const Any& value )
    : m_id( id )
    , m_value( value )
{
}


inline AnyEvent::AnyEvent( Int id, Any&& value )
    : m_id( id )
    , m_value( value )
{
}


template< typename T >
inline T AnyEvent::Value() const
{
    return m_value.template As< T >();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_H
