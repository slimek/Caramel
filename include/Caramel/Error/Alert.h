// Caramel C++ Library - Error Facility - Alert Header

#ifndef __CARAMEL_ERROR_ALERT_H
#define __CARAMEL_ERROR_ALERT_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/String/Sprintf.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Alert
// - Call Alert Handler internally.
//   This is the basis of Caramel.Assert
// 

void Alert(
    Int line, const std::string& file, const std::string& function,
    const std::string& message
);


///////////////////////////////////////////////////////////////////////////////
//
// Alert Handler
//
//   "Alert" is an warning event which expect the user interference.
//   You may give a UI dialog to show the warning message, and allow user to
//   choose the next step:
//     1. Continue once - next time this alert occur, handle it again.
//     2. Continue all - ignore all this alert later.
//     3. Break the programe and start to debug (if possible).
//     4. Abort the program.
//
//   The default behavior is ANSI C assert(), whose behavior depends on platform
//   implementation.
//

enum AlertResult
{
    ALERT_RESULT_NONE           = 0,
    ALERT_RESULT_CONTINUE_ONCE  = 1,
    ALERT_RESULT_CONTINUE_ALL   = 2,
    ALERT_RESULT_BREAK          = 3,
    ALERT_RESULT_ABORT          = 4,  // *1
};

// NOTE: Some handlers may abort the program itself.


typedef AlertResult (* AlertHandler )
(
    Int line,
    const std::string& file,
    const std::string& function,
    const std::string& message
);

// Returns the previous handler.
AlertHandler SetAlertHandler( AlertHandler newHandler );

//
// Default handler
// - In Debug build, call the assert() implementation of each system.
//   In Release build, trace parameters in warn level.
//
AlertResult DefaultAlertHandler(
    Int line, const std::string& file, const std::string& function,
    const std::string& message
);


// Trace parameters in warn level.
AlertResult TraceAlertHandler(
    Int line, const std::string& file, const std::string& function,
    const std::string& message
);


// Throws a Caramel::Exception
AlertResult ThrowAlertHandler(
    Int line, const std::string& file, const std::string& function,
    const std::string& message
);


} // namespace Caramel

///////////////////////////////////////////////////////////////////////////////
//
// Alert Macro
//

#define CARAMEL_ALERT( ... ) \
    Caramel::Alert( __LINE__, __FILE__, __FUNCTION__, Sprintf( __VA_ARGS__ ))


///////////////////////////////////////////////////////////////////////////////

#endif // __CARAMEL_ERROR_ALERT_H
