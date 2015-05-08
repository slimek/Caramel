// Caramel C++ Library Test - Value - Shared Array Suite

#include "CaramelTestPch.h"

#include "Utils/SharedArrayUtils.h"
#include <Caramel/Value/SharedArray.h>
#include <boost/range/algorithm.hpp>
#include <set>
#include <vector>


namespace Caramel
{

SUITE( SharedArray )
{

TEST( ConstSharedArray )
{
    ConstSharedArray< Int > ia0;
    
    CHECK( true  == ia0.IsEmpty() );
    CHECK( 0     == ia0.Size() );
    CHECK( false == ia0.Contains( 42 ));
    CHECK( ia0.Begin() == ia0.End() );

    ConstSharedArray< Int > ia1( 1 );

    CHECK( false == ia1.IsEmpty() );
    CHECK( 1     == ia1.Size() );
    CHECK( ia1.Begin() + 1 == ia1.End() );
}


TEST( SharedArray )
{
    SharedArray< std::string > sa0;

    CHECK( true   == sa0.IsEmpty() );
    CHECK( 0      == sa0.Size() );
    CHECK( false  == sa0.Contains( "Cirno" ));
    CHECK( sa0.Begin() == sa0.End() );

    SharedArray< std::string > sa( 3 );

    CHECK( false  == sa.IsEmpty() );
    CHECK( 3      == sa.Size() );
    CHECK( ""     == sa[0] );

    sa[0] = "Alice";
    sa[1] = "Reimu";
    sa[2] = "Marisa";

    CHECK( "Alice" == sa[0] );

    auto iter = sa.Begin();
    *( ++ iter) = "Suika";
    CHECK( "Suika" == sa[1] );

    sa.Reset( 5 );

    CHECK( 5  == sa.Size() );
    CHECK( "" == sa[1] );
}


TEST( SharedArrayInitializer )
{
    SharedArray< std::string > sa0{};

    CHECK( true == sa0.IsEmpty() );
    CHECK( 0    == sa0.Size() );


    SharedArray< std::string > sa1{ "Cirno" };

    CHECK( false == sa1.IsEmpty() );
    CHECK( 1     == sa1.Size() );
    CHECK( "Cirno" == sa1[0] );


    SharedArray< std::string > sa3{ "Alice", "Reimu", "Marisa" };

    CHECK( false == sa3.IsEmpty() );
    CHECK( 3     == sa3.Size() );
    CHECK( "Alice" == sa3[0] );
    CHECK( "Marisa" == sa3[2] );
}


TEST( SharedArrayRange )
{
    std::vector< Int > data{ 1, 2, 3 };
    SharedArray< Int > array1( data.begin(), data.size() );

    CHECK(( array1 == SharedArray< Int >{ 1, 2, 3 } ));

    std::set< std::string > names{ "Alice", "Reimu", "Marisa" };
    ConstSharedArray< std::string > array2( names.begin(), names.size() );

    // std::set would sort the values.
    CHECK(( array2 == SharedArray< std::string >{ "Alice", "Marisa", "Reimu" } ));


    // Transform into square
    ConstSharedArray< Int > array3( data.begin(), data.size(), [] ( Int v ) { return v * v; } );
    CHECK(( array3 == SharedArray< Int >{ 1, 4, 9 } ));

    // Transform into string length
    ConstSharedArray< Usize > array4(
        array2.Begin(), array2.Size(), [] ( const std::string& s ) { return s.length(); } );
    CHECK(( array4 == SharedArray< Usize >{ 5, 6, 5 } ));
}


// Test of the fill constructors
TEST( SharedArrayFill )
{
    SharedArray< Int > array1( 1, 7 );
    CHECK(( array1 == SharedArray< Int >{ 7 } ));

    SharedArray< std::string > array2( 2, "Alice" );
    CHECK(( array2 == SharedArray< std::string >{ "Alice", "Alice" } ));

    ConstSharedArray< Float > array3( 3, 42.f );
    CHECK(( array3 == SharedArray< Float >{ 42.f, 42.f, 42.f } ));
}


TEST( SharedArrayBoostRange )
{
    SharedArray< Int > ary( 3 );
    CHECK( ary.Begin() == boost::begin( ary ));

    ConstSharedArray< std::string > cary( 5 );
    CHECK( cary.Begin() == boost::begin( cary ));

    // We can pass the compiling ~
    // - Both SharedArray and ConstSharedArray are accepted by Boost.Range algorithms.
    boost::range::sort( ary );
    boost::range::max_element( cary );
}


TEST( SharedArrayCopyFrom )
{
    std::vector< Int > idata = { 3, 2, 7, 6, 8 };
    const auto icopy = SharedArray< Int >::CopyFrom( idata );

    CHECK(( icopy == SharedArray< Int >{ 3, 2, 7, 6, 8 } ));

    std::string sdata = "Alice";
    const auto bcopy = SharedArray< Byte >::CopyFrom( sdata );

    CHECK(( bcopy == SharedArray< Byte >{ 65, 108, 105, 99, 101 } ));  // 'A', 'l', 'i', 'c', 'e'

    std::vector< std::string > empty;
    const auto none = SharedArray< std::string >::CopyFrom( empty );

    CHECK( none.IsEmpty() );
}


} // SUITE SharedArray

} // namespace Caramel
