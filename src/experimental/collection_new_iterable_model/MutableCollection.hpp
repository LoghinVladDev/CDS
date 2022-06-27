//
// Created by loghin on 6/27/22.
//

#ifndef __CDS_EX_MUTABLE_COLLECTION_HPP__
#define __CDS_EX_MUTABLE_COLLECTION_HPP__

#include <CDS/experimental/Collection>

#include "shared/delegateIterableCommunication/client/DelegateForwardIterableClient.hpp"
#include "shared/delegateIterableCommunication/client/AbstractIteratorRemoveClient.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class MutableCollection :
                public Collection < __ElementType >,
                public __hidden :: __impl :: __DelegateForwardIterableClient <
                        MutableCollection < __ElementType >,
                        __ElementType,
                        false
                >,
                public __hidden :: __impl :: __AbstractIteratorRemoveClient <
                        MutableCollection < __ElementType >,
                        __ElementType
                > {
        public:
            using ElementType = __ElementType;

        protected:
            using Collection =
                    Collection < __ElementType >;

        protected:
            using DelegateForwardIterableClient =
                    __hidden :: __impl :: __DelegateForwardIterableClient <
                            MutableCollection < __ElementType >,
                            __ElementType,
                            false
                    >;

        protected:
            using AbstractIteratorRemoveClient =
                    __hidden :: __impl :: __AbstractIteratorRemoveClient <
                            MutableCollection < __ElementType >,
                            __ElementType
                    >;

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
            __CDS_cpplang_VirtualConstexpr ~MutableCollection () noexcept override;

        public: using Collection :: begin;
        public: using Collection :: end;
        public: using Collection :: cbegin;
        public: using Collection :: cend;

        public: using DelegateForwardIterableClient :: begin;
        public: using DelegateForwardIterableClient :: end;

        public: using Collection :: remove;
        public: using AbstractIteratorRemoveClient :: remove;

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

#include "shared/delegateIterableCommunication/client/impl/DelegateForwardIterableClient.hpp"
#include "shared/delegateIterableCommunication/client/impl/AbstractIteratorRemoveClient.hpp"

#include "mutableCollection/impl/MutableCollection.hpp"

#endif // __CDS_EX_MUTABLE_COLLECTION_HPP__
