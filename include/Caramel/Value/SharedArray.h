// Caramel C++ Library - Value Facility - Shared Array Header

#ifndef __CARAMEL_VALUE_SHARED_ARRAY_H
#define __CARAMEL_VALUE_SHARED_ARRAY_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Error/Assert.h>
#include <Caramel/Error/Exception.h>
#include <boost/shared_array.hpp>
#include <algorithm>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Shared Array
// - A lightweight wrapper for std::shared_array< T >.
//   NOT thread-safe.
//

template< typename T >
class ConstSharedArray
{
public:

    ConstSharedArray();
    explicit ConstSharedArray( Uint size );

    
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

    typedef boost::shared_array< T > ArrayType;
    ArrayType m_array;

    Uint m_size;
};


template< typename T >
class SharedArray : public ConstSharedArray< T >
{
public:

    SharedArray();
    explicit SharedArray( Uint size );


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
ConstSharedArray< T >::ConstSharedArray()
    : m_array( new T[1] )  // dummy content
    , m_size( 0 )
{
}


template< typename T >
ConstSharedArray< T >::ConstSharedArray( Uint size )
    : m_size( size )
{
    // If size is 0, keep a dummy content in m_array.
    const Uint implSize = ( 0 < size ) ? size : 1;

    m_array.reset( new T[implSize] );
}


template< typename T >
SharedArray< T >::SharedArray()
    : ConstSharedArray< T >()
{
}


template< typename T >
SharedArray< T >::SharedArray ( Uint size )
    : ConstSharedArray< T >( size )
{
}


//
// Accessors
//

template< typename T >
Bool ConstSharedArray< T >::Contains( const T& value ) const
{
    return this->End() != std::find( this->Begin(), this->End(), value );
}


template< typename T >
const T& ConstSharedArray< T >::operator[]( Uint i ) const
{
    CARAMEL_ASSERT( m_size > i );
    return m_array[i];
}


template< typename T >
T& SharedArray< T >::operator[]( Uint i )
{
    CARAMEL_ASSERT( m_size > i );
    return m_array[i];
}


//
// Modifiers
//

template< typename T >
void SharedArray< T >::Reset( Uint size )
{
    m_array.reset( new T[size] );
    m_size = size;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_VALUE_SHARED_ARRAY_H
