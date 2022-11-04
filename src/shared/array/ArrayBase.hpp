/*
 * Created by loghin on 7/5/22.
 */

#ifndef __CDS_SHARED_ARRAY_BASE_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_ARRAY_BASE_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @class Base implementation class for array-based objects
             *
             * Works with a two-headed buffer, allocated with a front and back capacity, to allow for pushFront and pushBack operations in O(1)
             *
             * @tparam __ElementType is the element enclosed in the array
             * @tparam __equals is the function used to compare two elements
             *
             * @test Suite: CTS-00001, Group: All, Test Cases: All
             * @test Suite: MCTS-00001, Group: All, Test Cases: All
             *
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename                                                                            __ElementType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __ElementType const &, __ElementType const & >    __equals        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > class __ArrayBase {                                                                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @typedef Alias for template parameter __ElementType
                 * @protected
                 */
                using ElementType = __ElementType;

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Starting and Minimum capacity for front and back allocation sizes
                 * @static
                 * @private
                 */
                static Size const __ab_minCapacity = 32ULL; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @typedef Alias for forward mutable iterator
                 * @public
                 */
                using __ab_Iterator                      = ForwardAddressIterator < __ElementType >; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @typedef Alias for forward immutable iterator
                 * @public
                 */
                using __ab_ConstIterator                 = ForwardAddressIterator < __ElementType const >; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @typedef Alias for backward mutable iterator
                 * @public
                 */
                using __ab_ReverseIterator               = BackwardAddressIterator < __ElementType >; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @typedef Alias for backward immutable iterator
                 * @public
                 */
                using __ab_ConstReverseIterator          = BackwardAddressIterator < __ElementType const >; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @class Dispatcher to this class' implementation
                 * @implements __ListServerDispatcher
                 * @public
                 */
                template < typename __ServerType >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                class __Dispatcher;                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @struct Container for the elements required by the array
                 * @private
                 */
                struct __ArrayImplDataContainer { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                    /** @brief Pointer to the data buffer */
                    __ElementType * _pBuffer            { nullptr };

                    /** @brief Pointer to the first element in the buffer */
                    __ElementType * _pFront             { nullptr };

                    /** @brief Pointer to the element after the last in the buffer */
                    __ElementType * _pBack              { nullptr };

                    /** @brief Capacity allocated for front elements */
                    Size            _frontCapacity      { 0ULL };

                    /** @brief Capacity allocated for back elements */
                    Size            _backCapacity       { 0ULL };

                    /** @brief Next capacity allocated for front elements */
                    Size            _frontNextCapacity  { 0ULL };

                    /** @brief Next capacity allocated for back elements */
                    Size            _backNextCapacity   { 0ULL };
                };

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Pointer to the data required for the array
                 * @private
                 */
                __ArrayImplDataContainer * _pData { nullptr };

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Default Constructor, constexpr
                 * @exceptsafe
                 *
                 * @test Suite: CTS-00001, Group: All, Test Cases: All
                 * @test Suite: MCTS-00001, Group: All, Test Cases: All
                 * @protected
                 */
                constexpr __ArrayBase () noexcept;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Copy Constructor
                 * @param [in] array : __ArrayBase cref = Constant Reference to an Array to copy the data from
                 * @exceptsafe
                 *
                 * @test Suite: CTS-00001, Group: All, Test Cases: All
                 * @test Suite: MCTS-00001, Group: All, Test Cases: All
                 * @protected
                 */
                __ArrayBase ( /* NOLINT(bugprone-reserved-identifier,google-explicit-constructor) */
                        __ArrayBase const & array
                ) noexcept;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Move Constructor, constexpr
                 * @param [in, out] array : __ArrayBase mref = Move Reference to an array to release and acquire the data from
                 * @exceptsafe
                 *
                 * @test Suite: CTS-00001, Group: All, Test Cases: All
                 * @test Suite: MCTS-00001, Group: All, Test Cases: All
                 * @protected
                 */
                constexpr __ArrayBase (
                        __ArrayBase && array
                ) noexcept;

            public:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Implicit Destructor, constexpr
                 * @exceptsafe
                 *
                 * @test Suite: CTS-00001, Group: All, Test Cases: All
                 * @test Suite: MCTS-00001, Group: All, Test Cases: All
                 * @protected
                 */
                ~__ArrayBase () noexcept = default;

            public:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Deleted Copy Assignment Operator, constexpr
                 * @param [in] array : __ArrayBase cref = Constant Reference to an Array to copy the data from
                 * @exceptsafe
                 * @return __ArrayBase ref = Reference to the modified object
                 *
                 * @test Suite: CTS-00001, Group: All, Test Cases: All
                 * @test Suite: MCTS-00001, Group: All, Test Cases: All
                 * @protected
                 */
                auto operator = (
                        __ArrayBase const &
                ) noexcept -> __ArrayBase & = delete;

            public:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Deleted Copy Assignment Operator, constexpr
                 * @param [in, out] array : __ArrayBase mref = Move Reference to an array to release and acquire the data from
                 * @exceptsafe
                 * @return __ArrayBase ref = Reference to the modified object
                 *
                 * @test Suite: CTS-00001, Group: All, Test Cases: All
                 * @test Suite: MCTS-00001, Group: All, Test Cases: All
                 * @protected
                 */
                auto operator = (
                        __ArrayBase &&
                ) noexcept -> __ArrayBase & = delete;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to clear either the contents of the buffer, or purge the whole array data
                 * @param [in] destroyBuffer : bool = if true, will purge the whole memory array data, otherwise, will only clear the buffer
                 * @exceptsafe
                 *
                 * @test Suite: CTS-00001, Group: All, Test Cases: All
                 * @test Suite: MCTS-00001, Group: All, Test Cases: All
                 * @protected
                 */
                auto __ab_clear ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        bool destroyBuffer
                ) noexcept -> void;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to acquire the number of elements in the array
                 * @exceptsafe
                 * @return Size = number of elements in the array
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard constexpr auto __ab_size () const noexcept -> Size; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to remove an element at a given index
                 * @param [in] index : Index = index of the element to be removed
                 * @exceptsafe
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                auto __ab_remove ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        Index index
                ) noexcept -> void;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to remove an element at a given iterator
                 * @param [in] iterator : AbstractAddressIterator cref = Constant Reference to an iterator indicating to the element to be removed
                 * @exceptsafe
                 * @return bool = true if removal was successful, false otherwise
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                auto __ab_removeIterator ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        AbstractAddressIterator < __ElementType > const & iterator
                ) noexcept -> bool;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to remove an element at a given const iterator
                 * @param [in] iterator : AbstractAddressIterator cref = Constant Reference to an iterator indicating to the element to be removed
                 * @exceptsafe
                 * @return bool = true if removal was successful, false otherwise
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                auto __ab_removeConstIterator ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        AbstractAddressIterator < __ElementType const > const & iterator
                ) noexcept -> bool;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to remove multiple elements at a given number of iterators
                 * @param [in] ppIterators : AbstractAddressIterator cptr cptr  = Immutable Address to an array of Immutable Addresses to iterators
                 * @param [in] iteratorArrayCount : Size = number of iterators in the given array
                 * @exceptsafe
                 * @return Size = number of removed elements
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                auto __ab_removeIteratorArray ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        AbstractAddressIterator < __ElementType >   const * const * ppIterators,
                        Size                                                        iteratorCount
                ) noexcept -> Size;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to remove multiple elements at a given number of const iterators
                 * @param [in] ppIterators : AbstractAddressIterator cptr cptr  = Immutable Address to an array of Immutable Addresses to const iterators
                 * @param [in] iteratorArrayCount : Size = number of iterators in the given array
                 * @exceptsafe
                 * @return Size = number of removed elements
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                auto __ab_removeConstIteratorArray ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        AbstractAddressIterator < __ElementType const > const * const * ppIterators,
                        Size                                                            iteratorCount
                ) noexcept -> Size;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to acquire an address to the element located at given index
                 * @param [in] index : Index = index of the element to acquire the address of
                 * @exceptsafe
                 * @return ElementType ptr = Address of the requested element
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __ab_get ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */
                        Index index
                ) noexcept -> ElementType *;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to acquire an address to the element located at given index
                 * @param [in] index : Index = index of the element to acquire the address of
                 * @exceptsafe
                 * @return ElementType cptr = Address of the requested immutable element
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard constexpr auto __ab_get ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard) */
                        Index index
                ) const noexcept -> ElementType const *;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to allocate and return the address of the newly created element space in the front of the array
                 * @exceptsafe
                 * @return ElementType ptr = Address to the new memory space
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard auto __ab_newFront () noexcept -> ElementType *; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to allocate and return the address of the newly created element space in the back of the array
                 * @exceptsafe
                 * @return ElementType ptr = Address to the new memory space
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard auto __ab_newBack () noexcept -> ElementType *; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
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
                auto __ab_newFrontArray ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        Size                count,
                        __ElementType    ** ppElements
                ) noexcept -> void;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
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
                auto __ab_newBackArray ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        Size                count,
                        __ElementType    ** ppElements
                ) noexcept -> void;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
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
                auto __ab_newAddress ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ElementType const * pReferenceElement,
                        bool                * pNewElementCreated
                ) noexcept -> ElementType *;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to allocate space for an element at a given index. Will move elements, starting with the given index, to the right
                 * @param index : Index = index to create the element at
                 * @exceptsafe
                 * @return __ElementType ptr = Address to the newly created space for the element
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard auto __ab_newAt ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        Index index
                ) noexcept -> ElementType *;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
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
                auto __ab_newArrayAt ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        Index               index,
                        Size                count,
                        __ElementType    ** ppElements
                ) noexcept -> void;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to allocate space for an element before a given iterator. Will move elements, starting with the given iterator element, to the right
                 * @param [in] iterator : AbstractAddressIterator cref = Constant Reference to the iterator to allocate an element space before
                 * @exceptsafe
                 * @return __ElementType ptr = Address to the newly created space for the element
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                auto __ab_newBefore ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        AbstractAddressIterator < __ElementType > const & iterator
                ) noexcept -> __ElementType *;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to allocate space for an element before a given const iterator. Will move elements, starting with the given iterator element, to the right
                 * @param [in] iterator : AbstractAddressIterator cref = Constant Reference to the const iterator to allocate an element space before
                 * @exceptsafe
                 * @return __ElementType ptr = Address to the newly created space for the element
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                auto __ab_newBeforeConst ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        AbstractAddressIterator < __ElementType const > const & iterator
                ) noexcept -> __ElementType *;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to allocate space for an element after a given iterator. Will move elements, starting after the given iterator element, to the right
                 * @param [in] iterator : AbstractAddressIterator cref = Constant Reference to the iterator to allocate an element space after
                 * @exceptsafe
                 * @return __ElementType ptr = Address to the newly created space for the element
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                auto __ab_newAfter ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        AbstractAddressIterator < __ElementType > const & iterator
                ) noexcept -> __ElementType *;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to allocate space for an element after a given const iterator. Will move elements, starting after the given iterator element, to the right
                 * @param [in] iterator : AbstractAddressIterator cref = Constant Reference to the const iterator to allocate an element space after
                 * @exceptsafe
                 * @return __ElementType ptr = Address to the newly created space for the element
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                auto __ab_newAfterConst ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        AbstractAddressIterator < __ElementType const > const & iterator
                ) noexcept -> __ElementType *;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
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
                auto __ab_newBeforeArray ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        AbstractAddressIterator < __ElementType >   const & iterator,
                        Size                                                count,
                        __ElementType                                    ** ppElements
                ) noexcept -> bool;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
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
                auto __ab_newBeforeArrayConst ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        AbstractAddressIterator < __ElementType const > const & iterator,
                        Size                                                    count,
                        __ElementType                                        ** ppElements
                ) noexcept -> bool;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
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
                auto __ab_newAfterArray ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        AbstractAddressIterator < __ElementType >   const & iterator,
                        Size                                                count,
                        __ElementType                                    ** ppElements
                ) noexcept -> bool;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
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
                auto __ab_newAfterArrayConst ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        AbstractAddressIterator < __ElementType const > const & iterator,
                        Size                                                    count,
                        __ElementType                                        ** ppElements
                ) noexcept -> bool;

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to initialize the array data at first use
                 * @exceptsafe
                 *
                 * @test Suite: CTS-00001, Group: All, Test Cases: All
                 * @test Suite: MCTS-00001, Group: All, Test Cases: All
                 * @private
                 */
                auto __ab_init () noexcept -> void; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to acquire a mutable forward iterator referencing the first element
                 * @excetpsafe
                 * @return __ab_Iterator = Address Iterator to the first element
                 *
                 * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
                 * @protected
                 */
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __ab_begin () noexcept -> __ab_Iterator; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to acquire a mutable forward iterator referencing the space after the last element
                 * @excetpsafe
                 * @return __ab_Iterator = Address Iterator to the space after the last element
                 *
                 * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
                 * @protected
                 */
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __ab_end () noexcept -> __ab_Iterator; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to acquire an immutable forward iterator referencing the first element
                 * @excetpsafe
                 * @return __ab_ConstIterator = Address Const Iterator to the first element
                 *
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @protected
                 */
                __CDS_NoDiscard constexpr auto __ab_cbegin () const noexcept -> __ab_ConstIterator; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to acquire an immutable forward iterator referencing the space after the last element
                 * @excetpsafe
                 * @return __ab_ConstIterator = Address Const Iterator to the space after the last element
                 *
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @protected
                 */
                __CDS_NoDiscard constexpr auto __ab_cend () const noexcept -> __ab_ConstIterator; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to acquire a mutable backward iterator referencing the last element
                 * @excetpsafe
                 * @return __ab_ReverseIterator = Address Iterator to the last element
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __ab_rbegin () noexcept -> __ab_ReverseIterator; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to acquire a mutable backward iterator referencing the space before the first element
                 * @excetpsafe
                 * @return __ab_ReverseIterator = Address Iterator to the space before the first element
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __ab_rend () noexcept -> __ab_ReverseIterator; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to acquire an immutable backward iterator referencing the last element
                 * @excetpsafe
                 * @return __ab_ConstReverseIterator = Address Const Iterator to the last element
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard constexpr auto __ab_crbegin () const noexcept -> __ab_ConstReverseIterator; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to acquire an immutable backward iterator referencing the space before the first element
                 * @excetpsafe
                 * @return __ab_ConstReverseIterator = Address Const Iterator to the space before the first element
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard constexpr auto __ab_crend () const noexcept -> __ab_ConstReverseIterator; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to acquire the address of the buffer, offset from the first element
                 * @exceptsafe
                 * @return __ElementType cptr = Equivalent to a C-Array, Address to the first immutable element
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard constexpr auto __ab_data () const noexcept -> __ElementType const *; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to acquire the address of the buffer, offset from the first element
                 * @exceptsafe
                 * @return __ElementType ptr = Equivalent to a C-Array, Address to the first element
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __ab_data () noexcept -> __ElementType *; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
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
                        typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isDefaultConstructible < __TElementType > ()
                        > = 0
                > auto __ab_resize (                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        Size size
                ) noexcept -> void;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
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
                        typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        > = 0
                > auto __ab_resize (                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        Size                    size,
                        __ElementType   const & defaultValue
                ) noexcept -> void;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to shrink the array to the given size. Will not do anything if given a size greater than actual
                 * @param [in] size : Size = new size of the array
                 * @exceptsafe
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                auto __ab_shrink (                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        Size size
                ) noexcept -> void;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to enlarge, but not initialize the elements, the array to the given size. New space will NOT be initialized
                 * @param [in] size : Size = new size of the array
                 * @exceptsafe
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                auto __ab_reserve (                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        Size size
                ) noexcept -> void;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to clear the current contents and copy the data from a received array.
                 * @tparam __TElementType is an alias for __ElementType used to invoke substitution, enabling the function only if __ElementType is copy constructible
                 * @param [in] array : __ArrayBase cref = Constant Reference to an array to copy the data from
                 * @exceptsafe
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                template <
                        typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        > = 0
                > auto __ab_copy (                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ArrayBase const & array
                ) noexcept -> void;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to clear the current contents and move the data from a received array.
                 * @param [in, out] array : __ArrayBase mref = Move Reference to an array to acquire and release the data from
                 * @exceptsafe
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                auto __ab_move ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ArrayBase && array
                ) noexcept -> void;

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to copy the data from a received array. It will NOT clear the array prior to copying
                 * @tparam __TElementType is an alias for __ElementType used to invoke substitution, enabling the function only if __ElementType is copy constructible
                 * @param [in] array : __ArrayBase cref = Constant Reference to an array to copy the data from
                 * @exceptsafe
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @private
                 */
                template <
                        typename __TElementType = __ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        > = 0
                > auto __ab_copyCleared (                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ArrayBase const & array
                ) noexcept -> void;

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to move the data from a received array. It will NOT clear the array prior to copying
                 * @param [in, out] array : __ArrayBase mref = Move Reference to an array to acquire and release the data from
                 * @exceptsafe
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @private
                 */
                __CDS_cpplang_NonConstConstexprMemberFunction auto __ab_moveCleared (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ArrayBase && array
                ) noexcept -> void;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to compare the current array to a given array
                 * @param [in] array : __ArrayBase cref = Constant Reference to an array to compare the current one to
                 * @exceptsafe
                 * @return bool = true if arrays contain equal content, false otherwise
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @protected
                 */
                __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __ab_equals (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */
                        __ArrayBase const & array
                ) const noexcept -> bool;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                template <
                        typename __Comparator = decltype ( & cds :: predicates :: lessThan < __ElementType > )  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                > auto __ab_sort (                                                                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __Comparator const & comparator = & cds :: predicates :: lessThan < __ElementType >
                ) noexcept -> void;

            };


            template <
                    typename                                                                            __ElementType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __ElementType const &, __ElementType const & >    __equals        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename __ServerType                                                                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > class __ArrayBase <
                    __ElementType,
                    __equals
            > :: __Dispatcher :
                    public __ListServerDispatcher <
                            __ServerType,
                            __ArrayBase < __ElementType, __equals >,
                            __ElementType,
                            AbstractAddressIterator < __ElementType >,
                            AbstractAddressIterator < __ElementType const >,
                            ForwardAddressIterator < __ElementType >,
                            ForwardAddressIterator < __ElementType const >,
                            BackwardAddressIterator < __ElementType >,
                            BackwardAddressIterator < __ElementType const >,
                            & __ArrayBase < __ElementType, __equals > :: __ab_begin,
                            & __ArrayBase < __ElementType, __equals > :: __ab_end,
                            & __ArrayBase < __ElementType, __equals > :: __ab_cbegin,
                            & __ArrayBase < __ElementType, __equals > :: __ab_cend,
                            & __ArrayBase < __ElementType, __equals > :: __ab_rbegin,
                            & __ArrayBase < __ElementType, __equals > :: __ab_rend,
                            & __ArrayBase < __ElementType, __equals > :: __ab_crbegin,
                            & __ArrayBase < __ElementType, __equals > :: __ab_crend,
                            & __ArrayBase < __ElementType, __equals > :: __ab_newAddress,
                            & __ArrayBase < __ElementType, __equals > :: __ab_newFront,
                            & __ArrayBase < __ElementType, __equals > :: __ab_newBack,
                            & __ArrayBase < __ElementType, __equals > :: __ab_newFrontArray,
                            & __ArrayBase < __ElementType, __equals > :: __ab_newBackArray,
                            & __ArrayBase < __ElementType, __equals > :: __ab_newBefore,
                            & __ArrayBase < __ElementType, __equals > :: __ab_newBeforeConst,
                            & __ArrayBase < __ElementType, __equals > :: __ab_newAfter,
                            & __ArrayBase < __ElementType, __equals > :: __ab_newAfterConst,
                            & __ArrayBase < __ElementType, __equals > :: __ab_newBeforeArray,
                            & __ArrayBase < __ElementType, __equals > :: __ab_newBeforeArrayConst,
                            & __ArrayBase < __ElementType, __equals > :: __ab_newAfterArray,
                            & __ArrayBase < __ElementType, __equals > :: __ab_newAfterArrayConst,
                            & __ArrayBase < __ElementType, __equals > :: __ab_removeIterator,
                            & __ArrayBase < __ElementType, __equals > :: __ab_removeConstIterator,
                            & __ArrayBase < __ElementType, __equals > :: __ab_removeIteratorArray,
                            & __ArrayBase < __ElementType, __equals > :: __ab_removeConstIteratorArray
                    > {};

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_ARRAY_BASE_HPP__ */
