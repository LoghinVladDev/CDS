//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ADDRESS_ITERATOR_HPP_IMPL__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_ADDRESS_ITERATOR_HPP_IMPL__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr AbstractAddressIterator <__ElementType>::AbstractAddressIterator () noexcept = default;


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr AbstractAddressIterator <__ElementType>::AbstractAddressIterator (
    Address pElement
) noexcept : _currentAddress (pElement) {
  // copy given address value
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr AbstractAddressIterator <__ElementType>::AbstractAddressIterator (
    AbstractAddressIterator const& iterator
) noexcept : _currentAddress (iterator._currentAddress) {
  // copy iterator address value
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr AbstractAddressIterator <__ElementType>::AbstractAddressIterator (
    AbstractAddressIterator&& iterator
) noexcept : _currentAddress (cds::exchange (iterator._currentAddress, nullptr)) {
  // move iterator address value
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto AbstractAddressIterator <__ElementType>::operator= (
    AbstractAddressIterator const& iterator
) noexcept -> AbstractAddressIterator& {
  if(this == &iterator) {
    return *this;
  }

  _currentAddress = iterator._currentAddress;
  return *this;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto AbstractAddressIterator <__ElementType>::operator= (
    AbstractAddressIterator && iterator
) noexcept -> AbstractAddressIterator& {
  if(this == &iterator) {
    return *this;
  }

  _currentAddress = cds::exchange (iterator._currentAddress, nullptr);
  return *this;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto AbstractAddressIterator <__ElementType>::current () const noexcept -> Address {
  // return current address
  return _currentAddress;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto AbstractAddressIterator <__ElementType>::operator * () const noexcept -> __ElementType& {
  // return value at given address
  return *_currentAddress;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto AbstractAddressIterator <__ElementType>::operator -> () const noexcept -> __ElementType* {
  // return address of the element directly
  return _currentAddress;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto AbstractAddressIterator <__ElementType>::operator == (
    AbstractAddressIterator <__ElementType> const& iterator
) const noexcept -> bool {
  // iterators are equal if addresses are equal
  return current() == iterator.current();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto AbstractAddressIterator <__ElementType>::operator != (
    AbstractAddressIterator <__ElementType> const& iterator
) const noexcept -> bool {
  // iterators are not equal if addresses are not equal
  return current() != iterator.current();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto AbstractAddressIterator <__ElementType>::operator - (
    AbstractAddressIterator const& iterator
) const noexcept -> Size {
  // return the difference in absolute value
  return
      _currentAddress > iterator._currentAddress ?
      _currentAddress - iterator._currentAddress :
      iterator._currentAddress - _currentAddress;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < typename __NumericType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto AbstractAddressIterator <__ElementType>::operator [] (
    __NumericType index
) const noexcept -> ElementType& {
  // return the element at given offset
  return _currentAddress [index];
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto AbstractAddressIterator<__ElementType>::address() noexcept -> Address& {
  return _currentAddress;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto AbstractAddressIterator<__ElementType>::address() const noexcept -> Address const& {
  return _currentAddress;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr AbstractAddressIterator <__ElementType>::operator bool () const noexcept {
  // iterator is valid if not null
  return _currentAddress != nullptr;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto ForwardAddressIterator <__ElementType>::operator == (
    ForwardAddressIterator const& iterator
) const noexcept -> bool {
  // iterators are equal if addresses are equal
  return address() == iterator.address();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto ForwardAddressIterator <__ElementType>::operator != (
    ForwardAddressIterator const& iterator
) const noexcept -> bool {
  // iterators are not equal if addresses are not equal
  return address() != iterator.address();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto ForwardAddressIterator <__ElementType>::absoluteBefore () const noexcept -> Address {
  // Already forward, return current address
  return address();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto ForwardAddressIterator <__ElementType>::absoluteAfter () const noexcept -> Address {
  // Already forward, return current address
  return address();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto ForwardAddressIterator <__ElementType>::operator ++ () noexcept -> ForwardAddressIterator & {
  // Forward Iterator - advance forward
  ++address();
  return *this;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto ForwardAddressIterator <__ElementType>::operator ++ (int) noexcept -> ForwardAddressIterator {
  // Forward Iterator - create copy, advance forward, return copy
  auto copy = *this;
  ++address();
  return copy;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto ForwardAddressIterator <__ElementType>::operator -- () noexcept -> ForwardAddressIterator & {
  // Forward Iterator - advance backward
  --address();
  return *this;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto ForwardAddressIterator <__ElementType>::operator -- (int) noexcept -> ForwardAddressIterator {
  // Forward Iterator - create copy, advance backward, return copy
  auto copy = *this;
  --address();
  return copy;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < typename __NumericType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto ForwardAddressIterator <__ElementType>::operator + (
    __NumericType value
) const noexcept -> ForwardAddressIterator {
  // Forward Iterator - positive offset from current address
  return ForwardAddressIterator (address() + value);
}


template <typename __FElementType, typename __NumericType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto operator + (
    __NumericType                                   value,
    ForwardAddressIterator <__FElementType> const&  iterator
) noexcept -> ForwardAddressIterator <__FElementType> {
  // Forward Iterator - positive offset from given iterator address
  return ForwardAddressIterator <__FElementType> (iterator.address() + value);
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < typename __NumericType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto ForwardAddressIterator <__ElementType>::operator - (
    __NumericType value
) const noexcept -> ForwardAddressIterator {
  // Forward Iterator - negative offset from given iterator address
  return ForwardAddressIterator (address() - value);
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto ForwardAddressIterator <__ElementType>::operator - (
    ForwardAddressIterator const& iterator
) const noexcept -> Size {
  // Compute absolute distance between iterators
  return
      address() > iterator.address() ?
      address() - iterator.address() :
      iterator.address() - address();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto ForwardAddressIterator <__ElementType>::operator > (
    ForwardAddressIterator const& iterator
) const noexcept -> bool {
  // Forward Iterator - greater than iterator is same as greater than address
  return address() > iterator.address();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto ForwardAddressIterator <__ElementType>::operator < (
    ForwardAddressIterator const& iterator
) const noexcept -> bool {
  // Forward Iterator - less than iterator is same as less than address
  return address() < iterator.address();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto ForwardAddressIterator <__ElementType>::operator >= (
    ForwardAddressIterator const& iterator
) const noexcept -> bool {
  // Forward Iterator - greater than or equal to iterator is same as greater than or equal to address
  return address() >= iterator.address();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto ForwardAddressIterator <__ElementType>::operator <= (
    ForwardAddressIterator const& iterator
) const noexcept -> bool {
  // Forward Iterator - less than or equal to iterator is same as less than or equal to address
  return address() <= iterator.address();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto BackwardAddressIterator <__ElementType>::operator == (
    BackwardAddressIterator const& iterator
) const noexcept -> bool {
  // iterators are equal if addresses are equal
  return address() == iterator.address();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto BackwardAddressIterator <__ElementType>::operator != (
    BackwardAddressIterator const& iterator
) const noexcept -> bool {
  // iterators are not equal if addresses are not equal
  return address() != iterator.address();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto BackwardAddressIterator <__ElementType>::absoluteBefore () const noexcept -> Address {
  // is backward, shift one position to the right
  return address() + 1u;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto BackwardAddressIterator <__ElementType>::absoluteAfter () const noexcept -> Address {
  // is backward, shift one position to the left
  return address() - 1u;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto BackwardAddressIterator <__ElementType>::operator ++ () noexcept -> BackwardAddressIterator & {
  // Backward Iterator - advance backward
  --address();
  return *this;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto BackwardAddressIterator <__ElementType>::operator ++ (int) noexcept -> BackwardAddressIterator {
  // Backward Iterator - create copy, advance backward, return copy
  auto copy = *this;
  --address();
  return copy;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto BackwardAddressIterator <__ElementType>::operator -- () noexcept -> BackwardAddressIterator & {
  // Backward Iterator - advance forward
  ++address();
  return *this;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto BackwardAddressIterator <__ElementType>::operator -- (int) noexcept -> BackwardAddressIterator {
  // BackwardIterator - create copy, advance forward, return copy
  auto copy = *this;
  ++address();
  return copy;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < typename __NumericType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto BackwardAddressIterator <__ElementType>::operator + (
    __NumericType value
) const noexcept -> BackwardAddressIterator {
  // Backward Iterator - negative offset from current address
  return BackwardAddressIterator (address() - value);
}


template <typename __FElementType, typename __NumericType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto operator + (
    __NumericType                                   value,
    BackwardAddressIterator <__FElementType> const& iterator
) noexcept -> BackwardAddressIterator <__FElementType> {
  // Backward Iterator - negative offset from given iterator address
  return BackwardAddressIterator <__FElementType> (iterator.address() - value);
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template < typename __NumericType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto BackwardAddressIterator <__ElementType>::operator - (
    __NumericType value
) const noexcept -> BackwardAddressIterator {
  // Backward Iterator - positive offset from given iterator address
  return BackwardAddressIterator (address() + value);
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto BackwardAddressIterator <__ElementType>::operator - (
    BackwardAddressIterator const& iterator
) const noexcept -> Size {
  // Compute absolute distance between iterators
  return
      address() > iterator.address() ?
      address() - iterator.address() :
      iterator.address() - address();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto BackwardAddressIterator <__ElementType>::operator > (
    BackwardAddressIterator const& iterator
) const noexcept -> bool {
  // Backward Iterator - greater than iterator is same as less than address
  return address() < iterator.address();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto BackwardAddressIterator <__ElementType>::operator < (
    BackwardAddressIterator const& iterator
) const noexcept -> bool {
  // Backward Iterator - less than iterator is same as greater than address
  return address() > iterator.address();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto BackwardAddressIterator <__ElementType>::operator >= (
    BackwardAddressIterator const& iterator
) const noexcept -> bool {
  // Forward Iterator - greater than or equal to iterator is same as less than or equal to address
  return address() <= iterator.address();
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto BackwardAddressIterator <__ElementType>::operator <= (
    BackwardAddressIterator const& iterator
) const noexcept -> bool {
  // Forward Iterator - less than or equal to iterator is same as greater than or equal to address
  return address() >= iterator.address();
}

} // namespace cds

#endif // __CDS_SHARED_ADDRESS_ITERATOR_HPP_IMPL__
