// Caramel C++ Library Test - Meta - Is General String Suite

#include "CaramelTestPch.h"

#include <Caramel/Meta/IsGeneralString.h>
#include <vector>


namespace Caramel
{

SUITE( IsGeneralStringSuite )
{

class IgsTester
{
public:

    template< typename T >
    IgsTester( const T& seed )
    {
        m_value = IsGeneralStringT< T >::VALUE; 
    }

    operator Bool() const { return m_value; }

private:
    Bool m_value;
};


TEST( IsGeneralStringTest )
{
    /// Fundamental Types ///

    CHECK( false == IgsTester( 1 ));
    CHECK( false == IgsTester( true ));
    CHECK( false == IgsTester( nullptr ));
    
    
    /// General Strings ///

    CHECK( true == IgsTester( "Alice" ));
    CHECK( true == IgsTester( std::string( "Marisa" )));


    const Char* csz = "Const Char Ptr";
    CHECK( true == IgsTester( csz ));

    Char* sz = (Char*)( "Char Ptr" );
    CHECK( true == IgsTester( sz ));

    const Char csa[] = "Const Char Array";
    CHECK( true == IgsTester( csa ));

    Char sa[] = "Char Array";
    CHECK( true == IgsTester( sa ));

    const std::string cs = "Const String";
    CHECK( true == IgsTester( cs ));

    std::string s = "String";
    CHECK( true == IgsTester( s ));


    /// Arbitrary Types ///

    CHECK( false == IgsTester( IgsTester( 1 )));
    CHECK( false == IgsTester( std::vector< Char >() ));
}


} // SUITE IsGeneralStringSuite

} // namespace Caramel
