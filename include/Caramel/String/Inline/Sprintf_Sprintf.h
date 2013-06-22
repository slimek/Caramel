// Caramel C++ Library - String Facility - Sprintf Inline Header

//
// NOTE: Inline header needs no include guard or namespace.
//

/// Functions with 1 Argument ///

template< typename T0 >
inline std::string Sprintf( const Char* format
    , const T0& a0 )
{
    return Detail::SprintfImpl( format
        , Detail::SprintfParameter< T0 >()( a0 )
    );
}

template< typename T0 >
inline std::string Sprintf( const std::string& format
    , const T0& a0 )
{
    return Detail::SprintfImpl( format.c_str()
        , Detail::SprintfParameter< T0 >()( a0 )
    );
}

template< typename T0, typename T1 >
inline std::string Sprintf( const Char* format
    , const T0& a0, const T1& a1 )
{
    return Detail::SprintfImpl( format
        , Detail::SprintfParameter< T0 >()( a0 )
        , Detail::SprintfParameter< T1 >()( a1 )
    );
}

template< typename T0, typename T1 >
inline std::string Sprintf( const std::string& format
    , const T0& a0, const T1& a1 )
{
    return Detail::SprintfImpl( format.c_str()
        , Detail::SprintfParameter< T0 >()( a0 )
        , Detail::SprintfParameter< T1 >()( a1 )
    );
}

template< typename T0, typename T1, typename T2 >
inline std::string Sprintf( const Char* format
    , const T0& a0, const T1& a1, const T2& a2 )
{
    return Detail::SprintfImpl( format
        , Detail::SprintfParameter< T0 >()( a0 )
        , Detail::SprintfParameter< T1 >()( a1 )
        , Detail::SprintfParameter< T2 >()( a2 )
    );
}

template< typename T0, typename T1, typename T2 >
inline std::string Sprintf( const std::string& format
    , const T0& a0, const T1& a1, const T2& a2 )
{
    return Detail::SprintfImpl( format.c_str()
        , Detail::SprintfParameter< T0 >()( a0 )
        , Detail::SprintfParameter< T1 >()( a1 )
        , Detail::SprintfParameter< T2 >()( a2 )
    );
}

template< typename T0, typename T1, typename T2, typename T3 >
inline std::string Sprintf( const Char* format
    , const T0& a0, const T1& a1, const T2& a2, const T3& a3 )
{
    return Detail::SprintfImpl( format
        , Detail::SprintfParameter< T0 >()( a0 )
        , Detail::SprintfParameter< T1 >()( a1 )
        , Detail::SprintfParameter< T2 >()( a2 )
        , Detail::SprintfParameter< T3 >()( a3 )
    );
}

template< typename T0, typename T1, typename T2, typename T3 >
inline std::string Sprintf( const std::string& format
    , const T0& a0, const T1& a1, const T2& a2, const T3& a3 )
{
    return Detail::SprintfImpl( format.c_str()
        , Detail::SprintfParameter< T0 >()( a0 )
        , Detail::SprintfParameter< T1 >()( a1 )
        , Detail::SprintfParameter< T2 >()( a2 )
        , Detail::SprintfParameter< T3 >()( a3 )
    );
}


