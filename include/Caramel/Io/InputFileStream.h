// Caramel C++ Library - I/O Amenity - Input File Stream Header

#ifndef __CARAMEL_IO_INPUT_FILE_STREAM_H
#define __CARAMEL_IO_INPUT_FILE_STREAM_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Io/Detail/FileStream.h>
#include <Caramel/Io/InputStream.h>
#include <Caramel/String/Utf8String.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Input File Stream
//

class InputFileStream : public Detail::FileStream
                      , public InputStream
{
public:

    InputFileStream();

    explicit InputFileStream( const Utf8String& fileName );

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_INPUT_FILE_STREAM_H
