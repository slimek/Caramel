// Caramel C++ Library - Lexical Facility - Version Header

#ifndef __CARAMEL_LEXICAL_VERSION_H
#define __CARAMEL_LEXICAL_VERSION_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <boost/operators.hpp>


namespace Caramel
{

namespace Lexical
{

///////////////////////////////////////////////////////////////////////////////
//
// Version
// - Convert a version string into a comparable object.
//
//   FORMAT:
//
//     The string format should be "1", "1.2", "1.2.3" or "1.2.3.4".
//     Padding 0s would be omitted. For example, "1.2.03.004" equals to "1.2.3.4".
//     Each component should be Uint32.
//
//   Method throws if :
//     1. There are characters other then digits and '.' .
//     2. There are more than 4 components.
//   

class Version : public boost::totally_ordered< Version >
{
public:
    Version() {}

    explicit Version( Uint32 major, Uint32 minor = 0, Uint32 build = 0, Uint32 revision = 0 );

    // Throws if the input is not a valid version string.
    static Version FromString( const std::string& versionString );


    /// Propertyes ///

    Uint32 Major()    const;
    Uint32 Minor()    const;
    Uint32 Build()    const;
    Uint32 Revision() const;


    /// Operators ///

    Bool operator==( const Version& rhs ) const;
    Bool operator< ( const Version& rhs ) const;


    /// Conversion ///

    // Always 4 components : M.m.b.r
    std::string ToString() const;

    //
    // Partial String
    // - Only represents some components of the version number.
    //
    //   1 : M
    //   2 : M.m
    //   3 : M.m.b
    //   4 : M.m.b.r
    //
    std::string ToString( Uint numComponents ) const;


    //
    // Parsing
    // - See the FORMAT above.
    //   Besides this, it returns false if the input is an empty string.
    //
    Bool TryParse( const std::string& input );


private:

    Uint64 m_majorMinor { 0 };
    Uint64 m_buildRevision { 0 };
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Lexical

} // namespace Caramel

#endif // __CARAMEL_LEXICAL_VERSION_H
