// Caramel C++ Library - Error Facility - Try-Catch Result Header

#ifndef __CARAMEL_ERROR_TRY_CATCH_RESULT_H
#define __CARAMEL_ERROR_TRY_CATCH_RESULT_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Error/Exceptionptr.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Try-Catch Result
// - A common type to generalize the handling of:
//   1. ExceptionCatcher
//   2. TaskCore::CatchResult
//
// - When catching an AnyFailure,
//   you may get it from both the 'anyFailure' and 'exception' fields.
//   For other exception types the 'anyFailure' is nullptr.
//

struct TryCatchResult
{
    AnyFailurePtr anyFailure;
    ExceptionPtr  exception;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ERROR_TRY_CATCH_RESULT_H
