//
// Created by loghin on 16/02/23.
//

#ifndef __CDS_STATIC_ARRAY_CONSTRUCTS_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_STATIC_ARRAY_CONSTRUCTS_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {             // NOLINT(modernize-concat-nested-namespaces)
template <typename __Element, Size __size> class StaticArray; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __Element, Size __size>
using __StaticArrayImplementation =
    __StaticArrayBase <
        __Element, __size, &cds::meta::equals <__Element>,
        __StaticArrayMemoryContainer <__Element, __size>
    >;


template <typename __Element, Size __size>
using __StaticArrayDispatcher =
    typename __StaticArrayImplementation <__Element, __size>::template __Dispatcher <StaticArray <__Element, __size>>;


template <typename __Element, Size __size>
using __StaticArrayServer =
    __IterableServer <StaticArray <__Element, __size>, __Element>;


template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __StaticArrayFindOfIterableClient =           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __LocalFindOfMutableCompositeClient <
        cds::StaticArray <__Element, __size>, __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables)
        AddressIterator <__Element>, cds::Iterable <__Element>,
        &__iterableContains <__Element>, &__iterableNotContains <__Element>
    >;


template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __StaticArrayFindOfInitializerListClient =    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __LocalFindOfMutableCompositeClient <
        cds::StaticArray <__Element, __size>, __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables)
        AddressIterator <__Element>, std::initializer_list <__Element>,
        &__initializerListContains <__Element, &cds::meta::equals <__Element>>,
        &__initializerListNotContains <__Element, &cds::meta::equals <__Element>>
    >;


template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __StaticArrayConstFindOfIterableClient =      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __LocalFindOfImmutableCompositeClient <
        cds::StaticArray <__Element, __size>, __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables)
        AddressIterator <__Element const>, cds::Iterable <__Element>,
        &__iterableContains <__Element>, &__iterableNotContains <__Element>
    >;


template <typename __Element, Size __size>        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __StaticArrayConstFindOfInitializerListClient =   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __LocalFindOfImmutableCompositeClient <
        cds::StaticArray <__Element, __size>, __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables)
        AddressIterator <__Element const>, std::initializer_list <__Element>,
        &__initializerListContains <__Element, &cds::meta::equals <__Element>>,
        &__initializerListNotContains <__Element, &cds::meta::equals <__Element>>
    >;


template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __StaticArrayFindByClient =                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __LocalFindByMutableCompositeClient <
        cds::StaticArray <__Element, __size>, __Element,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables)
        AddressIterator <__Element>
    >;


template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __StaticArrayConstFindByClient =              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __LocalFindByImmutableCompositeClient <
        cds::StaticArray <__Element, __size>, __Element,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables)
        AddressIterator <__Element const>
    >;


template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __StaticArrayGenericStatementsClient =        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __LocalGenericMutableStatementsCompositeClient <
        cds::StaticArray <__Element, __size>, __Element
    >;


template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __StaticArrayGenericConstStatementsClient =   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __LocalGenericImmutableStatementsCompositeClient <
        cds::StaticArray <__Element, __size>, __Element
    >;


template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __StaticArrayReplaceClient =                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __LocalReplaceCompositeClient <
        cds::StaticArray <__Element, __size>, __Element
    >;


template <typename __Element, Size __size>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __StaticArrayReplaceOfIterableClient =  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __LocalReplaceOfCompositeClient <
        cds::StaticArray <__Element, __size>, __Element,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables)
        cds::Iterable <__Element>, &__iterableContains <__Element>
    >;


template <typename __Element, Size __size>             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __StaticArrayReplaceOfInitializerListClient =   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __LocalReplaceOfCompositeClient <
        cds::StaticArray <__Element, __size>, __Element, std::initializer_list <__Element>, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables)
        &__initializerListContains <__Element, &cds::meta::equals <__Element>>
    >;


template <typename __Element, Size __size> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __StaticArrayReplaceByClient =      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __LocalReplaceByCompositeClient <cds::StaticArray <__Element, __size>, __Element>;


template <typename __Element, Size __size>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __StaticArrayIndexedOperationsClient =  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __LocalIndexedOperationsPrimitiveClient <cds::StaticArray <__Element, __size>, __Element>;


template <typename __Element, Size __size> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __StaticArrayIndicesClient =        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __LocalIndicesCompositeClient <cds::StaticArray <__Element, __size>, __Element>;


template <typename __Element, Size __size>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __StaticArrayIndicesOfIterableClient =  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __LocalIndicesOfCompositeClient <
        cds::StaticArray <__Element, __size>, __Element,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables)
        cds::Iterable <__Element>, &__iterableContains <__Element>
    >;


template <typename __Element, Size __size>             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __StaticArrayIndicesOfInitializerListClient =   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __LocalIndicesOfCompositeClient <
        cds::StaticArray <__Element, __size>, __Element,                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables)
        std::initializer_list <__Element>,
        &__initializerListContains <__Element, &cds::meta::equals <__Element>>
    >;


template <typename __Element, Size __size> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __StaticArrayIndicesByClient =      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __LocalIndicesByCompositeClient <cds::StaticArray <__Element, __size>, __Element>;


template <typename __Element, Size __size>     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __StaticArrayContainsOfIterableClient = // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __LocalContainsOfCompositeClient <
        cds::StaticArray <__Element, __size>, __Element,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables)
        cds::Iterable <__Element>, &__iterableContains <__Element>
    >;


template <typename __Element, Size __size>             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __StaticArrayContainsOfInitializerListClient =  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __LocalContainsOfCompositeClient <
        cds::StaticArray <__Element, __size>, __Element, std::initializer_list <__Element>, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-non-const-global-variables)
        &__initializerListContains <__Element, &cds::meta::equals <__Element>>
    >;


template <typename __Element, Size __size>             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __StaticArrayDelegateForwardIterableClient =    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __LocalDelegateForwardIterablePrimitiveClient <
        cds::StaticArray <__Element, __size>,
        typename __StaticArrayImplementation <__Element, __size>::__sab_Iterator
    >;


template <typename __Element, Size __size>                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __StaticArrayDelegateForwardConstIterableClient =   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __LocalDelegateForwardConstIterablePrimitiveClient <
        cds::StaticArray <__Element, __size>,
        typename __StaticArrayImplementation <__Element, __size>::__sab_ConstIterator
    >;


template <typename __Element, Size __size>             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __StaticArrayDelegateBackwardIterableClient =   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __LocalDelegateBackwardIterablePrimitiveClient <
        cds::StaticArray <__Element, __size>,
        typename __StaticArrayImplementation <__Element, __size>::__sab_ReverseIterator
    >;


template <typename __Element, Size __size>                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using __StaticArrayDelegateBackwardConstIterableClient =  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __LocalDelegateBackwardConstIterablePrimitiveClient <
        cds::StaticArray <__Element, __size>,
        typename __StaticArrayImplementation <__Element, __size>::__sab_ConstReverseIterator
    >;
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_STATIC_ARRAY_CONSTRUCTS_HPP__
