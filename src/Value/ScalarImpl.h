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

    ScalarImpl() {}

    template< typename T >
    explicit ScalarImpl( T value, ScalarType type )
        : m_value( value )
        , m_type( type )
    {}

    // Specialized overloading
    explicit ScalarImpl( std::string&& value )
        : m_value( std::move( value ))
        , m_type( SCALAR_STRING )
    {}


    /// Observers ///

    ScalarType GetType() const { return m_type; }


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

    boost::variant< Int64, Uint64, Double, std::string > m_value;
    ScalarType m_type { SCALAR_UNDEF };
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_VALUE_SCALAR_IMPL_H
