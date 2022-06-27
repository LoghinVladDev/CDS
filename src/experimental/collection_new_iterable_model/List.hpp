//
// Created by loghin on 6/27/22.
//

#ifndef __CDS_EX_LIST_HPP__
#define __CDS_EX_LIST_HPP__

#include <CDS/experimental/MutableCollection>

#include "shared/delegateIterator/BidirectionalDelegateWrapperIterator.hpp"

#include "shared/delegateIterableCommunication/client/DelegateBackwardIterableClient.hpp"
#include "shared/delegateIterableCommunication/client/DelegateBackwardConstIterableClient.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class List :
                public MutableCollection < __ElementType >,
                public __hidden :: __impl :: __DelegateForwardIterableClient <
                        List < __ElementType >,
                        __ElementType,
                        true
                >,
                public __hidden :: __impl :: __DelegateBackwardIterableClient <
                        List < __ElementType >,
                        __ElementType,
                        true
                >,
                public __hidden :: __impl :: __DelegateForwardConstIterableClient <
                        List < __ElementType >,
                        __ElementType,
                        true
                >,
                public __hidden :: __impl :: __DelegateBackwardConstIterableClient <
                        List < __ElementType >,
                        __ElementType,
                        true
                > {

        public:
            using ElemenetType = __ElementType;

        protected:
            using DelegateForwardIterableClient =
                    __hidden :: __impl :: __DelegateForwardIterableClient <
                            List < __ElementType >,
                            __ElementType,
                            true
                    >;

        protected:
            using DelegateBackwardIterableClient =
                    __hidden :: __impl :: __DelegateBackwardIterableClient <
                            List < __ElementType >,
                            __ElementType,
                            true
                    >;

        protected:
            using DelegateForwardConstIterableClient =
                    __hidden :: __impl :: __DelegateForwardConstIterableClient <
                            List < __ElementType >,
                            __ElementType,
                            true
                    >;

        protected:
            using DelegateBackwardConstIterableClient =
                    __hidden :: __impl :: __DelegateBackwardConstIterableClient <
                            List < __ElementType >,
                            __ElementType,
                            true
                    >;

        protected:
            using MutableCollection = MutableCollection < __ElementType >;

        protected:
            constexpr List () noexcept;

        protected:
            constexpr List (
                    List const & list
            ) noexcept;

        protected:
            constexpr List (
                    List && list
            ) noexcept;

        protected:
            __CDS_cpplang_ConstexprDestructor ~List () noexcept override;

        public: using DelegateForwardIterableClient :: begin;
        public: using DelegateForwardIterableClient :: end;

        public: using DelegateBackwardIterableClient :: rbegin;
        public: using DelegateBackwardIterableClient :: rend;

        public: using DelegateForwardConstIterableClient :: begin;
        public: using DelegateForwardConstIterableClient :: end;
        public: using DelegateForwardConstIterableClient :: cbegin;
        public: using DelegateForwardConstIterableClient :: cend;

        public: using DelegateBackwardConstIterableClient :: rbegin;
        public: using DelegateBackwardConstIterableClient :: rend;
        public: using DelegateBackwardConstIterableClient :: crbegin;
        public: using DelegateBackwardConstIterableClient :: crend;

        public:
            __CDS_NoDiscard auto toString () const noexcept -> String override;

        public:
            auto clear () noexcept -> void override = 0;

        };

    }
}

#include "shared/delegateIterator/impl/BidirectionalDelegateWrapperIterator.hpp"

#include "shared/delegateIterableCommunication/client/impl/DelegateBackwardIterableClient.hpp"
#include "shared/delegateIterableCommunication/client/impl/DelegateBackwardConstIterableClient.hpp"

#include "list/impl/List.hpp"

#endif // __CDS_EX_LIST_HPP__
