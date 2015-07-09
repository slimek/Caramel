// Caramel C++ Library - Android Facility - Input Asset Stream Header

#ifndef __CARAMEL_ANDROID_INPUT_ASSET_STREAM_H
#define __CARAMEL_ANDROID_INPUT_ASSET_STREAM_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Io/InputStream.h>
#include <android/asset_manager.h>
#include <boost/noncopyable.hpp>


namespace Caramel
{

namespace Android
{

///////////////////////////////////////////////////////////////////////////////
//
// Input Asset Stream
//

class InputAssetStream : public InputStream
                       , public boost::noncopyable
{
public:
    
    InputAssetStream( AAssetManager* manager, const std::string& assetName );
    ~InputAssetStream();

    Uint Length() const { return m_length; }


    /// Implements InputStream ///

    Usize Read( Void* buffer, Usize size ) override;

    void Seek( Int offset ) override;

    Uint Tell()  const override;
    
    Bool IsEof() const override { return m_eof; }


private:

    AAsset* m_asset { nullptr };
    
    std::string m_assetName;
    Uint m_length { 0 };  // The total length of the asset, in bytes.

    Bool m_eof { false };
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Android

} // namespace Caramel

#endif // __CARAMEL_ANDROID_INPUT_ASSET_STREAM_H
