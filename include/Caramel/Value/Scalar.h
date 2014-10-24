// Caramel C++ Library - Value Facility - Scalar Header

#ifndef __CARAMEL_VALUE_SCALAR_H
#define __CARAMEL_VALUE_SCALAR_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <boost/optional.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Scalar
// - A single value which can be represented as a string.
//
//   Immutable.
//
//   Supporting value types:
//
//     Bool, Int, Uint, Int64, Uint64, Float, Double, std::string
//
//
// REMARKS:
//   This type does NOT follow the std::is_scalar() rule.
//

class ScalarImpl;

class Scalar
{
public:

    // Default: an undef value. Can not be converted to any type.
    Scalar();

    explicit Scalar( Bool v );
    explicit Scalar( Int v );
    explicit Scalar( Uint v );
    explicit Scalar( Int64 v );
    explicit Scalar( Uint64 v );
    explicit Scalar( Double v );
    explicit Scalar( std::string v );

    
    //
    // Get Value by exactly conversion
    //

    boost::optional< Bool >   AsBool()   const;
    boost::optional< Int >    AsInt()    const;
    boost::optional< Uint >   AsUint()   const;
    boost::optional< Int64 >  AsInt64()  const;
    boost::optional< Uint64 > AsUint64() const;
    boost::optional< Float >  AsFloat()  const;
    boost::optional< Double > AsDouble() const;

    boost::optional< std::string > AsString() const;


private:

    std::shared_ptr< ScalarImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_VALUE_SCALAR_H
