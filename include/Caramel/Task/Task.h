// Caramel C++ Library - Task Facility - Task Header

#ifndef __CARAMEL_TASK_TASK_H
#define __CARAMEL_TASK_TASK_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Memory/UniquePtrUtils.h>
#include <Caramel/Meta/Utility.h>
#include <Caramel/Task/Detail/TaskHolders.h>
#include <Caramel/Task/Detail/TaskTraits.h>
#include <Caramel/Task/TaskCore.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Task
//

template< typename Result >
class Task : public TaskCore
{
public:
    
    typedef Result ResultType;
    typedef std::function< Result() > TaskFunction;


    /// Creation ///

    Task() {}  // Create a "not-a-task". Submit it results in exception.

    explicit Task( TaskFunction f );

    Task( std::string name, TaskFunction f );
    Task( std::string name, std::unique_ptr< Detail::TaskHolder >&& holder );


    /// Scheduling ///

    Task& DelayFor( const Ticks& duration );


    /// Retrieve the Result ///

    Result GetResult() const;


    /// Continuation ///

    template< typename ThenFunction >
    typename Detail::ContinuationTraits< ThenFunction, Result >::TaskType
    Then( std::string name, ThenFunction f );

    // If this task's name is empty, the then task's name would also be empty.
    // Otherwise it's name is "name-Then".
    template< typename ThenFunction >
    typename Detail::ContinuationTraits< ThenFunction, Result >::TaskType
    Then( ThenFunction f );


    /// Continuation by another Executor ///

    template< typename ThenFunction >
    typename Detail::ContinuationTraits< ThenFunction, Result >::TaskType
    Then( std::string name, TaskExecutor& executor, ThenFunction f );

    template< typename ThenFunction >
    typename Detail::ContinuationTraits< ThenFunction, Result >::TaskType
    Then( TaskExecutor& executor, ThenFunction f );
};


//
// Specialization for void - Tasks return no values
//

template<>
class Task< void > : public TaskCore
{
public:

    typedef void ResultType;
    typedef std::function< void() > TaskFunction;


    /// Creation ///

    Task() {}  // Create a "not-a-task". Submit it results in exception.

    explicit Task( TaskFunction f );

    Task( std::string name, TaskFunction f );
    Task( std::string name, std::unique_ptr< Detail::TaskHolder >&& holder );


    /// Scheduling ///

    Task& DelayFor( const Ticks& duration );


    /// Continuation ///

    template< typename ThenFunction >
    typename Detail::ContinuationTraits< ThenFunction, void >::TaskType
    Then( std::string name, ThenFunction f );

    // If this task's name is empty, the then task's name would also be empty.
    // Otherwise it's name is "name-Then".
    template< typename ThenFunction >
    typename Detail::ContinuationTraits< ThenFunction, void >::TaskType
    Then( ThenFunction f );


    /// Continuation by another Executor ///

    template< typename ThenFunction >
    typename Detail::ContinuationTraits< ThenFunction, void >::TaskType
    Then( std::string name, TaskExecutor& executor, ThenFunction f );

    template< typename ThenFunction >
    typename Detail::ContinuationTraits< ThenFunction, void >::TaskType
    Then( TaskExecutor& executor, ThenFunction f );
};


//
// Make Task
// - Helper function to make an anonymous task object
//

template< typename Function >
inline auto MakeTask( Function f ) -> Task< decltype( f() ) >
{
    return Task< decltype( f() ) >( std::move( f ));
}


template< typename Function >
inline auto MakeTask( std::string name, Function f ) -> Task< decltype( f() ) >
{
    return Task< decltype( f() ) >( std::move( name ), std::move( f ));
}


//
// Macros
//

//
// Task of Bind
// - 1. Make the task function of std::bind.
//   2. Use the function name as the task name.
//

#define CARAMEL_TASK_OF_BIND( function, ... ) \
    Caramel::MakeTask( #function, std::bind( &function, ##__VA_ARGS__ ))


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

//
// Task< Result >
//

template< typename Result >
inline Task< Result >::Task( TaskFunction f )
    : TaskCore( std::string(), MakeUnique< Detail::RegularTask< Result >>( std::move( f )))
{
}


template< typename Result >
inline Task< Result >::Task( std::string name, TaskFunction f )
    : TaskCore( std::move( name ), MakeUnique< Detail::RegularTask< Result >>( std::move( f )))
{
}


template< typename Result >
inline Task< Result >::Task( std::string name, std::unique_ptr< Detail::TaskHolder >&& holder )
    : TaskCore( std::move( name ), std::move( holder ))
{
}


template< typename Result >
inline Task< Result >& Task< Result >::DelayFor( const Ticks& duration )
{
    this->DoDelayFor( duration );
    return *this;
}


template< typename Result >
inline Result Task< Result >::GetResult() const
{
    this->Wait();

    return static_cast< const Detail::BasicTask< Result >* >( this->GetHolder() )->GetResult();
}


template< typename AnteResult >
template< typename ThenFunction >
inline typename Detail::ContinuationTraits< ThenFunction, AnteResult >::TaskType
Task< AnteResult >::Then( std::string name, ThenFunction f )
{
    typedef typename Detail::ContinuationTraits< ThenFunction, AnteResult >::HolderType HolderType;
    typedef typename Detail::ContinuationTraits< ThenFunction, AnteResult >::TaskType TaskType;

    // Convert to Detail::TaskHolder explicitly.
    std::unique_ptr< Detail::TaskHolder > thenHolder =
        MakeUnique< HolderType >( std::move( f ), *this );

    auto thenTask = TaskType( std::move( name ), std::move( thenHolder ));
    this->AddContinuation( thenTask );
    return thenTask;
}


template< typename AnteResult >
template< typename ThenFunction >
inline typename Detail::ContinuationTraits< ThenFunction, AnteResult >::TaskType
Task< AnteResult >::Then( ThenFunction f )
{
    return this->Then( this->MakeDefaultThenTaskName(), std::move( f ));
}


template< typename AnteResult >
template< typename ThenFunction >
inline typename Detail::ContinuationTraits< ThenFunction, AnteResult >::TaskType
Task< AnteResult >::Then( std::string name, TaskExecutor& executor, ThenFunction f )
{
    typedef typename Detail::ContinuationTraits< ThenFunction, AnteResult >::HolderType HolderType;
    typedef typename Detail::ContinuationTraits< ThenFunction, AnteResult >::TaskType TaskType;

    // Convert to Detail::TaskHolder explicitly.
    std::unique_ptr< Detail::TaskHolder > thenHolder =
        MakeUnique< HolderType >( std::move( f ), *this );

    auto thenTask = TaskType( std::move( name ), std::move( thenHolder ));
    this->AddContinuation( executor, thenTask );
    return thenTask;
}


template< typename AnteResult >
template< typename ThenFunction >
inline typename Detail::ContinuationTraits< ThenFunction, AnteResult >::TaskType
Task< AnteResult >::Then( TaskExecutor& executor, ThenFunction f )
{
    return this->Then( this->MakeDefaultThenTaskName(), executor, std::move( f ));
}


//
// Task< void >
//

inline Task< void >::Task( TaskFunction f )
    : TaskCore( std::string(), MakeUnique< Detail::RegularTask< void >>( std::move( f )))
{
}


inline Task< void >::Task( std::string name, TaskFunction f )
    : TaskCore( std::move( name ), MakeUnique< Detail::RegularTask< void >>( std::move( f )))
{
}


inline Task< void >::Task( std::string name, std::unique_ptr< Detail::TaskHolder >&& holder )
    : TaskCore( std::move( name ), std::move( holder ))
{
}


inline Task< void >& Task< void >::DelayFor( const Ticks& duration )
{
    this->DoDelayFor( duration );
    return *this;
}


template< typename ThenFunction >
inline typename Detail::ContinuationTraits< ThenFunction, void >::TaskType
Task< void >::Then( std::string name, ThenFunction f )
{
    typedef typename Detail::ContinuationTraits< ThenFunction, void >::HolderType HolderType;
    typedef typename Detail::ContinuationTraits< ThenFunction, void >::TaskType TaskType;

    // Convert to Detail::TaskHolder explicitly.
    std::unique_ptr< Detail::TaskHolder > thenHolder =
        MakeUnique< HolderType >( std::move( f ), *this );

    auto thenTask = TaskType( std::move( name ), std::move( thenHolder ));
    this->AddContinuation( thenTask );
    return thenTask;
}


template< typename ThenFunction >
inline typename Detail::ContinuationTraits< ThenFunction, void >::TaskType
Task< void >::Then( ThenFunction f )
{
    return this->Then( this->MakeDefaultThenTaskName(), std::move( f ));
}


template< typename ThenFunction >
inline typename Detail::ContinuationTraits< ThenFunction, void >::TaskType
Task< void >::Then( std::string name, TaskExecutor& executor, ThenFunction f )
{
    typedef typename Detail::ContinuationTraits< ThenFunction, void >::HolderType HolderType;
    typedef typename Detail::ContinuationTraits< ThenFunction, void >::TaskType TaskType;

    // Convert to Detail::TaskHolder explicitly.
    std::unique_ptr< Detail::TaskHolder > thenHolder =
        MakeUnique< HolderType >( std::move( f ), *this );

    auto thenTask = TaskType( std::move( name ), std::move( thenHolder ));
    this->AddContinuation( executor, thenTask );
    return thenTask;
}


template< typename ThenFunction >
inline typename Detail::ContinuationTraits< ThenFunction, void >::TaskType
Task< void >::Then( TaskExecutor& executor, ThenFunction f )
{
    return this->Then( this->MakeDefaultThenTaskName(), executor, std::move( f ));
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_H
