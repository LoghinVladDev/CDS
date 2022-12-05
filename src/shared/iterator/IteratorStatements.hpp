/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_ITERATOR_STATEMENTS_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_ITERATOR_STATEMENTS_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Function used to apply an action over each element of an iterable range. This is the action = callable object variant
             * @tparam __IteratorType is the type of the iterator elements that define the range of iteration
             * @tparam __Consumer is the type of the consumer given as a parameter, the type must be callable and compatible with the 'Any ( Decay < ElementType > )' function signature, where Any is any type or a member function compatible with the signature 'Any () const'
             * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
             * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
             * @param [in] consumer : __Consumer cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter, if callable, or as an object caller, if member function
             * @exceptsafe if __Consumer callable / member function is exceptsafe
             *
             * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00139-FS-forEachCount }
             * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00201-FSMF-forEach }
             *
             * @test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00139-FS-forEachCount, MCTC-00140-FS-forEachMutability, MCTC-00141-FS-forEachMemberFnMutability }
             * @test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00201-FSMF-forEach }
             *
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __IteratorType,                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Consumer,                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            ! cds :: meta :: isMemberFunctionPointer <
                                    __Consumer,
                                    cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                            > ()
                    > = 0
            > __CDS_cpplang_ConstexprConditioned auto __forEach (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    __Consumer     const & consumer
            ) noexcept ( noexcept ( consumer ( * begin ) ) ) -> void;

            /**
             * @brief Function used to check if the iterable range contains exactly 'count' elements that are validated by a given predicate. This is the predicate = callable object variant
             * @tparam __IteratorType is the type of the iterator elements that define the range of iteration
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be a callable compatible with the 'bool ( Decay < ElementType > )' function signature or a member function compatible with the signature 'bool () const'
             * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
             * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
             * @param [in] count : Size = number of elements required to match
             * @param [in] predicate : __Predicate cref = Constant Reference to callable / member function object, to be called with each element of the range as a parameter. If no predicate is given, it will default to a predicate that will validate every value.
             * @exceptsafe if Predicate is exceptsafe
             * @return bool = true if number of elements validated == count, false otherwise
             *
             * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00136-FS-someExact, CTC-00137-FS-someLessFalse, CTC-00138-someMoreFalse }
             * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00202-FSMF-someEqual, CTC-00203-FSMF-someLess, CTC-00204-someMore }
             *
             * @test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00136-FS-someExact, MCTC-00137-FS-someLessFalse, MCTC-00138-someMoreFalse }
             * @test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00202-FSMF-someEqual, MCTC-00203-FSMF-someLess, MCTC-00204-someMore }
             *
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __IteratorType,                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate,                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            ! cds :: meta :: isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                            > ()
                    > = 0
            > __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __some (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    Size                   count,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool;

            /**
             * @brief Function used to check if the iterable range contains at least 'count' elements that are validated by a given predicate. This is the predicate = callable object variant
             * @tparam __IteratorType is the type of the iterator elements that define the range of iteration
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable compatible with the signature 'bool ( Decay < ElementType > )' or a member function compatible with the signature 'bool () const'
             * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
             * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
             * @param [in] count : Size = minimum number of elements required to match
             * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter. If no predicate is given, it will default to a predicate that will validate every value
             * @exceptsafe if Predicate is exceptsafe
             * @return bool = true if number of elements validated >= count, false otherwise
             *
             * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00132-FS-atLeastTrue, CTC-00133-FS-atLeastCloseTrue, CTC-00134-atLeastCloseFalse, CTC-00135-atLeastFalse }
             * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00205-FSMF-atLeast, CTC-00206-FSMF-atLeastLess, CTC-00207-atLeastMore }
             *
             * @test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00132-FS-atLeastTrue, MCTC-00133-FS-atLeastCloseTrue, MCTC-00134-atLeastCloseFalse, MCTC-00135-atLeastFalse }
             * @test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00205-FSMF-atLeast, MCTC-00206-FSMF-atLeastLess, MCTC-00207-atLeastMore }
             *
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __IteratorType,                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate,                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            ! cds :: meta :: isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                            > ()
                    > = 0
            > __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __atLeast (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    Size                   count,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool;

            /**
             * @brief Function used to check if the iterable range contains at most 'count' elements that are validated by a given predicate. This is the predicate = callable object variant
             * @tparam __IteratorType is the type of the iterator elements that define the range of iteration
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable compatible with the signature 'bool ( Decay < ElementType > )' or a member function compatible with the signature 'bool () const'
             * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
             * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
             * @param [in] count : Size = maximum number of elements required to match
             * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter. If no predicate is given, it will default to a predicate that will validate every value
             * @exceptsafe if Predicate is exceptsafe
             * @return bool = true if number of elements validated <= count, false otherwise
             *
             * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00128-FS-atMostTrue, CTC-00129-FS-atMostCloseTrue, CTC-00130-atMostCloseFalse, CTC-00131-atMostFalse }
             * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00208-FSMF-atMost, CTC-00209-FSMF-atMostLess, CTC-00210-atMostMore }
             *
             * @test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00128-FS-atMostTrue, MCTC-00129-FS-atMostCloseTrue, MCTC-00130-atMostCloseFalse, MCTC-00131-atMostFalse }
             * @test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00208-FSMF-atMost, MCTC-00209-FSMF-atMostLess, MCTC-00210-atMostMore }
             *
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __IteratorType,                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate,                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            ! cds :: meta :: isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                            > ()
                    > = 0
            > __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __atMost (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    Size                   count,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool;

            /**
             * @brief Function used to check if the iterable range contains more than 'count' elements that are validated by a given predicate. This is the predicate = callable object variant
             * @tparam __IteratorType is the type of the iterator elements that define the range of iteration
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable compatible with the signature 'bool ( Decay < ElementType > )' or a member function compatible with the signature 'bool () const'
             * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
             * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
             * @param [in] count : Size = minimum number of elements required to match
             * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter. If no predicate is given, it will default to a predicate that will validate every value
             * @exceptsafe if Predicate is exceptsafe
             * @return bool = true if number of elements validated > count, false otherwise
             *
             * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00123-FS-moreThanTrue, CTC-00124-FS-moreThanCloseTrue, CTC-00125-moreThanCloseFalse, CTC-00126-moreThanFalse, CTC-00127-moreThanCompletelyFalse }
             * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00211-FSMF-moreThan, CTC-00212-FSMF-moreThanLess, CTC-00213-moreThanMore }
             *
             * @test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00123-FS-moreThanTrue, MCTC-00124-FS-moreThanCloseTrue, MCTC-00125-moreThanCloseFalse, MCTC-00126-moreThanFalse, MCTC-00127-moreThanCompletelyFalse }
             * @test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00211-FSMF-moreThan, MCTC-00212-FSMF-moreThanLess, MCTC-00213-moreThanMore }
             *
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __IteratorType,                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate,                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            ! cds :: meta :: isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                            > ()
                    > = 0
            > __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __moreThan (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    Size                   count,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool;

            /**
             * @brief Function used to check if the iterable range contains less than 'count' elements that are validated by a given predicate. This is the predicate = callable object variant
             * @tparam __IteratorType is the type of the iterator elements that define the range of iteration
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable compatible with the signature 'bool ( Decay < ElementType > )' or a member function compatible with the signature 'bool () const'
             * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
             * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
             * @param [in] count : Size = maximum number of elements required to match
             * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter. If no predicate is given, it will default to a predicate that will validate every value
             * @exceptsafe if Predicate is exceptsafe
             * @return bool = true if number of elements validated < count, false otherwise
             *
             * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00118-FS-fewerThanTrue, CTC-00119-FS-fewerThanCloseTrue, CTC-00120-fewerThanCloseFalse, CTC-00121-fewerThanFalse, CTC-00122-fewerThanCompletelyFalse }
             * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00214-FSMF-fewerThan, CTC-00215-FSMF-fewerThanLess, CTC-00216-fewerThanMore }
             *
             * @test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00118-FS-fewerThanTrue, MCTC-00119-FS-fewerThanCloseTrue, MCTC-00120-fewerThanCloseFalse, MCTC-00121-fewerThanFalse, MCTC-00122-fewerThanCompletelyFalse }
             * @test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00214-FSMF-fewerThan, MCTC-00215-FSMF-fewerThanLess, MCTC-00216-fewerThanMore }
             *
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __IteratorType,                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate,                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            ! cds :: meta :: isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                            > ()
                    > = 0
            > __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __fewerThan ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    Size                   count,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool;

            /**
             * @brief Function used to acquire the number of elements that are validated by a given predicate in a given iterable range. This is the predicate = callable object variant
             * @tparam __IteratorType is the type of the iterator elements that define the range of iteration
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable compatible with the signature 'bool ( Decay < ElementType > )' or a member function compatible with the signature 'bool () const'
             * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
             * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
             * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter. If no predicate is given, it will default to a predicate that will validate every value
             * @exceptsafe if Predicate is exceptsafe
             * @return Size = number of elements that are validated by the given predicate
             *
             * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00113-FS-countProp1, CTC-00114-FS-countProp2, CTC-00115-countProp3, CTC-00116-countProp4, CTC-00117-countPropLbd }
             * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00217-FSMF-countExact }
             *
             * @test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00113-FS-countProp1, MCTC-00114-FS-countProp2, MCTC-00115-countProp3, MCTC-00116-countProp4, MCTC-00117-countPropLbd }
             * @test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00217-FSMF-countExact }
             *
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __IteratorType,                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate,                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            ! cds :: meta :: isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                            > ()
                    > = 0
            > __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __count ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> Size;

            /**
             * @brief Function used to check if any of the iterable range's elements are validated by a given predicate. This is the predicate = callable object variant
             * @tparam __IteratorType is the type of the iterator elements that define the range of iteration
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable compatible with the signature 'bool ( Decay < ElementType > )' or a member function compatible with the signature 'bool () const'
             * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
             * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
             * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter. If no predicate is given, it will default to a predicate that will validate every value
             * @exceptsafe if Predicate is exceptsafe
             * @return bool = true if at least one element is validated by the given predicate, false otherwise
             *
             * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00101-FS-anyNone, CTC-00102-FS-anyOne, CTC-00103-anyMore, CTC-00104-anyAll }
             * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00218-FSMF-anyNone, CTC-00219-FSMF-anyOne, CTC-00220-anyMore, CTC-00221-anyAll }
             *
             * @test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00101-FS-anyNone, MCTC-00102-FS-anyOne, MCTC-00103-anyMore, MCTC-00104-anyAll }
             * @test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00218-FSMF-anyNone, MCTC-00219-FSMF-anyOne, MCTC-00220-anyMore, MCTC-00221-anyAll }
             *
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __IteratorType,                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate,                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            ! cds :: meta :: isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                            > ()
                    > = 0
            > __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __any (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool;

            /**
             * @brief Function used to check if all of the iterable range's elements are validated by a given predicate. This is the predicate = callable object variant
             * @tparam __IteratorType is the type of the iterator elements that define the range of iteration
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable compatible with the signature 'bool ( Decay < ElementType > )' or a member function compatible with the signature 'bool () const'
             * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
             * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
             * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter. If no predicate is given, it will default to a predicate that will validate every value
             * @exceptsafe if Predicate is exceptsafe
             * @return bool = true if all of the iterable's elements are validated by the given predicate, false otherwise
             *
             * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00105-FS-allNone, CTC-00106-FS-allOne, CTC-00107-allMore, CTC-00108-allAll }
             * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00222-FSMF-allNone, CTC-00223-FSMF-allOne, CTC-00224-allMore, CTC-00225-allAll }
             *
             * @test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00105-FS-allNone, MCTC-00106-FS-allOne, MCTC-00107-allMore, MCTC-00108-allAll }
             * @test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00222-FSMF-allNone, MCTC-00223-FSMF-allOne, MCTC-00224-allMore, MCTC-00225-allAll }
             *
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __IteratorType,                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate,                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            ! cds :: meta :: isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                            > ()
                    > = 0
            > __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __all (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool;

            /**
             * @brief Function used to check if none of the iterable range's elements are validated by a given predicate. This is the predicate = callable object variant
             * @tparam __IteratorType is the type of the iterator elements that define the range of iteration
             * @tparam __Predicate the type of the predicate given as a parameter, the type must be callable compatible with the signature 'bool ( Decay < ElementType > )' or a member function compatible with the signature 'bool () const'
             * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
             * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
             * @param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter. If no predicate is given, it will default to a predicate that will validate every value
             * @exceptsafe if Predicate is exceptsafe
             * @return bool = true if none of the iterable's elements are validated by the given predicate, false otherwise
             *
             * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00109-FS-noneNone, CTC-00110-FS-noneOne, CTC-00111-noneMore, CTC-00112-noneAll }
             * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00226-FSMF-noneNone, CTC-00227-FSMF-noneOne, CTC-00228-noneMore, CTC-00229-noneAll }
             *
             * @test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00109-FS-noneNone, MCTC-00110-FS-noneOne, MCTC-00111-noneMore, MCTC-00112-noneAll }
             * @test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00226-FSMF-noneNone, MCTC-00227-FSMF-noneOne, MCTC-00228-noneMore, MCTC-00229-noneAll }
             *
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __IteratorType,                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __Predicate,                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    cds :: meta :: EnableIf <
                            ! cds :: meta :: isMemberFunctionPointer <
                                    __Predicate,
                                    cds :: meta :: Decay < decltype ( * cds :: meta :: valueOf < __IteratorType > () ) >
                            > ()
                    > = 0
            > __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __none (  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __IteratorType const & begin,
                    __IteratorType const & end,
                    __Predicate    const & predicate
            ) noexcept ( noexcept ( predicate ( * begin ) ) ) -> bool;

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_ITERATOR_STATEMENTS_HPP__ */
