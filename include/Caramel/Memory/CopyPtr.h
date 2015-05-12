// Caramel C++ Library - Memory Amenity - Copy Pointer Header

#ifndef __CARAMEL_MEMORY_COPY_PTR_H
#define __CARAMEL_MEMORY_COPY_PTR_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <type_traits>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Copy Pointer
// - A smart pointer which automatically copy the content to a new pointer. 
//   It only does a swallow copy, therefore you can only use it on a
//   non-polymorphic type.
//

template< typename T >
class CopyPtr
{
    static_assert( ! std::is_polymorphic< T >::value, "T must be non-polymorphic" );
    static_assert( ! std::is_array< T >::value, "T cannot be an array" );

public:

    CopyPtr();
    explicit CopyPtr( T* p );

    CopyPtr( const CopyPtr& other );
    CopyPtr( CopyPtr&& other );
    ~CopyPtr();

    // Unified assignment
    CopyPtr& operator=( CopyPtr other );


    /// Modifiers ///
    
    void Swap( CopyPtr& other );

    void Reset( T* p = nullptr );

    
    /// Properties and Accessors ///

    explicit operator Bool() const { return m_p != nullptr; }

    T* Get()        const { return m_p; }
    T& operator*()  const { return *m_p; }
    T* operator->() const { return m_p; }


private:

    T* m_p { nullptr };
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename T >
inline CopyPtr< T >::CopyPtr()
    // m_p already is nullptr
{}


template< typename T >
inline CopyPtr< T >::CopyPtr( T* p )
{
    this->Reset( p );
}


template< typename T >
inline CopyPtr< T >::CopyPtr( const CopyPtr& other )
{
    if ( other.m_p )
    {
        m_p = new T( *other.m_p );
    }
}


template< typename T >
inline CopyPtr< T >::CopyPtr( CopyPtr&& other )
    : m_p( std::move( other.m_p ))
{
    other.m_p = nullptr;
}


template< typename T >
inline CopyPtr< T >::~CopyPtr()
{
    if ( m_p )
    {
        delete m_p;
    }
}


//
// Unified Assignment
// - Use copy-and-swap idiom.
//

template< typename T >
inline CopyPtr< T >& CopyPtr< T >::operator=( CopyPtr other )
{
    this->Swap( other );
    return *this;
}


//
// Modifiers
//

template< typename T >
inline void CopyPtr< T >::Swap( CopyPtr& other )
{
    std::swap( m_p, other.m_p );
}


template< typename T >
inline void CopyPtr< T >::Reset( T* p )
{
    if ( m_p )
    {
        delete m_p;
    }

    m_p = p;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace

#endif // __CARAMEL_MEMORY_COPY_PTR_H

