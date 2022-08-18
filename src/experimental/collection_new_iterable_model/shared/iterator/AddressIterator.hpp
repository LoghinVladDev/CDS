/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_ADDRESS_ITERATOR_HPP__
#define __CDS_SHARED_ADDRESS_ITERATOR_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include "IteratorModel.hpp"

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        /**
         * @brief Abstract Address Iterator, iterating over continuous address ranges.
         * @tparam __ElementType is the type of the enclosed element. Must not be decayed, as it can represent a const iterator
         * @implements RandomAccessIterator
         * @tparam __ElementType
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @namespace cds :: experimental
         */
        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        class AbstractAddressIterator : public meta :: RandomAccessIterator {

        public:
            /**
             * @typedef Alias for the __ElementType template parameter
             * @public
             */
            using ElementType = __ElementType;

        public:
            /**
             * @typedef Alias for the Address indicating at currently
             * @public
             */
            using Address = ElementType *;

        protected:
            /**
             * @brief Current Address, holding the current element in the continuous range
             * @protected
             */
            Address _currentAddress { nullptr };

        protected:
            /**
             * @brief Default Constructor, constexpr
             * @exceptsafe
             *
             * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
             * @protected
             */
            constexpr AbstractAddressIterator () noexcept;

        protected:
            /**
             * @brief Initialization Constructor, constexpr
             * @param pElement : Address = address of the element the iterator is indicating at
             * @exceptsafe
             *
             * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
             * @protected
             */
            __CDS_Explicit constexpr AbstractAddressIterator (
                    Address pElement
            ) noexcept;

        protected:
            /**
             * @brief Copy Constructor, constexpr
             * @param iterator : AbstractAddressIterator cref = Constant Reference to the iterator to acquire the address from
             * @exceptsafe
             *
             * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
             * @protected
             */
            constexpr AbstractAddressIterator (
                    AbstractAddressIterator const & iterator
            ) noexcept;

        protected:
            /**
             * @brief Move Constructor, constexpr
             * @param iterator : AbstractAddressIterator mref = Move Reference to the iterator to move the address from
             * @exceptsafe
             *
             * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
             * @protected
             */
            constexpr AbstractAddressIterator (
                    AbstractAddressIterator && iterator
            ) noexcept;

        protected:
            /**
             * @brief Function used to acquire the current address that the iterator is pointing to
             * @exceptsafe
             * @return Address = the address the iterator is indicating to
             *
             * @test Suite: TBA, Group: TBA, Test Cases: TBA
             * @protected
             */
            __CDS_NoDiscard constexpr auto current () const noexcept -> Address;

        protected:
            /**
             * @brief Function used to copy the address stored in the given iterator
             * @param iterator : AbstractAddressIterator cref = Constant Reference to the iterator to copy the address of
             * @exceptsafe
             *
             * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
             * @protected
             */
            __CDS_cpplang_NonConstConstexprMemberFunction auto copy (
                    AbstractAddressIterator const & iterator
            ) noexcept -> void;

        protected:
            /**
             * @brief Function used to move the address stored in the given iterator
             * @param iterator : AbstractAddressIterator mref = Move Reference to the iterator to move the address of
             * @exceptsafe
             *
             * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
             * @protected
             */
            __CDS_cpplang_NonConstConstexprMemberFunction auto move (
                    AbstractAddressIterator && iterator
            ) noexcept -> void;

        public:
            /**
             * @brief Function used to acquire the current value the iterator is indicating to
             * @exceptsafe
             * @return __ElementType ref = Reference to the element the address is indicating to
             *
             * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
             * @public
             */
            __CDS_NoDiscard constexpr auto operator * () const noexcept -> __ElementType &;

        public:
            /**
             * @brief Function used to acquire the address of the value the iterator is indicating to
             * @exceptsafe
             * @return __ElementType ptr = Pointer to the element the address is indicating to
             *
             * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
             * @public
             */
            __CDS_NoDiscard constexpr auto operator -> () const noexcept -> __ElementType *;

        public:
            /**
             * @brief Equality Comparison Operator
             * @param iterator : AbstractAddressIterator cref = Constant Reference to another iterator to compare this one to
             * @exceptsafe
             * @return bool = true if addresses are equal, false otherwise
             *
             * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
             * @public
             */
            __CDS_NoDiscard constexpr auto operator == (
                    AbstractAddressIterator < __ElementType > const & iterator
            ) const noexcept -> bool;

        public:
            /**
             * @brief Inequality Comparison Operator
             * @param iterator : AbstractAddressIterator cref = Constant Reference to another iterator to compare this one to
             * @exceptsafe
             * @return bool = true if addresses are not equal, false otherwise
             *
             * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
             * @public
             */
            __CDS_NoDiscard constexpr auto operator != (
                    AbstractAddressIterator < __ElementType > const & iterator
            ) const noexcept -> bool;

        public:
            /**
             * @brief Difference Operator. Acquires the number of elements between two iterators
             * @param iterator : AbstractAddressIterator cref = Constant Reference to another iterator to acquire the distance to
             * @exceptsafe
             * @return Size = distance, positive, element count between the two iterators
             *
             * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
             * @public
             */
            __CDS_NoDiscard constexpr auto operator - (
                    AbstractAddressIterator const & iterator
            ) const noexcept -> Size;

        public:
            /**
             * @brief Index Operator. Acquires the value from a given offset of the address of the iterator
             * @tparam __NumericType is the type of the numeric value given as parameter
             * @param index : __NumericType = the offset value to acquire the value from the iterator
             * @exceptsafe
             * @return ElementType ref = Reference to the element at the given offset from this iterator
             *
             * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
             * @public
             */
            template < typename __NumericType > /* NOLINT(bugprone-reserved-identifier) */
            __CDS_NoDiscard constexpr auto operator [] (
                    __NumericType index
            ) const noexcept -> ElementType &;

        public:
            /**
             * @brief Validity function, bool cast.
             * @exceptsafe
             * @return bool = true if not null address, false otherwise
             *
             * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
             * @public
             */
            __CDS_Explicit constexpr operator bool () const noexcept;
        };


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        class ForwardAddressIterator : public AbstractAddressIterator < __ElementType > {

        public:
            using ElementType = __ElementType;

        public:
            using Address = ElementType *;

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
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ForwardAddressIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> ForwardAddressIterator;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> ForwardAddressIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> ForwardAddressIterator;

        public:
            template < typename __NumericType > /* NOLINT(bugprone-reserved-identifier) */
            __CDS_NoDiscard constexpr auto operator + (
                    __NumericType value
            ) const noexcept -> ForwardAddressIterator;

        public:
            template < typename __FElementType, typename __NumericType > /* NOLINT(bugprone-reserved-identifier) */
            friend constexpr auto operator + (
                    __NumericType                                      value,
                    ForwardAddressIterator < __FElementType >  const & iterator
            ) noexcept -> ForwardAddressIterator < __FElementType >;

        public:
            template < typename __NumericType > /* NOLINT(bugprone-reserved-identifier) */
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
        };

        template < typename __FElementType, typename __NumericType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto operator + (
                __NumericType                                      value,
                ForwardAddressIterator < __FElementType >  const & iterator
        ) noexcept -> ForwardAddressIterator < __FElementType >;

        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        class BackwardAddressIterator : public AbstractAddressIterator < __ElementType > {

        public:
            using ElementType = __ElementType;

        public:
            using Address = ElementType *;

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
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> BackwardAddressIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> BackwardAddressIterator;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> BackwardAddressIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> BackwardAddressIterator;

        public:
            template < typename __NumericType > /* NOLINT(bugprone-reserved-identifier) */
            __CDS_NoDiscard constexpr auto operator + (
                    __NumericType value
            ) const noexcept -> BackwardAddressIterator;

        public:
            template < typename __FElementType, typename __NumericType > /* NOLINT(bugprone-reserved-identifier) */
            friend constexpr auto operator + (
                    __NumericType                                       value,
                    BackwardAddressIterator < __FElementType >  const & iterator
            ) noexcept -> BackwardAddressIterator < __FElementType >;

        public:
            template < typename __NumericType > /* NOLINT(bugprone-reserved-identifier) */
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
        };

        template < typename __FElementType, typename __NumericType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto operator + (
                __NumericType                                       value,
                BackwardAddressIterator < __FElementType >  const & iterator
        ) noexcept -> BackwardAddressIterator < __FElementType >;


        template <
                typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                bool     __reverse = false  /* NOLINT(bugprone-reserved-identifier) */
        > using AddressIterator = cds :: meta :: Conditional <
                __reverse,
                BackwardAddressIterator < __ElementType >,
                ForwardAddressIterator < __ElementType >
        >;

    }
}

#endif /* __CDS_SHARED_ADDRESS_ITERATOR_HPP__ */
