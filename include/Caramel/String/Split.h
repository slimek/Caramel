// Caramel C++ Library - String Facility - Split Header

#ifndef __CARAMEL_STRING_SPLIT_H
#define __CARAMEL_STRING_SPLIT_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/String/Algorithm.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Split into Two Parts
// - Based on Before/After algorithms.
//
//   USAGE:
//
//     SplitterFirst split( text, ',' );
//     if ( split )
//     {
//         std::string head = split.before;
//         std::string tail = split.after;
//         ...
//     }
//

struct SplitterFirst
{
    SplitterFirst( const std::string& input, Char c );

    operator Bool() const { return splitted; }

    Bool splitted;
    std::string before;
    std::string after;

};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

//
// Splitter First
//

inline SplitterFirst::SplitterFirst( const std::string& input, Char c )
    : splitted( Contains( input, c ))
    , before( BeforeFirst( input, c ))
    , after( AfterFirst( input, c ))
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_SPLIT_H
