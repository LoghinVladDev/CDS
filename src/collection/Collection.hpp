//
// Created by loghin on 15.01.2021.
//

#ifndef CDS_COLLECTION_HPP
#define CDS_COLLECTION_HPP

#include <functional>

#ifdef COLLECTION_FORCE_EXPLICIT_CONVERSIONS
#ifndef COLLECTION_EXPLICIT_CONVERSION
#define COLLECTION_EXPLICIT_CONVERSION explicit
#endif
#else
#ifndef COLLECTION_EXPLICIT_CONVERSION
#define COLLECTION_EXPLICIT_CONVERSION
#endif
#endif

#include "../std-types.h"
#include <CDS/Pointer>

#if defined(__cpp_concepts) && !defined(_MSC_VER)
template <typename T>
concept Comparable = requires ( const T & a, const T & b ) {
    std::is_convertible < decltype(a < b), bool >::value;
};
#endif

#include <type_traits>
#include <CDS/Object>

#include <CDS/Traits>
#include <CDS/Concepts>

template <class T>
class Comparator {
public:
    virtual auto operator () (const T &, const T &) const noexcept -> bool = 0;
};

template < typename C >
class Sequence;

template <class T>
class Collection : public Object {
public:
    using ElementType = T;
    using ElementRef = T &;
    using ElementMRef = T &&;
    using ElementCRef = T const &;
    using ElementPtr = T *;
    using ElementCPtr = T const *;

protected:
    class CollectionOutOfBounds : public std::exception {
    public:
        __CDS_NoDiscard auto what() const noexcept -> StringLiteral override {
            return "Accessed Collection Iterator/Index Out of Range";
        }
    };

    Collection() noexcept = default;

public:

    class Iterator : public Object {
        friend class Collection < T >;

    protected:
        Iterator() noexcept = default;
        Iterator(const Iterator &) noexcept = default;
        Iterator(Iterator &&) noexcept = default;

        virtual auto of ( Collection const * ) const noexcept -> bool = 0;
    public:
        ~Iterator() noexcept override = default;

        __CDS_cpplang_ConstexprPureAbstract virtual auto next (  ) noexcept -> Iterator & = 0;
        __CDS_cpplang_ConstexprPureAbstract virtual auto equals ( const Iterator & ) const noexcept -> bool = 0;
        __CDS_cpplang_ConstexprPureAbstract virtual auto value() const noexcept -> T& = 0;

        __CDS_cpplang_VirtualConstexpr virtual auto operator ++ () noexcept -> Iterator & { this->next(); return * this; }

        constexpr auto operator == ( const Iterator & o ) const noexcept -> bool { return this->equals(o ); }
        constexpr auto operator != ( const Iterator & o ) const noexcept -> bool { return ! this->equals(o ); }
        constexpr auto operator * () const noexcept -> T& { return this->value(); }

        __CDS_NoDiscard auto copy () const noexcept -> Iterator * override = 0;
    };

    class ConstIterator : public Object {
        friend class Collection < T >;

    protected:
        ConstIterator() noexcept = default;
        ConstIterator(const ConstIterator &) noexcept = default;
        ConstIterator(ConstIterator &&) noexcept = default;

        virtual auto of ( Collection const * ) const noexcept -> bool = 0;
    public:
        ~ConstIterator() noexcept override = default;

        __CDS_cpplang_ConstexprPureAbstract virtual auto next (  ) noexcept -> ConstIterator & = 0;
        __CDS_cpplang_ConstexprPureAbstract virtual auto equals ( const ConstIterator & ) const noexcept -> bool = 0;
        __CDS_cpplang_ConstexprPureAbstract virtual auto value () const noexcept -> const T& = 0;

        __CDS_cpplang_VirtualConstexpr virtual auto operator ++ () noexcept -> ConstIterator & { this->next(); return * this; }

        constexpr inline auto operator == ( const ConstIterator & o ) const noexcept -> bool { return this->equals(o ); }
        constexpr inline auto operator != ( const ConstIterator & o ) const noexcept -> bool { return ! this->equals(o ); }
        constexpr inline auto operator * () const noexcept -> const T& { return this->value(); }

        __CDS_NoDiscard auto copy () const noexcept -> ConstIterator * override = 0;
    };
protected:
    virtual auto beginPtr () noexcept -> Iterator * = 0;
    virtual auto endPtr () noexcept -> Iterator * = 0;
    __CDS_MaybeUnused virtual auto beginPtr () const noexcept -> ConstIterator * = 0;
    __CDS_MaybeUnused virtual auto endPtr () const noexcept -> ConstIterator * = 0;

    static inline auto beginPtr ( Collection < T > & o ) noexcept -> Iterator * { return o.beginPtr(); }
    static inline auto endPtr ( Collection < T > & o ) noexcept -> Iterator * { return o.endPtr(); }
    static inline auto beginPtr ( const Collection < T > & o ) noexcept -> ConstIterator * { return o.beginPtr(); }
    static inline auto endPtr ( const Collection < T > & o ) noexcept -> ConstIterator * { return o.endPtr(); }

    static inline auto iteratorIsOf ( Iterator const & it, Collection < T > const & collection ) noexcept -> bool {
        return it.of(& collection);
    }

    static inline auto iteratorIsOf ( ConstIterator const & it, Collection < T > const & collection ) noexcept -> bool {
        return it.of(& collection);
    }

//    virtual auto findPtr ( T & ) noexcept -> Iterator & = 0;
//    virtual auto findPtr ( const T & ) const noexcept -> ConstIterator & = 0;

public:
    __CDS_MaybeUnused virtual auto remove ( const T &, Size ) noexcept -> bool = 0;
    __CDS_MaybeUnused virtual auto inline removeAll ( const T & o ) noexcept -> bool { return this->remove( o, this->size() ); }
    __CDS_MaybeUnused virtual auto inline removeFirst ( const T & o ) noexcept -> bool { return this->remove( o, 1 ); }
    __CDS_MaybeUnused virtual auto removeLast ( const T & o ) noexcept -> bool = 0;

    __CDS_MaybeUnused virtual auto removeOf ( const Collection &, Size ) noexcept -> bool = 0;
    __CDS_MaybeUnused virtual auto inline removeFirstOf ( const Collection & o ) noexcept -> bool { return this->removeOf( o, 1 ); }
    __CDS_MaybeUnused virtual auto inline removeAllOf ( const Collection & o ) noexcept -> bool { return this->removeOf ( o, this->size() ); }
    __CDS_MaybeUnused virtual auto removeLastOf ( const Collection & ) noexcept -> bool = 0;

    __CDS_MaybeUnused virtual auto removeNotOf ( const Collection &, Size ) noexcept -> bool = 0;
    __CDS_MaybeUnused virtual auto inline removeFirstNotOf ( const Collection & o ) noexcept -> bool { return this->removeNotOf ( o, 1 ); }
    __CDS_MaybeUnused virtual auto inline removeAllNotOf ( const Collection & o ) noexcept -> bool  { return this->removeNotOf( o, this->size() ); }
    __CDS_MaybeUnused virtual auto removeLastNotOf ( const Collection & ) noexcept -> bool = 0;

    __CDS_MaybeUnused virtual auto removeOf ( const std::initializer_list<T> &, Size ) noexcept -> bool = 0;
    __CDS_MaybeUnused virtual auto inline removeFirstOf ( const std::initializer_list<T> & o ) noexcept -> bool { return this->removeOf( o, 1 ); }
    __CDS_MaybeUnused virtual auto inline removeAllOf ( const std::initializer_list<T> & o ) noexcept -> bool { return this->removeOf ( o, this->size() ); }
    __CDS_MaybeUnused virtual auto removeLastOf ( const std::initializer_list<T> & ) noexcept -> bool = 0;

    __CDS_MaybeUnused virtual auto removeNotOf ( const std::initializer_list<T> &, Size ) noexcept -> bool = 0;
    __CDS_MaybeUnused virtual auto inline removeFirstNotOf ( const std::initializer_list<T> & o ) noexcept -> bool { return this->removeNotOf ( o, 1 ); }
    __CDS_MaybeUnused virtual auto inline removeAllNotOf ( const std::initializer_list<T> & o ) noexcept -> bool  { return this->removeNotOf( o, this->size() ); }
    __CDS_MaybeUnused virtual auto removeLastNotOf ( const std::initializer_list<T> & ) noexcept -> bool = 0;

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
    __CDS_MaybeUnused auto replaceOf ( Collection const & of, ElementCRef with, Size count ) noexcept -> Size {
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
    __CDS_MaybeUnused auto inline replaceFirstOf ( Collection const & of, ElementCRef with ) noexcept -> bool {
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
    __CDS_MaybeUnused auto inline replaceFirstOf ( Collection const & of, ElementMRef with ) noexcept -> bool {
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
    __CDS_MaybeUnused auto inline replaceAllOf ( Collection const & of, ElementCRef with ) noexcept -> Size {
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
    __CDS_MaybeUnused auto replaceLastOf ( Collection const & of, ElementCRef with ) noexcept -> bool {
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
    __CDS_MaybeUnused auto replaceLastOf ( Collection const & of, ElementCRef with ) noexcept -> bool {
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
    __CDS_MaybeUnused auto replaceNotOf ( Collection const & of, ElementCRef with, Size count ) noexcept -> Size {
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
    __CDS_MaybeUnused auto inline replaceFirstNotOf ( Collection const & of, ElementCRef with ) noexcept -> bool {
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
    __CDS_MaybeUnused auto inline replaceFirstNotOf ( Collection const & of, ElementMRef with ) noexcept -> bool {
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
    __CDS_MaybeUnused auto inline replaceAllNotOf ( Collection const & of, ElementCRef with ) noexcept -> Size {
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
    __CDS_MaybeUnused auto replaceLastNotOf ( Collection const & of, ElementCRef with ) noexcept -> bool {
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
    __CDS_MaybeUnused auto replaceLastNotOf ( Collection const & of, ElementMRef with ) noexcept -> bool {
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

protected:

    static auto iListContains ( std :: initializer_list < T > const & list, ElementCRef what ) noexcept -> bool {
        for ( auto & e : list )
            if ( Type < T > :: compare (e, what) )
                return true;

        return false;
    }

    virtual auto allocInsertGetPtr () noexcept -> ElementPtr = 0;

public:

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

#if __cpp_constexpr >= 201907
    constexpr virtual inline auto front () const noexcept (false) -> const T & = 0;
    constexpr virtual inline auto front () noexcept (false) -> T & = 0;

    __CDS_NoDiscard __CDS_MaybeUnused constexpr virtual inline auto empty () const noexcept -> bool = 0;
#else
    virtual auto front () const noexcept (false) -> const T & = 0;
    virtual auto front () noexcept (false) -> T & = 0;

    __CDS_NoDiscard __CDS_MaybeUnused virtual auto empty () const noexcept -> bool = 0;
#endif

    template < typename V = T, typename std :: enable_if < Type < V > :: copyAssignable, int > :: type = 0 >
    inline auto add (ElementCRef element) noexcept -> void {
        * this->allocInsertGetPtr() = element;
    }

    template < typename V = T, typename std :: enable_if < Type < V > :: moveAssignable, int > :: type = 0 >
    inline auto add (ElementMRef element) noexcept -> void {
        * this->allocInsertGetPtr() = element;
    }

    virtual auto clear () noexcept -> void = 0;

    __CDS_MaybeUnused __CDS_NoDiscard virtual auto size () const noexcept -> Size = 0;
    __CDS_MaybeUnused virtual auto makeUnique () noexcept -> void = 0;

    virtual auto contains ( const T & ) const noexcept -> bool = 0;

#define COMMA ,

    template < typename Action >
    __CDS_MaybeUnused auto forEach ( Action const & ) noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Action > () ) ( Type < ElementType > :: unsafeReference() ) ) ) -> void __CDS_Requires ( IsActionOver < Action COMMA T > );
    template < typename Action >
    __CDS_MaybeUnused auto forEach ( Action const & ) const noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Action > () ) ( Type < ElementType const > :: unsafeReference() ) ) ) -> void __CDS_Requires ( IsActionOver < Action COMMA T > );

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    __CDS_MaybeUnused inline auto some ( Size count, Predicate const & predicate = []( ElementType const & ) noexcept -> bool { return true; } ) noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {
        return this->count(predicate) == count;
    }

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    __CDS_MaybeUnused inline auto some ( Size count, Predicate const & predicate = []( ElementType const & ) noexcept -> bool { return true; } ) const noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType const > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {
        return this->count(predicate) == count;
    }

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    __CDS_MaybeUnused inline auto atLeast ( Size count, Predicate const & predicate = []( ElementType const & ) noexcept -> bool { return true; } ) noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {
        return this->count(predicate) >= count;
    }

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    __CDS_MaybeUnused inline auto atLeast ( Size count, Predicate const & predicate = []( ElementType const & ) noexcept -> bool { return true; } ) const noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType const > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {
        return this->count(predicate) >= count;
    }

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    __CDS_MaybeUnused inline auto atMost ( Size count, Predicate const & predicate = []( ElementType const & ) noexcept -> bool { return true; } ) noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {
        return this->count(predicate) <= count;
    }

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    __CDS_MaybeUnused inline auto atMost ( Size count, Predicate const & predicate = []( ElementType const & ) noexcept -> bool { return true; } ) const noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType const > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {
        return this->count(predicate) <= count;
    }

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    __CDS_MaybeUnused inline auto moreThan ( Size count, Predicate const & predicate = []( ElementType const & ) noexcept -> bool { return true; } ) noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {
        return this->atLeast ( count, predicate );
    }

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    __CDS_MaybeUnused inline auto moreThan ( Size count, Predicate const & predicate = []( ElementType const & ) noexcept -> bool { return true; } ) const noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType const > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {
        return this->atLeast ( count, predicate );
    }

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    __CDS_MaybeUnused inline auto lessThan ( Size count, Predicate const & predicate = []( ElementType const & ) noexcept -> bool { return true; } ) noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {
        return this->lessThan ( count, predicate );
    }

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    __CDS_MaybeUnused inline auto lessThan ( Size count, Predicate const & predicate = []( ElementType const & ) noexcept -> bool { return true; } ) const noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType const > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {
        return this->lessThan ( count, predicate );
    }

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    __CDS_MaybeUnused auto count ( Predicate const & = []( ElementType const & ) noexcept -> bool { return true; } ) noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType > :: unsafeReference() ) ) ) -> Size __CDS_Requires( IsPredicateOver < Predicate COMMA T > );

    template < typename Predicate = std::function < bool ( ElementType const & ) > >
    __CDS_MaybeUnused auto count ( Predicate const & = []( ElementType const & ) noexcept -> bool { return true; } ) const noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType const > :: unsafeReference() ) ) ) -> Size __CDS_Requires( IsPredicateOver < Predicate COMMA T > );

    template < typename Predicate >
    __CDS_MaybeUnused inline auto any ( Predicate const & p ) noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) { return this->atLeast ( 1, p ); }
    template < typename Predicate >
    __CDS_MaybeUnused inline auto any ( Predicate const & p ) const noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType const > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) { return this->atLeast ( 1, p ); }

    template < typename Predicate >
    __CDS_MaybeUnused inline auto all ( Predicate const & p ) noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) { return ! this->any ( [&p] (T & e) noexcept -> bool { return ! p(e); } ); }
    template < typename Predicate >
    __CDS_MaybeUnused inline auto all ( Predicate const & p ) const noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType const > :: unsafeReference() ) ) ) -> bool __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) { return ! this->any ( [&p] (T const & e) noexcept -> bool { return ! p(e); } ); }

#undef COMMA

    virtual COLLECTION_EXPLICIT_CONVERSION operator bool () const noexcept { // NOLINT(google-explicit-constructor)
        return this->size() != 0;
    }

    __CDS_NoDiscard auto toString () const noexcept -> String override = 0;

    ~Collection() noexcept override = default;

    friend inline auto operator << ( std::ostream & o, const Collection & c ) noexcept -> std::ostream & {
         return ( o << c.toString() );
    }
};

#define COMMA ,

template < typename T >
template < typename Action >
auto Collection<T>::forEach ( Action const & a ) noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Action > () ) ( Type < ElementType > :: unsafeReference() ) ) ) -> void __CDS_Requires( IsActionOver < Action COMMA T > ) {
    auto begin = this->beginPtr();
    auto end = this->endPtr();

    for ( auto it = begin; ! it->equals( * end ); it->next() )
        a ( it->value() );

    delete begin;
    delete end;
}

template < typename T >
template < typename Action >
auto Collection<T>::forEach ( Action const & a ) const noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Action > () ) ( Type < ElementType const > :: unsafeReference() ) ) ) -> void __CDS_Requires( IsActionOver < Action COMMA T > ) {
    auto begin = this->beginPtr();
    auto end = this->endPtr();

    for ( auto it = begin; ! it->equals( * end ); it->next() )
        a ( it->value() );

    delete begin;
    delete end;
}

template < typename T >
template < typename Predicate >
auto Collection<T>::count ( Predicate const & p ) noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType > :: unsafeReference() ) ) ) -> Size __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {
    Size trueCount = 0;

    auto pBegin = this->beginPtr();
    auto pEnd = this->endPtr();

    for ( auto it = pBegin; ! it->equals( * pEnd ); it->next() )
        if ( p ( it->value() ) )
            trueCount ++;

    delete pBegin;
    delete pEnd;

    return trueCount;
}

template < typename T >
template < typename Predicate >
auto Collection<T>::count ( Predicate const & p ) const noexcept ( noexcept ( ( * dataTypes :: unsafeAddress < Predicate > () ) ( Type < ElementType const > :: unsafeReference() ) ) ) -> Size __CDS_Requires( IsPredicateOver < Predicate COMMA T > ) {
    Size trueCount = 0;

    auto pBegin = this->beginPtr();
    auto pEnd = this->endPtr();

    for ( auto it = pBegin; ! it->equals( * pEnd ); it->next() )
        if ( p ( it->value() ) )
            trueCount ++;

    delete pBegin;
    delete pEnd;

    return trueCount;
}

#undef COMMA


#endif //CDS_COLLECTION_HPP
