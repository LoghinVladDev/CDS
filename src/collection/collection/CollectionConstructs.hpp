// NOLINT(llvm-header-guard)
// Created by loghin on 6/26/22.
//

#ifndef __CDS_COLLECTION_CONSTRUCTS_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_COLLECTION_CONSTRUCTS_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)

/// \brief Pre-declaration of the Collection class
/// \namespace cds
template <typename> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class Collection;

namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
/// \class Alias used by Collection to implement the Const Iterator Remove Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __CollectionConstIteratorRemoveClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __AbstractConstIteratorRemovePrimitiveClient <cds::Collection <__ElementType>, __ElementType> {};


/// \class Alias used by Collection to implement the Random Insertion Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __CollectionRandomInsertionClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __RandomInsertionPrimitiveClient <
        cds::Collection <__ElementType>, __ElementType, __ElementType const
    > {};


/// \class Alias used by Collection to implement the Remove of Iterable Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __CollectionRemoveOfCollectionClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __RemoveOfCompositeClient <
        cds::Collection <__ElementType>, __ElementType,
        cds::Iterable <__ElementType>, &__iterableContains <__ElementType>
    > {};


/// \class Alias used by Collection to implement the Remove of Initializer List Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __CollectionRemoveOfInitializerListClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __RemoveOfCompositeClient <
        cds::Collection <__ElementType>, __ElementType,
        std::initializer_list <__ElementType>,
        &__initializerListContains <__ElementType, &cds::meta::equals <__ElementType>>
    > {};


/// \class Alias used by Collection to implement the Remove by Predicate Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __CollectionRemoveByClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __RemoveByCompositeClient <cds::Collection <__ElementType>, __ElementType> {};
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_COLLECTION_CONSTRUCTS_HPP__
