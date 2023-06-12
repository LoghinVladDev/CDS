// NOLINT(llvm-header-guard)
// Created by loghin on 08/07/22.
//

#ifndef __CDS_LINKED_LIST_CONSTRUCTS_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_LINKED_LIST_CONSTRUCTS_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __ElementType>                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListImplementation : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __DoubleLinkedList <__ElementType, &cds::meta::equals <__ElementType>> {};


template <typename __ElementType>                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListDispatcher : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LinkedListImplementation <__ElementType>::template __Dispatcher <LinkedList <__ElementType>> {};


template <typename __ElementType>             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListServer : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __ListServer <cds::LinkedList <__ElementType>, __ElementType> {};


template <typename __ElementType>                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListRandomInsertionClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRandomInsertionPrimitiveClient <
        cds::LinkedList <__ElementType>, __ElementType, __ElementType
    > {};


template <typename __ElementType>                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListBoundaryInsertionClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalBoundaryInsertionPrimitiveClient <
        cds::LinkedList <__ElementType>, __ElementType, __ElementType
    > {};


template <typename __ElementType>                                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListIteratorRelativeInsertionClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalIteratorRelativeInsertionPrimitiveClient <
        cds::LinkedList <__ElementType>, __ElementType, AbstractBidirectionalNodeIterator <__ElementType>
    > {};


template <typename __ElementType>                                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListConstIteratorRelativeInsertionClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalConstIteratorRelativeInsertionPrimitiveClient <
        cds::LinkedList <__ElementType>, __ElementType, AbstractBidirectionalNodeIterator <__ElementType const>
    > {};


template <typename __ElementType>                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListFindOfIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfMutableCompositeClient <
        cds::LinkedList <__ElementType>, __ElementType, ForwardBidirectionalNodeIterator <__ElementType>,
        cds::Iterable <__ElementType>, &__iterableContains <__ElementType>, &__iterableNotContains <__ElementType>
    > {};


template <typename __ElementType>                                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListFindOfInitializerListClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfMutableCompositeClient <
        cds::LinkedList <__ElementType>, __ElementType,
        ForwardBidirectionalNodeIterator <__ElementType>,
        std::initializer_list <__ElementType>,
        &__initializerListContains <__ElementType, &cds::meta::equals <__ElementType>>,
        &__initializerListNotContains <__ElementType, &cds::meta::equals <__ElementType>>
    > {};


template <typename __ElementType>                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListFindConstOfIterableClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        cds::LinkedList <__ElementType>, __ElementType, ForwardBidirectionalNodeIterator <__ElementType const>,
        cds::Iterable <__ElementType>, &__iterableContains <__ElementType>, &__iterableNotContains <__ElementType>
    > {};


template <typename __ElementType>                                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListFindConstOfInitializerListClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        cds::LinkedList <__ElementType>, __ElementType,
        ForwardBidirectionalNodeIterator <__ElementType const>,
        std::initializer_list <__ElementType>,
        &__initializerListContains <__ElementType, &cds::meta::equals <__ElementType>>,
        &__initializerListNotContains <__ElementType, &cds::meta::equals <__ElementType>>
    > {};


template <typename __ElementType>                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListFindByClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByMutableCompositeClient <
        cds::LinkedList <__ElementType>, __ElementType, ForwardBidirectionalNodeIterator <__ElementType>
    > {};


template <typename __ElementType>                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListFindConstByClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByImmutableCompositeClient <
        cds::LinkedList <__ElementType>, __ElementType, ForwardBidirectionalNodeIterator <__ElementType const>
    > {};


template <typename __ElementType>                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListIteratorRemoveClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalIteratorRemovePrimitiveClient <
        cds::LinkedList <__ElementType>, __ElementType, AbstractBidirectionalNodeIterator <__ElementType>
    > {};


template <typename __ElementType>                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListConstIteratorRemoveClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalConstIteratorRemovePrimitiveClient <
        cds::LinkedList <__ElementType>, __ElementType, AbstractBidirectionalNodeIterator <__ElementType const>
    > {};


template <typename __ElementType>                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListRemoveOfIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        cds::LinkedList <__ElementType>, __ElementType,
        cds::Iterable <__ElementType>, &__iterableContains <__ElementType>
    > {};


template <typename __ElementType>                                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListRemoveOfInitializerListClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        cds::LinkedList <__ElementType>, __ElementType,
        std::initializer_list <__ElementType>,
        &__initializerListContains <__ElementType, &cds::meta::equals <__ElementType>>
    > {};


template <typename __ElementType>                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListRemoveByClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveByCompositeClient <cds::LinkedList <__ElementType>, __ElementType> {};


template <typename __ElementType>                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListGenericStatementsClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericMutableStatementsCompositeClient <cds::LinkedList <__ElementType>, __ElementType> {};


template <typename __ElementType>                                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListGenericConstStatementsClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericImmutableStatementsCompositeClient <cds::LinkedList <__ElementType>, __ElementType> {};


template <typename __ElementType>                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListReplaceClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalReplaceCompositeClient <cds::LinkedList <__ElementType>, __ElementType> {};


template <typename __ElementType>                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListReplaceOfIterableClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalReplaceOfCompositeClient <
        cds::LinkedList <__ElementType>, __ElementType,
        cds::Iterable <__ElementType>, &__iterableContains <__ElementType>
    > {};


template <typename __ElementType>                                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListReplaceOfInitializerListClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalReplaceOfCompositeClient <
        cds::LinkedList <__ElementType>, __ElementType,
        std::initializer_list <__ElementType>,
        &__initializerListContains <__ElementType, &cds::meta::equals <__ElementType>>
    > {};


template <typename __ElementType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListReplaceByClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalReplaceByCompositeClient <cds::LinkedList <__ElementType>, __ElementType> {};


template <typename __ElementType>                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListIndexedOperationsClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalIndexedOperationsPrimitiveClient <cds::LinkedList <__ElementType>, __ElementType> {};


template <typename __ElementType>                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListIndicesClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalIndicesCompositeClient <cds::LinkedList <__ElementType>, __ElementType> {};


template <typename __ElementType>                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListIndicesOfIterableClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalIndicesOfCompositeClient <
        cds::LinkedList <__ElementType>, __ElementType,
        cds::Iterable <__ElementType>, &__iterableContains <__ElementType>
    > {};


template <typename __ElementType>                                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListIndicesOfInitializerListClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalIndicesOfCompositeClient <
        cds::LinkedList <__ElementType>, __ElementType,
        std::initializer_list <__ElementType>,
        &__initializerListContains <__ElementType, &cds::meta::equals <__ElementType>>
    > {};


template <typename __ElementType>                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListIndicesByClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalIndicesByCompositeClient <cds::LinkedList <__ElementType>, __ElementType> {};


template <typename __ElementType>                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListContainsOfIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        cds::LinkedList <__ElementType>, __ElementType,
        cds::Iterable <__ElementType>, &__iterableContains <__ElementType>
    > {};


template < typename __ElementType>                                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListContainsOfInitializerListClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        cds::LinkedList <__ElementType>, __ElementType,
        std::initializer_list <__ElementType>,
        &__initializerListContains <__ElementType, &cds::meta::equals <__ElementType>>
    > {};


template <typename __ElementType>                                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListDelegateForwardIterableClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardIterablePrimitiveClient <
        cds::LinkedList <__ElementType>, typename __LinkedListImplementation <__ElementType>::__dll_Iterator
    > {};


template <typename __ElementType>                                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListDelegateForwardConstIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardConstIterablePrimitiveClient <
        cds::LinkedList <__ElementType>, typename __LinkedListImplementation <__ElementType>::__dll_ConstIterator
    > {};


template <typename __ElementType>                                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListDelegateBackwardIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateBackwardIterablePrimitiveClient <
        cds::LinkedList <__ElementType>, typename __LinkedListImplementation <__ElementType>::__dll_ReverseIterator
    > {};


template <typename __ElementType>                                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedListDelegateBackwardConstIterableClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateBackwardConstIterablePrimitiveClient <
        cds::LinkedList <__ElementType>, typename __LinkedListImplementation <__ElementType>::__dll_ConstReverseIterator
    > {};

} // namespace __impl 
} // namespace __hidden 
} // namespace cds

#endif // __CDS_LINKED_LIST_CONSTRUCTS_HPP__
