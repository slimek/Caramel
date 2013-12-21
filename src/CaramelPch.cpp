// Caramel C++ Library - Precompiled Header Creator

#include "CaramelPch.h"
#include <boost/version.hpp>
#include <type_traits>

void CaramelPchDummy() {}


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Validation
//

/// Size of Fudamental Types ///

static_assert( 1 == sizeof( Int8 ),  "Int8 should be size 1" );
static_assert( 1 == sizeof( Uint8 ), "Uint8 should be size 1" );
static_assert( 2 == sizeof( Int16 ),  "Int16 should be size 2" );
static_assert( 2 == sizeof( Uint16 ), "Uint16 should be size 2" );
static_assert( 4 == sizeof( Int32 ),  "Int32 should be size 4" );
static_assert( 4 == sizeof( Uint32 ), "Uint32 should be size 4" );
static_assert( 8 == sizeof( Int64 ),  "Int64 should be size 8" );
static_assert( 8 == sizeof( Uint64 ), "Uint64 should be size 8" );


// The size of the below types may depend on the system...

static_assert( 4 == sizeof( Int ),   "Int should be size 4" );
static_assert( 4 == sizeof( Uint ),  "Uint should be size 4" );


#if !defined( CARAMEL_SYSTEM_IS_IOS )

// NOTES: In Xcode we can't get the size of Long/Ulong. The reason is unknown yet...

static_assert( 4 == sizeof( Long ),  "sizeof( Long ) should be 4" );
static_assert( 4 == sizeof( Ulong ), "sizeof( Ulong ) should be 4" );

#endif


/// Type Traits of Fundamental Typedefs ///

static_assert( std::is_signed< Int >  ::value, "Int should be signed" );
static_assert( std::is_signed< Int8 > ::value, "Int8 should be signed" );
static_assert( std::is_signed< Int16 >::value, "Int16 should be signed" );
static_assert( std::is_signed< Int32 >::value, "Int32 should be signed" );
static_assert( std::is_signed< Int64 >::value, "Int64 should be signed" );
static_assert( std::is_signed< Long > ::value, "Long should be signed" );

static_assert( std::is_unsigned< Uint >::value,   "Uint should be unsigned" );
static_assert( std::is_unsigned< Uint8 >::value,  "Uint8 should be unsigned" );
static_assert( std::is_unsigned< Uint16 >::value, "Uint16 should be unsigned" );
static_assert( std::is_unsigned< Uint32 >::value, "Uint32 should be unsigned" );
static_assert( std::is_unsigned< Uint64 >::value, "Uint64 should be unsigned" );
static_assert( std::is_unsigned< Ulong > ::value, "Ulong should be unsigned" );


/// Boost Versions ///

static_assert( 105400 == BOOST_VERSION, "Boost version not matched" );


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
