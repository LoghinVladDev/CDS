//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ADDRESS_ITERATOR_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_ADDRESS_ITERATOR_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include "IteratorModel.hpp"

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(bugprone-reserved-identifier, modernize-concat-nested-namespaces, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <
    typename __Element, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Element const&, __Element const&>
> class __ArrayBase;            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <
    typename __Element, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size,
    functional::PredicateFunction <__Element const&, __Element const&>,
    typename
> class __StaticArrayBase;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

} // namespace __impl
} // namespace __hidden

/// \brief Abstract Address Iterator, iterating over continuous address ranges.
/// \tparam __Element is the type of the enclosed element. Must not be decayed, as it can represent a const iterator
/// \implements RandomAccessIterator
///
/// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
/// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
/// \namespace cds::experimental
template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class AbstractAddressIterator : public meta::RandomAccessIterator {
public:
  /// \typedef Alias for the __Element template parameter
  /// \public
  using ElementType = __Element;

  /// \typedef Alias for the Address indicating at currently
  /// \public
  using Address = ElementType*;

  ~AbstractAddressIterator () noexcept = default;
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (AbstractAddressIterator const&) noexcept -> AbstractAddressIterator&;
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (AbstractAddressIterator&&) noexcept -> AbstractAddressIterator&;

  /// \brief Function used to acquire the current value the iterator is indicating to
  /// \exceptsafe
  /// \return __Element ref = Reference to the element the address is indicating to
  ///
  /// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  __CDS_NoDiscard constexpr auto operator* () const noexcept -> __Element&;

  /// \brief Function used to acquire the address of the value the iterator is indicating to
  /// \exceptsafe
  /// \return __Element ptr = Pointer to the element the address is indicating to
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard constexpr auto operator -> () const noexcept -> __Element*;

  /// \brief Equality Comparison Operator
  /// \param [in] iterator : AbstractAddressIterator cref = Constant Reference to another iterator to compare this one to
  /// \exceptsafe
  /// \return bool = true if addresses are equal, false otherwise
  ///
  /// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  __CDS_NoDiscard constexpr auto operator == (
      AbstractAddressIterator <__Element> const& iterator
  ) const noexcept -> bool;

  /// \brief Inequality Comparison Operator
  /// \param [in] iterator : AbstractAddressIterator cref = Constant Reference to another iterator to compare this one to
  /// \exceptsafe
  /// \return bool = true if addresses are not equal, false otherwise
  ///
  /// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  __CDS_NoDiscard constexpr auto operator != (
      AbstractAddressIterator <__Element> const& iterator
  ) const noexcept -> bool;

  /// \brief Difference Operator. Acquires the number of elements between two iterators
  /// \param [in] iterator : AbstractAddressIterator cref = Constant Reference to another iterator to acquire the distance to
  /// \exceptsafe
  /// \return Size = distance, positive, element count between the two iterators
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard constexpr auto operator - (
      AbstractAddressIterator const& iterator
  ) const noexcept -> Size;

  /// \brief Index Operator. Acquires the value from a given offset of the address of the iterator
  /// \tparam __NumericType is the type of the numeric value given as parameter
  /// \param [in] index : __NumericType = the offset value to acquire the value from the iterator
  /// \exceptsafe
  /// \return ElementType ref = Reference to the element at the given offset from this iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  template < typename __NumericType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard constexpr auto operator [] (
      __NumericType index
  ) const noexcept -> ElementType&;

  /// \brief Validity function, bool cast.
  /// \exceptsafe
  /// \return bool = true if not null address, false otherwise
  ///
  /// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  __CDS_NoDiscard __CDS_Explicit constexpr operator bool () const noexcept; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-non-private-member-variables-in-classes)

  /// \brief Default Constructor, constexpr
  /// \exceptsafe
  ///
  /// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  constexpr AbstractAddressIterator () noexcept;

  /// \brief Initialization Constructor, constexpr
  /// \param [in] pElement : Address = address of the element the iterator is indicating at
  /// \exceptsafe
  ///
  /// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  __CDS_Explicit constexpr AbstractAddressIterator (Address pElement) noexcept;

  /// \brief Copy Constructor, constexpr
  /// \param [in] iterator : AbstractAddressIterator cref = Constant Reference to the iterator to acquire the address from
  /// \exceptsafe
  ///
  /// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  constexpr AbstractAddressIterator (AbstractAddressIterator const& iterator) noexcept;

  /// \brief Move Constructor, constexpr
  /// \param [in, out] iterator : AbstractAddressIterator mref = Move Reference to the iterator to move the address from
  /// \exceptsafe
  ///
  /// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  constexpr AbstractAddressIterator (AbstractAddressIterator&& iterator) noexcept;

protected:
  /// \brief Function used to acquire the current address that the iterator is pointing to
  /// \exceptsafe
  /// \return Address = the address the iterator is indicating to
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard constexpr auto current () const noexcept -> Address;

  /// \brief Function used to return the address before it from an absolute point of view, as if forward iterator.
  /// Used in insertion after/before functions
  /// \exceptsafe
  /// \return Address = Address to absolute memory
  /// \test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: All
  /// \private
  __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto absoluteBefore () const noexcept -> Address = 0;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,*-non-private-member-variables-in-classes)

  /// \brief Function used to return the address after from an absolute point of view, as if forward iterator.
  /// Used in insertion after/before functions
  /// \exceptsafe
  /// \return Address = Address to absolute memory
  /// \test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: All
  /// \private
  __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto absoluteAfter () const noexcept -> Address = 0;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto address() noexcept -> Address &;
  __CDS_NoDiscard constexpr auto address() const noexcept -> Address const&;

private:
  /// \brief Current Address, holding the current element in the continuous range
  /// \protected
  Address _currentAddress {nullptr}; // NOLINT(*-non-private-member-variables-in-classes)

  // Friend class declaration for use of 'absoluteBase' function
  template <
      typename __TElementType,                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      functional::PredicateFunction <__TElementType const&, __TElementType const&>
  > friend class cds::__hidden::__impl::__ArrayBase;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


/// \brief Forward Address Iterator, iterating over continuous address ranges from low to high value.
/// Used by __Array, __BaseString, __BaseStringView - begin / end / cbegin / cend
/// \tparam __Element is the type of the enclosed element. Must not be decayed, as it can represent a const iterator
/// \extends AbstractAddressIterator
///
/// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
/// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
/// \namespace cds::experimental
template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class ForwardAddressIterator : public AbstractAddressIterator <__Element> {
public:
  /// \typedef Alias for the __Element template parameter
  /// \public
  using ElementType = __Element;

  /// \typedef Alias for the Address indicating at currently
  /// \public
  using Address = ElementType*;

  using AbstractAddressIterator <__Element>::AbstractAddressIterator;
  using AbstractAddressIterator <__Element>::operator=;
  ~ForwardAddressIterator() noexcept = default;

  /// \brief Equality Comparison Operator
  /// \param [in] iterator : ForwardAddressIterator cref = Constant Reference to another iterator to compare this one to
  /// \exceptsafe
  /// \return bool = true if addresses are equal, false otherwise
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  __CDS_NoDiscard constexpr auto operator == (
      ForwardAddressIterator const& iterator
  ) const noexcept -> bool;

  /// \brief Inequality Comparison Operator
  /// \param [in] iterator : ForwardAddressIterator cref = Constant Reference to another iterator to compare this one to
  /// \exceptsafe
  /// \return bool = true if addresses are not equal, false otherwise
  ///
  /// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  __CDS_NoDiscard constexpr auto operator != (
      ForwardAddressIterator const& iterator
  ) const noexcept -> bool;

  /// \brief Prefix Increment Operator. Will advance forward one position and then return
  /// \exceptsafe
  /// \return ForwardAddressIterator ref = Reference to the modified iterator
  ///
  /// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ForwardAddressIterator&;

  /// \brief Postfix Increment Operator. Will return the original iterator, and then advance forward the current one
  /// \exceptsafe
  /// \return ForwardAddressIterator = A copy of the original iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> ForwardAddressIterator;

  /// \brief Prefix Decrement Operator. Will advance backward one position and then return
  /// \exceptsafe
  /// \return ForwardAddressIterator ref = Reference to the modified iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> ForwardAddressIterator&;

  /// \brief Postfix Decrement Operator. Will return the original iterator, and then advance backward the current one
  /// \exceptsafe
  /// \return ForwardAddressIterator = A copy of the original iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> ForwardAddressIterator;

  /// \brief Arithmetic Sum Operator, will return the iterator offset from a number of positions specified in the given value
  /// \tparam __NumericType is the type of the numeric value given
  /// \param [in] value : __NumericType = number of positions to advance
  /// \exceptsafe
  /// \return ForwardAddressIterator = Iterator at 'value' positions from the original iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  template < typename __NumericType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard constexpr auto operator + (
      __NumericType value
  ) const noexcept -> ForwardAddressIterator;

  /// \brief Arithmetic Sum Operator, will return the iterator offset from a number of positions specified in the given value from the given iterator
  /// \tparam __FElementType is the type of the element enclosed at the iterator value
  /// \tparam __NumericType is the type of the numeric value given
  /// \param [in] value : __NumericType = number of positions to advance
  /// \param [in] iterator : ForwardAddressIterator cref = Constant Reference to the iterator to start from
  /// \exceptsafe
  /// \return ForwardAddressIterator = Iterator at 'value' positions from the original iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  template <typename __FElementType, typename __NumericType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  friend constexpr auto operator + (
      __NumericType                                   value,
      ForwardAddressIterator <__FElementType> const&  iterator
  ) noexcept -> ForwardAddressIterator <__FElementType>;

  /// \brief Difference Operator. Acquires the iterator offset negatively with a number of positions from the original iterator
  /// \tparam __NumericType is the type of the numeric value
  /// \param [in] value : __NumericType = offset value to subtract from the current iterator value in order to obtain the new iterator
  /// \exceptsafe
  /// \return BackwardAddressIterator = Iterator at 'value' positions backward from the original iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  template < typename __NumericType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard constexpr auto operator - (
      __NumericType value
  ) const noexcept -> ForwardAddressIterator;

  /// \brief Difference Operator. Acquires the number of elements between two iterators
  /// \param [in] iterator : ForwardAddressIterator cref = Constant Reference to another iterator to acquire the distance to
  /// \exceptsafe
  /// \return Size = distance, positive, element count between the two iterators
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard constexpr auto operator - (
      ForwardAddressIterator const& iterator
  ) const noexcept -> Size;

  /// \brief Greater Than Operator. Checks if the current iterator is ahead of the given iterator, absolute position - higher address
  /// \param [in] iterator : ForwardAddressIterator cref = Constant Reference to another iterator to acquire the distance to
  /// \exceptsafe
  /// \return bool = true if current iterator has a higher address than the parameter iterator, false otherwise
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard constexpr auto operator > (
      ForwardAddressIterator const& iterator
  ) const noexcept -> bool;

  /// \brief Greater Than Operator. Checks if the current iterator is behind the given iterator, absolute position - lower address
  /// \param [in] iterator : ForwardAddressIterator cref = Constant Reference to another iterator to acquire the distance to
  /// \exceptsafe
  /// \return bool = true if current iterator has a lower address than the parameter iterator, false otherwise
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard constexpr auto operator < (
      ForwardAddressIterator const& iterator
  ) const noexcept -> bool;

  /// \brief Greater Than Operator. Checks if the current iterator is ahead of or at the given iterator, absolute position - higher or equal address
  /// \param [in] iterator : ForwardAddressIterator cref = Constant Reference to another iterator to acquire the distance to
  /// \exceptsafe
  /// \return bool = true if current iterator has a higher or equal address than the parameter iterator, false otherwise
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard constexpr auto operator >= (
      ForwardAddressIterator const& iterator
  ) const noexcept -> bool;

  /// \brief Greater Than Operator. Checks if the current iterator is behind or at the given iterator, absolute position - lower or equal address
  /// \param [in] iterator : ForwardAddressIterator cref = Constant Reference to another iterator to acquire the distance to
  /// \exceptsafe
  /// \return bool = true if current iterator has a lower or equal address than the parameter iterator, false otherwise
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard constexpr auto operator <= (
      ForwardAddressIterator const& iterator
  ) const noexcept -> bool;

private:
  /// \brief Function used to return the address before from an absolute point of view, as if forward iterator.
  /// Used in insertion after/before functions
  /// \exceptsafe
  /// \return Address = Address to absolute memory
  /// \test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: All
  /// \private
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto absoluteBefore () const noexcept -> Address override;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to return the address after from an absolute point of view, as if forward iterator.
  /// Used in insertion after/before functions
  /// \exceptsafe
  /// \return Address = Address to absolute memory
  /// \test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: All
  /// \private
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto absoluteAfter () const noexcept -> Address override;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using AbstractAddressIterator <__Element>::address;
};

/// \brief Arithmetic Sum Operator, will return the iterator offset from a number of positions specified in the given value from the given iterator
/// \tparam __FElementType is the type of the element enclosed at the iterator value
/// \tparam __NumericType is the type of the numeric value given
/// \param [in] value : __NumericType = number of positions to advance
/// \param [in] iterator : ForwardAddressIterator cref = Constant Reference to the iterator to start from
/// \exceptsafe
/// \return ForwardAddressIterator = Iterator at 'value' positions from the original iterator
///
/// \test Suite: TBA, Group: TBA, Test Cases: TBA
/// \namespace cds::experimental
template <typename __FElementType, typename __NumericType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto operator + (
    __NumericType                                   value,
    ForwardAddressIterator <__FElementType> const&  iterator
) noexcept -> ForwardAddressIterator <__FElementType>;


/// \brief Backward Address Iterator, iterating over continuous address ranges from high to low value.
/// Used by __Array, __BaseString, __BaseStringView - rbegin / rend / crbegin / crend
/// \tparam __Element is the type of the enclosed element. Must not be decayed, as it can represent a const iterator
/// \extends AbstractAddressIterator
///
/// \test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
///      LTC-00203-IT-perValueRevCheck,
///      LTC-00204-IT-perValueRevImmCheck,
///      LTC-00207-IT-perValueRevBwdCheck,
///      LTC-00208-IT-perValueRevBwdImmCheck,
///      LTC-00211-IT-itMutabilityStdRev
/// }
/// \namespace cds::experimental
template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class BackwardAddressIterator : public AbstractAddressIterator <__Element> {
public:
  /// \typedef Alias for the __Element template parameter
  /// \public
  using ElementType = __Element;

  /// \typedef Alias for the Address indicating at currently
  /// \public
  using Address = ElementType*;
  using AbstractAddressIterator <__Element>::AbstractAddressIterator;
  using AbstractAddressIterator <__Element>::operator=;
  ~BackwardAddressIterator () noexcept = default;

  /// \brief Equality Comparison Operator
  /// \param [in] iterator : BackwardAddressIterator cref = Constant Reference to another iterator to compare this one to
  /// \exceptsafe
  /// \return bool = true if addresses are equal, false otherwise
  ///
  /// \test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
  ///      LTC-00203-IT-perValueRevCheck,
  ///      LTC-00204-IT-perValueRevImmCheck,
  ///      LTC-00207-IT-perValueRevBwdCheck,
  ///      LTC-00208-IT-perValueRevBwdImmCheck,
  ///      LTC-00211-IT-itMutabilityStdRev
  /// }
  /// \public
  __CDS_NoDiscard constexpr auto operator == (
      BackwardAddressIterator const& iterator
  ) const noexcept -> bool;

  /// \brief Inequality Comparison Operator
  /// \param [in] iterator : BackwardAddressIterator cref = Constant Reference to another iterator to compare this one to
  /// \exceptsafe
  /// \return bool = true if addresses are not equal, false otherwise
  ///
  /// \test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
  ///      LTC-00203-IT-perValueRevCheck,
  ///      LTC-00204-IT-perValueRevImmCheck,
  ///      LTC-00207-IT-perValueRevBwdCheck,
  ///      LTC-00208-IT-perValueRevBwdImmCheck,
  ///      LTC-00211-IT-itMutabilityStdRev
  /// }
  /// \public
  __CDS_NoDiscard constexpr auto operator != (
      BackwardAddressIterator const& iterator
  ) const noexcept -> bool;

  /// \brief Prefix Increment Operator. Will advance backward one position and then return
  /// \exceptsafe
  /// \return BackwardAddressIterator ref = Reference to the modified iterator
  ///
  /// \test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
  ///      LTC-00203-IT-perValueRevCheck,
  ///      LTC-00204-IT-perValueRevImmCheck,
  ///      LTC-00211-IT-itMutabilityStdRev
  /// }
  /// \public
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> BackwardAddressIterator&;

  /// \brief Postfix Increment Operator. Will return the original iterator, and then advance backward the current one
  /// \exceptsafe
  /// \return BackwardAddressIterator = A copy of the original iterator
  ///
  /// \test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
  ///      LTC-00203-IT-perValueRevCheck,
  ///      LTC-00204-IT-perValueRevImmCheck,
  ///      LTC-00211-IT-itMutabilityStdRev
  /// }
  /// \public
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> BackwardAddressIterator;

  /// \brief Prefix Decrement Operator. Will advance forward one position and then return
  /// \exceptsafe
  /// \return BackwardAddressIterator ref = Reference to the modified iterator
  ///
  /// \test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
  ///      LTC-00207-IT-perValueRevBwdCheck,
  ///      LTC-00208-IT-perValueRevBwdImmCheck
  /// }
  /// \public
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> BackwardAddressIterator&;

  /// \brief Postfix Decrement Operator. Will return the original iterator, and then advance forward the current one
  /// \exceptsafe
  /// \return BackwardAddressIterator = A copy of the original iterator
  ///
  ///
  /// \test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
  ///      LTC-00207-IT-perValueRevBwdCheck,
  ///      LTC-00208-IT-perValueRevBwdImmCheck
  /// }
  /// \public
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> BackwardAddressIterator;

  /// \brief Arithmetic Sum Operator, will return the iterator offset from a number of positions specified in the given value ( positive offset = backward advance - iterator is reverse )
  /// \tparam __NumericType is the type of the numeric value given
  /// \param [in] value : __NumericType = number of positions to advance
  /// \exceptsafe
  /// \return BackwardAddressIterator = Iterator at 'value' positions from the original iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  template < typename __NumericType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard constexpr auto operator + (
      __NumericType value
  ) const noexcept -> BackwardAddressIterator;

  /// \brief Arithmetic Sum Operator, will return the iterator offset from a number of positions specified in the given value from the given iterator ( positive offset = backward advance - iterator is reverse )
  /// \tparam __FElementType is the type of the element enclosed at the iterator value
  /// \tparam __NumericType is the type of the numeric value given
  /// \param [in] value : __NumericType = number of positions to advance
  /// \param [in] iterator : BackwardAddressIterator cref = Constant Reference to the iterator to start from
  /// \exceptsafe
  /// \return BackwardAddressIterator = Iterator at 'value' positions from the original iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  template <typename __FElementType, typename __NumericType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  friend constexpr auto operator + (
      __NumericType                                   value,
      BackwardAddressIterator <__FElementType> const& iterator
  ) noexcept -> BackwardAddressIterator <__FElementType>;

  /// \brief Difference Operator. Acquires the iterator offset negatively with a number of positions from the original iterator
  /// \tparam __NumericType is the type of the numeric value
  /// \param [in] value : __NumericType = offset value to subtract from the current iterator value in order to obtain the new iterator
  /// \exceptsafe
  /// \return BackwardAddressIterator = Iterator at 'value' positions backward ( forward, since reverse ) from the original iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  template < typename __NumericType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard constexpr auto operator - (
      __NumericType value
  ) const noexcept -> BackwardAddressIterator;

  /// \brief Difference Operator. Acquires the number of elements between two iterators
  /// \param [in] iterator : BackwardAddressIterator cref = Constant Reference to another iterator to acquire the distance to
  /// \exceptsafe
  /// \return Size = distance, positive, element count between the two iterators
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard constexpr auto operator - (
      BackwardAddressIterator const& iterator
  ) const noexcept -> Size;

  /// \brief Greater Than Operator. Checks if the current iterator is ahead of the given iterator, absolute position - lower address
  /// \param [in] iterator : BackwardAddressIterator cref = Constant Reference to another iterator to acquire the distance to
  /// \exceptsafe
  /// \return bool = true if current iterator has a lower address than the parameter iterator, false otherwise
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard constexpr auto operator > (
      BackwardAddressIterator const& iterator
  ) const noexcept -> bool;

  /// \brief Greater Than Operator. Checks if the current iterator is behind the given iterator, absolute position - higher address
  /// \param [in] iterator : BackwardAddressIterator cref = Constant Reference to another iterator to acquire the distance to
  /// \exceptsafe
  /// \return bool = true if current iterator has a higher address than the parameter iterator, false otherwise
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard constexpr auto operator < (
      BackwardAddressIterator const& iterator
  ) const noexcept -> bool;

  /// \brief Greater Than Operator. Checks if the current iterator is ahead of or at the given iterator, absolute position - lower or equal address
  /// \param [in] iterator : BackwardAddressIterator cref = Constant Reference to another iterator to acquire the distance to
  /// \exceptsafe
  /// \return bool = true if current iterator has a lower or equal address than the parameter iterator, false otherwise
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard constexpr auto operator >= (
      BackwardAddressIterator const& iterator
  ) const noexcept -> bool;

  /// \brief Greater Than Operator. Checks if the current iterator is behind or at the given iterator, absolute position - higher or equal address
  /// \param [in] iterator : BackwardAddressIterator cref = Constant Reference to another iterator to acquire the distance to
  /// \exceptsafe
  /// \return bool = true if current iterator has a higher or equal address than the parameter iterator, false otherwise
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard constexpr auto operator <= (
      BackwardAddressIterator const& iterator
  ) const noexcept -> bool;

private:
  /// \brief Function used to return the address before from an absolute point of view, as if forward iterator.
  /// Used in insertion after/before functions
  /// \exceptsafe
  /// \return Address = Address to absolute memory
  /// \test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: All
  /// \private
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto absoluteBefore () const noexcept -> Address override;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to return the address after from an absolute point of view, as if forward iterator.
  /// Used in insertion after/before functions
  /// \exceptsafe
  /// \return Address = Address to absolute memory
  /// \test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: All
  /// \private
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto absoluteAfter () const noexcept -> Address override;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using AbstractAddressIterator <__Element>::address;
};


/// \brief Arithmetic Sum Operator, will return the iterator offset from a number of positions specified in the given value from the given iterator ( reverse positioning due to reverse iterator )
/// \tparam __FElementType is the type of the element enclosed at the iterator value
/// \tparam __NumericType is the type of the numeric value given
/// \param [in] value : __NumericType = number of positions to advance
/// \param [in] iterator : BackwardAddressIterator cref = Constant Reference to the iterator to start from
/// \exceptsafe
/// \return BackwardAddressIterator = Iterator at 'value' positions from the original iterator
///
/// \test Suite: TBA, Group: TBA, Test Cases: TBA
/// \namespace cds::experimental
template <typename __FElementType, typename __NumericType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto operator + (
    __NumericType                                   value,
    BackwardAddressIterator <__FElementType> const& iterator
) noexcept -> BackwardAddressIterator <__FElementType>;


/// \brief Generic Address Iterator, iterating over continuous address ranges from from low to high or high to low value, based on reverse value.
/// \tparam __Element is the type of the enclosed element. Must not be decayed, as it can represent a const iterator
/// \tparam __reverse is whether the iterator should go backward or forward. If false, it will go forward, being a ForwardAddressIterator. Otherwise, backward, and will be a BackwardAddressIterator
/// \extends AbstractAddressIterator
///
/// \test Suite: TBA, Group: TBA, Test Cases: TBA
/// \namespace cds::experimental
template <typename __Element, bool __reverse = false> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using AddressIterator = cds::meta::Conditional <
    __reverse,
    BackwardAddressIterator <__Element>,
    ForwardAddressIterator <__Element>
>;
} // namespace cds

#endif // __CDS_SHARED_ADDRESS_ITERATOR_HPP__
