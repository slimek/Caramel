// Caramel C++ Library - Configuration Facility - Configuration Value Types Header

#ifndef __CARAMEL_CONFIGURATION_CONFIG_VALUE_H
#define __CARAMEL_CONFIGURATION_CONFIG_VALUE_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Configuration/ConfigSection.h>
#include <boost/noncopyable.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Configuration Values
//

//
// Abstract Value
//

class ConfigValue : public boost::noncopyable
{
public:

    ConfigValue( const std::string& name, Bool hasDefault );
    
    virtual ~ConfigValue() {}

    
    std::string GetName() const { return m_name; }
    Bool HasDefault() const { return m_hasDefault; }


    // In the 'data' should have a value with 'm_name'.
    virtual void Load( const NamedValues& data ) = 0;


protected:

    // Data Members //

    std::string m_name;
    Bool m_hasDefault { false };
};


//
// Boolean
//

class ConfigBool : public ConfigValue
{
public:

    ConfigBool( ConfigSection& s, const std::string& name );
    ConfigBool( ConfigSection& s, const std::string& name, Bool defaultValue );

    Bool ToBool()   const { return m_value; }
    operator Bool() const { return m_value; }


    void Load( const NamedValues& data ) override;


private:

    Bool m_value { false };
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CONFIGURATION_CONFIG_VALUE_H

