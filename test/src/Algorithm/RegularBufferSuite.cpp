// Caramel C++ Library Test - Algorithm - Regular Buffer Suite

#include "CaramelTestPch.h"

#include <Caramel/Algorithm/RegularBuffer.h>
#include <Caramel/Random/UniformRandom.h>


namespace Caramel
{

SUITE( RegularBuffer )
{

TEST( RegularBuffer )
{
    RegularBuffer< Uint > buffer( 64 );

    Uint genId = 0;

    for ( Uint i = 0; i < 10000; ++ i )
    {
        std::vector< Uint > piece( GenRandomUsize( 1, 297 ));
        std::generate( piece.begin(), piece.end(), [&] { return genId ++; } );

        buffer.Add( piece );
    }

    RegularBuffer< Uint >::Chunk chunk;
    Uint probeId = 0;

    while ( buffer.TryTake( chunk ))
    {
        CHECK( chunk.Size() == buffer.ChunkSize() );

        for ( Uint i = 0; i < chunk.Size(); ++ i )
        {
            CHECK( probeId ++ == chunk[i] );
        }
    }
}


} // SUITE RegularBuffer

} // namespace Caramel
