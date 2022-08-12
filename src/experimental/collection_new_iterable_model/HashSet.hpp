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
                public __hidden :: __impl :: __HashSetDelegateIterableServer < __ElementType, __Hasher > {

        protected:  using SetBase                   = Set < __ElementType >;
        protected:  using Server                    = __hidden :: __impl :: __HashSetServer < __ElementType, __Hasher >;
        protected:  using Implementation            = __hidden :: __impl :: __HashSetImplementation < __ElementType, __Hasher >;
        protected:  using Dispatcher                = __hidden :: __impl :: __HashSetDispatcher < __ElementType, __Hasher >;
        protected:  using DelegateIterableServer    = __hidden :: __impl :: __HashSetDelegateIterableServer < __ElementType, __Hasher >;

        protected:  friend Server;

        protected:  using typename SetBase :: __GenericHandler;         // NOLINT(bugprone-reserved-identifier)
        protected:  using typename SetBase :: __GenericConstHandler;    // NOLINT(bugprone-reserved-identifier)

        public:     using ElementType   = __ElementType;
        public:     using ConstIterator = typename Implementation :: __ht_ConstIterator;

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
            __CDS_NoDiscard auto sequence () & noexcept -> Sequence < HashSet < __ElementType > >;

        public:
            __CDS_NoDiscard auto sequence () && noexcept -> Sequence < HashSet < __ElementType > >;

        public:
            __CDS_NoDiscard auto sequence () const & noexcept -> Sequence < HashSet < __ElementType > const >;

        public:
            __CDS_NoDiscard auto sequence () const && noexcept -> Sequence < HashSet < __ElementType > const >;
        };

    }
}

#include "shared/hashTable/impl/HashTable.hpp"

#include "shared/iterator/impl/HashTableIterator.hpp"

#include "shared/collectionInternalCommunication/server/impl/SetServer.hpp"
#include "shared/collectionInternalCommunication/server/impl/SetServerDispatcher.hpp"
#include "shared/collectionInternalCommunication/server/impl/DelegateIterableServer.hpp"

#include "hashSet/impl/HashSet.hpp"

#endif // __CDS_EX_HASH_SET_HPP__
