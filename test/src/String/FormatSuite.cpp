// Caramel C++ Library Test - String - Format Suite

#include "CaramelTestPch.h"

#include <Caramel/Chrono/SecondClock.h>
#include <Caramel/Chrono/TickClock.h>
#include <Caramel/String/Format.h>
#include <Caramel/Value/Scalar.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( FormatSuite )
{

TEST( FormatTrivialTest )
{
    CHECK( "" == Format( "" ));

    const Char alice1[] = "Alice";
    const Char* alice2 = "Alice";
    const std::string alice3( "Alice" );

    CHECK( "Alice" == Format( "Alice" ));
    CHECK( "Alice" == Format( alice1 ));
    CHECK( "Alice" == Format( alice2 ));
    CHECK( "Alice" == Format( alice3 ));
}


TEST( FormatBooleanTest )
{
    CHECK( "Kami is true not false" == Format( "Kami is {0} not {1}", true, false ));
}


TEST( FormatIntegerTest )
{
    CHECK( "Score 0" == Format( "Score {0}", 0 ));
    CHECK( "Answer -1:42" == Format( "Answer {0}:{1}", -1, 42 ));
    CHECK( "2014/1/1 Happy NY!" == Format( "{0}/{1}/{2} Happy NY!", 2014, 1u, 1u ));
    CHECK( "Version 1.4.16.256" == Format( "Version {3}.{2}.{1}.{0}", 256, 16, 4, 1 ));

    const Int64 i64 = -123456789012;
    CHECK( "Int64 -123456789012" == Format( "Int64 {0}", i64 ));

    const Uint64 u64 = 123456789012;
    CHECK( "Uint64 123456789012" == Format( "Uint64 {0}", u64 ));

    const Long il = -45678912;
    CHECK( "Long -45678912" == Format( "Long {0}", il ));

    const Ulong ul = 45678912;
    CHECK( "Ulong 45678912" == Format( "Ulong {0}", ul ));
}


TEST( FormatFloatingTest )
{
    CHECK( "Score 0" == Format( "Score {0}", 0.0 ));
    CHECK( "Score 0" == Format( "Score {0}", 0.0f ));

    CHECK( "Answer 51.42" == Format( "Answer {0}", 51.42 ));
    CHECK( "65535 Years" == Format( "{0} Years", 65535.f ));
}


TEST( FormatStringTest )
{
    CHECK( "Miko: Reimu" == Format( "Miko: {0}", "Reimu" ));
    CHECK( "Ah Ha Ha Ha!" == Format( "{1} {0} {0} {0}!", "Ha", "Ah" ));

    auto text0 = "Perfect";
    const Char text1[] = "Cherry";
    const Char* text2 = "Blossom";

    CHECK( "Perfect Cherry Blossom" == Format( "{0} {1} {2}", text0, text1, text2 ));
}


TEST( FormatFailureTest )
{
    CHECK( "Score 0" == Format( "Score 0", 42 ));
    CHECK( "Score {0" == Format( "Score {0", 42 ));
    CHECK( "Score 0}" == Format( "Score 0}", 42 ));
    CHECK( "Score {}" == Format( "Score {}", 42 ));
}


TEST( FormatStringConvertibleTest )
{
    // Scalar is StringConvertible

    Scalar s0( 77 );
    Scalar s1( "Alice" );
    
    CHECK( "Alice has 77 dolls" == Format( "{1} has {0} dolls", s0, s1 ));
}


TEST( FormatNumberConvertibleTest )
{
    // Ticks and Seconds are NumberConvertible

    Ticks ticks( 512 );
    Seconds secs( 3.14 );

    CHECK( "512 3.14" == Format( "{0} {1}", ticks, secs ));
}


TEST( FormatFixedPointForFloatingTest )
{
    CHECK( "0.00"   == Format( "{0:F}", 0.0 ));  // default is F2
    CHECK( "3.1416" == Format( "{0:F4}", 3.1415926 ));
    CHECK( "511"    == Format( "{0:F0}", 511.49 ));
    CHECK( "512"    == Format( "{0:F0}", 511.50 ));
    CHECK( "42.000" == Format( "{0:F3}", 42.0 ));
    CHECK( "0"      == Format( "{0:F0}", 0.32757));
    CHECK( "0.001"  == Format( "{0:F3}", 0.00085 ));

    // 'f' can be lowercase
    CHECK( "3.1416" == Format( "{0:f4}", 3.1415926 ));
    CHECK( "511"    == Format( "{0:f0}", 511.49 ));
    CHECK( "512"    == Format( "{0:f0}", 511.50 ));
    CHECK( "42.000" == Format( "{0:f3}", 42.0 ));

    // Very long...
    CHECK( "0.123456789000" == Format( "{0:F12}", 0.123456789 ));
    CHECK( "7890123456.0" == Format( "{0:F1}", 7890123456.0 ));

    // Negative
    CHECK( "-6.23"    == Format( "{0:F}", -6.2253 ));
    CHECK( "-134"     == Format( "{0:F0}", -133.98 ));
    CHECK( "-4.52100" == Format( "{0:F5}", -4.521 ));
    CHECK( "-32.00"   == Format( "{0:F2}", -32.0 ));

    // Negative Zero
    // - Do not output "-0" or "-0.00" : according to .NET Format rule,
    //   a negative zero does not output with sing.
    CHECK( "0"    == Format( "{0:F0}", -0.1248 ));
    CHECK( "0.0"  == Format( "{0:F1}", -0.0123 ));
    CHECK( "0.00" == Format( "{0:f}", -0.0 ));

    // Rounding: MSVC and GCC/Clang are different:
    CHECK( "512" == Format( "{0:F0}", 512.49 ));
    #if defined( CARAMEL_COMPILER_IS_MSVC )
    CHECK( "513" == Format( "{0:F0}", 512.50 ));  // Round-up
    #else
    CHECK( "512" == Format( "{0:F0}", 512.50 ));  // Round-to-Even
    #endif
    CHECK( "513" == Format( "{0:F0}", 512.51 ));

    // Float is ok
    CHECK( "0.00"   == Format( "{0:F}", 0.0f ));
    CHECK( "3.1416" == Format( "{0:F4}", 3.1415926f ));
    CHECK( "511"    == Format( "{0:F0}", 511.49f ));
    CHECK( "512"    == Format( "{0:F0}", 511.50f ));
}


TEST( FormatFixedPointForIntegerTest )
{
    // Int / Int32
    CHECK( "0.00"    == Format( "{0:F}", 0 ));
    CHECK( "0"       == Format( "{0:F0}", 0 ));
    CHECK( "2048"    == Format( "{0:F0}", 2048 ));
    CHECK( "127.000" == Format( "{0:F3}", 127 ));
    CHECK( "-42.0"   == Format( "{0:F1}", -42 ));

    // Uint / Uint32
    CHECK( "0.00"    == Format( "{0:F}", 0u ));
    CHECK( "0"       == Format( "{0:F0}", 0u ));
    CHECK( "2048"    == Format( "{0:F0}", 2048u ));
    CHECK( "127.000" == Format( "{0:F3}", 127u ));
    CHECK( "4294967295.0" == Format( "{0:F1}", UINT_MAX ));

    // Int64
    CHECK( "0.00"    == Format( "{0:F}", 0ll ));
    CHECK( "0"       == Format( "{0:F0}", 0ll ));
    CHECK( "2048"    == Format( "{0:F0}", 2048ll ));
    CHECK( "127.000" == Format( "{0:F3}", 127ll ));
    CHECK( "-42.0"   == Format( "{0:F1}", -42ll ));

    // Uint64
    CHECK( "0.00"    == Format( "{0:F}", 0ull ));
    CHECK( "0"       == Format( "{0:F0}", 0ull ));
    CHECK( "2048"    == Format( "{0:F0}", 2048ull ));
    CHECK( "127.000" == Format( "{0:F3}", 127ull ));

    // Int16
    const Int16 i16z = 0;
    const Int16 i16u = 1;
    CHECK( "0.00"      == Format( "{0:F}",  i16z ));
    CHECK( "1"         == Format( "{0:F0}", i16u ));
    CHECK( "32767.000" == Format( "{0:F3}", INT16_MAX ));
    CHECK( "-32768.0"  == Format( "{0:F1}", INT16_MIN ));

    // Uint16
    const Uint16 u16z = 0;
    const Uint16 u16u = 1;
    CHECK( "0.00"      == Format( "{0:F}",  u16z ));
    CHECK( "1"         == Format( "{0:F0}", u16u ));
    CHECK( "65535.000" == Format( "{0:F3}", UINT16_MAX ));

    // Int8
    const Int8 i8z = 0;
    const Int8 i8u = 1;
    CHECK( "0.00"    == Format( "{0:F}",  i8z ));
    CHECK( "1"       == Format( "{0:F0}", i8u ));
    CHECK( "127.000" == Format( "{0:F3}", INT8_MAX ));
    CHECK( "-128.0"  == Format( "{0:F1}", INT8_MIN ));

    // Uint8
    const Uint8 u8z = 0;
    const Uint8 u8u = 1;
    CHECK( "0.00"    == Format( "{0:F}",  u8z ));
    CHECK( "1"       == Format( "{0:F0}", u8u ));
    CHECK( "255.000" == Format( "{0:F3}", UINT8_MAX ));
}


TEST( FormatNumberTest )
{
    /// Floatings ///

    CHECK( "0.00"   == Format( "{0:N}", 0.0 ));   // Default is N2
    CHECK( "3.1416" == Format( "{0:N4}", 3.1415926 ));
    CHECK( "512"    == Format( "{0:N0}", 512.49 ));

    CHECK( "123,456.789"  == Format( "{0:N3}", 123456.789 ));
    CHECK( "32,159.001"   == Format( "{0:N3}", 32159.00085 ));
    CHECK( "-24,515,387.2" == Format( "{0:N1}", -24515387.2 ));
    CHECK( "-0.14286"      == Format( "{0:N5}", -0.142857 ));
    CHECK( "-127.94"       == Format( "{0:N}", -127.94 ));

    // 'n' can be lowercase
    CHECK( "47.13" == Format( "{0:n}", 47.128 ));
    CHECK( "1,023" == Format( "{0:n0}", 1022.52 ));


    /// Integers ///

    CHECK( "0.00" == Format( "{0:N}", 0 ));     // Default is N2

    CHECK( "1,234.00"  == Format( "{0:N}", 1234 ));
    CHECK( "573,012.0" == Format( "{0:N1}", 573012 ));
    CHECK( "-25,357"   == Format( "{0:N0}", -25357 ));
    CHECK( "-365.0000" == Format( "{0:N4}", -365 ));
    
    CHECK( "4,294,967,295" == Format( "{0:N0}", UINT_MAX ));

    // 'n' can be lowercase
    CHECK( "-35.00"        == Format( "{0:n}", -35 ));
    CHECK( "1,875,300.000" == Format( "{0:n3}", 1875300 ));
}


TEST( FormatHexadecimalTest )
{
    CHECK( "0" == Format( "{0:X}", 0 ));   // Default is X1

    CHECK( "1AE"   == Format( "{0:X}", 0x1AE ));
    CHECK( "1AE"   == Format( "{0:X0}", 0x1AE ));
    CHECK( "001AE" == Format( "{0:X5}", 0x1AE ));

    // Int / Int32
    const Int32 i32n = -1;
    CHECK( "7FFFFFFF" == Format( "{0:X}", INT32_MAX ));
    CHECK( "FFFFFFFF" == Format( "{0:X}", i32n ));

    // Uint / UInt32
    CHECK( "FFFFFFFF" == Format( "{0:X}", UINT32_MAX ));

    // Int8
    const Int8 i8n = -1;
    CHECK( "7F" == Format( "{0:X}", INT8_MAX ));
    CHECK( "FF" == Format( "{0:X}", i8n ));
    CHECK( "000FF" == Format( "{0:X5}", i8n ));

    // Uint8
    const Uint8 u8v = 124;
    CHECK( "7C" == Format( "{0:X}", u8v ));
    CHECK( "FF" == Format( "{0:X}", UINT8_MAX ));
    CHECK( "000FF" == Format( "{0:X5}", UINT8_MAX ));

    // Int16
    const Int16 i16n = -1;
    CHECK( "7FFF" == Format( "{0:X}", INT16_MAX ));
    CHECK( "FFFF" == Format( "{0:X}", i16n ));
    CHECK( "0FFFF" == Format( "{0:X5}", i16n ));

    // Uint16
    const Uint16 u16v = 32754;
    CHECK( "7FF2" == Format( "{0:X}", u16v ));
    CHECK( "FFFF" == Format( "{0:X}", UINT16_MAX ));
    CHECK( "0FFFF" == Format( "{0:X5}", UINT16_MAX ));

    // Int64
    const Int64 i64n = -1;
    CHECK( "7FFFFFFFFFFFFFFF" == Format( "{0:X}", INT64_MAX ));
    CHECK( "FFFFFFFFFFFFFFFF" == Format( "{0:X}", i64n ));

    // Uint64
    const Uint64 u64v = 1000000000000uLL;
    CHECK( "E8D4A51000" == Format( "{0:X}", u64v ));
    CHECK( "FFFFFFFFFFFFFFFF" == Format( "{0:X}", UINT64_MAX ));
    CHECK( "FFFFFFFFFFFFFFFF" == Format( "{0:X5}", UINT64_MAX ));

    // Lowercase
    CHECK( "1ae"   == Format( "{0:x}", 0x1AE ));
    CHECK( "1ae"   == Format( "{0:x0}", 0x1AE ));
    CHECK( "001ae" == Format( "{0:x5}", 0x1AE ));
    CHECK( "ff"    == Format( "{0:x}", i8n ));
    CHECK( "7c"    == Format( "{0:x}", u8v ));
    CHECK( "0ffff" == Format( "{0:x5}", i16n ));
    CHECK( "7ff2"  == Format( "{0:x}", u16v ));
    CHECK( "e8d4a51000" == Format( "{0:x}", u64v ));
}


TEST( FormatArgumentsTest )
{
    CHECK( "ABCDEFGH12345678" ==
        Format( "{0}{1}{2}{3}{4}{5}{6}{7}{8}{9}{10}{11}{12}{13}{14}{15}",
                "A", "B", "C", "D", "E", "F", "G", "H", 1, 2, 3, 4, 5, 6, 7, 8 ));

    CHECK( "7777777777777777" ==
        Format( "{0}{0}{0}{0}{0}{0}{0}{0}{0}{0}{0}{0}{0}{0}{0}{0}", 7 ));

    
    /// Missing Arguments - the placeholder would disappear ///

    CHECK( "Yukari" == Format( "Y{0}k{1}a{2}ri{3}", "u" ));
    CHECK( "Yakumo" == Format( "Y{0}aku{1}{2}m{3}o" ));


    /// Redundant Arguments would be discarded ///

    CHECK( "Yuyuko" == Format( "Yu{0}ko", "yu", 8, "saki", "lunatic" ));
}


} // SUITE FormatSuite

} // namespace Caramel
