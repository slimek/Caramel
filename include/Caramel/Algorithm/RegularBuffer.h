// Caramel C++ Library - Algorithm Amenity - Regular Buffer Header

#ifndef __CARAMEL_ALGORITHM_REGULAR_BUFFER_H
#define __CARAMEL_ALGORITHM_REGULAR_BUFFER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Value/SharedArray.h>
#include <algorithm>
#include <queue>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Regular Buffer
//
// - You may feed this buffer with pieces of various length,
//   and get chunks with the same size.
//
// - Requirements:
//   1. The value type of InputPiece must be copyable to T.
//   2. InputPiece must supports begin(), end() and size().
//
// - Remarks: This class is NOT thread-safe.
//

template< typename T >
class RegularBuffer
{
public:

    RegularBuffer( Usize chunkSize );


    /// Operations ///

    template< typename InputPiece >
    void Add( const InputPiece& input );

    typedef SharedArray< T > Chunk;

    Bool TryTake( Chunk& output );


    /// Properties ///

    Usize ChunkSize() const { return m_chunkSize; }


private:

    void PushWorkingChunk();


    Usize m_chunkSize;

    Chunk m_workingChunk;
    Usize m_written;  // How many values are already written into the working chunk.

    std::queue< Chunk > m_chunkQueue;
    
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename T >
inline RegularBuffer< T >::RegularBuffer( Usize chunkSize )
    : m_chunkSize( chunkSize )
    , m_workingChunk( chunkSize )
    , m_written( 0 )
{}


template< typename T >
template< typename InputPiece >
inline void RegularBuffer< T >::Add( const InputPiece& input )
{
    Usize readIndex = 0;
    Usize remain = input.size();
    Usize spare = m_chunkSize - m_written;  // the rest space can be written into the working chunk.

    // If the remain of input are larger then the spare of working chunk :
    // - Write it as possible, then prepare a new working buffer.

    while ( remain > spare )
    {
        auto srcIt = input.begin() + readIndex;
        auto destIt = m_workingChunk.begin() + m_written;
        std::copy( srcIt, srcIt + spare, destIt );  // copy length : spare

        this->PushWorkingChunk();

        readIndex += spare;
        remain = input.size() - readIndex;
        spare = m_chunkSize;
    }

    // Write all content in input into the working chunk.

    auto srcIt = input.begin() + readIndex;
    auto destIt = m_workingChunk.begin() + m_written;
    std::copy( srcIt, srcIt + remain, destIt );  // copy lenght : remain

    m_written += remain;
    if ( m_written == m_chunkSize )
    {
        this->PushWorkingChunk();
    }
}


template< typename T >
inline Bool RegularBuffer< T >::TryTake( Chunk& output )
{
    if ( m_chunkQueue.empty() ) { return false; }

    output = m_chunkQueue.front();
    m_chunkQueue.pop();
    return true;
}


template< typename T >
inline void RegularBuffer< T >::PushWorkingChunk()
{
    m_chunkQueue.push( m_workingChunk );
    m_workingChunk = Chunk( m_chunkSize );
    m_written = 0;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ALGORITHM_REGULAR_BUFFER_H
