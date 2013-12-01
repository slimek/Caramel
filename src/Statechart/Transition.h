// Caramel C++ Library - Statechart Facility - Transition Header

#ifndef __CARAMEL_STATECHART_TRANSITION_H
#define __CARAMEL_STATECHART_TRANSITION_H
#pragma once

#include <Caramel/Caramel.h>


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

    explicit Transition( Int targetStateId )
        : targetStateId( targetStateId )
    {}

    Int targetStateId;
};

typedef std::shared_ptr< Transition > TransitionPtr;


///////////////////////////////////////////////////////////////////////////////

} // namespace Statechart

} // namespace Caramel

#endif // __CARAMEL_STATECHART_TRANSITION_H
