// Caramel C++ Library - Error Facility - Exception Pointer Header

#ifndef __CARAMEL_ERROR_EXCEPTION_PTR_H
#define __CARAMEL_ERROR_EXCEPTION_PTR_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Error/Detail/ExceptionHolders.h>
#include <boost/operators.hpp>
#include <exception>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Exception Pointer
//
//   It is similar to std::exception_ptr, but can be cast to an AnyFailiure.
//   We need this mechanism in Task exception handling.
//

class ExceptionPtr : public boost::equality_comparable< ExceptionPtr, std::nullptr_t >
{
public:

    ExceptionPtr();
    ExceptionPtr( std::nullptr_t );

    explicit ExceptionPtr( const Caramel::Exception& e );
    explicit ExceptionPtr( const Caramel::AnyFailure& e );

    explicit ExceptionPtr( Detail::ExceptionHolder* holder );

    template< typename E >
    static ExceptionPtr Clone( const E& exception );

    // Represents an exception not recognized by Caramel.Error facility.
    static ExceptionPtr Unknown();


    /// Predicates ///

    explicit operator Bool() const { return static_cast< Bool >( m_holder ); }


    /// Operators ///

    Bool operator==( std::nullptr_t rhs ) const;


    /// Operations ///

    void Rethrow() const;

    std::string TracingMessage() const;


private:

    friend class AnyFailurePtr;

    explicit ExceptionPtr(
        const std::shared_ptr< Detail::ExceptionHolder >& holder );

    
    /// Data Members ///

    std::shared_ptr< Detail::ExceptionHolder > m_holder;
};


//
// Auxiliary Functions
//
 
// You may call this function in catch {} scope.
ExceptionPtr CurrentException();


///////////////////////////////////////////////////////////////////////////////
//
// Any Failure Pointer
//
//   Specialized ExceptionPtr, to provide AnyFailure operations.
//

class AnyFailurePtr : public ExceptionPtr
{
public:

    AnyFailurePtr();
    AnyFailurePtr( std::nullptr_t );

    // Return a null pointer if e is not an AnyFailure.
    static AnyFailurePtr CastFrom( const ExceptionPtr& e );

    const AnyFailure* operator->() const;

private:

    explicit AnyFailurePtr(
        const std::shared_ptr< Detail::CaramelAnyFailureHolder >& holder );
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline ExceptionPtr::ExceptionPtr()
    : m_holder( nullptr )
{
}


inline ExceptionPtr::ExceptionPtr( std::nullptr_t )
    : m_holder( nullptr )
{
}


inline ExceptionPtr::ExceptionPtr( Detail::ExceptionHolder* holder )
    : m_holder( holder )
{
}


template< typename E >
inline ExceptionPtr ExceptionPtr::Clone( const E& clonee )
{
    return ExceptionPtr( new Detail::StdExceptionHolder< E >( clonee ));
}


inline ExceptionPtr ExceptionPtr::Unknown()
{
    return ExceptionPtr( new Detail::UnknownExceptionHolder );
}


//
// Operators
//

inline Bool ExceptionPtr::operator==( std::nullptr_t ) const
{
    return ! m_holder;
}


//
// Operations
//

inline void ExceptionPtr::Rethrow() const
{
    m_holder->Rethrow();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ERROR_EXCEPTION_PTR_H
