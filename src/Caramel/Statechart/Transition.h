// Caramel C++ Library - Statechart Facility - Transition Header

#ifndef __CARAMEL_STATECHART_TRANSITION_H
#define __CARAMEL_STATECHART_TRANSITION_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


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
