//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_EX_COLLECTION_HPP__
#define __CDS_EX_COLLECTION_HPP__

#include <CDS/Object>
#include "../../shared/memory/PrimitiveAllocation.hpp"
#include "shared/delegateIterator/ForwardDelegateWrapperIterator.hpp"
#include "shared/delegateIterableCommunication/channel/DelegateIterableChannel.hpp"
#include "shared/delegateIterableCommunication/client/DelegateForwardConstIterableClient.hpp"
#include "shared/delegateIterableCommunication/client/AbstractConstIteratorRemoveClient.hpp"
#include "shared/iterable/IterableRemoveByPredicate.hpp"

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
                public __hidden :: __impl :: __IterableRemoveByPredicate <
                        Collection < __ElementType >,
                        __ElementType
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

        public:
            using ElementType   = __ElementType;

        public:
            using typename DelegateForwardConstIterableClient :: ConstIterator;

        public:
            using DelegateForwardConstIterableClient :: begin;

        public:
            using DelegateForwardConstIterableClient :: end;

        public:
            using DelegateForwardConstIterableClient :: cbegin;

        public:
            using DelegateForwardConstIterableClient :: cend;

        public:
            using AbstractConstIteratorRemoveClient :: remove;

        public:
            using IterableRemoveByPredicate :: removeIf;

        public:
            using IterableRemoveByPredicate :: removeFirstIf;

        public:
            using IterableRemoveByPredicate :: removeLastIf;

        public:
            using IterableRemoveByPredicate :: removeAllIf;
        };


    }
}

#include "shared/delegateIterator/impl/ForwardDelegateWrapperIterator.hpp"
#include "shared/delegateIterableCommunication/channel/impl/DelegateIterableChannel.hpp"
#include "shared/delegateIterableCommunication/client/impl/DelegateForwardConstIterableClient.hpp"
#include "shared/delegateIterableCommunication/client/impl/AbstractConstIteratorRemoveClient.hpp"
#include "shared/iterable/impl/IterableRemoveByPredicate.hpp"

#endif // __CDS_EX_COLLECTION_HPP__
