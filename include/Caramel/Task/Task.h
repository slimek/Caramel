// Caramel C++ Library - Task Facility - Task Header

#ifndef __CARAMEL_TASK_TASK_H
#define __CARAMEL_TASK_TASK_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Meta/Utility.h>
#include <Caramel/Task/Detail/TaskFwd.h>
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

    Task( const std::string& name, TaskFunction&& f );


    /// Scheduling ///

    Task& DelayFor( const Ticks& duration );


    /// Retrieve the Result ///

    Result GetResult() const;


    /// Continuation ///

    template< typename ThenFunction >
    typename Detail::ThenFunctionTraits< ThenFunction, Result >::TaskType
    Then( const std::string& name, ThenFunction&& f );

    template< typename ThenFunction, typename AnteResult >
    Task( const std::string& name, ThenFunction&& f, TypeT< AnteResult > );

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

    Task( const std::string& name, TaskFunction&& f );


    /// Scheduling ///

    Task& DelayFor( const Ticks& duration );


    /// Continuation ///

    template< typename ThenFunction >
    typename Detail::ThenFunctionTraits< ThenFunction, void >::TaskType
    Then( const std::string& name, ThenFunction&& f );

    template< typename ThenFunction, typename AnteResult >
    Task( const std::string& name, ThenFunction&& f, TypeT< AnteResult > );

};


//
// Make Task
// - Helper function to make an anonymous task object
//

template< typename Function >
inline auto MakeTask( const std::string& name, Function&& f ) -> Task< decltype( f() ) >
{
    return Task< decltype( f() ) >( name, std::move( f ));
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
inline Task< Result >::Task( const std::string& name, TaskFunction&& f )
    : TaskCore( name, std::make_shared< Detail::RegularTask< Result >>( std::move( f )))
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
    return std::static_pointer_cast< const Detail::BasicTask< Result >>( this->GetHolder() )->GetResult();
}


template< typename Result >
template< typename ThenFunction >
inline typename Detail::ThenFunctionTraits< ThenFunction, Result >::TaskType
Task< Result >::Then( const std::string& name, ThenFunction&& f )
{
    typedef typename Detail::ThenFunctionTraits< ThenFunction, Result >::TaskType TaskType;
    return TaskType( name, std::move( f ), TypeT< Result >() );
}


//
// Task< void >
//

inline Task< void >::Task( const std::string& name, TaskFunction&& f )
    : TaskCore( name, std::make_shared< Detail::RegularTask< void >>( std::move( f )))
{
}


inline Task< void >& Task< void >::DelayFor( const Ticks& duration )
{
    this->DoDelayFor( duration );
    return *this;
}


template< typename ThenFunction >
inline typename Detail::ThenFunctionTraits< ThenFunction, void >::TaskType
Task< void >::Then( const std::string& name, ThenFunction&& f )
{
    typedef typename Detail::ThenFunctionTraits< ThenFunction, void >::TaskType TaskType;
    return TaskType( name, std::move( f ), TypeT< void >() );
}


template< typename ThenFunction, typename AnteResult >
inline Task< void >::Task( const std::string& name, ThenFunction&& f, TypeT< AnteResult > )
    : TaskCore( name, std::make_shared< Detail::ThenTask< void, AnteResult >>( std::move( f )))
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_H
