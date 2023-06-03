// NOLINT(llvm-header-guard)
// Created by loghin on 08/07/22.
//

#ifndef __CDS_LIST_CONSTRUCTS_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_LIST_CONSTRUCTS_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

/// \brief Pre-declaration of the List class
/// \namespace cds
template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class List;

namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
/// \class Alias used by List to implement the Delegate Forward Iterable Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ListDelegateForwardIterableClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __DelegateForwardIterablePrimitiveClient <cds::List <__ElementType>, __ElementType, true> {};


/// \class Alias used by List to implement the Delegate Backward Iterable Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ListDelegateBackwardIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __DelegateBackwardIterablePrimitiveClient <cds::List <__ElementType>, __ElementType, true> {};


/// \class Alias used by List to implement the Delegate Forward Const Iterable Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ListDelegateForwardConstIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __DelegateForwardConstIterablePrimitiveClient <cds::List <__ElementType>, __ElementType, true> {};


/// \class Alias used by List to implement the Delegate Backward Const Iterable Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ListDelegateBackwardConstIterableClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __DelegateBackwardConstIterablePrimitiveClient <cds::List <__ElementType>, __ElementType, true> {};


/// \class Alias used by List to implement the Boundary Insertion Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ListBoundaryInsertionClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __BoundaryInsertionPrimitiveClient <cds::List <__ElementType>, __ElementType, __ElementType> {};


/// \class Alias used by List to implement the Iterator-Relative Insertion Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ListIteratorRelativeInsertionClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __AbstractIteratorRelativeInsertionPrimitiveClient <cds::List <__ElementType>, __ElementType> {};


/// \class Alias used by List to implement the Const-Iterator-Relative Insertion Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ListConstIteratorRelativeInsertionClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __AbstractConstIteratorRelativeInsertionPrimitiveClient <cds::List <__ElementType>, __ElementType> {};


/// \class Alias used by List to implement the Indexed Operations Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ListIndexedOperationsClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __IndexedOperationsPrimitiveClient <cds::List <__ElementType>, __ElementType> {};


/// \class Alias used by List to implement the Replace Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ListReplaceClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __ReplaceCompositeClient <cds::List <__ElementType>, __ElementType> {};


/// \class Alias used by List to implement the Replace of Iterable Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ListReplaceOfIterableClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __ReplaceOfCompositeClient <
        cds::List <__ElementType>, __ElementType,
        cds::Iterable <__ElementType>, &__iterableContains <__ElementType>
    > {};


/// \class Alias used by List to implement the Replace of Initializer List Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ListReplaceOfInitializerListClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __ReplaceOfCompositeClient <
        cds::List <__ElementType>, __ElementType,
        std::initializer_list <__ElementType>,
        &__initializerListContains <__ElementType, &cds::meta::equals <__ElementType>>
    > {};


/// \class Alias used by List to implement the Replace by Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ListReplaceByClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __ReplaceByCompositeClient <cds::List <__ElementType>, __ElementType> {};


/// \class Alias used by List to implement the Indices Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ListIndicesClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __IndicesCompositeClient <cds::List <__ElementType>, __ElementType> {};


/// \class Alias used by List to implement the Indices of Iterable Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ListIndicesOfIterableClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __IndicesOfCompositeClient <
        cds::List <__ElementType>, __ElementType,
        cds::Iterable <__ElementType>, &__iterableContains <__ElementType>
    > {};


/// \class Alias used by List to implement the Indices of Initializer List Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ListIndicesOfInitializerListClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __IndicesOfCompositeClient <
        cds::List <__ElementType>,
        __ElementType,
        std::initializer_list <__ElementType>,
        &__initializerListContains <__ElementType, &cds::meta::equals <__ElementType>>
    > {};


/// \class Alias used by List to implement the Indices by Client
/// \tparam __ElementType the type of the elements enclosed in the extending Collection
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __ElementType>                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __ListIndicesByClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __IndicesByCompositeClient <cds::List <__ElementType>, __ElementType> {};
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_LIST_CONSTRUCTS_HPP__
