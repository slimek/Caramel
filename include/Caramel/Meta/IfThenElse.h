// Caramel C++ Library - Metaprogramming Amenity - If-Then-Else Header

#ifndef __CARAMEL_META_IF_THEN_ELSE_H
#define __CARAMEL_META_IF_THEN_ELSE_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Meta/Select.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// If-Then-Else Type Selecting
//

template< Bool cond0, typename T0, typename Default >
struct IfThenElse1T
    : public SelectT< cond0, T0, Default >
{};

template< Bool cond0, typename T0, Bool cond1, typename T1, typename Default >
struct IfThenElse2T
    : public SelectT< cond0, T0, SelectT< cond1, T1, Default > >
{};

template< Bool cond0, typename T0, Bool cond1, typename T1, Bool cond2, typename T2, typename Default >
struct IfThenElse3T
    : public SelectT< cond0, T0, SelectT< cond1, T1, SelectT< cond2, T2, Default > > >
{};

template< Bool cond0, typename T0, Bool cond1, typename T1, Bool cond2, typename T2, Bool cond3, typename T3, typename Default >
struct IfThenElse4T
    : public SelectT< cond0, T0, SelectT< cond1, T1, SelectT< cond2, T2, SelectT< cond3, T3, Default > > > >
{};

template< Bool cond0, typename T0, Bool cond1, typename T1, Bool cond2, typename T2, Bool cond3, typename T3, Bool cond4, typename T4, typename Default >
struct IfThenElse5T
    : public SelectT< cond0, T0, SelectT< cond1, T1, SelectT< cond2, T2, SelectT< cond3, T3, SelectT< cond4, T4, Default > > > > >
{};

template< Bool cond0, typename T0, Bool cond1, typename T1, Bool cond2, typename T2, Bool cond3, typename T3, Bool cond4, typename T4, Bool cond5, typename T5, typename Default >
struct IfThenElse6T
    : public SelectT< cond0, T0, SelectT< cond1, T1, SelectT< cond2, T2, SelectT< cond3, T3, SelectT< cond4, T4, SelectT< cond5, T5, Default > > > > > >
{};

template< Bool cond0, typename T0, Bool cond1, typename T1, Bool cond2, typename T2, Bool cond3, typename T3, Bool cond4, typename T4, Bool cond5, typename T5, Bool cond6, typename T6, typename Default >
struct IfThenElse7T
    : public SelectT< cond0, T0, SelectT< cond1, T1, SelectT< cond2, T2, SelectT< cond3, T3, SelectT< cond4, T4, SelectT< cond5, T5, SelectT< cond6, T6, Default > > > > > > >
{};

template< Bool cond0, typename T0, Bool cond1, typename T1, Bool cond2, typename T2, Bool cond3, typename T3, Bool cond4, typename T4, Bool cond5, typename T5, Bool cond6, typename T6, Bool cond7, typename T7, typename Default >
struct IfThenElse8T
    : public SelectT< cond0, T0, SelectT< cond1, T1, SelectT< cond2, T2, SelectT< cond3, T3, SelectT< cond4, T4, SelectT< cond5, T5, SelectT< cond6, T6, SelectT< cond7, T7, Default > > > > > > > >
{};

template< Bool cond0, typename T0, Bool cond1, typename T1, Bool cond2, typename T2, Bool cond3, typename T3, Bool cond4, typename T4, Bool cond5, typename T5, Bool cond6, typename T6, Bool cond7, typename T7, Bool cond8, typename T8, typename Default >
struct IfThenElse9T
    : public SelectT< cond0, T0, SelectT< cond1, T1, SelectT< cond2, T2, SelectT< cond3, T3, SelectT< cond4, T4, SelectT< cond5, T5, SelectT< cond6, T6, SelectT< cond7, T7, SelectT< cond8, T8, Default > > > > > > > > >
{};

template< Bool cond0, typename T0, Bool cond1, typename T1, Bool cond2, typename T2, Bool cond3, typename T3, Bool cond4, typename T4, Bool cond5, typename T5, Bool cond6, typename T6, Bool cond7, typename T7, Bool cond8, typename T8, Bool cond9, typename T9, typename Default >
struct IfThenElse10T
    : public SelectT< cond0, T0, SelectT< cond1, T1, SelectT< cond2, T2, SelectT< cond3, T3, SelectT< cond4, T4, SelectT< cond5, T5, SelectT< cond6, T6, SelectT< cond7, T7, SelectT< cond8, T8, SelectT< cond9, T9, Default > > > > > > > > > >
{};

template< Bool cond0, typename T0, Bool cond1, typename T1, Bool cond2, typename T2, Bool cond3, typename T3, Bool cond4, typename T4, Bool cond5, typename T5, Bool cond6, typename T6, Bool cond7, typename T7, Bool cond8, typename T8, Bool cond9, typename T9, Bool cond10, typename T10, typename Default >
struct IfThenElse11T
    : public SelectT< cond0, T0, SelectT< cond1, T1, SelectT< cond2, T2, SelectT< cond3, T3, SelectT< cond4, T4, SelectT< cond5, T5, SelectT< cond6, T6, SelectT< cond7, T7, SelectT< cond8, T8, SelectT< cond9, T9, SelectT< cond10, T10, Default > > > > > > > > > > >
{};

template< Bool cond0, typename T0, Bool cond1, typename T1, Bool cond2, typename T2, Bool cond3, typename T3, Bool cond4, typename T4, Bool cond5, typename T5, Bool cond6, typename T6, Bool cond7, typename T7, Bool cond8, typename T8, Bool cond9, typename T9, Bool cond10, typename T10, Bool cond11, typename T11, typename Default >
struct IfThenElse12T
    : public SelectT< cond0, T0, SelectT< cond1, T1, SelectT< cond2, T2, SelectT< cond3, T3, SelectT< cond4, T4, SelectT< cond5, T5, SelectT< cond6, T6, SelectT< cond7, T7, SelectT< cond8, T8, SelectT< cond9, T9, SelectT< cond10, T10, SelectT< cond11, T11, Default > > > > > > > > > > > >
{};

template< Bool cond0, typename T0, Bool cond1, typename T1, Bool cond2, typename T2, Bool cond3, typename T3, Bool cond4, typename T4, Bool cond5, typename T5, Bool cond6, typename T6, Bool cond7, typename T7, Bool cond8, typename T8, Bool cond9, typename T9, Bool cond10, typename T10, Bool cond11, typename T11, Bool cond12, typename T12, typename Default >
struct IfThenElse13T
    : public SelectT< cond0, T0, SelectT< cond1, T1, SelectT< cond2, T2, SelectT< cond3, T3, SelectT< cond4, T4, SelectT< cond5, T5, SelectT< cond6, T6, SelectT< cond7, T7, SelectT< cond8, T8, SelectT< cond9, T9, SelectT< cond10, T10, SelectT< cond11, T11, SelectT< cond12, T12, Default > > > > > > > > > > > > >
{};

template< Bool cond0, typename T0, Bool cond1, typename T1, Bool cond2, typename T2, Bool cond3, typename T3, Bool cond4, typename T4, Bool cond5, typename T5, Bool cond6, typename T6, Bool cond7, typename T7, Bool cond8, typename T8, Bool cond9, typename T9, Bool cond10, typename T10, Bool cond11, typename T11, Bool cond12, typename T12, Bool cond13, typename T13, typename Default >
struct IfThenElse14T
    : public SelectT< cond0, T0, SelectT< cond1, T1, SelectT< cond2, T2, SelectT< cond3, T3, SelectT< cond4, T4, SelectT< cond5, T5, SelectT< cond6, T6, SelectT< cond7, T7, SelectT< cond8, T8, SelectT< cond9, T9, SelectT< cond10, T10, SelectT< cond11, T11, SelectT< cond12, T12, SelectT< cond13, T13, Default > > > > > > > > > > > > > >
{};

template< Bool cond0, typename T0, Bool cond1, typename T1, Bool cond2, typename T2, Bool cond3, typename T3, Bool cond4, typename T4, Bool cond5, typename T5, Bool cond6, typename T6, Bool cond7, typename T7, Bool cond8, typename T8, Bool cond9, typename T9, Bool cond10, typename T10, Bool cond11, typename T11, Bool cond12, typename T12, Bool cond13, typename T13, Bool cond14, typename T14, typename Default >
struct IfThenElse15T
    : public SelectT< cond0, T0, SelectT< cond1, T1, SelectT< cond2, T2, SelectT< cond3, T3, SelectT< cond4, T4, SelectT< cond5, T5, SelectT< cond6, T6, SelectT< cond7, T7, SelectT< cond8, T8, SelectT< cond9, T9, SelectT< cond10, T10, SelectT< cond11, T11, SelectT< cond12, T12, SelectT< cond13, T13, SelectT< cond14, T14, Default > > > > > > > > > > > > > > >
{};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_META_IF_THEN_ELSE_H
