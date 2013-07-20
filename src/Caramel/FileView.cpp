// Caramel C++ Library - File View Facility - Implementation

#include <Caramel/CaramelPch.h>

#include <Caramel/FileView/IniFileViewImpl.h>
#include <Caramel/Io/InputFileStream.h>
#include <Caramel/Io/TextStreamReader.h>


namespace Caramel
{

//
// Contents
//
// 1. IniFileView
//

///////////////////////////////////////////////////////////////////////////////
//
// INI File View
//

IniFileView::IniFileView()
    : m_impl( new IniFileViewImpl )
{
}


IniFileView::IniFileView( const Utf8String& fileName )
    : m_impl( new IniFileViewImpl )
{
    this->LoadFromFile( fileName );
}


IniFileView::~IniFileView()
{
}


void IniFileView::LoadFromFile( const Utf8String& fileName )
{
    const Path inputPath( fileName );

    const Path fullPath = inputPath.HasExtension()
                        ? inputPath
                        : inputPath.AppendExtension( "ini" );

    InputFileStream file( fullPath );
    TextStreamReader reader( file );

    m_impl->LoadFromText( reader );
}


void IniFileView::LoadFromText( TextReader& reader )
{
    m_impl->LoadFromText( reader );
}


//
// Implementation
//

void IniFileViewImpl::LoadFromText( TextReader& reader )
{
    
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
