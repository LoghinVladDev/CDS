//
// Created by loghin on 7/5/22.
//

#ifndef __CDS_SHARED_ARRAY_BASE_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_ARRAY_BASE_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces) 
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 

/// \class Base implementation class for array-based objects
///
/// Works with a two-headed buffer, allocated with a front and back capacity, to allow for pushFront and pushBack operations in O(1)
///
/// \tparam __Type is the element enclosed in the array
/// \tparam __equals is the function used to compare two elements
///
/// \test Suite: CTS-00001, Group: All, Test Cases: All
/// \test Suite: MCTS-00001, Group: All, Test Cases: All
///
/// \namespace cds::__hidden::__impl
/// \internal library-private

template <
    typename                                                      __Type,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
    functional::PredicateFunction <__Type const &, __Type const&> __equals  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
> class __ArrayBase {                                                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init)
public:
  /// \typedef Alias for forward mutable iterator
  /// \public
  using __ab_Iterator                      = ForwardAddressIterator <__Type>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \typedef Alias for forward immutable iterator
  /// \public
  using __ab_ConstIterator                 = ForwardAddressIterator <__Type const>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \typedef Alias for backward mutable iterator
  /// \public
  using __ab_ReverseIterator               = BackwardAddressIterator <__Type>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \typedef Alias for backward immutable iterator
  /// \public
  using __ab_ConstReverseIterator          = BackwardAddressIterator <__Type const>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \class Dispatcher to this class' implementation
  /// \implements __ListServerDispatcher
  /// \public
  template <typename __ServerType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  class __Dispatcher;               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Implicit Destructor, constexpr
  /// \exceptsafe
  /// \test Suite: CTS-00001, Group: All, Test Cases: All
  /// \test Suite: MCTS-00001, Group: All, Test Cases: All
  /// \public
  ~__ArrayBase () noexcept = default;

  /// \brief Deleted Copy Assignment Operator, constexpr
  /// \param [in] array : __ArrayBase cref = Constant Reference to an Array to copy the data from
  /// \exceptsafe
  /// \return __ArrayBase ref = Reference to the modified object
  /// \test Suite: CTS-00001, Group: All, Test Cases: All
  /// \test Suite: MCTS-00001, Group: All, Test Cases: All
  /// \public
  auto operator = (__ArrayBase const&) noexcept -> __ArrayBase& = delete;

  /// \brief Deleted Copy Assignment Operator, constexpr
  /// \param [in, out] array : __ArrayBase mref = Move Reference to an array to release and acquire the data from
  /// \exceptsafe
  /// \return __ArrayBase ref = Reference to the modified object
  /// \test Suite: CTS-00001, Group: All, Test Cases: All
  /// \test Suite: MCTS-00001, Group: All, Test Cases: All
  /// \public
  auto operator = (__ArrayBase&&) noexcept -> __ArrayBase& = delete;

protected:
  /// \typedef Alias for template parameter __Type
  /// \protected
  using ElementType = __Type;

  /// \brief Default Constructor, constexpr
  /// \exceptsafe
  /// \test Suite: CTS-00001, Group: All, Test Cases: All
  /// \test Suite: MCTS-00001, Group: All, Test Cases: All
  /// \protected
  constexpr __ArrayBase () noexcept = default;

  /// \brief Copy Constructor
  /// \param [in] array : __ArrayBase cref = Constant Reference to an Array to copy the data from
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \test Suite: CTS-00001, Group: All, Test Cases: All
  /// \test Suite: MCTS-00001, Group: All, Test Cases: All
  /// \protected
  __ArrayBase (__ArrayBase const& array) noexcept(false); // NOLINT(bugprone-reserved-identifier,google-explicit-constructor)

  /// \brief Move Constructor, constexpr
  /// \param [in, out] array : __ArrayBase mref = Move Reference to an array to release and acquire the data from
  /// \exceptsafe
  /// \test Suite: CTS-00001, Group: All, Test Cases: All
  /// \test Suite: MCTS-00001, Group: All, Test Cases: All
  /// \protected
  constexpr __ArrayBase (__ArrayBase&& array) noexcept;

  /// \brief Function used to clear either the contents of the buffer, or purge the whole array data
  /// \param [in] destroyBuffer : bool = if true, will purge the whole memory array data, otherwise, will only clear the buffer
  /// \exceptsafe
  /// \test Suite: CTS-00001, Group: All, Test Cases: All
  /// \test Suite: MCTS-00001, Group: All, Test Cases: All
  /// \protected

  auto __ab_clear (bool destroyBuffer) noexcept -> void; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  
  /// \brief Function used to acquire the number of elements in the array
  /// \exceptsafe
  /// \return Size = number of elements in the array
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard constexpr auto __ab_size() const noexcept -> Size; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard)

  /// \brief Function used to remove an element at a given index
  /// \param [in] index : Index = index of the element to be removed
  /// \exceptsafe
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ab_remove (Index index) noexcept -> void; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to remove an element at a given iterator
  /// \param [in] iterator : AbstractAddressIterator cref = Constant Reference to an iterator indicating to the element to be removed
  /// \exceptsafe
  /// \return bool = true if removal was successful, false otherwise
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ab_removeIterator (AbstractAddressIterator <__Type> const& iterator) noexcept -> bool; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to remove an element at a given const iterator
  /// \param [in] iterator : AbstractAddressIterator cref = Constant Reference to an iterator indicating to the element to be removed
  /// \exceptsafe
  /// \return bool = true if removal was successful, false otherwise
  ///  \test Suite: TBA, Group: TBA, Test Cases: TBA
  ///  \protected
  auto __ab_removeConstIterator (AbstractAddressIterator <__Type const> const& iterator) noexcept -> bool; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to remove multiple elements at a given number of iterators
  /// \param [in] ppIterators : AbstractAddressIterator cptr cptr  = Immutable Address to an array of Immutable Addresses to iterators
  /// \param [in] iteratorArrayCount : Size = number of iterators in the given array
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \return Size = number of removed elements
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ab_removeIteratorArray ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
      AbstractAddressIterator <__Type> const* const*  ppIterators,
      Size                                            iteratorCount
  ) noexcept(false) -> Size;

  /// \brief Function used to remove multiple elements at a given number of const iterators
  /// \param [in] ppIterators : AbstractAddressIterator cptr cptr  = Immutable Address to an array of Immutable Addresses to const iterators
  /// \param [in] iteratorArrayCount : Size = number of iterators in the given array
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \return Size = number of removed elements
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ab_removeConstIteratorArray ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
      AbstractAddressIterator <__Type const> const* const*  ppIterators,
      Size                                                  iteratorCount
  ) noexcept(false) -> Size;

  ///  \brief Function used to acquire an address to the element located at given index
  ///  \param [in] index : Index = index of the element to acquire the address of
  ///  \exceptsafe
  ///  \return ElementType ptr = Address of the requested element
  ///  \test Suite: TBA, Group: TBA, Test Cases: TBA
  ///  \protected
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __ab_get ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) 
      Index index
  ) noexcept -> ElementType*;

  /// \brief Function used to acquire an address to the element located at given index
  /// \param [in] index : Index = index of the element to acquire the address of
  /// \exceptsafe
  /// \return ElementType cptr = Address of the requested immutable element
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard constexpr auto __ab_get ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard) 
      Index index
  ) const noexcept -> ElementType const*;

  /// \brief Function used to allocate and return the address of the newly created element space in the front of the array
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \return ElementType ptr = Address to the new memory space
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard auto __ab_newFront () noexcept(false) -> ElementType*; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to allocate and return the address of the newly created element space in the back of the array
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \return ElementType ptr = Address to the new memory space
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard auto __ab_newBack () noexcept(false) -> ElementType*; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to allocate space for a number of elements at the front of the array, and return the addresses of each
  /// individual memory space in a given array
  /// \param [in] count : Size = number of elements space is required for
  /// \param [out] ppElements : __Type ptr ptr = Address to the array of addresses to populate with the newly created space
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ab_newFrontArray ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
      Size      count,
      __Type**  ppElements
  ) noexcept(false) -> void;

  /// \brief Function used to allocate space for a number of elements at the back of the array, and return the addresses of each
  /// individual memory space in a given array
  /// \param [in] count : Size = number of elements space is required for
  /// \param [out] ppElements : __Type ptr ptr = Address to the array of addresses to populate with the newly created space
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ab_newBackArray ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
      Size      count,
      __Type**  ppElements
  ) noexcept(false) -> void;

  /// \brief Function used to allocate space for an element, regardless of the location, and return the memory address
  /// \param [in] pReferenceElement : __Type cptr = Address to an Immutable Reference comparison element. Unused in array since no restriction for added values exists
  /// \param [out] pNewElementCreated : bool ptr = Address of a boolean value to be set to true if newly created value was created. In array, it is always set true
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \return __Type ptr = Address to the newly created space for the element
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ab_newAddress ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
      __Type const* pReferenceElement,
      bool*         pNewElementCreated
  ) noexcept(false) -> ElementType*;

  /// \brief Function used to allocate space for an element at a given index. Will move elements, starting with the given index, to the right
  /// \param index : Index = index to create the element at
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \return __Type ptr = Address to the newly created space for the element
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard auto __ab_newAt ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
      Index index
  ) noexcept(false) -> ElementType*;

  /// \brief Function used to allocate space for a given number of elements at a given index. Will move elements, starting with the given index, to the right
  /// \param [in] index : Index = index to create the element spaces at
  /// \param [in] count : Size = number of elements to be inserted at given index
  /// \param [out] ppElements : __Type ptr ptr = Address to the array of addresses to populate with the addresses of the newly created memory spaces
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ab_newArrayAt ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
      Index     index,
      Size      count,
      __Type**  ppElements
  ) noexcept(false) -> void;

  /// \brief Function used to allocate space for an element before a given iterator. Will move elements, starting with the given iterator element, to the right
  /// \param [in] iterator : AbstractAddressIterator cref = Constant Reference to the iterator to allocate an element space before
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \return __Type ptr = Address to the newly created space for the element
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ab_newBefore (AbstractAddressIterator <__Type> const& iterator) noexcept(false) -> __Type*; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to allocate space for an element before a given const iterator. Will move elements, starting with the given iterator element, to the right
  /// \param [in] iterator : AbstractAddressIterator cref = Constant Reference to the const iterator to allocate an element space before
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \return __Type ptr = Address to the newly created space for the element
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ab_newBeforeConst (AbstractAddressIterator <__Type const> const& iterator) noexcept(false) -> __Type*; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to allocate space for an element after a given iterator. Will move elements, starting after the given iterator element, to the right
  /// \param [in] iterator : AbstractAddressIterator cref = Constant Reference to the iterator to allocate an element space after
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \return __Type ptr = Address to the newly created space for the element
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ab_newAfter (AbstractAddressIterator <__Type> const& iterator) noexcept(false) -> __Type*; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to allocate space for an element after a given const iterator. Will move elements, starting after the given iterator element, to the right
  /// \param [in] iterator : AbstractAddressIterator cref = Constant Reference to the const iterator to allocate an element space after
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \return __Type ptr = Address to the newly created space for the element
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ab_newAfterConst (AbstractAddressIterator <__Type const> const& iterator) noexcept(false) -> __Type*; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to allocate space for a given number of elements before a given iterator. Will move elements, starting with the given iterator, to the right
  /// \param [in] iterator : AbstractAddressIterator cref = Constant Reference to the iterator to allocate the element spaces before
  /// \param [in] count : Size = number of elements to be inserted at given index
  /// \param [out] ppElements : __Type ptr ptr = Address to the array of addresses to populate with the addresses of the newly created memory spaces
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \return bool = true if allocation was successful, false otherwise
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ab_newBeforeArray ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
      AbstractAddressIterator <__Type> const& iterator,
      Size                                    count,
      __Type**                                ppElements
  ) noexcept(false) -> bool;

  /// \brief Function used to allocate space for a given number of elements before a given const iterator. Will move elements, starting with the given iterator, to the right
  /// \param [in] iterator : AbstractAddressIterator cref = Constant Reference to the const iterator to allocate the element spaces before
  /// \param [in] count : Size = number of elements to be inserted at given index
  /// \param [out] ppElements : __Type ptr ptr = Address to the array of addresses to populate with the addresses of the newly created memory spaces
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \return bool = true if allocation was successful, false otherwise
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ab_newBeforeArrayConst ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
      AbstractAddressIterator <__Type const> const& iterator,
      Size                                          count,
      __Type**                                      ppElements
  ) noexcept(false) -> bool;

  /// \brief Function used to allocate space for a given number of elements after a given iterator. Will move elements, starting after the given iterator, to the right
  /// \param [in] iterator : AbstractAddressIterator cref = Constant Reference to the iterator to allocate the element spaces after
  /// \param [in] count : Size = number of elements to be inserted at given index
  /// \param [out] ppElements : __Type ptr ptr = Address to the array of addresses to populate with the addresses of the newly created memory spaces
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \return bool = true if allocation was successful, false otherwise
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ab_newAfterArray ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
      AbstractAddressIterator <__Type> const& iterator,
      Size                                    count,
      __Type**                                ppElements
  ) noexcept(false) -> bool;

  /// \brief Function used to allocate space for a given number of elements after a given const iterator. Will move elements, starting after the given iterator, to the right
  /// \param [in] iterator : AbstractAddressIterator cref = Constant Reference to the const iterator to allocate the element spaces after
  /// \param [in] count : Size = number of elements to be inserted at given index
  /// \param [out] ppElements : __Type ptr ptr = Address to the array of addresses to populate with the addresses of the newly created memory spaces
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \return bool = true if allocation was successful, false otherwise
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ab_newAfterArrayConst ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
      AbstractAddressIterator <__Type const> const& iterator,
      Size                                          count,
      __Type**                                      ppElements
  ) noexcept(false) -> bool;

  /// \brief Function used to acquire a mutable forward iterator referencing the first element
  /// \excetpsafe
  /// \return __ab_Iterator = Address Iterator to the first element
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \protected
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __ab_begin () noexcept -> __ab_Iterator; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to acquire a mutable forward iterator referencing the space after the last element
  /// \excetpsafe
  /// \return __ab_Iterator = Address Iterator to the space after the last element
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \protected
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __ab_end () noexcept -> __ab_Iterator; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to acquire an immutable forward iterator referencing the first element
  /// \excetpsafe
  /// \return __ab_ConstIterator = Address Const Iterator to the first element
  /// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
  /// \protected
  __CDS_NoDiscard constexpr auto __ab_cbegin () const noexcept -> __ab_ConstIterator; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard)

  /// \brief Function used to acquire an immutable forward iterator referencing the space after the last element
  /// \excetpsafe
  /// \return __ab_ConstIterator = Address Const Iterator to the space after the last element
  /// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
  /// \protected
  __CDS_NoDiscard constexpr auto __ab_cend () const noexcept -> __ab_ConstIterator; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard)

  /// \brief Function used to acquire a mutable backward iterator referencing the last element
  /// \excetpsafe
  /// \return __ab_ReverseIterator = Address Iterator to the last element
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __ab_rbegin () noexcept -> __ab_ReverseIterator; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to acquire a mutable backward iterator referencing the space before the first element
  /// \excetpsafe
  /// \return __ab_ReverseIterator = Address Iterator to the space before the first element
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __ab_rend () noexcept -> __ab_ReverseIterator; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to acquire an immutable backward iterator referencing the last element
  /// \excetpsafe
  /// \return __ab_ConstReverseIterator = Address Const Iterator to the last element
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard constexpr auto __ab_crbegin () const noexcept -> __ab_ConstReverseIterator; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard)

  /// \brief Function used to acquire an immutable backward iterator referencing the space before the first element
  /// \excetpsafe
  /// \return __ab_ConstReverseIterator = Address Const Iterator to the space before the first element
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard constexpr auto __ab_crend () const noexcept -> __ab_ConstReverseIterator; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard)

  /// \brief Function used to acquire the address of the buffer, offset from the first element
  /// \exceptsafe
  /// \return __Type cptr = Equivalent to a C-Array, Address to the first immutable element
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard constexpr auto __ab_data () const noexcept -> __Type const *; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, modernize-use-nodiscard)

  /// \brief Function used to acquire the address of the buffer, offset from the first element
  /// \exceptsafe
  /// \return __Type ptr = Equivalent to a C-Array, Address to the first element
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __ab_data () noexcept -> __Type *; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to resize the element space to a given size. It will initialize the empty space with a default constructor
  /// \tparam __TElementType is an alias for __Type used to invoke substitution, enabling the function only if __Type is default constructible
  /// \param [in] size : Size = new size of the array
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  template <
      typename __TElementType = __Type,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsDefaultConstructible <__TElementType>::value> = 0
  > auto __ab_resize (Size size) noexcept(false) -> void; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to resize the element space to a given size. It will initialize the empty space with the received value
  /// \tparam __TElementType is an alias for __Type used to invoke substitution, enabling the function only if __Type is copy constructible
  /// \param [in] size : Size = new size of the array
  /// \param [in] defaultValue : __Type cref = Constant Reference to the element to be used initializing the newly created elements
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  template <
      typename __TElementType = __Type,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > auto __ab_resize (Size size, __Type const& defaultValue) noexcept(false) -> void; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to shrink the array to the given size. Will not do anything if given a size greater than actual
  /// \param [in] size : Size = new size of the array
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ab_shrink (Size size) noexcept -> void; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to enlarge, but not initialize the elements, the array to the given size. New space will NOT be initialized
  /// \param [in] size : Size = new size of the array
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ab_reserve (Size size) noexcept(false) -> void; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to clear the current contents and copy the data from a received array.
  /// \tparam __TElementType is an alias for __Type used to invoke substitution, enabling the function only if __Type is copy constructible
  /// \param [in] array : __ArrayBase cref = Constant Reference to an array to copy the data from
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  template <
      typename __TElementType = __Type,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > auto __ab_copy (__ArrayBase const& array) noexcept(false) -> void;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to clear the current contents and move the data from a received array.
  /// \param [in, out] array : __ArrayBase mref = Move Reference to an array to acquire and release the data from
  /// \exceptsafe
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  auto __ab_move (__ArrayBase&& array) noexcept -> void; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to compare the current array to a given array
  /// \param [in] array : __ArrayBase cref = Constant Reference to an array to compare the current one to
  /// \exceptsafe
  /// \return bool = true if arrays contain equal content, false otherwise
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \protected
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __ab_equals (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes)
      __ArrayBase const& array
  ) const noexcept -> bool;

  template <typename __Comparator = decltype (&cds::predicates::lessThan <__Type>)> auto __ab_sort (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Comparator const& comparator = &cds::predicates::lessThan <__Type>
  ) noexcept -> void;

private:
  /// \brief Starting and Minimum capacity for front and back allocation sizes
  /// \static
  /// \private
  static Size const __ab_minCapacity = 32ULL; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \struct Container for the elements required by the array
  /// \private
  struct __ArrayImplDataContainer { // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    /// \brief Pointer to the data buffer 
    __Type* _pBuffer            { nullptr };
    /// \brief Pointer to the first element in the buffer 
    __Type* _pFront             { nullptr };
    /// \brief Pointer to the element after the last in the buffer 
    __Type* _pBack              { nullptr };
    /// \brief Capacity allocated for front elements 
    Size    _frontCapacity      { 0ULL };
    /// \brief Capacity allocated for back elements 
    Size    _backCapacity       { 0ULL };
    /// \brief Next capacity allocated for front elements 
    Size    _frontNextCapacity  { 0ULL };
    /// \brief Next capacity allocated for back elements 
    Size    _backNextCapacity   { 0ULL };
  };
 
  /// \brief Pointer to the data required for the array
  /// \private     
  __ArrayImplDataContainer * _pData { nullptr };

  /// \brief Function used to initialize the array data at first use
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \test Suite: CTS-00001, Group: All, Test Cases: All
  /// \test Suite: MCTS-00001, Group: All, Test Cases: All
  /// \private
  auto __ab_init () noexcept(false) -> void; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to copy the data from a received array. It will NOT clear the array prior to copying
  /// \tparam __TElementType is an alias for __Type used to invoke substitution, enabling the function only if __Type is copy constructible
  /// \param [in] array : __ArrayBase cref = Constant Reference to an array to copy the data from
  /// \throws cds::OutOfMemoryException if required heap allocation fails
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \private
  template <
      typename __TElementType = __Type,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > auto __ab_copyCleared (__ArrayBase const& array) noexcept(false) -> void; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to move the data from a received array. It will NOT clear the array prior to copying
  /// \param [in, out] array : __ArrayBase mref = Move Reference to an array to acquire and release the data from
  /// \exceptsafe
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \private
  __CDS_cpplang_NonConstConstexprMemberFunction auto __ab_moveCleared (__ArrayBase&& array) noexcept -> void; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <
    typename                                                      __Type,               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Type const&, __Type const&>  __equals              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <typename __ServerType> class __ArrayBase <__Type, __equals>::__Dispatcher : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __ListServerDispatcher <
        __ServerType, __ArrayBase, __Type,
        AbstractAddressIterator <__Type>, AbstractAddressIterator <__Type const>,
        ForwardAddressIterator <__Type>, ForwardAddressIterator <__Type const>,
        BackwardAddressIterator <__Type>, BackwardAddressIterator <__Type const>,
        &__ArrayBase::__ab_begin, &__ArrayBase::__ab_end,
        &__ArrayBase::__ab_cbegin, &__ArrayBase::__ab_cend,
        &__ArrayBase::__ab_rbegin, &__ArrayBase::__ab_rend,
        &__ArrayBase::__ab_crbegin, &__ArrayBase::__ab_crend,
        &__ArrayBase::__ab_newAddress, &__ArrayBase::__ab_newFront, &__ArrayBase::__ab_newBack,
        &__ArrayBase::__ab_newFrontArray, &__ArrayBase::__ab_newBackArray,
        &__ArrayBase::__ab_newBefore, &__ArrayBase::__ab_newBeforeConst,
        &__ArrayBase::__ab_newAfter, &__ArrayBase::__ab_newAfterConst,
        &__ArrayBase::__ab_newBeforeArray, &__ArrayBase::__ab_newBeforeArrayConst,
        &__ArrayBase::__ab_newAfterArray, &__ArrayBase::__ab_newAfterArrayConst,
        &__ArrayBase::__ab_removeIterator, &__ArrayBase::__ab_removeConstIterator,
        &__ArrayBase::__ab_removeIteratorArray, &__ArrayBase::__ab_removeConstIteratorArray
    > {};

} // namespace __impl 
} // namespace __hidden 
} // namespace cds 

#endif // __CDS_SHARED_ARRAY_BASE_HPP__ 
