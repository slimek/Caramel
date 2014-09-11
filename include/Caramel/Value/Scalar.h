// Caramel C++ Library - Value Facility - Scalar Header

#ifndef __CARAMEL_VALUE_SCALAR_H
#define __CARAMEL_VALUE_SCALAR_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <boost/noncopyable.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Scalar
// - A single value which can be represented as a string.
//
//   Supporting value types:
//       Bool, Int, Uint, Int64, Uint64, Float, Double, std::string
//
// REMARKS:
//   This type DOES NOT follow the std::is_scalar() rule.
//

class ScalarImpl;

class Scalar : public boost::noncopyable
{
public:

    // Default: an undef value. Can not be converted to any type.
    Scalar();

    
    //
    // Set Value and Type
    //

    void SetBool  ( Bool v );
    void SetInt64 ( Int64 v );
    void SetUint64( Uint64 v );
    void SetDouble( Double v );
    void SetString( const std::string& v );


    //
    // Get Value with exactly conversion.
    // - Throws if conversion failed.
    //

    Bool        AsBool()   const;
    Int         AsInt()    const;
    Uint        AsUint()   const;
    Int64       AsInt64()  const;
    Uint64      AsUint64() const;
    Float       AsFloat()  const;
    Double      AsDouble() const;
    std::string AsString() const;


private:

    std::shared_ptr< ScalarImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_VALUE_SCALAR_H
