//
// Created by loghin on 24.01.2021.
//

#ifndef CDS_PAIR_HPP
#define CDS_PAIR_HPP

#include <CDS/Object>
#include <sstream>

template <class K, class V>
class Pair final : public Object {
private:
    K first;
    V second;

public:
    Pair() noexcept = default;
    Pair(const K & k, const V & v) noexcept : first(k), second(v) {  }
    ~Pair () noexcept override = default;

    auto inline getFirst () const noexcept -> K const & { return first; }
    auto inline getSecond() const noexcept -> V const & { return second; }

    auto inline getFirst () noexcept -> K & { return first; }
    auto inline getSecond() noexcept -> V & { return second; }

    auto inline setFirst(K const & k) noexcept -> Pair & {first = k; return * this;}
    auto inline setSecond(V const & v) noexcept -> Pair & {second = v; return * this;}

    auto inline operator == (const Object & o) const noexcept -> bool final {
        if ( this == & o ) return true;
        auto a = dynamic_cast < Pair const * > ( & o );
        if ( a == nullptr ) return false;
        return a->first == first && a->second == second;
    }

    Pair & operator = ( const Pair & o ) noexcept {
        if ( this == & o )
            return * this;

        this->first = o.first;
        this->second = o.second;

        return * this;
    }

    auto inline invert () const noexcept -> Pair <V, K> { return Pair(second, first); }

    [[nodiscard]] auto inline toString() const noexcept -> String final {
        std::stringstream oss;
        if constexpr ( (
                    std::is_integral < K >::value ||
                    std::is_same < K, StringLiteral > ::value ||
                    std::is_same < K, String > ::value ||
                    std::is_base_of < Object, K >::value ||
                    std::is_same < K , std::string > ::value
                ) && (
                    std::is_integral < V > ::value ||
                    std::is_same < V, StringLiteral >::value,
                    std::is_same < V, String >::value,
                    std::is_base_of < Object, V >::value,
                    std::is_same < V, std::string > ::value
                )
        )
            oss << "( k = " << first << ", v = " << second << " )";
        return String(oss.str());
    }

    [[nodiscard]] auto copy () const noexcept -> Pair * override {
        return new Pair( * this );
    }
};


#endif //CDS_PAIR_HPP
