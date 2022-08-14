//
// Created by loghin on 6/27/22.
//

#ifndef __CDS_EX_MAP_HPP__
#define __CDS_EX_MAP_HPP__

#include <CDS/experimental/MutableCollection>
#include <CDS/experimental/Set>

#include "shared/collectionInternalCommunication/client/primitive/FindUniqueMutablePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/FindUniqueImmutablePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/server/MutableCollectionServer.hpp"

#include "../../collection/mutableCollection/map/map/entry/Entry.hpp"

#include "map/Constructs.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType    // NOLINT(bugprone-reserved-identifier)
        > class Map :
                public MutableCollection < cds :: __hidden :: __impl :: __MapEntry < __KeyType, __ValueType > >,
                public __hidden :: __impl :: __MapFindUniqueImmutableClient < __KeyType, __ValueType >,
                public __hidden :: __impl :: __MapFindUniqueMutableClient < __KeyType, __ValueType > {

        protected:  using MutableCollectionBase     = MutableCollection < cds :: __hidden :: __impl :: __MapEntry < __KeyType, __ValueType > >;
        protected:  using FindUniqueImmutableClient = __hidden :: __impl :: __MapFindUniqueImmutableClient < __KeyType, __ValueType >;
        protected:  using FindUniqueMutableClient   = __hidden :: __impl :: __MapFindUniqueMutableClient < __KeyType, __ValueType >;

        protected:  using typename MutableCollectionBase :: __GenericHandler;       // NOLINT(bugprone-reserved-identifier)
        protected:  using typename MutableCollectionBase :: __GenericConstHandler;  // NOLINT(bugprone-reserved-identifier)
        public:     using typename MutableCollectionBase :: ElementType;
        public:     using MutableCollectionBase :: remove;

        public:     using EntryType = ElementType;
        public:     using KeyType   = __KeyType;
        public:     using ValueType = __ValueType;

        protected:  class AbstractMapProxy;
        protected:  class AbstractKeySetProxy;
        protected:  class AbstractValueMutableCollectionProxy;
        protected:  class AbstractEntryMutableCollectionProxy;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto keys () const noexcept -> Set < KeyType const > const &;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto keys () noexcept -> Set < KeyType const > &;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto values () const noexcept -> MutableCollection < ValueType > const &;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto values () noexcept -> MutableCollection < ValueType > &;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto entries () const noexcept -> MutableCollection < EntryType > const &;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto entries () noexcept -> MutableCollection < EntryType > &;

        protected:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto keySetProxy () const noexcept -> AbstractKeySetProxy const & = 0;

        protected:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto keySetProxy () noexcept -> AbstractKeySetProxy & = 0;

        protected:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto valueMutableCollectionProxy () const noexcept -> AbstractValueMutableCollectionProxy const & = 0;

        protected:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto valueMutableCollectionProxy () noexcept -> AbstractValueMutableCollectionProxy & = 0;

        protected:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto entryMutableCollectionProxy () const noexcept -> AbstractEntryMutableCollectionProxy const & = 0;

        protected:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto entryMutableCollectionProxy () noexcept -> AbstractEntryMutableCollectionProxy & = 0;

        public:
            constexpr Map () noexcept;

        public:
            constexpr Map (
                    Map const & map
            ) noexcept;

        public:
            constexpr Map (
                    Map && map
            ) noexcept;

        public:
            __CDS_cpplang_ConstexprDestructor ~Map () noexcept override;

        public: using FindUniqueImmutableClient :: find;
        public: using FindUniqueMutableClient :: find;

        public:
            __CDS_NoDiscard auto toString () const noexcept -> String override;

        public:
            auto clear () noexcept -> void override = 0;

        public:
            virtual auto remove (
                    __KeyType const & key
            ) noexcept -> bool = 0;
        };

    }
}

#include "map/AbstractMapProxy.hpp"
#include "map/AbstractKeySetProxy.hpp"
#include "map/AbstractValueMutableCollectionProxy.hpp"
#include "map/AbstractEntryMutableCollectionProxy.hpp"

#include "shared/collectionInternalCommunication/client/primitive/impl/FindUniqueMutablePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/impl/FindUniqueImmutablePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/server/impl/MutableCollectionServer.hpp"

#include "../../collection/mutableCollection/map/map/entry/impl/Entry.hpp"

#include "map/impl/Map.hpp"
#include "map/impl/AbstractMapProxy.hpp"
#include "map/impl/AbstractKeySetProxy.hpp"
#include "map/impl/AbstractValueMutableCollectionProxy.hpp"
#include "map/impl/AbstractEntryMutableCollectionProxy.hpp"

#endif // __CDS_EX_MAP_HPP__
