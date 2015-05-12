// Caramel C++ Library Test - Memory - Copy Pointer Suite

#include "CaramelTestPch.h"

#include <Caramel/Memory/CopyPtr.h>


namespace Caramel
{

SUITE( CopyPtr )
{

template< typename T >
CopyPtr< T > MakeCopyPtr( const T& value )
{
    return CopyPtr< T >( new T( value ));
}


TEST( CopyPtr )
{
    /// Trivial ///

    CopyPtr< int > p1;

    CHECK( ! p1 );
    CHECK( nullptr == p1.Get() );

    auto p2 = p1;
    CHECK( ! p2 );
    CHECK( nullptr == p2.Get() );


    /// Copy ///

    CopyPtr< std::string > p3( new std::string( "Alice" ));

    CHECK( p3 );
    
    std::string v3 = *p3;
    CHECK( "Alice" == v3 );

    CHECK( 5 == p3->length() );

    auto p4 = p3;

    CHECK( "Alice" == *p4 );
    *p4 = "Marisa";

    CHECK( "Alice" == *p3 );

    p4.Reset();
    CHECK( ! p4 );

    p4.Reset( new std::string( "Reimu" ));
    CHECK( "Reimu" == *p4 );
    CHECK( 5 == p4->length() );


    /// Move ///

    CopyPtr< std::string > p5( std::move( p3 ));

    CHECK( ! p3 );
    CHECK( "Alice" == *p5 );

    CopyPtr< std::string > p6( MakeCopyPtr( std::string( "Sanae" )));

    CHECK( p6 );
    CHECK( "Sanae" == *p6 );

    p6 = MakeCopyPtr( std::string( "Suwako" ));

    CHECK( "Suwako" == *p6 );


    /// Get ///

    auto s7 = new std::string( "Sakuya" );
    CopyPtr< std::string > p7( s7 );

    CHECK( s7 == p7.Get() );

    {
        CopyPtr< std::string > p8 = p7;

        CHECK( "Sakuya" == *p8 );
    }

    // destroy p8 doesn't affect p7 and s7

    CHECK( "Sakuya" == *p7 );

}


} // SUITE CopyPtr

} // namespace Caramel
