// Caramel C++ Library - Task Facility - Detail - Task Holders Header

#ifndef __CARAMEL_TASK_DETAIL_TASK_HOLDERS_H
#define __CARAMEL_TASK_DETAIL_TASK_HOLDERS_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
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


//
// Basic Task
//

template< typename Result >
class BasicTask : public TaskHolder
{
public:

    typedef Result ResultType;

    Result GetResult() const { return m_result; }

protected:
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
};


//
// Regular Task
//

template< typename Result >
class RegularTask : public BasicTask< Result >
{
public:

    using typename BasicTask< Result >::ResultType;
    using BasicTask< Result >::m_result;

    typedef std::function< Result() > TaskFunction;

    explicit RegularTask( TaskFunction&& f );

    void Invoke() override;

private:
    TaskFunction m_function;
};


//
// Regular Task - No Result
// - Only the Invoke() function is specialized
//

template<>
class RegularTask< void > : public BasicTask< void >
{
public:
    
    typedef std::function< void() > TaskFunction;

    explicit RegularTask( TaskFunction&& f );

    void Invoke() override;

private:
    TaskFunction m_function;
};


//
// "Then with Task" Task
//

template< typename Result, typename AnteResult >
class ThenWithTaskTask : public BasicTask< Result >
{
public:

    using typename BasicTask< Result >::ResultType;
    using BasicTask< Result >::m_result;

    typedef std::function< Result( Task< AnteResult > ) > ThenFunction;

    ThenWithTaskTask( ThenFunction&& f, Task< AnteResult > antecedent );

    void Invoke() override;

private:

    ThenFunction m_thenFunction;
    Task< AnteResult > m_antecedent;
};


//
// "Then with Task" Task - No result
//

template< typename AnteResult >
class ThenWithTaskTask< void, AnteResult > : public BasicTask< void >
{
public:

    typedef std::function< void( Task< AnteResult > ) > ThenFunction;

    ThenWithTaskTask( ThenFunction&& f, Task< AnteResult > antecedent );

    void Invoke() override;


private:

    ThenFunction m_thenFunction;
    Task< AnteResult > m_antecedent;
};


//
// "Then with Void" Task 
//

template< typename Result >
class ThenWithVoidTask : public BasicTask< Result >
{
public:

    using typename BasicTask< Result >::ResultType;
    using BasicTask< Result >::m_result;

    typedef std::function< Result() > ThenFunction;

    ThenWithVoidTask( ThenFunction&& f, const TaskCore& );

    void Invoke() override;

private:

    ThenFunction m_thenFunction;
};


//
// "Then with Void" Task - No Result
//

template<>
class ThenWithVoidTask< void > : public BasicTask< void >
{
public:

    typedef std::function< void() > ThenFunction;

    ThenWithVoidTask( ThenFunction&& f, const TaskCore& );

    void Invoke() override;

private:

    ThenFunction m_thenFunction;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

//
// RegularTask
//

template< typename Result >
inline RegularTask< Result >::RegularTask( TaskFunction&& f )
    : m_function( std::move( f ))
{
}


template< typename Result >
inline void RegularTask< Result >::Invoke()
{
    m_result = m_function();

}


//
// RegularTask< void >
//

inline RegularTask< void >::RegularTask( TaskFunction&& f )
    : m_function( std::move( f ))
{
}


inline void RegularTask< void >::Invoke()
{
    m_function();
}


//
// ThenWithTaskTask< Result >
//

template< typename Result, typename AnteResult >
inline ThenWithTaskTask< Result, AnteResult >::ThenWithTaskTask( ThenFunction&& f, Task< AnteResult > antecedent )
    : m_thenFunction( std::move( f ))
    , m_antecedent( antecedent )
{
}


template< typename Result, typename AnteResult >
inline void ThenWithTaskTask< Result, AnteResult >::Invoke()
{
    m_result = m_thenFunction( m_antecedent );
}


//
// ThenWithTaskTask< void >
//

template< typename AnteResult >
inline ThenWithTaskTask< void, AnteResult >::ThenWithTaskTask( ThenFunction&& f, Task< AnteResult > antecedent )
    : m_thenFunction( std::move( f ))
    , m_antecedent( antecedent )
{
}


template< typename AnteResult >
inline void ThenWithTaskTask< void, AnteResult >::Invoke()
{
    m_thenFunction( m_antecedent );
}


//
// ThenWithVoidTask< void >
//

inline ThenWithVoidTask< void >::ThenWithVoidTask( ThenFunction&& f, const TaskCore& )
    : m_thenFunction( std::move( f ))
{
}


inline void ThenWithVoidTask< void >::Invoke()
{
    m_thenFunction();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_TASK_DETAIL_TASK_HOLDERS_H
