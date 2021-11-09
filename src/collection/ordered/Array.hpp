//
// Created by loghin on 01.03.2021.
//

#ifndef CDS_ARRAY_HPP
#define CDS_ARRAY_HPP

#include <CDS/List>
#include <CDS/Memory>

namespace cds {

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

    public:
        using Iterator                      = typename List < T > :: Iterator;
        using ConstIterator                 = typename List < T > :: ConstIterator;

        using ReverseIterator               = typename List < T > :: ReverseIterator;
        using ConstReverseIterator          = typename List < T > :: ConstReverseIterator;

    private:
        using DelegateIterator              = typename List < T > :: DelegateIterator;
        using DelegateConstIterator         = typename List < T > :: DelegateConstIterator;

        using InitializerList               = typename List < T > :: InitializerList;

        __CDS_MaybeUnused auto expandWith ( Size ) noexcept -> void;

    public:

        Array () noexcept = default;
        Array ( Array const & ) noexcept;
        Array ( Array && ) noexcept;

        Array (
            Iterator const &,
            Iterator const &
        ) noexcept;

        Array (
            ConstIterator const &,
            ConstIterator const &
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
        auto _resize ( Size ) noexcept -> void;

    public:

        template < typename V = T, EnableIf < Type < V > :: defaultConstructible > = 0 >
        __CDS_OptionalInline auto resize ( Size newSize ) noexcept -> void {
            this->_resize(newSize);
            for ( auto i = this->_size; i < newSize; ++ i )
                this->_pData[i] = Memory :: instance ().create < T > ();
            this->_size = newSize;
        }

        template < EnableIf < Type < T > :: copyConstructible > = 0 >
        __CDS_OptionalInline auto resize ( Size newSize, ElementCRef value ) noexcept -> void {
            this->_resize(newSize);
            for ( auto i = this->_size; i < newSize; ++ i )
                this->_pData[i] = Memory :: instance ().create < T > (value);
            this->_size = newSize;
        }

        auto shrinkToSize ( Size ) noexcept -> void;

        auto remove ( ElementCRef , Size ) noexcept -> bool final;
        auto removeLast ( ElementCRef ) noexcept -> bool final;

        auto removeOf ( Collection < ElementType > const &, Size ) noexcept -> bool final;
        auto removeLastOf ( Collection < ElementType > const & ) noexcept -> bool final;
        auto removeNotOf ( Collection < ElementType > const &, Size ) noexcept -> bool final;
        auto removeLastNotOf ( Collection < ElementType > const & ) noexcept -> bool final;

        auto remove ( Iterator const & ) noexcept(false) -> ElementType final;

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

        __CDS_OptionalInline auto operator == (Array const & o) const noexcept -> bool {
            if ( this == & o ) return true;
            if ( o.size() != this->size() ) return false;

            for ( auto i1 = this->begin(), i2 = o.begin(); i1 != this->end() && i2 != o.end(); i1++, i2++ )
                if ( ! ( Type < T > :: compare ( * i1, * i2 ) ) )
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

        __CDS_OptionalInline auto popFront () noexcept (false) -> ElementType final {
            if ( this->empty() )
                throw OutOfBoundsException("Array is Empty");

            auto retVal = * this->_pData[0];
            Memory :: instance().destroy ( exchange(this->_pData[0], nullptr) );

            for ( Index i = 0; i < this->size() - 1; i ++ )
                this->_pData[i] = this->_pData[i + 1];

            this->_pData[-- this->_size] = nullptr;

            return retVal;
        }

        __CDS_OptionalInline auto popBack () noexcept (false) -> ElementType final {
            if ( this->empty() )
                throw OutOfBoundsException("Array is Empty");

            auto v = * this->_pData[--this->_size];
            Memory :: instance().destroy ( exchange(this->_pData[this->_size], nullptr) );

            return v;
        }

    private:

        class ArrayDelegateIterator : public DelegateIterator {
        private:
            ForeignPointer < Array >    _pArray;
            Index                       _index;
            bool                        _forward;

        public:
            constexpr ArrayDelegateIterator ( Array * pArray, Index index, bool forward ) noexcept :
                    DelegateIterator (),
                    _pArray ( pArray ),
                    _index ( index ),
                    _forward ( forward ) {

            }

            constexpr ArrayDelegateIterator ( ArrayDelegateIterator const & ) noexcept = default;
            constexpr ArrayDelegateIterator ( ArrayDelegateIterator && ) noexcept = default;

            __CDS_cpplang_ConstexprDestructor ~ArrayDelegateIterator() noexcept override = default;

            __CDS_NoDiscard constexpr auto index () const noexcept -> Index {
                return this->_index;
            }

            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto isValid () const noexcept -> bool override {
                return
                    ! this->_pArray.isNull() &&
                    this->_index >= 0 && this->_index < this->_pArray->size();
            }

            __CDS_cpplang_ConstexprOverride auto next () noexcept -> ArrayDelegateIterator & override {
                (void) ( this->_forward ? ( ++ this->_index ) : ( -- this->_index ) );
                return * this;
            }

            __CDS_cpplang_ConstexprOverride auto previous () noexcept -> ArrayDelegateIterator & override {
                (void) ( this->_forward ? ( -- this->_index ) : ( ++ this->_index ) );
                return * this;
            }

            __CDS_cpplang_ConstexprOverride auto value () const noexcept -> ElementRef override {
                return * this->_pArray->_pData[ this->_index ];
            }

            __CDS_OptimalInline auto equals ( DelegateIterator const & it ) const noexcept -> bool override {
                if ( this == & it ) return true;
                auto p = reinterpret_cast < decltype ( this ) > ( & it );

                return this->_pArray == p->_pArray && this->_index == p->_index;
            }

            __CDS_OptimalInline auto copy () const noexcept -> ArrayDelegateIterator * override {
                return Memory :: instance () . create < ArrayDelegateIterator > ( * this );
            }
        };

        class ArrayDelegateConstIterator : public DelegateConstIterator {
        private:
            ForeignPointer < Array const >  _pArray;
            Index                           _index;
            bool                            _forward;

        public:
            constexpr ArrayDelegateConstIterator ( Array const * pArray, Index index, bool forward ) noexcept :
                    DelegateConstIterator (),
                    _pArray ( pArray ),
                    _index ( index ),
                    _forward ( forward ) {

            }

            constexpr ArrayDelegateConstIterator ( ArrayDelegateConstIterator const & ) noexcept = default;
            constexpr ArrayDelegateConstIterator ( ArrayDelegateConstIterator && ) noexcept = default;

            __CDS_cpplang_ConstexprDestructor ~ArrayDelegateConstIterator() noexcept override = default;

            __CDS_NoDiscard constexpr auto index () const noexcept -> Index {
                return this->_index;
            }

            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto isValid () const noexcept -> bool override {
                return
                        ! this->_pArray.isNull() &&
                        this->_index >= 0 && this->_index < this->_pArray->size();
            }

            __CDS_cpplang_ConstexprOverride auto next () noexcept -> ArrayDelegateConstIterator & override {
                (void) ( this->_forward ? ( ++ this->_index ) : ( -- this->_index ) );
                return * this;
            }

            __CDS_cpplang_ConstexprOverride auto previous () noexcept -> ArrayDelegateConstIterator & override {
                (void) ( this->_forward ? ( -- this->_index ) : ( ++ this->_index ) );
                return * this;
            }

            __CDS_cpplang_ConstexprOverride auto value () const noexcept -> ElementCRef override {
                return * this->_pArray->_pData[ this->_index ];
            }

            __CDS_OptimalInline auto equals ( DelegateConstIterator const & it ) const noexcept -> bool override {
                if ( this == & it ) return true;
                auto p = reinterpret_cast < decltype ( this ) > ( & it );

                return this->_pArray == p->_pArray && this->_index == p->_index;
            }

            __CDS_OptimalInline auto copy () const noexcept -> ArrayDelegateConstIterator * override {
                return Memory :: instance () . create < ArrayDelegateConstIterator > ( * this );
            }
        };

        using DelegateIteratorRequestType = typename Collection < T > :: DelegateIteratorRequestType;

        __CDS_OptimalInline auto delegateIterator ( DelegateIteratorRequestType requestType ) noexcept -> UniquePointer < DelegateIterator > override {
            switch ( requestType ) {
                case DelegateIteratorRequestType :: FORWARD_BEGIN:
                    return Memory :: instance () . create < ArrayDelegateIterator > ( this, 0, true );
                case DelegateIteratorRequestType :: FORWARD_END:
                    return Memory :: instance () . create < ArrayDelegateIterator > ( this, this->size(), true );
                case DelegateIteratorRequestType :: BACKWARD_BEGIN:
                    return Memory :: instance () . create < ArrayDelegateIterator > ( this, this->size() - 1, false );
                case DelegateIteratorRequestType :: BACKWARD_END:
                    return Memory :: instance () . create < ArrayDelegateIterator > ( this, -1, false );
                default:
                    return nullptr;
            }
        }

        __CDS_OptimalInline auto delegateConstIterator ( DelegateIteratorRequestType requestType ) const noexcept -> UniquePointer < DelegateConstIterator > override {
            switch ( requestType ) {
                case DelegateIteratorRequestType :: FORWARD_BEGIN:
                    return Memory :: instance () . create < ArrayDelegateConstIterator > ( this, 0, true );
                case DelegateIteratorRequestType :: FORWARD_END:
                    return Memory :: instance () . create < ArrayDelegateConstIterator > ( this, this->size(), true );
                case DelegateIteratorRequestType :: BACKWARD_BEGIN:
                    return Memory :: instance () . create < ArrayDelegateConstIterator > ( this, this->size() - 1, false );
                case DelegateIteratorRequestType :: BACKWARD_END:
                    return Memory :: instance () . create < ArrayDelegateConstIterator > ( this, -1, false );
                default:
                    return nullptr;
            }
        }

        auto allocFrontGetPtr () noexcept -> ElementPtrRef override;
        auto allocBackGetPtr () noexcept -> ElementPtrRef override;
        __CDS_OptimalInline auto allocInsertGetPtr (ElementCRef e __CDS_MaybeUnused) noexcept -> ElementPtrRef override {
            return this->allocBackGetPtr();
        }

    public:
        auto operator = ( Collection < ElementType > const & ) noexcept -> Array &;

        __CDS_OptimalInline auto operator = ( Array const & o ) noexcept -> Array & { // NOLINT(bugprone-unhandled-self-assignment)
            return this->operator=( ( Collection<ElementType> const & )(o) );  // NOLINT(misc-unconventional-assign-operator)
        }

        __CDS_OptionalInline auto operator = ( Array && array ) noexcept -> Array & {
            if ( this == & array ) return * this;

            for ( Index i = 0; i < this->_size; ++ i )
                Memory :: instance().destroy ( this->_pData[i] );
            Memory :: instance().destroyArray ( this->_pData );

            this->_pData = exchange ( array._pData, nullptr );
            this->_capacity = exchange ( array._capacity, 0 );
            this->_size = exchange ( array._size, 0 );

            return * this;
        }

        auto sequence () const & noexcept -> Sequence < Array < T > const >;
        auto sequence () & noexcept -> Sequence < Array < T > >;
        auto sequence () const && noexcept -> Sequence < Array < T > const >;
        auto sequence () && noexcept -> Sequence < Array < T > >;
    };

}

namespace cds {

    template < typename T >
    template < typename V, EnableIf < Type < V > :: copyConstructible > >
    Array<T>::Array( InitializerList initializerList ) noexcept {
        for ( auto & e : initializerList )
            this->pushBack( e );
    }

    template <class T>
    Array<T>::~Array() noexcept {
        for ( Index i = 0; i < this->_capacity; i++ )
            Memory :: instance ().destroy ( exchange(this->_pData[i], nullptr) );
        Memory :: instance().destroyArray ( exchange(this->_pData, nullptr) );
    }

    template < typename T >
    auto Array < T > :: allocFrontGetPtr () noexcept -> ElementPtrRef {

        if ( this->_size < this->_capacity ) {
            Memory :: instance().destroy ( exchange(this->_pData[ this->_size ++ ], nullptr) );
            for ( Index i = this->_size - 1; i > 0; -- i )
                this->_pData[i] = this->_pData[i - 1];

            return (this->_pData[0] = nullptr);
        }

        auto newSize = this->_capacity * 2;
        auto newBuf = Memory :: instance().createArray < T * > ( newSize );
        std::memcpy ( newBuf + 1, this->_pData, this->_size * sizeof ( T * ) );
        std::memset ( newBuf + 1 + this->_size, 0, (newSize - this->_size - 1) * sizeof(T *) );

        this->_capacity = newSize;
        this->_size ++;

        Memory :: instance().destroyArray ( exchange ( this->_pData, newBuf ) );

        return (this->_pData[0] = nullptr);
    }

}

#if defined(_MSC_VER)

#pragma push_macro("min")
#pragma push_macro("max")
#undef min
#undef max

#endif


namespace cds {

    template < typename T >
    auto Array < T > :: allocBackGetPtr () noexcept -> ElementPtrRef {

        if ( this->_size < this->_capacity )
            return (this->_pData[ this->_size ++ ] = nullptr);

        auto newSize = std :: max ( this->_capacity * 2, this->_size + 1 );
        T ** newBuf = Memory :: instance ().createArray < T * > (newSize);

        std::memcpy ( newBuf, this->_pData, this->_size * sizeof(T *) );
        std::memset ( newBuf + this->_size, 0, ( newSize - this->_size ) * sizeof (T*) );

        this->_capacity = newSize;
        Memory :: instance ().destroyArray ( exchange ( this->_pData, newBuf ) );

        return (this->_pData[this->_size ++] = nullptr);
    }

}

#if defined(_MSC_VER)

#pragma pop_macro("max")
#pragma pop_macro("min")

#endif

namespace cds {

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

}

#if defined(_MSC_VER)
#pragma push_macro("max")
#undef max
#endif

namespace cds {

    template < typename T >
    __CDS_MaybeUnused auto Array<T>::expandWith(Size requiredSize) noexcept -> void {
        if ( this->_size + requiredSize < this->_capacity ) return;

        return this->_resize(std::max(this->_size + requiredSize, this->_capacity * 2));
    }

}

#if defined(_MSC_VER)
#pragma pop_macro("max")
#endif

namespace cds {

    template < typename T >
    auto Array<T>::shrinkToSize(Size size) noexcept -> void {
        if ( this->_capacity <= size ) return;

        return this->_resize(size);
    }

}

#if defined(_MSC_VER)

#pragma push_macro("min")
#pragma push_macro("max")
#undef min
#undef max

#endif

namespace cds {

    template < typename T >
    auto Array<T>::_resize(Size size) noexcept -> void {
        auto newMemory = Memory :: instance().createArray < ElementType * > ( size );

        for ( auto i = static_cast < SignedSize > ( this->_size ) - 1; i >= static_cast < SignedSize > ( size ); -- i )
            Memory :: instance ().destroy ( exchange(this->_pData[i], nullptr));

        std :: memcpy ( newMemory, this->_pData, sizeof ( T * ) * ( std :: min ( this->_size, size ) ) );

        if ( size > this->_size )
            std :: memset ( newMemory + this->_size, 0, sizeof ( T * ) * ( size - this->_size ) );

        Memory :: instance().destroyArray ( exchange ( this->_pData, newMemory ) );
        this->_capacity = size;
    }

}

#if defined(_MSC_VER)

#pragma pop_macro("max")
#pragma pop_macro("min")

#endif

namespace cds {

    template < typename T >
    Array<T>::Array( Array const & o ) noexcept :
            _pData( Memory :: instance ().createArray < T * > (o.size()) ),
            _capacity( o.size() ){

        this->_size = o.size();
        for ( auto i = 0; i < o.size(); ++ i )
            this->_pData[i] = Memory :: instance ().create < T > (*o._pData[i]);
    }

    template < typename T >
    Array<T>::Array( Array && moveObj ) noexcept {
        this->_pData = exchange(moveObj._pData, nullptr);
        this->_size = exchange(moveObj._size, 0);
        this->_capacity = exchange(moveObj._capacity, 0);
    }

}

#include <CDS/Pointer>

namespace cds {

    template < typename T >
    Array<T>::Array(
            Iterator const & from,
            Iterator const & to
    ) noexcept {
        for ( auto it = from; it != to; ++ it )
            this->pushBack( * it );
    }

    template < typename T >
    Array<T>::Array(
            ConstIterator const & from,
            ConstIterator const & to
    ) noexcept {
        for ( auto it = from; it != to; ++ it )
            this->pushBack( * it );
    }

    template < typename T >
    Array < T > :: Array ( Collection < T > const & collection ) noexcept {
        collection.forEach([this](T const & e){this->pushBack(e);});
    }

    template < typename T >
    template < typename V, EnableIf < Type < V > :: defaultConstructible > >
    Array < T > :: Array ( Size size ) noexcept :
            _pData ( Memory :: instance ().createArray <  T * > (size) ),
            _capacity ( size ) {

        this->_size = size;
        for ( Index i = 0; i < this->_size; ++ i )
            this->_pData [i] = Memory :: instance ().create < T > ();
    }

    template < typename T >
    template < typename V, EnableIf < Type < V > :: copyConstructible > >
    Array<T>::Array ( Size size, ElementCRef defaultValue ) noexcept :
            _pData(Memory :: instance ().createArray < T * > (size)),
            _capacity(size){

        this->_size = size;
        for ( Index i = 0; i < this->_size; ++ i )
            this->_pData[i] = Memory :: instance().create < T > ( defaultValue );
    }

    template < typename T >
    auto Array<T>::remove(ElementCRef e, Size count) noexcept -> bool {
        bool removed = false;

        T ** newBuf = Memory :: instance().createArray < T * > (this->size());

        Index i = 0, l = 0, c = 0;
        for (; i < this->size() && c < count; i++)
            if ( ! Type < T > :: compare ( * this->_pData[i], e ) ) {
                newBuf[l++] = this->_pData[i];
            } else {
                removed = true;
                ++ c;
                Memory :: instance().destroy ( exchange(this->_pData[i], nullptr) );
            }

        this->_capacity = this->size();
        this->_size = l;

        memset ( newBuf + l, 0, (this->_capacity - l) * sizeof(T *) );
        Memory :: instance().destroyArray ( exchange ( this->_pData, newBuf ) );

        return removed;
    }

}

#include <CDS/Range>

namespace cds {

    template < typename T >
    auto Array<T>::removeLast(ElementCRef e) noexcept -> bool {
        Index at = -1;
        for ( Index i = this->size() - 1; i >= 0; -- i )
            if ( Type < T > :: compare ( * this->_pData[i], e ) ) {
                at = i;
                break;
            }

        if ( at == -1 ) return false;

        Memory :: instance().destroy ( exchange(this->_pData[at], nullptr) );

        T ** pNewBuf = Memory::instance().createArray < T * > ( this->size() - 1 );
        std::memcpy ( pNewBuf, this->_pData, at * sizeof ( T * ) );
        std::memcpy ( pNewBuf + at, this->_pData + at + 1, (this->size() - at - 1) * sizeof(T *) );

        this->_capacity = -- this->_size;
        Memory :: instance().destroyArray ( exchange ( this->_pData, pNewBuf ) );
        return true;
    }

    template < typename T >
    auto Array<T>::removeOf(Collection<ElementType> const & elements, Size count) noexcept -> bool {
        bool removed = false;

        T ** newBuf = Memory :: instance ().createArray < T * > (this->size());

        Index i = 0, l = 0, c = 0;
        for (; i < this->size() && c < count; i++)
            if ( ! elements.contains ( * this->_pData[i] ) ) {
                newBuf[l++] = this->_pData[i];
            } else {
                removed = true;
                ++ c;
                Memory :: instance().destroy ( exchange(this->_pData[i], nullptr) );
            }

        this->_capacity = this->size();
        this->_size = l;

        std::memset ( newBuf + l, 0, (this->_capacity - this->_size) * sizeof ( T * ) );
        Memory :: instance().destroyArray ( exchange ( this->_pData, newBuf ) );

        return removed;
    }

    template < typename T >
    auto Array<T>::removeOf ( InitializerList elements, Size count ) noexcept -> bool {
        bool removed = false;

        T ** newBuf = Memory :: instance().createArray < T * > ( this->size() );
        Index i = 0, l = 0, c = 0;
        for (; i < this->size() && c < count; i++)
            if ( ! Collection < T > :: iListContains ( elements, * this->_pData[i] ) ) {
                newBuf[l++] = this->_pData[i];
            } else {
                removed = true;
                ++ c;
                Memory :: instance ().destroy ( exchange(this->_pData[i], nullptr) );
            }

        this->_capacity = this->size();
        this->_size = l;

        std::memset ( newBuf + l, 0, (this->_capacity - this->_size) * sizeof ( T * ) );
        Memory :: instance().destroyArray ( exchange ( this->_pData, newBuf ) );

        return removed;
    }

    template < typename T >
    auto Array<T>::removeNotOf( Collection<ElementType> const & elements, Size count) noexcept -> bool {
        bool removed = false;

        T ** newBuf = Memory :: instance().createArray < T * > (this->size());
        Index i = 0, l = 0, c = 0;
        for (; i < this->size() && c < count; i++)
            if ( elements.contains ( * this->_pData[i] ) ) {
                newBuf[l++] = this->_pData[i];
            } else {
                removed = true;
                ++ c;
                Memory :: instance ().destroy ( exchange(this->_pData[i], nullptr) );
            }

        this->_capacity = this->size();
        this->_size = l;
        std::memset ( newBuf + l, 0, (this->_capacity - this->_size) * sizeof ( T * ) );
        Memory :: instance ().destroyArray ( exchange ( this->_pData, newBuf ) );
        return removed;
    }

    template < typename T >
    auto Array<T>::removeNotOf( InitializerList elements, Size count ) noexcept -> bool {
        bool removed = false;

        T ** newBuf = Memory :: instance().createArray < T * > ( this->size() );
        Index i = 0, l = 0, c = 0;
        for (; i < this->size() && c < count; i++)
            if ( Collection < T > :: iListContains( elements, * this->_pData[i] ) ) {
                newBuf[l++] = this->_pData[i];
            } else {
                removed = true;
                ++ c;
                Memory :: instance ().destroy ( exchange(this->_pData[i], nullptr) );
            }

        this->_capacity = this->size();
        this->_size = l;
        std::memset ( newBuf + l, 0, (this->_capacity - this->_size) * sizeof ( T * ) );
        Memory :: instance ().destroyArray ( exchange ( this->_pData, newBuf ) );
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

        Memory :: instance().destroy ( exchange(this->_pData[at], nullptr) );

        T ** pNewBuf = Memory :: instance ().createArray < T * > ( this->size() - 1 );
        std::memcpy ( pNewBuf, this->_pData, at * sizeof ( T * ) );
        std::memcpy ( pNewBuf + at, this->_pData + at + 1, (this->size() - at - 1) * sizeof(T *) );
        Memory :: instance().destroyArray ( exchange ( this->_pData, pNewBuf ) );
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

        Memory :: instance().destroy ( exchange(this->_pData[at], nullptr) );

        T ** pNewBuf = Memory :: instance().createArray < T * > ( this->size() - 1 );
        std::memcpy ( pNewBuf, this->_pData, at * sizeof ( T * ) );
        std::memcpy ( pNewBuf + at, this->_pData + at + 1, (this->size() - at - 1) * sizeof(T *) );
        Memory :: instance().destroyArray ( exchange ( this->_pData, pNewBuf ) );
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

        Memory :: instance().destroy ( exchange(this->_pData[at], nullptr) );

        T ** pNewBuf = Memory :: instance(). createArray < T * > ( this->size() - 1 );
        std::memcpy ( pNewBuf, this->_pData, at * sizeof ( T * ) );
        std::memcpy ( pNewBuf + at, this->_pData + at + 1, (this->size() - at - 1) * sizeof(T *) );
        Memory :: instance().destroyArray ( exchange ( this->_pData, pNewBuf ) );
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

        Memory :: instance ().destroy ( exchange(this->_pData[at], nullptr) );

        T ** pNewBuf = Memory :: instance().createArray < T * > ( this->size() - 1 );
        std::memcpy ( pNewBuf, this->_pData, at * sizeof ( T * ) );
        std::memcpy ( pNewBuf + at, this->_pData + at + 1, (this->size() - at - 1) * sizeof(T *) );
        Memory :: instance().destroyArray ( exchange ( this->_pData, pNewBuf ) );
        this->_capacity = -- this->_size;
        return true;
    }

}


#include <CDS/Utility>

namespace cds {

    template < typename T >
    auto Array<T>::remove( Iterator const & it ) noexcept (false) -> ElementType {
        if ( ! it.of ( this ) )
            throw IllegalArgumentException ( "Iterator given is not of this collection" );

        auto pDelegate = reinterpret_cast < ArrayDelegateIterator * > ( Collection<T>::acquireDelegate( it ) );

        if ( pDelegate->index() < 0 || pDelegate->index() >= this->size() )
            throw OutOfBoundsException( pDelegate->index(), this->size() );

        T retVal = * this->_pData[ pDelegate->index() ];
        Memory :: instance().destroy ( exchange(this->_pData[ pDelegate->index() ], nullptr) );

        T ** pNewBuf = Memory :: instance().createArray < T * > ( this->size() - 1 );
        std::memcpy ( pNewBuf, this->_pData, pDelegate->index() * sizeof ( T * ) );
        std::memcpy ( pNewBuf + pDelegate->index(), this->_pData + pDelegate->index() + 1, (this->size() - pDelegate->index() - 1) * sizeof(T *) );
        Memory :: instance().destroyArray( exchange ( this->_pData, pNewBuf ) );

        this->_capacity = -- this->_size;
        return retVal;
    }

    template < typename T >
    auto Array<T>::clear() noexcept -> void {
        for ( Index i = 0; i < this->_size; ++ i )
            Memory :: instance().destroy ( exchange ( this->_pData[i], nullptr ) );
        this->_size = 0;
    }

    template < typename T >
    auto Array<T> :: makeUnique() noexcept -> void {
        T ** pNewData = Memory :: instance().createArray < T * > (this->size());
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
                Memory :: instance().destroy ( exchange(this->_pData[i], nullptr) );

        std :: memset ( pNewData + l, 0, (this->size() - l) * sizeof(T *) );

        this->_capacity = this->size();
        this->_size = l;

        Memory :: instance().destroyArray( exchange ( this->_pData, pNewData ) );
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

}

#include <CDS/LinkedList>

namespace cds {

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

}

#include <CDS/Utility>

namespace cds {
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

        for ( auto const & e : c )
            this->pushBack( e );

        return * this;
    }

}

#include <CDS/Sequence>

namespace cds {

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

}

#if __CDS_cpplang_CTAD_available == true

namespace cds {

template < typename T >
Array ( std::initializer_list < T > ) -> Array < T >;

}

#endif

__CDS_RegisterParseTypeTemplateT(Array)

#endif //CDS_ARRAY_HPP
