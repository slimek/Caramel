// Caramel C++ Library - Concurrent Amenity - Vector Header

#ifndef __CARAMEL_CONCURRENT_VECTOR_H
#define __CARAMEL_CONCURRENT_VECTOR_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Concurrent/ReplicatePolicies.h>
#include <Caramel/Concurrent/Detail/LockedSequence.h>
#include <Caramel/Thread/MutexLocks.h>
#include <boost/optional.hpp>
#include <algorithm>
#include <vector>


namespace Caramel
{

namespace Concurrent
{

///////////////////////////////////////////////////////////////////////////////
//
// Concurrent Vector
// - A thread-safe wrapper of std::vector.
//
//   Unlike other Concurrent containers, this Vector class is copyable -
//   it is done thread-safely, of course.
//
//   A vector is often used as a DTO (data transfer object),
//   therefore it supports Snapshot by default.
//

template< typename T >
class Vector : public ReplicateSnapshot::template Collection< Vector< T >, T >
{
public:

    typedef T ValueType;

    typedef typename ReplicateSnapshot::template Collection< Vector< T >, T > Replicator;


    /// Construtors ///

    Vector() {}
    Vector( std::initializer_list< T > ilist );

    Vector( const Vector& other );
    Vector( Vector&& other );

    explicit Vector( const std::vector< T >& vec );
    explicit Vector( std::vector< T >&& vec );


    /// Assignment ///

    Vector& operator=( std::initializer_list< T > ilist );

    Vector& operator=( const Vector& other );
    Vector& operator=( Vector&& other );

    Vector& operator=( const std::vector< T >& vec );
    Vector& operator=( std::vector< T >&& vec );


    /// Conversion ///

    std::vector< T > ToVector() const;


    /// Properties ///

    Bool  IsEmpty() const { return m_vector.empty(); }
    Usize Size()    const { return m_vector.size(); }


    /// Operations ///

    void PushBack( const T& x );
    void PushBack( T&& x );

    void Clear();


    /// Random Accessors ///

    // Returns false if index is out of range.
    Bool TryGetAt( Usize index, T& value ) const;

    // Returns boost::none if index is out of range.
    boost::optional< T > operator[] ( Usize index ) const;


    /// Algorithms ///
    
    template< typename Predicate >
    Bool Find( T& value, Predicate pred ) const;


    /// Locked Iterator Accessors ///
    
    class ConstLockedVector;
    friend class ConstLockedVector;

    // For Replicator
    typedef ConstLockedVector ConstLockedCollection;


private:

    /// Data Members ///

    typedef std::vector< T > VectorType;
    VectorType m_vector;

    mutable std::mutex m_vectorMutex;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

//
// Constructors
//

template< typename T >
inline Vector< T >::Vector( std::initializer_list< T > ilist )
    : Replicator( true )  // initially modified
    , m_vector( ilist )
{}


template< typename T >
inline Vector< T >::Vector( const Vector& other )
    : Replicator( true )
{
    m_vector = other.ToVector();  // Move a temporary copy
}


template< typename T >
inline Vector< T >::Vector( Vector&& other )
    : Replicator( true )
{
    m_vector = std::move( other.m_vector );
}


template< typename T >
inline Vector< T >::Vector( const std::vector< T >& vec )
    : Replicator( true )
    , m_vector( vec )
{}


template< typename T >
inline Vector< T >::Vector( std::vector< T >&& vec )
    : Replicator( true )
    , m_vector( std::move( vec ))
{}


//
// Assignment
//

template< typename T >
inline Vector< T >& Vector< T >::operator=( std::initializer_list< T > ilist )
{
    LockGuard lock( m_vectorMutex );

    m_vector = ilist;
    this->Replicator::ReplicaClear();
    return *this;
}


template< typename T >
inline Vector< T >& Vector< T >::operator=( const Vector< T >& other )
{
    // ATTENTION: Do NOT put this line after the lock, or you may encounter deadlocks.
    auto copy = other.ToVector();

    LockGuard lock( m_vectorMutex );

    m_vector = std::move( copy );
    this->Replicator::ReplicaClear();
    return *this;
}


template< typename T >
inline Vector< T >& Vector< T >::operator=( Vector< T >&& other )
{
    LockGuard lock( m_vectorMutex );

    m_vector = std::move( other.m_vector );
    this->Replicator::ReplicaClear();
    return *this;
}


template< typename T >
inline Vector< T >& Vector< T >::operator=( const std::vector< T >& vec )
{
    LockGuard lock( m_vectorMutex );

    m_vector = vec;
    this->Replicator::ReplicaClear();
    return *this;
}


template< typename T >
inline Vector< T >& Vector< T >::operator=( std::vector< T >&& vec )
{
    LockGuard lock( m_vectorMutex );

    m_vector = std::move( vec );
    this->Replicator::ReplicaClear();
    return *this;
}


//
// Conversion
//

template< typename T >
inline std::vector< T > Vector< T >::ToVector() const
{
    LockGuard lock( m_vectorMutex );
    
    return std::vector< T >( m_vector );
}


//
// Operations
//

template< typename T >
inline void Vector< T >::PushBack( const T& x )
{
    LockGuard lock( m_vectorMutex );

    m_vector.push_back( x );
    this->Replicator::ReplicaAdd( x );
}


template< typename T >
inline void Vector< T >::PushBack( T&& x )
{
    LockGuard lock( m_vectorMutex );

    m_vector.push_back( std::move( x ));
    this->Replicator::ReplicaAdd( m_vector.back() );
}


template< typename T >
inline void Vector< T >::Clear()
{
    LockGuard lock( m_vectorMutex );

    m_vector.clear();
    this->Replicator::ReplicaClear();
}


//
// Algorithms
//

template< typename T >
template< typename Predicate >
inline Bool Vector< T >::Find( T& value, Predicate pred ) const
{
    LockGuard lock( m_vectorMutex );

    const auto iter = std::find_if( m_vector.begin(), m_vector.end(), pred );
    if ( iter == m_vector.end() ) { return false; }

    value = *iter;
    return true;
}


//
// Random Accessors 
//

template< typename T >
inline Bool Vector< T >::TryGetAt( Usize index, T& value ) const
{
    LockGuard lock( m_vectorMutex );

    if ( index >= m_vector.size() ) { return false; }

    value = m_vector[index];
    return true;
}


template< typename T >
inline boost::optional< T > Vector< T >::operator[]( Usize index ) const
{
    LockGuard lock( m_vectorMutex );

    if ( index >= m_vector.size() ) { return boost::none; }

    return m_vector[index];
}


//
// Locked Iterator Accessors
//

template< typename T >
class Vector< T >::ConstLockedVector : public Detail::ConstLockedSequence< VectorType >
{
public:
    explicit ConstLockedVector( const Vector& host )
        : Detail::ConstLockedSequence< VectorType >( host.m_vectorMutex, host.m_vector )
    {}
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_VECTOR_H
