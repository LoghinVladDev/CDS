//
// Created by loghin on 24.01.2021.
//

#ifndef CDS_PAIR_HPP
#define CDS_PAIR_HPP

#include <CDS/Object>
#include <sstream>
#include <CDS/Traits>

template <class K, class V>
class Pair final : public Object {
public:
    using Key __CDS_MaybeUnused = K;
    using Value                 = V;

private:
    K _first;
    V _second;

public:
//    template < typename K1 = K, typename V1 = V, typename = typename std :: enable_if < std :: is_default_constructible < K1 > :: type :: value && std :: is_default_constructible < V1 > :: type :: value, int > :: type >
//    Pair () noexcept(noexcept(K()) && noexcept(noexcept(V()))) : _first(), _second() {}
//    Pair(const K & k, const V & v) noexcept(noexcept(K(k)) && noexcept(V(v))) : _first(k), _second(v) {  }
//    Pair(Pair const & obj) noexcept {
//        this->_first = obj._first;
//        this->_second = obj._second;
//    }
//
//    Pair(Pair &&) noexcept = default;
//    ~Pair () noexcept override = default;

    template < typename K1 = K, typename V1 = V, typename std :: enable_if < Type < K1 > :: defaultConstructible && Type < V1 > :: defaultConstructible, int > :: type = 0 >
    Pair () noexcept(noexcept(K()) && noexcept(V())) : _first(), _second() {}

    template < typename K1 = K, typename V1 = V, typename std :: enable_if < Type < K1 > :: copyConstructible && Type < V1 > :: copyConstructible, int > :: type = 0 >
    Pair ( Pair const & obj ) noexcept(noexcept(K(obj._first)) && noexcept(V(obj._second))) : _first(obj._first), _second(obj._second) { } // NOLINT(google-explicit-constructor)

    template < typename K1 = K, typename V1 = V, typename std :: enable_if < Type < K1 > :: moveConstructible && Type < V1 > :: moveConstructible, int > :: type = 0 >
    Pair ( Pair && obj ) noexcept(noexcept(K(std::move(obj._first))) && noexcept(V(std::move(obj._second)))) : _first(std::move(obj._first)), _second(std::move(obj._second)) { } // NOLINT(google-explicit-constructor)

    template < typename K1 = K, typename V1 = V, typename std :: enable_if < Type < K1 > :: copyConstructible && Type < V1 > :: copyConstructible, int > :: type = 0 >
    Pair ( K const & first, V const & second ) noexcept(noexcept(K(first)) && noexcept(V(second))) : _first(first), _second(second) { }

    template < typename K1 = K, typename V1 = V, typename std :: enable_if < Type < K1 > :: copyConstructible && Type < V1 > :: moveConstructible, int > :: type = 0 >
    Pair ( K const & first, V && second ) noexcept(noexcept(K(first)) && noexcept(V(std::move(second)))) : _first(first), _second(std::move(second)) { }

    template < typename K1 = K, typename V1 = V, typename std :: enable_if < Type < K1 > :: moveConstructible && Type < V1 > :: copyConstructible, int > :: type = 0 >
    Pair ( K && first, V const & second ) noexcept(noexcept(K(std::move(first))) && noexcept(V(second))) : _first(std::move(first)), _second(second) { }

    template < typename K1 = K, typename V1 = V, typename std :: enable_if < Type < K1 > :: moveConstructible && Type < V1 > :: moveConstructible, int > :: type = 0 >
    Pair ( K && first, V && second ) noexcept(noexcept(K(std::move(first))) && noexcept(V(std::move(second)))) : _first(std::move(first)), _second(std::move(second)) { }

    auto constexpr getFirst () const noexcept -> K const & { return _first; }
    auto constexpr getSecond() const noexcept -> V const & { return _second; }

    auto __CDS_cpplang_NonConstConstexprMemberFunction getFirst () noexcept -> K & { return _first; }
    auto __CDS_cpplang_NonConstConstexprMemberFunction getSecond() noexcept -> V & { return _second; }

    constexpr auto first () const noexcept -> K const & { return this->_first; }
    __CDS_cpplang_NonConstConstexprMemberFunction auto first () noexcept -> K & { return this->_first; }

    constexpr auto second () const noexcept -> V const & { return this->_second; }
    __CDS_cpplang_NonConstConstexprMemberFunction auto second () noexcept -> V & { return this->_second; }

    __CDS_MaybeUnused auto inline setFirst(K const & k) noexcept -> Pair & {_first = k; return * this;}
    __CDS_MaybeUnused auto inline setSecond(V const & v) noexcept -> Pair & {_second = v; return * this;}

    auto inline operator == ( Pair const & o ) const noexcept -> bool {
        if ( this == & o ) return true;
        return
            Type < K > :: compare( this->_first, o._first ) &&
            Type < V > :: compare( this->_second, o._second );
    }

    auto inline operator != ( Pair const & o ) const noexcept -> bool {
        if ( this == & o ) return false;

        return ! this->operator==(o);
    }

    __CDS_NoDiscard auto equals ( Object const & o ) const noexcept -> bool override {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype (this) > ( & o );
        if ( p == nullptr ) return false;

        return this->operator==(*p);
    }

    Pair & operator = ( Pair const & o ) noexcept {
        if ( this == & o )
            return * this;

        this->_first = o._first;
        this->_second = o._second;

        return * this;
    }

    __CDS_MaybeUnused auto inline invert () const noexcept -> Pair <V, K> { return Pair(_second, _first); }

    __CDS_NoDiscard auto inline toString() const noexcept -> String final {
        std::stringstream oss;
        if __CDS_cpplang_IfConstexpr ( (
                    std::is_integral < K >::value               ||
                    std::is_same < K, StringLiteral > ::value   ||
                    std::is_same < K, String > ::value          ||
                    std::is_base_of < Object, K >::value        ||
                    std::is_same < K , std::string > ::value
                ) && (
                    std::is_integral < V > ::value              ||
                    std::is_same < V, StringLiteral >::value    ||
                    std::is_same < V, String >::value           ||
                    std::is_base_of < Object, V >::value        ||
                    std::is_same < V, std::string > ::value
                )
        )
            oss << "( k = " << _first << ", v = " << _second << " )";
        return {oss.str()};
    }


    __CDS_NoDiscard auto copy () const noexcept -> Pair * override {
        if __CDS_cpplang_IfConstexpr ( std::is_copy_constructible < Pair > :: type::value )
            return new Pair( * this );
        else
            return nullptr;
    }
};

#if __CDS_cpplang_CTAD_available == true

template < typename K, typename V >
Pair(K, V) -> Pair<K, V>;
template < typename K, typename V >
Pair(K const &, V) -> Pair<K const, V>;
template < typename K, typename V >
Pair(K, V const &) -> Pair<K, V const>;
template < typename K, typename V >
Pair(K const &, V const &) -> Pair <K const, V const>;

#endif

#endif //CDS_PAIR_HPP
