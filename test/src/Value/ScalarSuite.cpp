// Caramel C++ Library Test - Value - Scalar Suite

#include "CaramelTestPch.h"

#include <Caramel/Value/Scalar.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( ScalarSuite )
{

TEST( ScalarTrivialTest )
{
    const Scalar s;

    // Undef scalar should throws.
    CHECK_THROW( s.AsBool(), Caramel::Exception );
    CHECK_THROW( s.AsString(), Caramel::Exception );
}


TEST( ScalarBoolTest )
{
    // Bool can convert to String, but not Integer or Floating.

    const Scalar st( true );

    CHECK( true   == st.AsBool() );
    CHECK( "true" == *st.AsString() );

    // Convertible ?
    CHECK( true  == static_cast< Bool >( st.AsBool() ));
    CHECK( false == static_cast< Bool >( st.AsInt() ));
    

    const Scalar sf( false );

    CHECK( false   == sf.AsBool() );
    CHECK( "false" == *sf.AsString() );

    // Convertible ?
    CHECK( true  == static_cast< Bool >( st.AsBool() ));
    CHECK( false == static_cast< Bool >( st.AsInt() ));
}


} // SUITE ScalarSuite

} // namespace Caramel
