// Caramel C++ Library - Value Facility - Detail - Named Value Ref Header

#ifndef __CARAMEL_VALUE_NAMED_VALUE_REF_H
#define __CARAMEL_VALUE_NAMED_VALUE_REF_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Value/Scalar.h>


namespace Caramel
{

// Forwards Declaration
class NamedValues;

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Constant Named Value
//

class ConstNamedValueRef
{
public:

    ConstNamedValueRef( const std::string& name, Scalar* value );


    /// Accessors ///

    Bool        AsBool()   const;
    Int         AsInt()    const;
    Uint        AsUint()   const;
    Int64       AsInt64()  const;
    Uint64      AsUint64() const;
    Double      AsDouble() const;
    std::string AsString() const;


protected:

    std::string m_name;
    Scalar*     m_value;
};


///////////////////////////////////////////////////////////////////////////////
//
// Mutable Named Value
//

class NamedValueRef : public ConstNamedValueRef
{
public:

    NamedValueRef( NamedValues* host, const std::string& name, Scalar* value );


    /// Operators ///

    NamedValueRef& operator=( Bool v );
    NamedValueRef& operator=( Int v );
    NamedValueRef& operator=( Uint v );
    NamedValueRef& operator=( Int64 v );
    NamedValueRef& operator=( Uint64 v );
    NamedValueRef& operator=( Long v );
    NamedValueRef& operator=( Ulong v );
    NamedValueRef& operator=( Double v );
    NamedValueRef& operator=( const std::string& v );
    NamedValueRef& operator=( const Char* v );


private:

    void PrepareEntry();

    NamedValues* m_host;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_VALUE_NAMED_VALUE_REF_H
