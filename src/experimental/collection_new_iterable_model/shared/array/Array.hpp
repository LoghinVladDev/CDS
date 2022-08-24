/*
 * Created by loghin on 7/5/22.
 */

#ifndef __CDS_SHARED_ARRAY_HPP__
#define __CDS_SHARED_ARRAY_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                /**
                 * @class Base implementation class for array-based objects
                 *
                 * Works with a two-headed buffer, allocated with a front and back capacity, to allow for pushFront and pushBack operations in O(1)
                 *
                 * @tparam __ElementType is the element enclosed in the array
                 * @tparam __equals is the function used to compare two elements
                 *
                 * @test Suite: CTS-00001, Group: All, Test Cases: All
                 *
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename                                        __ElementType,  /* NOLINT(bugprone-reserved-identifier) */
                        utility :: ComparisonFunction < __ElementType > __equals        /* NOLINT(bugprone-reserved-identifier) */
                > class __Array {                                                       /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @typedef Alias for template parameter __ElementType
                     * @protected
                     */
                    using ElementType = __ElementType;

                private:
                    /**
                     * @brief Starting and Minimum capacity for front and back allocation sizes
                     * @static
                     * @private
                     */
                    static Size const __a_minCapacity = 32ULL; /* NOLINT(bugprone-reserved-identifier) */

                public:
                    /**
                     * @typedef Alias for forward mutable iterator
                     * @public
                     */
                    using __a_Iterator                      = ForwardAddressIterator < __ElementType >; /* NOLINT(bugprone-reserved-identifier) */

                public:
                    /**
                     * @typedef Alias for forward immutable iterator
                     * @public
                     */
                    using __a_ConstIterator                 = ForwardAddressIterator < __ElementType const >; /* NOLINT(bugprone-reserved-identifier) */

                public:
                    /**
                     * @typedef Alias for backward mutable iterator
                     * @public
                     */
                    using __a_ReverseIterator               = BackwardAddressIterator < __ElementType >; /* NOLINT(bugprone-reserved-identifier) */

                public:
                    /**
                     * @typedef Alias for backward immutable iterator
                     * @public
                     */
                    using __a_ConstReverseIterator          = BackwardAddressIterator < __ElementType const >; /* NOLINT(bugprone-reserved-identifier) */

                public:
                    /**
                     * @class Dispatcher to this class' implementation
                     * @implements __ListServerDispatcher
                     * @public
                     */
                    template < typename __ServerType >  /* NOLINT(bugprone-reserved-identifier) */
                    class __Dispatcher;                 /* NOLINT(bugprone-reserved-identifier) */

                private:
                    /**
                     * @struct Container for the elements required by the array
                     * @private
                     */
                    struct __ArrayImplDataContainer { /* NOLINT(bugprone-reserved-identifier) */

                        /** @brief Pointer to the data buffer */
                        __ElementType * _pBuffer;

                        /** @brief Pointer to the first element in the buffer */
                        __ElementType * _pFront;

                        /** @brief Pointer to the element after the last in the buffer */
                        __ElementType * _pBack;

                        /** @brief Capacity allocated for front elements */
                        Size            _frontCapacity;

                        /** @brief Capacity allocated for back elements */
                        Size            _backCapacity;

                        /** @brief Next capacity allocated for front elements */
                        Size            _frontNextCapacity;

                        /** @brief Next capacity allocated for back elements */
                        Size            _backNextCapacity;
                    };

                private:
                    /**
                     * @brief Pointer to the data required for the array
                     * @private
                     */
                    __ArrayImplDataContainer * _pData { nullptr };

                protected:
                    /**
                     * @brief Default Constructor, constexpr
                     * @exceptsafe
                     *
                     * @test Suite: CTS-00001, Group: All, Test Cases: All
                     * @protected
                     */
                    constexpr __Array () noexcept;

                protected:
                    /**
                     * @brief Copy Constructor
                     * @param [in] array : __Array cref = Constant Reference to an Array to copy the data from
                     * @exceptsafe
                     *
                     * @test Suite: CTS-00001, Group: All, Test Cases: All
                     * @protected
                     */
                    __Array ( /* NOLINT(bugprone-reserved-identifier,google-explicit-constructor) */
                            __Array const & array
                    ) noexcept;

                protected:
                    /**
                     * @brief Move Constructor, constexpr
                     * @param [in, out] array : __Array mref = Move Reference to an array to release and acquire the data from
                     * @exceptsafe
                     *
                     * @test Suite: CTS-00001, Group: All, Test Cases: All
                     * @protected
                     */
                    constexpr __Array (
                            __Array && array
                    ) noexcept;

                protected:
                    /**
                     * @brief Function used to clear either the contents of the buffer, or purge the whole array data
                     * @param [in] destroyBuffer : bool = if true, will purge the whole memory array data, otherwise, will only clear the buffer
                     * @exceptsafe
                     *
                     * @test Suite: CTS-00001, Group: All, Test Cases: All
                     * @protected
                     */
                    auto __a_clear ( /* NOLINT(bugprone-reserved-identifier) */
                            bool destroyBuffer
                    ) noexcept -> void;

                protected:
                    /**
                     * @brief Function used to acquire the number of elements in the array
                     * @exceptsafe
                     * @return Size = number of elements in the array
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    __CDS_NoDiscard constexpr auto __a_size () const noexcept -> Size; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function used to remove an element at a given index
                     * @param [in] index : Index = index of the element to be removed
                     * @exceptsafe
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __a_remove ( /* NOLINT(bugprone-reserved-identifier) */
                            Index index
                    ) noexcept -> void;

                protected:
                    /**
                     * @brief Function used to remove an element at a given iterator
                     * @param [in] iterator : AbstractAddressIterator cref = Constant Reference to an iterator indicating to the element to be removed
                     * @exceptsafe
                     * @return bool = true if removal was successful, false otherwise
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __a_removeIterator ( /* NOLINT(bugprone-reserved-identifier) */
                            AbstractAddressIterator < __ElementType > const & iterator
                    ) noexcept -> bool;

                protected:
                    /**
                     * @brief Function used to remove an element at a given const iterator
                     * @param [in] iterator : AbstractAddressIterator cref = Constant Reference to an iterator indicating to the element to be removed
                     * @exceptsafe
                     * @return bool = true if removal was successful, false otherwise
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __a_removeConstIterator ( /* NOLINT(bugprone-reserved-identifier) */
                            AbstractAddressIterator < __ElementType const > const & iterator
                    ) noexcept -> bool;

                protected:
                    /**
                     * @brief Function used to acquire an address to the element located at given index
                     * @param [in] index : Index = index of the element to acquire the address of
                     * @exceptsafe
                     * @return ElementType ptr = Address of the requested element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    __CDS_NoDiscard constexpr auto __a_get ( /* NOLINT(bugprone-reserved-identifier) */
                            Index index
                    ) noexcept -> ElementType *;

                protected:
                    /**
                     * @brief Function used to acquire an address to the element located at given index
                     * @param [in] index : Index = index of the element to acquire the address of
                     * @exceptsafe
                     * @return ElementType cptr = Address of the requested immutable element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    __CDS_NoDiscard constexpr auto __a_get ( /* NOLINT(bugprone-reserved-identifier) */
                            Index index
                    ) const noexcept -> ElementType const *;

                protected:
                    /**
                     * @brief Function used to allocate and return the address of the newly created element space in the front of the array
                     * @exceptsafe
                     * @return ElementType ptr = Address to the new memory space
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    __CDS_NoDiscard auto __a_newFront () noexcept -> ElementType *; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function used to allocate and return the address of the newly created element space in the back of the array
                     * @exceptsafe
                     * @return ElementType ptr = Address to the new memory space
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    __CDS_NoDiscard auto __a_newBack () noexcept -> ElementType *; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function used to allocate space for a number of elements at the front of the array, and return the addresses of each
                     * individual memory space in a given array
                     * @param [in] count : Size = number of elements space is required for
                     * @param [out] ppElements : __ElementType ptr ptr = Address to the array of addresses to populate with the newly created space
                     * @exceptsafe
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __a_newFrontArray ( /* NOLINT(bugprone-reserved-identifier) */
                            Size                count,
                            __ElementType    ** ppElements
                    ) noexcept -> void;

                protected:
                    /**
                     * @brief Function used to allocate space for a number of elements at the back of the array, and return the addresses of each
                     * individual memory space in a given array
                     * @param [in] count : Size = number of elements space is required for
                     * @param [out] ppElements : __ElementType ptr ptr = Address to the array of addresses to populate with the newly created space
                     * @exceptsafe
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __a_newBackArray ( /* NOLINT(bugprone-reserved-identifier) */
                            Size                count,
                            __ElementType    ** ppElements
                    ) noexcept -> void;

                protected:
                    /**
                     * @brief Function used to allocate space for an element, regardless of the location, and return the memory address
                     * @param [in] pReferenceElement : __ElementType cptr = Address to an Immutable Reference comparison element. Unused in array since no restriction for added values exists
                     * @param [out] pNewElementCreated : bool ptr = Address of a boolean value to be set to true if newly created value was created. In array, it is always set true
                     * @exceptsafe
                     * @return __ElementType ptr = Address to the newly created space for the element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __a_newAddress ( /* NOLINT(bugprone-reserved-identifier) */
                            __ElementType const * pReferenceElement,
                            bool                * pNewElementCreated
                    ) noexcept -> ElementType *;

                protected:
                    /**
                     * @brief Function used to allocate space for an element at a given index. Will move elements, starting with the given index, to the right
                     * @param index : Index = index to create the element at
                     * @exceptsafe
                     * @return __ElementType ptr = Address to the newly created space for the element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    __CDS_NoDiscard auto __a_newAt ( /* NOLINT(bugprone-reserved-identifier) */
                            Index index
                    ) noexcept -> ElementType *;

                protected:
                    /**
                     * @brief Function used to allocate space for a given number of elements at a given index. Will move elements, starting with the given index, to the right
                     * @param [in] index : Index = index to create the element spaces at
                     * @param [in] count : Size = number of elements to be inserted at given index
                     * @param [out] ppElements : __ElementType ptr ptr = Address to the array of addresses to populate with the addresses of the newly created memory spaces
                     * @exceptsafe
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __a_newArrayAt ( /* NOLINT(bugprone-reserved-identifier) */
                            Index               index,
                            Size                count,
                            __ElementType    ** ppElements
                    ) noexcept -> void;

                protected:
                    /**
                     * @brief Function used to allocate space for an element before a given iterator. Will move elements, starting with the given iterator element, to the right
                     * @param [in] iterator : AbstractAddressIterator cref = Constant Reference to the iterator to allocate an element space before
                     * @exceptsafe
                     * @return __ElementType ptr = Address to the newly created space for the element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __a_newBefore ( /* NOLINT(bugprone-reserved-identifier) */
                            AbstractAddressIterator < __ElementType > const & iterator
                    ) noexcept -> __ElementType *;

                protected:
                    /**
                     * @brief Function used to allocate space for an element before a given const iterator. Will move elements, starting with the given iterator element, to the right
                     * @param [in] iterator : AbstractAddressIterator cref = Constant Reference to the const iterator to allocate an element space before
                     * @exceptsafe
                     * @return __ElementType ptr = Address to the newly created space for the element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __a_newBeforeConst ( /* NOLINT(bugprone-reserved-identifier) */
                            AbstractAddressIterator < __ElementType const > const & iterator
                    ) noexcept -> __ElementType *;

                protected:
                    /**
                     * @brief Function used to allocate space for an element after a given iterator. Will move elements, starting after the given iterator element, to the right
                     * @param [in] iterator : AbstractAddressIterator cref = Constant Reference to the iterator to allocate an element space after
                     * @exceptsafe
                     * @return __ElementType ptr = Address to the newly created space for the element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __a_newAfter ( /* NOLINT(bugprone-reserved-identifier) */
                            AbstractAddressIterator < __ElementType > const & iterator
                    ) noexcept -> __ElementType *;

                protected:
                    /**
                     * @brief Function used to allocate space for an element after a given const iterator. Will move elements, starting after the given iterator element, to the right
                     * @param [in] iterator : AbstractAddressIterator cref = Constant Reference to the const iterator to allocate an element space after
                     * @exceptsafe
                     * @return __ElementType ptr = Address to the newly created space for the element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __a_newAfterConst ( /* NOLINT(bugprone-reserved-identifier) */
                            AbstractAddressIterator < __ElementType const > const & iterator
                    ) noexcept -> __ElementType *;

                protected:
                    /**
                     * @brief Function used to allocate space for a given number of elements before a given iterator. Will move elements, starting with the given iterator, to the right
                     * @param [in] iterator : AbstractAddressIterator cref = Constant Reference to the iterator to allocate the element spaces before
                     * @param [in] count : Size = number of elements to be inserted at given index
                     * @param [out] ppElements : __ElementType ptr ptr = Address to the array of addresses to populate with the addresses of the newly created memory spaces
                     * @exceptsafe
                     * @return bool = true if allocation was successful, false otherwise
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __a_newBeforeArray ( /* NOLINT(bugprone-reserved-identifier) */
                            AbstractAddressIterator < __ElementType >   const & iterator,
                            Size                                                count,
                            __ElementType                                    ** ppElements
                    ) noexcept -> bool;

                protected:
                    /**
                     * @brief Function used to allocate space for a given number of elements before a given const iterator. Will move elements, starting with the given iterator, to the right
                     * @param [in] iterator : AbstractAddressIterator cref = Constant Reference to the const iterator to allocate the element spaces before
                     * @param [in] count : Size = number of elements to be inserted at given index
                     * @param [out] ppElements : __ElementType ptr ptr = Address to the array of addresses to populate with the addresses of the newly created memory spaces
                     * @exceptsafe
                     * @return bool = true if allocation was successful, false otherwise
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __a_newBeforeArrayConst ( /* NOLINT(bugprone-reserved-identifier) */
                            AbstractAddressIterator < __ElementType const > const & iterator,
                            Size                                                    count,
                            __ElementType                                        ** ppElements
                    ) noexcept -> bool;

                protected:
                    /**
                     * @brief Function used to allocate space for a given number of elements after a given iterator. Will move elements, starting after the given iterator, to the right
                     * @param [in] iterator : AbstractAddressIterator cref = Constant Reference to the iterator to allocate the element spaces after
                     * @param [in] count : Size = number of elements to be inserted at given index
                     * @param [out] ppElements : __ElementType ptr ptr = Address to the array of addresses to populate with the addresses of the newly created memory spaces
                     * @exceptsafe
                     * @return bool = true if allocation was successful, false otherwise
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __a_newAfterArray ( /* NOLINT(bugprone-reserved-identifier) */
                            AbstractAddressIterator < __ElementType >   const & iterator,
                            Size                                                count,
                            __ElementType                                    ** ppElements
                    ) noexcept -> bool;

                protected:
                    /**
                     * @brief Function used to allocate space for a given number of elements after a given const iterator. Will move elements, starting after the given iterator, to the right
                     * @param [in] iterator : AbstractAddressIterator cref = Constant Reference to the const iterator to allocate the element spaces after
                     * @param [in] count : Size = number of elements to be inserted at given index
                     * @param [out] ppElements : __ElementType ptr ptr = Address to the array of addresses to populate with the addresses of the newly created memory spaces
                     * @exceptsafe
                     * @return bool = true if allocation was successful, false otherwise
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __a_newAfterArrayConst ( /* NOLINT(bugprone-reserved-identifier) */
                            AbstractAddressIterator < __ElementType const > const & iterator,
                            Size                                                    count,
                            __ElementType                                        ** ppElements
                    ) noexcept -> bool;

                private:
                    /**
                     * @brief Function used to initialize the array data at first use
                     * @exceptsafe
                     *
                     * @test Suite: CTS-00001, Group: All, Test Cases: All
                     * @private
                     */
                    auto __a_init () noexcept -> void; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function used to acquire a mutable forward iterator referencing the first element
                     * @excetpsafe
                     * @return __a_Iterator = Address Iterator to the first element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __a_begin () noexcept -> __a_Iterator; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function used to acquire a mutable forward iterator referencing the space after the last element
                     * @excetpsafe
                     * @return __a_Iterator = Address Iterator to the space after the last element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __a_end () noexcept -> __a_Iterator; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function used to acquire an immutable forward iterator referencing the first element
                     * @excetpsafe
                     * @return __a_ConstIterator = Address Const Iterator to the first element
                     *
                     * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                     * @protected
                     */
                    __CDS_NoDiscard constexpr auto __a_cbegin () const noexcept -> __a_ConstIterator; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function used to acquire an immutable forward iterator referencing the space after the last element
                     * @excetpsafe
                     * @return __a_ConstIterator = Address Const Iterator to the space after the last element
                     *
                     * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                     * @protected
                     */
                    __CDS_NoDiscard constexpr auto __a_cend () const noexcept -> __a_ConstIterator; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function used to acquire a mutable backward iterator referencing the last element
                     * @excetpsafe
                     * @return __a_ReverseIterator = Address Iterator to the last element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __a_rbegin () noexcept -> __a_ReverseIterator; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function used to acquire a mutable backward iterator referencing the space before the first element
                     * @excetpsafe
                     * @return __a_ReverseIterator = Address Iterator to the space before the first element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __a_rend () noexcept -> __a_ReverseIterator; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function used to acquire an immutable backward iterator referencing the last element
                     * @excetpsafe
                     * @return __a_ConstReverseIterator = Address Const Iterator to the last element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    __CDS_NoDiscard constexpr auto __a_crbegin () const noexcept -> __a_ConstReverseIterator; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function used to acquire an immutable backward iterator referencing the space before the first element
                     * @excetpsafe
                     * @return __a_ConstReverseIterator = Address Const Iterator to the space before the first element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    __CDS_NoDiscard constexpr auto __a_crend () const noexcept -> __a_ConstReverseIterator; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function used to acquire the address of the buffer, offset from the first element
                     * @exceptsafe
                     * @return __ElementType cptr = Equivalent to a C-Array, Address to the first immutable element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    __CDS_NoDiscard constexpr auto __a_data () const noexcept -> __ElementType const *; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function used to acquire the address of the buffer, offset from the first element
                     * @exceptsafe
                     * @return __ElementType ptr = Equivalent to a C-Array, Address to the first element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __a_data () noexcept -> __ElementType *; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Function used to resize the element space to a given size. It will initialize the empty space with a default constructor
                     * @tparam __TElementType is an alias for __ElementType used to invoke substitution, enabling the function only if __ElementType is default constructible
                     * @param [in] size : Size = new size of the array
                     * @exceptsafe
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    template <
                            typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isDefaultConstructible < __TElementType > ()
                            > = 0
                    > auto __a_resize (                                 /* NOLINT(bugprone-reserved-identifier) */
                            Size size
                    ) noexcept -> void;

                protected:
                    /**
                     * @brief Function used to resize the element space to a given size. It will initialize the empty space with the received value
                     * @tparam __TElementType is an alias for __ElementType used to invoke substitution, enabling the function only if __ElementType is copy constructible
                     * @param [in] size : Size = new size of the array
                     * @param [in] defaultValue : __ElementType cref = Constant Reference to the element to be used initializing the newly created elements
                     * @exceptsafe
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    template <
                            typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto __a_resize (                                 /* NOLINT(bugprone-reserved-identifier) */
                            Size                    size,
                            __ElementType   const & defaultValue
                    ) noexcept -> void;

                protected:
                    /**
                     * @brief Function used to shrink the array to the given size. Will not do anything if given a size greater than actual
                     * @param [in] size : Size = new size of the array
                     * @exceptsafe
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __a_shrink (                                 /* NOLINT(bugprone-reserved-identifier) */
                            Size size
                    ) noexcept -> void;

                protected:
                    /**
                     * @brief Function used to enlarge, but not initialize the elements, the array to the given size. New space will NOT be initialized
                     * @param [in] size : Size = new size of the array
                     * @exceptsafe
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __a_reserve (                                /* NOLINT(bugprone-reserved-identifier) */
                            Size size
                    ) noexcept -> void;

                protected:
                    /**
                     * @brief Function used to clear the current contents and copy the data from a received array.
                     * @tparam __TElementType is an alias for __ElementType used to invoke substitution, enabling the function only if __ElementType is copy constructible
                     * @param [in] array : __Array cref = Constant Reference to an array to copy the data from
                     * @exceptsafe
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    template <
                            typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto __a_copy (                                   /* NOLINT(bugprone-reserved-identifier) */
                            __Array const & array
                    ) noexcept -> void;

                protected:
                    /**
                     * @brief Function used to clear the current contents and move the data from a received array.
                     * @param [in, out] array : __Array mref = Move Reference to an array to acquire and release the data from
                     * @exceptsafe
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    auto __a_move ( /* NOLINT(bugprone-reserved-identifier) */
                            __Array && array
                    ) noexcept -> void;

                private:
                    /**
                     * @brief Function used to copy the data from a received array. It will NOT clear the array prior to copying
                     * @tparam __TElementType is an alias for __ElementType used to invoke substitution, enabling the function only if __ElementType is copy constructible
                     * @param [in] array : __Array cref = Constant Reference to an array to copy the data from
                     * @exceptsafe
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    template <
                            typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto __a_copyCleared (                            /* NOLINT(bugprone-reserved-identifier) */
                            __Array const & array
                    ) noexcept -> void;

                private:
                    /**
                     * @brief Function used to move the data from a received array. It will NOT clear the array prior to copying
                     * @param [in, out] array : __Array mref = Move Reference to an array to acquire and release the data from
                     * @exceptsafe
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @protected
                     */
                    __CDS_cpplang_NonConstConstexprMemberFunction auto __a_moveCleared (  /* NOLINT(bugprone-reserved-identifier) */
                            __Array && array
                    ) noexcept -> void;
                };


                template <
                        typename __ElementType,                                         /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType > __equals /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename __ServerType                                           /* NOLINT(bugprone-reserved-identifier) */
                > class __Array <
                        __ElementType,
                        __equals
                > :: __Dispatcher :
                        public __ListServerDispatcher <
                                __ServerType,
                                __Array < __ElementType, __equals >,
                                __ElementType,
                                AbstractAddressIterator < __ElementType >,
                                AbstractAddressIterator < __ElementType const >,
                                ForwardAddressIterator < __ElementType >,
                                ForwardAddressIterator < __ElementType const >,
                                BackwardAddressIterator < __ElementType >,
                                BackwardAddressIterator < __ElementType const >,
                                & __Array < __ElementType, __equals > :: __a_begin,
                                & __Array < __ElementType, __equals > :: __a_end,
                                & __Array < __ElementType, __equals > :: __a_cbegin,
                                & __Array < __ElementType, __equals > :: __a_cend,
                                & __Array < __ElementType, __equals > :: __a_rbegin,
                                & __Array < __ElementType, __equals > :: __a_rend,
                                & __Array < __ElementType, __equals > :: __a_crbegin,
                                & __Array < __ElementType, __equals > :: __a_crend,
                                & __Array < __ElementType, __equals > :: __a_newAddress,
                                & __Array < __ElementType, __equals > :: __a_newFront,
                                & __Array < __ElementType, __equals > :: __a_newBack,
                                & __Array < __ElementType, __equals > :: __a_newFrontArray,
                                & __Array < __ElementType, __equals > :: __a_newBackArray,
                                & __Array < __ElementType, __equals > :: __a_newBefore,
                                & __Array < __ElementType, __equals > :: __a_newBeforeConst,
                                & __Array < __ElementType, __equals > :: __a_newAfter,
                                & __Array < __ElementType, __equals > :: __a_newAfterConst,
                                & __Array < __ElementType, __equals > :: __a_newBeforeArray,
                                & __Array < __ElementType, __equals > :: __a_newBeforeArrayConst,
                                & __Array < __ElementType, __equals > :: __a_newAfterArray,
                                & __Array < __ElementType, __equals > :: __a_newAfterArrayConst,
                                & __Array < __ElementType, __equals > :: __a_removeIterator,
                                & __Array < __ElementType, __equals > :: __a_removeConstIterator
                        > {};

            }
        }
    }
}

#endif /* __CDS_SHARED_ARRAY_HPP__ */
