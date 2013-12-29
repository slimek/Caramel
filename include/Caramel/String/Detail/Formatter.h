// Caramel C++ Library - String Facility - Detail - Formatter Header

#ifndef __CARAMEL_STRING_DETAIL_FORMATTER_H
#define __CARAMEL_STRING_DETAIL_FORMATTER_H
#pragma once

#include <Caramel/Caramel.h>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Formatter
//

class FormatterImpl;

class Formatter
{
public:

    explicit Formatter( const std::string& format );

    void Feed( Uint index, Int  value );
    void Feed( Uint index, Uint value );

    void Feed( Uint index, const std::string& value );


    std::string GetString() const;


private:

    std::shared_ptr< FormatterImpl > m_impl;
};

///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_STRING_DETAIL_FORMATTER_H
