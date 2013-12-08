// Caramel C++ Library - Thread Facility - Thread ID Private Header

#ifndef __CARAMEL_THREAD_THREAD_ID_IMPL_H
#define __CARAMEL_THREAD_THREAD_ID_IMPL_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Thread/ThreadId.h>
#include <boost/optional.hpp>
#include <thread>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Thread ID
//

class ThreadIdImpl : public std::thread::id
{
    friend class ThreadId;

public:
    
    explicit ThreadIdImpl( const std::thread::id& threadId );

private:

    boost::optional< Uint32 > m_nativeId;
    
};

typedef std::shared_ptr< ThreadIdImpl > ThreadIdPtr;


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_THREAD_THREAD_ID_IMPL_H
