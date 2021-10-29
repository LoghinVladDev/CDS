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

public:
    using ElementType   = typename Collection < T > :: ElementType;

protected:
    Size _size { 0ull };

    List () noexcept = default;
    using ElementRef            = typename Collection < T > :: ElementRef;
    using ElementCRef           = typename Collection < T > :: ElementCRef;
    using ElementMRef           = typename Collection < T > :: ElementMRef;
    using ElementPtr            = typename Collection < T > :: ElementPtr;
    using ElementPtrRef         = typename Collection < T > :: ElementPtrRef;
    using ElementCPtr           = typename Collection < T > :: ElementCPtr;
    using InitializerList       = typename Collection < T > :: InitializerList;

    using CollectionIterator    = typename Collection < T > :: Iterator;

public:
    virtual auto index ( ElementCRef ) const noexcept -> Index = 0;
    virtual auto index ( ElementRef ) noexcept -> Index = 0;

protected:
    virtual auto pAt ( Index ) noexcept (false) -> ElementPtr = 0;
    __CDS_MaybeUnused virtual auto pAt ( Index ) const noexcept (false) -> ElementCPtr = 0;

public:

    __CDS_OptimalInline auto get ( Index index ) noexcept (false) -> ElementRef {
        return * this->pAt ( index );
    }

    __CDS_OptimalInline auto get ( Index index ) const noexcept -> ElementCRef {
        return * this->pAt ( index );
    };

    template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
    __CDS_OptimalInline auto set ( ElementCRef e, Index index ) noexcept (false) -> ElementRef {
        * this->pAt(index) = e;
    }

    template < typename V = T, EnableIf < Type < V > :: moveAssignable > = 0 >
    __CDS_OptimalInline auto set ( ElementMRef e, Index index ) noexcept (false) -> ElementRef {
        * this->pAt(index) = std :: forward < ElementType > ( e );
    }

    template < typename ListType, typename V = T, EnableIf < Type < V > :: copyAssignable && isDerivedFrom < ListType, List < V > > :: value > = 0 >
    __CDS_MaybeUnused auto sub ( Index, Index = limits::S64_MAX ) const noexcept (false) -> ListType;

    __CDS_OptimalInline auto operator [] ( Index index ) noexcept -> ElementRef {
        return this->get( index );
    }

    __CDS_OptimalInline auto operator [] ( Index index ) const noexcept -> ElementCRef {
        return this->get( index );
    }

    auto virtual remove ( CollectionIterator const & ) noexcept (false) -> ElementType = 0;

    __CDS_MaybeUnused virtual auto popFront ( ) noexcept (false) -> ElementType = 0;
    __CDS_MaybeUnused virtual auto popBack ( ) noexcept (false) -> ElementType = 0;

protected:

    virtual auto allocFrontGetPtr () noexcept -> ElementPtrRef = 0;
    virtual auto allocBackGetPtr () noexcept -> ElementPtrRef = 0;

public:

    template < typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
    __CDS_OptimalInline auto pushFront ( ElementCRef value ) noexcept -> ElementRef {
        return * (this->allocFrontGetPtr() = new ElementType ( value ));
    }

    template < typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
    __CDS_OptimalInline auto pushBack ( ElementCRef value ) noexcept -> ElementRef {
        return * (this->allocBackGetPtr() = new ElementType ( value ));
    }

    template < typename V = T, EnableIf < Type < V > :: moveConstructible > = 0 >
    __CDS_OptimalInline auto pushFront ( ElementMRef value ) noexcept -> ElementRef {
        return * (this->allocFrontGetPtr() = new ElementType ( std :: forward < ElementType > ( value ) ));
    }

    template < typename V = T, EnableIf < Type < V > :: moveConstructible > = 0 >
    __CDS_OptimalInline auto pushBack ( ElementMRef value ) noexcept -> ElementRef {
        return * (this->allocBackGetPtr() = new ElementType ( std :: forward < ElementType > ( value ) ));
    }

    template < typename V = T, EnableIf< Type < V > :: copyConstructible > = 0 >
    __CDS_OptimalInline auto append ( ElementCRef v ) noexcept -> ElementRef {
        return this->pushBack ( v );
    }

    template < typename V = T, EnableIf < Type < V > :: moveConstructible > = 0 >
    __CDS_OptimalInline auto append ( ElementMRef v ) noexcept -> ElementRef {
        return this->pushBack ( std :: forward < ElementType > ( v ) );
    }


    template < typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
    __CDS_OptimalInline auto prepend ( ElementCRef v ) noexcept -> ElementRef {
        return this->pushFront(v);
    }

    template < typename V = T, EnableIf < Type < V > :: moveConstructible > = 0 >
    __CDS_OptimalInline auto prepend ( ElementMRef v ) noexcept -> ElementRef {
        return this->pushFront ( std :: forward < ElementType > ( v ) );
    }

    __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto size () const noexcept -> Size override {
        return this->_size;
    }

    __CDS_cpplang_ConstexprDestructor ~List () noexcept override = default;

    template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replace (
            ElementCRef what,
            ElementCRef with,
            Size count
    ) noexcept -> Size {

        Size replaceCount = 0;

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( replaceCount < count ) {
                if ( Type < T > :: compare ( it->value(), what ) ) {
                    it->value() = with;
                    ++ replaceCount;
                }
            } else
                return count;

        return replaceCount;
    }

    template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceFirst (
            ElementCRef what,
            ElementCRef with
    ) noexcept -> bool {

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( Type < T > :: compare ( it->value(), what ) ) {
                it->value() = with;
                return true;
            }

        return false;
    }

    template < typename V = T, EnableIf < Type < V > :: moveAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceFirst (
            ElementCRef what,
            ElementMRef with
    ) noexcept -> bool {

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( Type < T > :: compare ( it->value(), what ) ) {
                it->value() = std :: forward < ElementType > ( with );
                return true;
            }

        return false;
    }

    template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceAll (
            ElementCRef what,
            ElementCRef with
    ) noexcept -> Size {

        Size replacedCount = 0;

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( Type < T > :: compare ( it->value(), what ) ) {
                it->value() = with;
                ++ replacedCount;
            }

        return replacedCount;
    }

    template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceLast (
            ElementCRef what,
            ElementCRef with
    ) noexcept -> bool {

        UniquePointer < CollectionIterator > lastEncountered;

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( Type < T > :: compare ( it->value(), what ) )
                lastEncountered.reset(it->copy());

        if ( ! lastEncountered.isNull() )
            lastEncountered->value() = with;

        return ! lastEncountered.isNull();
    }

    template < typename V = T, EnableIf < Type < V > :: moveAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceLast (
            ElementCRef what,
            ElementMRef with
    ) noexcept -> bool {

        UniquePointer < CollectionIterator > lastEncountered;

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( Type < T > :: compare ( it->value(), what ) )
                lastEncountered.reset(it->copy());

        if ( ! lastEncountered.isNull() )
            lastEncountered->value() = std :: forward < ElementType > ( with );

        return ! lastEncountered.isNull();
    }

    template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceOf (
            Collection < T > const & of,
            ElementCRef with,
            Size count
    ) noexcept -> Size {

        Size replacedCount = 0;
        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
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

    template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceFirstOf (
            Collection < T > const & of,
            ElementCRef with
    ) noexcept -> bool {

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( of.contains( it->value() ) ) {
                it->value() = with;
                return true;
            }

        return false;
    }

    template < typename V = T, EnableIf < Type < V > :: moveAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceFirstOf (
            Collection < T > const & of,
            ElementMRef with
    ) noexcept -> bool {

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( of.contains( it->value() ) ) {
                it->value() = std :: forward < ElementType > ( with );
                return true;
            }

        return false;
    }

    template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceAllOf (
            Collection < T > const & of,
            ElementCRef with
    ) noexcept -> Size {

        Size replacedCount = 0;

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( of.contains( it->value() ) ) {
                it->value() = with;
                ++ replacedCount;
            }

        return replacedCount;
    }

    template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceLastOf (
            Collection < T > const & of,
            ElementCRef with
    ) noexcept -> bool {

        UniquePointer < CollectionIterator > lastOccurred;

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( of.contains( it->value() ) )
                lastOccurred.reset(it->copy());

        if ( ! lastOccurred.isNull() )
            lastOccurred->value() = with;

        return ! lastOccurred.isNull();
    }

    template < typename V = T, EnableIf < Type < V > :: moveAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceLastOf (
            Collection < T > const & of,
            ElementMRef with
    ) noexcept -> bool {

        UniquePointer < CollectionIterator > lastOccurred;

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( of.contains( it->value() ) )
                lastOccurred.reset(it->copy());

        if ( ! lastOccurred.isNull() )
            lastOccurred->value() = std :: forward < ElementType > ( with );

        return ! lastOccurred.isNull();
    }

    template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceNotOf (
            Collection < T > const & of,
            ElementCRef with,
            Size count
    ) noexcept -> Size {

        Size replacedCount = 0;

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
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

    template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceFirstNotOf (
            Collection < T > const & of,
            ElementCRef with
    ) noexcept -> bool {

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( ! of.contains( it->value() ) ) {
                it->value() = with;
                return true;
            }

        return false;
    }

    template < typename V = T, EnableIf < Type < V > :: moveAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceFirstNotOf (
            Collection < T > const & of,
            ElementMRef with
    ) noexcept -> bool {

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( ! of.contains( it->value() ) ) {
                it->value() = std :: forward < ElementType > ( with );
                return true;
            }

        return false;
    }

    template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceAllNotOf (
            Collection < T > const & of,
            ElementCRef with
    ) noexcept -> Size {

        Size replacedCount = 0;

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( ! of.contains( it->value() ) ) {
                it->value() = with;
                ++ replacedCount;
            }

        return replacedCount;
    }

    template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceLastNotOf (
            Collection < T > const & of,
            ElementCRef with
    ) noexcept -> bool {

        UniquePointer < CollectionIterator > lastOccurred;

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( ! of.contains( it->value() ) )
                lastOccurred.reset(it->copy());

        if ( ! lastOccurred.isNull() )
            lastOccurred->value() = with;

        return ! lastOccurred.isNull();
    }

    template < typename V = T, EnableIf < Type < V > :: moveAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceLastNotOf (
            Collection < T > const & of,
            ElementMRef with
    ) noexcept -> bool {

        UniquePointer < CollectionIterator > lastOccurred;

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( ! of.contains( it->value() ) )
                lastOccurred.reset(it->copy());

        if ( ! lastOccurred.isNull() )
            lastOccurred->value() = std :: forward < ElementType > ( with );

        return ! lastOccurred.isNull();
    }

    template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceOf (
            InitializerList of,
            ElementCRef with,
            Size count
    ) noexcept -> Size {

        Size replacedCount = 0;

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
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

    template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceFirstOf (
            InitializerList of,
            ElementCRef with
    ) noexcept -> bool {

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( Collection < T > :: iListContains ( of, it->value() ) ) {
                it->value() = with;
                return true;
            }

        return false;
    }

    template < typename V = T, EnableIf < Type < V > :: moveAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceFirstOf (
            InitializerList of,
            ElementMRef with
    ) noexcept -> bool {

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( Collection < T > :: iListContains ( of, it->value() ) ) {
                it->value() = std :: forward < ElementType > ( with );
                return true;
            }

        return false;
    }

    template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceAllOf (
            InitializerList of,
            ElementCRef with
    ) noexcept -> bool {

        Size replacedCount = 0;

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( Collection < T > :: iListContains ( of, it->value() ) ) {
                it->value() = with;
                ++ replacedCount;
            }

        return replacedCount;
    }

    template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceLastOf (
            InitializerList of,
            ElementCRef with
    ) noexcept -> bool {

        UniquePointer < CollectionIterator > lastOccurred;

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( Collection < T > ::iListContains( of, it->value() ) )
                lastOccurred.reset(it->copy());

        if ( ! lastOccurred.isNull() )
            lastOccurred->value() = with;

        return ! lastOccurred.isNull();
    }

    template < typename V = T, EnableIf < Type < V > :: moveAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceLastOf (
            InitializerList of,
            ElementMRef with
    ) noexcept -> bool {

        UniquePointer < CollectionIterator > lastOccurred;

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( Collection < T > ::iListContains( of, it->value() ) )
                lastOccurred.reset(it->copy());

        if ( ! lastOccurred.isNull() )
            lastOccurred->value() = std :: forward < ElementType > ( with );

        return ! lastOccurred.isNull();
    }

    template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceNotOf (
            InitializerList of,
            ElementCRef with,
            Size count
    ) noexcept -> Size {

        Size replacedCount = 0;

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
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

    template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceFirstNotOf (
            InitializerList of,
            ElementCRef with
    ) noexcept -> bool {

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( ! Collection < T > :: iListContains ( of, it->value() ) ) {
                it->value() = with;
                return true;
            }

        return false;
    }

    template < typename V = T, EnableIf < Type < V > :: moveAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceFirstNotOf (
            InitializerList of,
            ElementMRef with
    ) noexcept -> bool {

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( ! Collection < T > :: iListContains ( of, it->value() ) ) {
                it->value() = std :: forward < ElementType > ( with );
                return true;
            }

        return false;
    }

    template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceAllNotOf (
            InitializerList of,
            ElementCRef with
    ) noexcept -> bool {

        Size replacedCount = 0;

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( ! Collection < T > :: iListContains ( of, it->value() ) ) {
                it->value() = with;
                ++ replacedCount;
            }

        return replacedCount;
    }

    template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceLastNotOf (
            InitializerList of,
            ElementCRef with
    ) noexcept -> bool {

        UniquePointer < CollectionIterator > lastOccurred;

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( ! Collection < T > ::iListContains( of, it->value() ) )
                lastOccurred.reset(it->copy());

        if ( ! lastOccurred.isNull() )
            lastOccurred->value() = with;

        return ! lastOccurred.isNull();
    }

    template < typename V = T, EnableIf < Type < V > :: moveAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptionalInline auto replaceLastNotOf (
            InitializerList of,
            ElementMRef with
    ) noexcept -> bool {

        UniquePointer < CollectionIterator > lastOccurred;

        for (
            auto
                it = UniquePointer < CollectionIterator > ( this->beginPtr() ),
                end = UniquePointer < CollectionIterator > ( this->endPtr() );
            * it != * end;
            it->next()
        )
            if ( ! Collection < T > ::iListContains( of, it->value() ) )
                lastOccurred.reset(it->copy());

        if ( ! lastOccurred.isNull() )
            lastOccurred->value() = std :: forward < ElementType > ( with );

        return ! lastOccurred.isNull();
    }

    template < typename V = T, EnableIf < Type < V > :: copyAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptimalInline auto replace (
            CollectionIterator const & iterator,
            ElementCRef value
    ) noexcept -> bool {

        if ( iterator.of ( this ) ) {
            iterator.value() = value;
            return true;
        }

        return false;
    }

    template < typename V = T, EnableIf < Type < V > :: moveAssignable > = 0 >
    __CDS_MaybeUnused __CDS_OptimalInline auto replace (
            CollectionIterator const & iterator,
            ElementMRef value
    ) noexcept -> bool {

        if ( iterator.of ( this ) ) {
            iterator.value() = std :: forward < ElementType > ( value );
            return true;
        }

        return false;
    }

    __CDS_cpplang_ConstexprPureAbstract virtual auto back () noexcept (false) -> ElementRef = 0;
    __CDS_cpplang_ConstexprPureAbstract virtual auto back () const noexcept (false) -> ElementCRef = 0;

    __CDS_cpplang_ConstexprPureAbstract virtual auto front () const noexcept (false) -> ElementCRef = 0;
    __CDS_cpplang_ConstexprPureAbstract virtual auto front () noexcept (false) -> ElementRef = 0;

    __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_VirtualConstexpr auto empty () const noexcept -> bool override {
        return this->_size == 0;
    }
};

template < typename T >
template < typename ListType, typename V, EnableIf < Type < V > :: copyAssignable && isDerivedFrom < ListType, List < V > > :: value > >
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
