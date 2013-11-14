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

Uint GenRandomUint( Uint minValue, Uint maxValue )
{
    return RandomManager::Instance()->GenRandomUint( minValue, maxValue );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
