// Caramel C++ Library Test - Task - Continuation Traits Suite

#include "CaramelTestPch.h"

#include <Caramel/Task/Task.h>


namespace Caramel
{

SUITE( ContinuationTraitsSuite )
{

//
// Continuation Traits from Result
//

template< typename Result >
struct Work
{
    template< typename Function >
    auto ResultOf( Function&& f ) -> TypeT< typename Detail::ThenFunctionTraits< Function, Result >::ResultType >
    {
        return TypeT< typename Detail::ThenFunctionTraits< Function, Result >::ResultType >();
    }

    template< typename Function >
    auto HolderOf( Function&& f ) -> TypeT< typename Detail::ContinuationTraits< Function, Result >::HolderType >
    {
        return TypeT< typename Detail::ContinuationTraits< Function, Result >::HolderType >();
    }

    template< typename Function >
    auto TaskOf( Function&& f ) -> TypeT< typename Detail::ContinuationTraits< Function, Result >::TaskType >
    {
        return TypeT< typename Detail::ContinuationTraits< Function, Result >::TaskType >();
    }
};


TEST( ContinuationFromIntTraitsTest )
{
    typedef std::string Str;

    Work< Int > wi;

    /// Result Type ///
    {
        auto v2v = wi.ResultOf( [] {} );
        auto v2i = wi.ResultOf( [] () -> Int { return 42; } );
        auto v2s = wi.ResultOf( [] () -> Str { return "Alice"; } );

        CHECK(( true == std::is_same< TypeT< void >, decltype( v2v ) >::value ));
        CHECK(( true == std::is_same< TypeT< Int >,  decltype( v2i ) >::value ));
        CHECK(( true == std::is_same< TypeT< Str >,  decltype( v2s ) >::value ));

        auto i2v = wi.ResultOf( [] ( Int ) {} );
        auto i2i = wi.ResultOf( [] ( Int ) -> Int { return 42; } );
        auto i2s = wi.ResultOf( [] ( Int ) -> Str { return "Alice"; } );
        
        CHECK(( true == std::is_same< TypeT< void >, decltype( i2v ) >::value ));
        CHECK(( true == std::is_same< TypeT< Int >,  decltype( i2i ) >::value ));
        CHECK(( true == std::is_same< TypeT< Str >,  decltype( i2s ) >::value ));

        auto t2v = wi.ResultOf( [] ( Task< Int > ) {} );
        auto t2i = wi.ResultOf( [] ( Task< Int > ) -> Int { return 42; } );
        auto t2s = wi.ResultOf( [] ( Task< Int > ) -> Str { return "Alice"; } );

        CHECK(( true == std::is_same< TypeT< void >, decltype( t2v ) >::value ));
        CHECK(( true == std::is_same< TypeT< Int >,  decltype( t2i ) >::value ));
        CHECK(( true == std::is_same< TypeT< Str >,  decltype( t2s ) >::value ));
    }

    /// Holder Type ///
    {
        auto v2v = wi.HolderOf( [] {} );

        CHECK(( true == std::is_same< TypeT< Detail::ThenWithVoidTask< void >>, decltype( v2v ) >::value ));

        auto t2v = wi.HolderOf( [] ( Task< Int > ) {} );

        CHECK(( true == std::is_same< TypeT< Detail::ThenWithTaskTask< void, Int >>, decltype( t2v ) >::value ));
    }

    /// Task Type ///
    {
        auto v2v = wi.TaskOf( [] {} );
        auto v2i = wi.TaskOf( [] () -> Int { return 42; } );

        CHECK(( true == std::is_same< TypeT< Task< void >>, decltype( v2v ) >::value ));
        CHECK(( true == std::is_same< TypeT< Task< Int >>,  decltype( v2i ) >::value ));

        auto t2v = wi.TaskOf( [] ( Task< Int > ) {} );
        auto t2i = wi.TaskOf( [] ( Task< Int > ) -> Int { return 42; } );

        CHECK(( true == std::is_same< TypeT< Task< void >>, decltype( t2v ) >::value ));
        CHECK(( true == std::is_same< TypeT< Task< Int >>,  decltype( t2i ) >::value ));
    }
} 


//
// Continuation Traits from Void
//

template<>
struct Work< void >
{
    template< typename Function >
    auto ResultOf( Function&& f ) -> TypeT< typename Detail::ThenFunctionTraits< Function, void >::ResultType >
    {
        return TypeT< typename Detail::ThenFunctionTraits< Function, void >::ResultType >();
    }

    template< typename Function >
    auto HolderOf( Function&& f ) -> TypeT< typename Detail::ContinuationTraits< Function, void >::HolderType >
    {
        return TypeT< typename Detail::ContinuationTraits< Function, void >::HolderType >();
    }

    template< typename Function >
    auto TaskOf( Function&& f ) -> TypeT< typename Detail::ContinuationTraits< Function, void >::TaskType >
    {
        return TypeT< typename Detail::ContinuationTraits< Function, void >::TaskType >();
    }
};


TEST( ContinuationFromVoidTraitsTest )
{
    typedef std::string Str;

    Work< void > wv;

    /// Result Type ///
    {
        auto v2v = wv.ResultOf( [] {} );
        auto v2i = wv.ResultOf( [] () -> Int { return 42; } );
        auto v2s = wv.ResultOf( [] () -> Str { return "Alice"; } );

        static_assert( std::is_same< TypeT< void >, decltype( v2v ) >::value, "void" );
        static_assert( std::is_same< TypeT< Int >,  decltype( v2i ) >::value, "Int" );
        static_assert( std::is_same< TypeT< Str >,  decltype( v2s ) >::value, "Str" );

        auto t2v = wv.ResultOf( [] ( Task< void > ) {} );
        auto t2i = wv.ResultOf( [] ( Task< void > ) -> Int { return 42; } );
        auto t2s = wv.ResultOf( [] ( Task< void > ) -> Str { return "Alilce"; } );

        static_assert( std::is_same< TypeT< void >, decltype( t2v ) >::value, "void" );
        static_assert( std::is_same< TypeT< Int >,  decltype( t2i ) >::value, "Int" );
        static_assert( std::is_same< TypeT< Str >,  decltype( t2s ) >::value, "Str" );
    }

    /// Holder Type ///
    {
        auto v2v = wv.HolderOf( [] {} );

        CHECK(( true == std::is_same< TypeT< Detail::ThenWithVoidTask< void >>, decltype( v2v ) >::value ));

        auto t2v = wv.HolderOf( [] ( Task< void > ) {} );

        CHECK(( true == std::is_same< TypeT< Detail::ThenWithTaskTask< void, void >>, decltype( t2v ) >::value ));
    }

    /// Task Type ///
    {
        auto v2v = wv.TaskOf( [] {} );
        auto v2i = wv.TaskOf( [] () -> Int { return 42; } );

        CHECK(( true == std::is_same< TypeT< Task< void >>, decltype( v2v ) >::value ));
        CHECK(( true == std::is_same< TypeT< Task< Int >>,  decltype( v2i ) >::value ));

        auto t2v = wv.TaskOf( [] ( Task< void > ) {} );
        auto t2i = wv.TaskOf( [] ( Task< void > ) -> Int { return 42; } );

        CHECK(( true == std::is_same< TypeT< Task< void >>, decltype( t2v ) >::value ));
        CHECK(( true == std::is_same< TypeT< Task< Int >>,  decltype( t2i ) >::value ));
    }
}


} // SUITE ContinuationTraitsSuite

} // namespace Caramel
