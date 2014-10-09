// Caramel C++ Library Test - Value - Any Suite

#include "CaramelTestPch.h"

#include <Caramel/Numeric/NumberTraits.h>
#include <Caramel/Value/Any.h>
#include <Caramel/Value/AnyConvertible.h>
#include <UnitTest++/UnitTest++.h>
#include <cfloat>
#include <vector>


namespace Caramel
{

SUITE( AnySuite )
{

TEST( AnyEmptyTest )
{
    Any a0;
    CHECK( true == a0.IsEmpty() );
    CHECK_THROW( a0.As< Int >(), Caramel::Exception );

    Any ai( 1 );
    CHECK( false == ai.IsEmpty() );
}


TEST( AnyIntegerTest )
{
    Any ai( 42 );
    
    CHECK( 42 == ai.As< Int >() );
    CHECK( 42 == ai.As< Uint >() );
    CHECK( 42 == ai.As< Int64 >() );
    CHECK( 42 == ai.As< Uint64 >() );

    Any au( 216u );

    CHECK( 216 == au.As< Int >() );
    CHECK( 216 == au.As< Uint >() );
    CHECK( 216 == au.As< Int64 >() );
    CHECK( 216 == au.As< Uint64 >() );

    Any ai64( -2048LL );

    CHECK( -2048 == ai64.As< Int >() );
    CHECK( -2048 == ai64.As< Int64 >() );
    CHECK_THROW( ai64.As< Uint >(), Caramel::Exception );
    CHECK_THROW( ai64.As< Uint64 >(), Caramel::Exception );

    Any au64( 5730uLL );

    CHECK( 5730 == au64.As< Int >() );
    CHECK( 5730 == au64.As< Uint >() );
    CHECK( 5730 == au64.As< Int64 >() );
    CHECK( 5730 == au64.As< Uint64 >() );


    /// Out of Range would throw exceptions ///

    Any aux( 0xFFFFFFFF );

    CHECK( 0xFFFFFFFF == aux.As< Uint >() );
    CHECK_THROW( aux.As< Int >(), Caramel::Exception );

    Any aii( -1 );

    CHECK( -1 == aii.As< Int >() );
    CHECK_THROW( aii.As< Uint >(), Caramel::Exception );


    /// Convert to Floating ///

    CHECK( 42.0 == ai.As< Double >() );
    CHECK( -1.0 == aii.As< Double >() );
    CHECK( (Double)0xFFFFFFFF == aux.As< Double >() );
}


TEST( AnyBoolTest )
{
    Any atrue( true );
    CHECK( true == atrue.As< Bool >() );

    Any afalse( false );
    CHECK( false == afalse.As< Bool >() );
}


TEST( AnyStringTest )
{
    Any as( std::string( "Alice" ));
    Any asz1( "Cirno" );

    const Char* marisa = "Marisa";
    Any asz2( marisa );

    CHECK( "Alice"  == as.As< std::string >() );
    CHECK( "Cirno"  == asz1.As< std::string >() );
    CHECK( "Marisa" == asz2.As< std::string >() );

    // String type Any can only cast to std::string.
    // CHECK( as.As< const Char* >() );
}


enum Color
{
    COLOR_BLACK = 0,
    COLOR_BLUE  = 42,
};

enum FillMode
{
    FILL_BLANK = 0,
    FILL_SOLID = 255,
};

TEST( AnyEnumTest )
{
    Any ae( COLOR_BLUE );

    CHECK( 42         == ae.As< Int >() );
    CHECK( 42         == ae.As< Int64 >() );
    CHECK( COLOR_BLUE == ae.As< Color >() );

    // enum type doesn't match
    CHECK_THROW( ae.As< FillMode >(), Caramel::Exception );
}


TEST( AnyIntegerToFloatingTest )
{
    Any az( 0 );
    Any ai32max( INT32_MAX );
    Any ai32min( INT32_MIN );

    CHECK( 0 == az.As< Float >() );
    CHECK( 0 == az.As< Double >() );

    CHECK( INT32_MAX == ai32max.As< Double >() );
    CHECK( INT32_MIN == ai32min.As< Double >() );

    CHECK_THROW( ai32max.As< Float >(), Caramel::Exception );
    CHECK_THROW( ai32min.As< Float >(), Caramel::Exception );

    
    /// Conversion Limits ///

    const Int32 i32femax = NumberTraits< Float >::MAX_EXACT_INT32;
    const Int32 i32femin = NumberTraits< Float >::MIN_EXACT_INT32;

    Any ai32femax( i32femax );
    Any ai32femin( i32femin );

    CHECK( i32femax == ai32femax.As< Float >() );
    CHECK( i32femin == ai32femin.As< Float >() );

    Any ai32feover ( i32femax + 1 );
    Any ai32feunder( i32femin - 1 );

    CHECK_THROW( ai32feover.As< Float >(),  Caramel::Exception );
    CHECK_THROW( ai32feunder.As< Float >(), Caramel::Exception );
}


TEST( AnyFloatingTest )
{
    Any az( 0.0 );
    Any as( 42.0 );
    Any ap( 3.1416 );

    Any afmin( FLT_MIN );
    Any afpmax( FLT_MAX );
    Any afnmax( -FLT_MAX );
    Any afeps( FLT_EPSILON );

    Any admax( DBL_MAX );

    CHECK( 0.0f == az.As< Float >() );
    CHECK( 0.0  == az.As< Double >() );

    CHECK( 42.0f == as.As< Float >() );
    CHECK( 42.0  == as.As< Double >() );

    CHECK( 3.1416f == ap.As< Float >() );
    CHECK( 3.1416  == ap.As< Double >() );

    CHECK(  FLT_MIN == afmin.As< Float >() );
    CHECK(  FLT_MAX == afpmax.As< Float >() );
    CHECK( -FLT_MAX == afnmax.As< Float >() );
    CHECK(  FLT_EPSILON == afeps.As< Float >() );

    CHECK( DBL_MAX == admax.As< Double >() );
    CHECK_THROW( admax.As< Float >(), Caramel::Exception );
}


TEST( AnyObjectTest )
{
    /// Pair Struct ///

    typedef std::pair< Int, std::string > IdName;

    IdName src;
    src.first  = 42;
    src.second = "Eirin";

    Any ain( src );

    IdName dest = ain.As< IdName >();

    CHECK( 42      == dest.first );
    CHECK( "Eirin" == dest.second );


    /// Smart Pointer ///

    std::shared_ptr< Float > real( new Float( 3.14f ));

    Any asp( real );

    CHECK( 3.14f == *( asp.As< std::shared_ptr< Float > >() ));
}


struct Shape
{
    virtual ~Shape() {}
    virtual std::string GetName() const = 0;
};

struct Circle : public Shape
{
    std::string GetName() const override { return "Circle"; }
};

struct Square : public Shape
{
    std::string GetName() const override { return "Square"; }
};


TEST( AnyPolymorphicTest )
{
    std::vector< Any > anys;

    const auto circle = std::make_shared< Circle >();
    const auto square = std::make_shared< Square >();

    anys.push_back( MakeAny< Shape* >( circle.get() ));
    anys.push_back( MakeAny< Shape* >( square.get() ));

    CHECK( "Circle" == anys[0].As< Shape* >()->GetName() );
    CHECK( "Square" == anys[1].As< Shape* >()->GetName() );

    anys.push_back( MakeAny< std::shared_ptr< Shape > >( circle ));
    anys.push_back( MakeAny< std::shared_ptr< Shape > >( square ));

    CHECK( "Circle" == anys[2].As< std::shared_ptr< Shape > >()->GetName() );
    CHECK( "Square" == anys[3].As< std::shared_ptr< Shape > >()->GetName() );
}


TEST( AnyAssignTest )
{
    Any a1;

    CHECK( true == a1.IsEmpty() );

    a1 = 42;

    CHECK( false == a1.IsEmpty() );
    CHECK( 42 == a1.As< Int >() );
    
    a1 = "Alice";

    CHECK( "Alice" == a1.As< std::string >() );

    Any a2( 3.1416 );

    a1 = a2;

    CHECK( 3.1416 == a1.As< Double >() );
}


static Int s_copyCount = 0;
static Int s_moveCount = 0;

struct AnyItem
{
    AnyItem( Int value ) : value( value ) {}
    AnyItem( const AnyItem& rhs ) : value( rhs.value ) { ++ s_copyCount; }
    AnyItem( AnyItem&& rhs )      : value( rhs.value ) { ++ s_moveCount; rhs.value = 0; }

    Int value;
};


TEST( AnyMoveTest )
{
    AnyItem i1( 42 );
    
    CHECK( 0 == s_copyCount );
    CHECK( 0 == s_moveCount );

    // Copy
    Any a1( i1 );
    CHECK( 1 == s_copyCount );
    CHECK( 0 == s_moveCount );
    CHECK( 42 == i1.value );   // can't be moved

    // Move
    Any a2( AnyItem( 51 ));
    CHECK( 1 == s_copyCount );
    CHECK( 1 == s_moveCount );    

    // Force to move
    Any a3( std::move( i1 ));
    CHECK( 1 == s_copyCount );
    CHECK( 2 == s_moveCount );    

    CHECK( 42 == a1.As< AnyItem >().value );
    CHECK( 51 == a2.As< AnyItem >().value );
    CHECK( 42 == a3.As< AnyItem >().value );
    CHECK( 0 == i1.value );  // has been moved.
}


TEST( AnyAnyTest )
{
    Any a1( 42 );
    Any a2( a1 ); 

    Any a3;
    a3 = a1;

    // Correct : Any< Int >, a copy of a1.
    // Wrong   : Any< Any< Int >>

    CHECK( 42 == a2.As< Int >() );
    CHECK( 42 == a3.As< Int >() );
}

class StringProxyRigid
{
public:
    explicit StringProxyRigid( std::string&& value )
        : m_value( std::move( value ))
    {}

private:
    std::string m_value;    
};


class StringProxySmart : public AnyConvertible< StringProxySmart >
{
public:
    explicit StringProxySmart( std::string&& value )
        : m_value( std::move( value ))
    {}

    Any ToAny() const { return Any( m_value ); }

private:
    std::string m_value;    
};


TEST( AnyConvertibleTest )
{
    StringProxyRigid rigid( "Rigid" );
    StringProxySmart smart( "Smart" );

    CHECK( false == IsAnyConvertibleT< StringProxyRigid >::VALUE );
    CHECK( true  == IsAnyConvertibleT< StringProxySmart >::VALUE );

    
    // Without AnyConvertible : it is a StringProxyRigid

    Any anyR( rigid );
    CHECK_THROW( anyR.As< std::string >(), Caramel::Exception );

    
    // With AnyConvertible : ToAny() gives it a std::string.

    Any anyS( smart );
    CHECK( "Smart" == anyS.As< std::string >() );

    const auto& csmart = smart;
    Any anyCs( csmart );
    CHECK( "Smart" == anyCs.As< std::string >() );
}


} // SUITE AnySuite

} // namespace Caramel
