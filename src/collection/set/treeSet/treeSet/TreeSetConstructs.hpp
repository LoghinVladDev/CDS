//
// Created by stefan on 28.08.2022.
//

#ifndef __CDS_TREE_SET_CONSTRUCTS_HPP__
#define __CDS_TREE_SET_CONSTRUCTS_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {
template <
    typename __ElementType,                                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Comparator = functional::DecoratedPredicate <  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
        cds::functional::PredicateFunction <__ElementType const&, __ElementType const&>,
        &cds::predicates::lessThan <__ElementType>
    >
> class TreeSet;

namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ElementType>                                                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __treeSetKeyExtractor (__ElementType const& element) noexcept -> __ElementType const& { // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  return element;
}


template <typename __ElementType>                                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __treeSetDestructor (__ElementType& element) noexcept -> void {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  element.~__ElementType();
}


template <typename __ElementType>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __treeSetCopyConstructor (     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __ElementType&        destination,
    __ElementType const&  source
) noexcept -> void {
  (void) new (&destination) __ElementType (source);
}


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeSetImplementation :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __RedBlackTree <
        __ElementType,
        __ElementType,
        __Comparator,
        &__treeSetKeyExtractor <__ElementType>,
        &cds::meta::equals <__ElementType>,
        &__treeSetDestructor <__ElementType>
    > {};


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeSetDispatcher :       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __TreeSetImplementation <__ElementType, __Comparator>::template __SetDispatcher <
        cds::TreeSet <__ElementType, __Comparator>
    > {};


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeSetServer :           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __SetServer <cds::TreeSet <__ElementType, __Comparator>, __ElementType> {};


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeSetDelegateForwardConstIterableClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardConstIterablePrimitiveClient <
        cds::TreeSet <__ElementType, __Comparator>,
        typename __TreeSetImplementation <__ElementType, __Comparator>::__rbt_ConstIterator
    > {};


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeSetDelegateBackwardConstIterableClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateBackwardConstIterablePrimitiveClient <
        cds::TreeSet <__ElementType, __Comparator>,
        typename __TreeSetImplementation <__ElementType, __Comparator>::__rbt_ReverseConstIterator
    > {};


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeSetConstIteratorRemoveClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalConstIteratorRemovePrimitiveClient <
        cds::TreeSet <__ElementType, __Comparator>, __ElementType,
        typename __TreeSetImplementation <__ElementType, __Comparator>::__rbt_AbstractConstIterator
    > {};


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeSetRandomInsertionClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRandomInsertionPrimitiveClient <
        cds::TreeSet <__ElementType, __Comparator>, __ElementType, __ElementType const
    > {};

template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeSetFindUniqueClient :       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindUniqueImmutablePrimitiveClient <
        cds::TreeSet <__ElementType, __Comparator>, __ElementType,
        typename __TreeSetImplementation <__ElementType, __Comparator>::__rbt_ConstIterator
    > {};


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeSetContainsOfCollectionClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        cds::TreeSet <__ElementType, __Comparator>, __ElementType,
        cds::Iterable <__ElementType>, &__iterableContains <__ElementType>
    > {};


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeSetContainsOfInitializerListClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        cds::TreeSet <__ElementType, __Comparator>, __ElementType,
        std::initializer_list <__ElementType>,
        &__initializerListContains  <__ElementType, &cds::meta::equals <__ElementType>>
    > {};


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeSetFindOfCollectionClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        cds::TreeSet <__ElementType, __Comparator>, __ElementType,
        AbstractRedBlackTreeConstIterator <__ElementType>,
        cds::Iterable <__ElementType>,
        &__iterableContains <__ElementType>, &__iterableNotContains <__ElementType>
    > {};


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeSetFindOfInitializerListClient :     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        cds::TreeSet <__ElementType, __Comparator>, __ElementType,
        AbstractRedBlackTreeConstIterator <__ElementType>,
        std::initializer_list <__ElementType>,
        &__initializerListContains < __ElementType, &cds::meta::equals <__ElementType> >,
        &__initializerListNotContains < __ElementType, &cds::meta::equals <__ElementType> >
    > {};


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeSetFindByClient :           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByImmutableCompositeClient <
        cds::TreeSet <__ElementType, __Comparator>, __ElementType,
        AbstractRedBlackTreeConstIterator <__ElementType>
    > {};


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeSetRemoveOfCollectionClient :       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        cds::TreeSet <__ElementType, __Comparator>, __ElementType,
        cds::Iterable <__ElementType>, &__iterableContains <__ElementType>
    > {};


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeSetRemoveOfInitializerListClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        cds::TreeSet <__ElementType, __Comparator>, __ElementType,
        std::initializer_list<__ElementType>,
        &__initializerListContains < __ElementType, &cds::meta::equals <__ElementType> >
    > {};


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeSetRemoveByClient :                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveByCompositeClient <cds::TreeSet <__ElementType, __Comparator>, __ElementType> {};


template <typename __ElementType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __TreeSetGenericStatementsClient :        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __GenericImmutableStatementsCompositeClient <cds::TreeSet <__ElementType, __Comparator>, __ElementType> {};
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_TREE_SET_CONSTRUCTS_HPP__
