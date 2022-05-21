//
// Created by loghin on 01.03.2021.
//

#ifndef CDS_ARRAY_HPP
#define CDS_ARRAY_HPP

#if !defined(__CDS_LateInclude_Sequence)
#define __CDS_LateInclude_Sequence
#endif

#include <CDS/List>
#include <CDS/Memory>

namespace cds {

    template < typename C >
    class Sequence;

    template < typename T >
    class Array : public List <T> { // NOLINT(cppcoreguidelines-virtual-class-destructor)
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
            for ( Size i = this->_size; i < newSize; ++ i ) {
                this->_pData[i] = Memory :: instance ().create < T > ();
            }

            this->_size = newSize;
        }

        template < typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
        __CDS_OptionalInline auto resize ( Size newSize, ElementCRef value ) noexcept -> void {
            this->_resize(newSize);
            for ( Size i = this->_size; i < newSize; ++ i ) {
                this->_pData[i] = Memory :: instance ().create < T > (value);
            }

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
            if ( this->empty() ) {
                throw OutOfBoundsException("Array is Empty");
            }

            return * this->_pData[this->_size - 1];
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto front () noexcept (false) -> ElementRef final {
            if ( this->empty() ) {
                throw OutOfBoundsException("Array is Empty");
            }

            return * this->_pData[0];
        }

        __CDS_cpplang_ConstexprConditioned auto back () const noexcept (false) -> ElementCRef final {
            if ( this->empty() ) {
                throw OutOfBoundsException("Array is Empty");
            }

            return * this->_pData[this->_size - 1];
        }

        __CDS_cpplang_ConstexprConditioned auto front () const noexcept (false) -> ElementCRef final {
            if (this->empty()) {
                throw OutOfBoundsException("Array is Empty");
            }

            return *this->_pData[0];
        }

        __CDS_OptionalInline auto operator == (Array const & array) const noexcept -> bool {
            if ( this == & array ) {
                return true;
            }

            if (array.size() != this->size() ) {
                return false;
            }

            for ( // NOLINT(clion-misra-cpp2008-6-5-1)
                    auto // NOLINT(clion-misra-cpp2008-8-0-1)
                    aIt = this->begin(), aEnd = this->end(),
                            bIt = array.begin(), bEnd = array.end();
                    aIt != aEnd && bIt != bEnd;
                    ++ aIt, ++ bIt // NOLINT(clion-misra-cpp2008-5-18-1)
                    ) {
                if ( ! ( Type < T > :: compare (* aIt, * bIt ) ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                    return false;
                }
            }

            return true;
        }

        __CDS_OptimalInline auto operator != (Array const & array) const noexcept -> bool {
            return ! this->operator==(array); // NOLINT(clion-misra-cpp2008-5-3-1)
        }

        __CDS_NoDiscard auto equals (Object const & object) const noexcept -> bool final {
            if (this == &object) {
                return true;
            }

            auto pObject = dynamic_cast < Array < T > const * > ( &object );
            if (pObject == nullptr) {
                return false;
            }

            return this->operator==(*pObject);
        }

        auto clear () noexcept -> void override;
        auto makeUnique () noexcept -> void final;

        __CDS_MaybeUnused auto indices ( ElementCRef ) const noexcept -> DoubleLinkedList < Index >;

    private:
        auto pAt (Index) noexcept (false) -> ElementPtr override;
        auto pAt (Index) const noexcept (false) -> ElementCPtr override;

    public:

        __CDS_OptionalInline auto popFront () noexcept (false) -> ElementType final {
            if ( this->empty() ) {
                throw OutOfBoundsException("Array is Empty");
            }

            auto retVal = * this->_pData[0];
            Memory :: instance().destroy ( exchange(this->_pData[0], nullptr) );

            for ( Index i = 0; i < this->size() - 1; i ++ ) {
                this->_pData[i] = this->_pData[i + 1];
            }

            this->_pData[-- this->_size] = nullptr;

            return retVal;
        }

        __CDS_OptionalInline auto popBack () noexcept (false) -> ElementType final {
            if ( this->empty() ) {
                throw OutOfBoundsException("Array is Empty");
            }

            auto value = * this->_pData[--this->_size];
            Memory :: instance().destroy ( exchange(this->_pData[this->_size], nullptr) );

            return value;
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
                        this->_pArray != nullptr &&
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

            __CDS_OptimalInline auto equals ( DelegateIterator const & iterator ) const noexcept -> bool override {
                if ( this == & iterator ) {
                    return true;
                }

                auto pObject = reinterpret_cast < decltype ( this ) > ( & iterator );

                return this->_pArray == pObject->_pArray && this->_index == pObject->_index;
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
                        this->_pArray != nullptr &&
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

            __CDS_OptimalInline auto equals ( DelegateConstIterator const & iterator ) const noexcept -> bool override {
                if ( this == & iterator ) {
                    return true;
                }

                auto pObject = reinterpret_cast < decltype ( this ) > ( & iterator );

                return this->_pArray == pObject->_pArray && this->_index == pObject->_index;
            }

            __CDS_OptimalInline auto copy () const noexcept -> ArrayDelegateConstIterator * override {
                return Memory :: instance () . create < ArrayDelegateConstIterator > ( * this );
            }
        };

        using DelegateIteratorRequestType = typename Collection < T > :: DelegateIteratorRequestType;

        __CDS_OptimalInline auto delegateIterator ( DelegateIteratorRequestType requestType ) noexcept -> UniquePointer < DelegateIterator > override {
            switch ( requestType ) {
                case DelegateIteratorRequestType :: FORWARD_BEGIN: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < ArrayDelegateIterator > ( this, 0, true );
                case DelegateIteratorRequestType :: FORWARD_END: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < ArrayDelegateIterator > ( this, this->size(), true );
                case DelegateIteratorRequestType :: BACKWARD_BEGIN: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < ArrayDelegateIterator > ( this, this->size() - 1, false );
                case DelegateIteratorRequestType :: BACKWARD_END: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < ArrayDelegateIterator > ( this, -1, false );
                default: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return nullptr;
            }
        }

        __CDS_OptimalInline auto delegateConstIterator ( DelegateIteratorRequestType requestType ) const noexcept -> UniquePointer < DelegateConstIterator > override {
            switch ( requestType ) {
                case DelegateIteratorRequestType :: FORWARD_BEGIN: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < ArrayDelegateConstIterator > ( this, 0, true );
                case DelegateIteratorRequestType :: FORWARD_END: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < ArrayDelegateConstIterator > ( this, this->size(), true );
                case DelegateIteratorRequestType :: BACKWARD_BEGIN: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < ArrayDelegateConstIterator > ( this, this->size() - 1, false );
                case DelegateIteratorRequestType :: BACKWARD_END: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return Memory :: instance () . create < ArrayDelegateConstIterator > ( this, -1, false );
                default: // NOLINT(clion-misra-cpp2008-6-4-5)
                    return nullptr;
            }
        }

        auto allocFrontGetPtr () noexcept -> ElementPtrRef override;
        auto allocBackGetPtr () noexcept -> ElementPtrRef override;
        __CDS_OptimalInline auto allocInsertGetPtr (ElementCRef element __CDS_MaybeUnused) noexcept -> ElementPtrRef override {
            return this->allocBackGetPtr();
        }

    public:
        auto operator = ( Collection < ElementType > const & ) noexcept -> Array &;

        __CDS_OptimalInline auto operator = ( Array const & array ) noexcept -> Array & { // NOLINT(bugprone-unhandled-self-assignment)
            if ( this == & array ) {
                return * this;
            }

            (void) this->clear ();

            this->_size = array.size();
            this->_capacity = array.size();
            this->_pData = Memory :: instance().createArray < T * > ( array.size() );

            for ( Index i = 0; i < this->_size; ++ i ) {
                this->_pData[i] = Memory :: instance().create < T > ( array[i] );
            }

            return * this;
        }

        __CDS_OptionalInline auto operator = ( Array && array ) noexcept -> Array & {
            if ( this == & array ) {
                return * this;
            }

            for ( Index i = 0; i < this->_size; ++ i ){
                Memory :: instance().destroy ( this->_pData[i] );
            }

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

        __CDS_NoDiscard auto copy () const noexcept -> Array < T > * override {
            return Memory :: instance () .create < Array < T > > ( * this );
        }
    };

}

namespace cds {

    template < typename T >
    template < typename V, EnableIf < Type < V > :: copyConstructible > >
    Array<T>::Array( InitializerList initializerList __CDS_MaybeUnused ) noexcept {
        for ( auto & element __CDS_MaybeUnused : initializerList ) {
            this->pushBack(element);
        }
    }

    template <class T>
    Array<T>::~Array() noexcept {
        for ( Index i = 0; i < this->_capacity; i++ ) {
            Memory :: instance ().destroy ( exchange(this->_pData[i], nullptr) );
        }

        Memory :: instance().destroyArray ( exchange(this->_pData, nullptr) );
    }

    template < typename T >
    auto Array < T > :: allocFrontGetPtr () noexcept -> ElementPtrRef {
        if ( this->_size < this->_capacity ) {
            for ( Index i = this->_size; i > 0; -- i ) {
                this->_pData[i] = this->_pData[i - 1];
            }

            ++ this->_size;

            this->_pData[0] = nullptr;
            return this->_pData[0];
        }

        auto newSize = this->_capacity * 2;
        auto newBuf = Memory :: instance().createArray < T * > ( newSize );
        (void) std::memcpy ( newBuf + 1, this->_pData, this->_size * sizeof ( T * ) );
        (void) std::memset ( newBuf + 1 + this->_size, 0, (newSize - this->_size - 1) * sizeof(T *) );

        this->_capacity = newSize;
        this->_size ++;

        Memory :: instance().destroyArray ( exchange ( this->_pData, newBuf ) );

        this->_pData[0] = nullptr;
        return this->_pData[0];
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

        if ( this->_size < this->_capacity ) {
            this->_pData [ this->_size ] = nullptr;
            return this->_pData [ this->_size ++ ];
        }

        auto newSize = std :: max ( this->_capacity * 2, this->_size + 1 );
        T ** newBuf = Memory :: instance ().createArray < T * > (newSize);

        (void) std::memcpy ( newBuf, this->_pData, this->_size * sizeof(T *) );
        (void) std::memset ( newBuf + this->_size, 0, ( newSize - this->_size ) * sizeof (T*) );

        this->_capacity = newSize;
        Memory :: instance ().destroyArray ( exchange ( this->_pData, newBuf ) );

        this->_pData [ this->_size ] = nullptr;
        return this->_pData [ this->_size ++ ];
    }

}

#if defined(_MSC_VER)

#pragma pop_macro("max")
#pragma pop_macro("min")

#endif


#if defined(_MSC_VER)
#pragma push_macro("max")
#undef max
#endif

namespace cds {

    template < typename T >
    __CDS_MaybeUnused auto Array<T>::expandWith(Size requiredSize) noexcept -> void {
        if ( this->_size + requiredSize < this->_capacity ) {
            return;
        }

        return this->_resize(std::max(this->_size + requiredSize, this->_capacity * 2));
    }

}

#if defined(_MSC_VER)
#pragma pop_macro("max")
#endif

namespace cds {

    template < typename T >
    auto Array<T>::shrinkToSize(Size size) noexcept -> void {
        if ( this->_capacity <= size ) {
            return;
        }

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

        for ( auto i = static_cast < SignedSize > ( this->_size ) - 1; i >= static_cast < SignedSize > ( size ); -- i ) {
            Memory :: instance ().destroy ( exchange(this->_pData[i], nullptr));
        }

        (void) std :: memcpy ( newMemory, this->_pData, sizeof ( T * ) * ( std :: min ( this->_size, size ) ) );

        if ( size > this->_size ) {
            (void) std :: memset ( newMemory + this->_size, 0, sizeof ( T * ) * ( size - this->_size ) );
        }

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
    Array<T>::Array( Array const & array ) noexcept :
            _pData( nullptr ),
            _capacity(array.size() ){

        this->_size = array.size();

        if ( this->_size > 0 ) {
            this->_pData = Memory :: instance () .createArray < T * > ( this->_size );
        }

        for (auto i = 0; i < array.size(); ++ i ) {
            this->_pData[i] = Memory :: instance ().create < T > (*array._pData[i]);
        }
    }

    template < typename T >
    Array<T>::Array( Array && moveObj ) noexcept {
        this->_pData = exchange(moveObj._pData, nullptr);
        this->_size = exchange(moveObj._size, 0);
        this->_capacity = exchange(moveObj._capacity, 0);
    }

}

#include <CDS/smartPointers/UniquePointer>
#include <CDS/smartPointers/ForeignPointer>

namespace cds {

    template < typename T >
    Array<T>::Array(
            Iterator const & from, // NOLINT(bugprone-easily-swappable-parameters)
            Iterator const & until
    ) noexcept {
        for (auto it = from; it != until; ++ it ) {
            this->pushBack( * it );
        }
    }

    template < typename T >
    Array<T>::Array(
            ConstIterator const & from, // NOLINT(bugprone-easily-swappable-parameters)
            ConstIterator const & until
    ) noexcept {
        for (auto it = from; it != until; ++ it ) {
            this->pushBack( * it );
        }
    }

    template < typename T >
    Array < T > :: Array ( Collection < T > const & collection ) noexcept {
        collection.forEach([this](T const & element){this->pushBack(element);});
    }

    template < typename T >
    template < typename V, EnableIf < Type < V > :: defaultConstructible > >
    Array < T > :: Array ( Size size ) noexcept :
            _pData ( Memory :: instance ().createArray <  T * > (size) ),
            _capacity ( size ) {

        this->_size = size;
        for ( Index i = 0; i < this->_size; ++ i ) {
            this->_pData [i] = Memory :: instance ().create < T > ();
        }
    }

    template < typename T >
    template < typename V, EnableIf < Type < V > :: copyConstructible > >
    Array<T>::Array ( Size size, ElementCRef defaultValue ) noexcept :
            _pData(Memory :: instance ().createArray < T * > (size)),
            _capacity(size){

        this->_size = size;
        for ( Index i = 0; i < this->_size; ++ i ) {
            this->_pData[i] = Memory :: instance().create < T > ( defaultValue );
        }
    }

    template < typename T >
    auto Array<T>::remove(ElementCRef element, Size count) noexcept -> bool {
        bool removed = false;

        T ** newBuf = Memory :: instance().createArray < T * > (this->size());

        Index index = 0;
        Index newBufLength = 0;
        Size currentCount = 0u;

        for (; index < this->size(); index++) {
            if ( ! Type < T > :: compare (* this->_pData[index], element ) || currentCount >= count ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                newBuf[newBufLength++] = this->_pData[index];
            } else {
                removed = true;
                ++ currentCount;
                Memory :: instance().destroy ( exchange(this->_pData[index], nullptr) );
            }
        }

        this->_capacity = this->size();
        this->_size = newBufLength;

        (void) std :: memset (newBuf + newBufLength, 0, (this->_capacity - newBufLength) * sizeof(T *) );
        Memory :: instance().destroyArray ( exchange ( this->_pData, newBuf ) );

        return removed;
    }

}

#include <CDS/Range>

namespace cds {

    template < typename T >
    auto Array<T>::removeLast(ElementCRef element) noexcept -> bool {
        Index position = -1;
        for ( Index i = this->size() - 1; i >= 0; -- i ) {
            if ( Type < T > :: compare (* this->_pData[i], element ) ) {
                position = i;
                break;
            }
        }

        if (position == -1 ) {
            return false;
        }

        Memory :: instance().destroy ( exchange(this->_pData[position], nullptr) );

        T ** pNewBuf = Memory::instance().createArray < T * > ( this->size() - 1 );
        (void) std::memcpy ( pNewBuf, this->_pData, static_cast < Size > ( position ) * sizeof ( T * ) );
        (void) std::memcpy (pNewBuf + position, this->_pData + position + 1, (this->size() - position - 1) * sizeof(T *) );

        this->_capacity = -- this->_size;
        Memory :: instance().destroyArray ( exchange ( this->_pData, pNewBuf ) );
        return true;
    }

    template < typename T >
    auto Array<T>::removeOf(Collection<ElementType> const & elements, Size count) noexcept -> bool {
        bool removed = false;

        T ** newBuf = Memory :: instance ().createArray < T * > (this->size());

        Index index = 0;
        Index newBufLength = 0;
        Size currentCount = 0u;

        for (; index < this->size() && currentCount < count; index++) {
            if ( ! elements.contains ( * this->_pData[index] ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                newBuf[newBufLength++] = this->_pData[index];
            } else {
                removed = true;
                ++ currentCount;
                Memory :: instance().destroy ( exchange(this->_pData[index], nullptr) );
            }
        }

        this->_capacity = this->size();
        this->_size = newBufLength;

        (void) std::memset (newBuf + newBufLength, 0, (this->_capacity - this->_size) * sizeof ( T * ) );
        Memory :: instance().destroyArray ( exchange ( this->_pData, newBuf ) );

        return removed;
    }

    template < typename T >
    auto Array<T>::removeOf ( InitializerList elements, Size count ) noexcept -> bool {
        bool removed = false;

        T ** newBuf = Memory :: instance().createArray < T * > ( this->size() );
        Index index = 0;
        Index newBufLength = 0;
        Size currentCount = 0u;
        for (; index < this->size() && currentCount < count; index++) {
            if ( ! Collection < T > :: iListContains ( elements, * this->_pData[index] ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                newBuf[newBufLength++] = this->_pData[index];
            } else {
                removed = true;
                ++ currentCount;
                Memory :: instance ().destroy ( exchange(this->_pData[index], nullptr) );
            }
        }

        this->_capacity = this->size();
        this->_size = newBufLength;

        (void) std::memset (newBuf + newBufLength, 0, (this->_capacity - this->_size) * sizeof ( T * ) );
        Memory :: instance().destroyArray ( exchange ( this->_pData, newBuf ) );

        return removed;
    }

    template < typename T >
    auto Array<T>::removeNotOf( Collection<ElementType> const & elements, Size count) noexcept -> bool {
        bool removed = false;

        T ** newBuf = Memory :: instance().createArray < T * > (this->size());
        Index index = 0;
        Index newBufLength = 0;
        Size currentCount = 0u;
        for (; index < this->size() && currentCount < count; index++) {
            if ( elements.contains ( * this->_pData[index] ) ) {
                newBuf[newBufLength++] = this->_pData[index];
            } else {
                removed = true;
                ++ currentCount;
                Memory :: instance ().destroy ( exchange(this->_pData[index], nullptr) );
            }
        }

        this->_capacity = this->size();
        this->_size = newBufLength;
        (void) std::memset (newBuf + newBufLength, 0, (this->_capacity - this->_size) * sizeof ( T * ) );
        Memory :: instance ().destroyArray ( exchange ( this->_pData, newBuf ) );
        return removed;
    }

    template < typename T >
    auto Array<T>::removeNotOf( InitializerList elements, Size count ) noexcept -> bool {
        bool removed = false;

        T ** newBuf = Memory :: instance().createArray < T * > ( this->size() );
        Index index = 0;
        Index newBufLength = 0;
        Size currentCount = 0u;

        for (; index < this->size() && currentCount < count; index++) {
            if ( Collection < T > :: iListContains( elements, * this->_pData[index] ) ) {
                newBuf[newBufLength++] = this->_pData[index];
            } else {
                removed = true;
                ++ currentCount;
                Memory :: instance ().destroy ( exchange(this->_pData[index], nullptr) );
            }
        }

        this->_capacity = this->size();
        this->_size = newBufLength;
        (void) std::memset (newBuf + newBufLength, 0, (this->_capacity - this->_size) * sizeof ( T * ) );
        Memory :: instance ().destroyArray ( exchange ( this->_pData, newBuf ) );
        return removed;
    }

    template < typename T >
    auto Array<T>::removeLastOf(Collection<ElementType> const & elements) noexcept -> bool {
        Index position = -1;
        for ( Index i = this->size() - 1; i >= 0; -- i ) {
            if ( elements.contains( * this->_pData[i] ) ) {
                position = i;
                break;
            }
        }

        if (position == -1 ) {
            return false;
        }

        Memory :: instance().destroy ( exchange(this->_pData[position], nullptr) );

        T ** pNewBuf = Memory :: instance ().createArray < T * > ( this->size() - 1 );
        (void) std::memcpy ( pNewBuf, this->_pData, static_cast < Size > ( position ) * sizeof ( T * ) );
        (void) std::memcpy (pNewBuf + position, this->_pData + position + 1, (this->size() - position - 1) * sizeof(T *) );
        Memory :: instance().destroyArray ( exchange ( this->_pData, pNewBuf ) );
        this->_capacity = -- this->_size;
        return true;
    }

    template < typename T >
    auto Array<T>::removeLastOf( InitializerList elements ) noexcept -> bool {
        Index position = -1;
        for ( Index i = this->size() - 1; i >= 0; -- i ) {
            if ( Collection<T>::iListContains( elements, * this->_pData[i] ) ) {
                position = i;
                break;
            }
        }

        if (position == -1 ) {
            return false;
        }

        Memory :: instance().destroy ( exchange(this->_pData[position], nullptr) );

        T ** pNewBuf = Memory :: instance().createArray < T * > ( this->size() - 1 );
        (void) std::memcpy ( pNewBuf, this->_pData, static_cast < Size > ( position ) * sizeof ( T * ) );
        (void) std::memcpy (pNewBuf + position, this->_pData + position + 1, (this->size() - position - 1) * sizeof(T *) );
        Memory :: instance().destroyArray ( exchange ( this->_pData, pNewBuf ) );
        this->_capacity = -- this->_size;
        return true;
    }

    template < typename T >
    auto Array<T>::removeLastNotOf( Collection < ElementType > const & elements ) noexcept -> bool {
        Index position = -1;
        for ( Index i = this->size() - 1; i >= 0; -- i ) {
            if ( ! elements.contains( * this->_pData[i] ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                position = i;
                break;
            }
        }

        if (position == -1 ) {
            return false;
        }

        Memory :: instance().destroy ( exchange(this->_pData[position], nullptr) );

        T ** pNewBuf = Memory :: instance(). createArray < T * > ( this->size() - 1 );
        (void) std::memcpy ( pNewBuf, this->_pData, static_cast < Size > ( position ) * sizeof ( T * ) );
        (void) std::memcpy (pNewBuf + position, this->_pData + position + 1, (this->size() - position - 1) * sizeof(T *) );
        Memory :: instance().destroyArray ( exchange ( this->_pData, pNewBuf ) );
        this->_capacity = -- this->_size;
        return true;
    }

    template < typename T >
    auto Array<T>::removeLastNotOf( InitializerList elements) noexcept -> bool {
        Index position = -1;
        for ( Index i = this->size() - 1; i >= 0; -- i ) {
            if ( ! Collection < T > ::iListContains( elements, * this->_pData[i] ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                position = i;
                break;
            }
        }

        if (position == -1 ) {
            return false;
        }

        Memory :: instance ().destroy ( exchange(this->_pData[position], nullptr) );

        T ** pNewBuf = Memory :: instance().createArray < T * > ( this->size() - 1 );
        (void) std::memcpy ( pNewBuf, this->_pData, static_cast < Size > ( position ) * sizeof ( T * ) );
        (void) std::memcpy (pNewBuf + position, this->_pData + position + 1, (this->size() - position - 1) * sizeof(T *) );
        Memory :: instance().destroyArray ( exchange ( this->_pData, pNewBuf ) );
        this->_capacity = -- this->_size;
        return true;
    }

}


#include <CDS/Utility>

namespace cds {

    template < typename T >
    auto Array<T>::remove( Iterator const & iterator ) noexcept (false) -> ElementType {
        if ( ! iterator.of (this ) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
            throw IllegalArgumentException("Iterator given is not of this collection");
        }

        auto pDelegate = reinterpret_cast < ArrayDelegateIterator * > ( Collection<T>::acquireDelegate(iterator ) );

        if ( pDelegate->index() < 0 || pDelegate->index() >= this->size() ) {
            throw OutOfBoundsException ( pDelegate->index(), this->size() );
        }

        T retVal = * this->_pData[ pDelegate->index() ];
        Memory :: instance().destroy ( exchange(this->_pData[ pDelegate->index() ], nullptr) );

        T ** pNewBuf = Memory :: instance().createArray < T * > ( this->size() - 1 );
        (void) std::memcpy ( pNewBuf, this->_pData, pDelegate->index() * sizeof ( T * ) );
        (void) std::memcpy ( pNewBuf + pDelegate->index(), this->_pData + pDelegate->index() + 1, (this->size() - pDelegate->index() - 1) * sizeof(T *) );
        Memory :: instance().destroyArray( exchange ( this->_pData, pNewBuf ) );

        this->_capacity = -- this->_size;
        return retVal;
    }

    template < typename T >
    auto Array<T>::clear() noexcept -> void {
        for ( Index i = 0; i < this->_size; ++ i ) {
            Memory :: instance().destroy ( exchange ( this->_pData[i], nullptr ) );
        }

        this->_size = 0;
    }

    template < typename T >
    auto Array<T> :: makeUnique() noexcept -> void {
        T ** pNewData = Memory :: instance().createArray < T * > (this->size());
        Size newLength = 0u;

        static auto newArrContains = [](T ** pArray, Size arrayLength, ElementCRef element) noexcept -> bool {
            for (Size i = 0u; i < arrayLength; ++ i ) {
                if ( Type < T > :: compare (* pArray[i], element ) ) {
                    return true;
                }
            }

            return false;
        };

        for ( Index i = 0; i < this->size(); ++ i ) {
            if ( ! newArrContains(pNewData, newLength, * this->_pData[i]) ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                pNewData[ ++ newLength ] = this->_pData[i];
            } else {
                Memory :: instance().destroy ( exchange(this->_pData[i], nullptr) );
            }
        }

        (void) std :: memset (pNewData + newLength, 0, (this->size() - newLength) * sizeof(T *) );

        this->_capacity = this->size();
        this->_size = newLength;

        Memory :: instance().destroyArray( exchange ( this->_pData, pNewData ) );
    }
}

#include <CDS/DoubleLinkedList>

namespace cds {

    template < typename T >
    __CDS_MaybeUnused auto Array<T>::indices( ElementCRef value ) const noexcept -> DoubleLinkedList < Index > {
        DoubleLinkedList < Index > indices;

        for ( Index i = 0; i < this->_size; ++ i ) {
            if ( Type < T > :: compare ( * this->_pData[i], value ) ) {
                (void) indices.pushBack(i);
            }
        }

        return indices;
    }

}

#include <CDS/Utility>

namespace cds {
    template < typename T >
    auto Array < T > :: pAt ( Index index ) noexcept (false) -> ElementPtr {
        if ( this->empty() ) {
            throw OutOfBoundsException(index, 0);
        }

        if (index < 0 ) {
            index += (this->size() / (-index) ) * this->size();
        }

        if (index >= static_cast<Index>(this->size()) ) {
            index = index % this->size();
        }

        return this->_pData[index];
    }

    template < typename T >
    auto Array < T > :: pAt ( Index index ) const noexcept (false) -> ElementCPtr {
        if ( this->empty() ) {
            throw OutOfBoundsException(index, 0);
        }

        if (index < 0 ) {
            index += (this->size() / (-index)) * this->size();
        }

        if (index >= static_cast<Index>(this->size()) ) {
            index = index % this->size();
        }

        return this->_pData[index];
    }

    template < typename T >
    Array<T> & Array<T>::operator= (Collection<ElementType> const & collection __CDS_MaybeUnused) noexcept {
        if ( this == & collection ) {
            return * this;
        }

        this->clear();

        for ( auto const & element __CDS_MaybeUnused : collection ) {
            (void) this->pushBack(element);
        }

        return * this;
    }

}

#if defined(__CDS_LateInclude_Sequence)
#undef __CDS_LateInclude_Sequence
#include <CDS/Sequence>
#endif

namespace cds {

    template < typename T >
    auto Array < T > :: sequence () const & noexcept -> Sequence < Array < T > const > {
        return Sequence < RemoveReference < decltype (*this) > > (*this);
    }

    template < typename T >
    auto Array < T > :: sequence () & noexcept -> Sequence < Array < T > > {
        return Sequence < RemoveReference < decltype (*this) > > (*this);
    }

    template < typename T >
    auto Array < T > :: sequence () const && noexcept -> Sequence < Array < T > const > {
        return Sequence < RemoveReference < decltype (*this) > > (std::move(*this));
    }

    template < typename T >
    auto Array < T > :: sequence () && noexcept -> Sequence < Array < T > > {
        return Sequence < RemoveReference < decltype (*this) > > (std::move(*this));
    }

    namespace hidden {
        namespace impl {

            template < typename ArrayType, typename LastArgumentType >
            inline auto arrayOfPush ( ArrayType & array, LastArgumentType && lastArgument ) noexcept -> void {
                (void) array.pushBack ( std :: forward < LastArgumentType > ( lastArgument ) );
            }

            template < typename ArrayType, typename FirstArgumentType, typename ... RemainingArgumentTypes >
            inline auto arrayOfPush ( ArrayType & array, FirstArgumentType && first, RemainingArgumentTypes && ... remaining ) noexcept -> void {

                (void) array.pushBack ( std :: forward < FirstArgumentType > ( first ) );
                arrayOfPush ( array, std :: forward < RemainingArgumentTypes > ( remaining ) ... );
            }
        }
    }

    template < typename ... ArgumentTypes >
    auto arrayOf ( ArgumentTypes && ... types ) noexcept -> Array < typename std :: common_type < ArgumentTypes ... > :: type > {
        Array < typename std :: common_type < ArgumentTypes ... > :: type > array;

        hidden :: impl :: arrayOfPush ( array, std :: forward < ArgumentTypes > ( types ) ... );
        return array;
    }

}

#if __CDS_cpplang_CTAD_available == true

namespace cds {

    template < typename T >
    Array ( std::initializer_list < T > ) -> Array < T >;

}

#endif

__CDS_RegisterParseTypeTemplateT(Array) // NOLINT(clion-misra-cpp2008-8-0-1)

#endif //CDS_ARRAY_HPP
