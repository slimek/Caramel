// Caramel C++ Library - Windows Facility - Registry Header

#ifndef __CARAMEL_WINDOWS_REGISTRY_H
#define __CARAMEL_WINDOWS_REGISTRY_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/String/Utf8String.h>


#if defined( CARAMEL_SYSTEM_IS_WINDOWS )


namespace Caramel
{

namespace Windows
{

///////////////////////////////////////////////////////////////////////////////
//
// Registry
//

class RegistryImpl;

class Registry
{
public:

    static Registry LocalMachine();
    
    
    //
    // Get Values
    // - Returns false if the key or value doesn't exist.
    //

    Bool GetStringValue( const Utf8String& keyPath, const Utf8String& valueName, Utf8String& value ) const;


    //
    // Get Values - std::string style
    // - Returns false if the key or value doesn't exist.
    //   Throws if the input keyPath or valueName is not UTF-8 encoding.
    //   The output value is UTF-8 encoding.
    //
    
    Bool GetStringValue( const std::string& keyPath, const std::string& valueName, std::string& value ) const;


private:

    explicit Registry( std::shared_ptr< RegistryImpl > impl );

    std::shared_ptr< RegistryImpl > m_impl;
};

///////////////////////////////////////////////////////////////////////////////

} // namespace Windows

} // namespace Caramel


#endif // CARAMEL_SYSTEM_IS_WINDOWS

#endif // __CARAMEL_WINDOWS_REGISTRY_H
