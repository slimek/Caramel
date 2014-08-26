// Caramel C++ Library - Value Facility - Shared Array Header

#ifndef __CARAMEL_VALUE_SHARED_ARRAY_H
#define __CARAMEL_VALUE_SHARED_ARRAY_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Error/Assert.h>
#include <Caramel/Error/Exception.h>
#include <boost/shared_ptr.hpp>
#include <algorithm>
#include <initializer_list>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Shared Array
// - A lightweight wrapper for std::shared_ptr< T[] >.
//   NOT thread-safe.
//

template< typename T >
class ConstSharedArray
{
public:

    ConstSharedArray();
    explicit ConstSharedArray( Uint size );
    explicit ConstSharedArray( std::initializer_list< T > inits );

    template< typename InputIterator >
    ConstSharedArray( InputIterator first, Uint count );

    
    /// Properties ///

    Bool IsEmpty() const { return 0 == m_size; }
    Uint Size()    const { return m_size; }


    /// Accessors ///

    typedef T ValueType;

    const ValueType& operator[]( Uint i ) const;
    
    // Linear search
    Bool Contains( const T& value ) const;


    /// Iterator Accessors ///

    typedef const ValueType* ConstIterator;

    ConstIterator Begin() const { return &m_array[0]; }
    ConstIterator End()   const { return &m_array[ m_size ]; }


    /// STL Compatible ///

    typedef const ValueType* const_iterator;

    const_iterator begin() const { return this->Begin(); }
    const_iterator end()   const { return this->End(); }

    
protected:

    typedef boost::shared_ptr< T[] > ArrayType;
    ArrayType m_array;

    Uint m_size;
};


template< typename T >
class SharedArray : public ConstSharedArray< T >
{
public:

    SharedArray();
    explicit SharedArray( Uint size );
    explicit SharedArray( std::initializer_list< T > inits );
    
    template< typename InputIterator >
    SharedArray( InputIterator first, Uint count );


    /// Accessors (constant) ///

    using ConstSharedArray< T >::operator[];
    using ConstSharedArray< T >::Begin;
    using ConstSharedArray< T >::End;


    /// Accessors (non-constant) ///

    typedef T ValueType;

    ValueType& operator[]( Uint i );


    typedef ValueType* Iterator;

    Iterator Begin() { return &m_array[0]; }
    Iterator End()   { return &m_array[ m_size ]; }


    /// STL Compatible ///

    typedef ValueType* iterator;

    iterator begin() { return this->Begin(); }
    iterator end()   { return this->End(); }


    /// Modifiers ///

    void Reset( Uint size );


protected:

    /// Data Members ///

    using ConstSharedArray< T >::m_array;
    using ConstSharedArray< T >::m_size;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

//
// Constructors
//

template< typename T >
inline ConstSharedArray< T >::ConstSharedArray()
    : m_array( new T[1] )  // dummy content
    , m_size( 0 )
{
}


template< typename T >
inline ConstSharedArray< T >::ConstSharedArray( Uint size )
    : m_size( size )
{
    // If size is 0, keep a dummy content in m_array.
    const Uint implSize = ( 0 < size ) ? size : 1;

    m_array.reset( new T[implSize] );
}


template< typename T >
inline ConstSharedArray< T >::ConstSharedArray( std::initializer_list< T > inits )
    : m_size( inits.size() )
{
    // If size is 0, keep a dummy content in m_array.
    const Uint implSize = ( 0 < m_size ) ? m_size : 1;

    m_array.reset( new T[implSize] );
    std::copy( inits.begin(), inits.end(), &m_array[0] );    
}


template< typename T >
template< typename InputIterator >
inline ConstSharedArray< T >::ConstSharedArray( InputIterator first, Uint count )
    : m_size( count )
{
    // If size is 0, keep a dummy content in m_array.
    const Uint implSize = ( 0 < m_size ) ? m_size : 1;

    m_array.reset( new T[implSize] );
    std::copy_n( first, count, &m_array[0] );
}


template< typename T >
inline SharedArray< T >::SharedArray()
    : ConstSharedArray< T >()
{
}


template< typename T >
inline SharedArray< T >::SharedArray( Uint size )
    : ConstSharedArray< T >( size )
{
}


template< typename T >
inline SharedArray< T >::SharedArray( std::initializer_list< T > inits )
    : ConstSharedArray< T >( inits )
{
}


template< typename T >
template< typename InputIterator >
inline SharedArray< T >::SharedArray( InputIterator first, Uint count )
    : ConstSharedArray< T >( first, count )
{
}


//
// Accessors
//

template< typename T >
inline Bool ConstSharedArray< T >::Contains( const T& value ) const
{
    return this->End() != std::find( this->Begin(), this->End(), value );
}


template< typename T >
inline const T& ConstSharedArray< T >::operator[]( Uint i ) const
{
    CARAMEL_ASSERT( m_size > i );
    return m_array[i];
}


template< typename T >
inline T& SharedArray< T >::operator[]( Uint i )
{
    CARAMEL_ASSERT( m_size > i );
    return m_array[i];
}


//
// Modifiers
//

template< typename T >
inline void SharedArray< T >::Reset( Uint size )
{
    m_array.reset( new T[size] );
    m_size = size;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_VALUE_SHARED_ARRAY_H
