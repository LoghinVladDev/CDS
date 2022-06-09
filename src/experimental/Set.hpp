//
// Created by loghin on 6/3/2022.
//

#ifndef __CDS_EX_SET_HPP__
#define __CDS_EX_SET_HPP__

#include <CDS/experimental/Collection>

#include "set/SetMeta.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T, cds :: meta :: EnableIf < meta :: isValidSetElement < T > () > = 0 >
        class Set : public Collection < T > {

        public:
            using typename Collection < T > :: ElementType;

        protected:
            using typename Collection < T > :: InitializerList;

        protected:
            using typename Collection < T > :: DelegateConstIterator;

        protected:
            using typename Collection < T > :: DelegateIteratorRequestType;

        public:
            using typename Collection < T > :: ConstIterator;

        public:
            using typename Collection < T > :: ConstReverseIterator;

        protected:
            auto delegateConstIterator (
                    DelegateIteratorRequestType requestType
            ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override = 0;

        public:
            constexpr Set () noexcept = default;

        public:
            __CDS_NoDiscard auto toString () const noexcept -> String override;

        public:
            auto clear () noexcept -> void override = 0;

        public:
            __CDS_NoDiscard auto size () const noexcept -> Size override = 0;

        public:
            auto remove (
                    ConstIterator const & iterator
            ) noexcept -> bool override = 0;

        public:
            auto remove (
                    ConstReverseIterator const & iterator
            ) noexcept -> bool override = 0;

            public:
            auto remove (
                    ConstIterator   const * pIterators,
                    Size                    iteratorCount
            ) noexcept -> Size override = 0;

        public:
            auto remove (
                    ConstReverseIterator    const * pIterators,
                    Size                            iteratorCount
            ) noexcept -> Size override = 0;

        public:
            virtual auto remove (
                    ElementType const & element
            ) noexcept -> void = 0;

        public:
            auto pNewInsert () noexcept -> ElementType * & override = 0;

        public:
            template < typename V = T, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < V > () > = 0 >
            auto insert (
                    ElementType const & element
            ) noexcept -> void;

        public:
            template < typename V = T, cds :: meta :: EnableIf < cds :: meta :: isMoveConstructible < V > () > = 0 >
            auto insert (
                    ElementType && element
            ) noexcept -> void;
        };

    }
}

#include "set/impl/Set.hpp"

#endif // __CDS_EX_SET_HPP__
