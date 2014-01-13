// Caramel C++ Library Test - Concurrent - Set Test

#include "CaramelTestPch.h"

#include <Caramel/Concurrent/Set.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( ConcurrentSetSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Basic Set Test
//

template< typename SetType >
void TestBasicIntSet( SetType& set )
{
}


///////////////////////////////////////////////////////////////////////////////
//
// Concurrent Set Test
//

TEST( ConcurrentSetTest )
{
    Concurrent::Set< Int > iset;
    TestBasicIntSet( iset );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE ConcurrentSetSuite

} // namespace Caramel

