// Caramel C++ Library - Object Facility - Auto-Numbered Header

#ifndef __CARAMEL_OBJECT_AUTO_NUMBERED_H
#define __CARAMEL_OBJECT_AUTO_NUMBERED_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <atomic>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Auto-Numbered
//

template< typename Derived, Uint firstNumber = 0 >
class AutoNumbered
{
public:

    static const Uint INITIAL_NEXT_NUMBER = firstNumber;

    Uint ObjectNumber() const { return m_objectNumber; }


protected:

    AutoNumbered();
    AutoNumbered( const AutoNumbered& );
    AutoNumbered( AutoNumbered&& );

    AutoNumbered& operator=( const AutoNumbered& );
    AutoNumbered& operator=( AutoNumbered&& );


private:

    Uint m_objectNumber;

    static std::atomic< Uint > m_nextNumber;
};


//
// Implementation
//

template< typename Derived, Uint firstNumber >
std::atomic< Uint > AutoNumbered< Derived, firstNumber >::
    m_nextNumber( AutoNumbered< Derived, firstNumber >::INITIAL_NEXT_NUMBER );


template< typename Derived, Uint firstNumber >
inline AutoNumbered< Derived, firstNumber >::AutoNumbered()
    : m_objectNumber( m_nextNumber ++ )
{
}


template< typename Derived, Uint firstNumber >
inline AutoNumbered< Derived, firstNumber >::AutoNumbered( const AutoNumbered< Derived, firstNumber >& rhs )
    : m_objectNumber( m_nextNumber ++ )
{
}


template< typename Derived, Uint firstNumber >
inline AutoNumbered< Derived, firstNumber >::AutoNumbered( AutoNumbered< Derived, firstNumber >&& rhs )
    : m_objectNumber( rhs.m_objectNumber )
{
}


template< typename Derived, Uint firstNumber >
inline AutoNumbered< Derived, firstNumber >&
AutoNumbered< Derived, firstNumber >::operator=( const AutoNumbered< Derived, firstNumber >& rhs )
{
    // Object number doesn't change in assigment.
    return *this;
}


template< typename Derived, Uint firstNumber >
inline AutoNumbered< Derived, firstNumber >&
AutoNumbered< Derived, firstNumber >::operator=( AutoNumbered< Derived, firstNumber >&& rhs )
{
    // Object number doesn't change in assigment.
    return *this;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_OBJECT_AUTO_NUMBERED_H
