//
// Created by loghin on 30/10/22.
//

#ifndef __CDS_ITERABLE_FUNCTIONS_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_ITERABLE_FUNCTIONS_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

/// \class Represents the container for the function utility functions
/// \tparam __ElementType is the type of the elements contained by the Iterable
/// \tparam __compare is an address to a comparison function, default cds::meta::equals
/// \test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <
    typename                                                                    __ElementType,                                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __compare = &cds::meta::equals <__ElementType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __IterableFunctions {                                                                                                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
protected:
  /// \brief Function used to check if two elements of the iterable are equal
  /// \param left : __ElementType cref = Constant Reference to one of the elements involved in the comparison
  /// \param left : __ElementType cref = Constant Reference to another one of the elements involved in the comparison
  /// \exceptsafe
  /// \return bool = true if elements are equal, false otherwise
  /// \test Suite: CTS-00001, Group: CTG-00002-MF, Test Cases: { CTC-00010-MF-clear, CTC-00011-MF-equalsSelf,
  ///      CTC-00012-MF-equalsTrueSameType, CTC-00013-MF-equalsTrueDifferentType, CTC-00014-MF-equalsFalseSameType,
  ///      CTC-00015-MF-equalsFalseDifferentType, CTC-00016-MF-equalsFalseNotCollection }
  /// \protected
  __CDS_NoDiscard constexpr static auto __if_equals ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __ElementType const& left,
      __ElementType const& right
  ) noexcept -> bool;
};

} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_ITERABLE_FUNCTIONS_HPP__
