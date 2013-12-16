// Caramel C++ Library - Value Facility - Detail - Any Holders Header

#ifndef __CARAMEL_VALUE_DETAIL_ANY_HOLDERS
#define __CARAMEL_VALUE_DETAIL_ANY_HOLDERS
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Error/Exception.h>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Holder
// - Abstract class.
//

class AnyHolder
{
public:
    virtual ~AnyHolder() {}
};


//
// Any Number
// - For numeric fundamental types
//

class AnyNumberImpl;

class AnyNumber : public AnyHolder
{
public:
    
    explicit AnyNumber( Int value );
    explicit AnyNumber( Uint value );

    ~AnyNumber();
    

    /// Retrieve Value ///

    template< typename T >
    static T CastTo( const AnyHolder* holder )
    {
        auto number = dynamic_cast< const AnyNumber* >( holder );
        if ( ! number )
        {
            CARAMEL_THROW( "Not a Any Number type" );
        }

        T value = 0;
        number->Get( value );
        return value;        
    }


    void Get( Int& value ) const;
    void Get( Uint& value ) const;


private:
    std::unique_ptr< AnyNumberImpl > m_impl;
};


//
// Holder Select
//

template< typename T >
struct AnyHolderSelect
{
    typedef AnyNumber Type;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_VALUE_DETAIL_ANY_HOLDERS
