/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_ADDRESS_ITERATOR_HPP__
#define __CDS_SHARED_ADDRESS_ITERATOR_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include "IteratorModel.hpp"

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            template <
                    typename __ElementType,                                 /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __ElementType >
            > class __ArrayBase;                                            /* NOLINT(bugprone-reserved-identifier) */

        }
    }

    /**
     * @brief Abstract Address Iterator, iterating over continuous address ranges.
     * @tparam __ElementType is the type of the enclosed element. Must not be decayed, as it can represent a const iterator
     * @implements RandomAccessIterator
     *
     * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
     * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
     * @namespace cds :: experimental
     */
    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    class AbstractAddressIterator : public meta :: RandomAccessIterator {

    private:
        /** Friend class declaration for use of 'absoluteBase' function */
        template <
                typename __TElementType,                            /* NOLINT(bugprone-reserved-identifier) */
                cds :: utility :: ComparisonFunction < __TElementType >
        > friend class cds :: __hidden :: __impl :: __ArrayBase;    /* NOLINT(bugprone-reserved-identifier) */

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
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @protected
         */
        constexpr AbstractAddressIterator () noexcept;

    protected:
        /**
         * @brief Initialization Constructor, constexpr
         * @param [in] pElement : Address = address of the element the iterator is indicating at
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @protected
         */
        __CDS_Explicit constexpr AbstractAddressIterator (
                Address pElement
        ) noexcept;

    protected:
        /**
         * @brief Copy Constructor, constexpr
         * @param [in] iterator : AbstractAddressIterator cref = Constant Reference to the iterator to acquire the address from
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @protected
         */
        constexpr AbstractAddressIterator (
                AbstractAddressIterator const & iterator
        ) noexcept;

    protected:
        /**
         * @brief Move Constructor, constexpr
         * @param [in, out] iterator : AbstractAddressIterator mref = Move Reference to the iterator to move the address from
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
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
         * @param [in] iterator : AbstractAddressIterator cref = Constant Reference to the iterator to copy the address of
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @protected
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto copy (
                AbstractAddressIterator const & iterator
        ) noexcept -> void;

    protected:
        /**
         * @brief Function used to move the address stored in the given iterator
         * @param [in, out] iterator : AbstractAddressIterator mref = Move Reference to the iterator to move the address of
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
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
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_NoDiscard constexpr auto operator * () const noexcept -> __ElementType &;

    public:
        /**
         * @brief Function used to acquire the address of the value the iterator is indicating to
         * @exceptsafe
         * @return __ElementType ptr = Pointer to the element the address is indicating to
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_NoDiscard constexpr auto operator -> () const noexcept -> __ElementType *;

    public:
        /**
         * @brief Equality Comparison Operator
         * @param [in] iterator : AbstractAddressIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = true if addresses are equal, false otherwise
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_NoDiscard constexpr auto operator == (
                AbstractAddressIterator < __ElementType > const & iterator
        ) const noexcept -> bool;

    public:
        /**
         * @brief Inequality Comparison Operator
         * @param [in] iterator : AbstractAddressIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = true if addresses are not equal, false otherwise
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_NoDiscard constexpr auto operator != (
                AbstractAddressIterator < __ElementType > const & iterator
        ) const noexcept -> bool;

    protected:
        /**
         * @brief Function used to return the address before it from an absolute point of view, as if forward iterator.
         * Used in insertion after/before functions
         * @exceptsafe
         * @return Address = Address to absolute memory
         * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: All
         * @private
         */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto absoluteBefore () const noexcept -> Address = 0;

    protected:
        /**
         * @brief Function used to return the address after from an absolute point of view, as if forward iterator.
         * Used in insertion after/before functions
         * @exceptsafe
         * @return Address = Address to absolute memory
         * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: All
         * @private
         */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto absoluteAfter () const noexcept -> Address = 0;

    public:
        /**
         * @brief Difference Operator. Acquires the number of elements between two iterators
         * @param [in] iterator : AbstractAddressIterator cref = Constant Reference to another iterator to acquire the distance to
         * @exceptsafe
         * @return Size = distance, positive, element count between the two iterators
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_NoDiscard constexpr auto operator - (
                AbstractAddressIterator const & iterator
        ) const noexcept -> Size;

    public:
        /**
         * @brief Index Operator. Acquires the value from a given offset of the address of the iterator
         * @tparam __NumericType is the type of the numeric value given as parameter
         * @param [in] index : __NumericType = the offset value to acquire the value from the iterator
         * @exceptsafe
         * @return ElementType ref = Reference to the element at the given offset from this iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
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
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_Explicit constexpr operator bool () const noexcept;
    };


    /**
     * @brief Forward Address Iterator, iterating over continuous address ranges from low to high value.
     * Used by __Array, __BaseString, __BaseStringView - begin / end / cbegin / cend
     * @tparam __ElementType is the type of the enclosed element. Must not be decayed, as it can represent a const iterator
     * @extends AbstractAddressIterator
     *
     * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
     * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
     * @namespace cds :: experimental
     */
    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    class ForwardAddressIterator : public AbstractAddressIterator < __ElementType > {

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

    public:
        /**
         * @brief Default Constructor, constexpr
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        constexpr ForwardAddressIterator () noexcept;

    public:
        /**
         * @brief Initialization Constructor, constexpr
         * @param [in] pElement : Address = address of the element the iterator is indicating at
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_Explicit constexpr ForwardAddressIterator (
                Address pElement
        ) noexcept;

    public:
        /**
         * @brief Copy Constructor, constexpr
         * @param [in] iterator : ForwardAddressIterator cref = Constant Reference to the iterator to acquire the address from
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        constexpr ForwardAddressIterator (
                ForwardAddressIterator const & iterator
        ) noexcept;

    public:
        /**
         * @brief Move Constructor, constexpr
         * @param [in, out] iterator : ForwardAddressIterator mref = Move Reference to the iterator to move the address from
         * @exceptsafe
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        constexpr ForwardAddressIterator (
                ForwardAddressIterator && iterator
        ) noexcept;

    public:
        /**
         * @brief Copy Operator, constexpr
         * @param [in] iterator : ForwardAddressIterator cref = Constant Reference to an iterator to copy the address value from
         * @exceptsafe
         * @return ForwardAddressIterator ref = Reference to the modified iterator
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                ForwardAddressIterator const & iterator
        ) noexcept -> ForwardAddressIterator &;

    public:
        /**
         * @brief Move Operator, constexpr
         * @param [in, out] iterator : ForwardAddressIterator mref = Move Reference to an iterator to move the address value from
         * @exceptsafe
         * @return ForwardAddressIterator ref = Reference to the modified iterator
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                ForwardAddressIterator && iterator
        ) noexcept -> ForwardAddressIterator &;

    public:
        /**
         * @brief Equality Comparison Operator
         * @param [in] iterator : ForwardAddressIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = true if addresses are equal, false otherwise
         *
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_NoDiscard constexpr auto operator == (
                ForwardAddressIterator const & iterator
        ) const noexcept -> bool;

    public:
        /**
         * @brief Inequality Comparison Operator
         * @param [in] iterator : ForwardAddressIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = true if addresses are not equal, false otherwise
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_NoDiscard constexpr auto operator != (
                ForwardAddressIterator const & iterator
        ) const noexcept -> bool;

    private:
        /**
         * @brief Function used to return the address before from an absolute point of view, as if forward iterator.
         * Used in insertion after/before functions
         * @exceptsafe
         * @return Address = Address to absolute memory
         * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: All
         * @private
         */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto absoluteBefore () const noexcept -> Address override;

    private:
        /**
         * @brief Function used to return the address after from an absolute point of view, as if forward iterator.
         * Used in insertion after/before functions
         * @exceptsafe
         * @return Address = Address to absolute memory
         * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: All
         * @private
         */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto absoluteAfter () const noexcept -> Address override;

    public:
        /**
         * @brief Prefix Increment Operator. Will advance forward one position and then return
         * @exceptsafe
         * @return ForwardAddressIterator ref = Reference to the modified iterator
         *
         * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
         * @test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ForwardAddressIterator &;

    public:
        /**
         * @brief Postfix Increment Operator. Will return the original iterator, and then advance forward the current one
         * @exceptsafe
         * @return ForwardAddressIterator = A copy of the original iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> ForwardAddressIterator;

    public:
        /**
         * @brief Prefix Decrement Operator. Will advance backward one position and then return
         * @exceptsafe
         * @return ForwardAddressIterator ref = Reference to the modified iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> ForwardAddressIterator &;

    public:
        /**
         * @brief Postfix Decrement Operator. Will return the original iterator, and then advance backward the current one
         * @exceptsafe
         * @return ForwardAddressIterator = A copy of the original iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> ForwardAddressIterator;

    public:
        /**
         * @brief Arithmetic Sum Operator, will return the iterator offset from a number of positions specified in the given value
         * @tparam __NumericType is the type of the numeric value given
         * @param [in] value : __NumericType = number of positions to advance
         * @exceptsafe
         * @return ForwardAddressIterator = Iterator at 'value' positions from the original iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        template < typename __NumericType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_NoDiscard constexpr auto operator + (
                __NumericType value
        ) const noexcept -> ForwardAddressIterator;

    public:
        /**
         * @brief Arithmetic Sum Operator, will return the iterator offset from a number of positions specified in the given value from the given iterator
         * @tparam __FElementType is the type of the element enclosed at the iterator value
         * @tparam __NumericType is the type of the numeric value given
         * @param [in] value : __NumericType = number of positions to advance
         * @param [in] iterator : ForwardAddressIterator cref = Constant Reference to the iterator to start from
         * @exceptsafe
         * @return ForwardAddressIterator = Iterator at 'value' positions from the original iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        template < typename __FElementType, typename __NumericType > /* NOLINT(bugprone-reserved-identifier) */
        friend constexpr auto operator + (
                __NumericType                                      value,
                ForwardAddressIterator < __FElementType >  const & iterator
        ) noexcept -> ForwardAddressIterator < __FElementType >;

    public:
        /**
         * @brief Difference Operator. Acquires the iterator offset negatively with a number of positions from the original iterator
         * @tparam __NumericType is the type of the numeric value
         * @param [in] value : __NumericType = offset value to subtract from the current iterator value in order to obtain the new iterator
         * @exceptsafe
         * @return BackwardAddressIterator = Iterator at 'value' positions backward from the original iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        template < typename __NumericType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_NoDiscard constexpr auto operator - (
                __NumericType value
        ) const noexcept -> ForwardAddressIterator;

    public:
        /**
         * @brief Difference Operator. Acquires the number of elements between two iterators
         * @param [in] iterator : ForwardAddressIterator cref = Constant Reference to another iterator to acquire the distance to
         * @exceptsafe
         * @return Size = distance, positive, element count between the two iterators
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_NoDiscard constexpr auto operator - (
                ForwardAddressIterator const & iterator
        ) const noexcept -> Size;

    public:
        /**
         * @brief Greater Than Operator. Checks if the current iterator is ahead of the given iterator, absolute position - higher address
         * @param [in] iterator : ForwardAddressIterator cref = Constant Reference to another iterator to acquire the distance to
         * @exceptsafe
         * @return bool = true if current iterator has a higher address than the parameter iterator, false otherwise
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_NoDiscard constexpr auto operator > (
                ForwardAddressIterator const & iterator
        ) const noexcept -> bool;

    public:
        /**
         * @brief Greater Than Operator. Checks if the current iterator is behind the given iterator, absolute position - lower address
         * @param [in] iterator : ForwardAddressIterator cref = Constant Reference to another iterator to acquire the distance to
         * @exceptsafe
         * @return bool = true if current iterator has a lower address than the parameter iterator, false otherwise
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_NoDiscard constexpr auto operator < (
                ForwardAddressIterator const & iterator
        ) const noexcept -> bool;

    public:
        /**
         * @brief Greater Than Operator. Checks if the current iterator is ahead of or at the given iterator, absolute position - higher or equal address
         * @param [in] iterator : ForwardAddressIterator cref = Constant Reference to another iterator to acquire the distance to
         * @exceptsafe
         * @return bool = true if current iterator has a higher or equal address than the parameter iterator, false otherwise
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_NoDiscard constexpr auto operator >= (
                ForwardAddressIterator const & iterator
        ) const noexcept -> bool;

    public:
        /**
         * @brief Greater Than Operator. Checks if the current iterator is behind or at the given iterator, absolute position - lower or equal address
         * @param [in] iterator : ForwardAddressIterator cref = Constant Reference to another iterator to acquire the distance to
         * @exceptsafe
         * @return bool = true if current iterator has a lower or equal address than the parameter iterator, false otherwise
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_NoDiscard constexpr auto operator <= (
                ForwardAddressIterator const & iterator
        ) const noexcept -> bool;
    };

    /**
     * @brief Arithmetic Sum Operator, will return the iterator offset from a number of positions specified in the given value from the given iterator
     * @tparam __FElementType is the type of the element enclosed at the iterator value
     * @tparam __NumericType is the type of the numeric value given
     * @param [in] value : __NumericType = number of positions to advance
     * @param [in] iterator : ForwardAddressIterator cref = Constant Reference to the iterator to start from
     * @exceptsafe
     * @return ForwardAddressIterator = Iterator at 'value' positions from the original iterator
     *
     * @test Suite: TBA, Group: TBA, Test Cases: TBA
     * @namespace cds :: experimental
     */
    template < typename __FElementType, typename __NumericType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto operator + (
            __NumericType                                      value,
            ForwardAddressIterator < __FElementType >  const & iterator
    ) noexcept -> ForwardAddressIterator < __FElementType >;


    /**
     * @brief Backward Address Iterator, iterating over continuous address ranges from high to low value.
     * Used by __Array, __BaseString, __BaseStringView - rbegin / rend / crbegin / crend
     * @tparam __ElementType is the type of the enclosed element. Must not be decayed, as it can represent a const iterator
     * @extends AbstractAddressIterator
     *
     * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
     *      LTC-00203-IT-perValueRevCheck,
     *      LTC-00204-IT-perValueRevImmCheck,
     *      LTC-00207-IT-perValueRevBwdCheck,
     *      LTC-00208-IT-perValueRevBwdImmCheck,
     *      LTC-00211-IT-itMutabilityStdRev
     * }
     * @namespace cds :: experimental
     */
    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    class BackwardAddressIterator : public AbstractAddressIterator < __ElementType > {

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

    public:
        /**
         * @brief Default Constructor, constexpr
         * @exceptsafe
         *
         * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
         *      LTC-00203-IT-perValueRevCheck,
         *      LTC-00204-IT-perValueRevImmCheck,
         *      LTC-00207-IT-perValueRevBwdCheck,
         *      LTC-00208-IT-perValueRevBwdImmCheck,
         *      LTC-00211-IT-itMutabilityStdRev
         * }
         * @public
         */
        constexpr BackwardAddressIterator () noexcept;

    public:
        /**
         * @brief Initialization Constructor, constexpr
         * @param [in] pElement : Address = address of the element the iterator is indicating at
         * @exceptsafe
         *
         * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
         *      LTC-00203-IT-perValueRevCheck,
         *      LTC-00204-IT-perValueRevImmCheck,
         *      LTC-00207-IT-perValueRevBwdCheck,
         *      LTC-00208-IT-perValueRevBwdImmCheck,
         *      LTC-00211-IT-itMutabilityStdRev
         * }
         * @public
         */
        __CDS_Explicit constexpr BackwardAddressIterator (
                Address pElement
        ) noexcept;

    public:
        /**
         * @brief Copy Constructor, constexpr
         * @param [in] iterator : BackwardAddressIterator cref = Constant Reference to the iterator to acquire the address from
         * @exceptsafe
         *
         * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
         *      LTC-00203-IT-perValueRevCheck,
         *      LTC-00204-IT-perValueRevImmCheck,
         *      LTC-00207-IT-perValueRevBwdCheck,
         *      LTC-00208-IT-perValueRevBwdImmCheck,
         *      LTC-00211-IT-itMutabilityStdRev
         * }
         * @public
         */
        constexpr BackwardAddressIterator (
                BackwardAddressIterator const & iterator
        ) noexcept;

    public:
        /**
         * @brief Move Constructor, constexpr
         * @param [in, out] iterator : BackwardAddressIterator mref = Move Reference to the iterator to move the address from
         * @exceptsafe
         *
         * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
         *      LTC-00203-IT-perValueRevCheck,
         *      LTC-00204-IT-perValueRevImmCheck,
         *      LTC-00207-IT-perValueRevBwdCheck,
         *      LTC-00208-IT-perValueRevBwdImmCheck,
         *      LTC-00211-IT-itMutabilityStdRev
         * }
         * @public
         */
        constexpr BackwardAddressIterator (
                BackwardAddressIterator && iterator
        ) noexcept;

    public:
        /**
         * @brief Copy Operator, constexpr
         * @param [in] iterator : BackwardAddressIterator cref = Constant Reference to an iterator to copy the address value from
         * @exceptsafe
         * @return BackwardAddressIterator ref = Reference to the modified iterator
         *
         * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
         *      LTC-00203-IT-perValueRevCheck,
         *      LTC-00204-IT-perValueRevImmCheck,
         *      LTC-00207-IT-perValueRevBwdCheck,
         *      LTC-00208-IT-perValueRevBwdImmCheck,
         *      LTC-00211-IT-itMutabilityStdRev
         * }
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                BackwardAddressIterator const & iterator
        ) noexcept -> BackwardAddressIterator &;

    public:
        /**
         * @brief Move Operator, constexpr
         * @param [in, out] iterator : BackwardAddressIterator mref = Move Reference to an iterator to move the address value from
         * @exceptsafe
         * @return BackwardAddressIterator ref = Reference to the modified iterator
         *
         * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
         *      LTC-00203-IT-perValueRevCheck,
         *      LTC-00204-IT-perValueRevImmCheck,
         *      LTC-00207-IT-perValueRevBwdCheck,
         *      LTC-00208-IT-perValueRevBwdImmCheck,
         *      LTC-00211-IT-itMutabilityStdRev
         * }
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                BackwardAddressIterator && iterator
        ) noexcept -> BackwardAddressIterator &;

    public:
        /**
         * @brief Equality Comparison Operator
         * @param [in] iterator : BackwardAddressIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = true if addresses are equal, false otherwise
         *
         * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
         *      LTC-00203-IT-perValueRevCheck,
         *      LTC-00204-IT-perValueRevImmCheck,
         *      LTC-00207-IT-perValueRevBwdCheck,
         *      LTC-00208-IT-perValueRevBwdImmCheck,
         *      LTC-00211-IT-itMutabilityStdRev
         * }
         * @public
         */
        __CDS_NoDiscard constexpr auto operator == (
                BackwardAddressIterator const & iterator
        ) const noexcept -> bool;

    public:
        /**
         * @brief Inequality Comparison Operator
         * @param [in] iterator : BackwardAddressIterator cref = Constant Reference to another iterator to compare this one to
         * @exceptsafe
         * @return bool = true if addresses are not equal, false otherwise
         *
         * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
         *      LTC-00203-IT-perValueRevCheck,
         *      LTC-00204-IT-perValueRevImmCheck,
         *      LTC-00207-IT-perValueRevBwdCheck,
         *      LTC-00208-IT-perValueRevBwdImmCheck,
         *      LTC-00211-IT-itMutabilityStdRev
         * }
         * @public
         */
        __CDS_NoDiscard constexpr auto operator != (
                BackwardAddressIterator const & iterator
        ) const noexcept -> bool;

    private:
        /**
         * @brief Function used to return the address before from an absolute point of view, as if forward iterator.
         * Used in insertion after/before functions
         * @exceptsafe
         * @return Address = Address to absolute memory
         * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: All
         * @private
         */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto absoluteBefore () const noexcept -> Address override;

    private:
        /**
         * @brief Function used to return the address after from an absolute point of view, as if forward iterator.
         * Used in insertion after/before functions
         * @exceptsafe
         * @return Address = Address to absolute memory
         * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: All
         * @private
         */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto absoluteAfter () const noexcept -> Address override;

    public:
        /**
         * @brief Prefix Increment Operator. Will advance backward one position and then return
         * @exceptsafe
         * @return BackwardAddressIterator ref = Reference to the modified iterator
         *
         * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
         *      LTC-00203-IT-perValueRevCheck,
         *      LTC-00204-IT-perValueRevImmCheck,
         *      LTC-00211-IT-itMutabilityStdRev
         * }
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> BackwardAddressIterator &;

    public:
        /**
         * @brief Postfix Increment Operator. Will return the original iterator, and then advance backward the current one
         * @exceptsafe
         * @return BackwardAddressIterator = A copy of the original iterator
         *
         * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
         *      LTC-00203-IT-perValueRevCheck,
         *      LTC-00204-IT-perValueRevImmCheck,
         *      LTC-00211-IT-itMutabilityStdRev
         * }
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> BackwardAddressIterator;

    public:
        /**
         * @brief Prefix Decrement Operator. Will advance forward one position and then return
         * @exceptsafe
         * @return BackwardAddressIterator ref = Reference to the modified iterator
         *
         * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
         *      LTC-00207-IT-perValueRevBwdCheck,
         *      LTC-00208-IT-perValueRevBwdImmCheck
         * }
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> BackwardAddressIterator &;

    public:
        /**
         * @brief Postfix Decrement Operator. Will return the original iterator, and then advance forward the current one
         * @exceptsafe
         * @return BackwardAddressIterator = A copy of the original iterator
         *
         *
         * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
         *      LTC-00207-IT-perValueRevBwdCheck,
         *      LTC-00208-IT-perValueRevBwdImmCheck
         * }
         * @public
         */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> BackwardAddressIterator;

    public:
        /**
         * @brief Arithmetic Sum Operator, will return the iterator offset from a number of positions specified in the given value ( positive offset = backward advance - iterator is reverse )
         * @tparam __NumericType is the type of the numeric value given
         * @param [in] value : __NumericType = number of positions to advance
         * @exceptsafe
         * @return BackwardAddressIterator = Iterator at 'value' positions from the original iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        template < typename __NumericType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_NoDiscard constexpr auto operator + (
                __NumericType value
        ) const noexcept -> BackwardAddressIterator;

    public:
        /**
         * @brief Arithmetic Sum Operator, will return the iterator offset from a number of positions specified in the given value from the given iterator ( positive offset = backward advance - iterator is reverse )
         * @tparam __FElementType is the type of the element enclosed at the iterator value
         * @tparam __NumericType is the type of the numeric value given
         * @param [in] value : __NumericType = number of positions to advance
         * @param [in] iterator : BackwardAddressIterator cref = Constant Reference to the iterator to start from
         * @exceptsafe
         * @return BackwardAddressIterator = Iterator at 'value' positions from the original iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        template < typename __FElementType, typename __NumericType > /* NOLINT(bugprone-reserved-identifier) */
        friend constexpr auto operator + (
                __NumericType                                       value,
                BackwardAddressIterator < __FElementType >  const & iterator
        ) noexcept -> BackwardAddressIterator < __FElementType >;

    public:
        /**
         * @brief Difference Operator. Acquires the iterator offset negatively with a number of positions from the original iterator
         * @tparam __NumericType is the type of the numeric value
         * @param [in] value : __NumericType = offset value to subtract from the current iterator value in order to obtain the new iterator
         * @exceptsafe
         * @return BackwardAddressIterator = Iterator at 'value' positions backward ( forward, since reverse ) from the original iterator
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        template < typename __NumericType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_NoDiscard constexpr auto operator - (
                __NumericType value
        ) const noexcept -> BackwardAddressIterator;

    public:
        /**
         * @brief Difference Operator. Acquires the number of elements between two iterators
         * @param [in] iterator : BackwardAddressIterator cref = Constant Reference to another iterator to acquire the distance to
         * @exceptsafe
         * @return Size = distance, positive, element count between the two iterators
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_NoDiscard constexpr auto operator - (
                BackwardAddressIterator const & iterator
        ) const noexcept -> Size;

    public:
        /**
         * @brief Greater Than Operator. Checks if the current iterator is ahead of the given iterator, absolute position - lower address
         * @param [in] iterator : BackwardAddressIterator cref = Constant Reference to another iterator to acquire the distance to
         * @exceptsafe
         * @return bool = true if current iterator has a lower address than the parameter iterator, false otherwise
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_NoDiscard constexpr auto operator > (
                BackwardAddressIterator const & iterator
        ) const noexcept -> bool;

    public:
        /**
         * @brief Greater Than Operator. Checks if the current iterator is behind the given iterator, absolute position - higher address
         * @param [in] iterator : BackwardAddressIterator cref = Constant Reference to another iterator to acquire the distance to
         * @exceptsafe
         * @return bool = true if current iterator has a higher address than the parameter iterator, false otherwise
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_NoDiscard constexpr auto operator < (
                BackwardAddressIterator const & iterator
        ) const noexcept -> bool;

    public:
        /**
         * @brief Greater Than Operator. Checks if the current iterator is ahead of or at the given iterator, absolute position - lower or equal address
         * @param [in] iterator : BackwardAddressIterator cref = Constant Reference to another iterator to acquire the distance to
         * @exceptsafe
         * @return bool = true if current iterator has a lower or equal address than the parameter iterator, false otherwise
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_NoDiscard constexpr auto operator >= (
                BackwardAddressIterator const & iterator
        ) const noexcept -> bool;

    public:
        /**
         * @brief Greater Than Operator. Checks if the current iterator is behind or at the given iterator, absolute position - higher or equal address
         * @param [in] iterator : BackwardAddressIterator cref = Constant Reference to another iterator to acquire the distance to
         * @exceptsafe
         * @return bool = true if current iterator has a higher or equal address than the parameter iterator, false otherwise
         *
         * @test Suite: TBA, Group: TBA, Test Cases: TBA
         * @public
         */
        __CDS_NoDiscard constexpr auto operator <= (
                BackwardAddressIterator const & iterator
        ) const noexcept -> bool;
    };


    /**
     * @brief Arithmetic Sum Operator, will return the iterator offset from a number of positions specified in the given value from the given iterator ( reverse positioning due to reverse iterator )
     * @tparam __FElementType is the type of the element enclosed at the iterator value
     * @tparam __NumericType is the type of the numeric value given
     * @param [in] value : __NumericType = number of positions to advance
     * @param [in] iterator : BackwardAddressIterator cref = Constant Reference to the iterator to start from
     * @exceptsafe
     * @return BackwardAddressIterator = Iterator at 'value' positions from the original iterator
     *
     * @test Suite: TBA, Group: TBA, Test Cases: TBA
     * @namespace cds :: experimental
     */
    template < typename __FElementType, typename __NumericType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto operator + (
            __NumericType                                       value,
            BackwardAddressIterator < __FElementType >  const & iterator
    ) noexcept -> BackwardAddressIterator < __FElementType >;


    /**
     * @brief Generic Address Iterator, iterating over continuous address ranges from from low to high or high to low value, based on reverse value.
     * @tparam __ElementType is the type of the enclosed element. Must not be decayed, as it can represent a const iterator
     * @tparam __reverse is whether the iterator should go backward or forward. If false, it will go forward, being a ForwardAddressIterator. Otherwise, backward, and will be a BackwardAddressIterator
     * @extends AbstractAddressIterator
     *
     * @test Suite: TBA, Group: TBA, Test Cases: TBA
     * @namespace cds :: experimental
     */
    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
            bool     __reverse = false  /* NOLINT(bugprone-reserved-identifier) */
    > using AddressIterator = cds :: meta :: Conditional <
            __reverse,
            BackwardAddressIterator < __ElementType >,
            ForwardAddressIterator < __ElementType >
    >;
}

#endif /* __CDS_SHARED_ADDRESS_ITERATOR_HPP__ */
