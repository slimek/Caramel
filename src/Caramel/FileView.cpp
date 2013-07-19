// Caramel C++ Library - File View Facility - Implementation

#include <Caramel/CaramelPch.h>

#include <Caramel/FileView/IniFileViewImpl.h>


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


IniFileView::IniFileView( const Path& path )
    : m_impl( new IniFileViewImpl )
{
    this->LoadFromFile( path );
}


IniFileView::~IniFileView()
{
}


void IniFileView::LoadFromFile( const Path& inputPath )
{
    const Path fullPath = inputPath.HasExtension()
                        ? inputPath
                        : inputPath.AppendExtension( ".ini" );

}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
