// Caramel C++ Library - Functional Amenity - Scope Guard Header

#ifndef __CARAMEL_FUNCTIONAL_SCOPE_GUARD_H
#define __CARAMEL_FUNCTIONAL_SCOPE_GUARD_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <boost/noncopyable.hpp>
#include <functional>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Scope Guard
//

class ScopeGuard : public boost::noncopyable
{
    typedef std::function< void() > Function;

public:

    ScopeGuard( Function f );
    ~ScopeGuard();

    void Dismiss();


private:

    Function m_function;
    Bool     m_active;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementations
//

inline ScopeGuard::ScopeGuard( Function f )
    : m_function( f )
    , m_active( true )
{
}


inline ScopeGuard::~ScopeGuard()
{
    if ( m_active )
    {
        m_function();
    }
}


inline void ScopeGuard::Dismiss()
{
    m_active = false;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FUNCTIONAL_SCOPE_GUARD_H

