// Caramel C++ Library - String Facility - Sprintf Manager Header

#ifndef __CARAMEL_STRING_SPRINTF_MANAGER_H
#define __CARAMEL_STRING_SPRINTF_MANAGER_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Object/Singleton.h>
#include <Caramel/Object/FacilityLongevity.h>
#include <boost/lockfree/stack.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Sprintf Buffer
// - Element buffer for Sprintf() to work.
//

class SprintfBuffer
{
    static const Uint8  PAD_CHAR   = 0xD3;
    static const Uint32 TAIL_GUARD = 0xD3DED7DE;

    static const Uint CHUNK_SIZE   = 4048;  // <= 4096 - 48 , a little less than 4 KB page.
    static const Uint BUFFER_ALIGN = 64;    // Common CPU cache line length.

public:

    static const Uint SIZE = 3968;   // 64 x 62 bytes, available buffer size

    SprintfBuffer();
    ~SprintfBuffer();

    void Clear();

    Char* GetPointer() { return m_buffer; }


private:

    Char* m_chunk;
    Char* m_buffer;

    Uint32* m_tailGuard;
};


///////////////////////////////////////////////////////////////////////////////
//
// Sprintf Manager
// - Provide a cyclic list of buffers.
//

class SprintfManager : public Singleton< SprintfManager, FACILITY_LONGEVITY_SPRINTF >
{
public:

    ~SprintfManager();

    SprintfBuffer* AllocateBuffer();
    void FreeBuffer( SprintfBuffer* buffer );


private:

    typedef boost::lockfree::stack< SprintfBuffer* > BufferStack;
    BufferStack m_buffers;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_SPRINTF_MANAGER_H
