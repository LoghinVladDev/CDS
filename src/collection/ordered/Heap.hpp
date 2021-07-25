//
// Created by loghin on 24.07.2021.
//

#ifndef CDS_HEAP_HPP
#define CDS_HEAP_HPP

#include <CDS/Array>

template < typename T, typename PriorityFunction = std::less<> >
class Heap final : public List < T > {
private:
    Array < T > _elements;

public:

    class Iterator;
    class ConstIterator;

    Heap () noexcept = default;
    Heap (Heap const &) noexcept = default;
    Heap (Heap &&) noexcept = default;

    Heap (
        typename Collection < T > :: Iterator const &,
        typename Collection < T > :: Iterator const &
    ) noexcept;

    Heap (
        typename Collection < T > :: ConstIterator const &,
        typename Collection < T > :: ConstIterator const &
    ) noexcept;

    Heap ( std::initializer_list < T > const & ) noexcept;
    Heap ( Collection < T > const & ) noexcept;

    ~ Heap () noexcept override = default;

private:
    auto beginPtr () noexcept -> Iterator * final;
    auto endPtr () noexcept -> Iterator * final;
    auto beginPtr () const noexcept -> ConstIterator * final;
    auto endPtr () const noexcept -> ConstIterator * final;

public:

    auto begin () noexcept -> Iterator;
    auto end () noexcept -> Iterator;

    auto begin () const noexcept -> ConstIterator;
    auto end () const noexcept -> ConstIterator;
    auto cbegin () const noexcept -> ConstIterator;
    auto cend () const noexcept -> ConstIterator;

    virtual auto remove (Index) noexcept -> bool;

    auto remove ( T const &, Size ) noexcept -> bool override;
    auto removeLast ( T const & ) noexcept -> bool override;

    auto removeOf ( Collection<T> const &, Size ) noexcept -> bool override;
    auto removeLastOf ( Collection<T> const & ) noexcept -> bool override;

    auto removeNotOf ( Collection<T> const &, Size ) noexcept -> bool override;
    auto removeLastNotOf ( Collection<T> const & ) noexcept -> bool override;

    auto replace ( T const &, T const &, Size ) noexcept -> void override;
    auto replaceLast ( T const &, T const & ) noexcept -> void override;

    auto replaceOf ( Collection<T> const &, T const &, Size ) noexcept -> void override;
    auto replaceLastOf ( Collection<T> const &, T const & ) noexcept -> void override;

    auto replaceNotOf ( Collection<T> const &, T const &, Size ) noexcept -> void override;
    auto replaceLastNotOf ( Collection<T> const &, T const & ) noexcept -> void override;

    auto remove ( typename Collection<T>::Iterator const & ) noexcept (false) -> T override;
    auto replace( typename Collection<T>::Iterator const &, T const & ) noexcept -> void override;
    auto insertBefore( typename Collection<T>::Iterator const &, T const & ) noexcept -> void override;
    auto insertAfter( typename Collection<T>::Iterator const &, T const & ) noexcept -> void override;

    inline auto removeOf ( std::initializer_list<T> const & list, Size count ) noexcept -> bool override { return this->removeOf ( Heap <T> (list), count ); }
    inline auto removeLastOf ( std::initializer_list<T> const & list ) noexcept -> bool override { return this->removeLastOf ( Heap<T> (list) ); }

    inline auto removeNotOf ( std::initializer_list<T> const & list, Size count ) noexcept -> bool override { return this->removeNotOf( Heap<T> (list), count ); }
    inline auto removeLastNotOf ( std::initializer_list<T> const & list ) noexcept -> bool override { return this->removeLastNotOf( Heap<T> (list) ); }

    inline auto replaceOf ( std::initializer_list<T> const & list, T const & with, Size count ) noexcept -> void override { return this->replaceOf( Heap<T> (list), with, count ); }
    inline auto replaceLastOf ( std::initializer_list<T> const & list, T const & with ) noexcept -> void override { return this->replaceLastOf( Heap<T> (list), with ); }

    inline auto replaceNotOf ( std::initializer_list<T> const & list, T const & with, Size count ) noexcept -> void override { return this->replaceNotOf( Heap<T> (list), with, count ); }
    inline auto replaceLastNotOf ( std::initializer_list<T> const & list, T const & with ) noexcept -> void override { return this->replaceLastNotOf( Heap<T> (list), with ); }

    [[nodiscard]] constexpr auto back () noexcept (false) -> T & override {
        return this->_elements.back();
    }

    [[nodiscard]] constexpr auto front () noexcept (false) -> T & override {
        return this->_elements.front();
    }

    [[nodiscard]] constexpr auto back () const noexcept(false) -> T const & override {
        return this->_elements.back();
    }

    [[nodiscard]] constexpr auto front () const noexcept (false) -> T const & override {
        return this->_elements.front();
    }

    [[nodiscard]] constexpr auto empty () const noexcept -> bool final {
        return this->_elements.empty();
    }

    [[nodiscard]] auto operator == (Heap const &) const noexcept -> bool;
    [[nodiscard]] auto equals ( Object const & ) const noexcept -> bool final;

    inline auto clear () noexcept -> void final {
        this->_size = 0;
        this->_elements.clear();
    }

    inline auto makeUnique () noexcept -> void override {
        this->_elements.makeUnique();
        this->_size = this->_elements.size();
    }

    inline auto contains (T const & obj) const noexcept -> bool final {
        return this->_elements.contains(obj);
    }

    [[nodiscard]] inline auto toString () const noexcept -> String final {
        return this->_elements.toString();
    }

    [[nodiscard]] inline auto index ( T & obj ) noexcept -> Index override {
        return this->_elements.index( obj );
    }

    [[nodiscard]] inline auto index ( T const & obj ) const noexcept -> Index override {
        return this->_elements.index( obj );
    }

    [[nodiscard]] inline auto get (Index i) noexcept (false) -> T & override {
        return this->_elements.get(i);
    }

    [[nodiscard]] inline auto get (Index i) const noexcept (false) -> T const & override {
        return this->_elements.get(i);
    }

    inline auto set (T const & obj, Index i) noexcept (false) -> T & override {
        return this->_elements.set(obj, i);
    }

    inline auto sub ( List < T > & l, Index s, Index f ) const noexcept (false) -> void override {
        return this->_elements.sub(l, s, f);
    }

    [[nodiscard]] virtual inline auto sub ( Index from, Index to ) const noexcept (false) -> Array < T > {
        return this->_elements.sub(from, to);
    }

    auto popFront () noexcept (false) -> T override;
};

#endif //CDS_HEAP_HPP
