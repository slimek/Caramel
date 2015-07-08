// Caramel C++ Library - File System Facility - Implementation

#include "CaramelPch.h"

#include "FileSystem/PathImpl.h"
#include <Caramel/FileSystem/DirectoryInfo.h>
#include <Caramel/FileSystem/FileInfo.h>


namespace Caramel
{

//
// Contents
//
//   DirectoryInfo
//   FileInfo
//   Path
//

///////////////////////////////////////////////////////////////////////////////
//
// Directory Info
//

DirectoryInfo::DirectoryInfo( const Path& path )
    : m_path( path.m_impl )
{
}


DirectoryInfo::DirectoryInfo( std::shared_ptr< PathImpl > path )
    : m_path( path )
{
}


DirectoryInfo DirectoryInfo::Current()
{
    return DirectoryInfo( std::make_shared< PathImpl >( boost::filesystem::current_path() ));
}


Bool DirectoryInfo::Exists() const
{
    boost::filesystem::file_status status = boost::filesystem::status( *m_path );

    return boost::filesystem::is_directory( status )
        && boost::filesystem::exists( status );
}


Path DirectoryInfo::GetPath() const
{
    return Path( m_path );
}


//
// File / Directory Iteration
//

template< typename Value, typename Iterator >
std::vector< Value > DirectoryInfo::Traverse( Bool wantsFileNotDir ) const
{
    Iterator iter( *m_path );
    Iterator end;

    std::vector< Value > values;

    for ( ; iter != end; ++ iter )
    {
        const boost::filesystem::directory_entry entry = *iter;
        const boost::filesystem::file_status status = entry.status();

        const Bool accepts = wantsFileNotDir
                           ? boost::filesystem::is_regular_file( status )
                           : boost::filesystem::is_directory( status );

        if ( accepts )
        {
            values.push_back( Value( std::make_shared< PathImpl >( entry.path() ) ));
        }
    }

    return values;
}


std::vector< DirectoryInfo > DirectoryInfo::GetDirectories() const
{
    return Traverse<
        DirectoryInfo, boost::filesystem::directory_iterator >( false );
}


std::vector< DirectoryInfo > DirectoryInfo::GetDirectoriesRecursively() const
{
    return Traverse<
        DirectoryInfo, boost::filesystem::recursive_directory_iterator >( false );
}


std::vector< FileInfo > DirectoryInfo::GetFiles() const
{
    return Traverse<
        FileInfo, boost::filesystem::directory_iterator >( true );
}


std::vector< FileInfo > DirectoryInfo::GetFilesRecursively() const
{
    return Traverse<
        FileInfo, boost::filesystem::recursive_directory_iterator >( true );
}


//
// Operations
//

void DirectoryInfo::Create()
{
    // Do nothing if the directory already exists.
    if ( this->Exists() ) { return; }

    const Bool ok = boost::filesystem::create_directory( *m_path );
    if ( ! ok )
    {
        CARAMEL_THROW( "Create directory \"{0}\" failed", m_path->ToString() );
    }
}


void DirectoryInfo::CopyAllTo( const Path& goalPath ) const
{
	const std::string sourceRoot = m_path->ToString();
	const std::string goalRoot = goalPath.ToString();

	const auto directoryInfos = this->GetDirectoriesRecursively();
	const auto fileInfos = this->GetFilesRecursively();

	// Copy all directory
	for ( const auto& directoryInfo : directoryInfos )
	{
		std::string directoryString( directoryInfo.GetPath().ToString() );
		directoryString.replace( directoryString.find( sourceRoot ), sourceRoot.size(), goalRoot );
		directoryInfo.CopyTo( Path( directoryString ) );
	}

	// Copy all file
	for ( const auto& fileInfo : fileInfos )
	{
		std::string fileString( fileInfo.GetPath().ToString() );
		fileString.replace( fileString.find( sourceRoot ), sourceRoot.size(), goalRoot );
		fileInfo.CopyTo( Path( fileString ) );
	}
}


void DirectoryInfo::CopyTo( const Path& goalPath ) const
{
	boost::system::error_code errorCode;
    boost::filesystem::copy( *m_path, *goalPath.m_impl, errorCode );
    if ( errorCode != 0 )
    {
		CARAMEL_THROW( "Copy directory from \"{0}\" to \"{1}\" failed, error code: {2}",
                       m_path->ToString(), goalPath.ToString(), errorCode.value() );
    }
}


void DirectoryInfo::Rename( const Path& goalPath )
{
	boost::system::error_code errorCode;
    boost::filesystem::rename( *m_path, *goalPath.m_impl, errorCode );
    if ( errorCode != 0 )
    {
		CARAMEL_THROW( "Rename directory from \"{0}\" to \"{1}\" failed, error code: {2}",
                       m_path->ToString(), goalPath.ToString(), errorCode.value() );
    }
}


void DirectoryInfo::Delete()
{
    const Bool ok = boost::filesystem::remove( *m_path );
    if ( ! ok )
    {
        CARAMEL_THROW( "Delete directory \"{0}\" failed", m_path->ToString() );
    }
}


void DirectoryInfo::DeleteAll()
{
    const auto removes = boost::filesystem::remove_all( *m_path );
    if ( removes == 0 )
    {
        CARAMEL_THROW( "Delete directory \"{0}\" failed", m_path->ToString() );
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// File Info
//

FileInfo::FileInfo( const Path& path )
    : m_path( path.m_impl )
{
}


FileInfo::FileInfo( std::shared_ptr< PathImpl > path )
    : m_path( path )
{
}


//
// Properties
//

Bool FileInfo::Exists() const
{
    boost::filesystem::file_status status = boost::filesystem::status( *m_path );

    return boost::filesystem::is_regular_file( status )
        && boost::filesystem::exists( status );
}


Uint32 FileInfo::Size() const
{
    const Uint64 size = this->Size64();
    if ( size > UINT32_MAX )
    {
        CARAMEL_THROW( "File \"{0}\" size \"{1}\" is out of 32-bit", *m_path, size );
    }
    return static_cast< Uint32 >( size );
}


Uint64 FileInfo::Size64() const
{
    static_assert( sizeof( boost::filesystem::file_size( *m_path )) == 8,
                   "file_size() should return in 64-bit" );

    return boost::filesystem::file_size( *m_path );
}


Path FileInfo::GetPath() const
{
    return Path( m_path );
}


//
// Operations
//

void FileInfo::CopyTo( const Path& goalPath ) const
{
	boost::system::error_code errorCode;
    boost::filesystem::copy_file( *m_path, *goalPath.m_impl, errorCode );
    if ( errorCode != 0 )
    {
		CARAMEL_THROW( "Copy file from \"{0}\" to \"{1}\" failed, error code: {2}",
                       m_path->ToString(), goalPath.ToString(), errorCode.value() );
    }
}


void FileInfo::Delete() 
{
	const Bool ok = boost::filesystem::remove( *m_path );
    if ( ! ok )
    {
        CARAMEL_THROW( "Delete file \"{0}\" failed", m_path->ToString() );
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Path
//

Path::Path()
    : m_impl( new PathImpl( boost::filesystem::path() ))
{
}


Path::Path( std::shared_ptr< PathImpl > impl )
    : m_impl( impl )
{
}


Path::Path( const Utf8String& path )
    : m_impl( new PathImpl( path ))
{
}


//
// Construct from UTF-8 encoded path.
// - ASCII encoded path is fine.
// - NOTES: In Windows, a std::string may be encoded in ACP (acitve code page),
//          and would cause an exception in these functions.
//          Use Utf8String or Windows::WideString to convert the path to Unicode.
//

Path::Path( const std::string& path )
{
    this->Init( path );
}


Path::Path( const Char* path )
{
    this->Init( path );
}


void Path::Init( const std::string& path )
{
    CARAMEL_CHECK_UTF8_ARGUMENT( u8Path, path );

    m_impl.reset( new PathImpl( u8Path ));
}


#if defined( CARAMEL_SYSTEM_IS_WINDOWS )

//
// Constructors from wide string
// - Windows specific
//

Path::Path( const std::wstring& wpath )
    : m_impl( new PathImpl( boost::filesystem::path( wpath )))
{
}


Path::Path( const Wchar* wpath )
    : m_impl( new PathImpl( boost::filesystem::path( wpath )))
{
}


//
// Conversion to wide string
// - Windows specific
//

std::wstring Path::ToWstring() const
{
    return m_impl->wstring();
}


#endif // CARAMEL_SYSTEM_IS_WINDOWS


//
// Splits
//

Path Path::Directory() const { return Path( std::make_shared< PathImpl >( m_impl->parent_path() )); }
Path Path::Filename()  const { return Path( std::make_shared< PathImpl >( m_impl->filename() )); }
Path Path::Stem()      const { return Path( std::make_shared< PathImpl >( m_impl->stem() )); }
Path Path::Extension() const { return Path( std::make_shared< PathImpl >( m_impl->extension() )); }


//
// Predicates
//

Bool Path::HasExtension() const { return m_impl->has_extension(); }
Bool Path::IsAbsolute()   const { return m_impl->is_absolute(); }


//
// Comparisons
//

Bool Path::operator==( const Path& rhs ) const { return *m_impl == *rhs.m_impl; }
Bool Path::operator< ( const Path& rhs ) const { return *m_impl <  *rhs.m_impl; }


//
// Combine
//

void Path::Combine( const Path& subpath )
{
    PathPtr temp = m_impl;
    m_impl.reset( new PathImpl( *temp / *subpath.m_impl ));
}


Path& Path::operator/=( const Path& subpath )
{
    this->Combine( subpath );
    return *this;
}


//
// Manipulators
//

void Path::AppendExtension( const std::string& extension )
{
    if ( extension.empty() ) { return; }

    const std::string path = this->ToString();

    const std::string result = ( '.' == extension[0] )
                             ? path + extension
                             : path + '.' + extension;

    m_impl.reset( new PathImpl( Utf8String( result )));
}


Path& Path::operator%=( const std::string& extension )
{
    this->AppendExtension( extension );
    return *this;
}


void Path::InsertStemSuffix( const std::string& suffix )
{
    if ( suffix.empty() ) { return; }

    const Path dir = this->Directory();
    const Path ext = this->Extension();

    const std::string newStem = this->Stem().ToString() + suffix;

    Path result = dir / Path( newStem );
    result.AppendExtension( ext.ToString() );

    *this = result;
}


//
// Conversions
//

Utf8String Path::ToUtf8String() const { return m_impl->ToUtf8String(); }

Path::operator std::string() const { return m_impl->ToString(); }
std::string Path::ToString() const { return m_impl->ToString(); }


//
// Implementation
//

PathImpl::PathImpl( const boost::filesystem::path& path )
    : boost::filesystem::path( path )
{
}


PathImpl::PathImpl( boost::filesystem::path&& path )
    : boost::filesystem::path( path )
{
}


PathImpl::PathImpl( const Utf8String& path )
    #if defined( CARAMEL_SYSTEM_IS_WINDOWS )
    : boost::filesystem::path( path.ToWstring() )
    #else
    : boost::filesystem::path( path.ToString() )
    #endif
{
}


Utf8String PathImpl::ToUtf8String() const
{
    return Utf8String( this->native() );
}


std::string PathImpl::ToString() const
{
    return this->ToUtf8String().ToString();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
