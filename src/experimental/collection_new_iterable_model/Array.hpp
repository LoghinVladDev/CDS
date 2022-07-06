//
// Created by loghin on 7/2/22.
//

#ifndef __CDS_EX_ARRAY_HPP__
#define __CDS_EX_ARRAY_HPP__

#include <CDS/experimental/List>
#include "shared/collectionInternalCommunication/server/ListServer.hpp"
#include "shared/array/Array.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class Array :
                public List < __ElementType >,
                protected __hidden :: __impl :: __Array <
                        __ElementType,
                        & cds :: meta :: equals < __ElementType >
                >,
                protected __hidden :: __impl :: __ListServer <
                        Array < __ElementType >,
                        __ElementType
                > {

        private:
            template < typename, typename >
            friend class cds :: experimental :: __hidden :: __impl :: __ListServer; // NOLINT(bugprone-reserved-identifier)

        public:
            using ElementType = __ElementType;

        private:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericHandler ( // NOLINT(bugprone-reserved-identifier)
                    __hidden :: __impl :: __CollectionInternalRequestType requestType
            ) noexcept -> void ( Collection < __ElementType > :: * ) () override;

        private:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericConstHandler ( // NOLINT(bugprone-reserved-identifier)
                    __hidden :: __impl :: __CollectionInternalRequestType requestType
            ) const noexcept -> void ( Collection < __ElementType > :: * ) () const override;

        protected:
            using List < __ElementType > :: pushBack;

        public:
            constexpr Array () noexcept;

        public:
            ~Array () noexcept override;

        public:
            auto clear () noexcept -> void override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto size () const noexcept -> Size override;

        public:
            auto popFront () noexcept -> void override;

        public:
            auto popBack () noexcept -> void override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto front () noexcept (false) -> ElementType & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto front () const noexcept (false) -> ElementType const & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto back () noexcept (false) -> ElementType & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto back () const noexcept (false) -> ElementType const & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto get (
                    Index index
            ) noexcept (false) -> ElementType & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto get (
                    Index index
            ) const noexcept (false) -> ElementType const & override;

        public:
            auto removeAt (
                    Index index
            ) noexcept -> bool override;

        private:
            auto __newFront () noexcept -> ElementType *; // NOLINT(bugprone-reserved-identifier)

        private:
            auto __newBack () noexcept -> ElementType *; // NOLINT(bugprone-reserved-identifier)

        private:
            auto __newFrontArray ( // NOLINT(bugprone-reserved-identifier)
                    Size              count,
                    ElementType    ** ppElements
            ) noexcept -> void;

        private:
            auto __newBackArray ( // NOLINT(bugprone-reserved-identifier)
                    Size              count,
                    ElementType    ** ppElements
            ) noexcept -> void;
        };

    }
}

#include "array/impl/Array.hpp"
#include "shared/collectionInternalCommunication/server/impl/ListServer.hpp"
#include "shared/array/impl/Array.hpp"

#endif // __CDS_EX_ARRAY_HPP__
