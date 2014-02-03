// Caramel C++ Library - Async Amenity - Value Change Header

#ifndef __CARAMEL_ASYNC_VALUE_CHANGE_H
#define __CARAMEL_ASYNC_VALUE_CHANGE_H
#pragma once

#include <Caramel/Caramel.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Value Change
// - Tracking the modification of a scalar value.
//

template< typename T >
class ValueChange
{
public:

    ValueChange();
    explicit ValueChange( T initialValue );


    void Update( T newValue );

    template< T checkValue >
    Bool Enters() const;

    template< T checkValue >
    Bool Exits() const;


private:

    T m_previousValue;
    T m_currentValue;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename T >
inline ValueChange< T >::ValueChange()
    : m_previousValue( 0 )
    , m_currentValue( 0 )
{
}


template< typename T >
inline ValueChange< T >::ValueChange( T initialValue )
    : m_previousValue( initialValue )
    , m_currentValue( initialValue )
{
}


template< typename T >
inline void ValueChange< T >::Update( T newValue )
{
    m_previousValue = m_currentValue;
    m_currentValue = newValue;
}


template< typename T >
template< T checkValue >
inline Bool ValueChange< T >::Enters() const
{
    return m_previousValue != m_currentValue
        && m_currentValue == checkValue;
}


template< typename T >
template< T checkValue >
inline Bool ValueChange< T >::Exits() const
{
    return m_previousValue != m_currentValue
        && m_previousValue == checkValue;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_VALUE_CHANGE_H
