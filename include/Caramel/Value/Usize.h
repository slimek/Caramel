// Caramel C++ Library - Value Facility - Usize Header

#ifndef __CARAMEL_VALUE_USIZE_H
#define __CARAMEL_VALUE_USIZE_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Unsigned Size
// - An integer adpater that convert 32/64-bit integers into Uint (usngined 32-bit).
//
//   This class is a workaround for std::size_t, which is different types in
//   32/64-bit system. Further, the underlying type of 64-bit std::size_t depends
//   on compilter.
//
//                  Visual C++   Clang        GNU C++
//   OS is 32-bit | Uint       | Ulong      | Uint
//         64-bit | Uitn64     | Ulong      | ?
//
//   For functions which may accept a std::size_t parameter (e.g. std::string::lenght() )
//   you may use Usize as the parameter types.
//
//      void Foo( Usize size );
//
//    Then the following usages are all legal :
//
//      std::vector< Int > values;
//      SharedArray< Byte > buffer;
//
//      Foo( 5 );               // Int
//      Foo( values.size() );   // std::size_t, may by Uint or Long
//      Foo( buffer.Size() );   // Uint
//

class Usize
{
public:

    Usize() {}

    // Trivial constructor
    Usize( Uint value ) : m_value( value ) {}

    // Throws if value is out of range.
    Usize( Ulong  value );
    Usize( Uint64 value );

    // Throws if value is out of range, or is negative.
    Usize( Int   value );
    Usize( Long  value );
    Usize( Int64 value );

    // Boolean is not allowed.
    Usize( Bool value ) = delete;

    // Conversions
    operator Uint() const { return m_value; }
    Uint ToUint()   const { return m_value; }

private:

    template< typename T >
    void Init( T value );

    Uint m_value { 0 };
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_VALUE_USIZE_H

