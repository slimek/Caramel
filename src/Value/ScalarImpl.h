// Caramel C++ Library - Value Facility - Scalar Private Header

#ifndef __CARAMEL_VALUE_SCALAR_IMPL_H
#define __CARAMEL_VALUE_SCALAR_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Value/Scalar.h>
#include <boost/variant.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Scalar Type
//

enum ScalarType
{
    SCALAR_UNDEF = 0,

    SCALAR_BOOL,
    SCALAR_INT64,
    SCALAR_UINT64,
    SCALAR_DOUBLE,
    SCALAR_STRING,
};


///////////////////////////////////////////////////////////////////////////////
//
// Scalar
//

class ScalarImpl
{
public:

    /// Observers ///

    ScalarType GetType() const { return m_type; }


    /// Set Value and Type ///

    void SetBool  ( Bool v );
    void SetInt64 ( Int64 v );
    void SetUint64( Uint64 v );
    void SetDouble( Double v );
    void SetString( const std::string& v );


    /// Get Value with exactly conversion ///

    Bool        AsBool()   const;
    Int         AsInt()    const;
    Uint        AsUint()   const;
    Int64       AsInt64()  const;
    Uint64      AsUint64() const;
    Float       AsFloat()  const;
    Double      AsDouble() const;
    std::string AsString() const;


    /// Get Value ///

    Bool        GetBool()   const;
    Int64       GetInt64()  const;
    Uint64      GetUint64() const;
    Double      GetDouble() const;
    std::string GetString() const;


    /// Try Convert ///

    Bool TryConvertToBool();
    Bool TryConvertToInt64();
    Bool TryConvertToUint64();
    Bool TryConvertToDouble();


private:

    boost::variant< Uint64, Double, std::string > m_value;
    ScalarType m_type { SCALAR_UNDEF };
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_VALUE_SCALAR_IMPL_H
