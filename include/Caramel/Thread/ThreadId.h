// Caramel C++ Library - Thread Facility - Thread ID Header

#ifndef __CARAMEL_THREAD_THREAD_ID_H
#define __CARAMEL_THREAD_THREAD_ID_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Thread/ThreadTypes.h>
#include <boost/operators.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Thread ID
// - An identifier to represent a thread.
//   It can be compared, but no arithmetic operation.
//   The implementation depends on the operating systems.
//

class ThreadIdImpl;

class ThreadId : public boost::totally_ordered< ThreadId >
{
    friend class ThisThread;
    friend class Thread;

public:

    // Default is "Not a thread ID".
    ThreadId();

    
    /// Operators ///

    Bool operator==( const ThreadId& rhs ) const;
    Bool operator< ( const ThreadId& rhs ) const;


    /// Properties ///

    std::string ToString() const;

    Uint32 GetNativeId() const;


private:

    explicit ThreadId( std::shared_ptr< ThreadIdImpl > impl );

    std::shared_ptr< ThreadIdImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_THREAD_THREAD_ID_H
