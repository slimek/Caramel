// Caramel C++ Library - String Facility - Formatter Private Header

#ifndef __CARAMEL_STRING_FORMATTER_IMPL_H
#define __CARAMEL_STRING_FORMATTER_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/String/Detail/Formatter.h>
#include <functional>
#include <vector>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Formatter
//

class Formatter::Impl
{
public:

    explicit Impl( const std::string& format );

    void Distribute( std::function< std::string( const std::string& ) > formatResolver );

    std::string GetString() const;


private:
    
    struct FormatItem
    {
        Uint argIndex { 0 };

        std::string head;
        std::string content;
    };

    std::vector< FormatItem > m_items;
    std::string m_tail;

    Uint m_feedingIndex { 0 };  // Increment after each Distribute() called.
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_STRING_FORMATTER_IMPL_H
