// Caramel C++ Library - Error Facility - Any Failure Header

#ifndef __CARAMEL_ERROR_ANY_FAILURE_H
#define __CARAMEL_ERROR_ANY_FAILURE_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Value/Any.h>
#include <exception>


namespace Caramel
{

// Forwards declaration
class AnyEvent;

///////////////////////////////////////////////////////////////////////////////
//
// Any Failure
//  - An exception which can carry an ID and an any type value.
//    The meaning of failure ID depends on application.
//

class AnyFailure : public std::exception
{
public:

    // A failure without a value
    explicit AnyFailure( Int id );

    // A failure with a any value
    AnyFailure( Int id, const Any& value );
    AnyFailure( Int id, Any&& value );


    /// Accessors ///

    Int Id() const { return m_id; }

    template< typename T >
    T Value() const;

    // Add a custom what message
    AnyFailure& What( const std::string& what );
    AnyFailure& What( std::string&& what );

    // Get the what message
    std::string What() const { return m_what; }

    Bool HasCustomWhat() const { return m_customWhat; }


    /// Conversions ///

    AnyEvent ToAnyEvent() const;


    /// Overrides std::exception ///

    // Returns a generated message from id if m_what not given.
    const Char* what() const CARAMEL_NOEXCEPT override { return m_what.c_str(); }


private:

    void Init();

    Int m_id;
    Any m_value;

    Bool m_customWhat;
    std::string m_what;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename T >
inline T AnyFailure::Value() const
{
    return m_value.template As< T >();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ERROR_ANY_FAILURE_H

