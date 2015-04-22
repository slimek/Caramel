// Caramel C++ Library - Async Facility - Any Event Slot Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_SLOT_H
#define __CARAMEL_ASYNC_ANY_EVENT_SLOT_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/AnyEventTarget.h>
#include <boost/noncopyable.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Slot
//

class AnyEventSlotImpl;

class AnyEventSlot : public AnyEventTarget
                   , public boost::noncopyable
{
public:

    AnyEventSlot();
    ~AnyEventSlot();


    /// Properties ///

    explicit operator Bool() const { return this->IsValid(); }

    // Not receive an event yet.
    Bool IsEmpty() const { return ! this->IsValid(); }

    Bool IsValid() const;


    /// Operations ///

    void Set( const AnyEvent& event );
    void Set( AnyEvent&& event );

    void SetEvent( Int eventId );
    void SetEvent( Int eventId, const Any& value );
    void SetEvent( Int eventId, Any&& value );

    // Wait the slot until it becomes valid.
    void Wait();


    //
    // Accessors
    // - These functions throw if this slot is empty.
    //

    AnyEvent Take();

    Int Id() const;

    template< typename T >
    T Value() const;


    /// AnyEventTarget Operations ///

    // This function has two effects:
    // 1. Unlink from all linked dispatchers.
    // 2. Discard the event if have received one.
    void Reset() override;


private:

    /// Implements AnyEventTarget ///

    AnyEventTargetPtr GetTargetImpl() const override;


    /// Internal Functions ///

    // Throws if this slot is empty.
    AnyEvent GetEvent() const;


    /// Data Members ///

    std::shared_ptr< AnyEventSlotImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline Int AnyEventSlot::Id() const
{
    auto event = this->GetEvent();
    return event.Id();
}


template< typename T >
inline T AnyEventSlot::Value() const
{
    auto event = this->GetEvent();
    return event.template Value< T >();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_SLOT_H
