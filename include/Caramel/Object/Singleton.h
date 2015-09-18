// Caramel C++ Library - Object Facility - Singleton Header

#ifndef __CARAMEL_OBJECT_SINGLETON_H
#define __CARAMEL_OBJECT_SINGLETON_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Object/Detail/LifetimeTracker.h>
#include <boost/noncopyable.hpp>
#include <atomic>
#include <mutex>


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
    static void CreateInstance();
    static void DestroyInstance( T* );

    static volatile T* m_instance;
    static Bool m_instanceDestroyed;

    static std::once_flag m_created;


    // NOTE: m_destroyed has no function in code.
    //       but you may use it to check if a singleton is created more than once
    //       when debugging.
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
Bool Singleton< T, longevity >::m_instanceDestroyed = false;

template< typename T, Uint longevity >
std::once_flag Singleton< T, longevity >::m_created;


//
// Instance - Access to the single object.
//
template< typename T, Uint longevity >
inline T* Singleton< T, longevity >::Instance()
{
    if ( m_instance ) { return const_cast< T* >( m_instance ); }

    std::call_once( m_created, &CreateInstance );

    return const_cast< T* >( m_instance );
}


//
// Create - Create the single object and register its destroy handler.
//
template< typename T, Uint longevity >
inline void Singleton< T, longevity >::CreateInstance()
{
    T* instance = new T;
    
    // Make sure the instance is fully created before be assigned to m_instance.
    std::atomic_thread_fence( std::memory_order_release );

    m_instance = instance;

    Detail::LifetimeTrackerSortedList::Insert(
        const_cast< T* >( m_instance ), longevity, &Singleton::DestroyInstance );
}


//
// Destroy - Called when the program is to exit.
//
template< typename T, Uint longevity >
inline void Singleton< T, longevity >::DestroyInstance( T* )
{
    m_instanceDestroyed = true;

    delete m_instance;
    m_instance = nullptr;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_OBJECT_SINGLETON_H
