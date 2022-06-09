//
// Created by loghin on 27.01.2021.
//

#ifndef CDS_RANGE_HPP
#define CDS_RANGE_HPP

namespace cds {

    template < typename C >
    class Sequence;

}

#include <CDS/Object>
#include <CDS/Pair>
#include <CDS/Memory>

namespace cds {

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
            constexpr explicit Iterator(Index start, bool rev = false) noexcept :
                    i(start),
                    reversed(rev) {

            }

            __CDS_NoDiscard constexpr auto value () const noexcept -> Index { return this->i; }
            __CDS_cpplang_NonConstConstexprMemberFunction auto next () noexcept -> Iterator & {
                reversed ? --i : ++i;
                return * this;
            }

            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () -> Iterator & {
                return this->next();
            }

            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) -> Iterator {
                auto copy = * this;
                (void) this->next();
                return copy;
            }

            constexpr auto operator != ( Iterator const & iterator ) const noexcept -> bool {
                return i != iterator.i;
            }

            constexpr auto operator == ( Iterator const & iterator ) const noexcept -> bool {
                return i == iterator.i;
            }

            constexpr Index operator *() const noexcept {
                return i;
            }
        };

        using ConstIterator = Iterator;

        constexpr explicit Range(Index start, Index finish) noexcept :
                _s(start),
                _f(finish),
                _rev(start > finish) {

        }

        constexpr explicit Range(Index finish) noexcept :
                _s(0),
                _f(finish),
                _rev(0 > finish) {

        }

        template < typename T, meta :: EnableIf < meta :: isIntegral < T > () > = 0 >
        constexpr explicit Range(Pair < T, T > const & pair) noexcept :
                _s(pair.first()),
                _f(pair.second()),
                _rev(pair.first() > pair.second()) {

        }

        constexpr Range(Range const &) noexcept = default;
        constexpr Range(Range &&) noexcept = default;
        __CDS_cpplang_ConstexprDestructor ~Range() noexcept override = default;

        __CDS_NoDiscard constexpr auto begin() const noexcept -> Iterator {
            return Iterator(_s, _rev);
        }

        __CDS_NoDiscard constexpr auto end() const noexcept -> Iterator {
            return Iterator(_f, _rev);
        }

        __CDS_NoDiscard constexpr auto cbegin() const noexcept -> Iterator {
            return this->begin();
        }

        __CDS_NoDiscard constexpr auto cend() const noexcept -> Iterator {
            return this->end();
        }

        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto hash() const noexcept -> Index final {
            return _s + _f;
        }

        __CDS_NoDiscard __CDS_OptimalInline auto toString () const noexcept -> String final {
            return
                "( "_s +
                _s +
                " ... " +
                _f +
                " )";
        }

        __CDS_NoDiscard constexpr auto from () const noexcept -> Index {
            return this->_s;
        }

        __CDS_NoDiscard constexpr auto to () const noexcept -> Index {
            return this->_f;
        }

        __CDS_NoDiscard auto sequence () & noexcept -> Sequence < Range >;
        __CDS_NoDiscard auto sequence () && noexcept -> Sequence < Range >;
        __CDS_NoDiscard auto sequence () const & noexcept -> Sequence < const Range >;
        __CDS_NoDiscard auto sequence () const && noexcept -> Sequence < const Range >;
    };

}

__CDS_Meta_RegisterParseType(Range) // NOLINT(clion-misra-cpp2008-8-0-1)

#endif //CDS_RANGE_HPP
