//
// Created by loghin on 24.01.2021.
//

#ifndef CDS_PAIR_HPP
#define CDS_PAIR_HPP

#include <CDS/Object>
#include <sstream>
#include <CDS/Traits>

template <class K, class V>
class Pair : public Object {
public:
    using Key __CDS_MaybeUnused = K;
    using Value                 = V;

private:
    K _first;
    V _second;

public:
    template < typename K1 = K, typename V1 = V, EnableIf < Type < K1 > :: isFundamental && Type < V1 > :: isFundamental > = 0 >
    constexpr Pair () noexcept : _first(), _second() { }

    template < typename K1 = K, typename V1 = V, EnableIf < Type < K1 > :: defaultConstructible && Type < V1 > :: defaultConstructible && ! Type < K1 > :: isFundamental && ! Type < V1 > :: isFundamental > = 0 >
    constexpr Pair () noexcept(noexcept(K()) && noexcept(V())) : _first(), _second() {}

    template < typename K1 = K, typename V1 = V, EnableIf < Type < K1 > :: isFundamental && ! Type < V1 > :: isFundamental && Type < V1 > :: defaultConstructible > = 0 >
    constexpr Pair () noexcept(noexcept(V())) : _first(), _second() {}

    template < typename K1 = K, typename V1 = V, EnableIf < Type < V1 > :: isFundamental && ! Type < K1 > :: isFundamental && Type < K1 > :: defaultConstructible > = 0 >
    constexpr Pair () noexcept(noexcept(K())) : _first(), _second() {}


    template < typename K1 = K, typename V1 = V, EnableIf < Type < K1 > :: copyConstructible && Type < V1 > :: copyConstructible > = 0 >
    constexpr Pair ( Pair const & obj ) noexcept(noexcept(K(obj._first)) && noexcept(V(obj._second))) : _first(obj._first), _second(obj._second) { } // NOLINT(google-explicit-constructor)

    template < typename K1 = K, typename V1 = V, EnableIf < Type < K1 > :: moveConstructible && Type < V1 > :: moveConstructible > = 0 >
    constexpr Pair ( Pair && obj ) noexcept(noexcept(K(std::move(obj._first))) && noexcept(V(std::move(obj._second)))) : _first(std::move(obj._first)), _second(std::move(obj._second)) { } // NOLINT(google-explicit-constructor)


    template < typename K1 = K, typename V1 = V, EnableIf < Type < K1 > :: isFundamental && Type < V1 > :: isFundamental > = 0 >
    constexpr Pair ( K first, V second ) noexcept : _first(first), _second(second) { }

    template < typename K1 = K, typename V1 = V, EnableIf < Type < K1 > :: copyConstructible && Type < V1 > :: copyConstructible && ! Type < K1 > :: isFundamental && ! Type < V1 > :: isFundamental > = 0 >
    constexpr Pair ( K const & first, V const & second ) noexcept(noexcept(K(first)) && noexcept(V(second))) : _first(first), _second(second) { }

    template < typename K1 = K, typename V1 = V, EnableIf < Type < K1 > :: moveConstructible && Type < V1 > :: moveConstructible && ! Type < K1 > :: isFundamental && ! Type < V1 > :: isFundamental > = 0 >
    constexpr Pair ( K && first, V && second ) noexcept(noexcept(K(std::move(first))) && noexcept(V(std::move(second)))) : _first(std::move(first)), _second(std::move(second)) { }

    template < typename K1 = K, typename V1 = V, EnableIf < Type < K1 > :: isFundamental && ! Type < V1 > :: isFundamental && Type < V1 > :: copyConstructible > = 0 >
    constexpr Pair ( K first, V const & second ) noexcept(noexcept(V(second))) : _first(first), _second(second) { }

    template < typename K1 = K, typename V1 = V, EnableIf < Type < K1 > :: isFundamental && ! Type < V1 > :: isFundamental && Type < V1 > :: moveConstructible > = 0 >
    constexpr Pair ( K first, V && second ) noexcept(noexcept(V(std::move(second)))) : _first(first), _second(std::move(second)) { }

    template < typename K1 = K, typename V1 = V, EnableIf < ! Type < K1 > :: isFundamental && Type < V1 > :: isFundamental && Type < K1 > :: copyConstructible > = 0 >
    constexpr Pair ( K const & first, V second ) noexcept(noexcept(K(first))) : _first(first), _second(second) { }

    template < typename K1 = K, typename V1 = V, EnableIf < ! Type < K1 > :: isFundamental && Type < K1 > :: copyConstructible && ! Type < V1 > :: isFundamental && Type < V1 > :: moveConstructible > = 0 >
    constexpr Pair ( K const & first, V && second ) noexcept(noexcept(K(first)) && noexcept(V(std::move(second)))) : _first(first), _second(std::move(second)) { }

    template < typename K1 = K, typename V1 = V, EnableIf < ! Type < K1 > :: isFundamental && Type < K1 > :: moveConstructible && Type < V1 > :: isFundamental > = 0 >
    constexpr Pair ( K && first, V second ) noexcept(noexcept(K(std::move(first)))) : _first(std::move(first)), _second(second) { }

    template < typename K1 = K, typename V1 = V, EnableIf < ! Type < K1 > :: isFundamental && Type < K1 > :: moveConstructible && ! Type < V1 > :: isFundamental && Type < V1 > :: copyConstructible > = 0 >
    constexpr Pair ( K && first, V const & second ) noexcept(noexcept(K(std::move(first))) && noexcept(V(second))) : _first(std::move(first)), _second(second) { }


    __CDS_cpplang_ConstexprDestructor ~Pair() noexcept override = default;

    constexpr auto getFirst () const noexcept -> K const & { return _first; }
    constexpr auto getSecond() const noexcept -> V const & { return _second; }

    __CDS_cpplang_NonConstConstexprMemberFunction auto getFirst () noexcept -> K & { return _first; }
    __CDS_cpplang_NonConstConstexprMemberFunction auto getSecond() noexcept -> V & { return _second; }

    constexpr auto first () const noexcept -> K const & { return this->_first; }
    __CDS_cpplang_NonConstConstexprMemberFunction auto first () noexcept -> K & { return this->_first; }

    constexpr auto second () const noexcept -> V const & { return this->_second; }
    __CDS_cpplang_NonConstConstexprMemberFunction auto second () noexcept -> V & { return this->_second; }

    __CDS_MaybeUnused auto __CDS_OptimalInline setFirst(K const & k) noexcept -> Pair & {_first = k; return * this;}
    __CDS_MaybeUnused auto __CDS_OptimalInline setSecond(V const & v) noexcept -> Pair & {_second = v; return * this;}

    constexpr auto operator == ( Pair const & o ) const noexcept -> bool {
        return this == & o || (Type<K>::compare(this->_first, o._first) && Type<V>::compare(this->_second, o._second));
    }

    constexpr auto operator != ( Pair const & o ) const noexcept -> bool {
        return ! this->operator==(o);
    }

    __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto equals ( Object const & o ) const noexcept -> bool override {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype (this) > ( & o );
        if ( p == nullptr ) return false;

        return this->operator==(*p);
    }

    template < typename K1 = K, typename V1 = V, EnableIf < Type < K1 > :: copyAssignable && Type < V1 > :: copyAssignable > = 0 >
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( Pair const & o ) noexcept -> Pair & {
        if ( this == & o )
            return * this;

        this->_first = o._first;
        this->_second = o._second;

        return * this;
    }

    template < typename K1 = K, typename V1 = V, EnableIf < Type < K1 > :: moveAssignable && Type < V1 > :: moveAssignable > = 0 >
    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( Pair && o ) noexcept -> Pair & {
        if ( this == & o )
            return * this;

        this->_first = std :: move ( o._first );
        this->_second = std :: move ( o._second );

        return * this;
    }

    __CDS_MaybeUnused __CDS_cpplang_ConstexprDestructor auto invert () const noexcept -> Pair <V, K> { return Pair(_second, _first); }

    __CDS_NoDiscard __CDS_OptionalInline auto toString() const noexcept -> String final {
        std::stringstream oss;

        Type < V > :: streamPrint ( ( Type < K > :: streamPrint ( ( oss << "( k = " ), this->first() ) << ", v = " ), this->second() ) << " )";
         return {oss.str()};
    }


    __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto copy () const noexcept -> Pair * override {
        return new Pair( * this );
    }
};

#if __CDS_cpplang_CTAD_available == true

template < typename K, typename V >
Pair(K, V) -> Pair<K, V>;

#endif

namespace Utility {
    template<typename K, typename V>
    struct TypeParseTraits<Pair<K, V>> {
        constexpr static StringLiteral name = "Pair";
    };
}

#endif //CDS_PAIR_HPP
