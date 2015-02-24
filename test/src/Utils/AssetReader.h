// Caramel C++ Library Test - Utilits - Asset Reader Header

#ifndef __CARAMEL_TEST_UTILS_ASSET_READER_H
#define __CARAMEL_TEST_UTILS_ASSET_READER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Io/InputFileStream.h>
#include <Caramel/Io/InputMemoryStream.h>
#include <Caramel/Io/TextStreamReader.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Asset Reader
// - A text reader which read data from files in assets directory.
//

#if defined( CARAMEL_SYSTEM_OF_DESKTOP )

class AssetReader : public TextReader
{
public:
    explicit AssetReader( const std::string& fileName );

    Bool ReadLine( std::string& line ) override;

private:
    
    InputFileStream m_file;
    TextStreamReader m_reader;
};

#elif defined( CARAMEL_SYSTEM_IS_ANDROID )

class AssetReader : public TextReader
{
public:
    explicit AssetReader( const std::string& fileName );

    Bool ReadLine( std::string& line ) override;

private:

    std::vector< Byte > m_buffer;
    std::unique_ptr< InputMemoryStream > m_stream;
    std::unique_ptr< TextStreamReader > m_reader;
};

#endif


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TEST_UTILS_ASSET_READER_H
