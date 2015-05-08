// Caramel C++ Library Test - Object - Instance-Counted Suite

#include "CaramelTestPch.h"

#include <Caramel/Object/InstanceCounted.h>


namespace Caramel
{

SUITE( InstanceCounted )
{

class Widget : public InstanceCounted< Widget >
{
public:
    explicit Widget( std::string value )
        : m_value( std::move( value ))
    {}

    explicit Widget( const Widget& w )
        : m_value( w.m_value )
    {}

    explicit Widget( Widget&& w )
        : m_value( std::move( w.m_value ))
    {}

    Widget& operator=( const Widget& w )
    {
        m_value = w.m_value;
        return *this;
    }

    Widget& operator=( Widget&& w )
    {
        m_value = std::move( w.m_value );
        return *this;
    }

    std::string Value() const { return m_value; }

private:
    std::string m_value;
};


TEST( InstanceCounted )
{
    CHECK( 0 == Widget::GetInstanceCount() );

    Widget w1( "Alice" );

    CHECK( 1 == Widget::GetInstanceCount() );

    {
        Widget w2( w1 );

        CHECK( 2 == Widget::GetInstanceCount() );

        Widget w3( std::move( w1 ));

        CHECK( 3 == Widget::GetInstanceCount() );
    
        Widget w4( "Reimu" );
        w1 = w4;

        CHECK( 4 == Widget::GetInstanceCount() );

        w2 = std::move( w4 );

        CHECK( 4 == Widget::GetInstanceCount() );
    }

    CHECK( 1 == Widget::GetInstanceCount() );
}

} // SUITE InstanceCounted

} // namespace Caramel
