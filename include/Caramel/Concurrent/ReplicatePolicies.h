// Caramel C++ Library - Concurrent Amenity - Replicate Policies Header

#ifndef __CARAMEL_CONCURRENT_REPLICATE_POLICIES_H
#define __CARAMEL_CONCURRENT_REPLICATE_POLICIES_H
#pragma once

#include <Caramel/Caramel.h>


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
    template< typename Value >
    class Collection
    {
    public:
        void Add( const Value& ) {}
        void Remove( const Value& ) {}
    };


    template< typename Key, typename Value >
    class Dictionary
    {
    public:
        void Insert( const Key&, const Value& ) {}
        void Erase( const Key& ) {}
    };

};


///////////////////////////////////////////////////////////////////////////////
//
// Replicate Snapshot
//

struct ReplicateSnapshot
{
    // TODO: Implements DictionarySnapshot and CollectionSnapshot
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_REPLICATE_POLICIES_H
