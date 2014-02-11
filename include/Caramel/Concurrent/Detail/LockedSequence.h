// Caramel C++ Library - Concurrent Amenity - Detail - Locked Sequence Header

#ifndef __CARAMEL_CONCURRENT_DETAIL_LOCKED_SEQUENCE_H
#define __CARAMEL_CONCURRENT_DETAIL_LOCKED_SEQUENCE_H
#pragma once

#include <Caramel/Caramel.h>
#include <boost/noncopyable.hpp>
#include <mutex>


namespace Caramel
{

namespace Concurrent
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Const Locked Sequence
//

template< typename SequenceType >
class ConstLockedSequence : public boost::noncopyable
{
public:

    ConstLockedSequence( std::mutex& mutex, const SequenceType& sequence );


    /// Properties ///

    Bool IsEmpty() const { return m_constSequence.empty(); }
    Uint Size()    const { return static_cast< Uint >( m_constSequence.size() ); }


    /// Accessors ///

    typedef typename SequenceType::const_iterator ConstIterator;

    ConstIterator Begin() const { return m_constSequence.begin(); }
    ConstIterator End()   const { return m_constSequence.end(); }


    // Compatible with STL/Boost

    typedef typename SequenceType::const_iterator const_iterator;

    const_iterator begin() const { return m_constSequence.begin(); }
    const_iterator end()   const { return m_constSequence.end(); }


private:

    std::unique_lock< std::mutex > m_lock;
    const SequenceType& m_constSequence;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename SequenceT >
ConstLockedSequence< SequenceT >::ConstLockedSequence( std::mutex& mutex, const SequenceT& seq )
    : m_lock( mutex )
    , m_constSequence( seq )
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_DETAIL_LOCKED_SEQUENCE_H
