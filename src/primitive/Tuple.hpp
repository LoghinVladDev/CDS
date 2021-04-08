#include <CDS/Object>

template < typename L, typename ... types >
class Tuple;

namespace tuple_impl {
    template<CDS_uint32 _index, typename T>
    class Node {
    private:
        T value;

    public:
        explicit Node(T const &value) : value(value) {}
        explicit Node(T &&value) : value(std::move(value)) {}

        constexpr auto getBase() const noexcept -> T const & { return this->value; }
        constexpr auto getBase() noexcept -> T & { return this->value; }
    };

    template < CDS_uint32 _index, typename ... types >
    class TupleRecurrentBase {};

    template < CDS_uint32 _index, typename L, typename ... types >
    class TupleRecurrentBase < _index, L , types ... > : public Node<_index, L>, public TupleRecurrentBase<_index + 1, types ...> {
    public:
//        TupleRecurrentBase() noexcept : Node < _index, L > (), TupleRecurrentBase<_index + 1, types...>() { }
        TupleRecurrentBase( TupleRecurrentBase const & ) noexcept = default;

        template<typename ConstructorList, typename ... ConstructorListArgs>
        explicit TupleRecurrentBase(ConstructorList &&arg, ConstructorListArgs &&... args) noexcept :
                Node < _index, ConstructorList > ( std::forward < ConstructorList > (arg) ),
                TupleRecurrentBase< _index + 1, types ... >( std::forward < ConstructorListArgs > ( args ) ...) {}
    };

    template<CDS_uint32 _index, typename L, typename ... args>
    struct typeAt {
        using type = typename typeAt<_index - 1, args ...>::type;
    };

    template<typename L, typename ... args>
    struct typeAt<0, L, args ...> {
        using type = L;
    };

    template < CDS_uint32 _index, typename ... args >
    auto get ( Tuple < args ... > & t ) noexcept -> typename typeAt < _index, args ... >::type {
        return static_cast < Node < _index, typename typeAt < _index, args ...>::type > & >(t).getBase();
    }

    template < CDS_uint32 _index, typename ... args >
    auto get ( Tuple < args ... > const & t ) noexcept -> typename typeAt < _index, args ... >::type {
        return static_cast < Node < _index, typename typeAt < _index, args ... >::type > const &>(t).getBase();
    }

    template < CDS_uint32 _index, typename ... args >
    auto tupleComparison ( Tuple < args ... > const & t1, Tuple < args ... > const & t2 ) noexcept -> bool {
        if constexpr ( _index == 0 ) return get < 0 > ( t1 ) == get < 0 > ( t2 );
        else return get < _index > ( t1 ) == get < _index > ( t2 ) && tupleComparison < _index - 1 > ( t1, t2 );
    }

    template < CDS_uint32 _index, typename ... args >
    auto tupleAssign ( Tuple < args ... > & t1, Tuple < args ... > const & t2 ) noexcept -> void {
        if constexpr ( _index == 0 ) get < 0 > ( t1 ) = get < 0 > ( t2 );
        else {
            get < _index > ( t1 ) = get < _index > ( t2 );
            tupleAssign< _index - 1 > ( t1, t2 );
        }
    }
}

#include <tuple>

template < typename L, typename ... types >
class Tuple : public tuple_impl::TupleRecurrentBase < 0, L, types ... > {
public:
    template < typename ... ConstructorArgs >
    Tuple ( ConstructorArgs && ... args ) noexcept : tuple_impl::TupleRecurrentBase < 0, L, types ... >(  // NOLINT(google-explicit-constructor)
        std::forward < ConstructorArgs > ( args ) ...
    ) {

    }
//
//    template < typename ... ConstructorArgs >
//    ConstructorArgs

    template < int ... > struct seq {};
    template < int n, int ... s > struct gens : gens < n - 1, n - 1, s ... > { };
    template < int ... s > struct gens < 0, s ... > { using type = seq < s ... >; };
//    template < int ... s > auto unpack ( Tuple const & obj ) noexcept {
//        return
//    }

    template < int ... s >
    Tuple( Tuple const & obj, seq < s ... > ) noexcept : tuple_impl::TupleRecurrentBase<0, L, types ... > (
        tuple_impl::get<s>(obj) ...
    ) {

    }

//    Tuple ( Tuple const & obj ) noexcept = default;
    Tuple ( Tuple const & obj ) noexcept : Tuple ( obj, typename gens < sizeof ... ( types ) + 1 >::type () ) {

    }

    template < CDS_uint32 _index >
    auto get () noexcept -> typename tuple_impl::typeAt < _index, L, types ... >::type {
        return tuple_impl::get < _index > ( * this );
    }

    auto operator == ( Tuple const & obj ) const noexcept -> bool {
        return tuple_impl::tupleComparison < sizeof ... (types) > ( * this, obj );
    }

    auto operator != ( Tuple & obj ) noexcept -> bool {
        return ! tuple_impl::tupleComparison < sizeof ... (types) > ( * this, obj );
    }

    [[nodiscard]] auto size () const noexcept -> CDS_uint32 {
        return sizeof ... (types) + 1;
    }
};

template < typename ... ConstructorArguments >
Tuple (ConstructorArguments ... args) -> Tuple < ConstructorArguments ... >;