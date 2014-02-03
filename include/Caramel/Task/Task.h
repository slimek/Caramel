// Caramel C++ Library - Task Facility - Task Header

#ifndef __CARAMEL_TASK_TASK_H
#define __CARAMEL_TASK_TASK_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Task/Detail/TaskFwd.h>
#include <Caramel/Task/Detail/TaskHolders.h>
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
    : TaskCore( name, new Detail::BasicTask< Result >( std::move( f )))
{
}


template< typename Result >
inline Task< Result >& Task< Result >::DelayFor( const Ticks& duration )
{
    this->DoDelayFor( duration );
    return *this;
}


//
// Task< void >
//

inline Task< void >::Task( const std::string& name, TaskFunction&& f )
    : TaskCore( name, new Detail::BasicTask< void >( std::move( f )))
{
}


inline Task< void >& Task< void >::DelayFor( const Ticks& duration )
{
    this->DoDelayFor( duration );
    return *this;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_H
