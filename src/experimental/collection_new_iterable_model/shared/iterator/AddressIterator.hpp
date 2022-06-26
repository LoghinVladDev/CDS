//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ADDRESS_ITERATOR_HPP__
#define __CDS_SHARED_ADDRESS_ITERATOR_HPP__

#include "IteratorModel.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class AddressIterator : public meta :: RandomAccessIterator {

        public:
            using ElementType = __ElementType;

        public:
            using Address = ElementType *;

        private:
            Address _currentAddress { nullptr };

        public:
            constexpr AddressIterator () noexcept;

        public:
            __CDS_Explicit constexpr AddressIterator (
                    Address pAddress
            ) noexcept;

        public:
            constexpr AddressIterator (
                    AddressIterator const & iterator
            ) noexcept;

        public:
            constexpr AddressIterator (
                    AddressIterator && iterator
            ) noexcept;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                    AddressIterator const & iterator
            ) noexcept -> AddressIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                    AddressIterator && iterator
            ) noexcept -> AddressIterator &;

        public:
            __CDS_NoDiscard constexpr auto operator == (
                    AddressIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator != (
                    AddressIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator * () const noexcept -> __ElementType &;

        public:
            __CDS_NoDiscard constexpr auto operator -> () const noexcept -> __ElementType *;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> AddressIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> AddressIterator;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> AddressIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> AddressIterator;

        public:
            template < typename __NumericType > // NOLINT(bugprone-reserved-identifier)
            __CDS_NoDiscard constexpr auto operator + (
                    __NumericType value
            ) const noexcept -> AddressIterator;

        public:
            template < typename __FElementType, typename __NumericType > // NOLINT(bugprone-reserved-identifier)
            friend constexpr auto operator + (
                    __NumericType                               value,
                    AddressIterator < __FElementType >  const & iterator
            ) noexcept -> AddressIterator < __FElementType >;

        public:
            template < typename __NumericType > // NOLINT(bugprone-reserved-identifier)
            __CDS_NoDiscard constexpr auto operator - (
                    __NumericType value
            ) const noexcept -> AddressIterator;

        public:
            __CDS_NoDiscard constexpr auto operator - (
                    AddressIterator const & iterator
            ) const noexcept -> Size;

        public:
            __CDS_NoDiscard constexpr auto operator > (
                    AddressIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator < (
                    AddressIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator >= (
                    AddressIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator <= (
                    AddressIterator const & iterator
            ) const noexcept -> bool;

        public:
            template < typename __NumericType > // NOLINT(bugprone-reserved-identifier)
            __CDS_NoDiscard constexpr auto operator [] (
                    __NumericType index
            ) const noexcept -> ElementType &;

        public:
            __CDS_Explicit constexpr operator bool () const noexcept;
        };

        template < typename __FElementType, typename __NumericType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto operator + (
                __NumericType                               value,
                AddressIterator < __FElementType >  const & iterator
        ) noexcept -> AddressIterator < __FElementType >;

    }
}

#endif // __CDS_SHARED_ADDRESS_ITERATOR_HPP__
