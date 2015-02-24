// Caramel C++ Library - String Facility - Implementation

#include "CaramelPch.h"

#include "String/Converters.h"
#include "String/FormatterImpl.h"
#include "String/NumberFormat.h"
#include <Caramel/Functional/ScopeExit.h>
#include <Caramel/Lexical/Integer.h>
#include <Caramel/String/Algorithm.h>
#include <Caramel/String/Format.h>
#include <Caramel/String/Split.h>
#include <Caramel/String/ToString.h>
#include <Caramel/String/Utf8String.h>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/range/irange.hpp>
#include <cstdarg>
#include <cstdio>
#include <iomanip>
#include <sstream>

#if defined( CARAMEL_SYSTEM_IS_WINDOWS )
#include <Caramel/Windows/WideString.h>
#include <codecvt>
#endif


namespace Caramel
{

//
// Contents
//
//   Utf8String
//   Algorithm
//   NumberFormat
//   IntegerConverter
//   FloatingConverter
//   ToString
//   ToStringT
//   Formatter
//

///////////////////////////////////////////////////////////////////////////////
//
// UTF-8 String
//

Utf8String::Utf8String()
{
}


Utf8String::Utf8String( Char c )
{
    if ( 0x7f < static_cast< Uint8 >( c ))
    {
        CARAMEL_THROW( "Input c is not valid UTF-8 character" );
    }

    m_s.assign( 1, c );
}


Utf8String::Utf8String( const std::string& u8Text )
{
    if ( !this->TryParse( u8Text ))
    {
        CARAMEL_THROW( "Input text is not UTF-8 encoded" );
    }
}


//
// Validation
//

inline static Int Utf8String_CalculateNumTrails( Byte lead )
{
    if ( 0 == ( lead & 0x80 ))  //  0dddddddd
    {
        return 0;
    }
    else if ( 0xC0 == ( lead & 0xE0 ))  // 110ddddd
    {
        return 1;
    }
    else if ( 0xE0 == ( lead & 0xF0 ))  // 1110dddd
    {
        return 2;
    }
    else if ( 0xF0 == ( lead & 0xF8 ))  // 11110ddd
    {
        return 3;
    }
    else
        return -1;
}


inline static Bool Utf8String_IsTrail( Byte b )
{
    return ( 0x80 == ( b & 0xC0 ));  // 10dddddd
}


Bool Utf8String::Validate( const std::string& u8Text )
{
    std::size_t pos = 0;

    while ( u8Text.length() > pos )
    {
        Int num = Utf8String_CalculateNumTrails( static_cast< Byte >( u8Text[ pos ++ ] ));
        
        // not valid leading character
        if ( num < 0 ) { return false; }
        
        // not enough length
        if ( u8Text.length() < pos + num ) { return false; }

        while (( num -- ) > 0 )
        {
            // not trailing character
            if ( ! Utf8String_IsTrail( static_cast< Byte >( u8Text[ pos ++ ] ))) { return false; }
        }
    }

    return true;
}


//
// Conversions
//

Bool Utf8String::TryParse( const std::string& u8Text )
{
    const Bool u8Encoded = Validate( u8Text );
    if ( u8Encoded )
    {
        m_s.assign( u8Text );
    }
    return u8Encoded;
}


Bool Utf8String::TryParse( const Byte* data, Uint length )
{
    CARAMEL_NOT_IMPLEMENTED();
}


//
// Conversion between UTF-8 and other Multi-bytes encoding.
//

Bool Utf8String::TryParse( const std::string& text, TextEncoding encoding )
{
    #if defined( CARAMEL_SYSTEM_IS_WINDOWS )
    {
        Windows::WideString wbuffer;

        if ( ! wbuffer.TryParse( text, encoding ))
        {
            return false;
        }

        m_s.assign( wbuffer.ToNarrow( TEXT_ENCODING_UTF8 ));
        return true;
    }
    #else
    {
        CARAMEL_NOT_IMPLEMENTED();   
    }
    #endif
}


//
// Conversion between UTF-8 and UTF-16 LE, Windows specific
//

#if defined( CARAMEL_SYSTEM_IS_WINDOWS )

Utf8String::Utf8String( const std::wstring& wText )
{
    std::wstring_convert< std::codecvt_utf8_utf16< Wchar > > converter;
    m_s.assign( converter.to_bytes( wText ));
}


std::wstring Utf8String::ToWstring() const
{
    std::wstring_convert< std::codecvt_utf8_utf16< Wchar > > converter;
    return converter.from_bytes( static_cast< const std::string& >( m_s ));
}

#endif // CARAMEL_SYSTEM_IS_WINDOWS


//
// Operators
//

Utf8String& Utf8String::operator+=( const Utf8String& rhs )
{
    m_s += rhs.m_s;
    return *this;
}


///////////////////////////////////////////////////////////////////////////////
//
// String Algorithm
//

inline boost::integer_range< Char > CharRange( Char c )
{
    return boost::irange( c, static_cast< Char >( c + 1 ));
}


//
// Predicates
//

Bool Contains( const std::string& input, Char c )
{
    return boost::algorithm::contains( input, CharRange( c ));
}


Bool StartsWith( const std::string& input, Char c )
{
    return boost::algorithm::starts_with( input, CharRange( c ));
}


Bool EndsWith( const std::string& input, Char c )
{
    return boost::algorithm::ends_with( input, CharRange( c ));
}


Bool StartsWith( const std::string& input, const std::string& test )
{
    return boost::algorithm::starts_with( input, test );
}


Bool EndsWith( const std::string& input, const std::string& test )
{
    return boost::algorithm::ends_with( input, test );
}


Bool CainStartsWith( const std::string& input, Char c )
{
    return boost::algorithm::istarts_with( input, CharRange( c ));
}


Bool CainEndsWith( const std::string& input, Char c )
{
    return boost::algorithm::iends_with( input, CharRange( c ));
}


Bool CainStartsWith( const std::string& input, const std::string& test )
{
    return boost::algorithm::istarts_with( input, test );
}


Bool CainEndsWith( const std::string& input, const std::string& test )
{
    return boost::algorithm::iends_with( input, test );
}


Bool CainEquals( const std::string& input, const std::string& test )
{
    return boost::algorithm::iequals( input, test );
}


//
// Extractors
//

std::string BeforeFirst( const std::string& s, Char c )
{
    auto range = boost::algorithm::find_first( s, CharRange( c ));
    return std::string( s.begin(), range.begin() );
}


std::string AfterFirst( const std::string& s, Char c )
{
    auto range = boost::algorithm::find_first( s, CharRange( c ));
    return range.empty() ? std::string()
                         : std::string( range.begin() + 1, s.end() );
}


//
// Manipulators
//

void Trim( std::string& s )
{
    boost::algorithm::trim( s );
}


std::string TrimCopy( const std::string& s )
{
    return boost::algorithm::trim_copy( s );
}


//
// Concatenation
//

std::string Join( const std::vector< std::string >& sequence, const std::string& separator )
{
    return boost::algorithm::join( sequence, separator );
}


///////////////////////////////////////////////////////////////////////////////
//
// Number Format
//

NumberFormat::NumberFormat( const std::string& format )
{
    if ( format.empty() ) { return; }

    m_specifier = format[0];

    if ( format.length() == 1 ) { return; }

    /// Extract Precision ///

    const std::string sprec = format.substr( 1 );
    Lexical::Integer< Uint > iprec;
    if ( iprec.TryParse( sprec ))
    {
        m_precision = iprec;
        m_hasPrecision = true;
    }
    else
    {
        // Parse precision failed, clear m_specifier to invalidate the format.
        m_specifier = '\0';
    }
}


Uint NumberFormat::Precision( Uint defaultPrecision ) const
{
    return m_hasPrecision ? m_precision : defaultPrecision;
}


///////////////////////////////////////////////////////////////////////////////
//
// Converter Common Strings
//

static std::string SeparateIntegralString( const std::string& integral )
{
    // Separate the string with thousands separator.
    // i.e. insert a ',' for every 3 digits from decimal point.

    std::stringstream ss;

    for ( std::size_t i = 0; i < integral.length(); ++ i )
    {
        ss << integral[i];

        if ( integral[i] == '-' ) { continue; }  // Prevent "-,123.0"

        const auto nth = ( integral.length() - i );  // the nth digit from decimal point.
        if ( nth > 3 && ( nth % 3 == 1 ))
        {
            ss << ',';
        }
    }

    return ss.str();
}


///////////////////////////////////////////////////////////////////////////////
//
// Integer Converter
//

template< typename T >
std::string IntegerConverter< T >::ToString() const
{
    std::stringstream ss;
    ss << std::dec << m_value;
    return ss.str();
}


template<>
std::string IntegerConverter< Int8 >::ToString() const
{
    std::stringstream ss;
    ss << std::dec << static_cast< Int >( m_value );
    return ss.str();
}


template<>
std::string IntegerConverter< Uint8 >::ToString() const
{
    std::stringstream ss;
    ss << std::dec << static_cast< Uint >( m_value );
    return ss.str();
}


template< typename T >
std::string IntegerConverter< T >::ToStringWithPadding( Uint digits ) const
{
    const auto svalue = this->ToString();
    
    if ( StartsWith( svalue, '-' ))
    {
        // Negative
        if ( digits >= svalue.length() - 1 )
        {
            return std::string( "-" )
                 + std::string( digits - svalue.length() + 1, '0' )
                 + svalue.substr( 1 );
        }
    }
    else
    {
        // Positive
        if ( digits >= svalue.length() )
        {
            return std::string( digits - svalue.length(), '0' ) + svalue; 
        }
    }

    return svalue;
}


template< typename T >
std::string IntegerConverter< T >::ToStringWithFixedPoint( Uint digits ) const
{
    if ( digits == 0 ) { return this->ToString(); }

    return this->ToString() + "." + std::string( digits, '0' );
}


template< typename T >
std::string IntegerConverter< T >::ToStringWithGroup( Uint digits ) const
{
    const std::string fixed = this->ToStringWithFixedPoint( digits );
    
    if ( digits == 0 )
    {
        return SeparateIntegralString( fixed );
    }
    else
    {
        const SplitterFirst spliter( fixed, '.' );
        return SeparateIntegralString( spliter.before ) + '.' + spliter.after;
    }
}


template< typename T >
std::string IntegerConverter< T >::ToStringHexadecimalRaw( Bool useUppercase ) const
{
    std::stringstream ss;
    ss << std::hex << ( useUppercase ? std::uppercase : std::nouppercase )
       << m_value;
    return ss.str();    
}


template<>
std::string IntegerConverter< Int8 >::ToStringHexadecimalRaw( Bool useUppercase ) const
{
    std::stringstream ss;
    ss << std::hex << ( useUppercase ? std::uppercase : std::nouppercase )
       << static_cast< Int >( m_value );
    const auto result = ss.str();
    if ( result.length() < 2 )
    {
        return result;
    }
    else
        return result.substr( result.length() - 2 );
}


template<>
std::string IntegerConverter< Uint8 >::ToStringHexadecimalRaw( Bool useUppercase ) const
{
    std::stringstream ss;
    ss << std::hex << ( useUppercase ? std::uppercase : std::nouppercase )
       << static_cast< Uint >( m_value );
    const auto result = ss.str();
    if ( result.length() < 2 )
    {
        return result;
    }
    else
        return result.substr( result.length() - 2 );
}


template< typename T >
std::string IntegerConverter< T >::ToStringHexadecimal( Uint digits, Bool useUppercase ) const
{
    const std::string hexValue = this->ToStringHexadecimalRaw( useUppercase );
    if ( digits > hexValue.length() )
    {
        return std::string( digits - hexValue.length(), '0' ) + hexValue;
    }
    else
    {
        return hexValue;
    }
}


template< typename T >
std::string IntegerConverter< T >::operator() ( const std::string& format ) const
{
    if ( format.empty() ) { return this->ToString(); }

    const NumberFormat numFmt( format );

    switch ( numFmt.Specifier() )
    {
    case 'D': case 'd':
        return this->ToStringWithPadding( numFmt.Precision( 1 ));

    case 'F': case 'f':
        return this->ToStringWithFixedPoint( numFmt.Precision( 2 ));

    case 'N': case 'n':
        return this->ToStringWithGroup( numFmt.Precision( 2 ));

    case 'X':
        return this->ToStringHexadecimal( numFmt.Precision( 1 ), true );
        break;

    case 'x':
        return this->ToStringHexadecimal( numFmt.Precision( 1 ), false );
        break;

    default:
        CARAMEL_ALERT( "Invalid integer format: \"{0}\"", format );
        return this->ToString();
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Floating Converter
//

template< typename T >
std::string FloatingConverter< T >::ToString() const
{
    std::stringstream ss;
    ss << m_value;
    return ss.str();
}


template< typename T >
std::string FloatingConverter< T >::ToStringWithFixedPoint( Uint digits ) const
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision( digits ) << m_value;
    const auto result = ss.str();

    if ( StartsWith( result, '-' ))
    {
        // Special case: Zero does not output with sing - according to .NET Format rule.

        // If all chars are '0' or '.' -> The output is a zero.
        if ( result.find_first_not_of( "0.", 1 ) > result.length() )
        {
            return result.substr( 1 );  // Remove the leading '-'
        }
    }

    return ss.str();
}


template< typename T >
std::string FloatingConverter< T >::ToStringWithGroup( Uint digits ) const
{
    const std::string fixed = this->ToStringWithFixedPoint( digits );
    
    if ( digits == 0 )
    {
        return SeparateIntegralString( fixed );
    }
    else
    {
        const SplitterFirst spliter( fixed, '.' );
        return SeparateIntegralString( spliter.before ) + '.' + spliter.after;
    }
}


template< typename T >
std::string FloatingConverter< T >::operator() ( const std::string& format ) const
{
    if ( format.empty() ) { return this->ToString(); }

    const NumberFormat numFmt( format );

    switch ( numFmt.Specifier() )
    {
    case 'F': case 'f':
        return this->ToStringWithFixedPoint( numFmt.Precision( 2 ));

    case 'N': case 'n':
        return this->ToStringWithGroup( numFmt.Precision( 2 ));

    default:
        CARAMEL_ALERT( "Invalid floating format: \"{0}\"", format );
        return this->ToString();
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// ToString
//

std::string ToString( Bool x )
{
    return x ? "true" : "false";
}


//
// Integers
//

std::string ToString( Int16 x )  { return IntegerConverter< Int16 > ( x ).ToString(); }
std::string ToString( Uint16 x ) { return IntegerConverter< Uint16 >( x ).ToString(); }
std::string ToString( Int32 x )  { return IntegerConverter< Int32 > ( x ).ToString(); }
std::string ToString( Uint32 x ) { return IntegerConverter< Uint32 >( x ).ToString(); }
std::string ToString( Long x )   { return IntegerConverter< Long >  ( x ).ToString(); }
std::string ToString( Ulong x )  { return IntegerConverter< Ulong > ( x ).ToString(); }
std::string ToString( Int64 x )  { return IntegerConverter< Int64 > ( x ).ToString(); }
std::string ToString( Uint64 x ) { return IntegerConverter< Uint64 >( x ).ToString(); }


//
// Floatings
//

std::string ToString( Float  x ) { return FloatingConverter< Float > ( x ).ToString(); } 
std::string ToString( Double x ) { return FloatingConverter< Double >( x ).ToString(); }


///////////////////////////////////////////////////////////////////////////////
//
// ToString with Format
//

std::string ToString( Int16 x,  const std::string& format ) { return IntegerConverter< Int16 > ( x )( format ); }
std::string ToString( Uint16 x, const std::string& format ) { return IntegerConverter< Uint16 >( x )( format ); }
std::string ToString( Int32 x,  const std::string& format ) { return IntegerConverter< Int32 > ( x )( format ); }
std::string ToString( Uint32 x, const std::string& format ) { return IntegerConverter< Uint32 >( x )( format ); }
std::string ToString( Long x,   const std::string& format ) { return IntegerConverter< Long >  ( x )( format ); }
std::string ToString( Ulong x,  const std::string& format ) { return IntegerConverter< Ulong > ( x )( format ); }
std::string ToString( Int64 x,  const std::string& format ) { return IntegerConverter< Int64 > ( x )( format ); }
std::string ToString( Uint64 x, const std::string& format ) { return IntegerConverter< Uint64 >( x )( format ); }

std::string ToString( Float  x, const std::string& format ) { return FloatingConverter< Float > ( x )( format ); } 
std::string ToString( Double x, const std::string& format ) { return FloatingConverter< Double >( x )( format ); }


///////////////////////////////////////////////////////////////////////////////
//
// To String <Type>
//

template<> std::string ToStringT< Bool >()   { return "Bool"; }
template<> std::string ToStringT< Char >()   { return "Char"; }
template<> std::string ToStringT< Byte >()   { return "Byte"; }
template<> std::string ToStringT< Int16 >()  { return "Int16"; }
template<> std::string ToStringT< Uint16 >() { return "Uint16"; }
template<> std::string ToStringT< Int32 >()  { return "Int32"; }
template<> std::string ToStringT< Uint32 >() { return "Uint32"; }
template<> std::string ToStringT< Long >()   { return "Long"; }
template<> std::string ToStringT< Ulong >()  { return "Ulong"; }
template<> std::string ToStringT< Int64 >()  { return "Int64"; }
template<> std::string ToStringT< Uint64 >() { return "Uint64"; }

template<> std::string ToStringT< Float >()  { return "Float"; }
template<> std::string ToStringT< Double >() { return "Double"; }


///////////////////////////////////////////////////////////////////////////////
//
// Formatter
//

namespace Detail
{

Formatter::Formatter( const std::string& format )   
    : m_impl( new Formatter::Impl( format ))
{}


std::string Formatter::GetString() const
{
    return m_impl->GetString();
}


//
// Feeding Arguments
//

void Formatter::Feed( Int8 value )
{
    m_impl->Distribute( IntegerConverter< Int8 >( value ));
}


void Formatter::Feed( Uint8 value )
{
    m_impl->Distribute( IntegerConverter< Uint8 >( value ));
}


void Formatter::Feed( Int16 value )
{
    m_impl->Distribute( IntegerConverter< Int16 >( value ));
}


void Formatter::Feed( Uint16 value )
{
    m_impl->Distribute( IntegerConverter< Uint16 >( value ));
}


void Formatter::Feed( Int value )
{
    m_impl->Distribute( IntegerConverter< Int >( value ));
}


void Formatter::Feed( Uint value )
{
    m_impl->Distribute( IntegerConverter< Uint >( value ));
}


void Formatter::Feed( Int64 value )
{
    m_impl->Distribute( IntegerConverter< Int64 >( value ));
}


void Formatter::Feed( Uint64 value )
{
    m_impl->Distribute( IntegerConverter< Uint64 >( value ));
}


void Formatter::Feed( Long value )
{
    m_impl->Distribute( IntegerConverter< Long >( value ));
}


void Formatter::Feed( Ulong value )
{
    m_impl->Distribute( IntegerConverter< Ulong >( value ));
}


void Formatter::Feed( Float value )
{
    m_impl->Distribute( FloatingConverter< Float >( value ));
}


void Formatter::Feed( Double value )
{
    m_impl->Distribute( FloatingConverter< Double >( value ));
}


void Formatter::Feed( Bool value )
{
    m_impl->Distribute( [=] ( const std::string& ) { return ToString( value ); });
}


void Formatter::Feed( const std::string& value )
{
    m_impl->Distribute( [=] ( const std::string& ) { return value; });
}


//
// Implementation
//

Formatter::Impl::Impl( const std::string& format )
{
    std::string buffer = format;
    std::string head = "";

    while ( Contains( buffer, '}' ))
    {
        const std::string piece = BeforeFirst( buffer, '}' );
        buffer = AfterFirst( buffer, '}' );

        if ( ! Contains( piece, '{' ))
        {
            head += piece + "}";
            continue;
        }
        
        head += BeforeFirst( piece, '{' );

        const std::string inBrace = AfterFirst( piece, '{' );
        const std::string sindex = BeforeFirst( inBrace, ':' );

        Lexical::Integer< Uint > index;
        
        if ( ! index.TryParse( sindex ))
        {
            continue;
        }

        FormatItem item;
        item.argIndex = index;
        item.format = AfterFirst( inBrace, ':' );

        item.head = head;
        head.clear();
        
        m_items.push_back( item );
    }

    if ( m_items.empty() )
    {
        m_tail = format;
    }
    else
    {
        m_tail = buffer;
    }
}


void Formatter::Impl::Distribute(
    std::function< std::string ( const std::string& ) > formatResolver )
{
    const Uint index = m_feedingIndex ++;

    for ( auto& item : m_items )
    {
        if ( index != item.argIndex ) { continue; }

        item.content = formatResolver( item.format );
    }
}


std::string Formatter::Impl::GetString() const
{
    std::ostringstream stream;

    for ( const auto& item : m_items )
    {
        stream << item.head << item.content;
    }

    stream << m_tail;

    return stream.str();
}


} // namespace Detail

///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
