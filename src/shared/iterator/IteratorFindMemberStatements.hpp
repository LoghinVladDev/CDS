//
// Created by loghin on 6/27/22.
//

#ifndef __CDS_SHARED_ITERATOR_FIND_MEMBER_STATEMENTS_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_ITERATOR_FIND_MEMBER_STATEMENTS_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#ifndef _MSC_VER
/// \brief Function used to find the elements that are validated by a given predicate and return the iterators of the elements in a given collection, until a given limit has been reached, at which point the iteration will stop. This is the predicate = member function variant
/// \tparam __Iterator is the type of the iterator elements that define the range of iteration
/// \tparam __Collection is the type of template iterable to store the iterators in
/// \tparam __Predicate is the type of the predicate given as a parameter, the type must be callable and compatible with the 'bool ( Decay < ElementType > )' function signature, or with the 'bool () const' member function signature.
/// \param [in] begin : __Iterator cref = Constant Reference to the begin iterator of the range
/// \param [in] end : __Iterator cref = Constant Reference to the end iterator of the range
/// \param [in] count : Size = Maximum number of elements to find
/// \param [out] storeIn : __Collection \< __Iterator \> cref = Constant Reference to the collection to store the iterators in
/// \param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter, if callable, or as an object caller, if member function
/// \exceptsafe if __Predicate callable / member function is exceptsafe
/// \return __Collection \< __Iterator \> ref = Reference to the updated object given in the 'storeIn' parameter
///
/// \test Suite: CTS-00001, Group: CTG-00650-FTMF, Test Cases: {
///      CTC-00651-FTMF-findThatStoreInMemberFunction,
///      CTC-00652-FTMF-findThatReturnedMemberFunction
/// }
///
/// \test Suite: MCTS-00001, Group: MCTG-00650-FTMF, Test Cases: {
///      MCTC-00651-FTMF-findThatStoreInMemberFunction,
///      MCTC-00652-FTMF-findThatReturnedMemberFunction
/// }
///
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <
    typename __Iterator,                        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    template <typename...> class __Collection,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Predicate,                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <
        cds::meta::IsMemberFunctionPointer <
            __Predicate,
            cds::meta::Decay <decltype (*cds::meta::valueOf <__Iterator>())>
        >::value
    > = 0
> __CDS_cpplang_ConstexprConditioned auto __findThat (      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __Iterator const&           begin,
    __Iterator const&           end,
    Size                        count,
    __Collection <__Iterator>&  storeIn,
    __Predicate const&          predicate
) noexcept (false) -> __Collection <__Iterator>&;

/// \brief Function used to find the first element validated by a given predicate and return the iterator of the element, if found. This is the predicate = member function variant
/// \tparam __Iterator is the type of the iterator elements that define the range of iteration
/// \tparam __Predicate is the type of the predicate given as a parameter, the type must be callable and compatible with the 'bool ( Decay < ElementType > )' function signature, or with the 'bool () const' member function signature.
/// \param [in] begin : __Iterator cref = Constant Reference to the begin iterator of the range
/// \param [in] end : __Iterator cref = Constant Reference to the end iterator of the range
/// \param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter, if callable, or as an object caller, if member function
/// \exceptsafe if __Predicate callable / member function is exceptsafe
/// \return __Iterator = The found iterator, if applicable. Returns 'end' otherwise
///
/// \test Suite: CTS-00001, Group: CTG-00650-FTMF, Test Cases: {
///      CTC-00653-FTMF-findFirstThatMemberFunction
/// }
///
/// \test Suite: MCTS-00001, Group: MCTG-00650-FTMF, Test Cases: {
///      MCTC-00653-FTMF-findFirstThatMemberFunction
/// }
///
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <
    typename __Iterator,                                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Predicate,                                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <
        cds::meta::IsMemberFunctionPointer <
            __Predicate,
            cds::meta::Decay <decltype (*cds::meta::valueOf <__Iterator>())>
        >::value
    > = 0
> __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __findFirstThat ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __Iterator const&   begin,
    __Iterator const&   end,
    __Predicate const&  predicate
) noexcept (false) -> __Iterator;

/// \brief Function used to find the last element validated by a given predicate and return the iterator of the element, if found. This is the predicate = member function variant
/// \tparam __Iterator is the type of the iterator elements that define the range of iteration
/// \tparam __Predicate is the type of the predicate given as a parameter, the type must be callable and compatible with the 'bool ( Decay < ElementType > )' function signature, or with the 'bool () const' member function signature.
/// \param [in] begin : __Iterator cref = Constant Reference to the begin iterator of the range
/// \param [in] end : __Iterator cref = Constant Reference to the end iterator of the range
/// \param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter, if callable, or as an object caller, if member function
/// \exceptsafe if __Predicate callable / member function is exceptsafe
/// \return __Iterator = The found iterator, if applicable. Returns 'end' otherwise
///
/// \test Suite: CTS-00001, Group: CTG-00650-FTMF, Test Cases: {
///      CTC-00654-FTMF-findLastThatMemberFunction
/// }
///
/// \test Suite: MCTS-00001, Group: MCTG-00650-FTMF, Test Cases: {
///      MCTC-00654-FTMF-findLastThatMemberFunction
/// }
///
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <
    typename __Iterator,                                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Predicate,                                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <
        cds::meta::IsMemberFunctionPointer <
            __Predicate,
            cds::meta::Decay <decltype (*cds::meta::valueOf <__Iterator>())>
        >::value
    > = 0
> __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __findLastThat (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __Iterator const&   begin,
    __Iterator const&   end,
    __Predicate const&  predicate
) noexcept (false) -> __Iterator;

/// \brief Function used to find all the elements that are validated by a given predicate and return the iterators of the elements in a given collection. This is the predicate = member function variant
/// \tparam __Iterator is the type of the iterator elements that define the range of iteration
/// \tparam __Collection is the type of template iterable to store the iterators in
/// \tparam __Predicate is the type of the predicate given as a parameter, the type must be callable and compatible with the 'bool ( Decay < ElementType > )' function signature, or with the 'bool () const' member function signature.
/// \param [in] begin : __Iterator cref = Constant Reference to the begin iterator of the range
/// \param [in] end : __Iterator cref = Constant Reference to the end iterator of the range
/// \param [out] storeIn : __Collection \< __Iterator \> cref = Constant Reference to the collection to store the iterators in
/// \param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter, if callable, or as an object caller, if member function
/// \exceptsafe if __Predicate callable / member function is exceptsafe
/// \return __Collection \< __Iterator \> ref = Reference to the updated object given in the 'storeIn' parameter
///
/// \test Suite: CTS-00001, Group: CTG-00650-FTMF, Test Cases: {
///      CTC-00655-FTMF-findAllThatStoreInMemberFunction,
///      CTC-00656-FTMF-findAllThatReturnedMemberFunction
/// }
///
/// \test Suite: MCTS-00001, Group: MCTG-00650-FTMF, Test Cases: {
///      MCTC-00655-FTMF-findAllThatStoreInMemberFunction,
///      MCTC-00656-FTMF-findAllThatReturnedMemberFunction
/// }
///
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <
    typename __Iterator,                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    template <typename...> class __Collection,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Predicate,                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <
        cds::meta::IsMemberFunctionPointer <
            __Predicate,
            cds::meta::Decay <decltype (*cds::meta::valueOf <__Iterator>())>
        >::value
    > = 0
> __CDS_cpplang_ConstexprConditioned auto __findAllThat (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __Iterator const&           begin,
    __Iterator const&           end,
    __Collection <__Iterator>&  storeIn,
    __Predicate const&          predicate
) noexcept (false) -> __Collection <__Iterator> &;

#else

/// \brief Function used to find the elements that are validated by a given predicate and return the iterators of the elements in a given collection, until a given limit has been reached, at which point the iteration will stop. This is the predicate = member function variant
/// \tparam __Iterator is the type of the iterator elements that define the range of iteration
/// \tparam __Collection is the type of template iterable to store the iterators in
/// \tparam __Predicate is the type of the predicate given as a parameter, the type must be callable and compatible with the 'bool ( Decay < ElementType > )' function signature, or with the 'bool () const' member function signature.
/// \param [in] begin : __Iterator cref = Constant Reference to the begin iterator of the range
/// \param [in] end : __Iterator cref = Constant Reference to the end iterator of the range
/// \param [in] count : Size = Maximum number of elements to find
/// \param [out] storeIn : __Collection \< __Iterator \> cref = Constant Reference to the collection to store the iterators in
/// \param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter, if callable, or as an object caller, if member function
/// \exceptsafe if __Predicate callable / member function is exceptsafe
/// \return __Collection \< __Iterator \> ref = Reference to the updated object given in the 'storeIn' parameter
///
/// \test Suite: CTS-00001, Group: CTG-00650-FTMF, Test Cases: {
///      CTC-00651-FTMF-findThatStoreInMemberFunction,
///      CTC-00652-FTMF-findThatReturnedMemberFunction
/// }
///
/// \test Suite: MCTS-00001, Group: MCTG-00650-FTMF, Test Cases: {
///      MCTC-00651-FTMF-findThatStoreInMemberFunction,
///      MCTC-00652-FTMF-findThatReturnedMemberFunction
/// }
///
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <
        typename __Iterator,                        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
        template <typename...> class __Collection,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
        typename __Predicate                        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __findThatMember (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
        __Iterator const&           begin,
        __Iterator const&           end,
        Size                        count,
        __Collection <__Iterator>&  storeIn,
        __Predicate const&          predicate
) noexcept (false) -> __Collection <__Iterator>&;

/// \brief Function used to find the first element validated by a given predicate and return the iterator of the element, if found. This is the predicate = member function variant
/// \tparam __Iterator is the type of the iterator elements that define the range of iteration
/// \tparam __Predicate is the type of the predicate given as a parameter, the type must be callable and compatible with the 'bool ( Decay < ElementType > )' function signature, or with the 'bool () const' member function signature.
/// \param [in] begin : __Iterator cref = Constant Reference to the begin iterator of the range
/// \param [in] end : __Iterator cref = Constant Reference to the end iterator of the range
/// \param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter, if callable, or as an object caller, if member function
/// \exceptsafe if __Predicate callable / member function is exceptsafe
/// \return __Iterator = The found iterator, if applicable. Returns 'end' otherwise
///
/// \test Suite: CTS-00001, Group: CTG-00650-FTMF, Test Cases: {
///      CTC-00653-FTMF-findFirstThatMemberFunction
/// }
///
/// \test Suite: MCTS-00001, Group: MCTG-00650-FTMF, Test Cases: {
///      MCTC-00653-FTMF-findFirstThatMemberFunction
/// }
///
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <
        typename __Iterator,                                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
        typename __Predicate                                                        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __findFirstThatMember (   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
        __Iterator const&   begin,
        __Iterator const&   end,
        __Predicate const&  predicate
) noexcept (false) -> __Iterator;

/// \brief Function used to find the last element validated by a given predicate and return the iterator of the element, if found. This is the predicate = member function variant
/// \tparam __Iterator is the type of the iterator elements that define the range of iteration
/// \tparam __Predicate is the type of the predicate given as a parameter, the type must be callable and compatible with the 'bool ( Decay < ElementType > )' function signature, or with the 'bool () const' member function signature.
/// \param [in] begin : __Iterator cref = Constant Reference to the begin iterator of the range
/// \param [in] end : __Iterator cref = Constant Reference to the end iterator of the range
/// \param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter, if callable, or as an object caller, if member function
/// \exceptsafe if __Predicate callable / member function is exceptsafe
/// \return __Iterator = The found iterator, if applicable. Returns 'end' otherwise
///
/// \test Suite: CTS-00001, Group: CTG-00650-FTMF, Test Cases: {
///      CTC-00654-FTMF-findLastThatMemberFunction
/// }
///
/// \test Suite: MCTS-00001, Group: MCTG-00650-FTMF, Test Cases: {
///      MCTC-00654-FTMF-findLastThatMemberFunction
/// }
///
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <
        typename __Iterator,                                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
        typename __Predicate                                                        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __findLastThatMember (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
        __Iterator const&   begin,
        __Iterator const&   end,
        __Predicate const&  predicate
) noexcept (false) -> __Iterator;

/// \brief Function used to find all the elements that are validated by a given predicate and return the iterators of the elements in a given collection. This is the predicate = member function variant
/// \tparam __Iterator is the type of the iterator elements that define the range of iteration
/// \tparam __Collection is the type of template iterable to store the iterators in
/// \tparam __Predicate is the type of the predicate given as a parameter, the type must be callable and compatible with the 'bool ( Decay < ElementType > )' function signature, or with the 'bool () const' member function signature.
/// \param [in] begin : __Iterator cref = Constant Reference to the begin iterator of the range
/// \param [in] end : __Iterator cref = Constant Reference to the end iterator of the range
/// \param [out] storeIn : __Collection \< __Iterator \> cref = Constant Reference to the collection to store the iterators in
/// \param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter, if callable, or as an object caller, if member function
/// \exceptsafe if __Predicate callable / member function is exceptsafe
/// \return __Collection \< __Iterator \> ref = Reference to the updated object given in the 'storeIn' parameter
///
/// \test Suite: CTS-00001, Group: CTG-00650-FTMF, Test Cases: {
///      CTC-00655-FTMF-findAllThatStoreInMemberFunction,
///      CTC-00656-FTMF-findAllThatReturnedMemberFunction
/// }
///
/// \test Suite: MCTS-00001, Group: MCTG-00650-FTMF, Test Cases: {
///      MCTC-00655-FTMF-findAllThatStoreInMemberFunction,
///      MCTC-00656-FTMF-findAllThatReturnedMemberFunction
/// }
///
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <
        typename __Iterator,                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
        template <typename...> class __Collection,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
        typename __Predicate                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __findAllThatMember ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
        __Iterator const&           begin,
        __Iterator const&           end,
        __Collection <__Iterator>&  storeIn,
        __Predicate const&          predicate
) noexcept (false) -> __Collection <__Iterator>&;
#endif
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_ITERATOR_FIND_MEMBER_STATEMENTS_HPP__
