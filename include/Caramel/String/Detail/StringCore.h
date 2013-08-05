// Caramel C++ Library - String Facility - Detail - String Core Header

#ifndef __CARAMEL_STRING_DETAIL_STRING_CORE_H
#define __CARAMEL_STRING_DETAIL_STRING_CORE_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// String Core
//

class StringCore
{
public:

    /// Algorithms ///

    static std::string Trim( const std::string& input );
};


///////////////////////////////////////////////////////////////////////////////
//
// Wstring Core
//

class WstringCore
{
    // NOT IMPLEMENTED YET...
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_STRING_DETAIL_STRING_CORE_H
