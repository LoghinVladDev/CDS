//
// Created by loghin on 27.01.2021.
//

#ifndef CDS_RANGE_HPP
#define CDS_RANGE_HPP


//template < typename T >
//class View;

template < typename C >
class Sequence;

#include <CDS/Object>
class Range final : public Object {
private:
    Index _s;
    Index _f;
    bool  _rev;
public:
    class Iterator final {
    private:
        Index i;
        bool  reversed;

    public:
        constexpr explicit Iterator(Index start, bool rev = false) : i(start), reversed(rev) {}

        constexpr auto value () const noexcept -> Index { return this->i; }
        constexpr auto next () noexcept -> Iterator & { reversed ? --i : ++i; return * this; }

        constexpr auto operator ++ () -> Iterator & { reversed ? --i : ++i; return * this; }
        constexpr auto operator ++ (int) -> Iterator { auto copy = * this; ++(*this); return copy; }
        constexpr auto operator != ( Iterator const & o ) const noexcept -> bool { return i != o.i; }
        constexpr auto operator == ( Iterator const & o ) const noexcept -> bool { return i == o.i; }
        constexpr Index operator *() const noexcept { return i; }
    };

    using ConstIterator = Iterator;

    explicit Range(Index s, Index f) : _s(s), _f(f), _rev(s > f) { }
    explicit Range(Index f) : _s(0), _f(f), _rev(0 > f) { }
    explicit Range(Pair < Index, Index > const & p) : _s(p.getFirst()), _f(p.getSecond()), _rev(0 > p.getFirst()) { }
    Range(Range const &) noexcept = default;
    Range(Range &&) noexcept = default;
    ~Range() noexcept final = default;

    [[nodiscard]] constexpr auto begin() const noexcept -> Iterator { return Iterator(_s, _rev); }
    [[nodiscard]] constexpr auto end() const noexcept -> Iterator { return Iterator(_f, _rev); }
    [[nodiscard]] constexpr auto cbegin() const noexcept -> Iterator { return this->begin(); }
    [[nodiscard]] constexpr auto cend() const noexcept -> Iterator { return this->end(); }

    [[nodiscard]] auto hash() const noexcept -> Index final { return _s + _f; }
    [[nodiscard]] auto toString () const noexcept -> String final { return String("( ") + _s + " ... " + _f + " )";  }

    [[nodiscard]] auto copy () const noexcept -> Range * override {
        return new Range( * this );
    }

//    auto view () const noexcept -> View < Range >;
    auto sequence () const noexcept -> Sequence < const Range >;
    auto sequence () noexcept -> Sequence < Range >;
};

//#include <CDS/View>
//auto Range::view() const noexcept -> View < Range > {
//    return View(*this);
//}

#include <CDS/Sequence>

inline auto Range::sequence() noexcept -> Sequence<Range> {
    return Sequence(*this);
}

inline auto Range::sequence() const noexcept -> Sequence<const Range> {
    return Sequence(*this);
}

#endif //CDS_RANGE_HPP
