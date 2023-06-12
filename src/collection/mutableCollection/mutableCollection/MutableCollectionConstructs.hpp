// NOLINT(llvm-header-guard)
// Created by loghin on 08/07/22.
//

#ifndef __CDS_MUTABLE_COLLECTION_CONSTRUCTS_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_MUTABLE_COLLECTION_CONSTRUCTS_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
/// \brief Pre-declaration of the MutableCollection class
/// \namespace cds
template <typename> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class MutableCollection;

namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
/// \class Alias used by MutableCollection to implement the Delegate Forward Iterable Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __MutableCollectionDelegateForwardIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __DelegateForwardIterablePrimitiveClient <
        cds::MutableCollection <__ElementType>, __ElementType, false
    > {};


/// \class Alias used by MutableCollection to implement the Iterator Remove Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __MutableCollectionIteratorRemoveClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __AbstractIteratorRemovePrimitiveClient <cds::MutableCollection <__ElementType>, __ElementType> {};


/// \class Alias used by MutableCollection to implement the Random Insertion Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __MutableCollectionRandomInsertionClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __RandomInsertionPrimitiveClient <cds::MutableCollection <__ElementType>, __ElementType, __ElementType> {};


/// \class Alias used by MutableCollection to implement the Find Of Mutable Collection Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __MutableCollectionFindOfIterableClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __FindOfMutableCompositeClient <
        cds::MutableCollection <__ElementType>, __ElementType,
        typename __MutableCollectionDelegateForwardIterableClient <__ElementType>::Iterator,
        cds::Iterable <__ElementType>,
        &__iterableContains <__ElementType>, &__iterableNotContains <__ElementType>
    > {};


/// \class Alias used by MutableCollection to implement the Find Of Immutable Initializer List Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __MutableCollectionFindOfInitializerListClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __FindOfMutableCompositeClient <
        cds::MutableCollection <__ElementType>, __ElementType,
        typename __MutableCollectionDelegateForwardIterableClient <__ElementType>::Iterator,
        std::initializer_list <__ElementType>,
        &__initializerListContains <__ElementType, &cds::meta::equals <__ElementType>>,
        &__initializerListNotContains <__ElementType, &cds::meta::equals <__ElementType>>
    > {};


/// \class Alias used by MutableCollection to implement the Find by Immutable Predicate Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __MutableCollectionFindByClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __FindByMutableCompositeClient <
        cds::MutableCollection <__ElementType>, __ElementType,
        typename __MutableCollectionDelegateForwardIterableClient <__ElementType>::Iterator
    > {};


/// \class Alias used by MutableCollection to implement the Generic Mutable Statements Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __MutableCollectionGenericStatementsClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __GenericMutableStatementsCompositeClient <cds::MutableCollection <__ElementType>, __ElementType> {};
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_MUTABLE_COLLECTION_CONSTRUCTS_HPP__
