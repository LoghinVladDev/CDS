//
// Created by loghin on 27/07/22.
//

#ifndef __CDS_EX_HASH_SET_HPP__
#define __CDS_EX_HASH_SET_HPP__

#include <CDS/experimental/Set>

#include <CDS/Comparator>
#include <CDS/Extractor>
#include <CDS/Hasher>
#include <CDS/Destructor>
#include <CDS/CopyConstructor>

#include "../../shared/Node.hpp"
#include "../../shared/rehashPolicy/rehashPolicy.hpp"

#include "shared/iterator/HashTableIterator.hpp"

#include "shared/collectionInternalCommunication/server/SetServerDispatcher.hpp"

#include "shared/hashTable/HashTable.hpp"

#include "shared/collectionInternalCommunication/server/SetServer.hpp"
#include "shared/collectionInternalCommunication/server/DelegateIterableServer.hpp"

#include "hashSet/Constructs.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template <
                typename __ElementType, // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > class HashSet :
                public Set < __ElementType >,
                protected __hidden :: __impl :: __HashSetServer < __ElementType, __Hasher >,
                public __hidden :: __impl :: __HashSetImplementation < __ElementType, __Hasher >,
                public __hidden :: __impl :: __HashSetDispatcher < __ElementType, __Hasher >,
                public __hidden :: __impl :: __HashSetRandomInsertionClient < __ElementType, __Hasher >,
                public __hidden :: __impl :: __HashSetIteratorRemoveClient < __ElementType, __Hasher >,
                public __hidden :: __impl :: __HashSetFindOfCollectionClient < __ElementType, __Hasher >,
                public __hidden :: __impl :: __HashSetFindOfInitializerListClient < __ElementType, __Hasher >,
                public __hidden :: __impl :: __HashSetFindByClient < __ElementType, __Hasher >,
                public __hidden :: __impl :: __HashSetRemoveOfCollectionClient < __ElementType, __Hasher >,
                public __hidden :: __impl :: __HashSetRemoveOfInitializerListClient < __ElementType, __Hasher >,
                public __hidden :: __impl :: __HashSetRemoveByClient < __ElementType, __Hasher >,
                public __hidden :: __impl :: __HashSetGenericStatementsClient < __ElementType, __Hasher >,
                public __hidden :: __impl :: __HashSetDelegateIterableServer < __ElementType, __Hasher > {

        protected:  using SetBase                           = Set < __ElementType >;
        protected:  using Server                            = __hidden :: __impl :: __HashSetServer < __ElementType, __Hasher >;
        protected:  using Implementation                    = __hidden :: __impl :: __HashSetImplementation < __ElementType, __Hasher >;
        protected:  using Dispatcher                        = __hidden :: __impl :: __HashSetDispatcher < __ElementType, __Hasher >;
        protected:  using DelegateIterableServer            = __hidden :: __impl :: __HashSetDelegateIterableServer < __ElementType, __Hasher >;
        protected:  using RandomInsertionClient             = __hidden :: __impl :: __HashSetRandomInsertionClient < __ElementType, __Hasher >;
        protected:  using IteratorRemoveClient              = __hidden :: __impl :: __HashSetIteratorRemoveClient < __ElementType, __Hasher >;
        protected:  using FindOfCollectionClient            = __hidden :: __impl :: __HashSetFindOfCollectionClient < __ElementType, __Hasher >;
        protected:  using FindOfInitializerListClient       = __hidden :: __impl :: __HashSetFindOfInitializerListClient < __ElementType, __Hasher >;
        protected:  using FindByClient                      = __hidden :: __impl :: __HashSetFindByClient < __ElementType, __Hasher >;
        protected:  using RemoveOfCollectionClient          = __hidden :: __impl :: __HashSetRemoveOfCollectionClient < __ElementType, __Hasher >;
        protected:  using RemoveOfInitializerListClient     = __hidden :: __impl :: __HashSetRemoveOfInitializerListClient < __ElementType, __Hasher >;
        protected:  using RemoveByClient                    = __hidden :: __impl :: __HashSetRemoveByClient < __ElementType, __Hasher >;
        protected:  using GenericStatementsClient           = __hidden :: __impl :: __HashSetGenericStatementsClient < __ElementType, __Hasher >;

        protected:  friend Server;

        protected:  using typename SetBase :: __GenericHandler;         // NOLINT(bugprone-reserved-identifier)
        protected:  using typename SetBase :: __GenericConstHandler;    // NOLINT(bugprone-reserved-identifier)

        public:     using ElementType   = __ElementType;
        public:     using ConstIterator = typename Implementation :: __ht_ConstIterator;

        private:    friend RandomInsertionClient;
        private:    friend IteratorRemoveClient;

        private:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericHandler ( // NOLINT(bugprone-reserved-identifier)
                    __hidden :: __impl :: __CollectionInternalRequestType requestType
            ) noexcept -> __GenericHandler override;

        private:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericConstHandler (    // NOLINT(bugprone-reserved-identifier)
                    __hidden :: __impl :: __CollectionInternalRequestType requestType
            ) const noexcept -> __GenericConstHandler override;

        protected:  using SetBase :: begin;
        protected:  using SetBase :: end;
        protected:  using SetBase :: cbegin;
        protected:  using SetBase :: cend;

        public: using RemoveByClient :: removeIf;
        public: using RemoveByClient :: removeFirstIf;
        public: using RemoveByClient :: removeLastIf;
        public: using RemoveByClient :: removeAllIf;

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

        public: using FindByClient :: findThat;
        public: using FindByClient :: findFirstThat;
        public: using FindByClient :: findLastThat;
        public: using FindByClient :: findAllThat;

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
        public: using RandomInsertionClient :: emplace;

        public:
            constexpr HashSet () noexcept;

        public:
            template <
                    typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyConstructible < __TElementType > ()
                    > = 0
            > HashSet ( // NOLINT(google-explicit-constructor)
                    HashSet const & set
            ) noexcept;

        public:
            constexpr HashSet (
                    HashSet && set
            ) noexcept;

        public:
            template <
                    typename __IteratorType,                    // NOLINT(bugprone-reserved-identifier)
                    typename __TElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier)
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyConstructible < __TElementType > ()
                    > = 0
            > HashSet (
                    __IteratorType const & begin,
                    __IteratorType const & end
            ) noexcept;

        public:
            template <
                    typename __IteratorType,                    // NOLINT(bugprone-reserved-identifier)
                    typename __TElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier)
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyConstructible < __TElementType > ()
                    > = 0
            > HashSet (
                    __Hasher        const & hasher,
                    __IteratorType  const & begin,
                    __IteratorType  const & end
            ) noexcept;

        public:
            template <
                    typename __TElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier)
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyConstructible < __TElementType > ()
                    > = 0
            > HashSet (
                    std :: initializer_list < __ElementType > const & initializerList
            ) noexcept;

        public:
            template <
                    typename __TElementType = __ElementType,    // NOLINT(bugprone-reserved-identifier)
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyConstructible < __TElementType > ()
                    > = 0
            > HashSet (
                    __Hasher                                    const & hasher,
                    std :: initializer_list < __ElementType >   const & initializerList
            ) noexcept;

        public:
            template <
                    typename __OtherElementType, // NOLINT(bugprone-reserved-identifier)
                    cds :: meta :: EnableIf <
                            cds :: meta :: isConvertible < __OtherElementType, __ElementType > ()
                    > = 0
            > __CDS_Explicit HashSet (
                    Collection < __OtherElementType > const & collection
            ) noexcept;

        public:
            template <
                    typename __OtherElementType, // NOLINT(bugprone-reserved-identifier)
                    cds :: meta :: EnableIf <
                            cds :: meta :: isConvertible < __OtherElementType, __ElementType > ()
                    > = 0
            > HashSet (
                    __Hasher                            const & hasher,
                    Collection < __OtherElementType >   const & collection
            ) noexcept;

        public:
            ~HashSet () noexcept override;

        public:
            template <
                    typename __TElementType = __ElementType, // NOLINT(bugprone-reserved-identifier)
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyConstructible < __TElementType > ()
                    > = 0
            > auto operator = (
                    HashSet const & set
            ) noexcept -> HashSet &;

        public:
            auto operator = (
                    HashSet && set
            ) noexcept -> HashSet &;

        public:
            template <
                    typename __OtherElementType, // NOLINT(bugprone-reserved-identifier)
                    cds :: meta :: EnableIf <
                            cds :: meta :: isConvertible < __OtherElementType, __ElementType > ()
                    > = 0
            > auto operator = (
                    Collection < __OtherElementType > const & collection
            ) noexcept -> HashSet &;

        public:
            __CDS_NoDiscard constexpr auto begin () const noexcept -> ConstIterator;

        public:
            __CDS_NoDiscard constexpr auto end () const noexcept -> ConstIterator;

        public:
            __CDS_NoDiscard constexpr auto cbegin () const noexcept -> ConstIterator;

        public:
            __CDS_NoDiscard constexpr auto cend () const noexcept -> ConstIterator;

        public:
            auto clear () noexcept -> void override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto size () const noexcept -> Size override;

        public:
            auto remove (
                    __ElementType const & element
            ) noexcept -> bool override;

        public:
            __CDS_NoDiscard auto sequence () & noexcept -> Sequence < HashSet < __ElementType, __Hasher > >;

        public:
            __CDS_NoDiscard auto sequence () && noexcept -> Sequence < HashSet < __ElementType, __Hasher > >;

        public:
            __CDS_NoDiscard auto sequence () const & noexcept -> Sequence < HashSet < __ElementType, __Hasher > const >;

        public:
            __CDS_NoDiscard auto sequence () const && noexcept -> Sequence < HashSet < __ElementType, __Hasher > const >;
        };

    }
}

#include "shared/hashTable/impl/HashTable.hpp"

#include "shared/iterator/impl/HashTableIterator.hpp"

#include "shared/collectionInternalCommunication/server/impl/SetServer.hpp"
#include "shared/collectionInternalCommunication/server/impl/SetServerDispatcher.hpp"
#include "shared/collectionInternalCommunication/server/impl/DelegateIterableServer.hpp"

#include "hashSet/impl/HashSet.hpp"
#include "hashSet/impl/CTAD.hpp"

#include "shared/hashSet/HashSetSequence.hpp"

#endif // __CDS_EX_HASH_SET_HPP__
