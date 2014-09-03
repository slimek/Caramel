// Caramel C++ Library - Apple Facility - Shared Obj-C Pointer Header

#ifndef __CARAMEL_APPLE_SHARED_OBJC_PTR_H
#define __CARAMEL_APPLE_SHARED_OBJC_PTR_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


#if defined( CARAMEL_SYSTEM_OF_APPLE )


namespace Caramel
{

namespace Apple
{

///////////////////////////////////////////////////////////////////////////////
//
// Shared Obj-C Pointer
//

template< typename T >
class SharedObjcPtr
{
public:

    SharedObjcPtr();
    SharedObjcPtr( const SharedObjcPtr& sp );
    explicit SharedObjcPtr( T* p );
    SharedObjcPtr& operator=( const SharedObjcPtr& sp );
    ~SharedObjcPtr();

    T* Get() const { return m_p; }

private:
    T* m_p;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename T >
inline SharedObjcPtr< T >::SharedObjcPtr()
    : m_p( nil )
{
}


template< typename T >
inline SharedObjcPtr< T >::SharedObjcPtr( const SharedObjcPtr& sp )
    : m_p( [sp.m_p retain] )
{
}


template< typename T >
inline SharedObjcPtr< T >::SharedObjcPtr( T* p )
    : m_p( [p retain] )
{
}


template< typename T >
inline SharedObjcPtr< T >& SharedObjcPtr< T >::operator=( const SharedObjcPtr< T >& sp )
{
    [m_p autorelease];
    m_p = [sp.m_p retain];
}


template< typename T >
inline SharedObjcPtr< T >::~SharedObjcPtr< T >()
{
    [m_p release];
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Apple

} // namespace Caramel

#endif // CARAMEL_SYSTEM_OF_APPLE

#endif // __CARAMEL_APPLE_SHARED_OBJC_PTR_H
