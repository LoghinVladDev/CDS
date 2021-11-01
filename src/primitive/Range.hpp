//
// Created by loghin on 27.01.2021.
//

#ifndef CDS_RANGE_HPP
#define CDS_RANGE_HPP

template < typename C >
class Sequence;

#include <CDS/Object>
#include <CDS/Pair>
#include <CDS/Memory>

class Range : public Object {
private:
    Index _s;
    Index _f;
    bool  _rev;
public:
    using ElementType = Index;

    class Iterator {
    private:
        Index i;
        bool  reversed;

    public:
        constexpr explicit Iterator(Index start, bool rev = false) : i(start), reversed(rev) {}

        __CDS_NoDiscard constexpr auto value () const noexcept -> Index { return this->i; }
        __CDS_cpplang_NonConstConstexprMemberFunction auto next () noexcept -> Iterator & { reversed ? --i : ++i; return * this; }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () -> Iterator & { reversed ? --i : ++i; return * this; }
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) -> Iterator { auto copy = * this; ++(*this); return copy; }
        constexpr auto operator != ( Iterator const & o ) const noexcept -> bool { return i != o.i; }
        constexpr auto operator == ( Iterator const & o ) const noexcept -> bool { return i == o.i; }

        constexpr Index operator *() const noexcept { return i; }
    };

    using ConstIterator = Iterator;

    constexpr explicit Range(Index s, Index f) : _s(s), _f(f), _rev(s > f) { }
    constexpr explicit Range(Index f) : _s(0), _f(f), _rev(0 > f) { }

    template < typename T, typename std :: enable_if < std :: is_integral < T > :: type :: value, int > :: type = 0 >
    constexpr explicit Range(Pair < T, T > const & p) noexcept : _s(p.first()), _f(p.second()), _rev(p.first() > p.second()) { }

    constexpr Range(Range const &) noexcept = default;
    constexpr Range(Range &&) noexcept = default;
    __CDS_cpplang_ConstexprDestructor ~Range() noexcept override = default;

    __CDS_NoDiscard constexpr auto begin() const noexcept -> Iterator { return Iterator(_s, _rev); }
    __CDS_NoDiscard constexpr auto end() const noexcept -> Iterator { return Iterator(_f, _rev); }
    __CDS_NoDiscard constexpr auto cbegin() const noexcept -> Iterator { return this->begin(); }
    __CDS_NoDiscard constexpr auto cend() const noexcept -> Iterator { return this->end(); }

    __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto hash() const noexcept -> Index final { return _s + _f; }
    __CDS_NoDiscard __CDS_OptimalInline auto toString () const noexcept -> String final { return String("( ") + _s + " ... " + _f + " )";  }

    __CDS_NoDiscard __CDS_OptimalInline auto copy () const noexcept -> Range * override {
        return Memory :: instance().create < Range > ( * this );
    }

    __CDS_NoDiscard auto sequence () & noexcept -> Sequence < Range >;
    __CDS_NoDiscard auto sequence () && noexcept -> Sequence < Range >;
    __CDS_NoDiscard auto sequence () const & noexcept -> Sequence < const Range >;
    __CDS_NoDiscard auto sequence () const && noexcept -> Sequence < const Range >;
};

__CDS_RegisterParseType(Range)

#endif //CDS_RANGE_HPP
