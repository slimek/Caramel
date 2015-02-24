// Caramel C++ Library - Value Facility - Implementation

#include "CaramelPch.h"

#include "Value/NamedValuesImpl.h"
#include "Value/ScalarImpl.h"
#include <Caramel/Lexical/Boolean.h>
#include <Caramel/Lexical/Floating.h>
#include <Caramel/Lexical/Integer.h>
#include <Caramel/Numeric/NumberConverter.h>
#include <Caramel/Numeric/NumberTraits.h>
#include <Caramel/String/ToString.h>
#include <Caramel/Value/Any.h>
#include <Caramel/Value/Scalar.h>
#include <Caramel/Value/Usize.h>
#include <limits>


namespace Caramel
{

//
// Contents
//
//   AnyInteger
//   AnyFloating
//   AnyEnum
//   AnyString
//   NamedValues
//   ConstNamedValueRef
//   NamedValueRef
//   NamedValueEntry
//   NamedValueFeed
//   Scalar
//   Usize
//

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Boolean
//

AnyBoolean::AnyBoolean( Bool value )
    : m_value( value )
{
}


///////////////////////////////////////////////////////////////////////////////
//
// Any Integer
//

AnyInteger::AnyInteger( Int value )
    : m_isUint64( false )
    , m_value( value )
{
}


AnyInteger::AnyInteger( Uint value )
    : m_isUint64( false )
    , m_value( value )
{
}


AnyInteger::AnyInteger( Int64 value )
    : m_isUint64( false )
    , m_value( value )
{
}


AnyInteger::AnyInteger( Uint64 value )
    : m_isUint64( true )
    , m_value( value )
{
}


//
// Retrieve Value
// - We allow conversion only when it doesn't lose precision,
//   i.e. conversion of "exactly".
//

template< typename T, typename U >
void AnyInteger_Get( T& value, U intValue )
{
    if ( ! NumberConverter< T, U >::CanExactConvert( intValue ))
    {
        CARAMEL_THROW( "Can't exactly convert {0} to {1}, value: {2}",
                       ToStringT< U >(), ToStringT< T >(), ToString( intValue ));
    }
    
    value = static_cast< T >( intValue );
}


template< typename T >
void AnyInteger::DoGet( T& value ) const
{
    m_isUint64 ? AnyInteger_Get( value, static_cast< Uint64 >( m_value ))
               : AnyInteger_Get( value, m_value );
}


void AnyInteger::Get( Int& value )    const { this->DoGet( value ); }
void AnyInteger::Get( Uint& value )   const { this->DoGet( value ); }
void AnyInteger::Get( Int64& value )  const { this->DoGet( value ); }
void AnyInteger::Get( Uint64& value ) const { this->DoGet( value ); }
void AnyInteger::Get( Float& value )  const { this->DoGet( value ); }
void AnyInteger::Get( Double& value ) const { this->DoGet( value ); }


///////////////////////////////////////////////////////////////////////////////
//
// Any Floating
//

AnyFloating::AnyFloating( Float value )
    : m_value( value )
{
}


AnyFloating::AnyFloating( Double value )
    : m_value( value )
{
}


//
// Retrieve Value
//

void AnyFloating::Get( Float& value ) const
{
    if ( ! NumberConverter< Float, Double >::CanExactConvert( m_value ))
    {
        CARAMEL_THROW( "Can't exactly convert Double to Float, value: {0}", m_value );
    }

    value = static_cast< Float >( m_value );
}


void AnyFloating::Get( Double& value ) const
{
    value = m_value;
}


///////////////////////////////////////////////////////////////////////////////
//
// Any Enum
//

template< typename T >
void AnyEnum_Get( T& value, Int64 enumValue )
{
    const T MAX_VALUE = std::numeric_limits< T >::max();
    const T MIN_VALUE = std::numeric_limits< T >::min();

    CARAMEL_CHECK( MIN_VALUE <= enumValue && enumValue <= MAX_VALUE );
    value = static_cast< T >( enumValue );
}


void AnyEnum::Get( Int& value ) const
{
    AnyEnum_Get( value, this->ToInt64() );
}


void AnyEnum::Get( Uint& value ) const
{
    AnyEnum_Get( value, this->ToInt64() );
}


void AnyEnum::Get( Int64& value ) const
{
    value = this->ToInt64();
}


void AnyEnum::Get( Uint64& value ) const
{
    const Int64 enumValue = this->ToInt64();
    CARAMEL_CHECK( 0 <= enumValue );
    value = static_cast< Uint64 >( enumValue );
}


///////////////////////////////////////////////////////////////////////////////
//
// Any String
//

AnyString::AnyString( const std::string& s )
    : m_value( s )
{
}


AnyString::AnyString( const Char* sz )
{
    CARAMEL_ASSERT( sz );

    m_value = sz;
}


} // namespace Detail

///////////////////////////////////////////////////////////////////////////////
//
// Named Values
//

NamedValues::NamedValues()
    : m_impl( new NamedValuesImpl )
{
}


NamedValues::NamedValues( const std::map< std::string, std::string >& pairs )
    : m_impl( new NamedValuesImpl )
{
    for ( const auto& pair : pairs )
    {
        this->operator[]( pair.first ) = pair.second;
    }
}


NamedValues::NamedValues( std::initializer_list< Detail::NamedValueFeed > inits )
    : m_impl( new NamedValuesImpl )
{
    for ( const auto& init : inits )
    {
        *( m_impl->InsertValue( init.Name() )) = *( init.Value() );
    }
}


void NamedValues::Init()
{
    m_impl.reset( new NamedValuesImpl );
}


//
// Properties
//

Bool NamedValues::IsEmpty() const
{
    return m_impl->m_values.empty();
}


Uint NamedValues::Size() const
{
    return static_cast< Uint >( m_impl->m_values.size() );
}


//
// Accessors
//

Bool NamedValues::HasValue( const std::string& name ) const
{
    return m_impl->m_values.find( name ) != m_impl->m_values.end();
}


Detail::NamedValueRef NamedValues::operator[]( const std::string& name )
{
    Scalar* value = nullptr;

    auto ivalue = m_impl->m_values.find( name );
    if ( m_impl->m_values.end() != ivalue )
    {
        value = &( ivalue->second );
    }

    return Detail::NamedValueRef( this, name, value );
}


Detail::ConstNamedValueRef NamedValues::operator[]( const std::string& name ) const
{
    auto ivalue = m_impl->m_values.find( name );
    if ( m_impl->m_values.end() == ivalue )
    {
        CARAMEL_THROW( "Value not found, name: \"{0}\"", name );
    }

    return Detail::ConstNamedValueRef( name, &( ivalue->second ));
}


NamedValues::ValueMap NamedValues::GetValueMap() const
{
    ValueMap vmap;

    for ( auto& nameValue : m_impl->m_values )
    {
        const std::string name = nameValue.first;
        
        Detail::ConstNamedValueRef valueRef( name, &( nameValue.second ));

        vmap.insert( std::make_pair( name, valueRef.AsString() ));
    }

    return vmap;
}


//
// Implementation
//

Scalar* NamedValuesImpl::InsertValue( const std::string& name )
{
    return &m_values[ name ];
}


namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Constant Named Value Reference
//

ConstNamedValueRef::ConstNamedValueRef( const std::string& name, Scalar* value )
    : m_name( name )
    , m_value( value )
{
}


//
// Accessors 
//

Bool ConstNamedValueRef::AsBool() const
{
    const auto value = m_value->AsBool();
    if ( ! value )
    {
        CARAMEL_THROW( "Can't convert \"{0}\" value to Bool", m_name );
    }
    return *value;
}


Int ConstNamedValueRef::AsInt() const
{
    const auto value = m_value->AsInt();
    if ( ! value )
    {
        CARAMEL_THROW( "Can't convert \"{0}\" value to Int", m_name );
    }
    return *value;
}


Uint ConstNamedValueRef::AsUint() const
{
    const auto value = m_value->AsUint();
    if ( ! value )
    {
        CARAMEL_THROW( "Can't convert \"{0}\" value to Uint", m_name );
    }
    return *value;
}


Int64 ConstNamedValueRef::AsInt64() const
{
    const auto value = m_value->AsInt64();
    if ( ! value )
    {
        CARAMEL_THROW( "Can't convert \"{0}\" value to Int64", m_name );
    }
    return *value;
}


Uint64 ConstNamedValueRef::AsUint64() const
{
    const auto value = m_value->AsUint64();
    if ( ! value )
    {
        CARAMEL_THROW( "Can't convert \"{0}\" value to Uint64", m_name );
    }
    return *value;
}


Float ConstNamedValueRef::AsFloat() const
{
    const auto value = m_value->AsFloat();
    if ( ! value )
    {
        CARAMEL_THROW( "Can't convert \"{0}\" value to Float", m_name );
    }
    return *value;
}


Double ConstNamedValueRef::AsDouble() const
{
    const auto value = m_value->AsDouble();
    if ( ! value )
    {
        CARAMEL_THROW( "Can't convert \"{0}\" value to Double", m_name );
    }
    return *value;
}


std::string ConstNamedValueRef::AsString() const
{
    return *( m_value->AsString() );
}


///////////////////////////////////////////////////////////////////////////////
//
// Name Value Reference
//

NamedValueRef::NamedValueRef( NamedValues* host, const std::string& name, Scalar* value )
    : ConstNamedValueRef( name, value )
    , m_host( host )
{
}


NamedValueRef& NamedValueRef::operator=( Bool value )
{
    this->PrepareEntry();
    *m_value = Scalar( value );
    return *this;
}


NamedValueRef& NamedValueRef::operator=( Int value )
{
    this->PrepareEntry();
    *m_value = Scalar( value );
    return *this;
}


NamedValueRef& NamedValueRef::operator=( Uint value )
{
    this->PrepareEntry();
    *m_value = Scalar( value );
    return *this;
}


NamedValueRef& NamedValueRef::operator=( Int64 value )
{
    this->PrepareEntry();
    *m_value = Scalar( value );
    return *this;
}


NamedValueRef& NamedValueRef::operator=( Uint64 value )
{
    this->PrepareEntry();
    *m_value = Scalar( value );
    return *this;
}


NamedValueRef& NamedValueRef::operator=( Long value )
{
    this->PrepareEntry();
    *m_value = Scalar( value );
    return *this;
}


NamedValueRef& NamedValueRef::operator=( Ulong value )
{
    this->PrepareEntry();
    *m_value = Scalar( value );
    return *this;
}


NamedValueRef& NamedValueRef::operator=( Double value )
{
    this->PrepareEntry();
    *m_value = Scalar( value );
    return *this;
}


NamedValueRef& NamedValueRef::operator=( const std::string& value )
{
    this->PrepareEntry();
    *m_value = Scalar( value );
    return *this;
}


NamedValueRef& NamedValueRef::operator=( const Char* value )
{
    if ( ! value )
    {
        CARAMEL_INVALID_ARGUMENT();
    }

    return this->operator=( std::string( value ));
}


NamedValueRef& NamedValueRef::operator=( const Scalar& value )
{
    this->PrepareEntry();
    *m_value = value;
    return *this;
}


void NamedValueRef::PrepareEntry()
{
    if ( ! m_value )
    {
        m_value = m_host->m_impl->InsertValue( m_name );
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Named Value Feed
//

NamedValueFeed::NamedValueFeed( std::string name, Bool v )
    : m_name( std::move( name ))
    , m_value( new Scalar( v ))
{}


NamedValueFeed::NamedValueFeed( std::string name, Int v )
    : m_name( std::move( name ))
    , m_value( new Scalar( v ))
{}


NamedValueFeed::NamedValueFeed( std::string name, Uint v )
    : m_name( std::move( name ))
    , m_value( new Scalar( v ))
{}


NamedValueFeed::NamedValueFeed( std::string name, Int64 v )
    : m_name( std::move( name ))
    , m_value( new Scalar( v ))
{}


NamedValueFeed::NamedValueFeed( std::string name, Uint64 v )
    : m_name( std::move( name ))
    , m_value( new Scalar( v ))
{}


NamedValueFeed::NamedValueFeed( std::string name, Long v )
    : m_name( std::move( name ))
    , m_value( new Scalar( v ))
{}


NamedValueFeed::NamedValueFeed( std::string name, Ulong v )
    : m_name( std::move( name ))
    , m_value( new Scalar( v ))
{}


NamedValueFeed::NamedValueFeed( std::string name, Double v )
    : m_name( std::move( name ))
    , m_value( new Scalar( v ))
{}


NamedValueFeed::NamedValueFeed( std::string name, const Char* v )
    : m_name( std::move( name ))
{
    if ( ! v )
    {
        CARAMEL_INVALID_ARGUMENT();
    }

    m_value.reset( new Scalar( v ));
}


NamedValueFeed::NamedValueFeed( std::string name, std::string v )
    : m_name( std::move( name ))
    , m_value( new Scalar( std::move( v )))
{}


} // namespace Detail


///////////////////////////////////////////////////////////////////////////////
//
// Scalar
//

Scalar::Scalar()
    : m_impl( new ScalarImpl )
{}


Scalar::Scalar( Bool v )
    : m_impl( new ScalarImpl(( v ? 1LL : 0LL ), SCALAR_BOOL ))
{}


Scalar::Scalar( Int v )
    : m_impl( new ScalarImpl( static_cast< Int64 >( v ), SCALAR_INT64 ))
{}


Scalar::Scalar( Uint v )
    : m_impl( new ScalarImpl( static_cast< Uint64 >( v ), SCALAR_UINT64 ))
{}


Scalar::Scalar( Int64 v )
    : m_impl( new ScalarImpl( v, SCALAR_INT64 ))
{}


Scalar::Scalar( Uint64 v )
    : m_impl( new ScalarImpl( v, SCALAR_UINT64 ))
{}


Scalar::Scalar( Long v )
    : m_impl( new ScalarImpl( static_cast< Int64 >( v ), SCALAR_INT64 ))
{}


Scalar::Scalar( Ulong v )
    : m_impl( new ScalarImpl( static_cast< Uint64 >( v ), SCALAR_UINT64 ))
{}


Scalar::Scalar( Double v )
    : m_impl( new ScalarImpl( v, SCALAR_DOUBLE ))
{}


Scalar::Scalar( const std::string& v )
    : m_impl( new ScalarImpl( v, SCALAR_STRING ))
{}


Scalar::Scalar( std::string&& v )
    : m_impl( new ScalarImpl( std::move( v ), SCALAR_STRING ))
{}


Scalar::Scalar( const Char* sz )
    : m_impl( new ScalarImpl( std::string( sz ), SCALAR_STRING ))
{}


//
// Get Values with exaclty conversion
//

boost::optional< Bool > Scalar::AsBool() const
{
    switch ( m_impl->GetType() )
    {
    case SCALAR_BOOL:
        return m_impl->GetBool();

    case SCALAR_INT64:
        return ( 0 != m_impl->GetInt64() );

    case SCALAR_UINT64:
        return ( 0 != m_impl->GetUint64() );

    case SCALAR_DOUBLE:
        return ( 0.0 != m_impl->GetDouble() );

    case SCALAR_STRING:
    {
        Lexical::Boolean lexBool;
        if ( lexBool.TryParse( m_impl->GetString() ))
        {
            return static_cast< Bool >( lexBool );  // Then can convert to boost::optional< Bool >
        }
        return boost::none;
    }

    case SCALAR_UNDEF:
        CARAMEL_THROW( "Value is undef" );

    default:
        CARAMEL_NOT_REACHED();
    }
}


boost::optional< Int > Scalar::AsInt() const
{
    Int value = 0;

    switch ( m_impl->GetType() )
    {
    case SCALAR_INT64:
    {
        if ( NumberConverter< Int, Int64 >::TryExactConvert( value, m_impl->GetInt64() ))
        {
            return value;
        }
        return boost::none;
    }

    case SCALAR_BOOL:
    {
        return m_impl->GetBool() ? 1 : 0;
    }

    case SCALAR_UINT64:
    {
        if ( NumberConverter< Int, Uint64 >::TryExactConvert( value, m_impl->GetUint64() ))
        {
            return value;
        }
        return boost::none;
    }

    case SCALAR_DOUBLE:
        return boost::none;

    case SCALAR_STRING:
    {
        Lexical::Integer< Int > lexInt;
        if ( lexInt.TryParse( m_impl->GetString() ))
        {
            return static_cast< Int >( lexInt );
        }
        return boost::none;
    }

    case SCALAR_UNDEF:
        CARAMEL_THROW( "Value is undef" );

    default:
        CARAMEL_NOT_REACHED();
    }
}


boost::optional< Uint > Scalar::AsUint() const
{
    Uint value = 0;

    switch ( m_impl->GetType() )
    {
    case SCALAR_UINT64:
    {
        if ( NumberConverter< Uint, Uint64 >::TryExactConvert( value, m_impl->GetUint64() ))
        {
            return value;
        }
        return boost::none;
    }

    case SCALAR_BOOL:
    {
        return m_impl->GetBool() ? 1 : 0;
    }

    case SCALAR_INT64:
    {
        if ( NumberConverter< Uint, Int64 >::TryExactConvert( value, m_impl->GetInt64() ))
        {
            return value;
        }
        return boost::none;
    }

    case SCALAR_DOUBLE:
        return boost::none;
    
    case SCALAR_STRING:
    {
        Lexical::Integer< Uint > lexUint;
        if ( lexUint.TryParse( m_impl->GetString() ))
        {
            return static_cast< Uint >( lexUint );
        }
        return boost::none;
    }

    case SCALAR_UNDEF:
        CARAMEL_THROW( "Value is undef" );

    default:
        CARAMEL_NOT_REACHED();
    }
}


boost::optional< Int64 > Scalar::AsInt64() const
{
    Int64 value = 0;

    switch ( m_impl->GetType() )
    {
    case SCALAR_INT64:
        return m_impl->GetInt64();

    case SCALAR_BOOL:
        return m_impl->GetBool() ? 1 : 0;

    case SCALAR_UINT64:
    {
        if ( NumberConverter< Int64, Uint64 >::TryExactConvert( value, m_impl->GetUint64() ))
        {
            return value;
        }
        return boost::none;
    }

    case SCALAR_DOUBLE:
        return boost::none;

    case SCALAR_STRING:
    {
        Lexical::Integer< Int64 > lexInt;
        if ( lexInt.TryParse( m_impl->GetString() ))
        {
            return static_cast< Int64 >( lexInt );
        }
        return boost::none;
    }

    default:
        CARAMEL_NOT_REACHED();
    }
}


boost::optional< Uint64 > Scalar::AsUint64() const
{
    Uint64 value = 0;

    switch ( m_impl->GetType() )
    {
    case SCALAR_UINT64:
        return m_impl->GetUint64();

    case SCALAR_BOOL:
        return m_impl->GetBool() ? 1 : 0;

    case SCALAR_INT64:
    {
        if ( NumberConverter< Uint64, Int64 >::TryExactConvert( value, m_impl->GetInt64() ))
        {
            return value;
        }
        return boost::none;
    }

    case SCALAR_DOUBLE:
        return boost::none;

    case SCALAR_STRING:
    {
        Lexical::Integer< Uint64 > lexUint;
        if ( lexUint.TryParse( m_impl->GetString() ))
        {
            return static_cast< Uint64 >( lexUint );
        }
        return boost::none;
    }

    default:
        CARAMEL_NOT_REACHED();
    }
}


boost::optional< Float > Scalar::AsFloat() const
{
    Float value = 0.0f;

    switch ( m_impl->GetType() )
    {
    case SCALAR_DOUBLE:
        return static_cast< Float >( m_impl->GetDouble() );

    case SCALAR_BOOL:
        return m_impl->GetBool() ? 1.0f : 0.0f;

    case SCALAR_INT64:
    {
        if ( NumberConverter< Float, Int64 >::TryExactConvert( value, m_impl->GetInt64() ))
        {
            return value;
        }
        return boost::none;
    }

    case SCALAR_UINT64:
    {
        if ( NumberConverter< Float, Uint64 >::TryExactConvert( value, m_impl->GetUint64() ))
        {
            return value;
        }
        return boost::none;
    }

    case SCALAR_STRING:
    {
        Lexical::Floating< Float > lexFloat;
        if ( lexFloat.TryParse( m_impl->GetString() ))
        {
            return static_cast< Float >( lexFloat );
        }
        return boost::none;
    }

    default:
        CARAMEL_NOT_REACHED();
    }
}


boost::optional< Double > Scalar::AsDouble() const
{
    Double value = 0.0;

    switch ( m_impl->GetType() )
    {
    case SCALAR_DOUBLE:
        return m_impl->GetDouble();

    case SCALAR_BOOL:
        return m_impl->GetBool() ? 1.0 : 0.0;

    case SCALAR_INT64:
    {
        if ( NumberConverter< Double, Int64 >::TryExactConvert( value, m_impl->GetInt64() ))
        {
            return value;
        }
        return boost::none;
    }

    case SCALAR_UINT64:
    {
        if ( NumberConverter< Double, Uint64 >::TryExactConvert( value, m_impl->GetUint64() ))
        {
            return value;
        }
        return boost::none;
    }

    case SCALAR_STRING:
    {
        Lexical::Floating< Double > lexDouble;
        if ( lexDouble.TryParse( m_impl->GetString() ))
        {
            return static_cast< Double >( lexDouble );
        }
        return boost::none;
    }

    default:
        CARAMEL_NOT_REACHED();
    }
}


boost::optional< std::string > Scalar::AsString() const
{
    switch ( m_impl->GetType() )
    {
    case SCALAR_STRING:
        return m_impl->GetString();

    case SCALAR_BOOL:
        return Caramel::ToString( m_impl->GetBool() );

    case SCALAR_INT64:
        return Caramel::ToString( m_impl->GetInt64() );

    case SCALAR_UINT64:
        return Caramel::ToString( m_impl->GetUint64() );

    case SCALAR_DOUBLE:
        return Caramel::ToString( m_impl->GetDouble() );

    case SCALAR_UNDEF:
        CARAMEL_THROW( "Value is undef" );

    default:
        CARAMEL_NOT_REACHED();
    }
}


std::string Scalar::ToString() const
{
    if ( m_impl->GetType() == SCALAR_UNDEF )
    {
        return "(undef)";
    }

    return *( this->AsString() );
}


//
// Implementation
//

Bool ScalarImpl::GetBool() const
{
    CARAMEL_ASSERT( m_type == SCALAR_BOOL );
    return ( boost::get< Int64 >( m_value ) != 0 );
}


Int64 ScalarImpl::GetInt64() const
{
    CARAMEL_ASSERT( m_type == SCALAR_INT64 );
    return boost::get< Int64 >( m_value );
}


Uint64 ScalarImpl::GetUint64() const
{
    CARAMEL_ASSERT( m_type == SCALAR_UINT64 );
    return boost::get< Uint64 >( m_value );
}


Double ScalarImpl::GetDouble() const
{
    CARAMEL_ASSERT( m_type == SCALAR_DOUBLE );
    return boost::get< Double >( m_value );
}


std::string ScalarImpl::GetString() const
{
    CARAMEL_ASSERT( m_type == SCALAR_STRING );
    return boost::get< std::string >( m_value );
}


///////////////////////////////////////////////////////////////////////////////
//
// Unsigned Size
//

template< typename T >
inline void Usize::Init( T value )
{
    if ( ! NumberConverter< Uint, T >::TryExactConvert( m_value, value ))
    {
        CARAMEL_THROW( "Can't convert {0} ({1}) to Uint", value, ToStringT< T >() );
    }
}

Usize::Usize( Ulong  value ) { this->Init( value ); }
Usize::Usize( Uint64 value ) { this->Init( value ); }
Usize::Usize( Int    value ) { this->Init( value ); }
Usize::Usize( Long   value ) { this->Init( value ); }
Usize::Usize( Int64  value ) { this->Init( value ); }


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
