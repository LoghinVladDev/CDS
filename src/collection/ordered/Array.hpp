//
// Created by loghin on 01.03.2021.
//

#ifndef CDS_ARRAY_HPP
#define CDS_ARRAY_HPP

#include <CDS/List>

template < typename T >
class Array : public List <T> {
private:
    T ** _pData     {nullptr };
    Size _capacity  { 0ull };

public:
    using ElementType                   = typename List < T > :: ElementType;

private:
    using ElementRef                    = typename List < T > :: ElementRef;
    using ElementCRef                   = typename List < T > :: ElementCRef;
    using ElementMRef __CDS_MaybeUnused = typename List < T > :: ElementMRef;
    using ElementPtr                    = typename List < T > :: ElementPtr;
    using ElementPtrRef                 = typename List < T > :: ElementPtrRef;
    using ElementCPtr                   = typename List < T > :: ElementCPtr;

    using CollectionIterator            = typename List < T > :: CollectionIterator;
    using ConstCollectionIterator       = typename List < T > :: ConstCollectionIterator;

    using InitializerList               = typename List < T > :: InitializerList;

    class IteratorBase;
    class ConstIteratorBase;

    __CDS_MaybeUnused auto expandWith ( Size ) noexcept -> void;

public:

    class Iterator;
    class ReverseIterator;
    class ConstIterator;
    class ConstReverseIterator;

    Array () noexcept = default;
    Array ( Array const & ) noexcept;
    Array ( Array && ) noexcept;

    Array (
        CollectionIterator const &,
        CollectionIterator const &
    ) noexcept;

    Array (
        ConstCollectionIterator const &,
        ConstCollectionIterator const &
    ) noexcept;

    template < typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
    Array( InitializerList ) noexcept; // NOLINT(google-explicit-constructor)

    template < typename V = T, EnableIf < Type < V > :: defaultConstructible > = 0 >
    explicit Array( Size ) noexcept;

    template < typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
    explicit Array( Size, ElementCRef ) noexcept;

    explicit Array ( Collection < T > const & ) noexcept;

    ~Array () noexcept override;

private:
    __CDS_OptimalInline auto beginPtr () noexcept -> Iterator * final { return new Iterator( this, 0 ); }
    __CDS_OptimalInline auto endPtr () noexcept -> Iterator * final { return new Iterator(this, this->size()); }
    __CDS_OptimalInline auto beginPtr () const noexcept -> ConstIterator * final { return new ConstIterator( this, 0 ); }
    __CDS_OptimalInline auto endPtr () const noexcept -> ConstIterator * final { return new ConstIterator( this, this->size() ); }

public:
    __CDS_cpplang_NonConstConstexprMemberFunction auto begin () noexcept -> Iterator { return Iterator ( this, 0 ); }
    constexpr auto begin () const noexcept -> ConstIterator { return ConstIterator ( this, 0 ); }
    constexpr auto cbegin () const noexcept -> ConstIterator { return ConstIterator ( this, 0 ); }
    __CDS_cpplang_NonConstConstexprMemberFunction auto end () noexcept -> Iterator { return Iterator ( this, this->size() ); }
    constexpr auto end () const noexcept -> ConstIterator { return ConstIterator ( this, this->size() ); }
    constexpr auto cend () const noexcept -> ConstIterator { return ConstIterator ( this, this->size() ); }

    __CDS_cpplang_NonConstConstexprMemberFunction auto rbegin () noexcept -> ReverseIterator { return ReverseIterator ( this, this->size () - 1 ); }
    constexpr auto rbegin () const noexcept -> ConstReverseIterator { return ConstReverseIterator ( this, this->size () - 1 ); }
    __CDS_MaybeUnused constexpr auto crbegin () const noexcept -> ConstReverseIterator { return ConstReverseIterator ( this, this->size () - 1 ); }
    __CDS_cpplang_NonConstConstexprMemberFunction auto rend() noexcept -> ReverseIterator { return ReverseIterator(this, -1); }
    constexpr auto rend() const noexcept -> ConstReverseIterator { return ConstReverseIterator(this, -1); }
    __CDS_MaybeUnused constexpr auto crend() const noexcept -> ConstReverseIterator { return ConstReverseIterator(this, -1); }

private:
    auto _resize ( Size ) noexcept -> void;

public:

    template < typename V = T, EnableIf < Type < V > :: defaultConstructible > = 0 >
    __CDS_OptionalInline auto resize ( Size newSize ) noexcept -> void {
        this->_resize(newSize);
        for ( auto i = this->_size; i < newSize; ++ i )
            this->_pData[i] = new T();
        this->_size = newSize;
    }

    template < EnableIf < Type < T > :: copyConstructible > = 0 >
    __CDS_OptionalInline auto resize ( Size newSize, ElementCRef value ) noexcept -> void {
        this->_resize(newSize);
        for ( auto i = this->_size; i < newSize; ++ i )
            this->_pData[i] = new T(value);
        this->_size = newSize;
    }

    auto shrinkToSize ( Size ) noexcept -> void;

    auto remove ( ElementCRef , Size ) noexcept -> bool final;
    auto removeLast ( ElementCRef ) noexcept -> bool final;

    auto removeOf ( Collection < ElementType > const &, Size ) noexcept -> bool final;
    auto removeLastOf ( Collection < ElementType > const & ) noexcept -> bool final;
    auto removeNotOf ( Collection < ElementType > const &, Size ) noexcept -> bool final;
    auto removeLastNotOf ( Collection < ElementType > const & ) noexcept -> bool final;

    auto remove ( CollectionIterator const & ) noexcept(false) -> ElementType final;

    auto removeOf ( InitializerList, Size ) noexcept -> bool final;
    auto removeLastOf ( InitializerList ) noexcept -> bool final;
    auto removeNotOf ( InitializerList, Size ) noexcept -> bool final;
    auto removeLastNotOf ( InitializerList ) noexcept -> bool final;

    __CDS_cpplang_NonConstConstexprMemberFunction auto back () noexcept (false) -> ElementRef final {
        if ( this->empty() )
            throw OutOfBoundsException("Array is Empty");

        return * this->_pData[this->_size - 1];
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto front () noexcept (false) -> ElementRef final {
        if ( this->empty() )
            throw OutOfBoundsException("Array is Empty");

        return * this->_pData[0];
    }

    __CDS_cpplang_ConstexprConditioned auto back () const noexcept (false) -> ElementCRef final {
        if ( this->empty() )
            throw OutOfBoundsException("Array is Empty");

        return * this->_pData[this->_size - 1];
    }

    __CDS_cpplang_ConstexprConditioned auto front () const noexcept (false) -> ElementCRef final {
        if (this->empty())
            throw OutOfBoundsException("Array is Empty");

        return *this->_pData[0];
    }

    auto operator == (Array const & o) const noexcept -> bool {
        if ( this == & o ) return true;
        if ( o.size() != this->size() ) return false;

        for ( auto i1 = this->begin(), i2 = o.begin(); i1 != this->end() && i2 != o.end(); i1++, i2++ )
            if ( ! ( Type < T > :: compare ( i1.value(), i2.value() ) ) )
                return false;
        return true;
    }

    __CDS_OptimalInline auto operator != (Array const & o) const noexcept -> bool {
        return ! this->operator==(o);
    }

    __CDS_NoDiscard auto equals (Object const & o) const noexcept -> bool final {
        if (this == &o) return true;
        auto p = dynamic_cast < decltype(this) > ( &o );
        if (p == nullptr) return false;

        return this->operator==(*p);
    }

    auto clear () noexcept -> void final;
    auto makeUnique () noexcept -> void final;
    auto contains ( ElementCRef ) const noexcept -> bool final;

    __CDS_NoDiscard auto toString () const noexcept -> String final;

    auto index ( ElementCRef ) const noexcept -> Index final;
    auto index ( ElementRef ) noexcept -> Index final;

    __CDS_MaybeUnused auto indices ( ElementCRef ) const noexcept -> DoubleLinkedList < Index >;

private:
    auto pAt (Index) noexcept (false) -> ElementPtr override;
    auto pAt (Index) const noexcept (false) -> ElementCPtr override;

public:

    auto popFront () noexcept (false) -> ElementType final {
        if ( this->empty() )
            throw OutOfBoundsException("Array is Empty");

        auto retVal = * this->_pData[0];
        delete Utility::exchange(this->_pData[0], nullptr);

        for ( Index i = 0; i < this->size() - 1; i ++ )
            this->_pData[i] = this->_pData[i + 1];

        this->_pData[-- this->_size] = nullptr;

        return retVal;
    }

    auto popBack () noexcept (false) -> ElementType final {
        if ( this->empty() )
            throw OutOfBoundsException("Array is Empty");

        auto v = * this->_pData[--this->_size];
        delete Utility::exchange(this->_pData[this->_size], nullptr);

        return v;
    }

private:

    auto allocFrontGetPtr () noexcept -> ElementPtrRef override;
    auto allocBackGetPtr () noexcept -> ElementPtrRef override;
    __CDS_OptimalInline auto allocInsertGetPtr (ElementCRef e __CDS_MaybeUnused) noexcept -> ElementPtrRef override {
        return this->allocBackGetPtr();
    }

#if defined(__JETBRAINS_IDE__)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
#endif

    template < typename SortFunc, typename U = T, EnableIf < Type < U > :: copyAssignable > = 0 >
    auto static quickSort ( Iterator, Iterator, SortFunc const & ) noexcept -> void;

    template < typename SortFunc, typename U = T, EnableIf < Type < U > :: copyAssignable > = 0 >
    auto static quickSortPartition ( Iterator, Iterator, SortFunc const & ) noexcept -> Iterator;

#if defined(__JETBRAINS_IDE__)
#pragma clang diagnostic pop
#endif

public:
    template < typename SortFunc, typename U = T, EnableIf < Type < U > :: copyAssignable > = 0 >
    auto sort ( SortFunc const & ) noexcept -> void;

    template < typename U = T, EnableIf < Type < U > :: copyAssignable > = 0 >
    __CDS_OptimalInline auto sort ( Comparator < ElementType > const & c ) noexcept -> void {

        return this->sort ( [&c] (ElementCRef a, ElementCRef b) noexcept -> bool { return c(a, b); } );
    }

    auto operator = ( Collection < ElementType > const & ) noexcept -> Array &;

    __CDS_OptimalInline auto operator = ( Array const & o ) noexcept -> Array & { // NOLINT(bugprone-unhandled-self-assignment)
        return this->operator=( ( Collection<ElementType> const & )(o) );  // NOLINT(misc-unconventional-assign-operator)
    }

    __CDS_OptionalInline auto operator = ( Array && array ) noexcept -> Array & {
        if ( this == & array ) return * this;

        for ( Index i = 0; i < this->_size; ++ i )
            delete this->_pData[i];
        delete [] this->_pData;

        this->_pData = Utility :: exchange ( array._pData, nullptr );
        this->_capacity = Utility :: exchange ( array._capacity, 0 );
        this->_size = Utility :: exchange ( array._size, 0 );

        return * this;
    }

    auto sequence () const & noexcept -> Sequence < Array < T > const >;
    auto sequence () & noexcept -> Sequence < Array < T > >;
    auto sequence () const && noexcept -> Sequence < Array < T > const >;
    auto sequence () && noexcept -> Sequence < Array < T > >;
};

template < typename T >
class Array < T > :: IteratorBase : public Collection < T > :: Iterator {
protected:
    friend class Array;
    Index mutable   _index  { 0ull };
    Array         * _pArray { nullptr };

    constexpr IteratorBase( IteratorBase const & ) noexcept = default;
    constexpr IteratorBase( IteratorBase && ) noexcept = default;
    explicit constexpr IteratorBase( Array * pArray, Index index ) noexcept :
            Collection < T > :: Iterator( pArray ),
            _index(index),
            _pArray(pArray) {

    }

public:
    __CDS_cpplang_ConstexprDestructor ~IteratorBase() noexcept override = default;

    __CDS_cpplang_ConstexprOverride auto equals ( CollectionIterator const & o ) const noexcept -> bool final {
        if ( & o == this ) return true;
        auto p = dynamic_cast < IteratorBase const * > ( &o );
        if ( p == nullptr ) return false;

        return p->_pArray == this->_pArray && p->_index == this->_index;
    }

    __CDS_cpplang_ConstexprOverride auto value () const noexcept -> ElementRef final {
        return (* this->_pArray)[this->_index];
    }

    __CDS_NoDiscard auto copy () const noexcept -> IteratorBase * override = 0;
};

template < typename T >
class Array < T > :: ConstIteratorBase : public Collection < T > :: ConstIterator {
protected:
    friend class Array;
    Index mutable _index  { 0ull };
    Array const * _pArray { nullptr };

    constexpr ConstIteratorBase( ConstIteratorBase const & ) noexcept = default;
    constexpr ConstIteratorBase( ConstIteratorBase && ) noexcept = default;
    constexpr explicit ConstIteratorBase (Array const * pArray, Index index) noexcept :
            Collection < T > :: ConstIterator ( pArray ),
            _index(index),
            _pArray(pArray) {

    }

public:
    __CDS_cpplang_ConstexprDestructor ~ConstIteratorBase() noexcept override = default;

    __CDS_cpplang_ConstexprOverride auto equals ( ConstCollectionIterator const & o ) const noexcept -> bool final {
        if ( & o == this ) return true;
        auto p = dynamic_cast < ConstIteratorBase const * > ( &o );
        if ( p == nullptr ) return false;

        return p->_pArray == this->_pArray && p->_index == this->_index;
    }

    __CDS_cpplang_ConstexprOverride auto value () const noexcept -> ElementCRef final {
        return (* this->_pArray)[this->_index];
    }

    __CDS_NoDiscard auto copy () const noexcept -> ConstIteratorBase * override = 0;
};

template < typename T >
class Array < T > :: Iterator : public IteratorBase {
public:

    constexpr Iterator ( Iterator const & ) noexcept = default;
    constexpr Iterator ( Iterator && ) noexcept = default;

    constexpr explicit Iterator ( Array * pArray, Index index ) noexcept :
            IteratorBase( pArray, index ) {

    }

    __CDS_cpplang_ConstexprDestructor ~Iterator () noexcept override = default;

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( Iterator const & o ) noexcept -> Iterator & {
        if ( this == & o ) return * this;

        this->_pArray = o._pArray;
        this->_index = o._index;
        return * this;
    }

    __CDS_cpplang_ConstexprOverride auto operator == (Iterator const & o) const noexcept -> bool {
        return this->equals(o);
    }

    __CDS_cpplang_ConstexprOverride auto operator != (Iterator const & o) const noexcept -> bool {
        return !this->equals(o);
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto next () noexcept -> Iterator & final {
        this->_index ++;
        return * this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto prev () noexcept -> Iterator & {
        this->_index --;
        return * this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> Iterator & override {
        return this->next();
    }

    __CDS_cpplang_ConstexprDestructor auto operator ++ (int) noexcept -> Iterator {
        auto copy = * this;
        this->next();
        return copy;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> Iterator & {
        return this->prev();
    }

    __CDS_cpplang_ConstexprDestructor auto operator -- (int) noexcept -> Iterator {
        auto copy = * this;
        this->prev();
        return copy;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto copy () const noexcept -> Iterator * override {
        return new Iterator ( * this );
    }
};

template < typename T >
class Array < T > :: ReverseIterator : public IteratorBase {
public:

    constexpr ReverseIterator ( ReverseIterator const & ) noexcept = default;
    constexpr ReverseIterator ( ReverseIterator && ) noexcept = default;

    constexpr explicit ReverseIterator ( Array * pArray, Index index ) noexcept :
            IteratorBase( pArray, index ) {

    }

    __CDS_cpplang_ConstexprDestructor ~ReverseIterator () noexcept override = default;

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( ReverseIterator const & o ) noexcept -> ReverseIterator & {
        if ( this == & o ) return * this;

        this->_pArray = o._pArray;
        this->_index = o._index;
        return * this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto next () noexcept -> ReverseIterator & final {
        this->_index --;
        return * this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto prev () noexcept -> ReverseIterator & {
        this->_index ++;
        return * this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ReverseIterator & final {
        return this->next();
    }

    __CDS_cpplang_ConstexprDestructor auto operator ++ (int) noexcept -> ReverseIterator {
        auto copy = * this;
        this->next();
        return copy;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> ReverseIterator & {
        return this->prev();
    }

    __CDS_cpplang_ConstexprDestructor auto operator -- (int) noexcept -> ReverseIterator {
        auto copy = * this;
        this->prev();
        return copy;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto copy () const noexcept -> ReverseIterator * override {
        return new ReverseIterator ( * this );
    }
};

template < typename T >
class Array < T > :: ConstIterator : public ConstIteratorBase {
public:

    constexpr ConstIterator ( ConstIterator const & ) noexcept = default;
    constexpr ConstIterator ( ConstIterator && ) noexcept = default;

    constexpr explicit ConstIterator ( Array const * pArray, Index index ) noexcept :
            ConstIteratorBase( pArray, index ) {

    }

    __CDS_cpplang_ConstexprDestructor ~ConstIterator () noexcept override = default;

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( ConstIterator const & o ) noexcept -> ConstIterator & {
        if ( this == & o ) return * this;

        this->_pArray = o._pArray;
        this->_index = o._index;
        return * this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto next () noexcept -> ConstIterator & final {
        this->_index ++;
        return * this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto prev () noexcept -> ConstIterator & {
        this->_index --;
        return * this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ConstIterator & override {
        return this->next();
    }

    __CDS_cpplang_ConstexprDestructor auto operator ++ (int) noexcept -> ConstIterator {
        auto copy = * this;
        this->next();
        return copy;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> ConstIterator & {
        return this->prev();
    }

    __CDS_cpplang_ConstexprDestructor auto operator -- (int) noexcept -> ConstIterator {
        auto copy = * this;
        this->prev();
        return copy;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto copy () const noexcept -> ConstIterator * override {
        return new ConstIterator ( * this );
    }
};

template < typename T >
class Array < T > :: ConstReverseIterator : public ConstIteratorBase {
public:
    constexpr ConstReverseIterator ( ConstReverseIterator const & ) noexcept = default;
    constexpr ConstReverseIterator ( ConstReverseIterator && ) noexcept = default;

    constexpr explicit ConstReverseIterator ( Array const * pArray, Index index ) noexcept :
            ConstIteratorBase( pArray, index ) {

    }

    __CDS_cpplang_ConstexprDestructor ~ConstReverseIterator () noexcept override = default;

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( ConstReverseIterator const & o ) noexcept -> ConstReverseIterator & {
        if ( this == & o ) return * this;

        this->_pArray = o._pArray;
        this->_index = o._index;
        return * this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto next () noexcept -> ConstReverseIterator & final {
        this->_index --;
        return * this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto prev () noexcept -> ConstReverseIterator & {
        this->_index ++;
        return * this;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ConstReverseIterator & {
        return this->next();
    }

    __CDS_cpplang_ConstexprDestructor auto operator ++ (int) noexcept -> ConstReverseIterator {
        auto copy = * this;
        this->next();
        return copy;
    }

    __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> ConstReverseIterator & {
        return this->prev();
    }

    __CDS_cpplang_ConstexprDestructor auto operator -- (int) noexcept -> ConstReverseIterator {
        auto copy = * this;
        this->prev();
        return copy;
    }

    __CDS_NoDiscard __CDS_OptimalInline auto copy () const noexcept -> ConstReverseIterator * override {
        return new ConstReverseIterator ( * this );
    }
};

template < typename T >
template < typename V, EnableIf < Type < V > :: copyConstructible > >
Array<T>::Array( InitializerList initializerList ) noexcept {
    for ( auto & e : initializerList )
        this->pushBack( e );
}

template <class T>
Array<T>::~Array() noexcept {
    for ( Index i = 0; i < this->_capacity; i++ )
        delete Utility::exchange(this->_pData[i], nullptr);
    delete [] Utility::exchange(this->_pData, nullptr);
}

template < typename T >
auto Array < T > :: allocFrontGetPtr () noexcept -> ElementPtrRef {

    if ( this->_size < this->_capacity ) {
        delete Utility::exchange(this->_pData[ this->_size ++ ], nullptr);
        for ( Index i = this->_size - 1; i > 0; -- i )
            this->_pData[i] = this->_pData[i - 1];

        return (this->_pData[0] = nullptr);
    }

    auto newSize = this->_capacity * 2;
    auto newBuf = new T * [ newSize ];
    std::memcpy ( newBuf + 1, this->_pData, this->_size * sizeof ( T * ) );
    std::memset ( newBuf + 1 + this->_size, 0, (newSize - this->_size - 1) * sizeof(T *) );

    this->_capacity = newSize;
    this->_size ++;

    delete [] Utility::exchange ( this->_pData, newBuf );

    return (this->_pData[0] = nullptr);
}

#if defined(_MSC_VER)

#pragma push_macro("min")
#pragma push_macro("max")
#undef min
#undef max

#endif

template < typename T >
auto Array < T > :: allocBackGetPtr () noexcept -> ElementPtrRef {

    if ( this->_size < this->_capacity )
        return (this->_pData[ this->_size ++ ] = nullptr);

    auto newSize = std :: max ( this->_capacity * 2, this->_size + 1 );
    T ** newBuf = new T * [newSize];

    std::memcpy ( newBuf, this->_pData, this->_size * sizeof(T *) );
    std::memset ( newBuf + this->_size, 0, ( newSize - this->_size ) * sizeof (T*) );

    this->_capacity = newSize;
    delete [] Utility::exchange ( this->_pData, newBuf );

    return (this->_pData[this->_size ++] = nullptr);
}

#if defined(_MSC_VER)

#pragma pop_macro("max")
#pragma pop_macro("min")

#endif

template < typename T >
auto Array<T>::toString() const noexcept -> String {
    if ( this->empty() )
        return {"[ ]"};

    std::stringstream out;
    out << "[ ";

    for ( const auto & e : (*this) )
        Type < T > :: streamPrint( out, e ) << ", ";

    auto s = out.str();
    return s.substr(0, s.length() - 2).append(" ]");
}

#if defined(_MSC_VER)
#pragma push_macro("max")
#undef max
#endif

template < typename T >
__CDS_MaybeUnused auto Array<T>::expandWith(Size requiredSize) noexcept -> void {
    if ( this->_size + requiredSize < this->_capacity ) return;

    return this->_resize(std::max(this->_size + requiredSize, this->_capacity * 2));
}

#if defined(_MSC_VER)
#pragma pop_macro("max")
#endif

template < typename T >
auto Array<T>::shrinkToSize(Size size) noexcept -> void {
    if ( this->_capacity <= size ) return;

    return this->_resize(size);
}

#if defined(_MSC_VER)

#pragma push_macro("min")
#pragma push_macro("max")
#undef min
#undef max

#endif

template < typename T >
auto Array<T>::_resize(Size size) noexcept -> void {
    auto newMemory = new ElementType * [ size ];

    for ( auto i = static_cast < SignedSize > ( this->_size ) - 1; i >= static_cast < SignedSize > ( size ); -- i )
        delete Utility::exchange(this->_pData[i], nullptr);

    std :: memcpy ( newMemory, this->_pData, sizeof ( T * ) * ( std :: min ( this->_size, size ) ) );

    if ( size > this->_size )
        std :: memset ( newMemory + this->_size, 0, sizeof ( T * ) * ( size - this->_size ) );

    delete [] Utility::exchange ( this->_pData, newMemory );
    this->_capacity = size;
}

#if defined(_MSC_VER)

#pragma pop_macro("max")
#pragma pop_macro("min")

#endif

template < typename T >
Array<T>::Array( Array const & o ) noexcept :
        _pData( new T * [o.size()] ),
        _capacity( o.size() ){

    this->_size = o.size();
    for ( auto i = 0; i < o.size(); ++ i )
        this->_pData[i] = new T(*o._pData[i]);
}

template < typename T >
Array<T>::Array( Array && moveObj ) noexcept {
    this->_pData = Utility::exchange(moveObj._pData, nullptr);
    this->_size = Utility::exchange(moveObj._size, 0);
    this->_capacity = Utility::exchange(moveObj._capacity, 0);
}

#include <CDS/Pointer>
template < typename T >
Array<T>::Array(
        CollectionIterator const & from,
        CollectionIterator const & to
) noexcept {
    for ( auto it = UniquePointer < decltype ( & from ) > ( from.copy() ); ! it->equals (to); it->next() )
        this->pushBack( it->value() );
}

template < typename T >
Array<T>::Array(
        ConstCollectionIterator const & from,
        ConstCollectionIterator const & to
) noexcept {
    for ( auto it = UniquePointer < decltype ( & from ) > ( from.copy() ); ! it->equals (to); it->next() )
        this->pushBack( it->value() );
}

template < typename T >
Array < T > :: Array ( Collection < T > const & collection ) noexcept {
    collection.forEach([this](T const & e){this->pushBack(e);});
}

template < typename T >
template < typename V, EnableIf < Type < V > :: defaultConstructible > >
Array < T > :: Array ( Size size ) noexcept :
        _pData ( new T * [size] ),
        _capacity ( size ) {

    this->_size = size;
    for ( Index i = 0; i < this->_size; ++ i )
        this->_pData [i] = new T;
}

template < typename T >
template < typename V, EnableIf < Type < V > :: copyConstructible > >
Array<T>::Array ( Size size, ElementCRef defaultValue ) noexcept :
        _pData(new T * [size]),
        _capacity(size){

    this->_size = size;
    for ( Index i = 0; i < this->_size; ++ i )
        this->_pData[i] = new T ( defaultValue );
}

template < typename T >
auto Array<T>::remove(ElementCRef e, Size count) noexcept -> bool {
    bool removed = false;

    T ** newBuf = new T * [this->size()];

    Index i = 0, l = 0, c = 0;
    for (; i < this->size() && c < count; i++)
        if ( ! Type < T > :: compare ( * this->_pData[i], e ) ) {
            newBuf[l++] = this->_pData[i];
        } else {
            removed = true;
            ++ c;
            delete Utility::exchange(this->_pData[i], nullptr);
        }

    this->_capacity = this->size();
    this->_size = l;

    memset ( newBuf + l, 0, (this->_capacity - l) * sizeof(T *) );
    delete [] Utility::exchange ( this->_pData, newBuf );

    return removed;
}

#include <CDS/Range>
template < typename T >
auto Array<T>::removeLast(ElementCRef e) noexcept -> bool {
    Index at = -1;
    for ( Index i = this->size() - 1; i >= 0; -- i )
        if ( Type < T > :: compare ( * this->_pData[i], e ) ) {
            at = i;
            break;
        }

    if ( at == -1 ) return false;

    delete Utility::exchange(this->_pData[at], nullptr);

    T ** pNewBuf = new T * [ this->size() - 1 ];
    std::memcpy ( pNewBuf, this->_pData, at * sizeof ( T * ) );
    std::memcpy ( pNewBuf + at, this->_pData + at + 1, (this->size() - at - 1) * sizeof(T *) );

    this->_capacity = -- this->_size;
    delete [] Utility::exchange ( this->_pData, pNewBuf );
    return true;
}

template < typename T >
auto Array<T>::removeOf(Collection<ElementType> const & elements, Size count) noexcept -> bool {
    bool removed = false;

    T ** newBuf = new T * [this->size()];

    Index i = 0, l = 0, c = 0;
    for (; i < this->size() && c < count; i++)
        if ( ! elements.contains ( * this->_pData[i] ) ) {
            newBuf[l++] = this->_pData[i];
        } else {
            removed = true;
            ++ c;
            delete Utility::exchange(this->_pData[i], nullptr);
        }

    this->_capacity = this->size();
    this->_size = l;

    std::memset ( newBuf + l, 0, (this->_capacity - this->_size) * sizeof ( T * ) );
    delete [] Utility::exchange ( this->_pData, newBuf );

    return removed;
}

template < typename T >
auto Array<T>::removeOf ( InitializerList elements, Size count ) noexcept -> bool {
    bool removed = false;

    T ** newBuf = new T * [this->size()];
    Index i = 0, l = 0, c = 0;
    for (; i < this->size() && c < count; i++)
        if ( ! Collection < T > :: iListContains ( elements, * this->_pData[i] ) ) {
            newBuf[l++] = this->_pData[i];
        } else {
            removed = true;
            ++ c;
            delete Utility::exchange(this->_pData[i], nullptr);
        }

    this->_capacity = this->size();
    this->_size = l;

    std::memset ( newBuf + l, 0, (this->_capacity - this->_size) * sizeof ( T * ) );
    delete [] Utility::exchange ( this->_pData, newBuf );

    return removed;
}

template < typename T >
auto Array<T>::removeNotOf( Collection<ElementType> const & elements, Size count) noexcept -> bool {
    bool removed = false;

    T ** newBuf = new T * [this->size()];
    Index i = 0, l = 0, c = 0;
    for (; i < this->size() && c < count; i++)
        if ( elements.contains ( * this->_pData[i] ) ) {
            newBuf[l++] = this->_pData[i];
        } else {
            removed = true;
            ++ c;
            delete Utility::exchange(this->_pData[i], nullptr);
        }

    this->_capacity = this->size();
    this->_size = l;
    std::memset ( newBuf + l, 0, (this->_capacity - this->_size) * sizeof ( T * ) );
    delete [] Utility::exchange ( this->_pData, newBuf );
    return removed;
}

template < typename T >
auto Array<T>::removeNotOf( InitializerList elements, Size count ) noexcept -> bool {
    bool removed = false;

    T ** newBuf = new T * [this->size()];
    Index i = 0, l = 0, c = 0;
    for (; i < this->size() && c < count; i++)
        if ( Collection < T > :: iListContains( elements, * this->_pData[i] ) ) {
            newBuf[l++] = this->_pData[i];
        } else {
            removed = true;
            ++ c;
            delete Utility::exchange(this->_pData[i], nullptr);
        }

    this->_capacity = this->size();
    this->_size = l;
    std::memset ( newBuf + l, 0, (this->_capacity - this->_size) * sizeof ( T * ) );
    delete [] Utility::exchange ( this->_pData, newBuf );
    return removed;
}

template < typename T >
auto Array<T>::removeLastOf(Collection<ElementType> const & elements) noexcept -> bool {
    Index at = -1;
    for ( Index i = this->size() - 1; i >= 0; -- i )
        if ( elements.contains( * this->_pData[i] ) ) {
            at = i;
            break;
        }

    if ( at == -1 ) return false;

    delete Utility::exchange(this->_pData[at], nullptr);

    T ** pNewBuf = new T * [ this->size() - 1 ];
    std::memcpy ( pNewBuf, this->_pData, at * sizeof ( T * ) );
    std::memcpy ( pNewBuf + at, this->_pData + at + 1, (this->size() - at - 1) * sizeof(T *) );
    delete [] Utility::exchange ( this->_pData, pNewBuf );
    this->_capacity = -- this->_size;
    return true;
}

template < typename T >
auto Array<T>::removeLastOf( InitializerList elements ) noexcept -> bool {
    Index at = -1;
    for ( Index i = this->size() - 1; i >= 0; -- i )
        if ( Collection<T>::iListContains( elements, * this->_pData[i] ) ) {
            at = i;
            break;
        }

    if ( at == -1 ) return false;

    delete Utility::exchange(this->_pData[at], nullptr);

    T ** pNewBuf = new T * [ this->size() - 1 ];
    std::memcpy ( pNewBuf, this->_pData, at * sizeof ( T * ) );
    std::memcpy ( pNewBuf + at, this->_pData + at + 1, (this->size() - at - 1) * sizeof(T *) );
    delete [] Utility::exchange ( this->_pData, pNewBuf );
    this->_capacity = -- this->_size;
    return true;
}

template < typename T >
auto Array<T>::removeLastNotOf( Collection < ElementType > const & elements ) noexcept -> bool {
    Index at = -1;
    for ( Index i = this->size() - 1; i >= 0; -- i )
        if ( ! elements.contains( * this->_pData[i] ) ) {
            at = i;
            break;
        }

    if ( at == -1 ) return false;

    delete Utility::exchange(this->_pData[at], nullptr);

    T ** pNewBuf = new T * [ this->size() - 1 ];
    std::memcpy ( pNewBuf, this->_pData, at * sizeof ( T * ) );
    std::memcpy ( pNewBuf + at, this->_pData + at + 1, (this->size() - at - 1) * sizeof(T *) );
    delete [] Utility::exchange ( this->_pData, pNewBuf );
    this->_capacity = -- this->_size;
    return true;
}

template < typename T >
auto Array<T>::removeLastNotOf( InitializerList elements) noexcept -> bool {
    Index at = -1;
    for ( Index i = this->size() - 1; i >= 0; -- i )
        if ( ! Collection < T > ::iListContains( elements, * this->_pData[i] ) ) {
            at = i;
            break;
        }

    if ( at == -1 ) return false;

    delete Utility::exchange(this->_pData[at], nullptr);

    T ** pNewBuf = new T * [ this->size() - 1 ];
    std::memcpy ( pNewBuf, this->_pData, at * sizeof ( T * ) );
    std::memcpy ( pNewBuf + at, this->_pData + at + 1, (this->size() - at - 1) * sizeof(T *) );
    delete [] Utility::exchange ( this->_pData, pNewBuf );
    this->_capacity = -- this->_size;
    return true;
}

#include <CDS/Utility>
template < typename T >
auto Array<T>::remove( CollectionIterator const & it ) noexcept (false) -> ElementType {
    if ( ! Collection < T > :: iteratorIsOf (it, *this) )
        throw IllegalArgumentException("Iterator given is not of this collection");

    Index at = reinterpret_cast < Iterator const * > ( & it )->_index;

    if ( at < 0 || at >= this->size() )
        throw OutOfBoundsException(at, this->size());


    T retVal = * this->_pData[at];
    delete Utility::exchange(this->_pData[at], nullptr);

    T ** pNewBuf = new T * [ this->size() - 1 ];
    std::memcpy ( pNewBuf, this->_pData, at * sizeof ( T * ) );
    std::memcpy ( pNewBuf + at, this->_pData + at + 1, (this->size() - at - 1) * sizeof(T *) );
    delete [] Utility::exchange ( this->_pData, pNewBuf );
    this->_capacity = -- this->_size;
    return retVal;
}

template < typename T >
auto Array<T>::clear() noexcept -> void {
    for ( Index i = 0; i < this->_size; ++ i )
        delete Utility::exchange ( this->_pData[i], nullptr );
    this->_size = 0;
}

template < typename T >
auto Array<T> :: makeUnique() noexcept -> void {
    T ** pNewData = new T * [this->size()];
    Size l = 0;

    static auto newArrContains = [](T ** p, Size l, ElementCRef e) noexcept -> bool {
        for ( Index i = 0; i < l; ++ i )
            if ( Type < T > :: compare ( * p[i], e ) )
                return true;
        return false;
    };

    for ( Index i = 0; i < this->size(); ++ i )
        if ( ! newArrContains(pNewData, l, * this->_pData[i]) )
            pNewData[l ++] = this->_pData[i];
        else
            delete Utility::exchange(this->_pData[i], nullptr);

    std :: memset ( pNewData + l, 0, (this->size() - l) * sizeof(T *) );

    this->_capacity = this->size();
    this->_size = l;

    delete [] Utility::exchange ( this->_pData, pNewData );
}

template < typename T >
auto Array<T>::contains( ElementCRef value ) const noexcept -> bool {
    for ( auto & e : * this ) // NOLINT(readability-use-anyofallof)
        if ( Type < T > :: compare ( e, value ) )
            return true;
    return false;
}

template < typename T >
auto Array<T>::index( ElementCRef value ) const noexcept -> Index {
    Index i = 0;
    for ( auto & e : * this )
        if ( Type < T > :: compare ( e, value ) )
            return i;
        else
            i++;
    return -1;
}

template < typename T >
auto Array<T>::index( ElementRef value ) noexcept -> Index {
    Index i = 0;
    for ( auto & e : * this )
        if ( Type < T > :: compare ( e, value ) )
            return i;
        else
            i++;
    return -1;
}

#include <CDS/LinkedList>

template < typename T >
__CDS_MaybeUnused auto Array<T>::indices( ElementCRef value ) const noexcept -> DoubleLinkedList < Index > {
    DoubleLinkedList < Index > indices;

    Index i = 0;
    for ( auto & e : * this ) {
        if ( Type < T > :: compare ( e, value ) )
            indices.pushBack(i);
        i++;
    }

    return indices;
}

#include <CDS/Utility>
template < typename T >
auto Array < T > :: pAt ( Index i ) noexcept (false) -> ElementPtr {
    if ( this->empty() )
        throw OutOfBoundsException ( i, 0 );

    if ( i < 0 )
        i += ( this->size() / (-i) ) * this->size();
    if ( i >= static_cast<Index>(this->size()) )
        i = i % this->size();

    return this->_pData[i];
}

template < typename T >
auto Array < T > :: pAt ( Index i ) const noexcept (false) -> ElementCPtr {
    if ( this->empty() )
        throw OutOfBoundsException ( i, 0 );

    if ( i < 0 )
        i += ( this->size() / (-i) ) * this->size();
    if ( i >= static_cast<Index>(this->size()) )
        i = i % this->size();

    return this->_pData[i];
}

template < typename T >
Array<T> & Array<T>::operator= (Collection<ElementType> const & c) noexcept {
    if ( this == & c ) return * this;

    this->clear();

    auto pBegin = Collection<T>::beginPtr(c);
    auto pEnd = Collection<T>::endPtr(c);

    for ( auto it = pBegin; ! it->equals( * pEnd ); it->next() )
        this->pushBack ( it->value() );

    delete pBegin;
    delete pEnd;
    return * this;
}

template < typename T >
template < typename SortFunc, typename U, EnableIf < Type < U > :: copyAssignable > >
__CDS_MaybeUnused auto Array<T>::quickSortPartition(
        Iterator from,
        Iterator to,
        SortFunc const & sortFunc
) noexcept -> Iterator {
    __CDS_cpplang_ConstexprLambda static auto swap = [] ( T & a, T & b ) { auto aux = a; a = b; b = aux; };

    auto pivot = to.value();
    Iterator partitionIterator ( from );
    Iterator previous (nullptr, -1);

    for ( auto it = from; it != to; it++ ) {
        if ( sortFunc ( it.value(), pivot ) ) {
            swap ( partitionIterator.value(), it.value() );
            previous = partitionIterator;
            partitionIterator.next();
        }
    }

    swap ( partitionIterator.value(), to.value() );
    if ( previous._index == -1 )
        return partitionIterator;
    return previous;
}

template < typename T >
template < typename SortFunc, typename U, EnableIf < Type < U > :: copyAssignable > >
__CDS_MaybeUnused auto Array<T>::quickSort(
        Iterator from,
        Iterator to,
        SortFunc const & sortFunc
) noexcept -> void {
    __CDS_cpplang_ConstexprLambda static auto validIterator = []( Iterator & it ) noexcept->bool { return it._index >= 0 && it._index < it._pArray->_size; };

    auto next = to;
    if ( next._index < next._pArray->_size ) {
        next.next();
        if ( from == next )
            return;
    }

    if ( from != to && validIterator(from) && validIterator(to) ) {
        auto partitionIterator = Array::quickSortPartition(from, to, sortFunc);

        Array::quickSort(from, partitionIterator, sortFunc);

        if ( ! validIterator(partitionIterator) )
            return;

        if ( partitionIterator == from ) {
            partitionIterator.next();
            if ( validIterator ( partitionIterator ) )
                Array::quickSort(partitionIterator, to, sortFunc);
            return;
        }

        partitionIterator.next();
        if ( ! validIterator(partitionIterator) )
            return;
        partitionIterator.next();
        Array::quickSort( partitionIterator, to, sortFunc );
    }
}

template < typename T >
template < typename SortFunc, typename U, EnableIf < Type < U > :: copyAssignable > >
auto Array<T>::sort(SortFunc const & sortFunc) noexcept -> void {
    if ( this->size() < 2 )
        return;

    Array::quickSort( this->begin(), -- this->end(), sortFunc );
}

#include <CDS/Sequence>

template < typename T >
auto Array < T > :: sequence () const & noexcept -> Sequence < Array < T > const > {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
}

template < typename T >
auto Array < T > :: sequence () & noexcept -> Sequence < Array < T > > {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
}

template < typename T >
auto Array < T > :: sequence () const && noexcept -> Sequence < Array < T > const > {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (std::move(*this));
}

template < typename T >
auto Array < T > :: sequence () && noexcept -> Sequence < Array < T > > {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (std::move(*this));
}

#if __CDS_cpplang_CTAD_available == true

template < typename T >
Array ( std::initializer_list < T > ) -> Array < T >;

#endif

__CDS_RegisterParseTypeTemplateT(Array)

#endif //CDS_ARRAY_HPP
