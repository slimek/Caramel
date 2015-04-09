// Caramel C++ Library - Task Facility - Detail - Task Traits Header

#ifndef __CARAMEL_TASK_DETAIL_TASK_TRAITS_H
#define __CARAMEL_TASK_DETAIL_TASK_TRAITS_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Task/TaskFwd.h>
#include <Caramel/Task/Detail/TaskHolders.h>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Traits Types
//

//
// Primary Template - This is our target.
//
template< typename ThenFunction, typename AnteResult >
struct ContinuationTraits;


//
// Stuff
//

template< typename T > T&& Declval();


template< typename Type >
Task< Type > ToTask( Type );

template< typename Function >
Task< void > ToTaskVoid( Function );


template< typename Function, typename Type >
auto ReturnTypeHelper( Type t, Function func, int, int ) -> decltype( func( ToTask( t )));

template< typename Function, typename Type >
auto ReturnTypeHelper( Type t, Function func, int, ... ) -> decltype( func( t ));

template< typename Function, typename Type >
auto ReturnTypeHelper( Type t, Function func, ... ) -> decltype( func() );


template< typename Function, typename Type >
auto TakesTaskHelper( Type t, Function func, int, int ) -> decltype( func( ToTask( t )), std::true_type() );

template< typename Function, typename Type >
std::false_type TakesTaskHelper( Type t, Function func, int, ... );


template< typename Function, typename Type >
auto TakesValueHelper( Type t, Function func, int, int ) -> decltype( func( t ), std::true_type() );

template< typename Function, typename Type >
std::false_type TakesValueHelper( Type t, Function func, int, ... );


template< typename Function >
auto VoidReturnTypeHelper( Function func, int, int ) -> decltype( func( ToTaskVoid( func )));

template< typename Function >
auto VoidReturnTypeHelper( Function func, int, ... ) -> decltype( func() );


template< typename Function >
auto VoidTakesTaskHelper( Function func, int, int ) -> decltype( func( ToTaskVoid( func )), std::true_type() );

template< typename Function >
std::false_type VoidTakesTaskHelper( Function func, int, ... );


//
// Then Function Traits
//

template< typename ThenFunction, typename AnteResult >
struct ThenFunctionTraits
{
    typedef decltype( ReturnTypeHelper( Declval< AnteResult >(), Declval< ThenFunction >(), 0, 0 )) ResultType;
    typedef decltype( TakesTaskHelper ( Declval< AnteResult >(), Declval< ThenFunction >(), 0, 0 )) TakesTask;
    typedef decltype( TakesValueHelper( Declval< AnteResult >(), Declval< ThenFunction >(), 0, 0 )) TakesValue;
};


template< typename ThenFunction >
struct ThenFunctionTraits< ThenFunction, void >
{
    typedef decltype( VoidReturnTypeHelper( Declval< ThenFunction >(), 0, 0 )) ResultType;
    typedef decltype( VoidTakesTaskHelper ( Declval< ThenFunction >(), 0, 0 )) TakesTask;
};


//
// Continuation Traits
//

template< typename ThenFunction, typename AnteResult >
struct ContinuationTraits
{
    typedef typename ThenFunctionTraits< ThenFunction, AnteResult >::ResultType ResultType;

    typedef typename std::conditional
    <
        ThenFunctionTraits< ThenFunction, AnteResult >::TakesTask::value,
        ThenWithTaskTask< ResultType, AnteResult >,
        typename std::conditional
        <
            ThenFunctionTraits< ThenFunction, AnteResult >::TakesValue::value,
            ThenWithValueTask< ResultType, AnteResult >,
            ThenWithVoidTask< ResultType >
        >::type

    >::type HolderType;

    typedef Task< ResultType > TaskType;
};


template< typename ThenFunction >
struct ContinuationTraits< ThenFunction, void >
{
    typedef typename ThenFunctionTraits< ThenFunction, void >::ResultType ResultType;

    typedef typename std::conditional
    <
        ThenFunctionTraits< ThenFunction, void >::TakesTask::value,
        ThenWithTaskTask< ResultType, void >,
        ThenWithVoidTask< ResultType >
    
    >::type HolderType;
        
    typedef Task< ResultType > TaskType;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detial

} // namespace Caramel

#endif // __CARAMEL_TASK_DETAIL_TASK_TRAITS_H
