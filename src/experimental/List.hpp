//
// Created by loghin on 4/24/2022.
//

#ifndef __CDS_EX_LIST_HPP__
#define __CDS_EX_LIST_HPP__

#include <CDS/experimental/MutableCollection>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        /**
         * @class Abstract Object representing any Indexed Iterable Container of given elements of type
         * @tparam __ElementType is the type of elements contained into List
         */
        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class List : public MutableCollection < __ElementType > {

        public:
            /**
             * @typedef Alias for __ElementType, the type of the contained elements, publicly accessible, useful in sfinae statements - decltype ( Collection ) :: ElementType
             */
            using typename MutableCollection < __ElementType > :: ElementType;

        protected:
            /**
             * @typedef Alias for std :: initializer_list < T > or std :: initializer_list < ElementType >
             */
            using typename MutableCollection < __ElementType > :: InitializerList;

        protected:
            /**
             * @interface An Iterator Delegate represents the actual implementation of the iterator done by the derived classes. The Abstract Delegate Iterator is the base used by the Iterator bases
             */
            using typename MutableCollection < __ElementType > :: AbstractDelegateIterator;

        protected:
            /**
             * @class The base class for mutable Iterator types. It is the wrapper over the AbstractDelegateIterator, acquired from derived classes implementation
             */
            using typename MutableCollection < __ElementType > :: DelegateIterator;

        protected:
            /**
             * @class The base class for immutable Iterator types. It is the wrapper over the AbstractDelegateIterator, acquired from derived classes implementation
             */
            using typename MutableCollection < __ElementType > :: DelegateConstIterator;

        protected:
            /**
             * @class The base class for Iterator types, mutable or immutable. It is the wrapper over the AbstractDelegateIterator, acquired from derived classes implementation
             */
            using typename MutableCollection < __ElementType > :: AbstractIterator;

        protected:
            /**
             * @enum The types of delegate iterator requests the Collection Base Object can make to its Derivative Objects when acquiring an Iterator Delegate Implementation
             */
            using typename MutableCollection < __ElementType > :: DelegateIteratorRequestType;

        public:
            /**
             * @class The Iterator type used for Forward Iteration over mutable values
             */
            using typename MutableCollection < __ElementType > :: Iterator;

        public:
            /**
             * @class The Iterator type used for Forward Iteration over immutable values
             */
            using typename MutableCollection < __ElementType > :: ConstIterator;

        public:
            /**
             * @class The Iterator type used for Backward Iteration over mutable values
             */
            using typename MutableCollection < __ElementType > :: ReverseIterator;

        public:
            /**
             * @class The Iterator type used for Backward Iteration over immutable values
             */
            using typename MutableCollection < __ElementType > :: ConstReverseIterator;

        public:
            static Index const invalidIndex = -1;

        protected:
            /**
             * @brief Import statement for
             *      acquireDelegate ( AbstractIterator ),
             *      acquireDelegate ( ConstIterator ),
             *      acquireDelegate ( ConstReverseIterator )
             */
            using MutableCollection < __ElementType > :: acquireDelegate;

        protected:
            /**
             * @brief Function used to request a DelegateIterator from the Iterator constructing functions ( begin/end/rbegin/rend ) to acquire a DelegateIterator containing
             *      the implementation from the derived class, of requested iterator type
             * @param requestType : DelegateIteratorRequestType = the type of request, associated with expected returned type of iterator implementation
             * @exceptsafe
             * @return UniquePointer < DelegateIterator > = Uniquely-Owned Pointer to a DelegateIterator-derived object
             */
            auto delegateIterator (
                    DelegateIteratorRequestType
            ) noexcept -> cds :: UniquePointer < DelegateIterator > override = 0;

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
            __CDS_Explicit constexpr List (
                    Size size
            ) noexcept;

        protected:
            Size _size { 0ULL };

        public:
            /**
             * @brief Default Destructor
             * @exceptsafe
             * @test tested in collection/Collection test
             */
            __CDS_cpplang_ConstexprDestructor ~List () noexcept override = default;

        public:
            /**
             * @brief Function used to clear the collection, removing all elements from it
             * @exceptsafe
             * @test tested in base class test
             */
            auto clear () noexcept -> void override = 0;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto size () const noexcept -> Size override;

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
             * @brief Function used in Collection :: add implementation, called to acquire a pointer to emplace the element to
             * @param referenceElement : ElementType cref = Constant Reference to the element to be added, as a reference, if implementation requires specific placement
             * @exceptsafe
             * @return ElementType ptr = Pointer to an ElementType.
             * @test tested in collection/Collection test
             */
            auto pNewInsert (
                    ElementType const & referenceElement
            ) noexcept -> ElementType * override;

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
             * @return ElementType ptr = address value to emplace the new element at
             */
            virtual auto pNewFront () noexcept -> ElementType * = 0;

        protected:
            /**
             * @brief Function used to create and return the storage space for a new element, at the back of the list.
             *      Used in pushBack
             * @exceptsafe
             * @return ElementType ptr = address value to emplace the new element at
             */
            virtual auto pNewBack () noexcept -> ElementType * = 0;

        protected:
            /**
             * @brief Function used to create and return the storage space for a new element, before the position indicated by a given iterator.
             *      Used in insertBefore
             * @param iterator : Iterator cref = the iterator indicating the position to insert before
             * @exceptsafe
             * @return ElementType ptr = address value to emplace the new element at
             */
            virtual auto pNewBefore (
                    Iterator const & iterator
            ) noexcept -> ElementType * = 0;

        protected:
            /**
             * @brief Function used to create and return the storage space for a new element, after the position indicated by a given iterator.
             *      Used in insertAfter
             * @param iterator : Iterator cref = the iterator indicating the position to insert after
             * @exceptsafe
             * @return ElementType ptr = address value to emplace the new element at
             */
            virtual auto pNewAfter (
                    Iterator const & iterator
            ) noexcept -> ElementType * = 0;

        protected:
            /**
             * @brief Function used to create and return the storage space for a new element, before the position indicated by a given iterator.
             *      Used in insertBefore
             * @param iterator : ConstIterator cref = the iterator indicating the position to insert before
             * @exceptsafe
             * @return ElementType ptr = address value to emplace the new element at
             */
            virtual auto pNewBefore (
                    ConstIterator const & iterator
            ) noexcept -> ElementType * = 0;

        protected:
            /**
             * @brief Function used to create and return the storage space for a new element, after the position indicated by a given iterator.
             *      Used in insertAfter
             * @param iterator : ConstIterator cref = the iterator indicating the position to insert after
             * @exceptsafe
             * @return ElementType ptr = address value to emplace the new element at
             */
            virtual auto pNewAfter (
                    ConstIterator const & iterator
            ) noexcept -> ElementType * = 0;

        protected:
            /**
             * @brief Function used to create and return the storage space for a new element, before the position indicated by a given iterator.
             *      Used in insertBefore
             * @param iterator : ReverseIterator cref = the iterator indicating the position to insert before
             * @exceptsafe
             * @return ElementType ptr = address value to emplace the new element at
             */
            virtual auto pNewBefore (
                    ReverseIterator const & iterator
            ) noexcept -> ElementType * = 0;

        protected:
            /**
             * @brief Function used to create and return the storage space for a new element, after the position indicated by a given iterator.
             *      Used in insertAfter
             * @param iterator : ReverseIterator cref = the iterator indicating the position to insert after
             * @exceptsafe
             * @return ElementType ptr = address value to emplace the new element at
             */
            virtual auto pNewAfter (
                    ReverseIterator const & iterator
            ) noexcept -> ElementType * = 0;

        protected:
            /**
             * @brief Function used to create and return the storage space for a new element, before the position indicated by a given iterator.
             *      Used in insertBefore
             * @param iterator : ConstReverseIterator cref = the iterator indicating the position to insert before
             * @exceptsafe
             * @return ElementType ptr = address value to emplace the new element at
             */
            virtual auto pNewBefore (
                    ConstReverseIterator const & iterator
            ) noexcept -> ElementType * = 0;

        protected:
            /**
             * @brief Function used to create and return the storage space for a new element, after the position indicated by a given iterator.
             *      Used in insertAfter
             * @param iterator : ConstReverseIterator cref = the iterator indicating the position to insert after
             * @exceptsafe
             * @return ElementType ptr = address value to emplace the new element at
             */
            virtual auto pNewAfter (
                    ConstReverseIterator const & iterator
            ) noexcept -> ElementType * = 0;

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
            ) noexcept -> void;

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
            ) noexcept -> void;

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
            ) noexcept -> void;

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
            ) noexcept -> void;

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
            auto remove (
                    Iterator const & iterator
            ) noexcept -> bool override = 0;

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
            auto remove (
                    ReverseIterator const & iterator
            ) noexcept -> bool override = 0;

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
            auto remove (
                    Iterator    const * pIterators,
                    Size                size
            ) noexcept -> Size override = 0;

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
            auto remove (
                    ReverseIterator const * pIterators,
                    Size                    size
            ) noexcept -> Size override = 0;

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
        };

    }
}

#include "list/impl/List.hpp"

#endif // __CDS_EX_LIST_HPP__
