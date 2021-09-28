//
// Created by loghin on 15.01.2021.
//

#ifndef CDS_LIST_HPP
#define CDS_LIST_HPP

#include <CDS/Collection>
#include <CDS/Concepts>

template <class T>
class List : public Collection <T> {
private:
    auto beginPtr () noexcept -> typename Collection < T > :: Iterator * override = 0;
    auto endPtr () noexcept -> typename Collection < T > :: Iterator * override = 0;
    __CDS_MaybeUnused auto beginPtr () const noexcept -> typename Collection < T > :: ConstIterator * override = 0;
    __CDS_MaybeUnused auto endPtr () const noexcept -> typename Collection < T > :: ConstIterator * override = 0;

protected:
    Size _size { 0ull };

    List () noexcept = default;

    using ElementType = typename Collection < T > :: ElementType;
    using ElementRef = typename Collection < T > :: ElementRef;
    using ElementCRef = typename Collection < T > :: ElementCRef;
    using ElementMRef = typename Collection < T > :: ElementMRef;
    using ElementPtr = typename Collection < T > :: ElementPtr;
    using ElementCPtr = typename Collection < T > :: ElementCPtr;
public:
    class __CDS_Deprecated ListOutOfBounds: public Collection <T>::CollectionOutOfBounds {
    public:
        __CDS_NoDiscard auto what () const noexcept -> StringLiteral override {
            return "List Access Out of Bounds";
        }
    };

    virtual auto index ( T const & ) const noexcept -> Index = 0;
    virtual auto index ( T & ) noexcept -> Index = 0;

protected:
    virtual auto pAt ( Index ) noexcept (false) -> ElementPtr = 0;
    virtual auto pAt ( Index ) const noexcept (false) -> ElementCPtr = 0;

public:

    inline auto get ( Index index ) noexcept (false) -> ElementRef {
        return * this->pAt ( index );
    }

    inline auto get ( Index index ) const noexcept -> ElementCRef {
        return * this->pAt ( index );
    };

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    inline auto set ( ElementCRef e, Index index ) noexcept (false) -> T & {
        * this->pAt(index) = e;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: moveAssignable, int > :: type = 0 >
    inline auto set ( ElementMRef e, Index index ) noexcept (false) -> T & {
        * this->pAt(index) = e;
    }

    template < typename ListType, typename V = T, typename std :: enable_if < Type < V > :: copyAssignable && isDerivedFrom < ListType, List < T > > :: value, int > :: type = 0 >
    __CDS_MaybeUnused auto sub ( Index, Index = UINT64_MAX ) const noexcept (false) -> ListType;
//    __CDS_MaybeUnused virtual auto sub ( List &, Index, Index = UINT64_MAX ) const noexcept (false) -> void = 0; // NOLINT(google-default-arguments)

    inline auto operator [] ( Index index ) noexcept -> T & {
        return this->get( index );
    }

    inline auto operator [] ( const Index & index ) const noexcept -> const T & {
        return this->get( index );
    }

    virtual auto remove ( const typename Collection<T>::Iterator & ) noexcept (false) -> T = 0;
//    virtual auto replace( const typename Collection<T>::Iterator &, const T & ) noexcept -> void = 0;
//    __CDS_MaybeUnused virtual auto insertBefore( const typename Collection<T>::Iterator &, const T & ) noexcept -> void = 0;
//    __CDS_MaybeUnused virtual auto insertAfter( const typename Collection<T>::Iterator &, const T & ) noexcept -> void = 0;

    __CDS_MaybeUnused virtual auto popFront ( ) noexcept (false) -> T = 0;
    __CDS_MaybeUnused virtual auto popBack ( ) noexcept (false) -> T = 0;

protected:

    virtual auto allocFrontGetPtr () noexcept -> ElementPtr = 0;
    virtual auto allocBackGetPtr () noexcept -> ElementPtr = 0;

public:

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    inline auto pushFront ( ElementCRef value ) noexcept -> ElementRef {
        auto p = this->allocFrontGetPtr();
        * p = value;
        return * p;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    inline auto pushBack ( ElementCRef value ) noexcept -> ElementRef {
        auto p = this->allocBackGetPtr();
        * p = value;
        return * p;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: moveAssignable, int > :: type = 0 >
    inline auto pushFront ( ElementMRef value ) noexcept -> ElementRef {
        auto p = this->allocFrontGetPtr();
        * p = value;
        return * p;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: moveAssignable, int > :: type = 0 >
    inline auto pushBack ( ElementMRef value ) noexcept -> ElementRef {
        auto p = this->allocBackGetPtr();
        * p = value;
        return * p;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    inline auto append ( T const & v ) noexcept -> void { this->pushBack(v); }

    template < typename V = T, typename std :: enable_if < Type < V > :: moveAssignable, int > :: type = 0 >
    inline auto append ( T && v ) noexcept -> void { this->pushBack(v); }


    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    inline auto prepend ( T const & v ) noexcept -> void { this->pushFront(v); }

    template < typename V = T, typename std :: enable_if < Type < V > :: moveAssignable, int > :: type = 0 >
    inline auto prepend ( T && v ) noexcept -> void { this->pushFront(v); }

//
//    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
//    inline auto add ( T const & v ) noexcept -> void override { this->pushBack(v); }
//
//    template < typename V = T, typename std :: enable_if < Type < V > :: moveAssignable, int > :: type = 0 >
//    inline auto add ( T && v ) noexcept -> void override { this->pushBack(v); }

    __CDS_MaybeUnused virtual auto sort ( const Comparator < T > & ) noexcept -> void = 0;

    __CDS_NoDiscard inline auto size () const noexcept -> Size override { return this->_size; }

    ~List () noexcept override = default;
};

template < typename T >
template < typename ListType, typename V, typename std :: enable_if < Type < V > :: copyAssignable && isDerivedFrom < ListType, List < T > > :: value, int > :: type >
auto List < T > :: sub ( Index from, Index to ) const noexcept(false) -> ListType {
    ListType list;

    if ( from > to ) std :: swap ( from, to );
    if ( from < 0 ) from = 0;
    if ( to >= this->size() ) to = this->size();

    Index i = 0;
    this->forEach([&](ElementCRef element) noexcept -> void {
        if ( i >= from && i < to )
            list.add ( element );
    });

    return list;
}

#endif //CDS_LIST_HPP
