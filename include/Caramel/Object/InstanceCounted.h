// Caramel C++ Library - Object Facility - Instance-Counted Header

#ifndef __CARAMEL_OBJECT_INSTANCE_COUNTED_H
#define __CARAMEL_OBJECT_INSTANCE_COUNTED_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <atomic>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Instance-Counted
// - Count how many instances are existing now.
//

template< typename Derived >
class InstanceCounted
{
public:

    static Uint GetInstanceCount() { return m_instanceCount.load(); }

protected:

    InstanceCounted();
    InstanceCounted( const InstanceCounted& );
    InstanceCounted( InstanceCounted&& );
    ~InstanceCounted();        


private:

    static std::atomic< Uint > m_instanceCount;    
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename Derived >
std::atomic< Uint > InstanceCounted< Derived >::m_instanceCount( 0 );


template< typename Derived >
inline InstanceCounted< Derived >::InstanceCounted()
{
    ++ m_instanceCount;
}


template< typename Derived >
inline InstanceCounted< Derived >::InstanceCounted( const InstanceCounted& )
{
    ++ m_instanceCount;
}


template< typename Derived >
inline InstanceCounted< Derived >::InstanceCounted( InstanceCounted&& )
{
    ++ m_instanceCount;
}


template< typename Derived >
inline InstanceCounted< Derived >::~InstanceCounted()
{
    -- m_instanceCount;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_OBJECT_INSTANCE_COUNTED_H
