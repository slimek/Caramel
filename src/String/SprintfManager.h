// Caramel C++ Library - String Facility - Sprintf Manager Header

#ifndef __CARAMEL_STRING_SPRINTF_MANAGER_H
#define __CARAMEL_STRING_SPRINTF_MANAGER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Object/FacilityLongevity.h"
#include <Caramel/Concurrent/Queue.h>
#include <Caramel/Object/Singleton.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Sprintf Buffer
// - Element buffer for Sprintf() to work.
//

class SprintfBuffer
{
public:

    static const Uint SIZE = 3968;   // 64 x 62 bytes, available buffer size
                                     // A little less than 4 KB page.
    SprintfBuffer();

    Char* GetPointer() { return m_buffer; }

    Bool CheckGuard() const;


private:

    static const Uint8  PAD_CHAR   = 0xD3;
    static const Uint32 TAIL_GUARD = 0xD3DED700;

    static const Uint BUFFER_ALIGN = 64;    // Common CPU cache line length.

    static const Uint CHUNK_SIZE   = SIZE + BUFFER_ALIGN + 4;  // 4 : size of the tail guard

    Char* m_buffer;
    Char  m_chunk[ CHUNK_SIZE ];
};


///////////////////////////////////////////////////////////////////////////////
//
// Sprintf Manager
// - Provide a cyclic list of buffers.
//

class SprintfManager : public Singleton< SprintfManager, FACILITY_LONGEVITY_SPRINTF >
{
public:

    SprintfManager();
    ~SprintfManager();

    SprintfBuffer* AllocateBuffer();
    void FreeBuffer( SprintfBuffer* buffer );


private:

    typedef Concurrent::Queue< SprintfBuffer* > BufferQueue;
    BufferQueue m_buffers;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_SPRINTF_MANAGER_H
