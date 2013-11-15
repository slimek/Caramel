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


Int RandomManager::GenRandomInt( Int minValue, Int maxValue )
{
    auto ulock = UniqueLock( m_mutex );

    return static_cast< Int32 >( m_random.
        NextInt32( static_cast< Int32 >( minValue ), static_cast< Int32 >( maxValue )));
}


Uint RandomManager::GenRandomUint( Uint minValue, Uint maxValue )
{
    auto ulock = UniqueLock( m_mutex );

    return static_cast< Uint32 >( m_random.
        NextUint32( static_cast< Uint32 >( minValue ), static_cast< Uint32 >( maxValue ))
    );
}


///////////////////////////////////////////////////////////////////////////////
//
// Random
//

RandomImpl::RandomImpl( Uint32 seed )
    : m_random( seed )
{
}


//
// Generate Functions
//

Int32 RandomImpl::NextInt32( Int32 minValue, Int32 maxValue )
{
    std::uniform_int< Int32 > dist( minValue, maxValue );
    return dist( m_random );
}


Uint32 RandomImpl::NextUint32( Uint32 minValue, Uint32 maxValue )
{
    std::uniform_int< Uint32 > dist( minValue, maxValue );
    return dist( m_random );
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

    return RandomManager::Instance()->GenRandomInt( minValue, maxValue );
}


Uint GenRandomUint( Uint minValue, Uint maxValue )
{
    CARAMEL_ASSERT( minValue <= maxValue );

    return RandomManager::Instance()->GenRandomUint( minValue, maxValue );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
