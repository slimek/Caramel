// Caramel C++ Library - Concurrent Amenity - Replicate Policies Header

#ifndef __CARAMEL_CONCURRENT_REPLICATE_POLICIES_H
#define __CARAMEL_CONCURRENT_REPLICATE_POLICIES_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Concurrent/Detail/CollectionSnapshot.h>


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


    template< typename Key, typename Value >
    class Dictionary
    {
    public:
        void Add( const Key&, const Value& ) {}
        void Remove( const Key& ) {}
    };

};


///////////////////////////////////////////////////////////////////////////////
//
// Replicate Snapshot
//

struct ReplicateSnapshot
{
    // TODO: Replace the derived class with alias templates

    template< typename Derived, typename Value >
    class Collection : public Detail::CollectionSnapshot< Derived, Value >
    {
    };


    // TODO: Implements DictionarySnapshot and CollectionSnapshot
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_REPLICATE_POLICIES_H
