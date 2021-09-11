//
// Created by loghin on 27.01.2021.
//

#ifndef CDS_RANGE_HPP
#define CDS_RANGE_HPP

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

        __CDS_NoDiscard constexpr auto value () const noexcept -> Index { return this->i; }
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

    __CDS_NoDiscard constexpr auto begin() const noexcept -> Iterator { return Iterator(_s, _rev); }
    __CDS_NoDiscard constexpr auto end() const noexcept -> Iterator { return Iterator(_f, _rev); }
    __CDS_NoDiscard constexpr auto cbegin() const noexcept -> Iterator { return this->begin(); }
    __CDS_NoDiscard constexpr auto cend() const noexcept -> Iterator { return this->end(); }

    __CDS_NoDiscard auto hash() const noexcept -> Index final { return _s + _f; }
    __CDS_NoDiscard auto toString () const noexcept -> String final { return String("( ") + _s + " ... " + _f + " )";  }

    __CDS_NoDiscard auto copy () const noexcept -> Range * override {
        return new Range( * this );
    }

    __CDS_NoDiscard auto sequence () const noexcept -> Sequence < const Range >;
    __CDS_NoDiscard auto sequence () noexcept -> Sequence < Range >;
};

#include <CDS/Sequence>

inline auto Range::sequence() noexcept -> Sequence<Range> {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
}

inline auto Range::sequence() const noexcept -> Sequence<const Range> {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
}

#endif //CDS_RANGE_HPP
