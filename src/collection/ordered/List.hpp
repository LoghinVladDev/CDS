//
// Created by loghin on 15.01.2021.
//

#ifndef CDS_LIST_HPP
#define CDS_LIST_HPP

#include <CDS/Collection>
#if defined(__cpp_concepts) && !defined(_MSC_VER)
#include <concepts>
#endif

template <class T>
class List : public Collection <T> {
protected:
    Size _size { 0ull };

    List () noexcept = default;
public:
    class ListOutOfBounds: public Collection <T>::CollectionOutOfBounds {
    public:
        [[nodiscard]] auto what () const noexcept -> StringLiteral override {
            return "List Access Out of Bounds";
        }
    };

    virtual auto index ( T const & ) const noexcept -> Index = 0;

    virtual auto get ( Index ) noexcept (false) -> T & = 0;
    virtual auto get ( Index ) const noexcept (false) -> const T & = 0;

    virtual auto set ( const T &, Index ) noexcept (false) -> T & = 0;

    virtual auto sub ( List &, Index, Index = UINT64_MAX ) const noexcept (false) -> void = 0;

    inline auto operator [] ( const Index & index ) noexcept -> T & {
        return this->get( index );
    }

    inline auto operator [] ( const Index & index ) const noexcept -> const T & {
        return this->get( index );
    }

    virtual auto remove ( const typename Collection<T>::Iterator & ) noexcept (false) -> T = 0;
    virtual auto replace( const typename Collection<T>::Iterator &, const T & ) noexcept -> void = 0;
    virtual auto insertBefore( const typename Collection<T>::Iterator &, const T & ) noexcept -> void = 0;
    virtual auto insertAfter( const typename Collection<T>::Iterator &, const T & ) noexcept -> void = 0;

    virtual auto popFront ( ) noexcept (false) -> T = 0;
    virtual auto popBack ( ) noexcept (false) -> T = 0;

    virtual auto pushFront ( const T & ) noexcept -> void = 0;
    virtual auto pushBack ( const T & ) noexcept -> void = 0;

    virtual auto pushFront ( T && ) noexcept -> void = 0;
    virtual auto pushBack ( T && ) noexcept -> void = 0;

    inline auto append ( const T & v ) noexcept -> void { return this->pushBack(v); }
    inline auto append ( T && v ) noexcept -> void { return this->pushBack(v); }

    inline auto prepend ( const T & v ) noexcept -> void { return this->pushFront(v); }
    inline auto prepend ( T && v ) noexcept -> void { return this->pushFront(v); }

#if defined(__cpp_concepts) && !defined(_MSC_VER)
    virtual auto sort ( const Comparator < T > & ) noexcept -> void = 0;
//    virtual auto sort ( auto ) noexcept -> void = 0;
#else
//    virtual auto sort ( bool (*) (T const &, T const &) noexcept ) noexcept -> void = 0;
#endif

    [[nodiscard]] inline auto size () const noexcept -> Size override { return this->_size; }

    ~List () noexcept override = default;
};


#endif //CDS_LIST_HPP
