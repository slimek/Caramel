// Caramel C++ Library - Algorithm Amenity - Linear Resampler Header

#ifndef __CARAMEL_ALGORITHM_LINEAR_RESAMPLER_H
#define __CARAMEL_ALGORITHM_LINEAR_RESAMPLER_H
#pragma once

#include <Caramel/Value/SharedArray.h>
#include <deque>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Linear Resampler
// - T is the type of samples.
//   Rep is the representation type for internal computation.
//
//   USAGE: Convert audio samples, e.g. from 44100 Hz to 8000 Hz, and vice versa.
//

template< typename T, typename Rep = Float >
class LinearResampler
{
public:
    
    explicit LinearResampler( Rep ratio );

    template< typename Container >
    SharedArray< T > Convert( const Container& input );

    template< typename Iterator >
    SharedArray< T > Convert( Iterator first, Iterator last );

    template< typename Iterator >
    SharedArray< T > Convert( Iterator first, Usize count );


private:

    template< typename Iterator >
    SharedArray< T > Shrink( Iterator first, Iterator last );

    template< typename Iterator >
    SharedArray< T > Expand( Iterator first, Iterator last );

    Rep m_ratio { 1 };
    Rep m_fullCoef { 1 };
    Rep m_coef { 0 };
    Rep m_value { 0 };
    Rep m_remainCoef { 0 };
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename T, typename Rep >
inline LinearResampler< T, Rep >::LinearResampler( Rep ratio )
    : m_ratio( ratio )
    , m_fullCoef( 1 / ratio )
{
    if ( ratio <= 1 )
    {
        m_coef = m_fullCoef;  // for Shrink
    }
    else
    {
        m_coef = m_ratio;  // for Expand
    }
}


template< typename T, typename Rep >
template< typename Container >
inline SharedArray< T > LinearResampler< T, Rep >::Convert( const Container& input )
{
    if ( m_ratio <= 1 )
    {
        return this->Shrink( input.begin(), input.end() );
    }
    else
    {
        return this->Expand( input.begin(), input.end() );
    }
}


template< typename T, typename Rep >
template< typename Iterator >
inline SharedArray< T > LinearResampler< T, Rep >::Convert( Iterator first, Iterator last )
{
    if ( m_ratio <= 1 )
    {
        return this->Shrink( first, last );
    }
    else
    {
        return this->Expand( first, last );
    }
}


template< typename T, typename Rep >
template< typename Iterator >
inline SharedArray< T > LinearResampler< T, Rep >::Convert( Iterator first, Usize count )
{
    if ( m_ratio <= 1 )
    {
        return this->Shrink( first, first + count );
    }
    else
    {
        return this->Expand( first, first + count );
    }
}


template< typename T, typename Rep >
template< typename Iterator >
inline SharedArray< T > LinearResampler< T, Rep >::Shrink( Iterator first, Iterator last )
{
    std::deque< T > result;

    for ( Iterator is = first; is != last; ++ is )
    {
        const Rep rs = static_cast< Rep >( *is );

        if ( m_coef > 1 )
        {
            m_value += rs;
            m_coef -= 1;
        }
        else
        {
            m_value += rs * m_coef;
            result.push_back( static_cast< T >( m_value * m_ratio ));

            m_value = rs * ( 1 - m_coef );
            m_coef = m_fullCoef - ( 1 - m_coef );
        }
    }

    return SharedArray< T >( result.begin(), result.size() );
}


template< typename T, typename Rep >
template< typename Iterator >
inline SharedArray< T > LinearResampler< T, Rep >::Expand( Iterator first, Iterator last )
{
    std::deque< T > result;

    for ( Iterator is = first; is != last; ++ is )
    {
        const Rep rs = static_cast< Rep >( *is );

        if ( m_remainCoef > 0 )
        {
            result.push_back( static_cast< T >( m_value + rs * m_remainCoef ));
            m_value = 0;
            m_remainCoef = 0;
        }

        while ( m_coef > 1 )
        {
            result.push_back( static_cast< T >( rs ));
            m_coef -= 1;
        }

        m_value = rs * m_coef;
        m_remainCoef = 1 - m_coef;
        m_coef = m_ratio - m_remainCoef;
    }

    return SharedArray< T >( result.begin(), result.size() );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ALGORITHM_LINEAR_RESAMPLER_H
