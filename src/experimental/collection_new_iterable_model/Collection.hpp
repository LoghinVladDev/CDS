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

#include "shared/collectionInternalCommunication/channel/CollectionInternalCommunicationChannel.hpp"

#include "shared/collectionInternalCommunication/client/primitive/DelegateForwardConstIterablePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/ConstIteratorRemovePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/RandomInsertionPrimitiveClient.hpp"

#include "shared/collectionInternalCommunication/client/composite/ContainsOfCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/FindOfImmutableCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/FindByImmutableCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/RemoveOfCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/RemoveByCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/GenericImmutableStatementsCompositeClient.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class Collection :
                public __hidden :: __impl :: __CollectionInternalCommunicationChannel <
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
                public __hidden :: __impl :: __RandomInsertionClient <
                        Collection < __ElementType >,
                        __ElementType,
                        __ElementType const
                >,
                protected __hidden :: __impl :: __CollectionFunctions <
                        __ElementType,
                        FunctionComparator < __ElementType, & cds :: meta :: equals < __ElementType > >
                > {

        public:
            using ElementType   = __ElementType;

        protected:
            using CollectionInternalCommunicationChannel =
                    __hidden :: __impl :: __CollectionInternalCommunicationChannel <
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
            using IterableContainsOfCollection =
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
            using IterableImmutableFindOfCollection =
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
            using IterableRemoveOfCollection =
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

        protected:
            using RandomInsertionClient = __hidden :: __impl :: __RandomInsertionClient <
                            Collection < __ElementType >,
                            __ElementType,
                            __ElementType const
                    >;

        public:
            using typename DelegateForwardConstIterableClient :: ConstIterator;

        protected:
            constexpr Collection () noexcept;

        protected:
            constexpr Collection (
                    Collection const & collection
            ) noexcept;

        protected:
            constexpr Collection (
                    Collection && collection
            ) noexcept;

        public:
            __CDS_cpplang_ConstexprDestructor ~Collection() noexcept;

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

        public: using IterableRemoveOfCollection :: removeOf;
        public: using IterableRemoveOfCollection :: removeFirstOf;
        public: using IterableRemoveOfCollection :: removeLastOf;
        public: using IterableRemoveOfCollection :: removeAllOf;
        public: using IterableRemoveOfCollection :: removeNotOf;
        public: using IterableRemoveOfCollection :: removeFirstNotOf;
        public: using IterableRemoveOfCollection :: removeLastNotOf;
        public: using IterableRemoveOfCollection :: removeAllNotOf;

        public: using IterableRemoveOfInitializerList :: removeOf;
        public: using IterableRemoveOfInitializerList :: removeFirstOf;
        public: using IterableRemoveOfInitializerList :: removeLastOf;
        public: using IterableRemoveOfInitializerList :: removeAllOf;
        public: using IterableRemoveOfInitializerList :: removeNotOf;
        public: using IterableRemoveOfInitializerList :: removeFirstNotOf;
        public: using IterableRemoveOfInitializerList :: removeLastNotOf;
        public: using IterableRemoveOfInitializerList :: removeAllNotOf;

        public: using IterableContainsOfCollection :: containsAnyOf;
        public: using IterableContainsOfCollection :: containsAllOf;
        public: using IterableContainsOfCollection :: containsAnyNotOf;
        public: using IterableContainsOfCollection :: containsAllNotOf;

        public: using IterableContainsOfInitializerList :: containsAnyOf;
        public: using IterableContainsOfInitializerList :: containsAllOf;
        public: using IterableContainsOfInitializerList :: containsAnyNotOf;
        public: using IterableContainsOfInitializerList :: containsAllNotOf;

        public: using IterableImmutableFindByPredicate :: findThat;
        public: using IterableImmutableFindByPredicate :: findFirstThat;
        public: using IterableImmutableFindByPredicate :: findLastThat;
        public: using IterableImmutableFindByPredicate :: findAllThat;

        public: using IterableImmutableFindOfCollection :: findOf;
        public: using IterableImmutableFindOfCollection :: findFirstOf;
        public: using IterableImmutableFindOfCollection :: findLastOf;
        public: using IterableImmutableFindOfCollection :: findAllOf;
        public: using IterableImmutableFindOfCollection :: findNotOf;
        public: using IterableImmutableFindOfCollection :: findFirstNotOf;
        public: using IterableImmutableFindOfCollection :: findLastNotOf;
        public: using IterableImmutableFindOfCollection :: findAllNotOf;

        public: using IterableImmutableFindOfInitializerList :: findOf;
        public: using IterableImmutableFindOfInitializerList :: findFirstOf;
        public: using IterableImmutableFindOfInitializerList :: findLastOf;
        public: using IterableImmutableFindOfInitializerList :: findAllOf;
        public: using IterableImmutableFindOfInitializerList :: findNotOf;
        public: using IterableImmutableFindOfInitializerList :: findFirstNotOf;
        public: using IterableImmutableFindOfInitializerList :: findLastNotOf;
        public: using IterableImmutableFindOfInitializerList :: findAllNotOf;

        public: using RandomInsertionClient :: add;
        public: using RandomInsertionClient :: addAll;
        public: using RandomInsertionClient :: addAllOf;
        public: using RandomInsertionClient :: insert;
        public: using RandomInsertionClient :: insertAll;
        public: using RandomInsertionClient :: insertAllOf;


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

        };


    }
}

#include "collection/impl/CollectionConstructs.hpp"
#include "collection/impl/CollectionFunctions.hpp"

#include "shared/delegateIterator/impl/ForwardDelegateWrapperIterator.hpp"
#include "shared/collectionInternalCommunication/channel/impl/CollectionInternalCommunicationChannel.hpp"
#include "shared/collectionInternalCommunication/client/primitive/impl/DelegateForwardConstIterablePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/impl/ConstIteratorRemovePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/impl/RandomInsertionPrimitiveClient.hpp"

#include "shared/collectionInternalCommunication/client/composite/impl/ContainsOfCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/impl/FindOfImmutableCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/impl/FindByImmutableCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/impl/RemoveOfCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/impl/RemoveByCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/impl/GenericImmutableStatementsCompositeClient.hpp"

#include "collection/impl/Collection.hpp"

#endif // __CDS_EX_COLLECTION_HPP__
