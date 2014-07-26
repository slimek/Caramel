// Caramel C++ Library Test - Numeric - Number Traits Suite

#include "CaramelTestPch.h"

#include <Caramel/Numeric/NumberTraits.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( NumberTraitsSuite )
{

template< typename Floating, typename Integer >
Bool TestLossless( Integer before )
{
    const Floating temp  = static_cast< Floating >( before );
    const Integer  after = static_cast< Integer > ( temp );

    return before == after;
}


TEST( FloatTraitsTest )
{
    /// Float can contain any 16-bit Integers ///

    CHECK( true == TestLossless< Float >( 0 ));
    CHECK( true == TestLossless< Float >( INT16_MAX ));
    CHECK( true == TestLossless< Float >( INT16_MIN ));
    CHECK( true == TestLossless< Float >( UINT16_MAX ));


    /// 32-bit Integer Limits ///

    const Int32 i32max = NumberTraits< Float >::MAX_EXACT_INT32;
    const Int32 i32min = NumberTraits< Float >::MIN_EXACT_INT32;

    CHECK( true  == TestLossless< Float >( i32max ));
    CHECK( false == TestLossless< Float >( i32max + 2 ));

    CHECK( true  == TestLossless< Float >( i32min ));
    CHECK( false == TestLossless< Float >( i32min - 2 ));

    const Uint32 u32max = NumberTraits< Float >::MAX_EXACT_UINT32;

    CHECK( true  == TestLossless< Float >( u32max ));
    CHECK( false == TestLossless< Float >( u32max + 2 ));
}


TEST( DoubleTraitsTest )
{
    /// Double can contain any 32-bit Integers ///

    CHECK( true == TestLossless< Double >( 0 ));
    CHECK( true == TestLossless< Double >( INT32_MAX ));
    CHECK( true == TestLossless< Double >( INT32_MIN ));
    CHECK( true == TestLossless< Double >( UINT32_MAX ));


    /// 64-bit Integer Limits ///

    const Int64 i64max = NumberTraits< Double >::MAX_EXACT_INT64;
    const Int64 i64min = NumberTraits< Double >::MIN_EXACT_INT64;

    CHECK( true  == TestLossless< Double >( i64max ));
    CHECK( false == TestLossless< Double >( i64max + 2 ));

    CHECK( true  == TestLossless< Double >( i64min ));
    CHECK( false == TestLossless< Double >( i64min - 2 ));

    const Uint64 u64max = NumberTraits< Double >::MAX_EXACT_UINT64;

    CHECK( true  == TestLossless< Double >( u64max ));
    CHECK( false == TestLossless< Double >( u64max + 2 ));
}


} // SUITE NumberTraitsSuite

} // namespace Caramel
