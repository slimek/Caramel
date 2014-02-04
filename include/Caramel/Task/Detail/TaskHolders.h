// Caramel C++ Library - Task Facility - Detail - Task Holders Header

#ifndef __CARAMEL_TASK_DETAIL_TASK_HOLDERS_H
#define __CARAMEL_TASK_DETAIL_TASK_HOLDERS_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Task/Detail/TaskFwd.h>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Task Holder
//

class TaskHolder
{
public:
    
    virtual ~TaskHolder() {}

    virtual void Invoke() = 0;
};


//
// Basic Task
//

template< typename Result >
class BasicTask : public TaskHolder
{
public:

    typedef Result ResultType;
    typedef std::function< Result() > TaskFunction;

    BasicTask( TaskFunction&& f );

    void Invoke() override;

    Result GetResult() const { return m_result; }


private:

    TaskFunction m_function;
    Result m_result;
};


//
// Basic Task - No result
//

template<>
class BasicTask< void > : public TaskHolder
{
public:

    typedef void ResultType;
    typedef std::function< void() > TaskFunction;

    BasicTask( TaskFunction&& f );

    void Invoke() override;


private:

    TaskFunction m_function;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

//
// BasicTask< Result >
//

template< typename Result >
inline BasicTask< Result >::BasicTask( TaskFunction&& f )
    : m_function( f )
{
}


template< typename Result >
inline void BasicTask< Result >::Invoke()
{
    m_result = m_function();
}


//
// BasicTask< void >
//

inline BasicTask< void >::BasicTask( TaskFunction&& f )
    : m_function( f )
{
}


inline void BasicTask< void >::Invoke()
{
    m_function();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_TASK_DETAIL_TASK_HOLDERS_H
