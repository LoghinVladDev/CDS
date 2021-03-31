//
// Created by loghin on 27.01.2021.
//

#ifndef CDS_RANGE_HPP
#define CDS_RANGE_HPP


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
        constexpr auto operator ++ () -> Iterator & { reversed ? --i : ++i; return * this; }
        constexpr auto operator ++ (int) -> Iterator { auto copy = * this; ++(*this); return copy; }
        constexpr auto operator != ( Iterator const & o ) const noexcept -> bool { return i != o.i; }
        constexpr auto operator == ( Iterator const & o ) const noexcept -> bool { return i == o.i; }
        Index operator *() const noexcept { return i; }
    };

    explicit Range(Index s, Index f) : _s(s), _f(f), _rev(s > f) { }
    explicit Range(Index f) : _s(0), _f(f), _rev(0 > f) { }
    ~Range() noexcept final = default;

    [[nodiscard]] constexpr auto begin() const noexcept -> Iterator { return Iterator(_s, _rev); }
    [[nodiscard]] constexpr auto end() const noexcept -> Iterator { return Iterator(_f, _rev); }

    [[nodiscard]] auto hash() const noexcept -> Index final { return _s + _f; }
    [[nodiscard]] auto toString () const noexcept -> String final { return String("( ") + _s + " ... " + _f + " )";  }

    [[nodiscard]] auto copy () const noexcept -> Range * override {
        return new Range( * this );
    }
};


#endif //CDS_RANGE_HPP
