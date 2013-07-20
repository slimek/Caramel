// Caramel C++ Library - String Facility - Case Insensitive Less Header

#ifndef __CARAMEL_STRING_CAIN_LESS_H
#define __CARAMEL_STRING_CAIN_LESS_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <boost/algorithm/string/predicate.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Case Insensitive Less
//

struct CainLess
{
    template< typename StringType >
    Bool operator()( const StringType& lhs, const StringType& rhs ) const
    {
        return boost::algorithm::ilexicographical_compare( lhs, rhs );
    }
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_CAIN_LESS_H
