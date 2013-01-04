// Caramel C++ Library - Object Facility - Detail - Lifetime Tracer Header

#ifndef __CARAMEL_OBJECT_DETAIL_LIFETIME_TRACKER_H
#define __CARAMEL_OBJECT_DETAIL_LIFETIME_TRACKER_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Lifetime Tracker
// - A helper class for keeping 'longevity' of Singleton types.
//

class LifetimeTracker
{
public:
    explicit LifetimeTracker( Uint longevity )
        : m_longevity( longevity )
    {}

    virtual ~LifetimeTracker() {}

    static Bool Less( LifetimeTracker* lhs, LifetimeTracker* rhs );

private:
    Uint m_longevity;
};


template< typename T, typename Destroyer >
class ConcreteLifetimeTracker : public LifetimeTracker
{
public:
    ConcreteLifetimeTracker( T* tracked, Uint longevity, Destroyer d )
        : LifetimeTracker( longevity )
        , m_tracked( tracked )
        , m_destroyer( d )
    {}

    ~ConcreteLifetimeTracker()
    {
        m_destroyer( m_tracked );
    }

private:
    T*        m_tracked;    // The singleton object.
    Destroyer m_destroyer;  // A function which take T* as parameter and would destroy it.
};


///////////////////////////////////////////////////////////////////////////////
//
// Lifetime Tracker Sorted List
// - Keep all LifetimeTracker objects sorted by longevity.
//

class LifetimeTrackerSortedList
{
public:

    template< typename T, typename Destroyer >
    static void Insert( T* tracked, Uint longevity, Destroyer d )
    {
        std::unique_ptr< LifetimeTracker >
            p( new ConcreteLifetimeTracker< T, Destroyer >( tracked, longevity, d ));

        DoInsert( std::move( p ));  // it would move the ownershipt to this tracker array.
    }

    static LifetimeTracker* PopFront();  // return a tracker with lowest longevity


private:
    static void DoInsert( std::unique_ptr< LifetimeTracker >&& tracker );
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_OBJECT_DETAIL_LIFETIME_TRACKER_H
