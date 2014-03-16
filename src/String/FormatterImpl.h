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

class FormatterImpl
{
    friend class Formatter;

public:

    explicit FormatterImpl( const std::string& format );

    void Distribute( Uint argIndex, std::function< std::string ( const std::string& ) > formatter );
    
    std::string GetString() const;


private:

    struct FormatItem
    {
        FormatItem()
            : argIndex( 0 )
        {}
        
        Uint  argIndex;

        std::string head;
        std::string content;
    };

    std::vector< FormatItem > m_items;

    std::string m_tail;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_STRING_FORMATTER_IMPL_H
