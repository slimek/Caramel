// Caramel C++ Library - Task Facility - Detail - Task Holders Header

#ifndef __CARAMEL_TASK_DETAIL_TASK_HOLDERS_H
#define __CARAMEL_TASK_DETAIL_TASK_HOLDERS_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Concurrent/Queue.h>
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


template< typename Result >
class ContinuationHolder
{
public:

    virtual ~ContinuationHolder() {}

    virtual void Continue( Task< Result > antecedent ) = 0;
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

    BasicTask( TaskFunction&& f, Task< Result >& host );

    void Invoke() override;

    Result GetResult() const { return m_result; }


private:

    TaskFunction m_function;
    Result m_result;

    Task< Result >& m_host;

    typedef Concurrent::Queue< ContinuationHolder< Result >* > ContinuationQueue;
    ContinuationQueue m_continuations;
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

    BasicTask( TaskFunction&& f, Task< void >& host );

    void Invoke() override;


private:

    TaskFunction m_function;

    Task< void >& m_host;

    typedef Concurrent::Queue< ContinuationHolder< void > > ContinuationQueue;
    ContinuationQueue m_continuations;

};


//
// Then Task
//

template< typename Result, typename AnteResult >
class ThenTask : public BasicTask< Result >
               , public ContinuationHolder< AnteResult >
{
public:

    using BasicTask< Result >::ResultType;
    using BasicTask< Result >::TaskFunction;

    typedef std::function< Result( Task< AnteResult > ) > ThenFunction;

    ThenTask( ThenFunction&& f, Task< Result >& host );

    void Continue( Task< AnteResult > antecedent );

};


//
// Then Task - No result
//

template< typename AnteResult >
class ThenTask< void, AnteResult > : public BasicTask< void >
                                   , public ContinuationHolder< AnteResult >
{
public:

    using BasicTask< void >::ResultType;
    using BasicTask< void >::TaskFunction;

    typedef std::function< void( Task< AnteResult > ) > ThenFunction;

    ThenTask( ThenFunction&& f, Task< void >& host );

    void Continue( Task< AnteResult > antecedent );


private:

    ThenFunction thenFunction;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

//
// BasicTask< Result >
//

template< typename Result >
inline BasicTask< Result >::BasicTask( TaskFunction&& f, Task< Result >& host )
    : m_function( f )
    , m_host( host )
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

inline BasicTask< void >::BasicTask( TaskFunction&& f, Task< void >& host )
    : m_function( f )
    , m_host( host )
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
