// Caramel C++ Library - Value Facility - Detail - Named Value Ref Header

#ifndef __CARAMEL_VALUE_NAMED_VALUE_REF_H
#define __CARAMEL_VALUE_NAMED_VALUE_REF_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


namespace Caramel
{

// Forwards Declaration
class NamedValues;

namespace Detail
{

struct NamedValueEntry;

///////////////////////////////////////////////////////////////////////////////
//
// Constant Named Value
//

class ConstNamedValueRef
{
public:

    ConstNamedValueRef( const std::string& name, NamedValueEntry* entry );


    /// Accessors ///

    std::string AsString() const;


protected:

    std::string      m_name;
    NamedValueEntry* m_entry;
};


///////////////////////////////////////////////////////////////////////////////
//
// Mutable Named Value
//

class NamedValueRef : public ConstNamedValueRef
{
public:

    NamedValueRef( NamedValues* host, const std::string& name, NamedValueEntry* entry );


    /// Operators ///

    NamedValueRef& operator=( Bool v );
    NamedValueRef& operator=( Int v );
    NamedValueRef& operator=( Double v );
    NamedValueRef& operator=( const std::string& v );
    NamedValueRef& operator=( const Char* v );


private:

    NamedValues* m_host;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_VALUE_NAMED_VALUE_REF_H
