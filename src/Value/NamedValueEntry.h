// Caramel C++ Library - Value Facility - Named Value Entry Header

#ifndef __CARAMEL_VALUE_NAMED_VALUE_ENTRY_H
#define __CARAMEL_VALUE_NAMED_VALUE_ENTRY_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
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
    NAMED_VALUE_INT64,
    NAMED_VALUE_UINT64,
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

    
    void SetBool  ( Bool v );
    void SetInt   ( Int v );
    void SetUint  ( Uint v );
    void SetInt64 ( Int64 v );
    void SetUint64( Uint64 v );
    void SetDouble( Double v );
    void SetString( const std::string& v );

    void SetLong ( Long v );
    void SetUlong( Ulong v );


    // Throws if the type is incorrect
    Bool        GetBool()   const;
    Int         GetInt()    const;
    Uint        GetUint()   const;
    Int64       GetInt64()  const;
    Uint64      GetUint64() const;
    Double      GetDouble() const;
    std::string GetString() const;


    boost::variant< Uint64, Double, std::string > value;
    NamedValueType type;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_VALUE_NAMED_VALUE_ENTRY_H
