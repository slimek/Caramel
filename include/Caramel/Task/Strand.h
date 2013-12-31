// Caramel C++ Library - Task Facility - Strand Header

#ifndef __CARAMEL_TASK_STRAND_H
#define __CARAMEL_TASK_STRAND_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Task/TaskFwd.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Strand
// - Used to schedule the execution order of Tasks
//

class StrandImpl;

class Strand
{
public:

    void CancelAll();


private:
    
    std::shared_ptr< StrandImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_STRAND_H
