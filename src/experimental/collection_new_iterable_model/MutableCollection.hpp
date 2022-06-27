//
// Created by loghin on 6/27/22.
//

#ifndef __CDS_EX_MUTABLE_COLLECTION_HPP__
#define __CDS_EX_MUTABLE_COLLECTION_HPP__

#include <CDS/experimental/Collection>

#include "shared/delegateIterableCommunication/client/DelegateForwardIterableClient.hpp"
#include "shared/delegateIterableCommunication/client/AbstractIteratorRemoveClient.hpp"

#include "shared/iterable/IterableMutableStatements.hpp"
#include "shared/iterable/IterableMutableFindOf.hpp"
#include "shared/iterable/IterableMutableFindByPredicate.hpp"

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
                >,
                public __hidden :: __impl :: __IterableMutableFindOf <
                        MutableCollection < __ElementType >,
                        __ElementType,
                        typename __hidden :: __impl :: __DelegateForwardIterableClient < MutableCollection < __ElementType >, __ElementType, false > :: Iterator,
                        Collection < __ElementType >,
                        __hidden :: __impl :: __collectionContains < __ElementType >
                >,
                public __hidden :: __impl :: __IterableMutableFindOf <
                        MutableCollection < __ElementType >,
                        __ElementType,
                        typename __hidden :: __impl :: __DelegateForwardIterableClient < MutableCollection < __ElementType >, __ElementType, false > :: Iterator,
                        std :: initializer_list < __ElementType >,
                        __hidden :: __impl :: __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                >,
                public __hidden :: __impl :: __IterableMutableFindByPredicate <
                        MutableCollection < __ElementType >,
                        __ElementType,
                        typename __hidden :: __impl :: __DelegateForwardIterableClient < MutableCollection < __ElementType >, __ElementType, false > :: Iterator
                >,
                public __hidden :: __impl :: __IterableMutableStatements <
                MutableCollection < __ElementType >,
                        __ElementType
                > {

        public:
            using ElementType = __ElementType;

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

        protected:
            using IterableMutableFindOfCollection =
                    __hidden :: __impl :: __IterableMutableFindOf <
                            MutableCollection < __ElementType >,
                            __ElementType,
                            typename __hidden :: __impl :: __DelegateForwardIterableClient < MutableCollection < __ElementType >, __ElementType, false > :: Iterator,
                            Collection < __ElementType >,
                            __hidden :: __impl :: __collectionContains < __ElementType >
                    >;

        protected:
            using IterableMutableFindOfInitializerList =
                    __hidden :: __impl :: __IterableMutableFindOf <
                            MutableCollection < __ElementType >,
                            __ElementType,
                            typename __hidden :: __impl :: __DelegateForwardIterableClient < MutableCollection < __ElementType >, __ElementType, false > :: Iterator,
                            std :: initializer_list < __ElementType >,
                            __hidden :: __impl :: __initializerListContains < __ElementType, & cds :: meta :: equals < __ElementType > >
                    >;

        protected:
            using IterableMutableStatements =
                    __hidden :: __impl :: __IterableMutableStatements <
                            MutableCollection < __ElementType >,
                            __ElementType
                    >;

        protected:
            using IterableMutableFindByPredicate =
                    __hidden :: __impl :: __IterableMutableFindByPredicate <
                            MutableCollection < __ElementType >,
                            __ElementType,
                            typename __hidden :: __impl :: __DelegateForwardIterableClient < MutableCollection < __ElementType >, __ElementType, false > :: Iterator
                    >;

        protected:
            using Collection =
                    Collection < __ElementType >;


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
        public: using AbstractIteratorRemoveClient :: remove;

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

        public: using IterableMutableStatements :: forEach;
        public: using IterableMutableStatements :: some;
        public: using IterableMutableStatements :: atLeast;
        public: using IterableMutableStatements :: atMost;
        public: using IterableMutableStatements :: moreThan;
        public: using IterableMutableStatements :: fewerThan;
        public: using IterableMutableStatements :: count;
        public: using IterableMutableStatements :: any;
        public: using IterableMutableStatements :: all;
        public: using IterableMutableStatements :: none;

        public: using Collection :: findOf;
        public: using Collection :: findFirstOf;
        public: using Collection :: findLastOf;
        public: using Collection :: findAllOf;
        public: using Collection :: findNotOf;
        public: using Collection :: findFirstNotOf;
        public: using Collection :: findLastNotOf;
        public: using Collection :: findAllNotOf;

        public: using IterableMutableFindOfCollection :: findOf;
        public: using IterableMutableFindOfCollection :: findFirstOf;
        public: using IterableMutableFindOfCollection :: findLastOf;
        public: using IterableMutableFindOfCollection :: findAllOf;
        public: using IterableMutableFindOfCollection :: findNotOf;
        public: using IterableMutableFindOfCollection :: findFirstNotOf;
        public: using IterableMutableFindOfCollection :: findLastNotOf;
        public: using IterableMutableFindOfCollection :: findAllNotOf;

        public: using IterableMutableFindOfInitializerList :: findOf;
        public: using IterableMutableFindOfInitializerList :: findFirstOf;
        public: using IterableMutableFindOfInitializerList :: findLastOf;
        public: using IterableMutableFindOfInitializerList :: findAllOf;
        public: using IterableMutableFindOfInitializerList :: findNotOf;
        public: using IterableMutableFindOfInitializerList :: findFirstNotOf;
        public: using IterableMutableFindOfInitializerList :: findLastNotOf;
        public: using IterableMutableFindOfInitializerList :: findAllNotOf;

        public: using Collection :: findThat;
        public: using Collection :: findFirstThat;
        public: using Collection :: findLastThat;
        public: using Collection :: findAllThat;

        public: using IterableMutableFindByPredicate :: findThat;
        public: using IterableMutableFindByPredicate :: findFirstThat;
        public: using IterableMutableFindByPredicate :: findLastThat;
        public: using IterableMutableFindByPredicate :: findAllThat;

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

#include "shared/iterable/impl/IterableMutableStatements.hpp"
#include "shared/iterable/impl/IterableMutableFindOf.hpp"
#include "shared/iterable/impl/IterableMutableFindByPredicate.hpp"

#endif // __CDS_EX_MUTABLE_COLLECTION_HPP__
