//
// Created by loghin on 24.01.2021.
//

#ifndef CDS_PAIR_HPP
#define CDS_PAIR_HPP

#include <CDS/Object>
#include <sstream>
#include <CDS/Traits>
#include <CDS/Memory>

namespace cds {

    template <class K, class V>
    class Pair : public Object { // NOLINT(clion-misra-cpp2008-14-5-2)
    public:
        using Key __CDS_MaybeUnused = K;
        using Value                 = V;

    private:
        K _first;
        V _second;

    public:
        template < typename K1 = K, typename V1 = V, EnableIf < Type < K1 > :: isFundamental && Type < V1 > :: isFundamental > = 0 >
        constexpr Pair () noexcept :
                _first(), _second() {

        }

        template < typename K1 = K, typename V1 = V, EnableIf < Type < K1 > :: defaultConstructible && Type < V1 > :: defaultConstructible && ! Type < K1 > :: isFundamental && ! Type < V1 > :: isFundamental > = 0 > // NOLINT(clion-misra-cpp2008-5-3-1)
        constexpr Pair () noexcept(noexcept(K()) && noexcept(V())) :
                _first(),
                _second() {

        }

        template < typename K1 = K, typename V1 = V, EnableIf < Type < K1 > :: isFundamental && ! Type < V1 > :: isFundamental && Type < V1 > :: defaultConstructible > = 0 > // NOLINT(clion-misra-cpp2008-5-3-1)
        constexpr Pair () noexcept(noexcept(V())) :
                _first(),
                _second() {

        }

        template < typename K1 = K, typename V1 = V, EnableIf < Type < V1 > :: isFundamental && ! Type < K1 > :: isFundamental && Type < K1 > :: defaultConstructible > = 0 > // NOLINT(clion-misra-cpp2008-5-3-1)
        constexpr Pair () noexcept(noexcept(K())) :
                _first(),
                _second() {

        }


        template < typename K1 = K, typename V1 = V, EnableIf < Type < K1 > :: copyConstructible && Type < V1 > :: copyConstructible > = 0 >
        constexpr Pair ( Pair const & obj ) noexcept(noexcept(K(obj._first)) && noexcept(V(obj._second))) : // NOLINT(google-explicit-constructor)
                _first(obj._first),
                _second(obj._second) {

        }

        template < typename K1 = K, typename V1 = V, EnableIf < Type < K1 > :: moveConstructible && Type < V1 > :: moveConstructible > = 0 >
        constexpr Pair ( Pair && obj ) noexcept(noexcept(K(std::move(obj._first))) && noexcept(V(std::move(obj._second)))) : // NOLINT(google-explicit-constructor)
                _first(std::move(obj._first)),
                _second(std::move(obj._second)) {

        }


        template < typename K1 = K, typename V1 = V, EnableIf < Type < K1 > :: isFundamental && Type < V1 > :: isFundamental > = 0 >
        constexpr Pair ( K first, V second ) noexcept :
                _first(first),
                _second(second) {

        }

        template < typename K1 = K, typename V1 = V, EnableIf < Type < K1 > :: copyConstructible && Type < V1 > :: copyConstructible && ! Type < K1 > :: isFundamental && ! Type < V1 > :: isFundamental > = 0 > // NOLINT(clion-misra-cpp2008-5-3-1)
        constexpr Pair ( K const & first, V const & second ) noexcept(noexcept(K(first)) && noexcept(V(second))) :
                _first(first), _second(second) {

        }

        template < typename K1 = K, typename V1 = V, EnableIf < Type < K1 > :: moveConstructible && Type < V1 > :: moveConstructible && ! Type < K1 > :: isFundamental && ! Type < V1 > :: isFundamental > = 0 > // NOLINT(clion-misra-cpp2008-5-3-1)
        constexpr Pair ( K && first, V && second ) noexcept(noexcept(K(std::forward < K > (first))) && noexcept(V(std::forward < V > (second)))) :
                _first(std::forward < K && > (first)), _second(std::forward < V && > (second)) {

        }

        template < typename K1 = K, typename V1 = V, EnableIf < Type < K1 > :: isFundamental && ! Type < V1 > :: isFundamental && Type < V1 > :: copyConstructible > = 0 > // NOLINT(clion-misra-cpp2008-5-3-1)
        constexpr Pair ( K first, V const & second ) noexcept(noexcept(V(second))) :
                _first(first), _second(second) {

        }

        template < typename K1 = K, typename V1 = V, EnableIf < Type < K1 > :: isFundamental && ! Type < V1 > :: isFundamental && Type < V1 > :: moveConstructible > = 0 > // NOLINT(clion-misra-cpp2008-5-3-1)
        constexpr Pair ( K first, V && second ) noexcept(noexcept(V(std::forward < V && >(second)))) :
                _first(first),
                _second(std::forward < V && >(second)) {

        }

        template < typename K1 = K, typename V1 = V, EnableIf < ! Type < K1 > :: isFundamental && Type < V1 > :: isFundamental && Type < K1 > :: copyConstructible > = 0 > // NOLINT(clion-misra-cpp2008-5-3-1)
        constexpr Pair ( K const & first, V second ) noexcept(noexcept(K(first))) :
                _first(first),
                _second(second) {

        }

        template < typename K1 = K, typename V1 = V, EnableIf < ! Type < K1 > :: isFundamental && Type < K1 > :: copyConstructible && ! Type < V1 > :: isFundamental && Type < V1 > :: moveConstructible > = 0 > // NOLINT(clion-misra-cpp2008-5-3-1)
        constexpr Pair ( K const & first, V && second ) noexcept(noexcept(K(first)) && noexcept(V(std::forward < V && > (second)))) :
                _first(first),
                _second(std::forward < V && >(second)) {

        }

        template < typename K1 = K, typename V1 = V, EnableIf < ! Type < K1 > :: isFundamental && Type < K1 > :: moveConstructible && Type < V1 > :: isFundamental > = 0 > // NOLINT(clion-misra-cpp2008-5-3-1)
        constexpr Pair ( K && first, V second ) noexcept(noexcept(K(std::forward < K && >(first)))) :
                _first(std::forward < K && >(first)),
                _second(second) {

        }

        template < typename K1 = K, typename V1 = V, EnableIf < ! Type < K1 > :: isFundamental && Type < K1 > :: moveConstructible && ! Type < V1 > :: isFundamental && Type < V1 > :: copyConstructible > = 0 > // NOLINT(clion-misra-cpp2008-5-3-1)
        constexpr Pair ( K && first, V const & second ) noexcept(noexcept(K(std::forward < K && >(first))) && noexcept(V(second))) :
                _first(std::forward < K && >(first)),
                _second(second) {

        }


        __CDS_cpplang_ConstexprDestructor ~Pair() noexcept override = default;

        __CDS_NoDiscard constexpr auto getFirst () const noexcept -> K const & {
            return _first;
        }

        __CDS_NoDiscard constexpr auto getSecond() const noexcept -> V const & {
            return _second;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto getFirst () noexcept -> K & {
            return _first;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto getSecond() noexcept -> V & {
            return _second;
        }

        __CDS_NoDiscard constexpr auto first () const noexcept -> K const & {
            return this->_first;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto first () noexcept -> K & {
            return this->_first;
        }

        __CDS_NoDiscard constexpr auto second () const noexcept -> V const & {
            return this->_second;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto second () noexcept -> V & {
            return this->_second;
        }

        __CDS_MaybeUnused auto __CDS_OptimalInline setFirst(K const & first) noexcept -> Pair & {
            this->_first = first;
            return * this;
        }

        __CDS_MaybeUnused auto __CDS_OptimalInline setSecond(V const & second) noexcept -> Pair & {
            this->_second = second;
            return * this;
        }

        constexpr auto operator == ( Pair const & pair ) const noexcept -> bool {
            return
                this == & pair || (
                        Type<K>::compare(this->_first, pair._first) &&
                        Type<V>::compare(this->_second, pair._second)
                );
        }

        constexpr auto operator != ( Pair const & pair ) const noexcept -> bool {
            return ! this->operator==(pair); // NOLINT(clion-misra-cpp2008-5-3-1)
        }

        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto equals ( Object const & object ) const noexcept -> bool override {
            if ( this == & object ) {
                return true;
            }

            auto pPair = dynamic_cast < Pair < K, V > const * > ( & object );
            if (pPair == nullptr ) {
                return false;
            }

            return this->operator==(*pPair);
        }

        template < typename K1 = K, typename V1 = V, EnableIf < Type < K1 > :: copyAssignable && Type < V1 > :: copyAssignable > = 0 >
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( Pair const & pair ) noexcept -> Pair & {
            if ( this == & pair ) {
                return * this;
            }

            this->_first = pair._first;
            this->_second = pair._second;

            return * this;
        }

        template < typename K1 = K, typename V1 = V, EnableIf < Type < K1 > :: moveAssignable && Type < V1 > :: moveAssignable > = 0 >
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( Pair && pair ) noexcept -> Pair & {
            if ( this == & pair ) {
                return * this;
            }

            this->_first = std :: move (pair._first );
            this->_second = std :: move (pair._second );

            return * this;
        }

        __CDS_MaybeUnused __CDS_cpplang_ConstexprDestructor auto invert () const noexcept -> Pair <V, K> {
            return Pair(this->_second, this->_first);
        }

        __CDS_NoDiscard __CDS_OptionalInline auto toString() const noexcept -> String final {
            std::stringstream oss;

            Type < V > :: streamPrint ( ( Type < K > :: streamPrint ( ( oss << "( k = " ), this->first() ) << ", v = " ), this->second() ) << " )";
             return {oss.str()};
        }


        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto copy () const noexcept -> Pair * override {
            return Memory :: instance ().create < Pair > ( * this );
        }
    };

}
#if __CDS_cpplang_CTAD_available == true

namespace cds {

    template < typename K, typename V >
    Pair(K, V) -> Pair<K, V>;

}

#endif

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility {

        template<typename K, typename V>
        struct TypeParseTraits<Pair<K, V>> {
            constexpr static StringLiteral name = "Pair";
        };

    }
}

#endif //CDS_PAIR_HPP
