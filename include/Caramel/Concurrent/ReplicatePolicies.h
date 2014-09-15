// Caramel C++ Library - Concurrent Amenity - Replicate Policies Header

#ifndef __CARAMEL_CONCURRENT_REPLICATE_POLICIES_H
#define __CARAMEL_CONCURRENT_REPLICATE_POLICIES_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Concurrent/Detail/CollectionSnapshot.h>
#include <Caramel/Concurrent/Detail/DictionarySnapshot.h>


namespace Caramel
{

namespace Concurrent
{

///////////////////////////////////////////////////////////////////////////////
//
// Replicate Nothing
//

struct ReplicateNothing
{
    template< typename Derived, typename Value >
    class Collection
    {
    protected:
        void ReplicaAdd( const Value& ) {}
        void ReplicaRemove( const Value& ) {}
        void ReplicaClear() {}
    };


    template< typename Derived, typename Key, typename Value >
    class Dictionary
    {
    public:
        void ReplicaAdd( const Key&, const Value& ) {}
        void ReplicaRemove( const Key& ) {}
        void ReplicaClear() {}
    };

};


///////////////////////////////////////////////////////////////////////////////
//
// Replicate Snapshot
//

struct ReplicateSnapshot
{
    template< typename Derived, typename Value >
    using Collection = Detail::CollectionSnapshot< Derived, Value >;

    template< typename Derived, typename Key, typename Value >
    using Dictionary = Detail::DictionarySnapshot< Derived, Key, Value >;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_REPLICATE_POLICIES_H
