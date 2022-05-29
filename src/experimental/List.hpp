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
         * @tparam T is the type of elements contained into List
         */
        template < typename T >
        class List : public Collection < T > {

        public:
            /**
             * @typedef Alias for T, the type of the contained elements, publicly accessible, useful in sfinae statements - decltype ( Collection ) :: ElementType
             */
            using typename Collection < T > :: ElementType;

        protected:
            /**
             * @typedef Alias for std :: initializer_list < T > or std :: initializer_list < ElementType >
             */
            using typename Collection < T > :: InitializerList;

        protected:
            /**
             * @interface An Iterator Delegate represents the actual implementation of the iterator done by the derived classes. The Abstract Delegate Iterator is the base used by the Iterator bases
             */
            using typename Collection < T > :: AbstractDelegateIterator;

        protected:
            /**
             * @class The base class for mutable Iterator types. It is the wrapper over the AbstractDelegateIterator, acquired from derived classes implementation
             */
            class DelegateIterator;

        protected:
            /**
             * @class The base class for immutable Iterator types. It is the wrapper over the AbstractDelegateIterator, acquired from derived classes implementation
             */
            using typename Collection < T > :: DelegateConstIterator;

        protected:
            /**
             * @class The base class for Iterator types, mutable or immutable. It is the wrapper over the AbstractDelegateIterator, acquired from derived classes implementation
             */
            using typename Collection < T > :: AbstractIterator;

        protected:
            /**
             * @enum The types of delegate iterator requests the Collection Base Object can make to its Derivative Objects when acquiring an Iterator Delegate Implementation
             */
            using DelegateIteratorRequestType = typename Collection < T > :: DelegateIteratorRequestType;

        public:
            /**
             * @class The Iterator type used for Forward Iteration over mutable values
             */
            class Iterator;

        public:
            /**
             * @class The Iterator type used for Forward Iteration over immutable values
             */
            using typename Collection < T > :: ConstIterator;

        public:
            /**
             * @class The Iterator type used for Backward Iteration over mutable values
             */
            class ReverseIterator;

        public:
            /**
             * @class The Iterator type used for Backward Iteration over immutable values
             */
            using typename Collection < T > :: ConstReverseIterator;

        protected:
            /// number of elements present in the list
            Size _size { 0U };

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
            using Collection < T > :: acquireDelegate;

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
            using Collection < T > :: begin;

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
            using Collection < T > :: end;

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
            using Collection < T > :: rbegin;

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
            using Collection < T > :: rend;

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

        public:
            /**
             * @brief Explicit Comparison Function with generic CDS/Object
             * @param object : Object cref = Constant Reference to an Object-derived instance
             * @exceptsafe
             * @return bool = true if objects are equal, false otherwise
             */
            __CDS_NoDiscard auto equals (
                    Object const & object
            ) const noexcept -> bool override;

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
             * @tparam ListType is the type of the list to store the sublist into
             * @tparam V is a type alias for T used to disable the function if T is not copy constructible
             * @param storeIn : ListType ref = Reference to the list to store the new elements into
             * @param from : Index = the index from which to create the sublist, inclusive
             * @param to : Index = the index until which to create the sublist, exclusive
             * @exceptsafe
             * @return ListType ref = Reference to the given list in 'storeIn'
             */
            template < typename ListType, typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () && meta :: isDerivedFrom < ListType, Collection < T > > () > = 0 >
            auto sub (
                    ListType  & storeIn,
                    Index       from,
                    Index       to
            ) const noexcept -> ListType &;

        public:
            /**
             * @brief Function used to obtain a subsection of the current list
             * @tparam ListType is the type of the list to store the sublist into
             * @tparam V is a type alias for T used to disable the function if T is not copy constructible
             * @param from : Index = the index from which to create the sublist, inclusive
             * @param to : Index = the index until which to create the sublist, exclusive
             * @exceptsafe
             * @return ListType = List containing the requested subsection
             */
            template < typename ListType, typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () && meta :: isDerivedFrom < ListType, Collection < T > > () > = 0 >
            auto sub (
                    Index from,
                    Index to
            ) const noexcept -> ListType;

        public:
            /**
             * @brief Function used to obtain a subsection of the current list
             * @tparam ListType is the type of the list to store the sublist into
             * @tparam V is a type alias for T used to disable the function if T is not copy constructible
             * @param from : Index = the index from which to create the sublist, inclusive
             * @param to : Index = the index until which to create the sublist, exclusive
             * @exceptsafe
             * @return ListType = List containing the requested subsection
             */
            template < template < typename ... > class ListType, typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () && meta :: isDerivedFrom < ListType < T >, Collection < T > > () > = 0 >
             auto sub (
                     Index from,
                     Index to
             ) const noexcept -> ListType < ElementType >;

        public:
            /**
             * @brief Function used to obtain the indices of a given element and store them into a given list
             * @tparam ListType is the type of the list to store the indices into
             * @param storeIn : ListType ref = Reference to the List to store the indices into
             * @param element : ElementType cref = Constant Reference to the Element to acquire the indices for
             * @exceptsafe
             * @return ListType ref = Reference to the list passed in the 'storeIn' parameter
             */
            template < typename ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType, Collection < Index > > () > = 0 >
            auto indices (
                    ListType            & storeIn,
                    ElementType   const & element
            ) const noexcept -> ListType &;

        public:
            /**
             * @brief Function used to obtain the indices of a given element
             * @tparam ListType is the type of the list to store the indices into
             * @param element : ElementType cref = Constant Reference to the Element to acquire the indices for
             * @exceptsafe
             * @return ListType = List containing the requested indices
             */
            template < typename ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType, Collection < Index > > () > = 0 >
            auto indices (
                    ElementType const & element
            ) const noexcept -> ListType;

        public:
            /**
             * @brief Function used to obtain the indices of a given element
             * @tparam ListType is the type of the list to store the indices into
             * @param element : ElementType cref = Constant Reference to the Element to acquire the indices for
             * @exceptsafe
             * @return ListType = List containing the requested indices
             */
            template < template < typename ... > class ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType < Index >, Collection < Index > > () > = 0 >
            auto indices (
                    ElementType const & element
            ) const noexcept -> ListType < Index >;

        public:
            /**
             * @brief Function used to obtain the indices of the elements that validate a given predicate
             * @tparam Predicate is the type of the predicate object, it must be a valid callable type object, with a signature compatible with
             *      bool ( Decay < ElementType > )
             * @tparam ListType is the type of the list to store the indices into
             * @param storeIn : ListType ref = Reference to the List to store the indices into
             * @param predicate : Predicate cref = Constant Reference to the predicate callable object
             * @exceptsafe
             * @return ListType ref = Reference to the list passed in the 'storeIn' parameter
             */
            template < typename Predicate, typename ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType, Collection < Index > > () > = 0 >
            auto indices (
                    ListType          & storeIn,
                    Predicate   const & predicate
            ) const noexcept ( noexcept ( ( meta :: valueOf < Predicate > () ) ( meta :: referenceOf < ElementType > () ) ) ) -> ListType &;

        public:
            /**
             * @brief Function used to obtain the indices of the elements that validate a given predicate
             * @tparam Predicate is the type of the predicate object, it must be a valid callable type object, with a signature compatible with
             *      bool ( Decay < ElementType > )
             * @tparam ListType is the type of the list to store the indices into
             * @param predicate : Predicate cref = Constant Reference to the predicate callable object
             * @exceptsafe
             * @return ListType = List containing the requested indices
             */
            template < typename Predicate, typename ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType, Collection < Index > > () > = 0 >
            auto indices (
                    Predicate const & predicate
            ) const noexcept -> ListType;

        public:
            /**
             * @brief Function used to obtain the indices of the elements that validate a given predicate
             * @tparam Predicate is the type of the predicate object, it must be a valid callable type object, with a signature compatible with
             *      bool ( Decay < ElementType > )
             * @tparam ListType is the type of the list to store the indices into
             * @param predicate : Predicate cref = Constant Reference to the predicate callable object
             * @exceptsafe
             * @return ListType = List containing the requested indices
             */
            template < typename Predicate, template < typename ... > class ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType < Index >, Collection < Index > > () > = 0 >
            auto indices (
                    Predicate const & predicate
            ) const noexcept -> ListType < Index >;

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
             * @tparam V alias for ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param element : ElementType cref = Constant Reference to the element to copy and add into the collection
             * @exceptsafe if ElementType copy constructor is exceptsafe
             */
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            auto pushFront (
                    ElementType const & element
            ) noexcept -> ElementType &;

        public:
            /**
             * @brief Function used to add an element at the front of the list via move ( moving of the received instance ). Only used if element is moveConstructible ( has move ctor )
             * @tparam V alias for ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param element : ElementType mref = Move Reference to the element to move into the collection
             * @exceptsafe if ElementType move constructor is exceptsafe
             */
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            auto pushFront (
                    ElementType && element
            ) noexcept -> ElementType &;

        public:
            /**
             * @brief Function used to add an element at the back of the list via copy ( construction of new instance ). Only used if element is copyConstructible ( has copy ctor )
             * @tparam V alias for ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param element : ElementType cref = Constant Reference to the element to copy and add into the collection
             * @exceptsafe if ElementType copy constructor is exceptsafe
             */
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            auto pushBack (
                    ElementType const & element
            ) noexcept -> ElementType &;

        public:
            /**
             * @brief Function used to add an element at the back of the list via move ( moving of the received instance ). Only used if element is moveConstructible ( has move ctor )
             * @tparam V alias for ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param element : ElementType mref = Move Reference to the element to move into the collection
             * @exceptsafe if ElementType move constructor is exceptsafe
             */
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            auto pushBack (
                    ElementType && element
            ) noexcept -> ElementType &;

        public:
            /**
             * @brief Function used to add an element before a given iterator's referenced element via copy ( creating a new instance ). Only used if element is copyConstructible ( has copy ctor )
             * @tparam V is an alias for ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : Iterator cref = Constant Reference to an iterator to place the element before
             * @param element : ElementType cref = Constant Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            auto insertBefore (
                    Iterator    const & iterator,
                    ElementType const & element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element before a given iterator's referenced element via move ( move of the given instance ) Only used if element is moveConstructible ( has move ctor )
             * @tparam V is an alias for ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : Iterator cref = Constant Reference to an iterator to place the element before
             * @param element : ElementType mref = Move Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            auto insertBefore (
                    Iterator    const & iterator,
                    ElementType      && element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element after a given iterator's referenced element via copy ( creating a new instance ). Only used if element is copyConstructible ( has copy ctor )
             * @tparam V is an alias for ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : Iterator cref = Constant Reference to an iterator to place the element after
             * @param element : ElementType cref = Constant Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            auto insertAfter (
                    Iterator    const & iterator,
                    ElementType const & element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element after a given iterator's referenced element via move ( move of the given instance ) Only used if element is moveConstructible ( has move ctor )
             * @tparam V is an alias for ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : Iterator cref = Constant Reference to an iterator to place the element after
             * @param element : ElementType mref = Move Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            auto insertAfter (
                    Iterator   const & iterator,
                    ElementType     && element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element before a given iterator's referenced element via copy ( creating a new instance ). Only used if element is copyConstructible ( has copy ctor )
             * @tparam V is an alias for ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : ConstIterator cref = Constant Reference to an iterator to place the element before
             * @param element : ElementType cref = Constant Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            auto insertBefore (
                    ConstIterator   const & iterator,
                    ElementType     const & element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element before a given iterator's referenced element via move ( move of the given instance ) Only used if element is moveConstructible ( has move ctor )
             * @tparam V is an alias for ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : ConstIterator cref = Constant Reference to an iterator to place the element before
             * @param element : ElementType mref = Move Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            auto insertBefore (
                    ConstIterator  const & iterator,
                    ElementType         && element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element after a given iterator's referenced element via copy ( creating a new instance ). Only used if element is copyConstructible ( has copy ctor )
             * @tparam V is an alias for ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : ConstIterator cref = Constant Reference to an iterator to place the element after
             * @param element : ElementType cref = Constant Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            auto insertAfter (
                    ConstIterator   const & iterator,
                    ElementType     const & element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element after a given iterator's referenced element via move ( move of the given instance ) Only used if element is moveConstructible ( has move ctor )
             * @tparam V is an alias for ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : ConstIterator cref = Constant Reference to an iterator to place the element after
             * @param element : ElementType mref = Move Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            auto insertAfter (
                    ConstIterator  const & iterator,
                    ElementType         && element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element before a given iterator's referenced element via copy ( creating a new instance ). Only used if element is copyConstructible ( has copy ctor )
             * @tparam V is an alias for ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : ReverseIterator cref = Constant Reference to an iterator to place the element before
             * @param element : ElementType cref = Constant Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            auto insertBefore (
                    ReverseIterator const & iterator,
                    ElementType     const & element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element before a given iterator's referenced element via move ( move of the given instance ) Only used if element is moveConstructible ( has move ctor )
             * @tparam V is an alias for ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : ReverseIterator cref = Constant Reference to an iterator to place the element before
             * @param element : ElementType mref = Move Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            auto insertBefore (
                    ReverseIterator const & iterator,
                    ElementType          && element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element after a given iterator's referenced element via copy ( creating a new instance ). Only used if element is copyConstructible ( has copy ctor )
             * @tparam V is an alias for ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : ReverseIterator cref = Constant Reference to an iterator to place the element after
             * @param element : ElementType cref = Constant Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            auto insertAfter (
                    ReverseIterator const & iterator,
                    ElementType     const & element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element after a given iterator's referenced element via move ( move of the given instance ) Only used if element is moveConstructible ( has move ctor )
             * @tparam V is an alias for ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : ReverseIterator cref = Constant Reference to an iterator to place the element after
             * @param element : ElementType mref = Move Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            auto insertAfter (
                    ReverseIterator const & iterator,
                    ElementType          && element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element before a given iterator's referenced element via copy ( creating a new instance ). Only used if element is copyConstructible ( has copy ctor )
             * @tparam V is an alias for ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : ConstReverseIterator cref = Constant Reference to an iterator to place the element before
             * @param element : ElementType cref = Constant Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            auto insertBefore (
                    ConstReverseIterator    const & iterator,
                    ElementType             const & element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element before a given iterator's referenced element via move ( move of the given instance ) Only used if element is moveConstructible ( has move ctor )
             * @tparam V is an alias for ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : ConstReverseIterator cref = Constant Reference to an iterator to place the element before
             * @param element : ElementType mref = Move Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            auto insertBefore (
                    ConstReverseIterator const & iterator,
                    ElementType               && element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element after a given iterator's referenced element via copy ( creating a new instance ). Only used if element is copyConstructible ( has copy ctor )
             * @tparam V is an alias for ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : ConstReverseIterator cref = Constant Reference to an iterator to place the element after
             * @param element : ElementType cref = Constant Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            auto insertAfter (
                    ConstReverseIterator    const & iterator,
                    ElementType             const & element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Function used to add an element after a given iterator's referenced element via move ( move of the given instance ) Only used if element is moveConstructible ( has move ctor )
             * @tparam V is an alias for ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param iterator : ConstReverseIterator cref = Constant Reference to an iterator to place the element after
             * @param element : ElementType mref = Move Reference to the element to copy and place
             * @throws IllegalArgumentException if the given iterator is not obtained from this collection
             * @throws OutOfBoundsException if the given iterator is out of bounds
             * @return ElementType ref = Reference to the newly inserted value
             */
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            auto insertAfter (
                    ConstReverseIterator const & iterator,
                    ElementType               && element
            ) noexcept (false) -> ElementType &;

        public:
            /**
             * @brief Alias for pushBack, function used to add an element at the back of the list via copy ( construction of new instance ). Only used if element is copyConstructible ( has copy ctor )
             * @tparam V alias for ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param element : ElementType cref = Constant Reference to the element to copy and add into the collection
             * @exceptsafe if ElementType copy constructor is exceptsafe
             */
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            auto append (
                    ElementType const & element
            ) noexcept -> ElementType &;

        public:
            /**
             * @brief Alias for pushBack, function used to add an element at the back of the list via move ( moving of the received instance ). Only used if element is moveConstructible ( has move ctor )
             * @tparam V alias for ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param element : ElementType mref = Move Reference to the element to move into the collection
             * @exceptsafe if ElementType move constructor is exceptsafe
             */
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            auto append (
                    ElementType && element
            ) noexcept -> ElementType &;

        public:
            /**
             * @brief Alias for pushFront, function used to add an element at the front of the list via copy ( construction of new instance ). Only used if element is copyConstructible ( has copy ctor )
             * @tparam V alias for ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param element : ElementType cref = Constant Reference to the element to copy and add into the collection
             * @exceptsafe if ElementType copy constructor is exceptsafe
             */
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            auto prepend (
                    ElementType const & element
            ) noexcept -> ElementType &;

        public:
            /**
             * @brief Alias for pushFront, function used to add an element at the front of the list via move ( moving of the received instance ). Only used if element is moveConstructible ( has move ctor )
             * @tparam V alias for ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param element : ElementType mref = Move Reference to the element to move into the collection
             * @exceptsafe if ElementType move constructor is exceptsafe
             */
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
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
             * @tparam ComparatorFunction is the type of the comparator function, its signature must be compatible with bool ( Decay < ElementType >, Decay < ElementType > )
             * @param comparatorFunction : ComparatorFunction const & = Constant Reference to the comparator callable object / function
             * @exceptsafe if ComparatorFunction is exceptsafe
             */
            template < typename ComparatorFunction = decltype ( & predicates :: lessThan < ElementType > ) >
            auto sort (
                    ComparatorFunction const & comparatorFunction = & predicates :: lessThan < ElementType >
            ) noexcept ( noexcept ( comparatorFunction ( meta :: valueOf < ElementType > (), meta :: valueOf < ElementType > () ) ) ) -> void;

        public:
            __CDS_NoDiscard constexpr auto size () const noexcept -> Size override;

        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replace (
                    Size                count,
                    ElementType const & what,
                    ElementType const & with
            ) noexcept -> Size;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceAll (
                    ElementType const & what,
                    ElementType const & with
            ) noexcept -> Size;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceFirst (
                    ElementType const & what,
                    ElementType const & with
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replaceFirst (
                    ElementType const & what,
                    ElementType      && with
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceLast (
                    ElementType const & what,
                    ElementType const & with
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replaceLast (
                    ElementType const & what,
                    ElementType      && with
            ) noexcept -> bool;

        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceOf (
                    Size                                count,
                    Collection < ElementType >  const & of,
                    ElementType                 const & with
            ) noexcept -> Size;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceAllOf (
                    Collection < ElementType >  const & of,
                    ElementType                 const & with
            ) noexcept -> Size;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceFirstOf (
                    Collection < ElementType >  const & of,
                    ElementType                 const & with
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replaceFirstOf (
                    Collection < ElementType >  const & of,
                    ElementType                      && with
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceLastOf (
                    Collection < ElementType >  const & of,
                    ElementType                 const & with
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replaceLastOf (
                    Collection < ElementType >  const & of,
                    ElementType                      && with
            ) noexcept -> bool;

        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceNotOf (
                    Size                                count,
                    Collection < ElementType >  const & of,
                    ElementType                 const & with
            ) noexcept -> Size;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceAllNotOf (
                    Collection < ElementType >  const & of,
                    ElementType                 const & with
            ) noexcept -> Size;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceFirstNotOf (
                    Collection < ElementType >  const & of,
                    ElementType                 const & with
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replaceFirstNotOf (
                    Collection < ElementType >  const & of,
                    ElementType                      && with
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceLastNotOf (
                    Collection < ElementType >  const & of,
                    ElementType                 const & with
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replaceLastNotOf (
                    Collection < ElementType >  const & of,
                    ElementType                      && with
            ) noexcept -> bool;

        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceOf (
                    Size                        count,
                    InitializerList     const & of,
                    ElementType         const & with
            ) noexcept -> Size;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceAllOf (
                    InitializerList     const & of,
                    ElementType         const & with
            ) noexcept -> Size;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceFirstOf (
                    InitializerList     const & of,
                    ElementType         const & with
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replaceFirstOf (
                    InitializerList     const & of,
                    ElementType              && with
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceLastOf (
                    InitializerList     const & of,
                    ElementType         const & with
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replaceLastOf (
                    InitializerList     const & of,
                    ElementType              && with
            ) noexcept -> bool;

        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceNotOf (
                    Size                        count,
                    InitializerList     const & of,
                    ElementType         const & with
            ) noexcept -> Size;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceAllNotOf (
                    InitializerList     const & of,
                    ElementType         const & with
            ) noexcept -> Size;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceFirstNotOf (
                    InitializerList     const & of,
                    ElementType         const & with
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replaceFirstNotOf (
                    InitializerList     const & of,
                    ElementType              && with
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceLastNotOf (
                    InitializerList     const & of,
                    ElementType         const & with
            ) noexcept -> bool;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replaceLastNotOf (
                    InitializerList     const & of,
                    ElementType              && with
            ) noexcept -> bool;

        public:
            template < typename Predicate, typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replace (
                    Size                count,
                    Predicate   const & predicate,
                    ElementType const & with
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> Size;
        public:
            template < typename Predicate, typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceAll (
                    Predicate   const & predicate,
                    ElementType const & with
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> Size;
        public:
            template < typename Predicate, typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceFirst (
                    Predicate   const & predicate,
                    ElementType const & with
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;
        public:
            template < typename Predicate, typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replaceFirst (
                    Predicate   const & predicate,
                    ElementType      && with
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;
        public:
            template < typename Predicate, typename V = T, meta :: EnableIf < meta :: isCopyAssignable < V > () > = 0 >
            auto replaceLast (
                    Predicate   const & predicate,
                    ElementType const & with
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;
        public:
            template < typename Predicate, typename V = T, meta :: EnableIf < meta :: isMoveAssignable < V > () > = 0 >
            auto replaceLast (
                    Predicate   const & predicate,
                    ElementType      && with
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

        public:
            template < typename Predicate, typename Supplier >
            auto replace (
                    Size                count,
                    Predicate   const & predicate,
                    Supplier    const & supplier
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( meta :: referenceOf < ElementType > () ) ) ) -> Size;
        public:
            template < typename Predicate, typename Supplier >
            auto replaceAll (
                    Predicate   const & predicate,
                    Supplier    const & supplier
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( meta :: referenceOf < ElementType > () ) ) ) -> Size;
        public:
            template < typename Predicate, typename Supplier >
            auto replaceFirst (
                    Predicate   const & predicate,
                    Supplier    const & supplier
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( meta :: referenceOf < ElementType > () ) ) ) -> bool;
            template < typename Predicate, typename Supplier >
            auto replaceLast (
                    Predicate   const & predicate,
                    Supplier    const & supplier
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
            __CDS_NoDiscard constexpr auto empty () const noexcept -> bool override;
        public:
            __CDS_NoDiscard auto toString () const noexcept -> String override;

        public:
            auto index (
                    ElementType const &
            ) const noexcept -> Index;

        public:
            template < template < typename ... > class ListType >
            auto find (
                    Size,
                    ElementType             const &,
                    ListType < Iterator >         &
            ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > class ListType >
            auto find (
                    Size,
                    ElementType const &
            ) noexcept -> ListType < Iterator >;
        public:
            auto findFirst (
                    ElementType const &
            ) noexcept -> Iterator;
        public:
            auto findLast (
                    ElementType const &
            ) noexcept -> Iterator;
        public:
            template < template < typename ... > class ListType >
            auto findAll (
                    ElementType             const &,
                    ListType < Iterator >         &
            ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > class ListType >
            auto findAll (
                    ElementType const &
            ) noexcept -> ListType < Iterator >;

        public:
            template < template < typename ... > class ListType >
            auto findOf (
                    Size,
                    Collection < T >        const &,
                    ListType < Iterator >         &
            ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > class ListType >
            auto findOf (
                    Size,
                    Collection < T > const &
            ) noexcept -> ListType < Iterator >;
        public:
            auto findFirstOf (
                    Collection < T > const &
            ) noexcept -> Iterator;
        public:
            auto findLastOf (
                    Collection < T > const &
            ) noexcept -> Iterator;
        public:
            template < template < typename ... > class ListType >
            auto findAllOf (
                    Collection < T >        const &,
                    ListType < Iterator >         &
            ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > class ListType >
            auto findAllOf (
                    Collection < T > const &
            ) noexcept -> ListType < Iterator >;

        public:
            template < template < typename ... > class ListType >
            auto findNotOf (
                    Size,
                    Collection < T >        const &,
                    ListType < Iterator >         &
            ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > class ListType >
            auto findNotOf (
                    Size,
                    Collection < T > const &
            ) noexcept -> ListType < Iterator >;
        public:
            auto findFirstNotOf (
                    Collection < T > const &
            ) noexcept -> Iterator;
        public:
            auto findLastNotOf (
                    Collection < T > const &
            ) noexcept -> Iterator;
        public:
            template < template < typename ... > class ListType >
            auto findAllNotOf (
                    Collection < T >        const &,
                    ListType < Iterator >         &
            ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > class ListType >
            auto findAllNotOf (
                    Collection < T > const &
            ) noexcept -> ListType < Iterator >;

        public:
            template < template < typename ... > class ListType >
            auto findOf (
                    Size,
                    InitializerList         const &,
                    ListType < Iterator >         &
            ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > class ListType >
            auto findOf (
                    Size,
                    InitializerList const &
            ) noexcept -> ListType < Iterator >;
        public:
            auto findFirstOf (
                    InitializerList const &
            ) noexcept -> Iterator;
        public:
            auto findLastOf (
                    InitializerList const &
            ) noexcept -> Iterator;
        public:
            template < template < typename ... > class ListType >
            auto findAllOf (
                    InitializerList         const &,
                    ListType < Iterator >         &
            ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > class ListType >
            auto findAllOf (
                    InitializerList const &
            ) noexcept -> ListType < Iterator >;

        public:
            template < template < typename ... > class ListType >
            auto findNotOf (
                    Size,
                    InitializerList         const &,
                    ListType < Iterator >         &
            ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > class ListType >
            auto findNotOf (
                    Size,
                    InitializerList const &
            ) noexcept -> ListType < Iterator >;
        public:
            auto findFirstNotOf (
                    InitializerList const &
            ) noexcept -> Iterator;
        public:
            auto findLastNotOf (
                    InitializerList const &
            ) noexcept -> Iterator;
        public:
            template < template < typename ... > class ListType >
            auto findAllNotOf (
                    InitializerList         const &,
                    ListType < Iterator >         &
            ) noexcept -> ListType < Iterator > &;
        public:
            template < template < typename ... > class ListType >
            auto findAllNotOf (
                    InitializerList const &
            ) noexcept -> ListType < Iterator >;

        public:
            template < template < typename ... > class ListType, typename Predicate >
            auto find (
                    Size,
                    Predicate               const &,
                    ListType < Iterator >         &
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> ListType < Iterator > &;
        public:
            template < template < typename ... > class ListType, typename Predicate >
            auto find (
                    Size,
                    Predicate const &
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> ListType < Iterator >;
        public:
            template < typename Predicate >
            auto findFirst (
                    Predicate const &
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> Iterator;
        public:
            template < typename Predicate >
            auto findLast (
                    Predicate const &
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> Iterator;
        public:
            template < template < typename ... > class ListType, typename Predicate >
            auto findAll (
                    Predicate               const &,
                    ListType < Iterator >         &
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> ListType < Iterator > &;
        public:
            template < template < typename ... > class ListType, typename Predicate >
            auto findAll (
                    Predicate const &
            ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> ListType < Iterator >;

        public:
            template < typename Action >
            auto forEach (
                    Action const & action
            ) noexcept ( noexcept ( action ( meta :: referenceOf < ElementType > () ) ) ) -> void;

        public:
            template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
            auto some (
                    Size                count,
                    Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

        public:
            template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
            auto atLeast (
                    Size                count,
                    Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

        public:
            template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
            auto atMost (
                    Size                count,
                    Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

        public:
            template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
            auto moreThan (
                    Size                count,
                    Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

        public:
            template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
            auto fewerThan (
                    Size                count,
                    Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

        public:
            template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
            auto count (
                    Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> Size;

        public:
            template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
            auto any (
                    Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

        public:
            template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
            auto all (
                    Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

        public:
            template < typename Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) >
            auto none (
                    Predicate   const & predicate = & predicates :: alwaysTrue < ElementType >
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool;

        public:
            using Collection < T > :: forEach;
        public:
            using Collection < T > :: some;
        public:
            using Collection < T > :: atLeast;
        public:
            using Collection < T > :: atMost;
        public:
            using Collection < T > :: moreThan;
        public:
            using Collection < T > :: fewerThan;
        public:
            using Collection < T > :: count;
        public:
            using Collection < T > :: any;
        public:
            using Collection < T > :: all;
        public:
            using Collection < T > :: none;
        public:
            using Collection < T > :: find;
        public:
            using Collection < T > :: findFirst;
        public:
            using Collection < T > :: findLast;
        public:
            using Collection < T > :: findAll;
        public:
            using Collection < T > :: findOf;
        public:
            using Collection < T > :: findFirstOf;
        public:
            using Collection < T > :: findLastOf;
        public:
            using Collection < T > :: findAllOf;
        public:
            using Collection < T > :: findNotOf;
        public:
            using Collection < T > :: findFirstNotOf;
        public:
            using Collection < T > :: findLastNotOf;
        public:
            using Collection < T > :: findAllNotOf;
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
