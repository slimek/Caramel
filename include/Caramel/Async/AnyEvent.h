// Caramel C++ Library - Async Facility - Any Event Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_H
#define __CARAMEL_ASYNC_ANY_EVENT_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Error/Exception.h>
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

    // Not an event
    AnyEvent();

    // Move
    AnyEvent( AnyEvent&& other );

    // Make an Event without value
    explicit AnyEvent( Int id );

    // Make an Event with any value
    AnyEvent( Int id, Any value );


    /// Properties ///

    Bool IsValid()  const { return m_valid; }
    Bool HasValue() const { return ! m_value.IsEmpty(); }


    /// Accessors ///

    Int Id() const;

    template< typename T >
    T Value() const;


private:

    Bool m_valid;
    Int  m_id;
    Any  m_value;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline AnyEvent::AnyEvent()
    : m_valid( false )
    , m_id( 0 )
{
}


inline AnyEvent::AnyEvent( AnyEvent&& other )
    : m_valid( other.m_valid )
    , m_id( other.m_id )
    , m_value( std::move( other.m_value ))
{
    other.m_valid = false;
    other.m_id = 0;
}


inline AnyEvent::AnyEvent( Int id )
    : m_valid( true )
    , m_id( id )
{
}


inline AnyEvent::AnyEvent( Int id, Any value )
    : m_valid( true )
    , m_id( id )
    , m_value( std::move( value ))
{
}


inline Int AnyEvent::Id() const
{
    if ( ! m_valid )
    {
        CARAMEL_THROW( "Not an event" );
    }

    return m_id;
}


template< typename T >
inline T AnyEvent::Value() const
{
    if ( ! m_valid )
    {
        CARAMEL_THROW( "Not an event" );
    }

    return m_value.template As< T >();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_H
