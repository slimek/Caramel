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

    explicit BasicTask( Task< Result >& host );

    Result GetResult() const { return m_result; }


protected:

    Result m_result;

private:

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

    explicit BasicTask( Task< void >& host );


private:

    Task< void >& m_host;

    typedef Concurrent::Queue< ContinuationHolder< void > > ContinuationQueue;
    ContinuationQueue m_continuations;

};


//
// Regular Task
//

template< typename Result >
class RegularTask : public BasicTask< Result >
{
public:

    typedef std::function< Result() > TaskFunction;

    RegularTask( TaskFunction&& f, Task< Result >& host );

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

    RegularTask( TaskFunction&& f, Task< void >& host );

    void Invoke() override;

private:
    TaskFunction m_function;
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

    typedef std::function< Result( Task< AnteResult > ) > ThenFunction;

    ThenTask( ThenFunction&& f, Task< Result >& host );

    void Invoke() override;

    void Continue( Task< AnteResult > antecedent ) override;

private:

    ThenFunction m_thenFunction;
    Task< AnteResult > m_antecedent;
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

    typedef std::function< void( Task< AnteResult > ) > ThenFunction;

    ThenTask( ThenFunction&& f, Task< void >& host );

    void Invoke() override;

    void Continue( Task< AnteResult > antecedent ) override;


private:

    ThenFunction m_thenFunction;
    Task< AnteResult > m_antecedent;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

//
// BasicTask< Result >
//

template< typename Result >
inline BasicTask< Result >::BasicTask( Task< Result >& host )
    : m_host( host )
{
}


//
// BasicTask< void >
//

inline BasicTask< void >::BasicTask( Task< void >& host )
    : m_host( host )
{
}


//
// RegularTask
//

template< typename Result >
inline RegularTask< Result >::RegularTask( TaskFunction&& f, Task< Result >& host )
    : BasicTask< Result >( host )
    , m_function( std::move( f ))
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

inline RegularTask< void >::RegularTask( TaskFunction&& f, Task< void >& host )
    : BasicTask< void >( host )
    , m_function( std::move( f ))
{
}


inline void RegularTask< void >::Invoke()
{
    m_function();
}


//
// ThenTask< Result >
//

//
// ThenTask< void >
//

template< typename AnteResult >
inline ThenTask< void, AnteResult >::ThenTask( ThenFunction&& f, Task< void >& host )
    : BasicTask< void >( host )
    , m_thenFunction( std::move( f ))
{
}


template< typename AnteResult >
inline void ThenTask< void, AnteResult >::Invoke()
{
    m_thenFunction( m_antecedent );
}


template< typename AnteResult >
inline void ThenTask< void, AnteResult >::Continue( Task< AnteResult > antecedent )
{
    m_antecedent = antecedent;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_TASK_DETAIL_TASK_HOLDERS_H
