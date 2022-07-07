//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ADDRESS_ITERATOR_HPP__
#define __CDS_SHARED_ADDRESS_ITERATOR_HPP__

#include "IteratorModel.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class ForwardAddressIterator : public meta :: RandomAccessIterator {

        public:
            using ElementType = __ElementType;

        public:
            using Address = ElementType *;

        private:
            Address _currentAddress { nullptr };

        public:
            constexpr ForwardAddressIterator () noexcept;

        public:
            __CDS_Explicit constexpr ForwardAddressIterator (
                    Address pAddress
            ) noexcept;

        public:
            constexpr ForwardAddressIterator (
                    ForwardAddressIterator const & iterator
            ) noexcept;

        public:
            constexpr ForwardAddressIterator (
                    ForwardAddressIterator && iterator
            ) noexcept;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                    ForwardAddressIterator const & iterator
            ) noexcept -> ForwardAddressIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                    ForwardAddressIterator && iterator
            ) noexcept -> ForwardAddressIterator &;

        public:
            __CDS_NoDiscard constexpr auto operator == (
                    ForwardAddressIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator != (
                    ForwardAddressIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator * () const noexcept -> __ElementType &;

        public:
            __CDS_NoDiscard constexpr auto operator -> () const noexcept -> __ElementType *;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ForwardAddressIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> ForwardAddressIterator;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> ForwardAddressIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> ForwardAddressIterator;

        public:
            template < typename __NumericType > // NOLINT(bugprone-reserved-identifier)
            __CDS_NoDiscard constexpr auto operator + (
                    __NumericType value
            ) const noexcept -> ForwardAddressIterator;

        public:
            template < typename __FElementType, typename __NumericType > // NOLINT(bugprone-reserved-identifier)
            friend constexpr auto operator + (
                    __NumericType                                      value,
                    ForwardAddressIterator < __FElementType >  const & iterator
            ) noexcept -> ForwardAddressIterator < __FElementType >;

        public:
            template < typename __NumericType > // NOLINT(bugprone-reserved-identifier)
            __CDS_NoDiscard constexpr auto operator - (
                    __NumericType value
            ) const noexcept -> ForwardAddressIterator;

        public:
            __CDS_NoDiscard constexpr auto operator - (
                    ForwardAddressIterator const & iterator
            ) const noexcept -> Size;

        public:
            __CDS_NoDiscard constexpr auto operator > (
                    ForwardAddressIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator < (
                    ForwardAddressIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator >= (
                    ForwardAddressIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator <= (
                    ForwardAddressIterator const & iterator
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
                __NumericType                                      value,
                ForwardAddressIterator < __FElementType >  const & iterator
        ) noexcept -> ForwardAddressIterator < __FElementType >;

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class BackwardAddressIterator : public meta :: RandomAccessIterator {

        public:
            using ElementType = __ElementType;

        public:
            using Address = ElementType *;

        private:
            Address _currentAddress { nullptr };

        public:
            constexpr BackwardAddressIterator () noexcept;

        public:
            __CDS_Explicit constexpr BackwardAddressIterator (
                    Address pAddress
            ) noexcept;

        public:
            constexpr BackwardAddressIterator (
                    BackwardAddressIterator const & iterator
            ) noexcept;

        public:
            constexpr BackwardAddressIterator (
                    BackwardAddressIterator && iterator
            ) noexcept;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                    BackwardAddressIterator const & iterator
            ) noexcept -> BackwardAddressIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                    BackwardAddressIterator && iterator
            ) noexcept -> BackwardAddressIterator &;

        public:
            __CDS_NoDiscard constexpr auto operator == (
                    BackwardAddressIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator != (
                    BackwardAddressIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator * () const noexcept -> __ElementType &;

        public:
            __CDS_NoDiscard constexpr auto operator -> () const noexcept -> __ElementType *;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> BackwardAddressIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> BackwardAddressIterator;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> BackwardAddressIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> BackwardAddressIterator;

        public:
            template < typename __NumericType > // NOLINT(bugprone-reserved-identifier)
            __CDS_NoDiscard constexpr auto operator + (
                    __NumericType value
            ) const noexcept -> BackwardAddressIterator;

        public:
            template < typename __FElementType, typename __NumericType > // NOLINT(bugprone-reserved-identifier)
            friend constexpr auto operator + (
                    __NumericType                                       value,
                    BackwardAddressIterator < __FElementType >  const & iterator
            ) noexcept -> BackwardAddressIterator < __FElementType >;

        public:
            template < typename __NumericType > // NOLINT(bugprone-reserved-identifier)
            __CDS_NoDiscard constexpr auto operator - (
                    __NumericType value
            ) const noexcept -> BackwardAddressIterator;

        public:
            __CDS_NoDiscard constexpr auto operator - (
                    BackwardAddressIterator const & iterator
            ) const noexcept -> Size;

        public:
            __CDS_NoDiscard constexpr auto operator > (
                    BackwardAddressIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator < (
                    BackwardAddressIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator >= (
                    BackwardAddressIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator <= (
                    BackwardAddressIterator const & iterator
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
                __NumericType                                       value,
                BackwardAddressIterator < __FElementType >  const & iterator
        ) noexcept -> BackwardAddressIterator < __FElementType >;


        template <
                typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                bool     __reverse = false  // NOLINT(bugprone-reserved-identifier)
        > using AddressIterator = cds :: meta :: Conditional <
                __reverse,
                BackwardAddressIterator < __ElementType >,
                ForwardAddressIterator < __ElementType >
        >;

    }
}

#endif // __CDS_SHARED_ADDRESS_ITERATOR_HPP__
