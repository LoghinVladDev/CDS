//
// Created by loghin on 4/24/2022.
//

#ifndef __CDS_EX_COLLECTION_HPP__
#define __CDS_EX_COLLECTION_HPP__

#include <CDS/std-types>
#include <CDS/Object>
#include <CDS/meta/TypeTraits>
#include <CDS/Concepts>
#include <CDS/smartPointers/UniquePointer>

#include "collection/DelegateIteratorRequestType.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        /**
         * @class Abstract Object representing any Iterable Container of given elements of type
         * @tparam __ElementType is the type of elements contained into Collection
         * @test tested in collection/CollectionTest
         */
        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class Collection : public cds :: Object {

        public:
            /**
             * @typedef public alias for __ElementType, the type of the contained elements, publicly accessible, useful in sfinae statements - decltype ( Collection ) :: ElementType
             */
            using ElementType = __ElementType;

        protected:
            /**
             * @typedef Alias for std :: initializer_list < __ElementType > or std :: initializer_list < ElementType >
             */
            using InitializerList = std :: initializer_list < __ElementType >;

        protected:
            /**
             * @interface An Iterator Delegate represents the actual implementation of the iterator done by the derived classes. The Abstract Delegate Iterator is the base used by the Iterator bases
             */
            class AbstractDelegateIterator;

        protected:
            /**
             * @class The base class for immutable Iterator types. It is the wrapper over the AbstractDelegateIterator, acquired from derived classes implementation
             */
            class DelegateConstIterator;

        protected:
            /**
             * @class The base class for Iterator types, mutable or immutable. It is the wrapper over the AbstractDelegateIterator, acquired from derived classes implementation
             */
            class AbstractIterator;

        public:
            /**
             * @class The Iterator type used for Forward Iteration over immutable values
             */
            class ConstIterator;

        public:
            /**
             * @class The Iterator type used for Backward Iteration over immutable values
             */
            class ConstReverseIterator;

        protected:
            /**
             * @enum The types of delegate iterator requests the Collection Base Object can make to its Derived Objects when acquiring an Iterator Delegate Implementation
             * @test tested in nester class test
             */
            using DelegateIteratorRequestType = __hidden :: __impl :: DelegateIteratorRequestType;

        protected:
            /**
             * @brief Function used to safely acquire a Delegate Iterator Owned by a given Iterator
             * @param iterator : AbstractIterator cref = Constant Reference to an AbstractIterator-derived Object
             * @exceptsafe
             * @return AbstractDelegateIterator cptr = Pointer to an Immutable, AbstractDelegateIterator-derived Object
             * @test tested in the class test
             */
            constexpr static auto acquireDelegate (
                    AbstractIterator const & iterator
            ) noexcept -> AbstractDelegateIterator const *;

        protected:
            /**
             * @brief Function used to safely acquire a Delegate Iterator Owned by a given Iterator
             * @param iterator : ConstIterator cref = Constant Reference to an ConstIterator Object
             * @exceptsafe
             * @return DelegateConstIterator cptr = Pointer to an Immutable, DelegateConstIterator-derived Object
             * @test tested in the class test
             */
            constexpr static auto acquireDelegate (
                    ConstIterator const & iterator
            ) noexcept -> DelegateConstIterator const *;

        protected:
            /**
             * @brief Function used to safely acquire a Delegate Iterator Owned by a given Iterator
             * @param iterator : ConstReverseIterator cref = Constant Reference to an ConstIterator Object
             * @exceptsafe
             * @return DelegateConstIterator cptr = Pointer to an Immutable, DelegateConstIterator-derived Object
             * @test tested in the class test
             */
            constexpr static auto acquireDelegate (
                    ConstReverseIterator const & iterator
            ) noexcept -> DelegateConstIterator const *;

        protected:
            /**
             * @brief Function used to request a DelegateConstIterator from the Iterator constructing functions ( begin/cbegin/rbegin/crbegin/end/cend/rend/crend ) to acquire a DelegateConstIterator containing
             *      the implementation from the derived class, of requested iterator type
             * @param requestType : DelegateIteratorRequestType = the type of request, associated with expected returned type of iterator implementation
             * @exceptsafe
             * @return UniquePointer < DelegateConstIterator > = Uniquely-Owned Pointer to a DelegateConstIterator-derived object
             * @test tested in the class test
             */
            virtual auto delegateConstIterator (
                    DelegateIteratorRequestType requestType
            ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > = 0;


        public:
            /**
             * @brief Function used to acquire a Forward-ConstIterator, indicating to the first element of the collection
             * @exceptsafe
             * @return ConstIterator = requested Iterator object
             * @test tested in the class test
             */
            auto begin () const noexcept -> ConstIterator;

        public:
            /**
             * @brief Function used to acquire a Forward-ConstIterator, indicating after the last element of the collection
             * @exceptsafe
             * @return ConstIterator = requested Iterator object
             * @test tested in the class test
             */
            auto end () const noexcept -> ConstIterator;

        public:
            /**
             * @brief Function used to acquire a Forward-ConstIterator, indicating to the first element of the collection
             * @exceptsafe
             * @return ConstIterator = requested Iterator object
             * @test tested in the class test
             */
            auto cbegin () const noexcept -> ConstIterator;

        public:
            /**
             * @brief Function used to acquire a Forward-ConstIterator, indicating after the last element of the collection
             * @exceptsafe
             * @return ConstIterator = requested Iterator object
             * @test tested in the class test
             */
            auto cend () const noexcept -> ConstIterator;

        public:
            /**
             * @brief Function used to acquire a Backward-ConstIterator, indicating to the first element of the collection in reverse iteration order - last element of the collection
             * @exceptsafe
             * @return ConstReverseIterator = requested Iterator object
             * @test tested in the class test
             */
            auto rbegin () const noexcept -> ConstReverseIterator;

        public:
            /**
             * @brief Function used to acquire a Backward-ConstIterator, indicating after the last element of the collection in reverse iteration order - before first element of the collection
             * @exceptsafe
             * @return ConstReverseIterator = requested Iterator object
             * @test tested in the class test
             */
            auto rend () const noexcept -> ConstReverseIterator;

        public:
            /**
             * @brief Function used to acquire a Backward-ConstIterator, indicating to the first element of the collection in reverse iteration order - last element of the collection
             * @exceptsafe
             * @return ConstReverseIterator = requested Iterator object
             * @test tested in the class test
             */
            auto crbegin () const noexcept -> ConstReverseIterator;

        public:
            /**
             * @brief Function used to acquire a Backward-ConstIterator, indicating after the last element of the collection in reverse iteration order - before first element of the collection
             * @exceptsafe
             * @return ConstReverseIterator = requested Iterator object
             * @test tested in the class test
             */
            auto crend () const noexcept -> ConstReverseIterator;

        public:
            /**
             * @brief Function used to remove an element identified by a given Iterator
             * @param iterator : ConstIterator cref = Constant Reference to the Iterator indicating the value to be removed
             * @exceptsafe
             * @return bool = true if removal was successful, false otherwise ( invalid iterator )
             * @test tested in the class test
             */
            virtual auto remove (
                    ConstIterator const & iterator
            ) noexcept -> bool = 0;

        public:
            /**
             * @brief Function used to remove an element identified by a given Iterator
             * @param iterator : ConstReverseIterator cref = Constant Reference to the Reverse Iterator indicating the value to be removed
             * @exceptsafe
             * @return bool = true if removal was successful, false otherwise ( invalid iterator )
             * @test tested in the class test
             */
            virtual auto remove (
                    ConstReverseIterator const & iterator
            ) noexcept -> bool = 0;

        protected:
            /**
             * @brief Function used to remove a batch of elements identified by a given array of Iterators
             * @param pIterators : ConstIterator cptr = Address to an array of Constant ConstIterator objects, indicating the elements to be removed
             * @param size : Size = the number of elements in the pIterators array
             * @exceptsafe
             * @return Size = number of elements that were successfully removed
             * @test tested in the class test
             */
            virtual auto remove (
                    ConstIterator   const * pIterators,
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
            virtual auto remove (
                    ConstReverseIterator    const * pIterators,
                    Size                            size
            ) noexcept -> Size = 0;

        public:
            /**
             * @brief Function used to remove a given number of elements based on the validation by a given predicate ( bool ( ElementType ) function )
             * @tparam __Predicate the type of the given predicate. Must refer to a callable object, whose call is compatible with bool ( Decay < ElementType > )
             * @param count : Size = maximum number of elements to remove
             * @param predicate : __Predicate cref = Constant Reference to a callable function, lambda or object, compatible with the bool ( Decay < ElementType > ) signature
             * @exceptsafe if predicate is exceptsafe
             * @return Size = number of removed elements
             * @test tested in the class test
             */
            template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            auto remove (
                    Size                count,
                    __Predicate const & predicate
            ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> Size;

        public:
            /**
             * @brief Function used to remove the first element that matches the validation of a given predicate ( bool ( ElementType ) function )
             * @tparam __Predicate the type of the given predicate. Must refer to a callable object, whose call is compatible with bool ( Decay < ElementType > )
             * @param predicate : __Predicate cref = Constant Reference to a callable function, lambda or object, compatible with the bool ( Decay < ElementType > ) signature
             * @exceptsafe if predicate is exceptsafe
             * @return bool = true if one element was removed, false otherwise
             * @test tested in the class test
             */
            template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            auto removeFirst (
                    __Predicate const & predicate
            ) noexcept -> bool;

        public:
            /**
             * @brief Function used to remove the last element that matches the validation of a given predicate ( bool ( ElementType ) function )
             * @tparam __Predicate the type of the given predicate. Must refer to a callable object, whose call is compatible with bool ( Decay < ElementType > )
             * @param predicate : __Predicate cref = Constant Reference to a callable function, lambda or object, compatible with the bool ( Decay < ElementType > ) signature
             * @exceptsafe if predicate is exceptsafe
             * @return bool = true if one element was removed, false otherwise
             * @test tested in the class test
             */
            template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            auto removeLast (
                    __Predicate const & predicate
            ) noexcept -> bool;

        public:
            /**
             * @brief Function used to remove all the elements that match the validation of a given predicate ( bool ( ElementType ) function )
             * @tparam __Predicate the type of the given predicate. Must refer to a callable object, whose call is compatible with bool ( Decay < ElementType > )
             * @param predicate : __Predicate cref = Constant Reference to a callable function, lambda or object, compatible with the bool ( Decay < ElementType > ) signature
             * @exceptsafe if predicate is exceptsafe
             * @return Size = number of elements that were removed as a result of this call
             * @test tested in the class test
             */
            template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            auto removeAll (
                    __Predicate const & predicate
            ) noexcept -> Size;

        public:
            /**
             * @brief Function used to remove a given number of elements based by comparison to a given element
             * @param count : Size = maximum number of elements to remove
             * @param element : ElementType cref = Constant Reference to the element to compare collection elements to
             * @exceptsafe
             * @return Size = number of removed elements
             * @test tested in the class test
             */
            auto remove (
                    Size                count,
                    ElementType const & element
            ) noexcept -> Size;

        public:
            /**
             * @brief Function used to remove the first element that matches the comparison to a given element
             * @param element : ElementType cref = Constant Reference to the element to compare collection elements to
             * @exceptsafe
             * @return bool = true if one element was removed, false otherwise
             * @test tested in the class test
             */
            auto removeFirst (
                    ElementType const & element
            ) noexcept -> bool;

        public:
            /**
             * @brief Function used to remove the last element that matches the comparison to a given element
             * @param element : ElementType cref = Constant Reference to the element to compare collection elements to
             * @exceptsafe
             * @return bool = true if one element was removed, false otherwise
             * @test tested in the class test
             */
            auto removeLast (
                    ElementType const & element
            ) noexcept -> bool;

        public:
            /**
             * @brief Function used to remove all the elements that match the comparison to a given element
             * @param element : ElementType cref = Constant Reference to the element to compare collection elements to
             * @exceptsafe
             * @return Size = number of removed elements
             * @test tested in the class test
             */
            auto removeAll (
                    ElementType const & element
            ) noexcept -> Size;

        public:
            /**
             * @brief Function used to remove a given number of elements that are contained in a given collection
             * @param count : Size = maximum number of elements to remove
             * @param collection : Collection < ElementType > cref = Constant Reference a Collection given for contains check
             * @exceptsafe
             * @return Size = number of removed elements
             * @test tested in the class test
             */
            auto removeOf (
                    Size                                count,
                    Collection < ElementType >  const & collection
            ) noexcept -> Size;

        public:
            /**
             * @brief Function used to remove the first element that is contained in a given collection
             * @param collection : Collection < ElementType > cref = Constant Reference a Collection given for contains check
             * @exceptsafe
             * @return bool = true if one element was removed, false otherwise
             * @test tested in the class test
             */
            auto removeFirstOf (
                    Collection < ElementType > const & collection
            ) noexcept -> bool;

        public:
            /**
             * @brief Function used to remove the last element that is contained in a given collection
             * @param collection : Collection < ElementType > cref = Constant Reference a Collection given for contains check
             * @exceptsafe
             * @return bool = true if one element was removed, false otherwise
             * @test tested in the class test
             */
            auto removeLastOf (
                    Collection < ElementType > const & collection
            ) noexcept -> bool;

        public:
            /**
             * @brief Function used to remove all the elements that are contained in a given collection
             * @param collection : Collection < ElementType > cref = Constant Reference a Collection given for contains check
             * @exceptsafe
             * @return Size = number of removed elements
             * @test tested in the class test
             */
            auto removeAllOf (
                    Collection < ElementType > const & collection
            ) noexcept -> Size;

        public:
            /**
             * @brief Function used to remove a given number of elements that are not contained in a given collection
             * @param count : Size = maximum number of elements to remove
             * @param collection : Collection < ElementType > cref = Constant Reference a Collection given for not contains check
             * @exceptsafe
             * @return Size = number of removed elements
             * @test tested in the class test
             */
            auto removeNotOf (
                    Size                        count,
                    Collection < ElementType >    const & collection
            ) noexcept -> Size;

        public:
            /**
             * @brief Function used to remove the first element that is not contained in a given collection
             * @param collection : Collection < ElementType > cref = Constant Reference a Collection given for not contains check
             * @exceptsafe
             * @return bool = true if one element was removed, false otherwise
             * @test tested in the class test
             */
            auto removeFirstNotOf (
                    Collection < ElementType > const & collection
            ) noexcept -> bool;

        public:
            /**
             * @brief Function used to remove the last element that is not contained in a given collection
             * @param collection : Collection < ElementType > cref = Constant Reference a Collection given for not contains check
             * @exceptsafe
             * @return bool = true if one element was removed, false otherwise
             * @test tested in the class test
             */
            auto removeLastNotOf (
                    Collection < ElementType > const & collection
            ) noexcept -> bool;

        public:
            /**
             * @brief Function used to remove a given number of elements that are not contained in a given collection
             * @param collection : Collection < ElementType > cref = Constant Reference a Collection given for not contains check
             * @exceptsafe
             * @return Size = number of removed elements
             * @test tested in the class test
             */
            auto removeAllNotOf (
                    Collection < ElementType > const & collection
            ) noexcept -> Size;

        public:
            /**
             * @brief Function used to remove a given number of elements that are contained in a given initializer list
             * @param count : Size = maximum number of elements to remove
             * @param list : Collection < T > :: InitializerList cref = Constant Reference an Initializer List given for contains check
             * @exceptsafe
             * @return Size = number of removed elements
             * @test tested in the class test
             */
            auto removeOf (
                    Size                    count,
                    InitializerList const & list
            ) noexcept -> Size;

        public:
            /**
             * @brief Function used to remove the first element that is contained in a given initializer list
             * @param list : Collection < T > :: InitializerList cref = Constant Reference an Initializer List given for contains check
             * @exceptsafe
             * @return bool = true if one element was removed, false otherwise
             * @test tested in the class test
             */
            auto removeFirstOf (
                    InitializerList const & list
            ) noexcept -> bool;

        public:
            /**
             * @brief Function used to remove the last element that is contained in a given initializer list
             * @param list : Collection < T > :: InitializerList cref = Constant Reference an Initializer List given for contains check
             * @exceptsafe
             * @return bool = true if one element was removed, false otherwise
             * @test tested in the class test
             */
            auto removeLastOf (
                    InitializerList const & list
            ) noexcept -> bool;

        public:
            /**
             * @brief Function used to remove all the elements that are contained in a given initializer list
             * @param list : Collection < T > :: InitializerList cref = Constant Reference an Initializer List given for contains check
             * @exceptsafe
             * @return Size = number of removed elements
             * @test tested in the class test
             */
            auto removeAllOf (
                    InitializerList const & list
            ) noexcept -> Size;

        public:
            /**
             * @brief Function used to remove a given number of elements that are not contained in a given initializer list
             * @param count : Size = maximum number of elements to remove
             * @param list : Collection < T > :: InitializerList cref = Constant Reference an Initializer List given for contains check
             * @exceptsafe
             * @return Size = number of removed elements
             * @test tested in the class test
             */
            auto removeNotOf (
                    Size                    count,
                    InitializerList const & list
            ) noexcept -> Size;

        public:
            /**
             * @brief Function used to remove the first element that is not contained in a given initializer list
             * @param list : Collection < T > :: InitializerList cref = Constant Reference an Initializer List given for contains check
             * @exceptsafe
             * @return bool = true if one element was removed, false otherwise
             * @test tested in the class test
             */
            auto removeFirstNotOf (
                    InitializerList const & list
            ) noexcept -> bool;

        public:
            /**
             * @brief Function used to remove the last element that is not contained in a given initializer list
             * @param list : Collection < T > :: InitializerList cref = Constant Reference an Initializer List given for contains check
             * @exceptsafe
             * @return bool = true if one element was removed, false otherwise
             * @test tested in the class test
             */
            auto removeLastNotOf (
                    InitializerList const & list
            ) noexcept -> bool;

        public:
            /**
             * @brief Function used to remove a given number of elements that are not contained in a given initializer list
             * @param list : Collection < T > :: InitializerList cref = Constant Reference an Initializer List given for contains check
             * @exceptsafe
             * @return Size = number of removed elements
             * @test tested in the class test
             */
            auto removeAllNotOf (
                    InitializerList const & list
            ) noexcept -> Size;

        public:
            /**
             * @brief Function used to apply an action over each element of the collection
             * @tparam __Action the type of the action given as a parameter, the type must be callable and compatible with the void ( Decay < ElementType > ) function signature
             * @param action : __Action cref = Constant Reference to callable object, to be called with each element of the collection as a parameter
             * @exceptsafe if __Action is exceptsafe
             * @test tested in base class test
             */
            template < typename __Action > // NOLINT(bugprone-reserved-identifier)
            auto forEach (
                    __Action const & action
            ) const noexcept ( noexcept ( action ( meta :: referenceOf < ElementType const > () ) ) ) -> void;

        public:
            /**
             * @brief Function used to check if the collection contains exactly 'count' elements that are validated by a given predicate
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
             * @param count : Size = number of elements required to match
             * @param predicate : __Predicate cref = Constant Reference to callable object, to be called with each element of the collection as a parameter. If no predicate is given, it will default to a predicate that will validate every value.
             *      If no predicate is given, 'some' must yield the same value as 'caller.size() == count'
             * @exceptsafe if Predicate is exceptsafe
             * @return bool = true if number of elements validated == count, false otherwise
             * @test tested in base class test
             */
            template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
            auto some (
                    Size                count,
                    __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
            ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;

        public:
            /**
             * @brief Function used to check if the collection contains at least 'count' elements that are validated by a given predicate
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
             * @param count : Size = minimum number of elements required to match
             * @param predicate : __Predicate cref = Constant Reference to callable object, to be called with each element of the collection as a parameter. If no predicate is given, it will default to a predicate that will validate every value
             *      If no predicate is given, 'atLeast' must yield the same value as 'caller.size() >= count'
             * @exceptsafe if Predicate is exceptsafe
             * @return bool = true if number of elements validated >= count, false otherwise
             * @test tested in base class test
             */
            template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
            auto atLeast (
                    Size                count,
                    __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
            ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;

        public:
            /**
             * @brief Function used to check if the collection contains at most 'count' elements that are validated by a given predicate
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
             * @param count : Size = maximum number of elements required to match
             * @param predicate : __Predicate cref = Constant Reference to callable object, to be called with each element of the collection as a parameter. If no predicate is given, it will default to a predicate that will validate every value
             *      If no predicate is given, 'atMost' must yield the same value as 'caller.size() <= count'
             * @exceptsafe if Predicate is exceptsafe
             * @return bool = true if number of elements validated <= count, false otherwise
             * @test tested in base class test
             */
            template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
            auto atMost (
                    Size                count,
                    __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
            ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;

        public:
            /**
             * @brief Function used to check if the collection contains more than 'count' elements that are validated by a given predicate
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
             * @param count : Size = minimum number of elements required to match
             * @param predicate : __Predicate cref = Constant Reference to callable object, to be called with each element of the collection as a parameter. If no predicate is given, it will default to a predicate that will validate every value
             *      If no predicate is given, 'moreThan' must yield the same value as 'caller.size() > count'
             * @exceptsafe if Predicate is exceptsafe
             * @return bool = true if number of elements validated > count, false otherwise
             * @test tested in base class test
             */
            template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
            auto moreThan (
                    Size                count,
                    __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
            ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;

        public:
            /**
             * @brief Function used to check if the collection contains less than 'count' elements that are validated by a given predicate
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
             * @param count : Size = maximum number of elements required to match
             * @param predicate : __Predicate cref = Constant Reference to callable object, to be called with each element of the collection as a parameter. If no predicate is given, it will default to a predicate that will validate every value
             *      If no predicate is given, 'fewerThan' must yield the same value as 'caller.size() < count'
             * @exceptsafe if Predicate is exceptsafe
             * @return bool = true if number of elements validated < count, false otherwise
             * @test tested in base class test
             */
            template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
            auto fewerThan (
                    Size                count,
                    __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
            ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;

        public:
            /**
             * @brief Function used to acquire the number of elements that are validated by a given predicate
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
             * @param predicate : __Predicate cref = Constant Reference to callable object, to be called with each element of the collection as a parameter. If no predicate is given, it will default to a predicate that will validate every value
             *      If no predicate is given, 'count' must yield the same value as 'caller.size()'
             * @exceptsafe if Predicate is exceptsafe
             * @return Size = number of elements that are validated by the given predicate
             * @test tested in base class test
             */
            template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
            auto count (
                    __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
            ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> Size;

        public:
            /**
             * @brief Function used to check if any of the collection's elements are validated by a given predicate
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
             * @param predicate : __Predicate cref = Constant Reference to callable object, to be called with each element of the collection as a parameter. If no predicate is given, it will default to a predicate that will validate every value
             *      If no predicate is given, 'any' must yield the same value as 'caller.size() > 0'
             * @exceptsafe if Predicate is exceptsafe
             * @return bool = true if at least one element is validated by the given predicate, false otherwise
             * @test tested in base class test
             */
            template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
            auto any (
                    __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
            ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;

        public:
            /**
             * @brief Function used to check if all of the collection's elements are validated by a given predicate
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
             * @param predicate : __Predicate cref = Constant Reference to callable object, to be called with each element of the collection as a parameter. If no predicate is given, it will default to a predicate that will validate every value
             *      If no predicate is given, 'all' must return 'true'
             * @exceptsafe if Predicate is exceptsafe
             * @return bool = true if all of the collection's elements are validated by the given predicate, false otherwise
             * @test tested in base class test
             */
            template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
            auto all (
                    __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
            ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;

        public:
            /**
             * @brief Function used to check if none of the collection's elements are validated by a given predicate
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
             * @param predicate : __Predicate cref = Constant Reference to callable object, to be called with each element of the collection as a parameter. If no predicate is given, it will default to a predicate that will validate every value
             *      If no predicate is given, 'none' must yield the same value as 'caller.empty()'
             * @exceptsafe if Predicate is exceptsafe
             * @return bool = true if none of the collection's elements are validated by the given predicate, false otherwise
             * @test tested in base class test
             */
            template < typename __Predicate = decltype ( & predicates :: alwaysTrue < ElementType > ) > // NOLINT(bugprone-reserved-identifier)
            auto none (
                    __Predicate const & predicate = & predicates :: alwaysTrue < ElementType >
            ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;

        public:
            /**
             * @brief Function used to populate a given Collection of Iterators, 'storeIn', with maximum 'maxCount' elements, pointing to the values matching the comparison to the given 'element' value
             * @tparam CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
             * @param maxCount : Size = maximum number of iterators to add to the storeIn object
             * @param element : ElementType cref = Constant Reference to the element to compare the collection's elements to
             * @param storeIn : __CollectionType < Collection < ElementType > :: ConstIterator > ref = Reference to the collection of iterators to add the found iterators to
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: ConstIterator > ref = Reference to the given collection inside the 'storeIn' parameter
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto find (
                    Size                                        maxCount,
                    ElementType                         const & element,
                    __CollectionType < ConstIterator >        & storeIn
            ) const noexcept -> __CollectionType < ConstIterator > &;

        public:
            /**
             * @brief Function used to return a Collection non-abstract derived type of Iterators with maximum 'maxCount' elements, pointing to the values matching the comparison to the given 'element' value
             * @tparam __CollectionType the type of the Collection to be returned. Constraint : CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
             * @param maxCount : Size = maximum number of iterators to add to the returned object
             * @param element : ElementType cref = Constant Reference to the element to compare the collection's elements to
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: ConstIterator > = Newly created object containing the requested Iterators
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto find (
                    Size                maxCount,
                    ElementType const & element
            ) const noexcept -> __CollectionType < ConstIterator >;

        public:
            /**
             * @brief Function used to return the ConstIterator matching the first value that is equal to the given 'element' value
             * @param element : ElementType cref = Constant Reference to an element to compare the collection's elements to
             * @exceptsafe
             * @return ConstIterator = iterator matching the first value equal to the given 'element' value, caller.end() if no value matches
             * @test tested in base class test
             */
            auto findFirst (
                    ElementType const & element
            ) const noexcept -> ConstIterator;

        public:
            /**
             * @brief Function used to return the ConstIterator matching the last value that is equal to the given 'element' value
             * @param element : ElementType cref = Constant Reference to an element to compare the collection's elements to
             * @exceptsafe
             * @return ConstIterator = iterator matching the last value equal to the given 'element' value, caller.end() if no value matches
             * @test tested in base class test
             */
            auto findLast (
                    ElementType const & element
            ) const noexcept -> ConstIterator;

        public:
            /**
             * @brief Function used to populate a given Collection of Iterators, 'storeIn', with all the iterators pointing to the values matching the comparison to the given 'element' value
             * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
             * @param element : ElementType cref = Constant Reference to the element to compare the collection's elements to
             * @param storeIn : __CollectionType < Collection < ElementType > :: ConstIterator > ref = Reference to the collection of iterators to add the found iterators to
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: ConstIterator > ref = Reference to the given collection inside the 'storeIn' parameter
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findAll (
                    ElementType                         const & element,
                    __CollectionType < ConstIterator >        & storeIn
            ) const noexcept -> __CollectionType < ConstIterator > &;

        public:
            /**
             * @brief Function used to return a Collection non-abstract derived type of Iterators with all the iterators pointing to the values matching the comparison to the given 'element' value
             * @tparam __CollectionType the type of the Collection to be returned. Constraint : CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
             * @param element : ElementType cref = Constant Reference to the element to compare the collection's elements to
             * @exceptsafe
             * @return __CollectionType < Collection < ElementType > :: ConstIterator > = Newly created object containing the requested Iterators
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findAll (
                    ElementType const & element
            ) const noexcept -> __CollectionType < ConstIterator >;

        public:
            /**
             * @brief Function used to populate a given Collection of Iterators, 'storeIn', with maximum 'maxCount' elements, pointing to the values that are also found in the 'elements' collection
             * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
             * @param maxCount : Size = maximum number of iterators to add to the storeIn object
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the contains condition for
             * @param storeIn : __CollectionType < Collection < ElementType > :: ConstIterator > ref = Reference to the collection of iterators to add the found iterators to
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: ConstIterator > ref = Reference to the given collection inside the 'storeIn' parameter
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findOf (
                    Size                                        maxCount,
                    Collection < ElementType >          const & elements,
                    __CollectionType < ConstIterator >        & storeIn
            ) const noexcept -> __CollectionType < ConstIterator > &;

        public:
            /**
             * @brief Function used to return a Collection non-abstract derived type of Iterators with maximum 'maxCount' elements, pointing to the values that are also found in the 'elements' collection
             * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
             * @param maxCount : Size = maximum number of iterators to add to the returned object
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the contains condition for
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: ConstIterator > = Newly created object containing the requested Iterators
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findOf (
                    Size                                maxCount,
                    Collection < ElementType >  const & elements
            ) const noexcept -> __CollectionType < ConstIterator >;

        public:
            /**
             * @brief Function used to return the ConstIterator matching the first value that is also found in the 'elements' collection
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the contains condition for
             * @exceptsafe
             * @return ConstIterator = iterator matching the first value also found in the 'elements' collection, caller.end() if no value matches
             * @test tested in base class test
             */
            auto findFirstOf (
                    Collection < ElementType > const & elements
            ) const noexcept -> ConstIterator;

        public:
            /**
             * @brief Function used to return the ConstIterator matching the last value that is also found in the 'elements' collection
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the contains condition for
             * @exceptsafe
             * @return ConstIterator = iterator matching the last value also found in the 'elements' collection, caller.end() if no value matches
             * @test tested in base class test
             */
            auto findLastOf (
                    Collection < ElementType > const & elements
            ) const noexcept -> ConstIterator;

        public:
            /**
             * @brief Function used to populate a given Collection of Iterators, 'storeIn', with all the iterators pointing to the values that are also found in the 'elements' collection
             * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the contains condition for
             * @param storeIn : __CollectionType < Collection < ElementType > :: ConstIterator > ref = Reference to the collection of iterators to add the found iterators to
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: ConstIterator > ref = Reference to the given collection inside the 'storeIn' parameter
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findAllOf (
                    Collection < ElementType >          const & elements,
                    __CollectionType < ConstIterator >        & storeIn
            ) const noexcept -> __CollectionType < ConstIterator > &;

        public:
            /**
             * @brief Function used to return a Collection non-abstract derived type of Iterators with all the iterators pointing to the values that are also found in the 'elements' collection
             * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the contains condition for
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: ConstIterator > = Newly created object containing the requested Iterators
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findAllOf (
                    Collection < ElementType > const & elements
            ) const noexcept -> __CollectionType < ConstIterator >;

        public:
            /**
             * @brief Function used to populate a given Collection of Iterators, 'storeIn', with maximum 'maxCount' elements, pointing to the values that are not found in the 'elements' collection
             * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
             * @param maxCount : Size = maximum number of iterators to add to the storeIn object
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the not contains condition for
             * @param storeIn : __CollectionType < Collection < ElementType > :: ConstIterator > ref = Reference to the collection of iterators to add the found iterators to
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: ConstIterator > ref = Reference to the given collection inside the 'storeIn' parameter
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findNotOf (
                    Size                                        maxCount,
                    Collection < ElementType >          const & elements,
                    __CollectionType < ConstIterator >        & storeIn
            ) const noexcept -> __CollectionType < ConstIterator > &;

        public:
            /**
             * @brief Function used to return a Collection non-abstract derived type of Iterators with maximum 'maxCount' elements, pointing to the values that are not found in the 'elements' collection
             * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
             * @param maxCount : Size = maximum number of iterators to add to the returned object
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the not contains condition for
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: ConstIterator > = Newly created object containing the requested Iterators
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findNotOf (
                    Size                                maxCount,
                    Collection < ElementType >  const & elements
            ) const noexcept -> __CollectionType < ConstIterator >;

        public:
            /**
             * @brief Function used to return the ConstIterator matching the first value that is not found in the 'elements' collection
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the not contains condition for
             * @exceptsafe
             * @return ConstIterator = iterator matching the first value not found in the 'elements' collection, caller.end() if no value matches
             * @test tested in base class test
             */
            auto findFirstNotOf (
                    Collection < ElementType > const & elements
            ) const noexcept -> ConstIterator;

        public:
            /**
             * @brief Function used to return the ConstIterator matching the last value that is not found in the 'elements' collection
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the not contains condition for
             * @exceptsafe
             * @return ConstIterator = iterator matching the last value not found in the 'elements' collection, caller.end() if no value matches
             * @test tested in base class test
             */
            auto findLastNotOf (
                    Collection < ElementType > const & elements
            ) const noexcept -> ConstIterator;

        public:
            /**
             * @brief Function used to populate a given Collection of Iterators, 'storeIn', with all the iterators pointing to the values that are not found in the 'elements' collection
             * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the not contains condition for
             * @param storeIn : __CollectionType < Collection < ElementType > :: ConstIterator > ref = Reference to the collection of iterators to add the found iterators to
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: ConstIterator > ref = Reference to the given collection inside the 'storeIn' parameter
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findAllNotOf (
                    Collection < ElementType >          const & elements,
                    __CollectionType < ConstIterator >        & storeIn
            ) const noexcept -> __CollectionType < ConstIterator > &;

        public:
            /**
             * @brief Function used to return a Collection non-abstract derived type of Iterators with all the iterators pointing to the values that are not found in the 'elements' collection
             * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection to check the not contains condition for
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: ConstIterator > = Newly created object containing the requested Iterators
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findAllNotOf (
                    Collection < ElementType > const & elements
            ) const noexcept -> __CollectionType < ConstIterator >;

        public:
            /**
             * @brief Function used to populate a given Collection of Iterators, 'storeIn', with maximum 'maxCount' elements, pointing to the values that are also found in the 'elements' InitializerList
             * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
             * @param maxCount : Size = maximum number of iterators to add to the storeIn object
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
             * @param storeIn : __CollectionType < Collection < ElementType > :: ConstIterator > ref = Reference to the collection of iterators to add the found iterators to
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: ConstIterator > ref = Reference to the given collection inside the 'storeIn' parameter
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findOf (
                    Size                                        maxCount,
                    InitializerList                     const & elements,
                    __CollectionType < ConstIterator >        & storeIn
            ) const noexcept -> __CollectionType < ConstIterator > &;

        public:
            /**
             * @brief Function used to return a Collection non-abstract derived type of Iterators with maximum 'maxCount' elements, pointing to the values that are also found in the 'elements' InitializerList
             * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
             * @param maxCount : Size = maximum number of iterators to add to the returned object
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: ConstIterator > = Newly created object containing the requested Iterators
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findOf (
                    Size                    maxCount,
                    InitializerList const & elements
            ) const noexcept -> __CollectionType < ConstIterator >;

        public:
            /**
             * @brief Function used to return the ConstIterator matching the first value that is also found in the 'elements' InitializerList
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
             * @exceptsafe
             * @return ConstIterator = iterator matching the first value also found in the 'elements' list, caller.end() if no value matches
             * @test tested in base class test
             */
            auto findFirstOf (
                    InitializerList const & elements
            ) const noexcept -> ConstIterator;

        public:
            /**
             * @brief Function used to return the ConstIterator matching the last value that is also found in the 'elements' InitializerList
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
             * @exceptsafe
             * @return ConstIterator = iterator matching the last value also found in the 'elements' list, caller.end() if no value matches
             * @test tested in base class test
             */
            auto findLastOf (
                    InitializerList const & elements
            ) const noexcept -> ConstIterator;

        public:
            /**
             * @brief Function used to populate a given Collection of Iterators, 'storeIn', with all the iterators pointing to the values that are also found in the 'elements' InitializerList
             * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
             * @param storeIn : __CollectionType < Collection < ElementType > :: ConstIterator > ref = Reference to the collection of iterators to add the found iterators to
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: ConstIterator > ref = Reference to the given collection inside the 'storeIn' parameter
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findAllOf (
                    InitializerList                     const & elements,
                    __CollectionType < ConstIterator >        & storeIn
            ) const noexcept -> __CollectionType < ConstIterator > &;

        public:
            /**
             * @brief Function used to return a Collection non-abstract derived type of Iterators with all the iterators pointing to the values that are also found in the 'elements' InitializerList
             * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: ConstIterator > = Newly created object containing the requested Iterators
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findAllOf (
                    InitializerList const & elements
            ) const noexcept -> __CollectionType < ConstIterator >;

        public:
            /**
             * @brief Function used to populate a given Collection of Iterators, 'storeIn', with maximum 'maxCount' elements, pointing to the values that are not found in the 'elements' InitializerList
             * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
             * @param maxCount : Size = maximum number of iterators to add to the storeIn object
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
             * @param storeIn : __CollectionType < Collection < ElementType > :: ConstIterator > ref = Reference to the collection of iterators to add the found iterators to
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: ConstIterator > ref = Reference to the given collection inside the 'storeIn' parameter
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findNotOf (
                    Size                                        maxCount,
                    InitializerList                     const & elements,
                    __CollectionType < ConstIterator >        & storeIn
            ) const noexcept -> __CollectionType < ConstIterator > &;

        public:
            /**
             * @brief Function used to return a Collection non-abstract derived type of Iterators with maximum 'maxCount' elements, pointing to the values that are not found in the 'elements' InitializerList
             * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
             * @param maxCount : Size = maximum number of iterators to add to the returned object
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: ConstIterator > = Newly created object containing the requested Iterators
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findNotOf (
                    Size                    maxCount,
                    InitializerList const & elements
            ) const noexcept -> __CollectionType < ConstIterator >;

        public:
            /**
             * @brief Function used to return the ConstIterator matching the first value that is not found in the 'elements' InitializerList
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
             * @exceptsafe
             * @return ConstIterator = iterator matching the first value not found in the 'elements' list, caller.end() if no value matches
             * @test tested in base class test
             */
            auto findFirstNotOf (
                    InitializerList const & elements
            ) const noexcept -> ConstIterator;

        public:
            /**
             * @brief Function used to return the ConstIterator matching the last value that is not found in the 'elements' InitializerList
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
             * @exceptsafe
             * @return ConstIterator = iterator matching the last value not found in the 'elements' list, caller.end() if no value matches
             * @test tested in base class test
             */
            auto findLastNotOf (
                    InitializerList const & elements
            ) const noexcept -> ConstIterator;

        public:
            /**
             * @brief Function used to populate a given Collection of Iterators, 'storeIn', with all the iterators pointing to the values that are not found in the 'elements' InitializerList
             * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
             * @param storeIn : __CollectionType < Collection < ElementType > :: ConstIterator > ref = Reference to the collection of iterators to add the found iterators to
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: ConstIterator > ref = Reference to the given collection inside the 'storeIn' parameter
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findAllNotOf (
                    InitializerList                     const & elements,
                    __CollectionType < ConstIterator >        & storeIn
            ) const noexcept -> __CollectionType < ConstIterator > &;

        public:
            /**
             * @brief Function used to return a Collection non-abstract derived type of Iterators with all the iterators pointing to the values that are not found in the 'elements' InitializerList
             * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the initializer list to check the contains condition for
             * @exceptsafe
             * @return Collection < Collection < ElementType > :: ConstIterator > = Newly created object containing the requested Iterators
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
            auto findAllNotOf (
                    InitializerList const & elements
            ) const noexcept -> __CollectionType < ConstIterator >;

        public:
            /**
             * @brief Function used to populate a given Collection derived type of Iterators, with a maximum number of 'maxCount' iterators, pointing to the first or all the elements in the collection that are validated by a given predicate
             * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
             * @param maxCount : Size = maximum number of iterators to add to the storeIn object
             * @param predicate : __Predicate cref = Constant Reference to the callable predicate object to pass each element to
             * @param storeIn : __CollectionType < Collection < ElementType > :: ConstIterator > ref = Reference to the collection of iterators to add the found iterators to
             * @exceptsafe if Predicate is exceptsafe
             * @return Collection < Collection < ElementType > :: ConstIterator > ref = Reference to the given collection inside the 'storeIn' parameter
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType, typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            auto find (
                    Size                                        maxCount,
                    __Predicate                         const & predicate,
                    __CollectionType < ConstIterator >        & storeIn
            ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType < ConstIterator > &;

        public:
            /**
             * @brief Function used to return a Collection non-abstract derived type of Iterators, with a maximum number of 'maxCount' iterators, pointing to the first or all the elements in the collection that are validated by a given predicate
             * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
             * @param maxCount : Size = maximum number of iterators to add to the returned object
             * @param predicate : __Predicate cref = Constant Reference to the callable predicate object to pass each element to
             * @exceptsafe if Predicate is exceptsafe
             * @return Collection < Collection < ElementType > :: ConstIterator > = Newly created object containing the requested Iterators
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType, typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            auto find (
                    Size                maxCount,
                    __Predicate const & predicate
            ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType < ConstIterator >;

        public:
            /**
             * @brief Function used to return an iterator to the first element validated by the given predicate
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
             * @param predicate : __Predicate cref = Constant Reference to the callable predicate object to pass each element to
             * @exceptsafe if Predicate is exceptsafe
             * @return Collection < ElementType > :: ConstIterator = Iterator to the first element validated by the given predicate, caller.end() if none exist
             * @test tested in base class test
             */
            template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            auto findFirst (
                    __Predicate const & predicate
            ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> ConstIterator;

        public:
            /**
             * @brief Function used to return an iterator to the last element validated by the given predicate
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
             * @param predicate : __Predicate cref = Constant Reference to the callable predicate object to pass each element to
             * @exceptsafe if Predicate is exceptsafe
             * @return Collection < ElementType > :: ConstIterator = Iterator to the last element validated by the given predicate, caller.end() if none exist
             * @test tested in base class test
             */
            template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            auto findLast (
                    __Predicate const & predicate
            ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> ConstIterator;

        public:
            /**
             * @brief Function used to populate a given Collection derived type of Iterators with all iterators pointing to the first or all the elements in the collection that are validated by a given predicate
             * @tparam __CollectionType the type of the Collection passed in the 'storeIn' parameter. Constraint : __CollectionType must be derived from Collection / compatible to Collection derived types, with one template parameter
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
             * @param predicate : __Predicate cref = Constant Reference to the callable predicate object to pass each element to
             * @param storeIn : __CollectionType < Collection < ElementType > :: ConstIterator > ref = Reference to the collection of iterators to add the found iterators to
             * @exceptsafe if Predicate is exceptsafe
             * @return Collection < Collection < ElementType > :: ConstIterator > ref = Reference to the given collection inside the 'storeIn' parameter
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType, typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            auto findAll (
                    __Predicate                         const & predicate,
                    __CollectionType < ConstIterator >        & storeIn
            ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType < ConstIterator > &;

        public:
            /**
             * @brief Function used to return a Collection non-abstract derived type of Iterators with all the iterators pointing to the first or all the elements in the collection that are validated by a given predicate
             * @tparam __CollectionType the type of the Collection to be returned. Constraint : __CollectionType must be a non-abstract type derived from Collection / compatible to Collection derived types, with one template parameter. non-abstract derived from Collection types are Array, LinkedList, HashSet, ...
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable and compatible with the bool ( Decay < ElementType > ) function signature
             * @param predicate : __Predicate cref = Constant Reference to the callable predicate object to pass each element to
             * @exceptsafe if Predicate is exceptsafe
             * @return Collection < Collection < ElementType > :: ConstIterator > = Newly created object containing the requested Iterators
             * @test tested in base class test
             */
            template < template < typename ... > class __CollectionType, typename __Predicate > // NOLINT(bugprone-reserved-identifier)
            auto findAll (
                    __Predicate const & predicate
            ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType < ConstIterator >;

        public:
            /**
             * @brief Bool cast operator, functionality equal to python's iterable empty check. '(bool) collection' is equivalent to '! collection.empty()'
             * @exceptsafe
             * @return bool = true if collection is not empty, false otherwise
             * @test tested in base class test
             */
            __CDS_cpplang_ConstexprPureAbstract __CDS_Implicit operator bool () const noexcept; // NOLINT(google-explicit-constructor)

        public:
            /**
             * @brief String conversion function, used to obtain String representation of the object
             * @exceptsafe
             * @return String = string representation
             * @test tested in base class test
             */
            __CDS_NoDiscard auto toString () const noexcept -> String override = 0;

        public:
            /**
             * @brief Hash function
             * @exceptsafe
             * @return Index = hash code value of the instance
             * @test tested in base class test
             */
            __CDS_NoDiscard auto hash () const noexcept -> Size override;

        public:
            /**
             * @brief Explicit Comparison Function with generic CDS/Object
             * @param object : Object cref = Constant Reference to an Object-derived instance
             * @exceptsafe
             * @return bool = true if objects are equal, false otherwise
             * @test tested in base class test
             */
            __CDS_NoDiscard auto equals ( Object const & object ) const noexcept -> bool override;

        protected:
            /**
             * @brief Default Constructor
             * @exceptsafe
             * @test tested in base class test
             */
            constexpr Collection () noexcept = default;

        protected:
            constexpr Collection (
                    Collection const & collection
            ) noexcept;

        protected:
            constexpr Collection (
                    Collection && collection
            ) noexcept;

        public:
            /**
             * @brief Default Destructor
             * @exceptsafe
             * @test tested in base class test
             */
            __CDS_cpplang_ConstexprDestructor ~Collection() noexcept override = default;

        public:
            /**
             * @brief Function used to clear the collection, removing all elements from it
             * @exceptsafe
             * @test tested in base class test
             */
            virtual auto clear () noexcept -> void = 0;

        public:
            /**
             * @brief Function used to acquire the number of elements in the collection
             * @exceptsafe
             * @return Size = number of elements inside the collection
             * @test tested in base class test
             */
            __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto size () const noexcept -> Size;

        public:
            /**
             * @brief Function used to check if the collection does not contain any elements ( is empty )
             * @exceptsafe
             * @return bool = true if the collection is empty ( does not contain any elements ), false otherwise
             * @test tested in base class test
             */
            __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto empty () const noexcept -> bool;

        public:
            /**
             * @brief Function used to check if the collection contains the requested element. Equivalent to collection.findFirst ( element ) != collection.end()
             * @param element : ElementType cref = Constant Reference to the element to be found in the collection
             * @return bool = true if the element exists in the collection, false otherwise
             * @test tested in base class test
             */
            virtual auto contains (
                    ElementType const & element
            ) const noexcept -> bool;

        public:
            /**
             * @brief Function used to check if the collection contains any of the requested elements.
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection of elements from which the caller collection's elements must have at least one match
             * @return bool = true if any element in the caller collection is found in the 'elements' collection, false otherwise
             * @test tested in base class test
             */
            auto containsAnyOf (
                    Collection < ElementType > const & elements
            ) const noexcept -> bool;

        public:
            /**
             * @brief Function used to check if the collection contains any element that is not of the requested elements.
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection of elements from which the caller collection's elements must have at least one non-match
             * @return bool = true if any element in the caller collection is not found in the 'elements' collection, false otherwise
             * @test tested in base class test
             */
            auto containsAnyNotOf (
                    Collection < ElementType > const & elements
            ) const noexcept -> bool;

        public:
            /**
             * @brief Function used to check if the collection contains all of the requested elements.
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection of elements from which the caller collection's elements must have every element matching
             * @return bool = true if all element in the caller collection are found in the 'elements' collection, false otherwise
             * @test tested in base class test
             */
            auto containsAllOf (
                    Collection < ElementType > const & elements
            ) const noexcept -> bool;

        public:
            /**
             * @brief Function used to check if the collection contains none of the requested elements.
             * @param elements : Collection < ElementType > cref = Constant Reference to the collection of elements from which the caller collection's elements must have every element non-matching
             * @return bool = true if no element in the caller collection are found in the 'elements' collection, false otherwise
             * @test tested in base class test
             */
            auto containsAllNotOf (
                    Collection < ElementType > const & elements
            ) const noexcept -> bool;

        public:
            /**
             * @brief Function used to check if the collection contains any of the requested elements.
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the list of elements from which the caller collection's elements must have at least one match
             * @return bool = true if any element in the caller collection is found in the 'elements' list, false otherwise
             * @test tested in base class test
             */
            auto containsAnyOf (
                    InitializerList const & elements
            ) const noexcept -> bool;

        public:
            /**
             * @brief Function used to check if the collection contains any element that is not of the requested elements.
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the list of elements from which the caller collection's elements must have at least one non-match
             * @return bool = true if any element in the caller collection is not found in the 'elements' list, false otherwise
             * @test tested in base class test
             */
            auto containsAnyNotOf (
                    InitializerList const & elements
            ) const noexcept -> bool;

        public:
            /**
             * @brief Function used to check if the collection contains all of the requested elements.
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the list of elements from which the caller collection's elements must have every element matching
             * @return bool = true if all element in the caller collection are found in the 'elements' list, false otherwise
             * @test tested in base class test
             */
            auto containsAllOf (
                    InitializerList const & elements
            ) const noexcept -> bool;

        public:
            /**
             * @brief Function used to check if the collection contains none of the requested elements.
             * @param elements : Collection < ElementType > :: InitializerList cref = Constant Reference to the list of elements from which the caller collection's elements must have every element non-matching
             * @return bool = true if no element in the caller collection are found in the 'elements' list, false otherwise
             * @test tested in base class test
             */
            auto containsAllNotOf (
                    InitializerList const & elements
            ) const noexcept -> bool;

        public:
            /**
             * @brief Function used to add an element to the collection via copy ( construction of new instance ). Only used if element is copyConstructible ( has copy ctor )
             * @tparam __VElementType alias for __ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param element : ElementType cref = Constant Reference to the element to copy and add into the collection
             * @exceptsafe if ElementType copy constructor is exceptsafe
             * @test tested in base class test
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto add (
                    ElementType const & element
            ) noexcept ( noexcept ( ElementType ( element ) ) ) -> void;

        public:
            /**
             * @brief Function used to add an element to the collection via move ( moving of the received instance ). Only used if element is moveConstructible ( has move ctor )
             * @tparam __VElementType alias for __ElementType, used to enable the function using sfinae to avoid instantiation errors
             * @param element : ElementType mref = Move Reference to the element to move into the collection
             * @exceptsafe if ElementType move constructor is exceptsafe
             * @test tested in base class test
             */
            template < typename __VElementType = __ElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto add (
                    ElementType && element
            ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> void;

        public:
            /**
             * @brief Function used to add a pack of elements to the collection via available means ( conversion -> copy / move ). Given values are required to be convertible to ElementType
             * @tparam __ArgumentTypes pack of types, representing the types of each of the given parameters, each must be convertible to ElementType
             * @param arguments : ArgumentTypes fref = Pack of Forwarding References to the given elements / values
             * @exceptsafe
             * @test tested in base class test
             */
            template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
            auto addAll (
                    __ArgumentTypes && ... arguments
            ) noexcept -> void;

        public:
            /**
             * @brief Function used to add all the elements from a given collection to this collection, provided the type of the current collection is copy constructible and the given collection's element types are convertible to this collection's element types
             * @tparam __OtherElementType the other collection's element type
             * @tparam __VElementType alias for __ElementType used for sfinae enable
             * @param otherCollection : Collection < R > cref = Constant Reference to the collection to acquire the values from
             * @exceptsafe
             * @test tested in base class test
             */
            template < typename __OtherElementType, typename __VElementType = __ElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () || meta :: isConvertible < __OtherElementType, __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto addAllOf (
                    Collection < __OtherElementType > const & otherCollection
            ) noexcept -> void;

        protected:
            /**
             * @brief Function used in Collection :: add implementation, called to acquire a pointer to place the new object at
             * @param referenceElement : ElementType cref = Constant Reference to the element to be added, as a reference, if implementation requires specific placement
             * @exceptsafe
             * @return ElementType ptr = a pointer to an ElementType.
             * @test tested in base class test
             */
            virtual auto pNewInsert (
                    ElementType const & referenceElement
            ) noexcept -> ElementType * = 0;

        protected:
            /**
             * @brief Function used in Collection :: add implementation, called after storage of new value
             * @exceptsafe
             * @test tested in base class test
             */
            virtual auto pNewInsertPost () noexcept -> void;
        };
        template < template < typename ... > class __CollectionType, typename ... __ArgumentTypes, typename __Common = meta :: Common < __ArgumentTypes ... > > // NOLINT(bugprone-reserved-identifier)
        auto collectionOf (
                __ArgumentTypes && ... values
        ) noexcept -> __CollectionType < __Common >;

    }
}

/// definition of Collection < T > :: DelegateIteratorRequestType
#include "collection/DelegateIteratorRequestType.hpp"

/// definition of Collection < T > :: AbstractDelegateIterator
#include "collection/AbstractDelegateIterator.hpp"

/// definition of Collection < T > :: DelegateConstIterator
#include "collection/DelegateConstIterator.hpp"

/// definition of Collection < T > :: AbstractIterator
#include "collection/AbstractIterator.hpp"

/// definition of Collection < T > :: ConstIterator
#include "collection/ConstIterator.hpp"

/// definition of Collection < T > :: ConstReverseIterator
#include "collection/ConstReverseIterator.hpp"


/// implementation of Collection < T > :: AbstractDelegateIterator functions
#include "collection/impl/AbstractDelegateIterator.hpp"

/// implementation of Collection < T > :: DelegateConstIterator functions
#include "collection/impl/DelegateConstIterator.hpp"

/// implementation of Collection < T > :: AbstractIterator functions
#include "collection/impl/AbstractIterator.hpp"

/// implementation of Collection < T > :: ConstIterator functions
#include "collection/impl/ConstIterator.hpp"

/// implementation of Collection < T > :: ConstReverseIterator functions
#include "collection/impl/ConstReverseIterator.hpp"


/// implementation of Collection < T > functions
#include "collection/impl/Collection.hpp"


#endif // __CDS_EX_COLLECTION_HPP__
