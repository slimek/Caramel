// Caramel C++ Library - Apple Facility - Shared NSObject Pointer Header

#ifndef __CARAMEL_APPLE_SHARED_NSO_PTR_H
#define __CARAMEL_APPLE_SHARED_NSO_PTR_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


#if defined( CARAMEL_SYSTEM_OF_APPLE )


namespace Caramel
{

namespace Apple
{

///////////////////////////////////////////////////////////////////////////////
//
// Shared NSObject Pointer
//

template< typename T >
class SharedNsoPtr
{
public:

    SharedNsoPtr();
    SharedNsoPtr( const SharedNsoPtr& sp );
    SharedNsoPtr( SharedNsoPtr&& sp );
    explicit SharedNsoPtr( T* p );
    SharedNsoPtr& operator=( const SharedNsoPtr& sp );
    SharedNsoPtr& operator=( SharedNsoPtr&& sp );
    ~SharedNsoPtr();

    T* Get() const { return m_p; }
    T* Retain() const { return [m_p retain]; }

private:
    T* m_p;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename T >
inline SharedNsoPtr< T >::SharedNsoPtr()
    : m_p( nil )
{
}


template< typename T >
inline SharedNsoPtr< T >::SharedNsoPtr( const SharedNsoPtr& sp )
    : m_p( [sp.m_p retain] )
{
}


template< typename T >
inline SharedNsoPtr< T >::SharedNsoPtr( SharedNsoPtr&& sp )
    : m_p( sp.m_p )
{
    sp.m_p = nil;
}


template< typename T >
inline SharedNsoPtr< T >::SharedNsoPtr( T* p )
    : m_p( [p retain] )
{
}


template< typename T >
inline SharedNsoPtr< T >& SharedNsoPtr< T >::operator=( const SharedNsoPtr< T >& sp )
{
    [m_p autorelease];
    m_p = [sp.m_p retain];
    return *this;
}


template< typename T >
inline SharedNsoPtr< T >& SharedNsoPtr< T >::operator=( SharedNsoPtr< T >&& sp )
{
    [m_p autorelease];
    m_p = sp.m_p;
    sp.m_p = nil;
    return *this;
}


template< typename T >
inline SharedNsoPtr< T >::~SharedNsoPtr< T >()
{
    [m_p release];
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Apple

} // namespace Caramel

#endif // CARAMEL_SYSTEM_OF_APPLE

#endif // __CARAMEL_APPLE_SHARED_NSO_PTR_H
