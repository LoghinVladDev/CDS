//
// Created by loghin on 6/20/22.
//

#ifndef __CDS_MUTABLE_COLLECTION_HPP__
#define __CDS_MUTABLE_COLLECTION_HPP__

#include <CDS/Collection>

namespace cds {

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    class MutableCollection : public Collection < __ElementType > {

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
        constexpr MutableCollection () noexcept;

    protected:
        constexpr MutableCollection (
                MutableCollection const & collection
        ) noexcept;

    protected:
        constexpr MutableCollection (
                MutableCollection && collection
        ) noexcept;

    protected:
        __CDS_cpplang_ConstexprDestructor ~MutableCollection () noexcept override;

    public:
        /**
         * @brief Function used to clear the collection, removing all elements from it
         * @exceptsafe
         * @test tested in base class test
         */
        auto clear () noexcept -> void override = 0;

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
        __CDS_NoDiscard auto toString () const noexcept -> String override = 0;

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

#include "mutableCollection/DelegateIterator.hpp"
#include "mutableCollection/Iterator.hpp"
#include "mutableCollection/ReverseIterator.hpp"

#include "mutableCollection/impl/DelegateIterator.hpp"
#include "mutableCollection/impl/Iterator.hpp"
#include "mutableCollection/impl/ReverseIterator.hpp"
#include "mutableCollection/impl/MutableCollection.hpp"

#endif // __CDS_MUTABLE_COLLECTION_HPP__
