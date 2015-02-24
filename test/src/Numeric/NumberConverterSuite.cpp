// Caramel C++ Library Test - Numeric - Number Converter Suite

#include "CaramelTestPch.h"

#include <Caramel/Numeric/NumberConverter.h>
#include <Caramel/Numeric/NumberTraits.h>


namespace Caramel
{

SUITE( NumberConverterSuite )
{

TEST( NumberConverterTest )
{
    typedef NumberConverter< Int32, Int64 > NCI3I6;

    Int32 i32 = 0;

    CHECK( true == NCI3I6::TryExactConvert( i32, INT32_MAX ));
    CHECK( INT32_MAX == i32 );

    CHECK( true == NCI3I6::TryExactConvert( i32, INT32_MIN ));
    CHECK( INT32_MIN == i32 );

    CHECK( false == NCI3I6::TryExactConvert( i32, Int64Traits::MAX_INT32 + 1 ));


    typedef NumberConverter< Int32, Uint64 > NCI3U6;

    CHECK( true == NCI3I6::TryExactConvert( i32, INT32_MAX ));
    CHECK( INT32_MAX == i32 );


    Uint32 u32 = 0;

    typedef NumberConverter< Uint32, Int64 > NCU3I6;

    CHECK( true == NCU3I6::TryExactConvert( u32, UINT32_MAX ));
    CHECK( UINT32_MAX == u32 );

    CHECK( true == NCU3I6::TryExactConvert( u32, 0 ));
    CHECK( 0 == u32 );

    CHECK( false == NCU3I6::TryExactConvert( u32, -1 ));


    typedef NumberConverter< Uint32, Uint64 > NCU3U6;

    CHECK( true == NCU3U6::TryExactConvert( u32, UINT32_MAX ));
    CHECK( UINT32_MAX == u32 );


    typedef NumberConverter< Uint32, Long >  NCU3L;
    typedef NumberConverter< Uint32, Ulong > NCU3UL;

    #if defined( CARAMEL_LONG_IS_64_BIT )
    CHECK( false == NCU3L::TryExactConvert( u32, LONG_MAX ));
    CHECK( false == NCU3UL::TryExactConvert( u32, ULONG_MAX ));
    #else
    CHECK( true == NCU3L::TryExactConvert( u32, LONG_MAX ));
    CHECK( true == NCU3UL::TryExactConvert( u32, ULONG_MAX ));
    #endif
}

} // SUITE NumberConverterSuite

} // namespace Caramel
