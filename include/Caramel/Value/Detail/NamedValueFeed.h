// Caramel C++ Library - Value Facility - Detail - Named Value Feed Header

#ifndef __CARAMEL_VALUE_NAMED_VALUE_FEED_H
#define __CARAMEL_VALUE_NAMED_VALUE_FEED_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Value/Scalar.h>


namespace Caramel
{

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

    NamedValueFeed( std::string name, Bool v );
    NamedValueFeed( std::string name, Int v );
    NamedValueFeed( std::string name, Uint v );
    NamedValueFeed( std::string name, Int64 v );
    NamedValueFeed( std::string name, Uint64 v );
    NamedValueFeed( std::string name, Double v );
    NamedValueFeed( std::string name, std::string v );
    NamedValueFeed( std::string name, const Char* v );

    NamedValueFeed( std::string name, Long v );
    NamedValueFeed( std::string name, Ulong v );

    
    /// Properties ///

    std::string   Name()  const { return m_name; }
    const Scalar* Value() const { return m_value.get(); }


private:

    std::string m_name;
    std::shared_ptr< Scalar > m_value;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_VALUE_NAMED_VALUE_FEED_H
