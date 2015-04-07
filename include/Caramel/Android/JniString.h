// Caramel C++ Library - Android Facility - JNI String Header

#ifndef __CARAMEL_ANDROID_JNI_STRING_H
#define __CARAMEL_ANDROID_JNI_STRING_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Android/Detail/JniGlobals.h>


namespace Caramel
{
    
namespace Android
{
    
///////////////////////////////////////////////////////////////////////////////
//
// JNI String
//

class JniString
{
public:

    JniString() {}
    explicit JniString( jstring str );
    
    operator std::string() const;
    
private:

    std::shared_ptr< Detail::JniStringGlobal > m_string;    
};  

    
} // namespace Android

} // namespace Caramel

#endif // __CARAMEL_ANDROID_JNI_STRING_H
