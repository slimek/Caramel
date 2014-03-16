// Caramel C++ Library - Statechart Facility - Transition Header

#ifndef __CARAMEL_STATECHART_TRANSITION_H
#define __CARAMEL_STATECHART_TRANSITION_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Statechart/State.h>


namespace Caramel
{

namespace Statechart
{

///////////////////////////////////////////////////////////////////////////////
//
// Transition
//

struct Transition
{
    Transition()
        : targetStateId( 0 )
    {}

    Transition( Int targetStateId, Action action )
        : targetStateId( targetStateId )
        , action( action )
    {}

    Int    targetStateId;
    Action action;
};

typedef std::shared_ptr< Transition > TransitionPtr;


///////////////////////////////////////////////////////////////////////////////

} // namespace Statechart

} // namespace Caramel

#endif // __CARAMEL_STATECHART_TRANSITION_H
