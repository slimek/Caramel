// Caramel C++ Library - Thread Facility - Thread Header

#ifndef __CARAMEL_THREAD_THREAD_H
#define __CARAMEL_THREAD_THREAD_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Thread/ThreadTypes.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Thread
//

class ThreadImpl;

class Thread final
{
public:

    Thread();

    Thread( std::string name, WorkFunction work );

    ~Thread();


    /// Thread Operations ///

    void Start( std::string name, WorkFunction work );

    void Join();


    /// Properties ///

    ThreadId GetId() const;


private:

    std::unique_ptr< ThreadImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_THREAD_THREAD_H
