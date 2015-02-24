// Caramel C++ Library - Data Facility - Base64 Header

#ifndef __CARAMEL_DATA_BASE_64_H
#define __CARAMEL_DATA_BASE_64_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Value/SharedArray.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Base64 Encode
//

std::string Base64Encode( const Byte* data, std::size_t size );

std::string Base64Encode( const Void* data, std::size_t size );
std::string Base64Encode( const std::string& data );


///////////////////////////////////////////////////////////////////////////////
//
// Base64 Decode
//

//
// Returns false if decode failed.
//

Bool Base64Decode( const std::string& base64, SharedArray< Byte >& data );

Bool Base64Decode( const std::string& base64, std::string& data );


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_DATA_BASE_64_H
