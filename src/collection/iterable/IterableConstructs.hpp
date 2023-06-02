//
// Created by loghin on 30/10/22.
//

#ifndef __CDS_ITERABLE_CONSTRUCTS_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_ITERABLE_CONSTRUCTS_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)

/// \brief Pre-declaration of the Iterable interface
/// \namespace cds
template <typename> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class Iterable;

namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

/// \brief Function passed to client to check if a given iterable element contains a received value element
/// \tparam __ElementType the type of the value given and of the values enclosed in the iterable
/// \param [in] iterable : Iterable cref = Constant Reference to an iterable containing elements of required type
/// \param [in] element : __ElementType cref = Constant Reference to a value of the required type to be found in the given iterable
/// \exceptsafe
/// \return bool = true if iterable contains given element, false otherwise
/// \test Not Applicable
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __iterableContains (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::Iterable <__ElementType> const&  iterable,
    __ElementType const&                  element
) noexcept -> bool;

/// \brief Function passed to client to check if a given iterable element does not contain a received value element
/// \tparam __ElementType the type of the value given and of the values enclosed in the iterable
/// \param [in] iterable : Iterable cref = Constant Reference to an iterable containing elements of required type
/// \param [in] element : __ElementType cref = Constant Reference to a value of the required type to be found in the given iterable
/// \exceptsafe
/// \return bool = true if iterable does not contain the given element, false otherwise
/// \test Not Applicable
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __iterableNotContains (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::Iterable <__ElementType> const&  iterable,
    __ElementType const&                  element
) noexcept -> bool;


/// \brief Function passed to client to check if a given std::initializer_list element contains a received value element
/// \tparam __ElementType the type of the value given and of the values enclosed in the initializer list
/// \tparam __function the function used to compare equality, since std::initializer_list does not have .contains, and must be iterated and its elements compared to detect inclusion
/// \param [in] list : std::initializer_list cref = Constant Reference to an initializer list containing elements of required type
/// \param [in] element : __ElementType cref = Constant Reference to a value of the required type to be found in the given initializer list
/// \exceptsafe
/// \return bool = true if initializer list contains given element, false otherwise
/// \test Not Applicable
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __function      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __initializerListContains (                                                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,///-avoid-non-const-global-variables)
    std::initializer_list <__ElementType> const&  list,
    __ElementType const&                          element
) noexcept -> bool;


/// \brief Function passed to client to check if a given std::initializer_list element does not contain a received value element
/// \tparam __ElementType the type of the value given and of the values enclosed in the initializer list
/// \tparam __function the function used to compare equality, since std::initializer_list does not have .contains, and must be iterated and its elements compared to detect inclusion
/// \param [in] list : std::initializer_list cref = Constant Reference to an initializer list containing elements of required type
/// \param [in] element : __ElementType cref = Constant Reference to a value of the required type to be found in the given initializer list
/// \exceptsafe
/// \return bool = true if initializer list does not contain given element, false otherwise
/// \test Not Applicable
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <
    typename                                                                    __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>  __function      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __initializerListNotContains (                                                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,///-avoid-non-const-global-variables)
    std::initializer_list <__ElementType> const&  list,
    __ElementType const&                            element
) noexcept -> bool;


/// \class Alias used by Iterable to extend the Communication Channel object
/// \tparam __ElementType the type of the elements enclosed in the extending Iterable
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __IterableCommunicationChannel : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __IterableInternalCommunicationChannel <
        cds::Iterable <__ElementType>,
        __ElementType
    > {};


/// \class Alias used by Iterable to implement the Delegate Forward Const Iterable Client
/// \tparam __ElementType the type of the elements enclosed in the extending Iterable
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __IterableDelegateForwardConstIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __DelegateForwardConstIterablePrimitiveClient <
        cds::Iterable <__ElementType>,
        __ElementType,
        false
    > {};


/// \class Alias used by Iterable to implement the Contains Of Iterable Client
/// \tparam __ElementType the type of the elements enclosed in the extending Iterable
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __IterableContainsOfIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __ContainsOfCompositeClient <
        cds::Iterable <__ElementType>,
        __ElementType,
        cds::Iterable <__ElementType>,
        &__iterableContains <__ElementType>
    > {};


/// \class Alias used by Iterable to implement the Contains of Initializer List Client
/// \tparam __ElementType the type of the elements enclosed in the extending Iterable
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __IterableContainsOfInitializerListClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __ContainsOfCompositeClient <
        cds::Iterable <__ElementType>,
        __ElementType,
        std::initializer_list <__ElementType>,
        &__initializerListContains < __ElementType, &cds::meta::equals <__ElementType> >
    > {};


/// \class Alias used by Iterable to implement the Find Of Immutable Iterable Client
/// \tparam __ElementType the type of the elements enclosed in the extending Iterable
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __IterableFindOfIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __FindOfImmutableCompositeClient <
        cds::Iterable <__ElementType>,
        __ElementType,
        typename __IterableDelegateForwardConstIterableClient <__ElementType>::ConstIterator,
        cds::Iterable <__ElementType>,
        &__iterableContains <__ElementType>,
        &__iterableNotContains <__ElementType>
    > {};


/// \class Alias used by Iterable to implement the Find Of Immutable Initializer List Client
/// \tparam __ElementType the type of the elements enclosed in the extending Iterable
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __IterableFindOfInitializerListClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __FindOfImmutableCompositeClient <
        cds::Iterable <__ElementType>,
        __ElementType,
        typename __IterableDelegateForwardConstIterableClient <__ElementType>::ConstIterator,
        std::initializer_list <__ElementType>,
        &__initializerListContains <__ElementType, &cds::meta::equals <__ElementType>>,
        &__initializerListNotContains <__ElementType, &cds::meta::equals <__ElementType>>
    > {};


/// \class Alias used by Iterable to implement the Find by Immutable Predicate Client
/// \tparam __ElementType the type of the elements enclosed in the extending Iterable
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __IterableFindByClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __FindByImmutableCompositeClient <
        cds::Iterable <__ElementType>,
        __ElementType,
        typename __IterableDelegateForwardConstIterableClient <__ElementType>::ConstIterator
    > {};


/// \typedef Alias used by Iterable to implement the Generic Immutable Statements Client
/// \tparam __ElementType the type of the elements enclosed in the extending Iterable
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __IterableGenericStatementsClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __GenericImmutableStatementsCompositeClient <
        cds::Iterable <__ElementType>,
        __ElementType
    > {};

} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_ITERABLE_CONSTRUCTS_HPP__
