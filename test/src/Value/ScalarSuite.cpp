// Caramel C++ Library Test - Value - Scalar Suite

#include "CaramelTestPch.h"

#include <Caramel/Value/Scalar.h>
#include <Caramel/FileSystem/Path.h>


namespace Caramel
{

SUITE( ScalarSuite )
{

TEST( ScalarTrivialTest )
{
    const Scalar s;

    // Undef scalar should throws.
    CHECK_THROW( s.AsBool(),    Caramel::Exception );
    CHECK_THROW( s.AsInt(),     Caramel::Exception );
    CHECK_THROW( s.AsUint(),    Caramel::Exception );
    CHECK_THROW( s.AsInt64(),   Caramel::Exception );
    CHECK_THROW( s.AsUint64(),  Caramel::Exception );
    CHECK_THROW( s.AsFloat(),   Caramel::Exception );
    CHECK_THROW( s.AsDouble(),  Caramel::Exception );
    CHECK_THROW( s.AsString(),  Caramel::Exception );
}


TEST( ScalarBoolTest )
{
    const Scalar st( true );

    CHECK( true   == *st.AsBool() );
    CHECK( 1      == *st.AsInt() );
    CHECK( 1      == *st.AsUint() );
    CHECK( 1      == *st.AsInt64() );
    CHECK( 1      == *st.AsUint64() );
    CHECK( 1.0f   == *st.AsFloat() );
    CHECK( 1.0    == *st.AsDouble() );
    CHECK( "true" == *st.AsString() );

    // Convertible ?
    CHECK( true == static_cast< Bool >( st.AsBool() ));
    CHECK( true == static_cast< Bool >( st.AsInt() ));
    

    const Scalar sf( false );

    CHECK( false   == *sf.AsBool() );
    CHECK( 0       == *sf.AsInt() );
    CHECK( 0       == *sf.AsUint() );
    CHECK( 0       == *sf.AsInt64() );
    CHECK( 0       == *sf.AsUint64() );
    CHECK( 0.0f    == *sf.AsFloat() );
    CHECK( 0.0     == *sf.AsDouble() );
    CHECK( "false" == *sf.AsString() );

    // Convertible ?
    CHECK( true == static_cast< Bool >( st.AsBool() ));
    CHECK( true == static_cast< Bool >( st.AsInt() ));
}


TEST( ScalarIntTest )
{
    const Scalar si0( 0 );

    CHECK( false  == *si0.AsBool() );
    CHECK( 0      == *si0.AsInt() );
    CHECK( 0      == *si0.AsUint() );
    CHECK( 0      == *si0.AsInt64() );
    CHECK( 0      == *si0.AsUint64() );
    CHECK( 0.0f   == *si0.AsFloat() );
    CHECK( 0.0    == *si0.AsDouble() );
    CHECK( "0"    == *si0.AsString() );

    const Scalar si1( 1 );

    CHECK( true   == *si1.AsBool() );
    CHECK( 1      == *si1.AsInt() );
    CHECK( 1      == *si1.AsUint() );
    CHECK( 1      == *si1.AsInt64() );
    CHECK( 1      == *si1.AsUint64() );
    CHECK( 1.0f   == *si1.AsFloat() );
    CHECK( 1.0    == *si1.AsDouble() );
    CHECK( "1"    == *si1.AsString() );

    const Scalar sin1( -1 );

    CHECK( true   == *sin1.AsBool() );
    CHECK( -1     == *sin1.AsInt() );
    CHECK( -1     == *sin1.AsInt64() );
    CHECK( -1.0f  == *sin1.AsFloat() );
    CHECK( -1.0   == *sin1.AsDouble() );
    CHECK( "-1"   == *sin1.AsString() );

    // not convertible
    CHECK( ! sin1.AsUint() );
    CHECK( ! sin1.AsUint64() );
}


TEST( ScalarUintTest )
{
    const Scalar su0( 0u );

    CHECK( false  == *su0.AsBool() );
    CHECK( 0      == *su0.AsInt() );
    CHECK( 0      == *su0.AsUint() );
    CHECK( 0.0f   == *su0.AsFloat() );
    CHECK( 0.0    == *su0.AsDouble() );
    CHECK( "0"    == *su0.AsString() );

    const Scalar su1( 1u );

    CHECK( true   == *su1.AsBool() );
    CHECK( 1      == *su1.AsInt() );
    CHECK( 1      == *su1.AsUint() );
    CHECK( 1.0f   == *su1.AsFloat() );
    CHECK( 1.0    == *su1.AsDouble() );
    CHECK( "1"    == *su1.AsString() );

    const Scalar sux( 0xFFFFFFFFu );

    CHECK( true          == *sux.AsBool() );
    CHECK( 0xFFFFFFFFu   == *sux.AsUint() );
    CHECK( 0xFFFFFFFFLL  == *sux.AsInt64() );
    CHECK( 0xFFFFFFFFuLL == *sux.AsUint64() );
    CHECK( 4294967295.0  == *sux.AsDouble() );
    CHECK( "4294967295"  == *sux.AsString() );

    // not convertible
    CHECK( ! sux.AsInt() );
    CHECK( ! sux.AsFloat() );
}


TEST( ScalarInt64Test )
{
    const Scalar si0( 0LL );

    CHECK( false  == *si0.AsBool() );
    CHECK( 0      == *si0.AsInt() );
    CHECK( 0      == *si0.AsUint() );
    CHECK( 0      == *si0.AsInt64() );
    CHECK( 0      == *si0.AsUint64() );
    CHECK( 0.0f   == *si0.AsFloat() );
    CHECK( 0.0    == *si0.AsDouble() );
    CHECK( "0"    == *si0.AsString() );

    const Scalar sib( 10000000000LL );

    CHECK( true           == *sib.AsBool() );
    CHECK( 10000000000LL  == *sib.AsInt64() );
    CHECK( 10000000000uLL == *sib.AsUint64() );
    CHECK( 10000000000.0  == *sib.AsDouble() );
    CHECK( "10000000000"  == *sib.AsString() );

    // not convertible
    CHECK( ! sib.AsInt() );
    CHECK( ! sib.AsUint() );
    CHECK( ! sib.AsFloat() );
}


TEST( ScalarUint64Test )
{
    const Scalar su0( 0uLL );

    CHECK( false  == *su0.AsBool() );
    CHECK( 0      == *su0.AsInt() );
    CHECK( 0      == *su0.AsUint() );
    CHECK( 0      == *su0.AsInt64() );
    CHECK( 0      == *su0.AsUint64() );
    CHECK( 0.0f   == *su0.AsFloat() );
    CHECK( 0.0    == *su0.AsDouble() );
    CHECK( "0"    == *su0.AsString() );

    const Scalar sub( 100200300400500600uLL );

    CHECK( true                  == *sub.AsBool() );
    CHECK( 100200300400500600LL  == *sub.AsInt64() );
    CHECK( 100200300400500600uLL == *sub.AsUint64() );
    CHECK( "100200300400500600"  == *sub.AsString() );

    // not convertible
    CHECK( ! sub.AsInt() );
    CHECK( ! sub.AsUint() );
    CHECK( ! sub.AsFloat() );
    CHECK( ! sub.AsDouble() );
}


TEST( ScalarLongTest )
{
    // In Visual C++, Long is accepted by Int.

    const Long lz = 42;
    const Scalar sl( lz );

    CHECK( 42 == *sl.AsInt() );


    // In Visual C++, Ulong needs its own overloading.

    const Ulong uz = 51;
    const Scalar su( uz );

    CHECK( 51 == *su.AsUint() );
}


TEST( ScalarFloatTest )
{
    const Scalar sf0( 0.0f );

    CHECK( false  == *sf0.AsBool() );
    CHECK( 0.0f   == *sf0.AsFloat() );
    CHECK( 0.0    == *sf0.AsDouble() );
    CHECK( "0"    == *sf0.AsString() );

    // Convert from floating to interger is not allowed
    CHECK( ! sf0.AsInt() );
    CHECK( ! sf0.AsUint() );
    CHECK( ! sf0.AsInt64() );
    CHECK( ! sf0.AsUint64() );
}


TEST( ScalarDoubleTest )
{
    const Scalar sd0( 0.0 );

    CHECK( false  == *sd0.AsBool() );
    CHECK( 0.0f   == *sd0.AsFloat() );
    CHECK( 0.0    == *sd0.AsDouble() );
    CHECK( "0"    == *sd0.AsString() );

    // Convert from floating to interger is not allowed
    CHECK( ! sd0.AsInt() );
    CHECK( ! sd0.AsUint() );
    CHECK( ! sd0.AsInt64() );
    CHECK( ! sd0.AsUint64() );
}


TEST( ScalarStringTest )
{
    const Scalar se( "" );

    CHECK( "" == *se.AsString() );

    const Scalar sa( "Alice" );

    CHECK( "Alice" == *sa.AsString() );

    const std::string marisa = "Marisa";
    const Scalar sm( marisa );

    CHECK( "Marisa" == *sm.AsString() );

    std::string reimu = "Reimu";
    const Scalar sr( std::move( reimu ));

    CHECK( "Reimu" == *sr.AsString() );


    /// String Convertible ///

    const Path path( "Hello/World.exe" );
    const Scalar sp( path );

    CHECK( "Hello/World.exe" == *sp.AsString() );
}


TEST( ScalarStrintConvertTest )
{
    /// Not convertible ///

    const Scalar sbad( "bad" );

    CHECK( ! static_cast< Bool >( sbad.AsBool() ));
    CHECK( ! sbad.AsInt() );
    CHECK( ! sbad.AsUint() );
    CHECK( ! sbad.AsInt64() );
    CHECK( ! sbad.AsUint64() );
    CHECK( ! sbad.AsFloat() );
    CHECK( ! sbad.AsDouble() );


    /// Boolean ///

    const Scalar strue( "true" );
    
    CHECK( true == *strue.AsBool() );

    const Scalar sfalse( "false" );

    CHECK( false == *sfalse.AsBool() );


    /// Integer ///

    const Scalar szero( "0" );

    CHECK( false == *szero.AsBool() );
    CHECK( 0     == *szero.AsInt() );
    CHECK( 0     == *szero.AsUint() );
    CHECK( 0     == *szero.AsInt64() );
    CHECK( 0     == *szero.AsUint64() );
    CHECK( 0.0f  == *szero.AsFloat() );
    CHECK( 0.0   == *szero.AsDouble() );
    CHECK( "0"   == *szero.AsString() );

    const Scalar sarea( "51" );

    CHECK( true  == *sarea.AsBool() );
    CHECK( 51    == *sarea.AsInt() );
    CHECK( 51    == *sarea.AsUint() );
    CHECK( 51    == *sarea.AsInt64() );
    CHECK( 51    == *sarea.AsUint64() );
    CHECK( 51.0f == *sarea.AsFloat() );
    CHECK( 51.0  == *sarea.AsDouble() );
    CHECK( "51"  == *sarea.AsString() );

    const Scalar swhite( "0xFFFFFF" );

    CHECK( true       == *swhite.AsBool() );
    CHECK( 16777215   == *swhite.AsInt() );
    CHECK( 16777215   == *swhite.AsUint() );
    CHECK( 16777215   == *swhite.AsInt64() );
    CHECK( 16777215   == *swhite.AsUint64() );
    CHECK( "0xFFFFFF" == *swhite.AsString() );  // keep the original string

    #if defined( CARAMEL_COMPILER_IS_MSVC ) || defined( CARAMEL_COMPILER_IS_GCC )
    // Not convertible - In some compilers, strtof/strtod() don't support hexidecimal format.
    // Known compiler versions:
    // - Visual C++ 2013
    //   Android NDK GCC 4.8 + static GNU STL (gnustl_static)
    CHECK( ! swhite.AsFloat() );
    CHECK( ! swhite.AsDouble() );
    #else
    CHECK( 16777215.0f == *swhite.AsFloat() );
    CHECK( 16777215.0  == *swhite.AsDouble() );
    #endif


    /// Floating ///

    const Scalar spai( "3.1416" );

    CHECK( 3.1416f  == *spai.AsFloat() );
    CHECK( 3.1416   == *spai.AsDouble() );
    CHECK( "3.1416" == *spai.AsString() );

    // Not convertible
    // - Lexical.Boolean and Integer don't accept floating format.
    CHECK( ! static_cast< Bool >( spai.AsBool() ));
    CHECK( ! spai.AsInt() );
    CHECK( ! spai.AsUint() );
    CHECK( ! spai.AsInt64() );
    CHECK( ! spai.AsUint64() );
}


} // SUITE ScalarSuite

} // namespace Caramel
