// Caramel C++ Library Test - Numeric - Number Relation Suite

#include "CaramelTestPch.h"

#include <Caramel/Numeric/NumberRelation.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( NumberRelationSuite )
{

TEST( NumberRelationTest )
{
}


// Default underline type : Int
enum SpanishColor
{
    COLOR_NEGRO     = 0,
    COLOR_ROJO      = 1,
    COLOR_AZUL      = -1,
    COLOR_BLANCO    = INT32_MAX,
    COLOR_GRIS      = INT32_MIN,
};


template< typename OutputT, typename InputT >
Bool TestEnum( OutputT, InputT value )
{
    return NumberRelation< OutputT, InputT >::CanExactConvert( value );
}


TEST( NumberRelationEnumTest )
{
    Int i = 0;
    Uint u = 0;

    CHECK( true  == TestEnum( i, COLOR_ROJO ));
    CHECK( true  == TestEnum( u, COLOR_ROJO ));
    CHECK( true  == TestEnum( i, COLOR_AZUL ));
    CHECK( false == TestEnum( u, COLOR_AZUL ));   // negative enum > Uint
    CHECK( true  == TestEnum( i, COLOR_BLANCO ));
    CHECK( true  == TestEnum( u, COLOR_BLANCO ));
    CHECK( true  == TestEnum( i, COLOR_GRIS ));
    CHECK( false == TestEnum( u, COLOR_GRIS ));   // negative enum > Uint
}

} // SUITE NumberRelationSuite

} // namespace Caramel
