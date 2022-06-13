//
// Created by loghin on 4/24/2022.
//

#ifndef __CDS_EX_LIST_HPP__
#define __CDS_EX_LIST_HPP__

#include <CDS/experimental/Collection>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        /**
         * @class Abstract Object representing any Indexed Iterable Container of given elements of type
         * @tparam __ElementType is the type of elements contained into List
         */
        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class List : public Collection < __ElementType > {

        public:
            /**
             * @typedef Alias for __ElementType, the type of the contained elements, publicly accessible, useful in sfinae statements - decltype ( Collection ) :: ElementType
             */
            using typename Collection < __ElementType > :: ElementType;

        protected:
            /**
             * @typedef Alias for std :: initializer_list < T > or std :: initializer_list < ElementType >
             */
            using typename Collection < __ElementType > :: InitializerList;

        protected:
            /**
             * @interface An Iterator Delegate represents the actual implementation of the iterator done by the derived classes. The Abstract Delegate Iterator is the base used by the Iterator bases
             */
            using typename Collection < __ElementType > :: AbstractDelegateIterator;

        protected:
            /**
             * @class The base class for mutable Iterator types. It is the wrapper over the AbstractDelegateIterator, acquired from derived classes implementation
             */
            class DelegateIterator;

        protected:
            /**
             * @class The base class for immutable Iterator types. It is the wrapper over the AbstractDelegateIterator, acquired from derived classes implementation
             */
            using typename Collection < __ElementType > :: DelegateConstIterator;

        protected:
            /**
             * @class The base class for Iterator types, mutable or immutable. It is the wrapper over the AbstractDelegateIterator, acquired from derived classes implementation
             */
            using typename Collection < __ElementType > :: AbstractIterator;

        protected:
            /**
             * @enum The types of delegate iterator requests the Collection Base Object can make to its Derivative Objects when acquiring an Iterator Delegate Implementation
             */
            using typename Collection < __ElementType > :: DelegateIteratorRequestType;

        public:
            /**
             * @class The Iterator type used for Forward Iteration over mutable values
             */
            class Iterator;

        public:
            /**
             * @class The Iterator type used for Forward Iteration over immutable values
             */
            using typename Collection < __ElementType > :: ConstIterator;

        public:
            /**
             * @class The Iterator type used for Backward Iteration over mutable values
             */
            class ReverseIterator;

        public:
            /**
             * @class The Iterator type used for Backward Iteration over immutable values
             */
            using typename Collection < __ElementType > :: ConstReverseIterator;

        public:
            static Index const invalidIndex = -1;

        protected:
            /**
             * @brief Function used to safely acquire a Delegate Iterator Owned by a given Iterator
             * @param iterator : Iterator cref = Constant Reference to an Iterator Object
             * @exceptsafe
             * @return DelegateIterator cptr = Pointer to an Immutable, DelegateIterator-derived Object
             */
            constexpr static auto acquireDelegate (
                    Iterator const & iterator
            ) noexcept -> DelegateIterator const *;

        protected:
            /**
             * @brief Function used to safely acquire a Delegate Iterator Owned by a given Iterator
             * @param iterator : ReverseIterator cref = Constant Reference to an ReverseIterator Object
             * @exceptsafe
             * @return DelegateIterator cptr = Pointer to an Immutable, DelegateIterator-derived Object
             */
            constexpr static auto acquireDelegate (
                    ReverseIterator const & iterator
            ) noexcept -> DelegateIterator const *;

        protected:
            /**
             * @brief Import statement for
             *      acquireDelegate ( AbstractIterator ),
             *      acquireDelegate ( ConstIterator ),
             *      acquireDelegate ( ConstReverseIterator )
             */
            using Collection < __ElementType > :: acquireDelegate;

        protected:
            /**
             * @brief Function used to request a DelegateIterator from the Iterator constructing functions ( begin/end/rbegin/rend ) to acquire a DelegateIterator containing
             *      the implementation from the derived class, of requested iterator type
             * @param requestType : DelegateIteratorRequestType = the type of request, associated with expected returned type of iterator implementation
             * @exceptsafe
             * @return UniquePointer < DelegateIterator > = Uniquely-Owned Pointer to a DelegateIterator-derived object
             */
            virtual auto delegateIterator (
                    DelegateIteratorRequestType
            ) noexcept -> cds :: UniquePointer < DelegateIterator > = 0;

        public:
            /**
             * @brief Function used to acquire a Forward-Iterator, indicating to the first element of the collection
             * @exceptsafe
             * @return Iterator = requested Iterator object
             */
            auto begin () noexcept -> Iterator;

        public:
            /**
             * @brief Import statement for
             *      begin () const -> ConstIterator
             */
            using Collection < __ElementType > :: begin;

        public:
            /**
             * @brief Function used to acquire a Forward-Iterator, indicating after the last element of the collection
             * @exceptsafe
             * @return Iterator = requested Iterator object
             * @test tested in the class test
             */
            auto end () noexcept -> Iterator;

        public:
            /**
             * @brief Import statement for
             *      end () const -> ConstIterator
             */
            using Collection < __ElementType > :: end;

        public:
            /**
             * @brief Function used to acquire a Backward-ReverseIterator, indicating to the first element of the collection in reverse iteration order - last element of the collection
             * @exceptsafe
             * @return ReverseIterator = requested Iterator object
             * @test tested in the class test
             */
            auto rbegin () noexcept -> ReverseIterator;

        public:
            /**
             * @brief Import statement for
             *      rbegin () const -> ConstIterator
             */
            using Collection < __ElementType > :: rbegin;

        public:
            /**
             * @brief Function used to acquire a Backward-ReverseIterator, indicating after the last element of the collection in reverse iteration order - before first element of the collection
             * @exceptsafe
             * @return ReverseIterator = requested Iterator object
             * @test tested in the class test
             */
            auto rend () noexcept -> ReverseIterator;

        public:
            /**
             * @brief Import statement for
             *      rend () const -> ConstIterator
             */
            using Collection < __ElementType > :: rend;

        protected:
            /**
             * @brief Default Constructor
             * @exceptsafe
             * @test tested in collection/Collection test
             */
            constexpr List () noexcept = default;

        protected:
            /**
             * @brief Copy Constructor
             * @param list : List cref = Constant Reference to List to copy field values from
             * @exceptsafe
             * @test tested in collection/Collection test
             */
            constexpr List (
                    List const & list
            ) noexcept;

        protected:
            /**
             * @brief Move Constructor
             * @param list : List mref = Move Reference to List to move field values from
             * @exceptsafe
             * @test tested in collection/Collection test
             */
            constexpr List (
                    List && list
            ) noexcept;

        protected:
            /**
             * @brief Constructor with size given as parameter
             * @param size : Size = the element count of the created list
             * @exceptsafe
             * @test tested in collection/Collection test
             */
            constexpr explicit List (
                    Size size
            ) noexcept;

        public:
            /**
             * @brief Default Destructor
             * @exceptsafe
             * @test tested in collection/Collection test
             */
            ~List () noexcept override = default;

        public:
            /**
             * @brief Function used to acquire a mutable reference to the element at a given index.
             * @param index : Index = index of the element to acquire a reference to
             * @throws OutOfBoundsException if list is empty
             * @return ElementType ref = Reference to the element at the requested index
             *
             * Indexing works in a circular manner
             * <ul>
             *      <li> any index greater than or equal to the number of elements gets truncated by modulo with the number of elements. </li>
             *      <li> any negative index will act as if parsing the list in reverse. Any negative index less than the negative number of elements will behave as in the other case, being truncated </li>
             * </ul>
             *
             * @example
             *      given a list = [ 1, 2, 3, 4 ] <br/>
             *      list [ 1 ] = 1 <br/>
             *      list [ 5 ] = 1 <br/>
             *      list [ 6 ] = 1 <br/>
             *      list [ 14 ] = 3 <br/>
             *      list [ -1 ] = 4 <br/>
             *      list [ -2 ] = 3 <br/>
             *      list [ -3 ] = 2 <br/>
             *      list [ -4 ] = 1 <br/>
             *      list [ -7 ] = 2 <br/>
             */
            virtual auto get (
                    Index index
            ) noexcept (false) -> ElementType & = 0;

        public:
            /**
             * @brief Function used to acquire an immutable reference to the element at a given index.
             * @param index : Index = index of the element to acquire a reference to
             * @throws OutOfBoundsException if list is empty
             * @return ElementType cref = Constant Reference to the element at the requested index
             *
             * Indexing works in a circular manner
             * <ul>
             *      <li> any index greater than or equal to the number of elements gets truncated by modulo with the number of elements. </li>
             *      <li> any negative index will act as if parsing the list in reverse. Any negative index less than the negative number of elements will behave as in the other case, being truncated </li>
             * </ul>
             *
             * @example
             *      given a list = [ 1, 2, 3, 4 ] <br/>
             *      list [ 1 ] = 1 <br/>
             *      list [ 5 ] = 1 <br/>
             *      list [ 6 ] = 1 <br/>
             *      list [ 14 ] = 3 <br/>
             *      list [ -1 ] = 4 <br/>
             *      list [ -2 ] = 3 <br/>
             *      list [ -3 ] = 2 <br/>
             *      list [ -4 ] = 1 <br/>
             *      list [ -7 ] = 2 <br/>
             */
            virtual auto get (
                    Index index
            ) const noexcept (false) -> ElementType const & = 0;

        protected:
            /**
             * @brief Function used in Collection :: add implementation, called to acquire a pointer reference to allocate the new element to
             * @exceptsafe
             * @return ElementType ptr ref = Reference to an ElementType pointer.
             * @test tested in collection/Collection test
             */
            __CDS_OptimalInline auto pNewInsert () noexcept -> ElementType * & override;

        public:
            /**
             * @brief Function used to obtain a subsection of the current list, and store it into a given list
             * @tparam __CollectionType is the type of the list to store the sublist into
             * @tparam __VElementType is a type alias for __ElementType used to disable the function if __ElementType is not copy constructible
             * @param storeIn : __CollectionType ref = Reference to the list to store the new elements into
             * @param from : Index = the index from which to create the sublist, inclusive
             * @param to : Index = the index until which to create the sublist, exclusive
             * @exceptsafe
             * @return __CollectionType ref = Reference to the given list in 'storeIn'
             */
            template < typename __CollectionType, typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () && meta :: isDerivedFrom < __CollectionType, Collection < __ElementType > > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto sub (
                    __CollectionType  & storeIn,
                    Index               from,
                    Index               to
            ) const noexcept -> __CollectionType &;

        public:
            /**
             * @brief Function used to obtain a subsection of the current list
             * @tparam __CollectionType is the type of the list to store the sublist into
             * @tparam __VElementType is a type alias for __ElementType used to disable the function if __ElementType is not copy constructible
             * @param from : Index = the index from which to create the sublist, inclusive
             * @param to : Index = the index until which to create the sublist, exclusive
             * @exceptsafe
             * @return __CollectionType = List containing the requested subsection
             */
            template < typename __CollectionType, typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () && meta :: isDerivedFrom < __CollectionType, Collection < __ElementType > > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto sub (
                    Index from,
                    Index to
            ) const noexcept -> __CollectionType;

        public:
            /**
             * @brief Function used to obtain a subsection of the current list
             * @tparam __CollectionType is the type of the list to store the sublist into
             * @tparam __VElementType is a type alias for __ElementType used to disable the function if __ElementType is not copy constructible
             * @param from : Index = the index from which to create the sublist, inclusive
             * @param to : Index = the index until which to create the sublist, exclusive
             * @exceptsafe
             * @return ListType = List containing the requested subsection
             */
            template < template < typename ... > class __CollectionType, typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () && meta :: isDerivedFrom < __CollectionType < __ElementType >, Collection < __ElementType > > () > = 0 > // NOLINT(bugprone-reserved-identifier)
             auto sub (
                     Index from,
                     Index to
             ) const noexcept -> __CollectionType < ElementType >;

        public:
            /**
             * @brief Subscript Operator used to acquire a mutable reference to the element at a given index.
             * @param index : Index = index of the element to acquire a reference to
             * @throws OutOfBoundsException if list is empty
             * @return ElementType ref = Reference to the element at the requested index
             *
             * Indexing works in a circular manner
             * <ul>
             *      <li> any index greater than or equal to the number of elements gets truncated by modulo with the number of elements. </li>
             *      <li> any negative index will act as if parsing the list in reverse. Any negative index less than the negative number of elements will behave as in the other case, being truncated </li>
             * </ul>
             *
             * @example
             *      given a list = [ 1, 2, 3, 4 ] <br/>
             *      list [ 1 ] = 1 <br/>
             *      list [ 5 ] = 1 <br/>
             *      list [ 6 ] = 1 <br/>
             *      list [ 14 ] = 3 <br/>
             *      list [ -1 ] = 4 <br/>
             *      list [ -2 ] = 3 <br/>
             *      list [ -3 ] = 2 <br/>
             *      list [ -4 ] = 1 <br/>
             *      list [ -7 ] = 2 <br/>
             */
            auto operator [] (
                    Index index
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Subscript Operator used to acquire an immutable reference to the element at a given index.
             * @param index : Index = index of the element to acquire a reference to
             * @throws OutOfBoundsException if list is empty
             * @return ElementType cref = Constant Reference to the element at the requested index
             *
             * Indexing works in a circular manner
             * <ul>
             *      <li> any index greater than or equal to the number of elements gets truncated by modulo with the number of elements. </li>
             *      <li> any negative index will act as if parsing the list in reverse. Any negative index less than the negative number of elements will behave as in the other case, being truncated </li>
             * </ul>
             *
             * @example
             *      given a list = [ 1, 2, 3, 4 ] <br/>
             *      list [ 1 ] = 1 <br/>
             *      list [ 5 ] = 1 <br/>
             *      list [ 6 ] = 1 <br/>
             *      list [ 14 ] = 3 <br/>
             *      list [ -1 ] = 4 <br/>
             *      list [ -2 ] = 3 <br/>
             *      list [ -3 ] = 2 <br/>
             *      list [ -4 ] = 1 <br/>
             *      list [ -7 ] = 2 <br/>
             */
            auto operator [] (
                    Index index
            ) const noexcept (false) -> ElementType const &;

        public:
            /**
             * @brief Function used to remove the first element of the list
             * @exceptsafe
             */
            virtual auto popFront () noexcept -> void = 0;

        public:
            /**
             * @brief Function used to remove the last element of the list
             * @exceptsafe
             */
            virtual auto popBack () noexcept -> void = 0;

        protected:
            /**
             * @brief Function used to create and return the storage space for a new element, at the front of the list.
             *      Used in pushFront
             * @exceptsafe
             * @return ElementType ptr ref = Reference to the address value to allocate the new element at
             */
            virtual auto pNewFront () noexcept -> ElementType * & = 0;

        protected:
            /**
             * @brief Function used to create and return the storage space for a new element, at the back of the list.
             *      Used in pushBack
             * @exceptsafe
             * @return ElementType ptr ref = Reference to the address value to allocate the new element at
             */
            virtual auto pNewBack () noexcept -> ElementType * & = 0;

        protected:
            /**
             * @brief Function used to create and return the storage space for a new element, before the position indicated by a given iterator.
             *      Used in insertBefore
             * @param iterator : Iterator cref = the iterator indicating the position to insert before
             * @exceptsafe
             * @return ElementType ptr ref = Reference to the address value to allocate the new element at
             */
            virtual auto pNewBefore (
                    Iterator const & iterator
            ) noexcept -> ElementType * & = 0;

        protected:
            /**
             * @brief Function used to create and return the storage space for a new element, after the position indicated by a given iterator.
             *      Used in insertAfter
             * @param iterator : Iterator cref = the iterator indicating the position to insert after
             * @exceptsafe
             * @return ElementType ptr ref = Reference to the address value to allocate the new element at
             */
            virtual auto pNewAfter (
                    Iterator const & iterator
            ) noexcept -> ElementType * & = 0;

        protected:
            /**
             * @brief Function used to create and return the storage space for a new element, before the position indicated by a given iterator.
             *      Used in insertBefore
             * @param iterator : ConstIterator cref = the iterator indicating the position to insert before
             * @exceptsafe
             * @return ElementType ptr ref = Reference to the address value to allocate the new element at
             */
            virtual auto pNewBefore (
                    ConstIterator const & iterator
            ) noexcept -> ElementType * & = 0;

        protected:
            /**
             * @brief Function used to create and return the storage space for a new element, after the position indicated by a given iterator.
             *      Used in insertAfter
             * @param iterator : ConstIterator cref = the iterator indicating the position to insert after
             * @exceptsafe
             * @return ElementType ptr ref = Reference to the address value to allocate the new element at
             */
            virtual auto pNewAfter (
                    ConstIterator const & iterator
            ) noexcept -> ElementType * & = 0;

        protected:
            /**
             * @brief Function used to create and return the storage space for a new element, before the position indicated by a given iterator.
             *      Used in insertBefore
             * @param iterator : ReverseIterator cref = the iterator indicating the position to insert before
             * @exceptsafe
             * @return ElementType ptr ref = Reference to the address value to allocate the new element at
             */
            virtual auto pNewBefore (
                    ReverseIterator const & iterator
            ) noexcept -> ElementType * & = 0;

        protected:
            /**
             * @brief Function used to create and return the storage space for a new element, after the position indicated by a given iterator.
             *      Used in insertAfter
             * @param iterator : ReverseIterator cref = the iterator indicating the position to insert after
             * @exceptsafe
             * @return ElementType ptr ref = Reference to the address value to allocate the new element at
             */
            virtual auto pNewAfter (
                    ReverseIterator const & iterator
            ) noexcept -> ElementType * & = 0;

        protected:
            /**
             * @brief Function used to create and return the storage space for a new element, before the position indicated by a given iterator.
             *      Used in insertBefore
             * @param iterator : ConstReverseIterator cref = the iterator indicating the position to insert before
             * @exceptsafe
             * @return ElementType ptr ref = Reference to the address value to allocate the new element at
             */
            virtual auto pNewBefore (
                    ConstReverseIterator const & iterator
            ) noexcept -> ElementType * & = 0;

        protected:
            /**
             * @brief Function used to create and return the storage space for a new element, after the position indicated by a given iterator.
             *      Used in insertAfter
             * @param iterator : ConstReverseIterator cref = the iterator indicating the position to insert after
             * @exceptsafe
             * @return ElementType ptr ref = Reference to the address value to allocate the new element at
             */
            virtual auto pNewAfter (
                    ConstReverseIterator const & iterator
            ) noexcept -> ElementType * & = 0;

        public:
            /**
             * @brief Function used to add an element at the front of the list via copy ( construction of new instance ). Only used if element is copyConstructible ( has copy ctor )
             * @tparam __VElementType alias for __ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param element : ElementType cref = Constant Reference to the element to copy and add into the collection
             * @exceptsafe if ElementType copy constructor is exceptsafe
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto pushFront (
                    ElementType const & element
            ) noexcept -> ElementType &;

        public:
            /**
             * @brief Function used to add an element at the front of the list via move ( moving of the received instance ). Only used if element is moveConstructible ( has move ctor )
             * @tparam __VElementType alias for __ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param element : ElementType mref = Move Reference to the element to move into the collection
             * @exceptsafe if ElementType move constructor is exceptsafe
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto pushFront (
                    ElementType && element
            ) noexcept -> ElementType &;

        public:
            /**
             * @brief Function used to add an element at the back of the list via copy ( construction of new instance ). Only used if element is copyConstructible ( has copy ctor )
             * @tparam __VElementType alias for __ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param element : ElementType cref = Constant Reference to the element to copy and add into the collection
             * @exceptsafe if ElementType copy constructor is exceptsafe
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto pushBack (
                    ElementType const & element
            ) noexcept -> ElementType &;

        public:
            /**
             * @brief Function used to add an element at the back of the list via move ( moving of the received instance ). Only used if element is moveConstructible ( has move ctor )
             * @tparam V alias for __ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param element : ElementType mref = Move Reference to the element to move into the collection
             * @exceptsafe if ElementType move constructor is exceptsafe
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto pushBack (
                    ElementType && element
            ) noexcept -> ElementType &;

        public:
            /**
             * @brief Function used to add an element before a given iterator's referenced element via copy ( creating a new instance ). Only used if element is copyConstructible ( has copy ctor )
             * @tparam __VElementType is an alias for __VElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : Iterator cref = Constant Reference to an iterator to place the element before
             * @param element : ElementType cref = Constant Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto insertBefore (
                    Iterator    const & iterator,
                    ElementType const & element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element before a given iterator's referenced element via move ( move of the given instance ) Only used if element is moveConstructible ( has move ctor )
             * @tparam __VElementType is an alias for __VElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : Iterator cref = Constant Reference to an iterator to place the element before
             * @param element : ElementType mref = Move Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto insertBefore (
                    Iterator    const & iterator,
                    ElementType      && element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element after a given iterator's referenced element via copy ( creating a new instance ). Only used if element is copyConstructible ( has copy ctor )
             * @tparam __VElementType is an alias for __ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : Iterator cref = Constant Reference to an iterator to place the element after
             * @param element : ElementType cref = Constant Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto insertAfter (
                    Iterator    const & iterator,
                    ElementType const & element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element after a given iterator's referenced element via move ( move of the given instance ) Only used if element is moveConstructible ( has move ctor )
             * @tparam __VElementType is an alias for __ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : Iterator cref = Constant Reference to an iterator to place the element after
             * @param element : ElementType mref = Move Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto insertAfter (
                    Iterator   const & iterator,
                    ElementType     && element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element before a given iterator's referenced element via copy ( creating a new instance ). Only used if element is copyConstructible ( has copy ctor )
             * @tparam __VElementType is an alias for __ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : ConstIterator cref = Constant Reference to an iterator to place the element before
             * @param element : ElementType cref = Constant Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto insertBefore (
                    ConstIterator   const & iterator,
                    ElementType     const & element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element before a given iterator's referenced element via move ( move of the given instance ) Only used if element is moveConstructible ( has move ctor )
             * @tparam __VElementType is an alias for __ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : ConstIterator cref = Constant Reference to an iterator to place the element before
             * @param element : ElementType mref = Move Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto insertBefore (
                    ConstIterator  const & iterator,
                    ElementType         && element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element after a given iterator's referenced element via copy ( creating a new instance ). Only used if element is copyConstructible ( has copy ctor )
             * @tparam __VElementType is an alias for __ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : ConstIterator cref = Constant Reference to an iterator to place the element after
             * @param element : ElementType cref = Constant Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto insertAfter (
                    ConstIterator   const & iterator,
                    ElementType     const & element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element after a given iterator's referenced element via move ( move of the given instance ) Only used if element is moveConstructible ( has move ctor )
             * @tparam __VElementType is an alias for __ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : ConstIterator cref = Constant Reference to an iterator to place the element after
             * @param element : ElementType mref = Move Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto insertAfter (
                    ConstIterator  const & iterator,
                    ElementType         && element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element before a given iterator's referenced element via copy ( creating a new instance ). Only used if element is copyConstructible ( has copy ctor )
             * @tparam __VElementType is an alias for __ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : ReverseIterator cref = Constant Reference to an iterator to place the element before
             * @param element : ElementType cref = Constant Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto insertBefore (
                    ReverseIterator const & iterator,
                    ElementType     const & element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element before a given iterator's referenced element via move ( move of the given instance ) Only used if element is moveConstructible ( has move ctor )
             * @tparam __VElementType is an alias for __ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : ReverseIterator cref = Constant Reference to an iterator to place the element before
             * @param element : ElementType mref = Move Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto insertBefore (
                    ReverseIterator const & iterator,
                    ElementType          && element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element after a given iterator's referenced element via copy ( creating a new instance ). Only used if element is copyConstructible ( has copy ctor )
             * @tparam __VElementType is an alias for __ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : ReverseIterator cref = Constant Reference to an iterator to place the element after
             * @param element : ElementType cref = Constant Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto insertAfter (
                    ReverseIterator const & iterator,
                    ElementType     const & element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element after a given iterator's referenced element via move ( move of the given instance ) Only used if element is moveConstructible ( has move ctor )
             * @tparam __VElementType is an alias for __ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : ReverseIterator cref = Constant Reference to an iterator to place the element after
             * @param element : ElementType mref = Move Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto insertAfter (
                    ReverseIterator const & iterator,
                    ElementType          && element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element before a given iterator's referenced element via copy ( creating a new instance ). Only used if element is copyConstructible ( has copy ctor )
             * @tparam __VElementType is an alias for __ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : ConstReverseIterator cref = Constant Reference to an iterator to place the element before
             * @param element : ElementType cref = Constant Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto insertBefore (
                    ConstReverseIterator    const & iterator,
                    ElementType             const & element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element before a given iterator's referenced element via move ( move of the given instance ) Only used if element is moveConstructible ( has move ctor )
             * @tparam __VElementType is an alias for __ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : ConstReverseIterator cref = Constant Reference to an iterator to place the element before
             * @param element : ElementType mref = Move Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto insertBefore (
                    ConstReverseIterator const & iterator,
                    ElementType               && element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element after a given iterator's referenced element via copy ( creating a new instance ). Only used if element is copyConstructible ( has copy ctor )
             * @tparam __VElementType is an alias for __ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : ConstReverseIterator cref = Constant Reference to an iterator to place the element after
             * @param element : ElementType cref = Constant Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto insertAfter (
                    ConstReverseIterator    const & iterator,
                    ElementType             const & element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element after a given iterator's referenced element via move ( move of the given instance ) Only used if element is moveConstructible ( has move ctor )
             * @tparam __VElementType is an alias for __ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : ConstReverseIterator cref = Constant Reference to an iterator to place the element after
             * @param element : ElementType mref = Move Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto insertAfter (
                    ConstReverseIterator const & iterator,
                    ElementType               && element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Alias for pushBack, function used to add an element at the back of the list via copy ( construction of new instance ). Only used if element is copyConstructible ( has copy ctor )
             * @tparam __VElementType alias for __ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param element : ElementType cref = Constant Reference to the element to copy and add into the collection
             * @exceptsafe if ElementType copy constructor is exceptsafe
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto append (
                    ElementType const & element
            ) noexcept -> ElementType &;

        public:
            /**
             * @brief Alias for pushBack, function used to add an element at the back of the list via move ( moving of the received instance ). Only used if element is moveConstructible ( has move ctor )
             * @tparam __VElementType alias for __ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param element : ElementType mref = Move Reference to the element to move into the collection
             * @exceptsafe if ElementType move constructor is exceptsafe
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto append (
                    ElementType && element
            ) noexcept -> ElementType &;

        public:
            /**
             * @brief Alias for pushFront, function used to add an element at the front of the list via copy ( construction of new instance ). Only used if element is copyConstructible ( has copy ctor )
             * @tparam __VElementType alias for __ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param element : ElementType cref = Constant Reference to the element to copy and add into the collection
             * @exceptsafe if ElementType copy constructor is exceptsafe
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto prepend (
                    ElementType const & element
            ) noexcept -> ElementType &;

        public:
            /**
             * @brief Alias for pushFront, function used to add an element at the front of the list via move ( moving of the received instance ). Only used if element is moveConstructible ( has move ctor )
             * @tparam __VElementType alias for __ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param element : ElementType mref = Move Reference to the element to move into the collection
             * @exceptsafe if ElementType move constructor is exceptsafe
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto prepend (
                    ElementType && element
            ) noexcept -> ElementType &;

        public:
            /**
             * @brief Function used to remove an element at a given index
             * @param index : Index = index of the element to remove
             * @exceptsafe
             * @return bool = true if removal was done, false otherwise
             */
            virtual auto removeAt (
                    Index index
            ) noexcept -> bool = 0;

        public:
            /**
             * @brief Function used to remove several elements located at the given indices
             * @param indices : Collection < Index > cref = Constant Reference to a collection of indices of the elements to remove
             * @exceptsafe
             * @return Size = the number of elements that were removed successfully
             */
            virtual auto removeAt (
                    Collection < Index > const & indices
            ) noexcept -> Size = 0;

        public:
            /**
             * @brief Function used to remove several elements located at the given indices
             * @param indices : InitializerList cref = Constant Reference to a collection of indices of the elements to remove
             * @exceptsafe
             * @return Size = the number of elements that were removed successfully
             */
            virtual auto removeAt (
                    std :: initializer_list < Index > const & indices
            ) noexcept -> Size = 0;

        public:
            /**
             * @brief Function used to remove an element identified by a given Iterator
             * @param iterator : Iterator cref = Constant Reference to the Iterator indicating the value to be removed
             * @exceptsafe
             * @return bool = true if removal was successful, false otherwise ( invalid iterator )
             */
            virtual auto remove (
                    Iterator const & iterator
            ) noexcept -> bool = 0;

        public:
            /**
             * @brief Function used to remove an element identified by a given Iterator
             * @param iterator : ConstIterator cref = Constant Reference to the Iterator indicating the value to be removed
             * @exceptsafe
             * @return bool = true if removal was successful, false otherwise ( invalid iterator )
             * @test tested in the class test
             */
            auto remove (
                    ConstIterator const & iterator
            ) noexcept -> bool override = 0;

        public:
            /**
             * @brief Function used to remove an element identified by a given Iterator
             * @param iterator : ReverseIterator cref = Constant Reference to the Reverse Iterator indicating the value to be removed
             * @exceptsafe
             * @return bool = true if removal was successful, false otherwise ( invalid iterator )
             */
            virtual auto remove (
                    ReverseIterator const & iterator
            ) noexcept -> bool = 0;

        public:
            /**
             * @brief Function used to remove an element identified by a given Iterator
             * @param iterator : ConstReverseIterator cref = Constant Reference to the Reverse Iterator indicating the value to be removed
             * @exceptsafe
             * @return bool = true if removal was successful, false otherwise ( invalid iterator )
             * @test tested in the class test
             */
            auto remove (
                    ConstReverseIterator const & iterator
            ) noexcept -> bool override = 0;


        protected:
            /**
             * @brief Function used to remove a batch of elements identified by a given array of Iterators
             * @param pIterators : Iterator cptr = Address to an array of Constant Iterator objects, indicating the elements to be removed
             * @param size : Size = the number of elements in the pIterators array
             * @exceptsafe
             * @return Size = number of elements that were successfully removed
             */
            virtual auto remove (
                    Iterator    const * pIterators,
                    Size                size
            ) noexcept -> Size = 0;

        protected:
            /**
             * @brief Function used to remove a batch of elements identified by a given array of Iterators
             * @param pIterators : ConstIterator cptr = Address to an array of Constant ConstIterator objects, indicating the elements to be removed
             * @param size : Size = the number of elements in the pIterators array
             * @exceptsafe
             * @return Size = number of elements that were successfully removed
             * @test tested in the class test
             */
            auto remove (
                    ConstIterator   const * pIterators,
                    Size                    size
            ) noexcept -> Size override = 0;

        protected:
            /**
             * @brief Function used to remove a batch of elements identified by a given array of Iterators
             * @param pIterators : ReverseIterator cptr = Address to an array of Constant ReverseIterator objects, indicating the elements to be removed
             * @param size : Size = the number of elements in the pIterators array
             * @exceptsafe
             * @return Size = number of elements that were successfully removed
             */
            virtual auto remove (
                    ReverseIterator const * pIterators,
                    Size                    size
            ) noexcept -> Size = 0;

        protected:
            /**
             * @brief Function used to remove a batch of elements identified by a given array of Iterators
             * @param pIterators : ConstReverseIterator cptr = Address to an array of Constant ConstReverseIterator objects, indicating the elements to be removed
             * @param size : Size = the number of elements in the pIterators array
             * @exceptsafe
             * @return Size = number of elements that were successfully removed
             * @test tested in the class test
             */
            auto remove (
                    ConstReverseIterator    const * pIterators,
                    Size                            size
            ) noexcept -> Size override = 0;

        public:
            /**
             * @brief Function used to sort the current List based on a given comparator function
             * @tparam __ComparatorFunction is the type of the comparator function, its signature must be compatible with bool ( Decay < ElementType >, Decay < ElementType > )
             * @param comparatorFunction : ComparatorFunction const & = Constant Reference to the comparator callable object / function
             * @exceptsafe if ComparatorFunction is exceptsafe
             */
            template < typename __ComparatorFunction = decltype ( & predicates :: lessThan < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
            auto sort (
                    __ComparatorFunction const & comparatorFunction = & predicates :: lessThan < ElementType >
            ) noexcept ( noexcept ( comparatorFunction ( meta :: valueOf < ElementType > (), meta :: valueOf < ElementType > () ) ) ) -> void;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replace (
                    Size                count,
                    ElementType const & what,
                    ElementType const & with
            ) noexcept -> Size;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceAll (
                    ElementType const & what,
                    ElementType const & with
            ) noexcept -> Size;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceFirst (
                    ElementType const & what,
                    ElementType const & with
            ) noexcept -> bool;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isMoveAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceFirst (
                    ElementType const & what,
                    ElementType      && with
            ) noexcept -> bool;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceLast (
                    ElementType const & what,
                    ElementType const & with
            ) noexcept -> bool;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isMoveAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceLast (
                    ElementType const & what,
                    ElementType      && with
            ) noexcept -> bool;


        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceOf (
                    Size                                count,
                    Collection < ElementType >  const & of,
                    ElementType                 const & with
            ) noexcept -> Size;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceAllOf (
                    Collection < ElementType >  const & of,
                    ElementType                 const & with
            ) noexcept -> Size;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceFirstOf (
                    Collection < ElementType >  const & of,
                    ElementType                 const & with
            ) noexcept -> bool;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isMoveAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceFirstOf (
                    Collection < ElementType >  const & of,
                    ElementType                      && with
            ) noexcept -> bool;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceLastOf (
                    Collection < ElementType >  const & of,
                    ElementType                 const & with
            ) noexcept -> bool;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isMoveAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceLastOf (
                    Collection < ElementType >  const & of,
                    ElementType                      && with
            ) noexcept -> bool;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceNotOf (
                    Size                                count,
                    Collection < ElementType >  const & of,
                    ElementType                 const & with
            ) noexcept -> Size;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceAllNotOf (
                    Collection < ElementType >  const & of,
                    ElementType                 const & with
            ) noexcept -> Size;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceFirstNotOf (
                    Collection < ElementType >  const & of,
                    ElementType                 const & with
            ) noexcept -> bool;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isMoveAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceFirstNotOf (
                    Collection < ElementType >  const & of,
                    ElementType                      && with
            ) noexcept -> bool;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceLastNotOf (
                    Collection < ElementType >  const & of,
                    ElementType                 const & with
            ) noexcept -> bool;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isMoveAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceLastNotOf (
                    Collection < ElementType >  const & of,
                    ElementType                      && with
            ) noexcept -> bool;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceOf (
                    Size                        count,
                    InitializerList     const & of,
                    ElementType         const & with
            ) noexcept -> Size;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceAllOf (
                    InitializerList     const & of,
                    ElementType         const & with
            ) noexcept -> Size;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceFirstOf (
                    InitializerList     const & of,
                    ElementType         const & with
            ) noexcept -> bool;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isMoveAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceFirstOf (
                    InitializerList     const & of,
                    ElementType              && with
            ) noexcept -> bool;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceLastOf (
                    InitializerList     const & of,
                    ElementType         const & with
            ) noexcept -> bool;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isMoveAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceLastOf (
                    InitializerList     const & of,
                    ElementType              && with
            ) noexcept -> bool;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceNotOf (
                    Size                        count,
                    InitializerList     const & of,
                    ElementType         const & with
            ) noexcept -> Size;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceAllNotOf (
                    InitializerList     const & of,
                    ElementType         const & with
            ) noexcept -> Size;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceFirstNotOf (
                    InitializerList     const & of,
                    ElementType         const & with
            ) noexcept -> bool;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isMoveAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceFirstNotOf (
                    InitializerList     const & of,
                    ElementType              && with
            ) noexcept -> bool;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceLastNotOf (
                    InitializerList     const & of,
                    ElementType         const & with
            ) noexcept -> bool;

        public:
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isMoveAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceLastNotOf (
                    InitializerList     const & of,
                    ElementType              && with
            ) noexcept -> bool;

        public:
            template < typename __Predicate, typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replace (
                    Size                count,
                    __Predicate const & predicate,
                    ElementType const & with
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> Size;

        public:
            template < typename __Predicate, typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceAll (
                    __Predicate const & predicate,
                    ElementType const & with
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> Size;

        public:
            template < typename __Predicate, typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceFirst (
                    __Predicate const & predicate,
                    ElementType const & with
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

        public:
            template < typename __Predicate, typename __VElementType = __ElementType, meta :: EnableIf < meta :: isMoveAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceFirst (
                    __Predicate const & predicate,
                    ElementType      && with
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

        public:
            template < typename __Predicate, typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceLast (
                    __Predicate const & predicate,
                    ElementType const & with
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

        public:
            template < typename __Predicate, typename __VElementType = __ElementType, meta :: EnableIf < meta :: isMoveAssignable < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto replaceLast (
                    __Predicate const & predicate,
                    ElementType      && with
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

        public:
            template < typename __Predicate, typename __Supplier > // NOLINT(bugprone-reserved-identifier)
            auto replace (
                    Size                count,
                    __Predicate const & predicate,
                    __Supplier  const & supplier
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( meta :: referenceOf < ElementType > () ) ) ) -> Size;

        public:
            template < typename __Predicate, typename __Supplier > // NOLINT(bugprone-reserved-identifier)
            auto replaceAll (
                    __Predicate const & predicate,
                    __Supplier  const & supplier
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( meta :: referenceOf < ElementType > () ) ) ) -> Size;

        public:
            template < typename __Predicate, typename __Supplier > // NOLINT(bugprone-reserved-identifier)
            auto replaceFirst (
                    __Predicate const & predicate,
                    __Supplier  const & supplier
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

        public:
            template < typename __Predicate, typename __Supplier > // NOLINT(bugprone-reserved-identifier)
            auto replaceLast (
                    __Predicate const & predicate,
                    __Supplier  const & supplier
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

        public:
            virtual auto front () noexcept (false) -> ElementType & = 0;

        public:
            virtual auto front () const noexcept (false) -> ElementType const & = 0;

        public:
            virtual auto back () noexcept (false) -> ElementType & = 0;

        public:
            virtual auto back () const noexcept (false) -> ElementType const & = 0;

        public:
            virtual auto makeUnique () noexcept -> void = 0;

        public:
            __CDS_NoDiscard auto toString () const noexcept -> String override;


        public:
            /**
             * @brief Function used to obtain a maximum number of indices of a given element and store them into a given list
             * @tparam __CollectionType is the type of the list to store the indices into
             * @param count : Size = maximum number of indices to obtain
             * @param storeIn : __CollectionType ref = Reference to the List to store the indices into
             * @param element : ElementType cref = Constant Reference to the Element to acquire the indices for
             * @exceptsafe
             * @return __CollectionType ref = Reference to the list passed in the 'storeIn' parameter
             */
            template < typename __CollectionType, meta :: EnableIf < meta :: isDerivedFrom < __CollectionType, Collection < Index > > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto indices (
                    Size                  count,
                    __CollectionType    & storeIn,
                    ElementType   const & element
            ) const noexcept -> __CollectionType &;

        public:
            /**
             * @brief Function used to obtain the indices of a given element
             * @tparam __CollectionType is the type of the list to store the indices into
             * @param count : Size = maximum number of indices to obtain
             * @param element : ElementType cref = Constant Reference to the Element to acquire the indices for
             * @exceptsafe
             * @return __CollectionType = List containing the requested indices
             */
            template < typename __CollectionType, meta :: EnableIf < meta :: isDerivedFrom < __CollectionType, Collection < Index > > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto indices (
                    Size                count,
                    ElementType const & element
            ) const noexcept -> __CollectionType;

        public:
            /**
             * @brief Function used to obtain the indices of a given element
             * @tparam __CollectionType is the type of the list to store the indices into
             * @param count : Size = maximum number of indices to obtain
             * @param element : ElementType cref = Constant Reference to the Element to acquire the indices for
             * @exceptsafe
             * @return __CollectionType = List containing the requested indices
             */
            template < template < typename ... > class __CollectionType, meta :: EnableIf < meta :: isDerivedFrom < __CollectionType < Index >, Collection < Index > > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto indices (
                    Size                count,
                    ElementType const & element
            ) const noexcept -> __CollectionType < Index >;

        public:
            auto firstIndex (
                    ElementType const & element
            ) const noexcept -> Index;

        public:
            auto lastIndex (
                    ElementType const & element
            ) const noexcept -> Index;

        public:
            /**
             * @brief Function used to obtain the indices of a given element and store them into a given list
             * @tparam __CollectionType is the type of the list to store the indices into
             * @param storeIn : __CollectionType ref = Reference to the List to store the indices into
             * @param element : ElementType cref = Constant Reference to the Element to acquire the indices for
             * @exceptsafe
             * @return __CollectionType ref = Reference to the list passed in the 'storeIn' parameter
             */
            template < typename __CollectionType, meta :: EnableIf < meta :: isDerivedFrom < __CollectionType, Collection < Index > > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto allIndices (
                    __CollectionType    & storeIn,
                    ElementType   const & element
            ) const noexcept -> __CollectionType &;

        public:
            /**
             * @brief Function used to obtain the indices of a given element
             * @tparam __CollectionType is the type of the list to store the indices into
             * @param element : ElementType cref = Constant Reference to the Element to acquire the indices for
             * @exceptsafe
             * @return __CollectionType = List containing the requested indices
             */
            template < typename __CollectionType, meta :: EnableIf < meta :: isDerivedFrom < __CollectionType, Collection < Index > > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto allIndices (
                    ElementType const & element
            ) const noexcept -> __CollectionType;

        public:
            /**
             * @brief Function used to obtain the indices of a given element
             * @tparam __CollectionType is the type of the list to store the indices into
             * @param element : ElementType cref = Constant Reference to the Element to acquire the indices for
             * @exceptsafe
             * @return __CollectionType = List containing the requested indices
             */
            template < template < typename ... > class __CollectionType, meta :: EnableIf < meta :: isDerivedFrom < __CollectionType < Index >, Collection < Index > > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto allIndices (
                    ElementType const & element
            ) const noexcept -> __CollectionType < Index >;

        public:
            /**
             * @brief Function used to obtain the indices of the elements that validate a given predicate
             * @tparam __Predicate is the type of the predicate object, it must be a valid callable type object, with a signature compatible with
             *      bool ( Decay < ElementType > )
             * @tparam __CollectionType is the type of the list to store the indices into
             * @param count : Size = maximum number of indices to obtain
             * @param storeIn : __CollectionType ref = Reference to the List to store the indices into
             * @param predicate : Predicate cref = Constant Reference to the predicate callable object
             * @exceptsafe
             * @return __CollectionType ref = Reference to the list passed in the 'storeIn' parameter
             */
            template < typename __Predicate, typename __CollectionType, meta :: EnableIf < meta :: isDerivedFrom < __CollectionType, Collection < Index > > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto indices (
                    Size                count,
                    __CollectionType  & storeIn,
                    __Predicate const & predicate
            ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType &;

        public:
            /**
             * @brief Function used to obtain the indices of the elements that validate a given predicate
             * @tparam __Predicate is the type of the predicate object, it must be a valid callable type object, with a signature compatible with
             *      bool ( Decay < ElementType > )
             * @tparam __CollectionType is the type of the list to store the indices into
             * @param count : Size = maximum number of indices to obtain
             * @param predicate : Predicate cref = Constant Reference to the predicate callable object
             * @exceptsafe
             * @return __CollectionType = List containing the requested indices
             */
            template < typename __Predicate, typename __CollectionType, meta :: EnableIf < meta :: isDerivedFrom < __CollectionType, Collection < Index > > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto indices (
                    Size                count,
                    __Predicate const & predicate
            ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType;

        public:
            /**
             * @brief Function used to obtain the indices of the elements that validate a given predicate
             * @tparam __Predicate is the type of the predicate object, it must be a valid callable type object, with a signature compatible with
             *      bool ( Decay < ElementType > )
             * @tparam __CollectionType is the type of the list to store the indices into
             * @param count : Size = maximum number of indices to obtain
             * @param predicate : Predicate cref = Constant Reference to the predicate callable object
             * @exceptsafe
             * @return __CollectionType = List containing the requested indices
             */
            template < typename __Predicate, template < typename ... > class __CollectionType, meta :: EnableIf < meta :: isDerivedFrom < __CollectionType < Index >, Collection < Index > > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto indices (
                    Size                count,
                    __Predicate const & predicate
            ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType < Index >;

        public:
            template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            auto firstIndex (
                    __Predicate const & predicate
            ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> Index;

        public:
            template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            auto lastIndex (
                    __Predicate const & predicate
            ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> Index;

        public:
            /**
             * @brief Function used to obtain the indices of the elements that validate a given predicate
             * @tparam __Predicate is the type of the predicate object, it must be a valid callable type object, with a signature compatible with
             *      bool ( Decay < ElementType > )
             * @tparam __CollectionType is the type of the list to store the indices into
             * @param storeIn : __CollectionType ref = Reference to the List to store the indices into
             * @param predicate : Predicate cref = Constant Reference to the predicate callable object
             * @exceptsafe
             * @return __CollectionType ref = Reference to the list passed in the 'storeIn' parameter
             */
            template < typename __Predicate, typename __CollectionType, meta :: EnableIf < meta :: isDerivedFrom < __CollectionType, Collection < Index > > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto allIndices (
                    __CollectionType          & storeIn,
                    __Predicate const & predicate
            ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType &;

        public:
            /**
             * @brief Function used to obtain the indices of the elements that validate a given predicate
             * @tparam __Predicate is the type of the predicate object, it must be a valid callable type object, with a signature compatible with
             *      bool ( Decay < ElementType > )
             * @tparam __CollectionType is the type of the list to store the indices into
             * @param predicate : Predicate cref = Constant Reference to the predicate callable object
             * @exceptsafe
             * @return __CollectionType = List containing the requested indices
             */
            template < typename __Predicate, template < typename ... > class __CollectionType, meta :: EnableIf < meta :: isDerivedFrom < __CollectionType < Index >, Collection < Index > > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto allIndices (
                    __Predicate const & predicate
            ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType < Index >;

        public:
            /**
             * @brief Function used to obtain the indices of the elements that validate a given predicate
             * @tparam __Predicate is the type of the predicate object, it must be a valid callable type object, with a signature compatible with
             *      bool ( Decay < ElementType > )
             * @tparam __CollectionType is the type of the list to store the indices into
             * @param predicate : Predicate cref = Constant Reference to the predicate callable object
             * @exceptsafe
             * @return __CollectionType = List containing the requested indices
             */
            template < typename __Predicate, typename __CollectionType, meta :: EnableIf < meta :: isDerivedFrom < __CollectionType, Collection < Index > > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto allIndices (
                    __Predicate const & predicate
            ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType;

        public:
            /**
             * @brief Function used to populate a given Collection of Iterators, 'storeIn', with maximum 'maxCount' elements, pointing to the values matching the comparison to the given 'element' value
             * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
             * @param maxCount : Size = maximum number of iterators to add to the storeIn object
             * @param element : ElementType cref = Constant Reference to the element to compare the collection's elements to
             * @param storeIn : __CollectionType < Collection < ElementType > :: Iterator > ref = Reference to the collection of iterators to add the found iterators to
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: Iterator > ref = Reference to the given collection inside the 'storeIn' parameter
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto find (
                    Size                                        maxCount,
                    ElementType                         const & element,
                    __CollectionType < Iterator >               & storeIn
            ) noexcept -> __CollectionType < Iterator > &;

        public:
            /**
             * @brief Function used to return a Collection non-abstract derived type of Iterators with maximum 'maxCount' elements, pointing to the values matching the comparison to the given 'element' value
             * @tparam __CollectionType the type of the Collection to be returned. Constraint : CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
             * @param maxCount : Size = maximum number of iterators to add to the returned object
             * @param element : ElementType cref = Constant Reference to the element to compare the collection's elements to
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: Iterator > = Newly created object containing the requested Iterators
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto find (
                    Size                maxCount,
                    ElementType const & element
            ) noexcept -> __CollectionType < Iterator >;

        public:
            /**
             * @brief Function used to return the ConstIterator matching the first value that is equal to the given 'element' value
             * @param element : ElementType cref = Constant Reference to an element to compare the collection's elements to
             * @exceptsafe
             * @return Iterator = iterator matching the first value equal to the given 'element' value, caller.end() if no value matches
             * @test tested in base class test
             */
            auto findFirst (
                    ElementType const & element
            ) noexcept -> Iterator;

        public:
            /**
             * @brief Function used to return the ConstIterator matching the last value that is equal to the given 'element' value
             * @param element : ElementType cref = Constant Reference to an element to compare the collection's elements to
             * @exceptsafe
             * @return Iterator = iterator matching the last value equal to the given 'element' value, caller.end() if no value matches
             * @test tested in base class test
             */
            auto findLast (
                    ElementType const & element
            ) noexcept -> Iterator;

        public:
            /**
             * @brief Function used to populate a given Collection of Iterators, 'storeIn', with all the iterators pointing to the values matching the comparison to the given 'element' value
             * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
             * @param element : ElementType cref = Constant Reference to the element to compare the collection's elements to
             * @param storeIn : __CollectionType < Collection < ElementType > :: Iterator > ref = Reference to the collection of iterators to add the found iterators to
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: Iterator > ref = Reference to the given collection inside the 'storeIn' parameter
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findAll (
                    ElementType                         const & element,
                    __CollectionType < Iterator >               & storeIn
            ) noexcept -> __CollectionType < Iterator > &;

        public:
            /**
             * @brief Function used to return a Collection non-abstract derived type of Iterators with all the iterators pointing to the values matching the comparison to the given 'element' value
             * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
             * @param element : ElementType cref = Constant Reference to the element to compare the collection's elements to
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: Iterator > = Newly created object containing the requested Iterators
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findAll (
                    ElementType const & element
            ) noexcept -> __CollectionType < Iterator >;

        public:
            /**
             * @brief Function used to populate a given Collection of Iterators, 'storeIn', with maximum 'maxCount' elements, pointing to the values that are also found in the 'elements' collection
             * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
             * @param maxCount : Size = maximum number of iterators to add to the storeIn object
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the contains condition for
             * @param storeIn : __CollectionType < Collection < ElementType > :: Iterator > ref = Reference to the collection of iterators to add the found iterators to
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: Iterator > ref = Reference to the given collection inside the 'storeIn' parameter
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findOf (
                    Size                                        maxCount,
                    Collection < ElementType >          const & elements,
                    __CollectionType < Iterator >            & storeIn
            ) noexcept -> __CollectionType < Iterator > &;

        public:
            /**
             * @brief Function used to return a Collection non-abstract derived type of Iterators with maximum 'maxCount' elements, pointing to the values that are also found in the 'elements' collection
             * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
             * @param maxCount : Size = maximum number of iterators to add to the returned object
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the contains condition for
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: Iterator > = Newly created object containing the requested Iterators
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findOf (
                    Size                                maxCount,
                    Collection < ElementType >  const & elements
            ) noexcept -> __CollectionType < Iterator >;

        public:
            /**
             * @brief Function used to return the ConstIterator matching the first value that is also found in the 'elements' collection
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the contains condition for
             * @exceptsafe
             * @return Iterator = iterator matching the first value also found in the 'elements' collection, caller.end() if no value matches
             * @test tested in base class test
             */
            auto findFirstOf (
                    Collection < ElementType > const & elements
            ) noexcept -> Iterator;

        public:
            /**
             * @brief Function used to return the ConstIterator matching the last value that is also found in the 'elements' collection
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the contains condition for
             * @exceptsafe
             * @return Iterator = iterator matching the last value also found in the 'elements' collection, caller.end() if no value matches
             * @test tested in base class test
             */
            auto findLastOf (
                    Collection < ElementType > const & elements
            ) noexcept -> Iterator;

        public:
            /**
             * @brief Function used to populate a given Collection of Iterators, 'storeIn', with all the iterators pointing to the values that are also found in the 'elements' collection
             * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the contains condition for
             * @param storeIn : __CollectionType < Collection < ElementType > :: Iterator > ref = Reference to the collection of iterators to add the found iterators to
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: Iterator > ref = Reference to the given collection inside the 'storeIn' parameter
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findAllOf (
                    Collection < ElementType >          const & elements,
                    __CollectionType < Iterator >             & storeIn
            ) noexcept -> __CollectionType < Iterator > &;

        public:
            /**
             * @brief Function used to return a Collection non-abstract derived type of Iterators with all the iterators pointing to the values that are also found in the 'elements' collection
             * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the contains condition for
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: Iterator > = Newly created object containing the requested Iterators
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findAllOf (
                    Collection < ElementType > const & elements
            ) noexcept -> __CollectionType < Iterator >;

        public:
            /**
             * @brief Function used to populate a given Collection of Iterators, 'storeIn', with maximum 'maxCount' elements, pointing to the values that are not found in the 'elements' collection
             * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
             * @param maxCount : Size = maximum number of iterators to add to the storeIn object
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the not contains condition for
             * @param storeIn : __CollectionType < Collection < ElementType > :: Iterator > ref = Reference to the collection of iterators to add the found iterators to
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: Iterator > ref = Reference to the given collection inside the 'storeIn' parameter
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findNotOf (
                    Size                                        maxCount,
                    Collection < ElementType >          const & elements,
                    __CollectionType < Iterator >             & storeIn
            ) noexcept -> __CollectionType < Iterator > &;

        public:
            /**
             * @brief Function used to return a Collection non-abstract derived type of Iterators with maximum 'maxCount' elements, pointing to the values that are not found in the 'elements' collection
             * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
             * @param maxCount : Size = maximum number of iterators to add to the returned object
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the not contains condition for
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: Iterator > = Newly created object containing the requested Iterators
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findNotOf (
                    Size                                maxCount,
                    Collection < ElementType >  const & elements
            ) noexcept -> __CollectionType < Iterator >;

        public:
            /**
             * @brief Function used to return the ConstIterator matching the first value that is not found in the 'elements' collection
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the not contains condition for
             * @exceptsafe
             * @return Iterator = iterator matching the first value not found in the 'elements' collection, caller.end() if no value matches
             * @test tested in base class test
             */
            auto findFirstNotOf (
                    Collection < ElementType > const & elements
            ) noexcept -> Iterator;

        public:
            /**
             * @brief Function used to return the ConstIterator matching the last value that is not found in the 'elements' collection
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the not contains condition for
             * @exceptsafe
             * @return Iterator = iterator matching the last value not found in the 'elements' collection, caller.end() if no value matches
             * @test tested in base class test
             */
            auto findLastNotOf (
                    Collection < ElementType > const & elements
            ) noexcept -> Iterator;

        public:
            /**
             * @brief Function used to populate a given Collection of Iterators, 'storeIn', with all the iterators pointing to the values that are not found in the 'elements' collection
             * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the not contains condition for
             * @param storeIn : __CollectionType < Collection < ElementType > :: Iterator > ref = Reference to the collection of iterators to add the found iterators to
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: Iterator > ref = Reference to the given collection inside the 'storeIn' parameter
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findAllNotOf (
                    Collection < ElementType >          const & elements,
                    __CollectionType < Iterator >             & storeIn
            ) noexcept -> __CollectionType < Iterator > &;

        public:
            /**
             * @brief Function used to return a Collection non-abstract derived type of Iterators with all the iterators pointing to the values that are not found in the 'elements' collection
             * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the not contains condition for
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: Iterator > = Newly created object containing the requested Iterators
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findAllNotOf (
                    Collection < ElementType > const & elements
            ) noexcept -> __CollectionType < Iterator >;

        public:
            /**
             * @brief Function used to populate a given Collection of Iterators, 'storeIn', with maximum 'maxCount' elements, pointing to the values that are also found in the 'elements' InitializerList
             * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
             * @param maxCount : Size = maximum number of iterators to add to the storeIn object
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
             * @param storeIn : __CollectionType < Collection < ElementType > :: Iterator > ref = Reference to the collection of iterators to add the found iterators to
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: Iterator > ref = Reference to the given collection inside the 'storeIn' parameter
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findOf (
                    Size                                        maxCount,
                    InitializerList                     const & elements,
                    __CollectionType < Iterator >             & storeIn
            ) noexcept -> __CollectionType < Iterator > &;

        public:
            /**
             * @brief Function used to return a Collection non-abstract derived type of Iterators with maximum 'maxCount' elements, pointing to the values that are also found in the 'elements' InitializerList
             * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
             * @param maxCount : Size = maximum number of iterators to add to the returned object
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: Iterator > = Newly created object containing the requested Iterators
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findOf (
                    Size                    maxCount,
                    InitializerList const & elements
            ) noexcept -> __CollectionType < Iterator >;

        public:
            /**
             * @brief Function used to return the ConstIterator matching the first value that is also found in the 'elements' InitializerList
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
             * @exceptsafe
             * @return Iterator = iterator matching the first value also found in the 'elements' list, caller.end() if no value matches
             * @test tested in base class test
             */
            auto findFirstOf (
                    InitializerList const & elements
            ) noexcept -> Iterator;

        public:
            /**
             * @brief Function used to return the ConstIterator matching the last value that is also found in the 'elements' InitializerList
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
             * @exceptsafe
             * @return Iterator = iterator matching the last value also found in the 'elements' list, caller.end() if no value matches
             * @test tested in base class test
             */
            auto findLastOf (
                    InitializerList const & elements
            ) noexcept -> Iterator;

        public:
            /**
             * @brief Function used to populate a given Collection of Iterators, 'storeIn', with all the iterators pointing to the values that are also found in the 'elements' InitializerList
             * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
             * @param storeIn : __CollectionType < Collection < ElementType > :: Iterator > ref = Reference to the collection of iterators to add the found iterators to
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: Iterator > ref = Reference to the given collection inside the 'storeIn' parameter
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findAllOf (
                    InitializerList                     const & elements,
                    __CollectionType < Iterator >             & storeIn
            ) noexcept -> __CollectionType < Iterator > &;

        public:
            /**
             * @brief Function used to return a Collection non-abstract derived type of Iterators with all the iterators pointing to the values that are also found in the 'elements' InitializerList
             * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: Iterator > = Newly created object containing the requested Iterators
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findAllOf (
                    InitializerList const & elements
            ) noexcept -> __CollectionType < Iterator >;

        public:
            /**
             * @brief Function used to populate a given Collection of Iterators, 'storeIn', with maximum 'maxCount' elements, pointing to the values that are not found in the 'elements' InitializerList
             * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
             * @param maxCount : Size = maximum number of iterators to add to the storeIn object
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
             * @param storeIn : __CollectionType < Collection < ElementType > :: Iterator > ref = Reference to the collection of iterators to add the found iterators to
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: Iterator > ref = Reference to the given collection inside the 'storeIn' parameter
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findNotOf (
                    Size                                        maxCount,
                    InitializerList                     const & elements,
                    __CollectionType < Iterator >             & storeIn
            ) noexcept -> __CollectionType < Iterator > &;

        public:
            /**
             * @brief Function used to return a Collection non-abstract derived type of Iterators with maximum 'maxCount' elements, pointing to the values that are not found in the 'elements' InitializerList
             * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
             * @param maxCount : Size = maximum number of iterators to add to the returned object
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: Iterator > = Newly created object containing the requested Iterators
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findNotOf (
                    Size                    maxCount,
                    InitializerList const & elements
            ) noexcept -> __CollectionType < Iterator >;

        public:
            /**
             * @brief Function used to return the ConstIterator matching the first value that is not found in the 'elements' InitializerList
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
             * @exceptsafe
             * @return Iterator = iterator matching the first value not found in the 'elements' list, caller.end() if no value matches
             * @test tested in base class test
             */
            auto findFirstNotOf (
                    InitializerList const & elements
            ) noexcept -> Iterator;

        public:
            /**
             * @brief Function used to return the ConstIterator matching the last value that is not found in the 'elements' InitializerList
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
             * @exceptsafe
             * @return Iterator = iterator matching the last value not found in the 'elements' list, caller.end() if no value matches
             * @test tested in base class test
             */
            auto findLastNotOf (
                    InitializerList const & elements
            ) noexcept -> Iterator;

        public:
            /**
             * @brief Function used to populate a given Collection of Iterators, 'storeIn', with all the iterators pointing to the values that are not found in the 'elements' InitializerList
             * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
             * @param storeIn : __CollectionType < Collection < ElementType > :: Iterator > ref = Reference to the collection of iterators to add the found iterators to
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: Iterator > ref = Reference to the given collection inside the 'storeIn' parameter
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findAllNotOf (
                    InitializerList                     const & elements,
                    __CollectionType < Iterator >             & storeIn
            ) noexcept -> __CollectionType < Iterator > &;

        public:
            /**
             * @brief Function used to return a Collection non-abstract derived type of Iterators with all the iterators pointing to the values that are not found in the 'elements' InitializerList
             * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: Iterator > = Newly created object containing the requested Iterators
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findAllNotOf (
                    InitializerList const & elements
            ) noexcept -> __CollectionType < Iterator >;

        public:
            /**
             * @brief Function used to populate a given Collection derived type of Iterators, with a maximum number of 'maxCount' iterators, pointing to the first or all the elements in the collection that are validated by a given predicate
             * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
             * @param maxCount : Size = maximum number of iterators to add to the storeIn object
             * @param predicate : __Predicate cref = Constant Reference to the callable predicate object to pass each element to
             * @param storeIn : __CollectionType < Collection < ElementType > :: Iterator > ref = Reference to the collection of iterators to add the found iterators to
             * @exceptsafe if __Predicate is exceptsafe
             * @return Collection < Collection < ElementType > :: Iterator > ref = Reference to the given collection inside the 'storeIn' parameter
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType, typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            auto find (
                    Size                                        maxCount,
                    __Predicate                         const & predicate,
                    __CollectionType < Iterator >             & storeIn
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> __CollectionType < Iterator > &;

        public:
            /**
             * @brief Function used to return a Collection non-abstract derived type of Iterators, with a maximum number of 'maxCount' iterators, pointing to the first or all the elements in the collection that are validated by a given predicate
             * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
             * @param maxCount : Size = maximum number of iterators to add to the returned object
             * @param predicate : __Predicate cref = Constant Reference to the callable predicate object to pass each element to
             * @exceptsafe if __Predicate is exceptsafe
             * @return Collection < Collection < ElementType > :: Iterator > = Newly created object containing the requested Iterators
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType, typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            auto find (
                    Size                maxCount,
                    __Predicate const & predicate
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> __CollectionType < Iterator >;

        public:
            /**
             * @brief Function used to return an iterator to the first element validated by the given predicate
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
             * @param predicate : __Predicate cref = Constant Reference to the callable predicate object to pass each element to
             * @exceptsafe if __Predicate is exceptsafe
             * @return Collection < ElementType > :: Iterator = Iterator to the first element validated by the given predicate, caller.end() if none exist
             * @test tested in base class test
             */
            template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            auto findFirst (
                    __Predicate const & predicate
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> Iterator;

        public:
            /**
             * @brief Function used to return an iterator to the last element validated by the given predicate
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
             * @param predicate : __Predicate cref = Constant Reference to the callable predicate object to pass each element to
             * @exceptsafe if __Predicate is exceptsafe
             * @return Collection < ElementType > :: Iterator = Iterator to the last element validated by the given predicate, caller.end() if none exist
             * @test tested in base class test
             */
            template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            auto findLast (
                    __Predicate const & predicate
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> Iterator;

        public:
            /**
             * @brief Function used to populate a given Collection derived type of Iterators with all iterators pointing to the first or all the elements in the collection that are validated by a given predicate
             * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
             * @param predicate : __Predicate cref = Constant Reference to the callable predicate object to pass each element to
             * @param storeIn : __CollectionType < Collection < ElementType > :: Iterator > ref = Reference to the collection of iterators to add the found iterators to
             * @exceptsafe if __Predicate is exceptsafe
             * @return Collection < Collection < ElementType > :: Iterator > ref = Reference to the given collection inside the 'storeIn' parameter
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType, typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            auto findAll (
                    __Predicate                           const & predicate,
                    __CollectionType < Iterator >               & storeIn
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> __CollectionType < Iterator > &;

        public:
            /**
             * @brief Function used to return a Collection non-abstract derived type of Iterators with all the iterators pointing to the first or all the elements in the collection that are validated by a given predicate
             * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
             * @param predicate : __Predicate cref = Constant Reference to the callable predicate object to pass each element to
             * @exceptsafe if __Predicate is exceptsafe
             * @return Collection < Collection < ElementType > :: Iterator > = Newly created object containing the requested Iterators
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType, typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            auto findAll (
                    __Predicate const & predicate
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> __CollectionType < Iterator >;

        public:
            using Collection < __ElementType > :: find;
        public:
            using Collection < __ElementType > :: findFirst;
        public:
            using Collection < __ElementType > :: findLast;
        public:
            using Collection < __ElementType > :: findAll;
        public:
            using Collection < __ElementType > :: findOf;
        public:
            using Collection < __ElementType > :: findFirstOf;
        public:
            using Collection < __ElementType > :: findLastOf;
        public:
            using Collection < __ElementType > :: findAllOf;
        public:
            using Collection < __ElementType > :: findNotOf;
        public:
            using Collection < __ElementType > :: findFirstNotOf;
        public:
            using Collection < __ElementType > :: findLastNotOf;
        public:
            using Collection < __ElementType > :: findAllNotOf;

        public:
            template < typename __Action > // NOLINT(bugprone-reserved-identifier)
            auto forEach (
                    __Action const & action
            ) noexcept ( noexcept ( action ( meta :: referenceOf < ElementType > () ) ) ) -> void;

        public:
            template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
            auto some (
                    Size                count,
                    __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

        public:
            template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
            auto atLeast (
                    Size                count,
                    __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

        public:
            template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
            auto atMost (
                    Size                count,
                    __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

        public:
            template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
            auto moreThan (
                    Size                count,
                    __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

        public:
            template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
            auto fewerThan (
                    Size                count,
                    __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

        public:
            template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
            auto count (
                    __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> Size;

        public:
            template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
            auto any (
                    __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

        public:
            template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
            auto all (
                    __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

        public:
            template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
            auto none (
                    __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

        public:
            using Collection < __ElementType > :: forEach;
        public:
            using Collection < __ElementType > :: some;
        public:
            using Collection < __ElementType > :: atLeast;
        public:
            using Collection < __ElementType > :: atMost;
        public:
            using Collection < __ElementType > :: moreThan;
        public:
            using Collection < __ElementType > :: fewerThan;
        public:
            using Collection < __ElementType > :: count;
        public:
            using Collection < __ElementType > :: any;
        public:
            using Collection < __ElementType > :: all;
        public:
            using Collection < __ElementType > :: none;
        };

    }
}

#include "list/DelegateIterator.hpp"
#include "list/Iterator.hpp"
#include "list/ReverseIterator.hpp"

#include "list/impl/DelegateIterator.hpp"
#include "list/impl/Iterator.hpp"
#include "list/impl/ReverseIterator.hpp"

#include "list/impl/List.hpp"

#endif // __CDS_EX_LIST_HPP__
