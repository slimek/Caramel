// Caramel C++ Library - String Facility - Detail - Formatter Header

#ifndef __CARAMEL_STRING_DETAIL_FORMATTER_H
#define __CARAMEL_STRING_DETAIL_FORMATTER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Formatter
//

class Formatter
{
public:

    explicit Formatter( const std::string& format );

    std::string GetString() const;


    /// Feeding Arguments ///

    void Feed( Int    value );
    void Feed( Uint   value );
    void Feed( Int64  value );
    void Feed( Uint64 value );
    void Feed( Long   value );
    void Feed( Ulong  value );
    void Feed( Float  value );
    void Feed( Double value );

    void Feed( const std::string& value );


private:

    class Impl;
    std::shared_ptr< Impl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_STRING_DETAIL_FORMATTER_H
