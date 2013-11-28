// Caramel C++ Library - Value Facility - Named Value Entry Header

#ifndef __CARAMEL_VALUE_NAMED_VALUE_ENTRY_H
#define __CARAMEL_VALUE_NAMED_VALUE_ENTRY_H
#pragma once

#include <Caramel/Caramel.h>
#include <boost/variant.hpp>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Named Value Type
//

enum NamedValueType
{
    NAMED_VALUE_UNDEF = 0,

    NAMED_VALUE_BOOL,
    NAMED_VALUE_INT,
    NAMED_VALUE_UINT,
    NAMED_VALUE_DOUBLE,
    NAMED_VALUE_STRING,
};


///////////////////////////////////////////////////////////////////////////////
//
// Named Value Entry
//

struct NamedValueEntry
{
    NamedValueEntry() : type( NAMED_VALUE_UNDEF ) {}

    // Throws if the type is incorrect
    Bool        GetBool()   const;
    Int         GetInt()    const;
    Uint        GetUint()   const;
    Double      GetDouble() const;
    std::string GetString() const;


    boost::variant< Uint, Double, std::string > value;
    NamedValueType type;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_VALUE_NAMED_VALUE_ENTRY_H
