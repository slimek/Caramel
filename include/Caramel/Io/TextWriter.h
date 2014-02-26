// Caramel C++ Library - I/O Facility - Text Writer Header

#ifndef __CARAMEL_IO_TEXT_WRITER_H
#define __CARAMEL_IO_TEXT_WRITER_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/String/Utf8String.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Text Writer
// - Interface
//

struct TextWriter
{
    virtual ~TextWriter() {}

    //
    // Write a UTF-8 encoded text.
    // - Throws if the text is not UTF-8 encoded.
    //
    virtual void Write( const std::string& text ) = 0;
    virtual void Write( const Utf8String& text ) = 0;

    //
    // Write a UTF-8 encoded text, then append a new line character.
    // - Throws if the text is not UTF-8 encoded.
    //
    virtual void WriteLine( const std::string& text ) = 0;
    virtual void WriteLine( const Utf8String& text ) = 0;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_TEXT_WRITER_H
