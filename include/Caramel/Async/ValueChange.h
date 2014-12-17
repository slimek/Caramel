// Caramel C++ Library - Async Facility - Value Change Header

#ifndef __CARAMEL_ASYNC_VALUE_CHANGE_H
#define __CARAMEL_ASYNC_VALUE_CHANGE_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Thread/MutexLocks.h>
#include <boost/noncopyable.hpp>
#include <type_traits>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Value Change
// - Tracking the modification of an integral or enum value.
//
//   This class is thread-safe.
//

template< typename T >
class ValueChange : public boost::noncopyable
{
    static_assert(
        std::is_integral< T >::value || std::is_enum< T >::value,
        "T must be an integral or enum type"
    );

public:

    ValueChange();
    explicit ValueChange( T initialValue );


    void Update( T newValue );

    template< T checkValue >
    Bool Enters() const;

    template< T checkValue >
    Bool Exits() const;


private:

    mutable std::mutex m_mutex;

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
    LockGuard lock( m_mutex );

    m_previousValue = m_currentValue;
    m_currentValue = newValue;
}


template< typename T >
template< T checkValue >
inline Bool ValueChange< T >::Enters() const
{
    LockGuard lock( m_mutex );

    return m_previousValue != m_currentValue
        && m_currentValue == checkValue;
}


template< typename T >
template< T checkValue >
inline Bool ValueChange< T >::Exits() const
{
    LockGuard lock( m_mutex );

    return m_previousValue != m_currentValue
        && m_previousValue == checkValue;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_VALUE_CHANGE_H
