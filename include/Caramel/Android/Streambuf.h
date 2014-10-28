// Caramel C++ Library - Android Facility - Streambuf Header

#ifndef __CARAMEL_ANDROID_STREAMBUF_H
#define __CARAMEL_ANDROID_STREAMBUF_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <iostream>


#if defined( CARAMEL_SYSTEM_IS_ANDROID )

namespace Caramel
{

namespace Android
{

///////////////////////////////////////////////////////////////////////////////
//
// Streambuf
// - This class may redirect std::cout or std::cerr to Android log.
//
//   USAGE:
//
//     std::cout.rdbuf( new Android::Streambuf( "std::cout" );
//

class Streambuf : public std::streambuf
{
public:

    explicit Streambuf( std::string name );

private:

    Int overflow( Int c ) override;
    Int sync() override;

    static const Uint BUFFER_SIZE = 4096;

    std::string m_name;
    Char m_buffer[ BUFFER_SIZE ];
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Android

} // namespace Caramel

#endif // CARAMEL_SYSTEM_IS_ANDROID

#endif // __CARAMEL_ANDROID_STREAMBUF_H
