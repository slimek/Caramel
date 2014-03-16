// Caramel C++ Library - Error Facility - Error Manager Header

#ifndef __CARAMEL_ERROR_ERROR_MANAGER_H
#define __CARAMEL_ERROR_ERROR_MANAGER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Object/FacilityLongevity.h"
#include <Caramel/Error/Alert.h>
#include <Caramel/Object/Singleton.h>
#include <mutex>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Error Manager
//

class ErrorManager : public Singleton< ErrorManager, FACILITY_LONGEVITY_ERROR >
{
public:

    ErrorManager();

    AlertHandler SetAlertHandler( AlertHandler newHandler );
    AlertHandler GetAlertHandler() const;


private:

    mutable std::mutex m_mutex;

    AlertHandler m_alertHandler;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ERROR_ERROR_MANAGER_H
