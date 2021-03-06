// Caramel C++ Library - I/O Facility - Output File Stream Header

#ifndef __CARAMEL_IO_OUTPUT_FILE_STREAM_H
#define __CARAMEL_IO_OUTPUT_FILE_STREAM_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Io/FileStream.h>
#include <Caramel/Io/OutputStream.h>
#include <Caramel/String/Utf8String.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Output File Stream
//

class OutputFileStream : public FileStream
                       , public OutputStream
{
public:

    OutputFileStream();

    explicit OutputFileStream( const std::string& fileName );
    explicit OutputFileStream( const Utf8String&  fileName );

    
    //
    // Opertions
    //

    void Flush();


    //
    // Implements OutputStream
    //

    void Write( const Void* data, Usize size ) override;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_OUTPUT_FILE_STREAM_H
