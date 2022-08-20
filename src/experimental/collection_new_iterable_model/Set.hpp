/*
 * Created by loghin on 6/27/22.
 */

#ifndef __CDS_EX_SET_HPP__
#define __CDS_EX_SET_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include <CDS/experimental/Collection>

#include "shared/collectionInternalCommunication/client/primitive/FindUniqueImmutablePrimitiveClient.hpp"

#include "set/Constructs.hpp"

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template <
                typename __ElementType,                                                                                     /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf < cds :: experimental :: meta :: isValidSetElement < __ElementType > () > __enabler /* NOLINT(bugprone-reserved-identifier) */
        > class Set :
                public Collection < __ElementType >,
                public __hidden :: __impl :: __SetFindUniqueClient < __ElementType, __enabler > {

        public:     using ElementType       = __ElementType;
        protected:  using FindUniqueClient  = __hidden :: __impl :: __SetFindUniqueClient < __ElementType, __enabler >;

        protected:  using CollectionBase    = Collection < __ElementType >;

        protected:  using typename CollectionBase :: __GenericHandler;      /* NOLINT(bugprone-reserved-identifier) */
        protected:  using typename CollectionBase :: __GenericConstHandler; /* NOLINT(bugprone-reserved-identifier) */

        protected:
            constexpr Set () noexcept;

        protected:
            constexpr Set (
                    Set const & set
            ) noexcept;

        protected:
            constexpr Set (
                    Set && set
            ) noexcept;

        protected:
            __CDS_cpplang_ConstexprDestructor ~Set () noexcept override;

        public: using FindUniqueClient :: find;

        public:
            __CDS_NoDiscard auto toString () const noexcept -> String override;

        public:
            auto clear () noexcept -> void override = 0;

        public:
            virtual auto remove (
                    __ElementType const & element
            ) noexcept -> bool = 0;
        };

    }
}

#include "shared/collectionInternalCommunication/client/primitive/impl/FindUniqueImmutablePrimitiveClient.hpp"

#include "set/impl/Set.hpp"

#endif /* __CDS_EX_SET_HPP__ */
