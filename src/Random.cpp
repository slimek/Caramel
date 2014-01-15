// Caramel C++ Library - Random Facility - Implementation

#include "CaramelPch.h"

#include "Random/RandomImpl.h"
#include "Random/RandomManager.h"
#include <ctime>
#include <random>


namespace Caramel
{

//
// Contents
//
//   RandomManager
//   Random
//   UniformRandom
//

///////////////////////////////////////////////////////////////////////////////
//
// Random Manager
//

RandomManager::RandomManager()
    : m_random( static_cast< Uint32 >( std::time( nullptr )))
{
}


Int32 RandomManager::GenRandomInt32( Int32 minValue, Int32 maxValue )
{
    std::uniform_int_distribution< Int32 > dist( minValue, maxValue );

    auto ulock = UniqueLock( m_mutex );

    return dist( m_random.GetRef() );
}


Uint32 RandomManager::GenRandomUint32( Uint32 minValue, Uint32 maxValue )
{
    std::uniform_int_distribution< Uint32 > dist( minValue, maxValue );

    auto ulock = UniqueLock( m_mutex );

    return dist( m_random.GetRef() );
}


Float RandomManager::GenRandomFloat( Float lowerBound, Float upperBound )
{
    std::uniform_real_distribution< Float > dist( lowerBound, upperBound );

    auto ulock = UniqueLock( m_mutex );

    return dist( m_random.GetRef() );
}


Double RandomManager::GenRandomDouble( Double lowerBound, Double upperBound )
{
    std::uniform_real_distribution< Double > dist( lowerBound, upperBound );

    auto ulock = UniqueLock( m_mutex );

    return dist( m_random.GetRef() );
}


///////////////////////////////////////////////////////////////////////////////
//
// Random
//

RandomImpl::RandomImpl( Uint32 seed )
    : m_random( seed )
{
}


///////////////////////////////////////////////////////////////////////////////
//
// Uniform Random
//


//
// Stand-alone Functions
//

Int GenRandomInt( Int minValue, Int maxValue )
{
    CARAMEL_ASSERT( minValue <= maxValue );

    return static_cast< Int >( RandomManager::Instance()->
        GenRandomInt32( static_cast< Int32 >( minValue ), static_cast< Int32 >( maxValue )));
}


Uint GenRandomUint( Uint minValue, Uint maxValue )
{
    CARAMEL_ASSERT( minValue <= maxValue );

    return static_cast< Uint >( RandomManager::Instance()->
        GenRandomUint32( static_cast< Uint32 >( minValue ), static_cast< Uint32 >( maxValue )));
}


Float GenRandomFloat( Float lowerBound, Float upperBound )
{
    CARAMEL_ASSERT( lowerBound < upperBound );

    return RandomManager::Instance()->GenRandomFloat( lowerBound, upperBound );
}


Double GenRandomDouble( Double lowerBound, Double upperBound )
{
    CARAMEL_ASSERT( lowerBound < upperBound );

    return RandomManager::Instance()->GenRandomDouble( lowerBound, upperBound );
}


Bool GenRandomBool( Double prob )
{
    return RandomManager::Instance()->GenRandomDouble( 0.0, 1.0 ) < prob;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
