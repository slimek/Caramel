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

/// Size of Fundamental Types ///

static_assert( 1 == sizeof( Int8 ),  "Int8 should be size 1" );
static_assert( 1 == sizeof( Uint8 ), "Uint8 should be size 1" );
static_assert( 2 == sizeof( Int16 ),  "Int16 should be size 2" );
static_assert( 2 == sizeof( Uint16 ), "Uint16 should be size 2" );
static_assert( 4 == sizeof( Int32 ),  "Int32 should be size 4" );
static_assert( 4 == sizeof( Uint32 ), "Uint32 should be size 4" );
static_assert( 8 == sizeof( Int64 ),  "Int64 should be size 8" );
static_assert( 8 == sizeof( Uint64 ), "Uint64 should be size 8" );

static_assert( 1 == sizeof( Char ), "Char should be size 1" );
static_assert( 1 == sizeof( Byte ), "Byte should be size 1" );

static_assert( 4 == sizeof( Int ),  "Int should be size 4" );
static_assert( 4 == sizeof( Uint ), "Uint should be size 4" );



/// Type Aliases ///

static_assert( std::is_same< Byte, Uint8 > ::value, "Byte and Uint8 should be the same" );
static_assert( std::is_same< Int,  Int32 > ::value, "Int and Int32 should be the same" );
static_assert( std::is_same< Uint, Uint32 >::value, "Uint and Uint32 should be the same" );


/// Types that are similar but not the same ///

static_assert( ! std::is_same< Char,  Int8 >  ::value, "Char and Int8 are different" );    // Visual C++
static_assert( ! std::is_same< Char,  Uint8 > ::value, "Char and Uint8 are different" );   // GNU C++
static_assert( ! std::is_same< Wchar, Int16 > ::value, "Wchar and Int16 are different" );  
static_assert( ! std::is_same< Wchar, Uint16 >::value, "Wchar and Uint16 are different" ); // Visual C++
static_assert( ! std::is_same< Wchar, Int32 > ::value, "Wchar and Int32 are different" );  // GNU C++
static_assert( ! std::is_same< Wchar, Uint32 >::value, "Wchar and Uint32 are different" );
static_assert( ! std::is_same< Long,  Int32 > ::value, "Long and Int32 are different" );
static_assert( ! std::is_same< Long,  Int64 > ::value, "Long and Int64 are different" );
static_assert( ! std::is_same< Ulong, Uint32 >::value, "Ulong and Uint32 are different" );
static_assert( ! std::is_same< Ulong, Uint64 >::value, "Ulong and Uint64 are different" );


/// Signed or Unsigned ///

static_assert( std::is_signed< Int >  ::value, "Int should be signed" );
static_assert( std::is_signed< Int8 > ::value, "Int8 should be signed" );
static_assert( std::is_signed< Int16 >::value, "Int16 should be signed" );
static_assert( std::is_signed< Int32 >::value, "Int32 should be signed" );
static_assert( std::is_signed< Int64 >::value, "Int64 should be signed" );
static_assert( std::is_signed< Long > ::value, "Long should be signed" );

static_assert( std::is_unsigned< Uint >  ::value, "Uint should be unsigned" );
static_assert( std::is_unsigned< Uint8 > ::value, "Uint8 should be unsigned" );
static_assert( std::is_unsigned< Uint16 >::value, "Uint16 should be unsigned" );
static_assert( std::is_unsigned< Uint32 >::value, "Uint32 should be unsigned" );
static_assert( std::is_unsigned< Uint64 >::value, "Uint64 should be unsigned" );
static_assert( std::is_unsigned< Ulong > ::value, "Ulong should be unsigned" );

static_assert( std::is_unsigned< Byte >::value, "Byte should be unsigned" );


//
// Some fundamental types depend on Compiler and System:
//
//                  Visual C++   Clang        GNU C++
//   Int / Uint   | always 32  | always 32  | (not verify yet)
//   Long / Ulong | always 32  | 32 or 64   |
//
// std::size_t (Usize) are different typedefs :
//
//                  Visual C++   Clang        GNU C++
//   OS is 32-bit | Uint       | Ulong      | Uint
//         64-bit | Uitn64     | Ulong      | ?
//
// wchar_t (Wchar) size depends on System
//
//               Windows   OS X & iOS   Android
//   wchar_t   | 2       | 4          | 4
//

#if defined( CARAMEL_LONG_IS_64_BIT )

static_assert( 8 == sizeof( Long ),  "sizeof( Long ) should be 8" );
static_assert( 8 == sizeof( Ulong ), "sizeof( Ulong ) should be 8" );

#else

static_assert( 4 == sizeof( Long ),  "sizeof( Long ) should be 4" );
static_assert( 4 == sizeof( Ulong ), "sizeof( Ulong ) should be 4" );

#endif // Long is 64-bit


// Verify the underlying type of std::size_t

#if defined( CARAMEL_SIZE_T_IS_ULONG )
static_assert( std::is_same< std::size_t, Ulong >::value, "std::size_t should be Ulong" );

#elif defined( CARAMEL_SIZE_T_IS_UINT32 )
static_assert( std::is_same< std::size_t, Uint32 >::value, "std::size_t should be Uint32" );

#elif defined( CARAMEL_SIZE_T_IS_UINT64 )
static_assert( std::is_same< std::size_t, Uint64 >::value, "std::size_t should be Uint64" );

#else
#error std::size_t underline type not detected.

#endif


#if defined( CARAMEL_SYSTEM_IS_64_BIT )
static_assert( 8 == sizeof( std::size_t ), "sizeof( std::size_t ) should be 8" );

#else
static_assert( 4 == sizeof( std::size_t ), "sizeof( std::size_t ) should be 4" );

#endif  // System is 64-bit


#if defined( CARAMEL_WCHAR_IS_32_BIT )
static_assert( 4 == sizeof( Wchar ), "sizeof( Wchar ) should be 4" );

#elif defined( CARAMEL_WCHAR_IS_16_BIT )
static_assert( 2 == sizeof( Wchar ), "sizeof( Wchar ) should be 2" );

#else
#error Wchar size not detected

#endif  // Size of Wchar


/// Boost Versions ///

static_assert( 105400 == BOOST_VERSION, "Boost version not matched" );


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
