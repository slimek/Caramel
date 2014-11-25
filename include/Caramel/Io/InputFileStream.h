// Caramel C++ Library - I/O Facility - Input File Stream Header

#ifndef __CARAMEL_IO_INPUT_FILE_STREAM_H
#define __CARAMEL_IO_INPUT_FILE_STREAM_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Io/FileStream.h>
#include <Caramel/Io/InputStream.h>
#include <Caramel/String/Utf8String.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Input File Stream
//

class InputFileStream : public FileStream
                      , public InputStream
{
public:

    InputFileStream();

    explicit InputFileStream( const std::string& fileName );
    explicit InputFileStream( const Utf8String&  fileName );


    //
    // Implements InputStream
    //

    Uint Read( Void* buffer, Uint size ) override;

    void Seek( Int offset ) override;

    Uint Tell() const override;

    Bool IsEof() const override;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_INPUT_FILE_STREAM_H
