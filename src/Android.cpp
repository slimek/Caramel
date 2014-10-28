// Caramel C++ Library - Android Facility - Implementation

#include "CaramelPch.h"


#if defined( CARAMEL_SYSTEM_IS_ANDROID )

#include <Caramel/Android/LogTraceAdapter.h>
#include <Caramel/Android/Streambuf.h>
#include <android/log.h>
#include <cstring>


namespace Caramel
{

namespace Android
{

//
// Contents
//
//   LogTraceAdapter
//   Streambuf
//

///////////////////////////////////////////////////////////////////////////////
//
// Log Trace Adapter
//

LogTraceAdapter::LogTraceAdapter( const std::string& tagName )
    : m_tagName( tagName )
{
}


void LogTraceAdapter::Write( Trace::Level level, const std::string& message )
{
    CARAMEL_ASSERT( Trace::ExistsBuiltinChannel( level ));

    const auto priority = static_cast< android_LogPriority >( static_cast< Int >( level ) + 1 );

    __android_log_write( priority, m_tagName.c_str(), message.c_str() );
}


///////////////////////////////////////////////////////////////////////////////
//
// Streambuf
//

Streambuf::Streambuf( std::string name )
    : m_name( std::move( name ))
{
	this->setp( &m_buffer[0], &m_buffer[ BUFFER_SIZE - 1 ] );
}


Int Streambuf::overflow( Int c )
{
	if ( c == traits_type::eof() )
	{
		*this->pptr() = traits_type::to_char_type( c );
		this->sbumpc();
	}

	return this->sync() ? traits_type::eof() : traits_type::not_eof( c );
}


Int Streambuf::sync()
{
	Int rc = 0;
	if ( this->pbase() != this->pptr() )
	{
		Char writebuf[ BUFFER_SIZE + 1 ];
		std::memcpy( writebuf, this->pbase(), this->pptr() - this->pbase() );
		writebuf[ this->pptr() - this->pbase() ] = '\0';

		rc = __android_log_write( ANDROID_LOG_INFO, m_name.c_str(), writebuf ) > 0;
		this->setp( &m_buffer[0], &m_buffer[ BUFFER_SIZE - 1 ] );
	}

	return rc;
}


///////////////////////////////////////////////////////////////////////////////
//
// Validation
//

#define STATIC_ASSERT_LOG_TRACE_LEVEL( name ) \
    static_assert( ANDROID_LOG_ ## name == static_cast< Int >( Trace::LEVEL_ ## name + 1 ), "Log level " # name )

STATIC_ASSERT_LOG_TRACE_LEVEL( DEBUG );
STATIC_ASSERT_LOG_TRACE_LEVEL( INFO );
STATIC_ASSERT_LOG_TRACE_LEVEL( WARN );
STATIC_ASSERT_LOG_TRACE_LEVEL( ERROR );


///////////////////////////////////////////////////////////////////////////////

} // namespace Android

} // namespace Caramel

#endif // CARAMEL_SYSTEM_IS_ANDROID
