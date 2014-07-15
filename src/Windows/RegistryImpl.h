// Caramel C++ Library - Windows Facility - Registry Private Header

#ifndef __CARAMEL_WINDOWS_REGISTRY_IMPL_H
#define __CARAMEL_WINDOWS_REGISTRY_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Windows/Registry.h>
#include <Windows.h>


#if defined( CARAMEL_SYSTEM_IS_WINDOWS )


namespace Caramel
{

namespace Windows
{

///////////////////////////////////////////////////////////////////////////////
//
// Registry
//

class RegistryImpl
{
public:
    RegistryImpl( HKEY key, const std::string& name );
    ~RegistryImpl();

    /// Properties ///

    HKEY Handle() const { return m_key; }
    std::string Name() const { return m_name; }


    /// Get Values ///

    Bool GetStringValue( const Utf8String& valueName, Utf8String& value ) const;

    Bool HasValue( const std::wstring& valueName ) const;

    struct ValueInfo
    {
        DWORD type { REG_NONE };
        DWORD size { 0 };
    };
    
    ValueInfo GetValueInfo( const std::wstring& valueName ) const;


private:


    HKEY m_key { NULL };
    std::string m_name;  // UTF-8 encoding
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Windows

} // namespace Caramel


#endif // CARAMEL_SYSTEM_IS_WINDOWS

#endif // __CARAMEL_WINDOWS_REGISTRY_IMPL_H
