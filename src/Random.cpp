// Caramel C++ Library - Random Facility - Implementation

#include "CaramelPch.h"

#include "Random/RandomImpl.h"
#include "Random/RandomManager.h"
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
    : m_random( std::random_device()() )
{
}


Int32 RandomManager::GenRandomInt32( Int32 minValue, Int32 maxValue )
{
    std::uniform_int_distribution< Int32 > dist( minValue, maxValue );

    LockGuard lock( m_mutex );

    return dist( m_random.GetRef() );
}


Uint32 RandomManager::GenRandomUint32( Uint32 minValue, Uint32 maxValue )
{
    std::uniform_int_distribution< Uint32 > dist( minValue, maxValue );

    LockGuard lock( m_mutex );

    return dist( m_random.GetRef() );
}


Uint64 RandomManager::GenRandomUint64( Uint64 minValue, Uint64 maxValue )
{
    std::uniform_int_distribution< Uint64 > dist( minValue, maxValue );

    LockGuard lock( m_mutex );

    return dist( m_random.GetRef() );
}


Float RandomManager::GenRandomFloat( Float lowerBound, Float upperBound )
{
    std::uniform_real_distribution< Float > dist( lowerBound, upperBound );

    LockGuard lock( m_mutex );

    return dist( m_random.GetRef() );
}


Double RandomManager::GenRandomDouble( Double lowerBound, Double upperBound )
{
    std::uniform_real_distribution< Double > dist( lowerBound, upperBound );

    LockGuard lock( m_mutex );

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

    return RandomManager::Instance()->GenRandomInt32( minValue, maxValue );
}


Uint GenRandomUint( Uint minValue, Uint maxValue )
{
    CARAMEL_ASSERT( minValue <= maxValue );

    return RandomManager::Instance()->GenRandomUint32( minValue, maxValue );
}


Uint64 GenRandomUint64( Uint64 minValue, Uint64 maxValue )
{
    CARAMEL_ASSERT( minValue <= maxValue );

    return RandomManager::Instance()->GenRandomUint64( minValue, maxValue );
}


Usize GenRandomUsize( Usize minValue, Usize maxValue )
{
    CARAMEL_ASSERT( minValue <= maxValue );

    #if defined( CARAMEL_SYSTEM_IS_64_BIT )
    {
        return RandomManager::Instance()->GenRandomUint64( minValue, maxValue );
    }
    #else
    {
        return RandomManager::Instance()->GenRandomUint32( minValue, maxValue );
    }
    #endif
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
