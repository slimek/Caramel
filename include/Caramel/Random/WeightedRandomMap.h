// Caramel C++ Library - Random Facility - Weighted Random Map Header

#ifndef __CARAMEL_RANDOM_WEIGHTED_RANDOM_MAP_H
#define __CARAMEL_RANDOM_WEIGHTED_RANDOM_MAP_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Error/Assert.h>
#include <Caramel/Random/UniformRandom.h>
#include <map>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Weighted Random Map
// - NOT thread-safe.
//

template< typename Weight, typename Value >
class WeightedRandomMap
{
public:

    WeightedRandomMap();

    void Add( Weight w, const Value& v );

    // Retrieve a value from map, the probability is according to its weight.
    Value Next() const;


private:

    typedef std::map< Weight, Value > MapType;
    MapType m_map;

    Weight m_sum;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//


template< typename Weight, typename Value >
inline WeightedRandomMap< Weight, Value >::WeightedRandomMap()
    : m_sum( 0 )
{
}


//
// Specialized Traits
//

namespace Detail
{

template< typename T >
struct WeightRandom;

template<>
struct WeightRandom< Int >
{
    static Int Next( Int sum ) { return GenRandomInt( 1, sum ); }
};

template<>
struct WeightRandom< Uint >
{
    static Uint Next( Uint sum ) { return GenRandomUint( 1, sum ); }
};

template<>
struct WeightRandom< Float >
{
    static Float Next( Float sum ) { return GenRandomFloat( 0.0f, sum ); }
};

template<>
struct WeightRandom< Double >
{
    static Double Next( Double sum ) { return GenRandomDouble( 0.0, sum ); }
};


} // namespace Detail


//
// Operations
//

template< typename Weight, typename Value >
inline void WeightedRandomMap< Weight, Value >::Add( Weight weight, const Value& value )
{
    // Weight can't be less than 
    CARAMEL_ASSERT( 0 <= weight );

    // NOTES: If the weight is 0 or too small (when Weight is a floating-point),
    //        the m_map.insert() may failed and the value is just an "impossible" result.
    //        (i.e. the probability is 0 or near-to-zero).

    m_sum += weight;

    m_map.insert( std::make_pair( m_sum, value ));
}


template< typename Weight, typename Value >
inline Value WeightedRandomMap< Weight, Value >::Next() const
{
    CARAMEL_ASSERT( ! m_map.empty() );

    const Weight w = Detail::WeightRandom< Weight >::Next( m_sum );

    return m_map.lower_bound( w )->second;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_RANDOM_WEIGHTED_RANDOM_MAP_H
