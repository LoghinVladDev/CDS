//
// Created by loghin on 4/24/2022.
//

#ifndef __CDS_EX_COLLECTION_HPP__
#define __CDS_EX_COLLECTION_HPP__

#include <CDS/std-types>
#include <CDS/experimental/Object>
#include <CDS/experimental/meta/TypeTraits>
#include <CDS/Concepts>
#include <CDS/Function>
#include <CDS/smartPointers/UniquePointer>
#include <CDS/smartPointers/ForeignPointer>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

    namespace experimental {

        /**
         * @class Abstract Object representing any Iterable Container of given elements of type
         * @tparam T type of elements contained into Collection
         * @test tested in collection/CollectionTest
         */
        template < typename T >
        class Collection : public Object {
        public:

            /**
             * @typedef Alias for T, the type of the contained elements, publicly accessible, useful in sfinae statements - decltype ( Collection ) :: ElementType
             */
            using ElementType = T;

        protected:
            /**
             * @typedef Alias for std :: initializer_list < T > or std :: initializer_list < ElementType >
             */
            using InitializerList = std :: initializer_list < T >;

        protected:
            /**
             * @interface An Iterator Delegate represents the actual implementation of the iterator done by the derived classes. The Abstract Delegate Iterator is the base used by the Iterator bases
             */
            class AbstractDelegateIterator;

        protected:
            /**
             * @class The base class for Iterator types, mutable or immutable. It is the wrapper over the AbstractDelegateIterator, acquired from derived classes implementation
             */
            class DelegateConstIterator;

        protected:
            /**
             * @class The base class for Iterator types, mutable or immutable. It is the wrapper over the AbstractDelegateIterator, acquired from derived classes implementation
             */
            class AbstractIterator;

        protected:
            /**
             * @enum The types of delegate iterator requests the Collection Base Object can make to its Derivated Objects when acquiring an Iterator Delegate Implementation
             */
            enum class DelegateIteratorRequestType;

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
             * @tparam Predicate the type of the given predicate. Must refer to a callable object, whose call is compatible with bool ( Decay < ElementType > )
             * @param count : Size = maximum number of elements to remove
             * @param predicate : Predicate cref = Constant Reference to a callable function, lambda or object, compatible with the bool ( Decay < ElementType > ) signature
             * @exceptsafe if predicate is exceptsafe
             * @return Size = number of removed elements
             * @test tested in the class test
             */
            template < typename Predicate >
            auto remove (
                    Size                count,
                    Predicate   const & predicate
            ) noexcept ( noexcept ( ( meta :: valueOf < Predicate > () ) ( meta :: referenceOf < ElementType > () ) ) ) -> Size;

        public:
            /**
             * @brief Function used to remove the first element that matches the validation of a given predicate ( bool ( ElementType ) function )
             * @tparam Predicate the type of the given predicate. Must refer to a callable object, whose call is compatible with bool ( Decay < ElementType > )
             * @param predicate : Predicate cref = Constant Reference to a callable function, lambda or object, compatible with the bool ( Decay < ElementType > ) signature
             * @exceptsafe if predicate is exceptsafe
             * @return bool = true if one element was removed, false otherwise
             * @test tested in the class test
             */
            template < typename Predicate >
            auto removeFirst (
                    Predicate const & predicate
            ) noexcept -> bool;

        public:
            template < typename Predicate >
            auto removeLast (
                    Predicate const &
            ) noexcept -> bool;
        public:
            template < typename Predicate >
            auto removeAll (
                    Predicate const &
            ) noexcept -> Size;

        public:
            auto remove (
                    Size,
                    ElementType const &
            ) noexcept -> Size;
        public:
            auto removeFirst (
                    ElementType const &
            ) noexcept -> bool;
        public:
            auto removeLast (
                    ElementType const &
            ) noexcept -> bool;
        public:
            auto removeAll (
                    ElementType const &
            ) noexcept -> Size;

        public:
            auto removeOf (
                    Size,
                    Collection < T > const &
            ) noexcept -> Size;
        public:
            auto removeFirstOf (
                    Collection < T > const &
            ) noexcept -> bool;
        public:
            auto removeLastOf (
                    Collection < T > const &
            ) noexcept -> bool;
        public:
            auto removeAllOf (
                    Collection < T > const &
            ) noexcept -> Size;

        public:
            auto removeNotOf (
                    Size,
                    Collection < T > const &
            ) noexcept -> Size;
        public:
            auto removeFirstNotOf (
                    Collection < T > const &
            ) noexcept -> bool;
        public:
            auto removeLastNotOf (
                    Collection < T > const &
            ) noexcept -> bool;
        public:
            auto removeAllNotOf (
                    Collection < T > const &
            ) noexcept -> Size;

        public:
            auto removeOf (
                    Size,
                    InitializerList const &
            ) noexcept -> Size;
        public:
            auto removeFirstOf (
                    InitializerList const &
            ) noexcept -> bool;
        public:
            auto removeLastOf (
                    InitializerList const &
            ) noexcept -> bool;
        public:
            auto removeAllOf (
                    InitializerList const &
            ) noexcept -> Size;

        public:
            auto removeNotOf (
                    Size,
                    InitializerList const &
            ) noexcept -> Size;
        public:
            auto removeFirstNotOf (
                    InitializerList const &
            ) noexcept -> bool;
        public:
            auto removeLastNotOf (
                    InitializerList const &
            ) noexcept -> bool;
        public:
            auto removeAllNotOf (
                    InitializerList const &
            ) noexcept -> Size;

        public:
            template < typename Action >
            auto forEach (
                    Action const &
            ) const noexcept ( noexcept ( meta :: valueOf < Action > () ( meta :: referenceOf < ElementType const > () ) ) ) -> void;
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto some (
                    Size                count,
                    Predicate   const & predicate = [] ( ElementType const & ) noexcept -> bool {
                        return true;
                    }
            ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto atLeast (
                    Size                count,
                    Predicate   const & predicate = [] ( ElementType const & ) noexcept -> bool {
                        return true;
                    }
            ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto atMost (
                    Size                count,
                    Predicate   const & predicate = [] ( ElementType const & ) noexcept -> bool {
                        return true;
                    }
            ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto moreThan (
                    Size                count,
                    Predicate   const & predicate = [] ( ElementType const & ) noexcept -> bool {
                        return true;
                    }
            ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto lessThan (
                    Size                count,
                    Predicate   const & predicate = [] ( ElementType const & ) noexcept -> bool {
                        return true;
                    }
            ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto count (
                    Predicate   const & predicate = [] ( ElementType const & ) noexcept -> bool {
                        return true;
                    }
            ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> Size;
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto any (
                    Predicate   const & predicate = [] ( ElementType const & ) noexcept -> bool {
                        return true;
                    }
            ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;
        public:
            template < typename Predicate = Function < bool ( ElementType const & ) > >
            auto all (
                    Predicate   const & predicate = [] ( ElementType const & ) noexcept -> bool {
                        return true;
                    }
            ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> bool;

        public:
            template < template < typename ... > typename CollectionType >
            auto find (
                    Size,
                    ElementType                         const &,
                    CollectionType < ConstIterator >          &
            ) const noexcept -> CollectionType < ConstIterator > &;
        public:
            template < template < typename ... > typename CollectionType >
            auto find (
                    Size,
                    ElementType const &
            ) const noexcept -> CollectionType < ConstIterator >;
        public:
            auto findFirst (
                    ElementType const &
            ) const noexcept -> ConstIterator;
        public:
            auto findLast (
                    ElementType const &
            ) const noexcept -> ConstIterator;
        public:
            template < template < typename ... > typename CollectionType >
            auto findAll (
                    ElementType                         const &,
                    CollectionType < ConstIterator >          &
            ) const noexcept -> CollectionType < ConstIterator > &;
        public:
            template < template < typename ... > typename CollectionType >
            auto findAll (
                    ElementType const &
            ) const noexcept -> CollectionType < ConstIterator >;

        public:
            template < template < typename ... > typename CollectionType >
            auto findOf (
                    Size,
                    Collection < T >                    const &,
                    CollectionType < ConstIterator >          &
            ) const noexcept -> CollectionType < ConstIterator > &;
        public:
            template < template < typename ... > typename CollectionType >
            auto findOf (
                    Size,
                    Collection < T > const &
            ) const noexcept -> CollectionType < ConstIterator >;
        public:
            auto findFirstOf (
                    Collection < T > const &
            ) const noexcept -> ConstIterator;
        public:
            auto findLastOf (
                    Collection < T > const &
            ) const noexcept -> ConstIterator;
        public:
            template < template < typename ... > typename CollectionType >
            auto findAllOf (
                    Collection < T >                    const &,
                    CollectionType < ConstIterator >          &
            ) const noexcept -> CollectionType < ConstIterator > &;
        public:
            template < template < typename ... > typename CollectionType >
            auto findAllOf (
                    Collection < T > const &
            ) const noexcept -> CollectionType < ConstIterator >;

        public:
            template < template < typename ... > typename CollectionType >
            auto findNotOf (
                    Size,
                    Collection < T >                    const &,
                    CollectionType < ConstIterator >          &
            ) const noexcept -> CollectionType < ConstIterator > &;
        public:
            template < template < typename ... > typename CollectionType >
            auto findNotOf (
                    Size,
                    Collection < T > const &
            ) const noexcept -> CollectionType < ConstIterator >;
        public:
            auto findFirstNotOf (
                    Collection < T > const &
            ) const noexcept -> ConstIterator;
        public:
            auto findLastNotOf (
                    Collection < T > const &
            ) const noexcept -> ConstIterator;
        public:
            template < template < typename ... > typename CollectionType >
            auto findAllNotOf (
                    Collection < T >                    const &,
                    CollectionType < ConstIterator >          &
            ) const noexcept -> CollectionType < ConstIterator > &;
        public:
            template < template < typename ... > typename CollectionType >
            auto findAllNotOf (
                    Collection < T > const &
            ) const noexcept -> CollectionType < ConstIterator >;

        public:
            template < template < typename ... > typename CollectionType >
            auto findOf (
                    Size,
                    InitializerList                     const &,
                    CollectionType < ConstIterator >          &
            ) const noexcept -> CollectionType < ConstIterator > &;
        public:
            template < template < typename ... > typename CollectionType >
            auto findOf (
                    Size,
                    InitializerList const &
            ) const noexcept -> CollectionType < ConstIterator >;
        public:
            auto findFirstOf (
                    InitializerList const &
            ) const noexcept -> ConstIterator;
        public:
            auto findLastOf (
                    InitializerList const &
            ) const noexcept -> ConstIterator;
        public:
            template < template < typename ... > typename CollectionType >
            auto findAllOf (
                    InitializerList                     const &,
                    CollectionType < ConstIterator >          &
            ) const noexcept -> CollectionType < ConstIterator > &;
        public:
            template < template < typename ... > typename CollectionType >
            auto findAllOf (
                    InitializerList const &
            ) const noexcept -> CollectionType < ConstIterator >;

        public:
            template < template < typename ... > typename CollectionType >
            auto findNotOf (
                    Size,
                    InitializerList                     const &,
                    CollectionType < ConstIterator >          &
            ) const noexcept -> CollectionType < ConstIterator > &;
        public:
            template < template < typename ... > typename CollectionType >
            auto findNotOf (
                    Size,
                    InitializerList const &
            ) const noexcept -> CollectionType < ConstIterator >;
        public:
            auto findFirstNotOf (
                    InitializerList const &
            ) const noexcept -> ConstIterator;
        public:
            auto findLastNotOf (
                    InitializerList const &
            ) const noexcept -> ConstIterator;
        public:
            template < template < typename ... > typename CollectionType >
            auto findAllNotOf (
                    InitializerList                     const &,
                    CollectionType < ConstIterator >          &
            ) const noexcept -> CollectionType < ConstIterator > &;
        public:
            template < template < typename ... > typename CollectionType >
            auto findAllNotOf (
                    InitializerList const &
            ) const noexcept -> CollectionType < ConstIterator >;

        public:
            template < template < typename ... > typename CollectionType, typename Predicate >
            auto find (
                    Size,
                    Predicate                           const &,
                    CollectionType < ConstIterator >          &
            ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> CollectionType < ConstIterator > &;
        public:
            template < template < typename ... > typename CollectionType, typename Predicate >
            auto find (
                    Size,
                    Predicate const &
            ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> CollectionType < ConstIterator >;
        public:
            template < typename Predicate >
            auto findFirst (
                    Predicate const &
            ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> ConstIterator;
        public:
            template < typename Predicate >
            auto findLast (
                    Predicate const &
            ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> ConstIterator;
        public:
            template < template < typename ... > typename CollectionType, typename Predicate >
            auto findAll (
                    Predicate                           const &,
                    CollectionType < ConstIterator >          &
            ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> CollectionType < ConstIterator > &;
        public:
            template < template < typename ... > typename CollectionType, typename Predicate >
            auto findAll (
                    Predicate const &
            ) const noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType const > () ) ) ) -> CollectionType < ConstIterator >;

        public:
            __CDS_cpplang_ConstexprPureAbstract __CDS_explicit(false) operator bool () const noexcept; // NOLINT(google-explicit-constructor)

        public:
            __CDS_NoDiscard auto toString () const noexcept -> String override = 0;
        public:
            __CDS_NoDiscard auto hash () const noexcept -> Index override;
        public:
            __CDS_NoDiscard auto equals ( Object const & ) const noexcept -> bool override;

        protected:
            constexpr Collection () noexcept = default;
        public:
            ~Collection() noexcept override = default;

        public:
            virtual auto clear () noexcept -> void = 0;
        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto size () const noexcept -> Size = 0;
        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto empty () const noexcept -> bool;
        public:
            virtual auto contains (
                    ElementType const &
            ) const noexcept -> bool;

        public:
            auto containsAnyOf (
                    Collection < ElementType > const &
            ) const noexcept -> bool;
        public:
            auto containsAnyNotOf (
                    Collection < ElementType > const &
            ) const noexcept -> bool;
        public:
            auto containsAllOf (
                    Collection < ElementType > const &
            ) const noexcept -> bool;
        public:
            auto containsAllNotOf (
                    Collection < ElementType > const &
            ) const noexcept -> bool;

        public:
            auto containsAnyOf (
                    InitializerList const &
            ) const noexcept -> bool;
        public:
            auto containsAnyNotOf (
                    InitializerList const &
            ) const noexcept -> bool;
        public:
            auto containsAllOf (
                    InitializerList const &
            ) const noexcept -> bool;
        public:
            auto containsAllNotOf (
                    InitializerList const &
            ) const noexcept -> bool;

        public:
            template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
            auto add (
                    ElementType const &
            ) noexcept -> void;
        public:
            template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
            auto add (
                    ElementType &&
            ) noexcept -> void;

        public:
            template < typename ... ArgumentTypes >
            auto addAll (
                    ArgumentTypes && ...
            ) noexcept -> void;

        public:
            template < typename R, typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () || meta :: isConvertible < R, V > () > = 0 >
            auto addAllOf (
                    Collection < R > const &
            ) noexcept -> void;

        protected:
            virtual auto pNewInsert () noexcept -> ElementType * & = 0;
        protected:
            virtual auto pNewInsertPost () noexcept -> void;
        };

        template < template < typename ... > typename CollectionType, typename ... ArgumentTypes, typename Common = meta :: Common < ArgumentTypes ... > >
        auto collectionOf ( ArgumentTypes && ... ) noexcept -> CollectionType < Common >;

    }
}

#include "collection/DelegateIteratorRequestType.hpp"
#include "collection/AbstractDelegateIterator.hpp"
#include "collection/DelegateConstIterator.hpp"
#include "collection/AbstractIterator.hpp"
#include "collection/ConstIterator.hpp"
#include "collection/ConstReverseIterator.hpp"

#include "collection/impl/AbstractDelegateIterator.hpp"
#include "collection/impl/DelegateConstIterator.hpp"
#include "collection/impl/AbstractIterator.hpp"
#include "collection/impl/ConstIterator.hpp"
#include "collection/impl/ConstReverseIterator.hpp"

#include "collection/impl/Collection.hpp"

#endif // __CDS_EX_COLLECTION_HPP__
