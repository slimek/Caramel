// Caramel C++ Library - Task Facility - Detail - Task Traits Header

#ifndef __CARAMEL_TASK_DETAIL_TASK_TRAITS_H
#define __CARAMEL_TASK_DETAIL_TASK_TRAITS_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Task/Detail/TaskFwd.h>
#include <Caramel/Task/Detail/TaskHolders.h>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Task Function Traits
//

template< typename Function, typename AnteResult >
struct ThenFunctionTraits
{
    typedef decltype( std::declval< Function >()( Task< AnteResult >() )) ResultType;
    typedef Task< ResultType > TaskType;
};

template< typename T >
T&& Declval();


template< typename Type >
Task< Type > ToTask( Type );

template< typename Function >
Task< void > ToTaskVoid( Function );

struct BadContinuationParamType {};


template< typename Function, typename Type >
auto ReturnTypeHelper( Type t, Function func, int, int ) -> decltype( func( ToTask( t )));

template< typename Function, typename Type >
auto ReturnTypeHelper( Type t, Function func, int, ... ) -> decltype( func( t ));

template< typename Function, typename Type >
auto ReturnTypeHelper( Type t, Function func, ... ) -> BadContinuationParamType;


template< typename Function, typename ExpectedParameterType >
struct FunctionTypeTraits
{
    typedef decltype( ReturnTypeHelper( std::declval< ExpectedParameterType > (), std::declval< Function >(), 0, 0 )) FuncRetType;
};


template< typename Function >
auto VoidReturnTypeHelper( Function func, int, int ) -> decltype( func( ToTaskVoid( func )));

template< typename Function >
auto VoidReturnTypeHelper( Function func, int, ... ) -> decltype( func() );

template< typename Function >
struct FunctionTypeTraits< Function, void >
{
    typedef decltype( VoidReturnTypeHelper( std::declval< Function >(), 0, 0 )) FuncRetType;
};


//
// Then Function Traits
//

template< typename ThenFunction, typename AnteResult >
struct ThenFunctionTraits2
{

};


template< typename ThenFunction >
struct ThenFunctionTraits2< ThenFunction, void >
{
    typedef decltype( VoidReturnTypeHelper( std::declval< ThenFunction >(), 0, 0 )) ResultType;
};


//
// Continuation Traits
//

template< typename ThenFunction, typename AnteResult >
struct ContinuationTraits
{
    //typedef typename FunctionTypeTraits< Function, AnteResult >::FuncRetType FuncRetType;

    typedef ThenWithTaskTask< void, AnteResult > HolderType;
    typedef Task< void > TaskType;
};


template< typename ThenFunction >
struct ContinuationTraits< ThenFunction, void >
{
    typedef typename ThenFunctionTraits2< ThenFunction, void >::ResultType ResultType;

    typedef ThenWithTaskTask< ResultType, void > HolderType;
    typedef Task< ResultType > TaskType;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detial

} // namespace Caramel

#endif // __CARAMEL_TASK_DETAIL_TASK_TRAITS_H
