// Caramel C++ Library - Object Facility - Singleton Header

#ifndef __CARAMEL_OBJECT_SINGLETON_H
#define __CARAMEL_OBJECT_SINGLETON_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Object/Detail/LifetimeTracker.h>
#include <boost/noncopyable.hpp>
#include <mutex>

#if defined( CARAMEL_COMPILER_IS_GCC )
#include <thread>  // for std::call_once()
#endif


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Singleton
// - The higher longevity, the later it is destroyed.
//   If two singletons have the same longevity, the order of their destruction
//   is undetermined.
// - Longevity greater than 0x7FFFFFFF is reserved for Caramel internal usage.
// - Credit to "Loki" library.
//

template< typename T, Uint longevity = 0 >
class Singleton : public boost::noncopyable
{
public:
    static T* Instance();

private:
    static void Create();
    static void Destroy( T* );

    static volatile T* m_instance;
    static std::once_flag m_created;
    static Bool m_destroyed;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

//
// Data Members
//

template< typename T, Uint longevity >
volatile T* Singleton< T, longevity >::m_instance = nullptr;

template< typename T, Uint longevity >
std::once_flag Singleton< T, longevity >::m_created;

template< typename T, Uint longevity >
Bool Singleton< T, longevity >::m_destroyed = false;


//
// Instance - Access to the single object.
//
template< typename T, Uint longevity >
inline T* Singleton< T, longevity >::Instance()
{
    if ( m_instance ) { return const_cast< T* >( m_instance ); }

    std::call_once( m_created, &Create );

    return const_cast< T* >( m_instance );
}


//
// Create - Create the single object and register its destroy handler.
//
template< typename T, Uint longevity >
inline void Singleton< T, longevity >::Create()
{
    m_instance = new T;

    Detail::LifetimeTrackerSortedList::Insert(
        const_cast< T* >( m_instance ), longevity, &Singleton::Destroy );
}


//
// Destroy - Called when the program is to exit.
//
template< typename T, Uint longevity >
inline void Singleton< T, longevity >::Destroy( T* )
{
    m_destroyed = true;

    delete m_instance;
    m_instance = nullptr;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_OBJECT_SINGLETON_H
