// Caramel C++ Library - Value Facility - Detail - Any Holders Private Header

#ifndef __CARAMEL_VALUE_ANY_HOLDERS_IMPL_H
#define __CARAMEL_VALUE_ANY_HOLDERS_IMPL_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Value/Detail/AnyHolders.h>
#include <boost/variant.hpp>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Number Type
//

enum AnyNumberType
{
    ANY_NUMBER_INT64,
    ANY_NUMBER_UINT64,
    ANY_NUMBER_DOUBLE,    
};


///////////////////////////////////////////////////////////////////////////////
//
// Any Number
//

class AnyNumberImpl
{
    friend class AnyNumber;

public:

    explicit AnyNumberImpl( Int64  value );
    explicit AnyNumberImpl( Uint64 value );
    explicit AnyNumberImpl( Double value );

    template< typename T >
    void Get( T& value ) const;


private:
    AnyNumberType m_type;

    boost::variant< Int64, Uint64, Double > m_value;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_VALUE_ANY_HOLDERS_IMPL_H
