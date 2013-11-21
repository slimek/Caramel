// Caramel C++ Library - Random Facility - Random Private Header

#ifndef __CARAMEL_RANDOM_RANDOM_IMPL_H
#define __CARAMEL_RANDOM_RANDOM_IMPL_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <random>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Random
//

class RandomImpl
{
public:

    explicit RandomImpl( Uint32 seed );


    /// Generator Accessor ///

    typedef std::mt19937 RandomType;

    static_assert( std::is_same< RandomType::result_type, Uint32 >::value,
                   "Random result type must be Uint32" );

    RandomType& GetRef() { return m_random; }


private:

    RandomType m_random;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_RANDOM_RANDOM_IMPL_H
