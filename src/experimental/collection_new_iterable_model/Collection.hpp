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
                public __hidden :: __impl :: __DelegateForwardConstIterablePrimitiveClient <
                        Collection < __ElementType >,
                        __ElementType,
                        false
                >,
                public __hidden :: __impl :: __AbstractConstIteratorRemovePrimitiveClient <
                        Collection < __ElementType >,
                        __ElementType
                >,
                public __hidden :: __impl :: __RandomInsertionPrimitiveClient <
                        Collection < __ElementType >,
                        __ElementType,
                        __ElementType const
                >,
                public __hidden :: __impl :: __ContainsOfCompositeClient <
                        Collection < __ElementType >,
                        __ElementType,
                        Collection < __ElementType >
                >,
                public __hidden :: __impl :: __ContainsOfCompositeClient <
                        Collection < __ElementType >,
                        __ElementType,
                        std :: initializer_list < __ElementType >
                >,
                public __hidden :: __impl :: __FindOfImmutableCompositeClient <
                        Collection < __ElementType >,
                        __ElementType,
                        typename __hidden :: __impl :: __DelegateForwardConstIterablePrimitiveClient <
                                Collection < __ElementType >,
                                __ElementType,
                                false
                        > :: ConstIterator,
                        Collection < __ElementType >,
                        __hidden :: __impl :: __collectionContains < __ElementType >
                >,
                public __hidden :: __impl :: __FindOfImmutableCompositeClient <
                        Collection < __ElementType >,
                        __ElementType,
                        typename __hidden :: __impl :: __DelegateForwardConstIterablePrimitiveClient <
                                Collection < __ElementType >,
                                __ElementType,
                                false
                        > :: ConstIterator,
                        std :: initializer_list < __ElementType >,
                        __hidden :: __impl :: __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                >,
                public __hidden :: __impl :: __FindByImmutableCompositeClient <
                        Collection < __ElementType >,
                        __ElementType,
                        typename __hidden :: __impl :: __DelegateForwardConstIterablePrimitiveClient <
                                Collection < __ElementType >,
                                __ElementType,
                                false
                        > :: ConstIterator
                >,
                public __hidden :: __impl :: __RemoveOfCompositeClient <
                        Collection < __ElementType >,
                        __ElementType,
                        Collection < __ElementType >,
                        __hidden :: __impl :: __collectionContains < __ElementType >
                >,
                public __hidden :: __impl :: __RemoveOfCompositeClient <
                        Collection < __ElementType >,
                        __ElementType,
                        std :: initializer_list < __ElementType >,
                        __hidden :: __impl :: __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                >,
                public __hidden :: __impl :: __RemoveByCompositeClient <
                        Collection < __ElementType >,
                        __ElementType
                >,
                public __hidden :: __impl :: __GenericImmutableStatementsCompositeClient <
                        Collection < __ElementType >,
                        __ElementType
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
                    __hidden :: __impl :: __DelegateForwardConstIterablePrimitiveClient <
                            Collection < __ElementType >,
                            __ElementType,
                            false
                    >;

        protected:
            using AbstractConstIteratorRemoveClient =
                    __hidden :: __impl :: __AbstractConstIteratorRemovePrimitiveClient <
                            Collection < __ElementType >,
                            __ElementType
                    >;

        protected:
            using RemoveByClient =
                    __hidden :: __impl :: __RemoveByCompositeClient <
                            Collection < __ElementType >,
                            __ElementType
                    >;

        protected:
            using GenericImmutableStatementsClient =
                    __hidden :: __impl :: __GenericImmutableStatementsCompositeClient <
                            Collection < __ElementType >,
                            __ElementType
                    >;

        protected:
            using ContainsOfCollectionClient =
                    __hidden :: __impl :: __ContainsOfCompositeClient <
                            Collection < __ElementType >,
                            __ElementType,
                            Collection < __ElementType >
                    >;

        protected:
            using ContainsOfInitializerListClient =
                    __hidden :: __impl :: __ContainsOfCompositeClient <
                            Collection < __ElementType >,
                            __ElementType,
                            std :: initializer_list < __ElementType >
                    >;

        protected:
            using FindOfCollectionClient =
                    __hidden :: __impl :: __FindOfImmutableCompositeClient <
                            Collection < __ElementType >,
                            __ElementType,
                            typename __hidden :: __impl :: __DelegateForwardConstIterablePrimitiveClient <
                                    Collection < __ElementType >,
                                    __ElementType,
                                    false
                            > :: ConstIterator,
                            Collection < __ElementType >,
                            __hidden :: __impl :: __collectionContains < __ElementType >
                    >;

        protected:
            using FindOfInitializerListClient =
                    __hidden :: __impl :: __FindOfImmutableCompositeClient <
                            Collection < __ElementType >,
                            __ElementType,
                            typename __hidden :: __impl :: __DelegateForwardConstIterablePrimitiveClient <
                                    Collection < __ElementType >,
                                    __ElementType,
                                    false
                            > :: ConstIterator,
                            std :: initializer_list < __ElementType >,
                            __hidden :: __impl :: __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                    >;

        protected:
            using FindByImmutableClient =
                    __hidden :: __impl :: __FindByImmutableCompositeClient <
                            Collection < __ElementType >,
                            __ElementType,
                            typename __hidden :: __impl :: __DelegateForwardConstIterablePrimitiveClient <
                                    Collection < __ElementType >,
                                    __ElementType,
                                    false
                            > :: ConstIterator
                    >;

        protected:
            using RemoveOfCollectionClient =
                    __hidden :: __impl :: __RemoveOfCompositeClient <
                            Collection < __ElementType >,
                            __ElementType,
                            Collection < __ElementType >,
                            __hidden :: __impl :: __collectionContains < __ElementType >
                    >;

        protected:
            using RemoveOfInitializerListClient =
                    __hidden :: __impl :: __RemoveOfCompositeClient <
                            Collection < __ElementType >,
                            __ElementType,
                            std :: initializer_list < __ElementType >,
                            __hidden :: __impl :: __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                    >;

        protected:
            using RandomInsertionClient
                    = __hidden :: __impl :: __RandomInsertionPrimitiveClient <
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

        public: using RemoveByClient :: removeIf;
        public: using RemoveByClient :: removeFirstIf;
        public: using RemoveByClient :: removeLastIf;
        public: using RemoveByClient :: removeAllIf;

        public: using GenericImmutableStatementsClient :: forEach;
        public: using GenericImmutableStatementsClient :: some;
        public: using GenericImmutableStatementsClient :: atLeast;
        public: using GenericImmutableStatementsClient :: atMost;
        public: using GenericImmutableStatementsClient :: moreThan;
        public: using GenericImmutableStatementsClient :: fewerThan;
        public: using GenericImmutableStatementsClient :: count;
        public: using GenericImmutableStatementsClient :: any;
        public: using GenericImmutableStatementsClient :: all;
        public: using GenericImmutableStatementsClient :: none;

        public: using RemoveOfCollectionClient :: removeOf;
        public: using RemoveOfCollectionClient :: removeFirstOf;
        public: using RemoveOfCollectionClient :: removeLastOf;
        public: using RemoveOfCollectionClient :: removeAllOf;
        public: using RemoveOfCollectionClient :: removeNotOf;
        public: using RemoveOfCollectionClient :: removeFirstNotOf;
        public: using RemoveOfCollectionClient :: removeLastNotOf;
        public: using RemoveOfCollectionClient :: removeAllNotOf;

        public: using RemoveOfInitializerListClient :: removeOf;
        public: using RemoveOfInitializerListClient :: removeFirstOf;
        public: using RemoveOfInitializerListClient :: removeLastOf;
        public: using RemoveOfInitializerListClient :: removeAllOf;
        public: using RemoveOfInitializerListClient :: removeNotOf;
        public: using RemoveOfInitializerListClient :: removeFirstNotOf;
        public: using RemoveOfInitializerListClient :: removeLastNotOf;
        public: using RemoveOfInitializerListClient :: removeAllNotOf;

        public: using ContainsOfCollectionClient :: containsAnyOf;
        public: using ContainsOfCollectionClient :: containsAllOf;
        public: using ContainsOfCollectionClient :: containsAnyNotOf;
        public: using ContainsOfCollectionClient :: containsAllNotOf;

        public: using ContainsOfInitializerListClient :: containsAnyOf;
        public: using ContainsOfInitializerListClient :: containsAllOf;
        public: using ContainsOfInitializerListClient :: containsAnyNotOf;
        public: using ContainsOfInitializerListClient :: containsAllNotOf;

        public: using FindByImmutableClient :: findThat;
        public: using FindByImmutableClient :: findFirstThat;
        public: using FindByImmutableClient :: findLastThat;
        public: using FindByImmutableClient :: findAllThat;

        public: using FindOfCollectionClient :: findOf;
        public: using FindOfCollectionClient :: findFirstOf;
        public: using FindOfCollectionClient :: findLastOf;
        public: using FindOfCollectionClient :: findAllOf;
        public: using FindOfCollectionClient :: findNotOf;
        public: using FindOfCollectionClient :: findFirstNotOf;
        public: using FindOfCollectionClient :: findLastNotOf;
        public: using FindOfCollectionClient :: findAllNotOf;

        public: using FindOfInitializerListClient :: findOf;
        public: using FindOfInitializerListClient :: findFirstOf;
        public: using FindOfInitializerListClient :: findLastOf;
        public: using FindOfInitializerListClient :: findAllOf;
        public: using FindOfInitializerListClient :: findNotOf;
        public: using FindOfInitializerListClient :: findFirstNotOf;
        public: using FindOfInitializerListClient :: findLastNotOf;
        public: using FindOfInitializerListClient :: findAllNotOf;

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
