// Caramel C++ Library - Object Facility - Implementation

#include <Caramel/CaramelPch.h>

#include <algorithm>
#include <list>
#include <mutex>
#include <Caramel/Object/Singleton.h>


namespace Caramel
{

//
// Contents
//
// 1. LifetimeTrackerArray
//

///////////////////////////////////////////////////////////////////////////////
//
// Lifetime Tracker Array
//

namespace Detail
{

void CARAMEL_CDECL AtExit()
{
    LifetimeTracker* tracker = LifetimeTrackerSortedList::PopFront();
    delete tracker;
}


Bool LifetimeTracker::Less( LifetimeTracker* lhs, LifetimeTracker* rhs )
{
    return lhs->m_longevity < rhs->m_longevity;
}


struct LifetimeTrackerList
{
    std::mutex mutex;
    std::list< LifetimeTracker* > trackers;

    static LifetimeTrackerList* Instance()
    {
        // This is a Meyer's singleton.
        // It would be created before, and destroyed after any Caramel::Singleton.

        static LifetimeTrackerList instance;
        return &instance;
    }
};


void LifetimeTrackerSortedList::DoInsert( std::unique_ptr< LifetimeTracker >&& tracker )
{
    LifetimeTrackerList* tList = LifetimeTrackerList::Instance();

    std::unique_lock< std::mutex > ulock( tList->mutex );

    auto pos = std::upper_bound(
        tList->trackers.begin(), tList->trackers.end(), tracker.get(),
        &LifetimeTracker::Less );

    tList->trackers.insert( pos, tracker.get() );

    ulock.unlock();

    tracker.release();

    std::atexit( &AtExit );
}


LifetimeTracker* LifetimeTrackerSortedList::PopFront()
{
    LifetimeTrackerList* tList = LifetimeTrackerList::Instance();

    std::unique_lock< std::mutex > ulock( tList->mutex );

    LifetimeTracker* tracker = tList->trackers.front();
    tList->trackers.pop_front();

    return tracker;
}


} // namespace Detail

///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
