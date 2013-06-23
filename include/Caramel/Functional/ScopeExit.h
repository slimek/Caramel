// Caramel C++ Library - Functional Amenity - Scope Exit Header

#ifndef __CARAMEL_FUNCTIONAL_SCOPE_EXIT_H
#define __CARAMEL_FUNCTIONAL_SCOPE_EXIT_H

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

template< typename Function >
class ScopeGuard : public boost::noncopyable
{
public:

    ScopeGuard( Function f );
    ScopeGuard( ScopeGuard&& rhs );
    ~ScopeGuard();

    void Dismiss();


private:

    Function m_function;
    Bool     m_active;
};


//
// Stand-alone Function
//

template< typename Function >
inline ScopeGuard< Function > ScopeExit( Function f )
{
    return ScopeGuard< Function >( std::move( f ));
}


///////////////////////////////////////////////////////////////////////////////
//
// Implementations
//

template< typename Function >
inline ScopeGuard< Function >::ScopeGuard( Function f )
    : m_function( std::move( f ))
    , m_active( true )
{
}


template< typename Function >
inline ScopeGuard< Function >::ScopeGuard( ScopeGuard&& rhs )
    : m_function( std::move( rhs.m_function ))
    , m_active( rhs.m_active )
{
}


template< typename Function >
inline ScopeGuard< Function >::~ScopeGuard()
{
    if ( m_active )
    {
        m_function();
    }
}


template< typename Function >
inline void ScopeGuard< Function >::Dismiss()
{
    m_active = false;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FUNCTIONAL_SCOPE_EXIT_H

