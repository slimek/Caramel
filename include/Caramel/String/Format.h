// Caramel C++ Library - String Facility - Format Header

#ifndef __CARAMEL_STRING_FORMAT_H
#define __CARAMEL_STRING_FORMAT_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/String/Detail/Formatter.h>
#include <Caramel/String/Detail/FormatRecursive.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Format Function
//
//   Format is a strong-typed version of sprintf :
//
//   1. It detects the types of arguments with type-traits technique,
//      and choose an appropriate method to convert the arguments to strings.
//   2. Based on C++11 variadic template, it may accept any number of arguments.
//
//   The syntax of the format string is a mini subset of .NET Framework composite
//   format string. Please see the below for more details.
//

template< typename... Args >
inline std::string Format( const std::string& format, const Args&... args )
{
    Detail::Formatter formatter( format );
    return Detail::FormatRecursive( formatter, args... );
}


//
// Syntax of Format String
//
//   Format item is surrounded by braces. The syntax is:
//
//     {index[:format-string]}
//
//   Example:
//     const auto s = Format( "Name = {0}, Score = {1:F}", name, score );
//
//   
//   Index
//
//     The index refers to the arguments, starts from 0.
//   
//     Multple items can refer to the same argument, sometimes with different
//     format string.
//
//         Example: "{0} {0} {0:F}"
//
//     Item can refer to the arguments in any order.
//
//         Example: "{2} {0} {1}"
//
//     If its index does not present, the argument is just ignored.
//
//
//   Format String for Arithmetic Item
//
//     "F" or "f" : Fixed-point, number of decimal digits. Default precision is 2.
//
//         [Floating]
// 
//         1234.567 "F"  -> 1234.57    (default)
//         1234.567 "F0" -> 1235       (the decimal point is also omitted)
//         1234.567 "F1" -> 1234.6
//         1234.567 "F5" -> 1234.56700
//
//         [Integer]
//
//         1234  "F"  -> 1234.00    (default)
//         1234  "F0" -> 1234       (the decimal point is also omitted)
//         1234  "F3" -> 1234.000
//
//
//     "N" or "n" : Number with group separators and decimal digits. Default precision is 2.
//
//         [Floating]
//
//         1234.567 "N"  -> 1,234.57    (default)
//         1234.567 "N0" -> 1,235       (the decimal point is also omitted)
//         1234.567 "N1" -> 1,234.6
//         1234.567 "N5" -> 1,234.56700
//
//         [Integer]
//
//         1234  "N"  -> 1,234.00    (default)
//         1234  "N0" -> 1,234       (the decimal point is also omitted)
//         1234  "N3" -> 1,234.000
//
//
//   Format String for Integral Item
//
//     "D" or "d" : Decimal. The precision is the least digits, may pad with '0'.
//
//         1234  "D"  -> 1234
//         1234  "D6" -> 001234
//         1234  "D3" -> 1234
//        -1234  "D5" -> -01234

//
//     "X" or "x" : Hexadecimal. The precision is the least digits, may pad with '0'.
//
//         1234  "X"  -> 4D2
//         1234  "X5" -> 004D2
//         1234  "X1" -> 4D2     
//         1234  "x"  -> 4d2     (lowercase)
//
//
//   Acceptable Argument Types
//
//     1. All arithmetic types.
//     2. Enum types.
//     3. std::string and C-style strings.
//     4. Classes derived from StringConvertible or NumberConvertible.
//     5. Reference of all the above types.
//
//
//     NOTES: Pointers are not accepted by Format. If you need to represent the 
//            address of a pointer, cast it to an integer first.
//
//     See <Caramel/String/Detail/FormatParameter.h> for more details.
//

///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_FORMAT_H
