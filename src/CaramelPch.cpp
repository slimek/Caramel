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


// Type aliases

static_assert( std::is_same< Byte, Uint8 >::value, "Byte and Uint8 should be the same" );


// Type similar but not the same

static_assert( ! std::is_same< Char, Int8 >::value, "Char and Int8 are different" );


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


//
// Some fundamental types depend on Compiler and System:
//
//                  Visual C++   Clang        GNU C++
//   Int / Uint   | 32 or 64   | always 32  | (not verify yet)
//   Long / Ulong | always 32  | 32 or 64   |
//
// std::size_t (Usize) are also different:
//
//                  Visual C++   Clang        GNU C++
//   std::size_t  | Uint       | Ulong      | Uint
//

//
// Visual C+
//

#if defined( CARAMEL_COMPILER_IS_MSVC )

static_assert( ! std::is_same< Long, Int32 >::value, "Long should be an individual type" );

static_assert( 4 == sizeof( Long ),  "sizeof( Long ) should be 4" );
static_assert( 4 == sizeof( Ulong ), "sizeof( Ulong ) should be 4" );


#if defined( CARAMEL_SYSTEM_IS_64_BIT )

static_assert( 8 == sizeof( Int ),   "Int should be size 8" );
static_assert( 8 == sizeof( Uint ),  "Uint should be size 8" );

static_assert( std::is_same< Int,  Int64  >::value, "Int and Int64 should be the same" );
static_assert( std::is_same< Uint, Uint64 >::value, "Uint and Uint64 should be the same" );

static_assert( 8 == sizeof( Usize ), "sizeof( std::size_t ) should be 8" );

static_assert( std::is_same< Usize, Uint64 >::value, "std::size_t should be Uint64" );


#else // System is 32-bit

static_assert( 4 == sizeof( Int ),   "Int should be size 4" );
static_assert( 4 == sizeof( Uint ),  "Uint should be size 4" );

static_assert( std::is_same< Int,  Int32  >::value, "Int and Int32 should be the same" );
static_assert( std::is_same< Uint, Uint32 >::value, "Uint and Uint32 should be the same" );

static_assert( 4 == sizeof( Usize ), "sizeof( std::size_t ) should be 4" );

static_assert( std::is_same< Usize, Uint32 >::value, "std::size_t should be Uint32" );


#endif


//
// Clang
//

#elif defined( CARAMEL_COMPILER_IS_CLANG )

static_assert( 4 == sizeof( Int ),   "Int should be size 4" );
static_assert( 4 == sizeof( Uint ),  "Uint should be size 4" );

static_assert( std::is_same< Int,  Int32  >::value, "Int and Int32 should be the same" );
static_assert( std::is_same< Uint, Uint32 >::value, "Uint and Uint32 should be the same" );

static_assert( std::is_same< std::size_t, Ulong >::value, "std::size_t should be Ulong" );


#if defined( CARAMEL_SYSTEM_IS_64_BIT )

static_assert( ! std::is_same< Long, Int64 >::value, "Long should be an individual type" );

static_assert( 8 == sizeof( Long ),  "sizeof( Long ) should be 8" );
static_assert( 8 == sizeof( Ulong ), "sizeof( Ulong ) should be 8" );
static_assert( 8 == sizeof( Usize ), "sizeof( std::size_t ) should be 8" );


#else // System is 32-bit

static_assert( ! std::is_same< Long, Int32 >::value, "Long should be an individual type" );

static_assert( 4 == sizeof( Long ),  "sizeof( Long ) should be 4" );
static_assert( 4 == sizeof( Ulong ), "sizeof( Ulong ) should be 4" );
static_assert( 4 == sizeof( Usize ), "sizeof( std::size_t ) should be 4" );


#endif


//
// GNU C++
//

#elif defined( CARAMEL_COMPILER_IS_GCC )

static_assert( 4 == sizeof( Int ),   "Int should be size 4" );
static_assert( 4 == sizeof( Uint ),  "Uint should be size 4" );

static_assert( std::is_same< Int,  Int32  >::value, "Int and Int32 should be the same" );
static_assert( std::is_same< Uint, Uint32 >::value, "Uint and Uint32 should be the same" );

static_assert( std::is_same< Usize, Uint >::value, "std::size_t should be Uint" );


#if defined( CARAMEL_SYSTEM_IS_64_BIT )

// TODO: Not verify yet.

static_assert( ! std::is_same< Long, Int64 >::value, "Long should be an individual type" );

static_assert( 8 == sizeof( Long ),  "sizeof( Long ) should be 8" );
static_assert( 8 == sizeof( Ulong ), "sizeof( Ulong ) should be 8" );

static_assert( 8 == sizeof( Usize ), "sizeof( std::size_t ) should be 8" );

static_assert( std::is_same< Usize, Uint64 >::value, "std::size_t should be Uint64" );


#else // System is 32-bit

static_assert( ! std::is_same< Long, Int32 >::value, "Long should be an individual type" );

static_assert( 4 == sizeof( Long ),  "sizeof( Long ) should be 4" );
static_assert( 4 == sizeof( Ulong ), "sizeof( Ulong ) should be 4" );

static_assert( 4 == sizeof( Usize ), "sizeof( std::size_t ) should be 4" );

static_assert( std::is_same< Usize, Uint32 >::value, "std::size_t should be Uint32" );


#endif

#endif // CARAMEL_COMPILER_IS_xxx


/// Boost Versions ///

static_assert( 105400 == BOOST_VERSION, "Boost version not matched" );


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
