// Caramel C++ Library - Concurrent Amenity - Stack Header

#ifndef __CARAMEL_CONCURRENT_STACK_H
#define __CARAMEL_CONCURRENT_STACK_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Thread/MutexLocks.h>
#include <boost/noncopyable.hpp>
#include <deque>


namespace Caramel
{

namespace Concurrent
{

///////////////////////////////////////////////////////////////////////////////
//
// Concurrent Stack
//

template< typename T >
class Stack : public boost::noncopyable
{
public:

    typedef T ValueType;

    
    /// Properties ///

    Bool  IsEmpty() const { return m_stack.empty(); }
    Usize Size()    const { return m_stack.size(); }


    /// Operations ///

    void Push( const T& x );
    void Push( T&& x );

    Bool TryPop( T& x );


private:

    /// Data Members ///

    typedef std::deque< T > StackType;
    StackType m_stack;

    mutable std::mutex m_stackMutex;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename T >
inline void Stack< T >::Push( const T& x )
{
    LockGuard lock( m_stackMutex );

    m_stack.push_back( x );
}


template< typename T >
inline void Stack< T >::Push( T&& x )
{
    LockGuard lock( m_stackMutex );

    m_stack.push_back( std::move( x ));
}


template< typename T >
inline Bool Stack< T >::TryPop( T& x )
{
    if ( m_stack.empty() ) { return false; }

    LockGuard lock( m_stackMutex );

    if ( m_stack.empty() ) { return false; }

    x = m_stack.back();
    m_stack.pop_back();

    return true;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_STACK_H
