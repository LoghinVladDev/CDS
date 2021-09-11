//
// Created by loghin on 15.01.2021.
//

#ifndef CDS_LIST_HPP
#define CDS_LIST_HPP

#include <CDS/Collection>
#include <CDS/Concepts>

template <class T>
class List : public Collection <T> {
protected:
    Size _size { 0ull };

    List () noexcept = default;
public:
    class ListOutOfBounds: public Collection <T>::CollectionOutOfBounds {
    public:
        __CDS_NoDiscard auto what () const noexcept -> StringLiteral override {
            return "List Access Out of Bounds";
        }
    };

    virtual auto index ( T const & ) const noexcept -> Index = 0;
    virtual auto index ( T & ) noexcept -> Index = 0;

    virtual auto get ( Index ) noexcept (false) -> T & = 0;
    virtual auto get ( Index ) const noexcept (false) -> const T & = 0;

    virtual auto set ( const T &, Index ) noexcept (false) -> T & = 0;

    __CDS_MaybeUnused virtual auto sub ( List &, Index, Index = UINT64_MAX ) const noexcept (false) -> void = 0; // NOLINT(google-default-arguments)

    inline auto operator [] ( const Index & index ) noexcept -> T & {
        return this->get( index );
    }

    inline auto operator [] ( const Index & index ) const noexcept -> const T & {
        return this->get( index );
    }

    virtual auto remove ( const typename Collection<T>::Iterator & ) noexcept (false) -> T = 0;
    virtual auto replace( const typename Collection<T>::Iterator &, const T & ) noexcept -> void = 0;
    __CDS_MaybeUnused virtual auto insertBefore( const typename Collection<T>::Iterator &, const T & ) noexcept -> void = 0;
    __CDS_MaybeUnused virtual auto insertAfter( const typename Collection<T>::Iterator &, const T & ) noexcept -> void = 0;

    __CDS_MaybeUnused virtual auto popFront ( ) noexcept (false) -> T = 0;
    __CDS_MaybeUnused virtual auto popBack ( ) noexcept (false) -> T = 0;

    virtual auto pushFront ( const T & ) noexcept -> void = 0;
    virtual auto pushBack ( const T & ) noexcept -> void = 0;

    virtual auto pushFront ( T && ) noexcept -> void = 0;
    virtual auto pushBack ( T && ) noexcept -> void = 0;

    inline virtual auto append ( T const & v ) noexcept -> void { return this->pushBack(v); }
    inline virtual auto append ( T && v ) noexcept -> void { return this->pushBack(v); }

    inline virtual auto prepend ( T const & v ) noexcept -> void { return this->pushFront(v); }
    inline virtual auto prepend ( T && v ) noexcept -> void { return this->pushFront(v); }

    inline auto add ( T const & v ) noexcept -> void override { return this->pushBack(v); }
    inline auto add ( T && v ) noexcept -> void override { return this->pushBack(v); }

    __CDS_MaybeUnused virtual auto sort ( const Comparator < T > & ) noexcept -> void = 0;

    __CDS_NoDiscard inline auto size () const noexcept -> Size override { return this->_size; }

    ~List () noexcept override = default;
};


#endif //CDS_LIST_HPP
