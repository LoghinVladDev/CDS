//
// Created by loghin on 6/27/22.
//

#ifndef __CDS_EX_MUTABLE_COLLECTION_HPP__
#define __CDS_EX_MUTABLE_COLLECTION_HPP__

#include <CDS/experimental/Collection>

#include "shared/collectionInternalCommunication/client/primitive/DelegateForwardIterablePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/IteratorRemovePrimitiveClient.hpp"

#include "shared/collectionInternalCommunication/client/composite/GenericMutableStatementsCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/FindOfMutableCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/FindByMutableCompositeClient.hpp"

#include "mutableCollection/MutableCollectionConstructs.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class MutableCollection :
                public Collection < __ElementType >,
                public __hidden :: __impl :: __MutableCollectionDelegateForwardIterableClient < __ElementType >,
                public __hidden :: __impl :: __MutableCollectionIteratorRemoveClient < __ElementType >,
                public __hidden :: __impl :: __MutableCollectionRandomInsertionClient < __ElementType >,
                public __hidden :: __impl :: __MutableCollectionFindOfCollectionClient < __ElementType >,
                public __hidden :: __impl :: __MutableCollectionFindOfInitializerListClient < __ElementType >,
                public __hidden :: __impl :: __MutableCollectionFindByClient < __ElementType >,
                public __hidden :: __impl :: __MutableCollectionGenericStatementsClient < __ElementType > {

        public:     using ElementType                       = __ElementType;
        protected:  using Collection                        = Collection < __ElementType >;
        protected:  using DelegateForwardIterableClient     = __hidden :: __impl :: __MutableCollectionDelegateForwardIterableClient < __ElementType >;
        protected:  using IteratorRemoveClient              = __hidden :: __impl :: __MutableCollectionIteratorRemoveClient < __ElementType >;
        protected:  using RandomInsertionClient             = __hidden :: __impl :: __MutableCollectionRandomInsertionClient < __ElementType >;
        protected:  using FindOfCollectionClient            = __hidden :: __impl :: __MutableCollectionFindOfCollectionClient < __ElementType >;
        protected:  using FindOfInitializerListClient       = __hidden :: __impl :: __MutableCollectionFindOfInitializerListClient < __ElementType >;
        protected:  using FindByClient                      = __hidden :: __impl :: __MutableCollectionFindByClient < __ElementType >;
        protected:  using GenericStatementsClient           = __hidden :: __impl :: __MutableCollectionGenericStatementsClient < __ElementType >;


        public:
            using typename DelegateForwardIterableClient :: Iterator;

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

        public:
            __CDS_cpplang_ConstexprDestructor ~MutableCollection () noexcept override;

        public: using Collection :: begin;
        public: using Collection :: end;
        public: using Collection :: cbegin;
        public: using Collection :: cend;

        public: using DelegateForwardIterableClient :: begin;
        public: using DelegateForwardIterableClient :: end;

        public: using Collection :: remove;
        public: using IteratorRemoveClient :: remove;

        public: using Collection :: forEach;
        public: using Collection :: some;
        public: using Collection :: atLeast;
        public: using Collection :: atMost;
        public: using Collection :: moreThan;
        public: using Collection :: fewerThan;
        public: using Collection :: count;
        public: using Collection :: any;
        public: using Collection :: all;
        public: using Collection :: none;

        public: using GenericStatementsClient :: forEach;
        public: using GenericStatementsClient :: some;
        public: using GenericStatementsClient :: atLeast;
        public: using GenericStatementsClient :: atMost;
        public: using GenericStatementsClient :: moreThan;
        public: using GenericStatementsClient :: fewerThan;
        public: using GenericStatementsClient :: count;
        public: using GenericStatementsClient :: any;
        public: using GenericStatementsClient :: all;
        public: using GenericStatementsClient :: none;

        public: using Collection :: findOf;
        public: using Collection :: findFirstOf;
        public: using Collection :: findLastOf;
        public: using Collection :: findAllOf;
        public: using Collection :: findNotOf;
        public: using Collection :: findFirstNotOf;
        public: using Collection :: findLastNotOf;
        public: using Collection :: findAllNotOf;

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

        public: using Collection :: findThat;
        public: using Collection :: findFirstThat;
        public: using Collection :: findLastThat;
        public: using Collection :: findAllThat;

        public: using FindByClient :: findThat;
        public: using FindByClient :: findFirstThat;
        public: using FindByClient :: findLastThat;
        public: using FindByClient :: findAllThat;

        public: using RandomInsertionClient :: insert;
        public: using RandomInsertionClient :: insertAll;
        public: using RandomInsertionClient :: insertAllOf;
        public: using RandomInsertionClient :: add;
        public: using RandomInsertionClient :: addAll;
        public: using RandomInsertionClient :: addAllOf;

        public:
            __CDS_NoDiscard auto toString () const noexcept -> String override;

        public:
            auto clear () noexcept -> void override = 0;

        public:
            __CDS_NoDiscard virtual auto find (
                    ElementType const & element
            ) noexcept -> Iterator;

        };

    }
}

#include "mutableCollection/impl/MutableCollection.hpp"

#include "shared/collectionInternalCommunication/client/primitive/impl/DelegateForwardIterablePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/impl/IteratorRemovePrimitiveClient.hpp"

#include "shared/collectionInternalCommunication/client/composite/impl/GenericMutableStatementsCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/impl/FindOfMutableCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/impl/FindByMutableCompositeClient.hpp"

#endif // __CDS_EX_MUTABLE_COLLECTION_HPP__
