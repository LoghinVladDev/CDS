//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_EX_COLLECTION_HPP__
#define __CDS_EX_COLLECTION_HPP__

#include <CDS/Object>

#include <CDS/Comparator>
#include "../../shared/memory/PrimitiveAllocation.hpp"
#include "collection/CollectionFunctions.hpp"
#include "collection/CollectionConstructs.hpp"

#include "shared/delegateIterator/ForwardDelegateWrapperIterator.hpp"
#include "shared/delegateIterableCommunication/channel/DelegateIterableChannel.hpp"
#include "shared/delegateIterableCommunication/client/DelegateForwardConstIterableClient.hpp"
#include "shared/delegateIterableCommunication/client/AbstractConstIteratorRemoveClient.hpp"

#include "shared/iterable/IterableContainsOf.hpp"
#include "shared/iterable/IterableImmutableFindOf.hpp"
#include "shared/iterable/IterableImmutableFindByPredicate.hpp"
#include "shared/iterable/IterableRemoveOf.hpp"
#include "shared/iterable/IterableRemoveByPredicate.hpp"
#include "shared/iterable/IterableImmutableStatements.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class Collection :
                public __hidden :: __impl :: __DelegateIterableChannel <
                        Collection < __ElementType >,
                        __ElementType
                >,
                public __hidden :: __impl :: __DelegateForwardConstIterableClient <
                        Collection < __ElementType >,
                        __ElementType,
                        false
                >,
                public __hidden :: __impl :: __AbstractConstIteratorRemoveClient <
                        Collection < __ElementType >,
                        __ElementType
                >,
                public __hidden :: __impl :: __IterableContainsOf <
                        Collection < __ElementType >,
                        __ElementType,
                        Collection < __ElementType >
                >,
                public __hidden :: __impl :: __IterableContainsOf <
                        Collection < __ElementType >,
                        __ElementType,
                        std :: initializer_list < __ElementType >
                >,
                public __hidden :: __impl :: __IterableImmutableFindOf <
                        Collection < __ElementType >,
                        __ElementType,
                        typename __hidden :: __impl :: __DelegateForwardConstIterableClient < Collection < __ElementType >, __ElementType, false > :: ConstIterator,
                        Collection < __ElementType >,
                        __hidden :: __impl :: __collectionContains < __ElementType >
                >,
                public __hidden :: __impl :: __IterableImmutableFindOf <
                        Collection < __ElementType >,
                        __ElementType,
                        typename __hidden :: __impl :: __DelegateForwardConstIterableClient < Collection < __ElementType >, __ElementType, false > :: ConstIterator,
                        std :: initializer_list < __ElementType >,
                        __hidden :: __impl :: __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                >,
                public __hidden :: __impl :: __IterableImmutableFindByPredicate <
                        Collection < __ElementType >,
                        __ElementType,
                        typename __hidden :: __impl :: __DelegateForwardConstIterableClient < Collection < __ElementType >, __ElementType, false > :: ConstIterator
                >,
                public __hidden :: __impl :: __IterableRemoveOf <
                        Collection < __ElementType >,
                        __ElementType,
                        Collection < __ElementType >,
                        __hidden :: __impl :: __collectionContains < __ElementType >
                >,
                public __hidden :: __impl :: __IterableRemoveOf <
                        Collection < __ElementType >,
                        __ElementType,
                        std :: initializer_list < __ElementType >,
                        __hidden :: __impl :: __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                >,
                public __hidden :: __impl :: __IterableRemoveByPredicate <
                        Collection < __ElementType >,
                        __ElementType
                >,
                public __hidden :: __impl :: __IterableImmutableStatements <
                        Collection < __ElementType >,
                        __ElementType
                >,
                protected __hidden :: __impl :: __CollectionFunctions <
                        __ElementType,
                        FunctionComparator < __ElementType, & cds :: meta :: equals < __ElementType > >
                > {

        protected:
            using DelegateIterableChannel =
                    __hidden :: __impl :: __DelegateIterableChannel <
                            Collection < __ElementType >,
                            __ElementType
                    >;

        protected:
            using DelegateForwardConstIterableClient =
                    __hidden :: __impl :: __DelegateForwardConstIterableClient <
                            Collection < __ElementType >,
                            __ElementType,
                            false
                    >;

        protected:
            using AbstractConstIteratorRemoveClient =
                    __hidden :: __impl :: __AbstractConstIteratorRemoveClient <
                            Collection < __ElementType >,
                            __ElementType
                    >;

        protected:
            using IterableRemoveByPredicate =
                    __hidden :: __impl :: __IterableRemoveByPredicate <
                            Collection < __ElementType >,
                            __ElementType
                    >;

        protected:
            using IterableImmutableStatements =
                    __hidden :: __impl :: __IterableImmutableStatements <
                            Collection < __ElementType >,
                            __ElementType
                    >;

        protected:
            using IterableContainsOfColleciton =
                    __hidden :: __impl :: __IterableContainsOf <
                            Collection < __ElementType >,
                            __ElementType,
                            Collection < __ElementType >
                    >;

        protected:
            using IterableContainsOfInitializerList =
                    __hidden :: __impl :: __IterableContainsOf <
                            Collection < __ElementType >,
                            __ElementType,
                            std :: initializer_list < __ElementType >
                    >;

        protected:
            using IterableImmutableFindOfColleciton =
                    __hidden :: __impl :: __IterableImmutableFindOf <
                            Collection < __ElementType >,
                            __ElementType,
                            typename __hidden :: __impl :: __DelegateForwardConstIterableClient < Collection < __ElementType >, __ElementType, false > :: ConstIterator,
                            Collection < __ElementType >,
                            __hidden :: __impl :: __collectionContains < __ElementType >
                    >;

        protected:
            using IterableImmutableFindOfInitializerList =
                    __hidden :: __impl :: __IterableImmutableFindOf <
                            Collection < __ElementType >,
                            __ElementType,
                            typename __hidden :: __impl :: __DelegateForwardConstIterableClient < Collection < __ElementType >, __ElementType, false > :: ConstIterator,
                            std :: initializer_list < __ElementType >,
                            __hidden :: __impl :: __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                    >;

        protected:
            using IterableImmutableFindByPredicate =
                    __hidden :: __impl :: __IterableImmutableFindByPredicate <
                            Collection < __ElementType >,
                            __ElementType,
                            typename __hidden :: __impl :: __DelegateForwardConstIterableClient < Collection < __ElementType >, __ElementType, false > :: ConstIterator
                    >;

        protected:
            using IterableRemoveOfColleciton =
                    __hidden :: __impl :: __IterableRemoveOf <
                            Collection < __ElementType >,
                            __ElementType,
                            Collection < __ElementType >,
                            __hidden :: __impl :: __collectionContains < __ElementType >
                    >;

        protected:
            using IterableRemoveOfInitializerList =
                    __hidden :: __impl :: __IterableRemoveOf <
                            Collection < __ElementType >,
                            __ElementType,
                            std :: initializer_list < __ElementType >,
                            __hidden :: __impl :: __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                    >;

        public:
            using ElementType   = __ElementType;

        public:
            constexpr Collection () noexcept;

        public:
            constexpr Collection (
                    Collection const & collection
            ) noexcept;

        public:
            constexpr Collection (
                    Collection && collection
            ) noexcept;

        public:
            __CDS_cpplang_VirtualConstexpr ~Collection() noexcept;

        public: using typename DelegateForwardConstIterableClient :: ConstIterator;

        public: using DelegateForwardConstIterableClient :: begin;
        public: using DelegateForwardConstIterableClient :: end;
        public: using DelegateForwardConstIterableClient :: cbegin;
        public: using DelegateForwardConstIterableClient :: cend;

        public: using AbstractConstIteratorRemoveClient :: remove;

        public: using IterableRemoveByPredicate :: removeIf;
        public: using IterableRemoveByPredicate :: removeFirstIf;
        public: using IterableRemoveByPredicate :: removeLastIf;
        public: using IterableRemoveByPredicate :: removeAllIf;

        public: using IterableImmutableStatements :: forEach;
        public: using IterableImmutableStatements :: some;
        public: using IterableImmutableStatements :: atLeast;
        public: using IterableImmutableStatements :: atMost;
        public: using IterableImmutableStatements :: moreThan;
        public: using IterableImmutableStatements :: fewerThan;
        public: using IterableImmutableStatements :: count;
        public: using IterableImmutableStatements :: any;
        public: using IterableImmutableStatements :: all;
        public: using IterableImmutableStatements :: none;

        public: using IterableRemoveOfColleciton :: removeOf;
        public: using IterableRemoveOfColleciton :: removeFirstOf;
        public: using IterableRemoveOfColleciton :: removeLastOf;
        public: using IterableRemoveOfColleciton :: removeAllOf;
        public: using IterableRemoveOfColleciton :: removeNotOf;
        public: using IterableRemoveOfColleciton :: removeFirstNotOf;
        public: using IterableRemoveOfColleciton :: removeLastNotOf;
        public: using IterableRemoveOfColleciton :: removeAllNotOf;

        public: using IterableRemoveOfInitializerList :: removeOf;
        public: using IterableRemoveOfInitializerList :: removeFirstOf;
        public: using IterableRemoveOfInitializerList :: removeLastOf;
        public: using IterableRemoveOfInitializerList :: removeAllOf;
        public: using IterableRemoveOfInitializerList :: removeNotOf;
        public: using IterableRemoveOfInitializerList :: removeFirstNotOf;
        public: using IterableRemoveOfInitializerList :: removeLastNotOf;
        public: using IterableRemoveOfInitializerList :: removeAllNotOf;

        public: using IterableContainsOfColleciton :: containsAnyOf;
        public: using IterableContainsOfColleciton :: containsAllOf;
        public: using IterableContainsOfColleciton :: containsAnyNotOf;
        public: using IterableContainsOfColleciton :: containsAllNotOf;

        public: using IterableContainsOfInitializerList :: containsAnyOf;
        public: using IterableContainsOfInitializerList :: containsAllOf;
        public: using IterableContainsOfInitializerList :: containsAnyNotOf;
        public: using IterableContainsOfInitializerList :: containsAllNotOf;

        public: using IterableImmutableFindByPredicate :: findThat;
        public: using IterableImmutableFindByPredicate :: findFirstThat;
        public: using IterableImmutableFindByPredicate :: findLastThat;
        public: using IterableImmutableFindByPredicate :: findAllThat;

        public: using IterableImmutableFindOfColleciton :: findOf;
        public: using IterableImmutableFindOfColleciton :: findFirstOf;
        public: using IterableImmutableFindOfColleciton :: findLastOf;
        public: using IterableImmutableFindOfColleciton :: findAllOf;
        public: using IterableImmutableFindOfColleciton :: findNotOf;
        public: using IterableImmutableFindOfColleciton :: findFirstNotOf;
        public: using IterableImmutableFindOfColleciton :: findLastNotOf;
        public: using IterableImmutableFindOfColleciton :: findAllNotOf;

        public: using IterableImmutableFindOfInitializerList :: findOf;
        public: using IterableImmutableFindOfInitializerList :: findFirstOf;
        public: using IterableImmutableFindOfInitializerList :: findLastOf;
        public: using IterableImmutableFindOfInitializerList :: findAllOf;
        public: using IterableImmutableFindOfInitializerList :: findNotOf;
        public: using IterableImmutableFindOfInitializerList :: findFirstNotOf;
        public: using IterableImmutableFindOfInitializerList :: findLastNotOf;
        public: using IterableImmutableFindOfInitializerList :: findAllNotOf;


        public:
            __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto size () const noexcept -> Size;

        public:
            __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto empty () const noexcept -> bool;

        public:
            __CDS_cpplang_VirtualConstexpr __CDS_Implicit operator bool () const noexcept; // NOLINT(google-explicit-constructor)

        public:
            __CDS_NoDiscard auto toString () const noexcept -> String override;

        public:
            __CDS_NoDiscard auto hash () const noexcept -> Size override;

        public:
            __CDS_NoDiscard auto equals (
                    Object const & object
            ) const noexcept -> bool override;

        public:
            virtual auto clear () noexcept -> void = 0;

        public:
            virtual auto remove (
                    ElementType const & element
            ) noexcept -> bool;

        public:
            __CDS_NoDiscard virtual auto find (
                    ElementType const & element
            ) const noexcept -> ConstIterator;

        public:
            __CDS_NoDiscard virtual auto contains (
                    ElementType const & element
            ) const noexcept -> bool;

        public:
            template < typename __ForwardElementType > // NOLINT(bugprone-reserved-identifier)
            auto add (
                    __ForwardElementType && element
            ) noexcept ( noexcept ( ElementType ( std :: forward < __ForwardElementType > ( element ) ) ) ) -> ElementType const &;

        public:
            template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
            auto addAll (
                    __ArgumentTypes && ... values
            ) noexcept -> void;

        public:
            template < typename __IterableType > // NOLINT(bugprone-reserved-identifier)
            auto addAllOf (
                    __IterableType const & iterableType
            ) noexcept -> void;

        protected:
            virtual auto __c_new ( // NOLINT(bugprone-reserved-identifier)
                    ElementType const & referenceElement,
                    ElementType      ** ppNewLocation
            ) noexcept -> bool = 0;
        };


    }
}

#include "collection/impl/CollectionConstructs.hpp"
#include "collection/impl/CollectionFunctions.hpp"

#include "shared/delegateIterator/impl/ForwardDelegateWrapperIterator.hpp"
#include "shared/delegateIterableCommunication/channel/impl/DelegateIterableChannel.hpp"
#include "shared/delegateIterableCommunication/client/impl/DelegateForwardConstIterableClient.hpp"
#include "shared/delegateIterableCommunication/client/impl/AbstractConstIteratorRemoveClient.hpp"

#include "shared/iterable/impl/IterableContainsOf.hpp"
#include "shared/iterable/impl/IterableImmutableFindOf.hpp"
#include "shared/iterable/impl/IterableImmutableFindByPredicate.hpp"
#include "shared/iterable/impl/IterableRemoveOf.hpp"
#include "shared/iterable/impl/IterableRemoveByPredicate.hpp"
#include "shared/iterable/impl/IterableImmutableStatements.hpp"

#include "collection/impl/Collection.hpp"

#endif // __CDS_EX_COLLECTION_HPP__
