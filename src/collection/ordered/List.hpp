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

    using ElementType   = typename Collection < T > :: ElementType;
    using ElementRef    = typename Collection < T > :: ElementRef;
    using ElementCRef   = typename Collection < T > :: ElementCRef;
    using ElementMRef   = typename Collection < T > :: ElementMRef;
    using ElementPtr    = typename Collection < T > :: ElementPtr;
    using ElementPtrRef = typename Collection < T > :: ElementPtrRef;
    using ElementCPtr   = typename Collection < T > :: ElementCPtr;

    using Iterator = typename Collection < T > :: Iterator;
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
    __CDS_MaybeUnused virtual auto pAt ( Index ) const noexcept (false) -> ElementCPtr = 0;

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
    __CDS_MaybeUnused auto sub ( Index, Index = Limits::S64_MAX ) const noexcept (false) -> ListType;

    inline auto operator [] ( Index index ) noexcept -> T & {
        return this->get( index );
    }

    inline auto operator [] ( const Index & index ) const noexcept -> const T & {
        return this->get( index );
    }

    virtual auto remove ( const typename Collection<T>::Iterator & ) noexcept (false) -> T = 0;

    __CDS_MaybeUnused virtual auto popFront ( ) noexcept (false) -> T = 0;
    __CDS_MaybeUnused virtual auto popBack ( ) noexcept (false) -> T = 0;

protected:

    virtual auto allocFrontGetPtr () noexcept -> ElementPtrRef = 0;
    virtual auto allocBackGetPtr () noexcept -> ElementPtrRef = 0;

public:

    template < typename V = T, typename std :: enable_if < Type < V > :: copyConstructible, int > :: type = 0 >
    inline auto pushFront ( ElementCRef value ) noexcept -> ElementRef {
        return * (this->allocFrontGetPtr() = new ElementType ( value ));
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: copyConstructible, int > :: type = 0 >
    inline auto pushBack ( ElementCRef value ) noexcept -> ElementRef {
        return * (this->allocBackGetPtr() = new ElementType ( value ));
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: moveConstructible, int > :: type = 0 >
    inline auto pushFront ( ElementMRef value ) noexcept -> ElementRef {
        return * (this->allocFrontGetPtr() = new ElementType ( value ));
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: moveConstructible, int > :: type = 0 >
    inline auto pushBack ( ElementMRef value ) noexcept -> ElementRef {
        return * (this->allocBackGetPtr() = new ElementType ( value ));
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: copyConstructible, int > :: type = 0 >
    inline auto append ( ElementCRef v ) noexcept -> void { this->pushBack(v); }

    template < typename V = T, typename std :: enable_if < Type < V > :: moveConstructible, int > :: type = 0 >
    inline auto append ( ElementMRef v ) noexcept -> void { this->pushBack(v); }


    template < typename V = T, typename std :: enable_if < Type < V > :: copyConstructible, int > :: type = 0 >
    inline auto prepend ( ElementCRef v ) noexcept -> void { this->pushFront(v); }

    template < typename V = T, typename std :: enable_if < Type < V > :: moveConstructible, int > :: type = 0 >
    inline auto prepend ( ElementMRef v ) noexcept -> void { this->pushFront(v); }

//    __CDS_MaybeUnused virtual auto sort ( const Comparator < T > & ) noexcept -> void = 0;

    __CDS_NoDiscard inline auto size () const noexcept -> Size override { return this->_size; }

    ~List () noexcept override = default;

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto replace ( ElementCRef what, ElementCRef with, Size count ) noexcept -> Size {
        Size replaceCount = 0;

        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        ) {
            if ( replaceCount < count ) {
                if ( Type < T > :: compare ( it->value(), what ) ) {
                    it->value() = with;
                    ++ replaceCount;
                }
            } else
                return count;
        }

        return replaceCount;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto inline replaceFirst ( ElementCRef what, ElementCRef with ) noexcept -> bool {
        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( Type < T > :: compare ( it->value(), what ) ) {
                it->value() = with;
                return true;
            }

        return false;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: moveAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto inline replaceFirst ( ElementCRef what, ElementMRef with ) noexcept -> bool {
        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( Type < T > :: compare ( it->value(), what ) ) {
                it->value() = with;
                return true;
            }

        return false;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto inline replaceAll ( ElementCRef what, ElementCRef with ) noexcept -> Size {
        Size replacedCount = 0;

        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( Type < T > :: compare ( it->value(), what ) ) {
                it->value() = with;
                ++ replacedCount;
            }

        return replacedCount;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto replaceLast ( ElementCRef what, ElementCRef with ) noexcept -> bool {
        UniquePointer < Iterator > lastEncountered;

        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( Type < T > :: compare ( it->value(), what ) )
                lastEncountered.reset(it->copy());

        if ( ! lastEncountered.isNull() )
            lastEncountered->value() = with;

        return ! lastEncountered.isNull();
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: moveAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto replaceLast ( ElementCRef what, ElementMRef with ) noexcept -> bool {
        UniquePointer < Iterator > lastEncountered;

        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( Type < T > :: compare ( it->value(), what ) )
                lastEncountered.reset(it->copy());

        if ( ! lastEncountered.isNull() )
            lastEncountered->value() = with;

        return ! lastEncountered.isNull();
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto replaceOf ( Collection < T > const & of, ElementCRef with, Size count ) noexcept -> Size {
        Size replacedCount = 0;
        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( replacedCount < count ) {
                if ( of.contains( it->value() ) ) {
                    it->value() = with;
                    ++ replacedCount;
                }
            } else
                return count;

        return replacedCount;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto inline replaceFirstOf ( Collection < T > const & of, ElementCRef with ) noexcept -> bool {
        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( of.contains( it->value() ) ) {
                it->value() = with;
                return true;
            }

        return false;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: moveAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto inline replaceFirstOf ( Collection < T > const & of, ElementMRef with ) noexcept -> bool {
        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( of.contains( it->value() ) ) {
                it->value() = with;
                return true;
            }

        return false;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto inline replaceAllOf ( Collection < T > const & of, ElementCRef with ) noexcept -> Size {
        Size replacedCount = 0;

        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( of.contains( it->value() ) ) {
                it->value() = with;
                ++ replacedCount;
            }

        return replacedCount;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto replaceLastOf ( Collection < T > const & of, ElementCRef with ) noexcept -> bool {
        UniquePointer < Iterator > lastOccurred;

        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( of.contains( it->value() ) )
                lastOccurred.reset(it->copy());

        if ( ! lastOccurred.isNull() )
            lastOccurred->value() = with;

        return ! lastOccurred.isNull();
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: moveAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto replaceLastOf ( Collection < T > const & of, ElementCRef with ) noexcept -> bool {
        UniquePointer < Iterator > lastOccurred;

        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( of.contains( it->value() ) )
                lastOccurred.reset(it->copy());

        if ( ! lastOccurred.isNull() )
            lastOccurred->value() = with;

        return ! lastOccurred.isNull();
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto replaceNotOf ( Collection < T > const & of, ElementCRef with, Size count ) noexcept -> Size {
        Size replacedCount = 0;

        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( replacedCount < count ) {
                if ( ! of.contains( it->value() ) ) {
                    it->value() = with;
                    ++ replacedCount;
                }
            } else
                return count;

        return replacedCount;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto inline replaceFirstNotOf ( Collection < T > const & of, ElementCRef with ) noexcept -> bool {
        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( ! of.contains( it->value() ) ) {
                it->value() = with;
                return true;
            }

        return false;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: moveAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto inline replaceFirstNotOf ( Collection < T > const & of, ElementMRef with ) noexcept -> bool {
        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( ! of.contains( it->value() ) ) {
                it->value() = with;
                return true;
            }

        return false;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto inline replaceAllNotOf ( Collection < T > const & of, ElementCRef with ) noexcept -> Size {
        Size replacedCount = 0;

        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( ! of.contains( it->value() ) ) {
                it->value() = with;
                ++ replacedCount;
            }

        return replacedCount;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto replaceLastNotOf ( Collection < T > const & of, ElementCRef with ) noexcept -> bool {
        UniquePointer < Iterator > lastOccurred;

        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( ! of.contains( it->value() ) )
                lastOccurred.reset(it->copy());

        if ( ! lastOccurred.isNull() )
            lastOccurred->value() = with;

        return ! lastOccurred.isNull();
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: moveAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto replaceLastNotOf ( Collection < T > const & of, ElementMRef with ) noexcept -> bool {
        UniquePointer < Iterator > lastOccurred;

        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( ! of.contains( it->value() ) )
                lastOccurred.reset(it->copy());

        if ( ! lastOccurred.isNull() )
            lastOccurred->value() = with;

        return ! lastOccurred.isNull();
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto replaceOf ( std::initializer_list<T> const & of, ElementCRef with, Size count ) noexcept -> Size {
        Size replacedCount = 0;

        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( replacedCount < count ) {
                if ( Collection < T > :: iListContains ( of, it->value() ) ) {
                    it->value() = with;
                    ++ replacedCount;
                }
            } else
                return count;

        return replacedCount;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto inline replaceFirstOf ( std::initializer_list<T> const & of, ElementCRef with ) noexcept -> bool {
        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( Collection < T > :: iListContains ( of, it->value() ) ) {
                it->value() = with;
                return true;
            }

        return false;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: moveAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto inline replaceFirstOf ( std::initializer_list<T> const & of, ElementMRef with ) noexcept -> bool {
        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( Collection < T > :: iListContains ( of, it->value() ) ) {
                it->value() = with;
                return true;
            }

        return false;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto inline replaceAllOf ( std::initializer_list<T> const & of, ElementCRef with ) noexcept -> bool {
        Size replacedCount = 0;

        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( Collection < T > :: iListContains ( of, it->value() ) ) {
                it->value() = with;
                ++ replacedCount;
            }

        return replacedCount;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto replaceLastOf ( std::initializer_list<T> const & of, ElementCRef with ) noexcept -> bool {
        UniquePointer < Iterator > lastOccurred;

        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( Collection < T > ::iListContains( of, it->value() ) )
                lastOccurred.reset(it->copy());

        if ( ! lastOccurred.isNull() )
            lastOccurred->value() = with;

        return ! lastOccurred.isNull();
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: moveAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto replaceLastOf ( std::initializer_list<T> const & of, ElementMRef with ) noexcept -> bool {
        UniquePointer < Iterator > lastOccurred;

        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( Collection < T > ::iListContains( of, it->value() ) )
                lastOccurred.reset(it->copy());

        if ( ! lastOccurred.isNull() )
            lastOccurred->value() = with;

        return ! lastOccurred.isNull();
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto replaceNotOf ( std::initializer_list<T> const & of, ElementCRef with, Size count ) noexcept -> Size {
        Size replacedCount = 0;

        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( replacedCount < count ) {
                if ( ! Collection < T > :: iListContains ( of, it->value() ) ) {
                    it->value() = with;
                    ++ replacedCount;
                }
            } else
                return count;

        return replacedCount;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto inline replaceFirstNotOf ( std::initializer_list<T> const & of, ElementCRef with ) noexcept -> bool {
        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( ! Collection < T > :: iListContains ( of, it->value() ) ) {
                it->value() = with;
                return true;
            }

        return false;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: moveAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto inline replaceFirstNotOf ( std::initializer_list<T> const & of, ElementMRef with ) noexcept -> bool {
        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( ! Collection < T > :: iListContains ( of, it->value() ) ) {
                it->value() = with;
                return true;
            }

        return false;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto inline replaceAllNotOf ( std::initializer_list<T> const & of, ElementCRef with ) noexcept -> bool {
        Size replacedCount = 0;

        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( ! Collection < T > :: iListContains ( of, it->value() ) ) {
                it->value() = with;
                ++ replacedCount;
            }

        return replacedCount;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto replaceLastNotOf ( std::initializer_list<T> const & of, ElementCRef with ) noexcept -> bool {
        UniquePointer < Iterator > lastOccurred;

        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( ! Collection < T > ::iListContains( of, it->value() ) )
                lastOccurred.reset(it->copy());

        if ( ! lastOccurred.isNull() )
            lastOccurred->value() = with;

        return ! lastOccurred.isNull();
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: moveAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto replaceLastNotOf ( std::initializer_list<T> const & of, ElementMRef with ) noexcept -> bool {
        UniquePointer < Iterator > lastOccurred;

        for (
                auto
                        it = UniquePointer < Iterator > ( this->beginPtr() ),
                        end = UniquePointer < Iterator > ( this->endPtr() );
                * it != * end;
                it->next()
        )
            if ( ! Collection < T > ::iListContains( of, it->value() ) )
                lastOccurred.reset(it->copy());

        if ( ! lastOccurred.isNull() )
            lastOccurred->value() = with;

        return ! lastOccurred.isNull();
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    __CDS_MaybeUnused auto replace ( Iterator const & iterator, ElementCRef value ) noexcept -> bool {
        if ( iterator.of ( this ) ) {
            iterator.value() = value;
            return true;
        }

        return false;
    }

    virtual auto back () noexcept (false) -> T & = 0;
    virtual auto back () const noexcept (false) -> const T & = 0;

    __CDS_cpplang_ConstexprPureAbstract virtual auto front () const noexcept (false) -> const T & = 0;
    __CDS_cpplang_ConstexprPureAbstract virtual auto front () noexcept (false) -> T & = 0;

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_VirtualConstexpr auto empty () const noexcept -> bool override {
        return this->_size == 0;
    }
};

template < typename T >
template < typename ListType, typename V, typename std :: enable_if < Type < V > :: copyAssignable && isDerivedFrom < ListType, List < T > > :: value, int > :: type >
__CDS_MaybeUnused auto List < T > :: sub ( Index from, Index to ) const noexcept(false) -> ListType {
    ListType list;

    if ( from > to ) std :: swap ( from, to );
    if ( from < 0 ) from = 0;
    if ( to >= this->size() ) to = this->size();

    Index i = 0;
    this->forEach([&](ElementCRef element) noexcept -> void {
        if ( i >= from && i < to )
            list.add ( element );
        ++ i;
    });

    return list;
}

__CDS_RegisterParseTypeTemplateT(List)

#endif //CDS_LIST_HPP
