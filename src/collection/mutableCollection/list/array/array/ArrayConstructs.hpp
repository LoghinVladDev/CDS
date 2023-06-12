// NOLINT(llvm-header-guard)
// Created by loghin on 08/07/22.
//

#ifndef __CDS_ARRAY_CONSTRUCTS_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_ARRAY_CONSTRUCTS_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {             // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __ElementType>                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayImplementation :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __ArrayBase <__ElementType, &cds::meta::equals <__ElementType>> {};


template <typename __ElementType>             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayDispatcher :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __ArrayImplementation <__ElementType>::template __Dispatcher <Array <__ElementType>> {};


template <typename __ElementType>         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayServer :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __ListServer <cds::Array <__ElementType>, __ElementType> {};


template <typename __ElementType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayRandomInsertionClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRandomInsertionPrimitiveClient <
        cds::Array <__ElementType>,
        __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables)
        __ElementType
    > {};


template <typename __ElementType>                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayBoundaryInsertionClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalBoundaryInsertionPrimitiveClient <
        cds::Array <__ElementType>,
        __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables)
        __ElementType
    > {};


template <typename __ElementType>                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayIteratorRelativeInsertionClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalIteratorRelativeInsertionPrimitiveClient <
        cds::Array <__ElementType>,
        __ElementType,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables)
        AbstractAddressIterator <__ElementType>
    > {};


template <typename __ElementType>                                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayConstIteratorRelativeInsertionClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalConstIteratorRelativeInsertionPrimitiveClient <
        cds::Array <__ElementType>,
        __ElementType,                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables)
        AbstractAddressIterator <__ElementType const>
    > {};


template <typename __ElementType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayFindOfIterableClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfMutableCompositeClient <
        cds::Array <__ElementType>, __ElementType,
        AddressIterator <__ElementType>, cds::Iterable <__ElementType>,
        &__iterableContains <__ElementType>, &__iterableNotContains <__ElementType>
    > {};


template <typename __ElementType>                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayFindOfInitializerListClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfMutableCompositeClient <
        cds::Array <__ElementType>, __ElementType,
        AddressIterator <__ElementType>, std::initializer_list <__ElementType>,
        &__initializerListContains <__ElementType, &cds::meta::equals <__ElementType>>,
        &__initializerListNotContains <__ElementType, &cds::meta::equals <__ElementType>>
    > {};


template <typename __ElementType>                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayFindConstOfIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        cds::Array <__ElementType>, __ElementType,
        AddressIterator < __ElementType const >, cds::Iterable <__ElementType>,
        &__iterableContains <__ElementType>, &__iterableNotContains <__ElementType>
    > {};


template <typename __ElementType>                                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayFindConstOfInitializerListClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        cds::Array <__ElementType>, __ElementType,
        AddressIterator < __ElementType const >, std::initializer_list <__ElementType>,
        &__initializerListContains <__ElementType, &cds::meta::equals <__ElementType>>,
        &__initializerListNotContains <__ElementType, &cds::meta::equals <__ElementType>>
    > {};


template <typename __ElementType>               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayFindByClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByMutableCompositeClient <
        cds::Array <__ElementType>, __ElementType, AddressIterator <__ElementType>
    > {};


template <typename __ElementType>                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayFindConstByClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByImmutableCompositeClient <
        cds::Array <__ElementType>, __ElementType, AddressIterator <__ElementType const>
    > {};


template <typename __ElementType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayIteratorRemoveClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalIteratorRemovePrimitiveClient <
        cds::Array <__ElementType>, __ElementType, AbstractAddressIterator <__ElementType>
    > {};


template <typename __ElementType>                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayConstIteratorRemoveClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalConstIteratorRemovePrimitiveClient <
        cds::Array <__ElementType>, __ElementType, AbstractAddressIterator <__ElementType const>
    > {};


template <typename __ElementType>                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayRemoveOfIterableClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        cds::Array <__ElementType>, __ElementType,
        cds::Iterable <__ElementType>, &__iterableContains <__ElementType>
    > {};


template <typename __ElementType>                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayRemoveOfInitializerListClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        cds::Array <__ElementType>, __ElementType,
        std::initializer_list <__ElementType>,
        &__initializerListContains <__ElementType, &cds::meta::equals <__ElementType>>
    > {};


template <typename __ElementType>                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayRemoveByClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveByCompositeClient <cds::Array <__ElementType>, __ElementType> {};


template <typename __ElementType>                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayGenericStatementsClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericMutableStatementsCompositeClient <cds::Array <__ElementType>, __ElementType> {};


template <typename __ElementType>                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayGenericConstStatementsClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericImmutableStatementsCompositeClient <cds::Array <__ElementType>, __ElementType> {};


template <typename __ElementType>               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayReplaceClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalReplaceCompositeClient <cds::Array <__ElementType>, __ElementType> {};


template <typename __ElementType>                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayReplaceOfIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalReplaceOfCompositeClient <
        cds::Array <__ElementType>, __ElementType,
        cds::Iterable <__ElementType>, &__iterableContains <__ElementType>
    > {};


template <typename __ElementType>                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayReplaceOfInitializerListClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalReplaceOfCompositeClient <
        cds::Array <__ElementType>, __ElementType,
        std::initializer_list <__ElementType>,
        &__initializerListContains < __ElementType, &cds::meta::equals <__ElementType> >
    > {};


template <typename __ElementType>                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayReplaceByClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalReplaceByCompositeClient <cds::Array <__ElementType>, __ElementType> {};


template <typename __ElementType>                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayIndexedOperationsClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalIndexedOperationsPrimitiveClient <cds::Array <__ElementType>, __ElementType> {};


template <typename __ElementType>               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayIndicesClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalIndicesCompositeClient <cds::Array <__ElementType>, __ElementType> {};


template <typename __ElementType>                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayIndicesOfIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalIndicesOfCompositeClient <
        cds::Array <__ElementType>, __ElementType,
        cds::Iterable <__ElementType>, &__iterableContains <__ElementType>
    > {};


template <typename __ElementType>                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayIndicesOfInitializerListClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalIndicesOfCompositeClient <
        cds::Array <__ElementType>, __ElementType,
        std::initializer_list <__ElementType>,
        &__initializerListContains < __ElementType, &cds::meta::equals <__ElementType> >
    > {};


template <typename __ElementType>                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayIndicesByClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalIndicesByCompositeClient <cds::Array <__ElementType>, __ElementType> {};


template <typename __ElementType>                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayContainsOfIterableClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        cds::Array <__ElementType>, __ElementType,
        cds::Iterable <__ElementType>, &__iterableContains <__ElementType>
    > {};


template <typename __ElementType>                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayContainsOfInitializerListClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        cds::Array <__ElementType>, __ElementType,
        std::initializer_list <__ElementType>,
        &__initializerListContains < __ElementType, &cds::meta::equals <__ElementType> >
    > {};


template <typename __ElementType>                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayDelegateForwardIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardIterablePrimitiveClient <
        cds::Array <__ElementType>, typename __ArrayImplementation <__ElementType>::__ab_Iterator
    > {};


template <typename __ElementType>                                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayDelegateForwardConstIterableClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardConstIterablePrimitiveClient <
        cds::Array <__ElementType>, typename __ArrayImplementation <__ElementType>::__ab_ConstIterator
    > {};


template <typename __ElementType>                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayDelegateBackwardIterableClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateBackwardIterablePrimitiveClient <
        cds::Array <__ElementType>, typename __ArrayImplementation <__ElementType>::__ab_ReverseIterator
    > {};


template <typename __ElementType>                                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ArrayDelegateBackwardConstIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateBackwardConstIterablePrimitiveClient <
        cds::Array <__ElementType>, typename __ArrayImplementation <__ElementType>::__ab_ConstReverseIterator
    > {};

} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_ARRAY_CONSTRUCTS_HPP__
