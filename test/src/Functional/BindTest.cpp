// Caramel C++ Library Test - Functional - Bind Test

#include "CaramelTestPch.h"

#include <Caramel/Functional/Bind.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( BindSuite )
{

//
// Utilities
//

static Int Plus( Int x, Int y ) { return x + y; }
static std::string Append( const std::string& x, const std::string& y ) { return x + y; }

class Widget
{
public:
    Int Double( Int x ) const { return x * 2; }
    void SetName( const std::string& name ) { m_name = name; }
    std::string GetName() const { return m_name; }

private:
    std::string m_name;
};


//
// Test Bind1st
// - With function types:
//   1. Regular function
//   2. Member function, const or non-const
//   3. Lambda expression
//

TEST( Bind1stTest )
{
    /// Regular Functions ///

    auto plus3 = Bind1st( &Plus, 3 );
    CHECK( 7 == plus3( 4 ));

    auto appendAlice = Bind1st( &Append, "Alice" );
    CHECK( "Alice.Dollmaster" == appendAlice( ".Dollmaster" ));


    /// Member Functions ///

    Widget w;

    auto wdouble = Bind1st( &Widget::Double, &w );
    CHECK( 16 == wdouble( 8 ));

    auto wsetname = Bind1st( &Widget::SetName, &w );
    wsetname( "Reimu" );
    CHECK( "Reimu" == w.GetName() );


    /// Lambda Expression ///

    auto mul5 = Bind1st( [] ( Double x, Double y ) { return x * y; }, 5 );
    CHECK( 35 == mul5( 7 ));
}

} // SUITE BindSuite

} // namespace Caramel
