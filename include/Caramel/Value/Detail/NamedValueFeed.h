// Caramel C++ Library - Value Facility - Detail - Named Value Feed Header

#ifndef __CARAMEL_VALUE_NAMED_VALUE_FEED_H
#define __CARAMEL_VALUE_NAMED_VALUE_FEED_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


namespace Caramel
{

// Forwards Declaration
class NamedValueEntry;

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Named Value Feed
// - Helper class for create a NamedValues with initializer list.
//

class NamedValueFeed
{
public:

    NamedValueFeed( const std::string& name, Bool v );
    NamedValueFeed( const std::string& name, Int v );
    NamedValueFeed( const std::string& name, Uint v );
    NamedValueFeed( const std::string& name, Int64 v );
    NamedValueFeed( const std::string& name, Uint64 v );
    NamedValueFeed( const std::string& name, Double v );
    NamedValueFeed( const std::string& name, const std::string& v );
    NamedValueFeed( const std::string& name, const Char* v );

    NamedValueFeed( const std::string& name, Long v );
    NamedValueFeed( const std::string& name, Ulong v );

    
    /// Properties ///

    std::string            Name()  const { return m_name; }
    const NamedValueEntry* Entry() const { return m_entry.get(); }


private:

    std::string m_name;
    std::shared_ptr< NamedValueEntry > m_entry;    
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_VALUE_NAMED_VALUE_FEED_H
