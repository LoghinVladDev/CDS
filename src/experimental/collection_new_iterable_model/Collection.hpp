/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_EX_COLLECTION_HPP__
#define __CDS_EX_COLLECTION_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include <CDS/Object>
#include <CDS/Comparator>

#include "../../shared/memory/PrimitiveAllocation.hpp"

#include "collection/CollectionFunctions.hpp"

#include "shared/delegateIterator/ForwardDelegateWrapperIterator.hpp"

#include "shared/collectionInternalCommunication/channel/CollectionInternalCommunicationChannel.hpp"

#include "shared/collectionInternalCommunication/client/primitive/DelegateForwardConstIterablePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/ConstIteratorRemovePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/RandomInsertionPrimitiveClient.hpp"

#include "shared/collectionInternalCommunication/client/composite/ContainsOfCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/FindOfImmutableCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/FindByImmutableCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/RemoveOfCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/RemoveByCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/GenericImmutableStatementsCompositeClient.hpp"

#include "collection/CollectionConstructs.hpp"

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        /**
         * @class Abstract Object representing any Iterable Container of given elements of type
         * @tparam __ElementType is the type of elements contained into Collection
         *
         * @extends [public]            __CollectionCommunicationChannel - Base class used to communicate requests from Abstract Collection to Derived Collections
         * @extends [public,implicit]   Object - base cds Class, inherited from __CollectionCommunicationChannel
         * @extends [protected]         __CollectionFunctions - container for statically stored equals function
         *
         * @implements [public]         __CollectionDelegateForwardConstIterableClient - Abstract Iterator Request Client - begin / end / cbegin / cend
         * @implements [public]         __CollectionConstIteratorRemoveClient - Abstract Iterator Remove Client - remove
         * @implements [public]         __CollectionRandomInsertionClient - Insertion without specified position Client - <strike>add</strike> / <strike>addAll</strike> / <strike>addAllOf</strike> / insert / insertAll / insertAllOf / emplace
         * @implements [public]         __CollectionContainsOfCollectionClient - Contains Functions for Collection parameter Client - containsAnyOf / containsAllOf / containsAnyOf / containsAnyNotOf
         * @implements [public]         __CollectionContainsOfInitializerListClient - Contains Functions for std :: initializer_list parameter Client - containsAnyOf / containsAllOf / containsAnyOf / containsAnyNotOf
         * @implements [public]         __CollectionFindOfCollectionClient - Find Of Functions for Collection parameter Client - findOf / findFirstOf / findLastOf / findAllOf / findNotOf / findFirstNotOf / findLastNotOf / findAllNotOf
         * @implements [public]         __CollectionFindOfInitializerListClient - Find Of Functions for std :: initializer_list parameter Client - findOf / findFirstOf / findLastOf / findAllOf / findNotOf / findFirstNotOf / findLastNotOf / findAllNotOf
         * @implements [public]         __CollectionFindByClient - Find By Functions for Predicates Client - findThat / findFirstThat / findLastThat / findAllThat
         * @implements [public]         __CollectionRemoveOfCollectionClient - Remove Of Functions for Collection parameter Client - removeOf / removeFirstOf / removeLastOf / removeAllOf / removeNotOf / removeFirstNotOf / removeLastNotOf / removeAllNotOf
         * @implements [public]         __CollectionRemoveOfInitializerListClient - Remove Of Functions for std :: initializer_list parameter Client - removeOf / removeFirstOf / removeLastOf / removeAllOf / removeNotOf / removeFirstNotOf / removeLastNotOf / removeAllNotOf
         * @implements [public]         __CollectionRemoveByClient - Remove By Functions for Predicates Client - removeThat / removeFirstThat / removeLastThat / removeAllThat
         * @implements [public]         __CollectionGenericStatementsClient - Generic Functional Statements for Predicates - forEach / some / atLeast / atMost / moreThat / fewerThan / count / any / all / none
         *
         * @test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
         * @namespace cds :: experimental
         * @public
         */
        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        class Collection :
                public __hidden :: __impl :: __CollectionCommunicationChannel < __ElementType >,
                public __hidden :: __impl :: __CollectionDelegateForwardConstIterableClient < __ElementType >,
                public __hidden :: __impl :: __CollectionConstIteratorRemoveClient < __ElementType >,
                public __hidden :: __impl :: __CollectionRandomInsertionClient < __ElementType >,
                public __hidden :: __impl :: __CollectionContainsOfCollectionClient < __ElementType >,
                public __hidden :: __impl :: __CollectionContainsOfInitializerListClient < __ElementType >,
                public __hidden :: __impl :: __CollectionFindOfCollectionClient < __ElementType >,
                public __hidden :: __impl :: __CollectionFindOfInitializerListClient < __ElementType >,
                public __hidden :: __impl :: __CollectionFindByClient < __ElementType >,
                public __hidden :: __impl :: __CollectionRemoveOfCollectionClient < __ElementType >,
                public __hidden :: __impl :: __CollectionRemoveOfInitializerListClient < __ElementType >,
                public __hidden :: __impl :: __CollectionRemoveByClient < __ElementType >,
                public __hidden :: __impl :: __CollectionGenericStatementsClient < __ElementType >,
                protected __hidden :: __impl :: __CollectionFunctions < __ElementType > {

        public:
            /**
             * @typedef public alias for __ElementType, the type of the contained elements,
             * publicly accessible, useful in sfinae statements - decltype ( Collection ) :: ElementType
             * @public
             */
            using ElementType                           = __ElementType;

        protected:
            /**
             * @typedef protected alias for __CollectionCommunicationChannel base interface - providing communication channel abstract functions __cicch_obtainGenericHandler / __cicch_obtainGenericConstHandler
             * @protected
             */
            using CommunicationChannel                  = __hidden :: __impl :: __CollectionCommunicationChannel < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __CollectionDelegateForwardConstIterableClient base interface - providing begin / end / cbegin / cend for Abstract Iterators
             * @protected
             */
            using DelegateForwardConstIterableClient    = __hidden :: __impl :: __CollectionDelegateForwardConstIterableClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __CollectionConstIteratorRemoveClient base interface - providing remove for Abstract Iterators
             * @protected
             */
            using ConstIteratorRemoveClient             = __hidden :: __impl :: __CollectionConstIteratorRemoveClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __CollectionRandomInsertionClient base interface - providing insertion functions - <strike>add</strike> / <strike>addAll</strike> / <strike>addAllOf</strike> / insert / insertAll / insertAllOf / emplace
             * @protected
             */
            using RandomInsertionClient                 = __hidden :: __impl :: __CollectionRandomInsertionClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __CollectionContainsOfCollectionClient base interface - providing contains-of functions with a Collection parameter - containsAnyOf / containsAllOf / containsAnyOf / containsAnyNotOf
             * @protected
             */
            using ContainsOfCollectionClient            = __hidden :: __impl :: __CollectionContainsOfCollectionClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __CollectionContainsOfInitializerListClient base interface - providing contains-of functions with a std :: initializer_list parameter - containsAnyOf / containsAllOf / containsAnyOf / containsAnyNotOf
             * @protected
             */
            using ContainsOfInitializerListClient       = __hidden :: __impl :: __CollectionContainsOfInitializerListClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __CollectionFindOfCollectionClient base interface - providing find-of functions with a Collection parameter - findOf / findFirstOf / findLastOf / findAllOf / findNotOf / findFirstNotOf / findLastNotOf / findAllNotOf
             * @protected
             */
            using FindOfCollectionClient                = __hidden :: __impl :: __CollectionFindOfCollectionClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __CollectionFindOfInitializerListClient base interface - providing find-of functions with a std :: initializer_list parameter - findOf / findFirstOf / findLastOf / findAllOf / findNotOf / findFirstNotOf / findLastNotOf / findAllNotOf
             * @protected
             */
            using FindOfInitializerListClient           = __hidden :: __impl :: __CollectionFindOfInitializerListClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __CollectionFindByClient base interface - providing find-by-predicate functions - findThat / findFirstThat / findLastThat / findAllThat
             * @protected
             */
             using FindByClient                          = __hidden :: __impl :: __CollectionFindByClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __CollectionRemoveOfCollectionClient base interface - providing remove-of functions with a Collection parameter - removeOf / removeFirstOf / removeLastOf / removeAllOf / removeNotOf / removeFirstNotOf / removeLastNotOf / removeAllNotOf
             * @protected
             */
            using RemoveOfCollectionClient              = __hidden :: __impl :: __CollectionRemoveOfCollectionClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __CollectionRemoveOfInitializerListClient base interface - providing remove-of functions with a std :: initializer_list parameter - removeOf / removeFirstOf / removeLastOf / removeAllOf / removeNotOf / removeFirstNotOf / removeLastNotOf / removeAllNotOf
             * @protected
             */
            using RemoveOfInitializerListClient         = __hidden :: __impl :: __CollectionRemoveOfInitializerListClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __CollectionRemoveByClient base interface - providing remove-by-predicate functions - removeThat / removeFirstThat / removeLastThat / removeAllThat
             * @protected
             */
            using RemoveByClient                        = __hidden :: __impl :: __CollectionRemoveByClient < __ElementType >;

        protected:
            /**
             * @typedef protected alias for __CollectionGenericStatementsClient base interface - providing functional-predicate functions - forEach / some / atLeast / atMost / moreThat / fewerThan / count / any / all / none
             * @protected
             */
            using GenericStatementsClient               = __hidden :: __impl :: __CollectionGenericStatementsClient < __ElementType >;

        protected:
            /**
             * @typedef imported protected alias for __GenericHandler, representing a generic member function pointer, represents a function returned at a request made through the Collection Communication Channel
             * @protected
             */
            using __GenericHandler                      = typename CommunicationChannel :: __GenericHandler;        /* NOLINT(bugprone-reserved-identifier) */

        protected:
            /**
             * @typedef imported protected alias for __GenericConstHandler, representing a generic member const-function pointer, represents a function returned at a request made through the Collection Communication Channel
             * @protected
             */
            using __GenericConstHandler                 = typename CommunicationChannel :: __GenericConstHandler;   /* NOLINT(bugprone-reserved-identifier) */

        public:
            /**
             * @typedef The Const Iterator Type, imported from Abstract Forward Iterator Client
             * @public
             */
            using ConstIterator                         = typename DelegateForwardConstIterableClient :: ConstIterator;

        protected:
            /**
             * @brief Default Constructor
             * @exceptsafe
             * @test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
             * @protected
             */
            constexpr Collection () noexcept;

        protected:
            /**
             * @brief Copy Constructor
             * @param [in] collection : Collection cref = Constant Reference to a collection to copy data from
             * @exceptsafe
             * @test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
             * @protected
             */
            constexpr Collection (
                    Collection const & collection
            ) noexcept;

        protected:
            /**
             * @brief Move Constructor
             * @param [in] collection : Collection mref = Move Reference to a collection to copy data from
             * @exceptsafe
             * @test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
             * @protected
             */
            constexpr Collection (
                    Collection && collection
            ) noexcept;

        public:
            /**
             * @brief Destructor Constructor
             * @exceptsafe
             * @test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
             * @public
             */
            __CDS_cpplang_ConstexprDestructor ~Collection() noexcept;

        public: 
            /** 
             * @inherit begin function inherited from DelegateForwardConstIterableClient interface.
             * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00051-IT-range, CTC-00052-IT-begin_end,
             *      CTC-00054-IT-e_begin_end, CTC-00056-IT-e_emptyRange }
             * @public
             */
            using DelegateForwardConstIterableClient :: begin;
            
        public:
            /**
             * @inherit end function inherited from DelegateForwardConstIterableClient interface.
             * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00051-IT-range, CTC-00052-IT-begin_end,
             *      CTC-00054-IT-e_begin_end, CTC-00056-IT-e_emptyRange }
             * @public
             */
            using DelegateForwardConstIterableClient :: end;

        public:
            /**
             * @inherit cbegin function inherited from DelegateForwardConstIterableClient interface.
             * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00051-IT-range, CTC-00053-IT-cbegin_cend,
             *      CTC-00055-IT-e_cbegin_cend, CTC-00056-IT-e_emptyRange }
             * @public
             */
            using DelegateForwardConstIterableClient :: cbegin;

        public:
            /**
             * @inherit cend function inherited from DelegateForwardConstIterableClient interface.
             * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00051-IT-range, CTC-00053-IT-cbegin_cend,
             *      CTC-00055-IT-e_cbegin_cend, CTC-00056-IT-e_emptyRange }
             * @public
             */
             using DelegateForwardConstIterableClient :: cend;

        public:
            /**
             * @inherit forEach functional call, inherited from GenericStatementsClient interface
             * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00139-FS-forEachCount }
             * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00201-FSMF-forEach }
             * @public
             */
            using GenericStatementsClient :: forEach;

        public:
            /**
             * @inherit some functional call, inherited from GenericStatementsClient interface
             * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00136-FS-someExact, CTC-00137-FS-someLessFalse, CTC-00138-someMoreFalse }
             * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00202-FSMF-someEqual, CTC-00203-FSMF-someLess, CTC-00204-someMore }
             * @public
             */
             using GenericStatementsClient :: some;

        public:
            /**
             * @inherit some functional call, inherited from GenericStatementsClient interface
             * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00132-FS-atLeastTrue, CTC-00133-FS-atLeastCloseTrue, CTC-00134-atLeastCloseFalse, CTC-00135-atLeastFalse }
             * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00205-FSMF-atLeast, CTC-00206-FSMF-atLeastLess, CTC-00207-atLeastMore }
             * @public
             */
            using GenericStatementsClient :: atLeast;

        public:
            /**
             * @inherit some functional call, inherited from GenericStatementsClient interface
             * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00128-FS-atMostTrue, CTC-00129-FS-atMostCloseTrue, CTC-00130-atMostCloseFalse, CTC-00131-atMostFalse }
             * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00208-FSMF-atMost, CTC-00209-FSMF-atMostLess, CTC-00210-atMostMore }
             * @public
             */
            using GenericStatementsClient :: atMost;

        public:
            /**
             * @inherit some functional call, inherited from GenericStatementsClient interface
             * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00123-FS-moreThanTrue, CTC-00124-FS-moreThanCloseTrue, CTC-00125-moreThanCloseFalse, CTC-00126-moreThanFalse, CTC-00127-moreThanCompletelyFalse }
             * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00211-FSMF-moreThan, CTC-00212-FSMF-moreThanLess, CTC-00213-moreThanMore }
             * @public
             */
            using GenericStatementsClient :: moreThan;

        public:
            /**
             * @inherit some functional call, inherited from GenericStatementsClient interface
             * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00118-FS-fewerThanTrue, CTC-00119-FS-fewerThanCloseTrue, CTC-00120-fewerThanCloseFalse, CTC-00121-fewerThanFalse, CTC-00122-fewerThanCompletelyFalse }
             * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00214-FSMF-fewerThan, CTC-00215-FSMF-fewerThanLess, CTC-00216-fewerThanMore }
             * @public
             */
            using GenericStatementsClient :: fewerThan;

        public:
            /**
             * @inherit some functional call, inherited from GenericStatementsClient interface
             * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00113-FS-countProp1, CTC-00114-FS-countProp2, CTC-00115-countProp3, CTC-00116-countProp4, CTC-00117-countPropLbd }
             * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00217-FSMF-countExact }
             * @public
             */
             using GenericStatementsClient :: count;

        public:
            /**
             * @inherit some functional call, inherited from GenericStatementsClient interface
             * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00101-FS-anyNone, CTC-00102-FS-anyOne, CTC-00103-anyMore, CTC-00104-anyAll }
             * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00218-FSMF-anyNone, CTC-00219-FSMF-anyOne, CTC-00220-anyMore, CTC-00221-anyAll }
             * @public
             */
             using GenericStatementsClient :: any;

        public:
            /**
             * @inherit some functional call, inherited from GenericStatementsClient interface
             * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00105-FS-allNone, CTC-00106-FS-allOne, CTC-00107-allMore, CTC-00108-allAll }
             * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00222-FSMF-allNone, CTC-00223-FSMF-allOne, CTC-00224-allMore, CTC-00225-allAll }
             * @public
             */
            using GenericStatementsClient :: all;

        public:
            /**
             * @inherit some functional call, inherited from GenericStatementsClient interface
             * @test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00109-FS-noneNone, CTC-00110-FS-noneOne, CTC-00111-noneMore, CTC-00112-noneAll }
             * @test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00226-FSMF-noneNone, CTC-00227-FSMF-noneOne, CTC-00228-noneMore, CTC-00229-noneAll }
             * @public
             */
            using GenericStatementsClient :: none;

        public:
            /**
             * @inherit containsAnyOf ( Collection ) call, inherited from ContainsOfCollectionClient interface
             * @test Suite: CTS-00001, Group: CTG-00300-CO, Test Cases: {
             *      CTC-00301-CO-containsAnyOfCollectionNoneCommon [-Collection Group],
             *      CTC-00302-CO-containsAnyOfCollectionOneCommon [-Collection Group],
             *      CTC-00303-CO-containsAnyOfCollectionMoreCommon [-Collection Group],
             *      CTC-00304-CO-containsAnyOfCollectionAllCommon [-Collection Group],
             *      CTC-00305-CO-containsAnyOfCollectionAllCommonAndMore [-Collection Group]
             * }
             * @public
             */
            using ContainsOfCollectionClient :: containsAnyOf;

        public:
            /**
             * @inherit containsAllOf ( Collection ) call, inherited from ContainsOfCollectionClient interface
             * @test Suite: CTS-00001, Group: CTG-00300-CO, Test Cases: {
             *      CTC-00306-CO-containsAllOfCollectionNoneCommon [-Collection Group],
             *      CTC-00307-CO-containsAllOfCollectionOneCommon [-Collection Group],
             *      CTC-00308-CO-containsAllOfCollectionMoreCommon [-Collection Group],
             *      CTC-00309-CO-containsAllOfCollectionAllCommon [-Collection Group],
             *      CTC-00310-CO-containsAllOfCollectionAllCommonAndMore [-Collection Group]
             * }
             * @public
             */
            using ContainsOfCollectionClient :: containsAllOf;

        public:
            /**
             * @inherit containsAnyNotOf ( Collection ) call, inherited from ContainsOfCollectionClient interface
             * @test Suite: CTS-00001, Group: CTG-00300-CO, Test Cases: {
             *      CTC-00311-CO-containsAnyNotOfCollectionNoneCommon [-Collection Group],
             *      CTC-00312-CO-containsAnyNotOfCollectionOneCommon [-Collection Group],
             *      CTC-00313-CO-containsAnyNotOfCollectionMoreCommon [-Collection Group],
             *      CTC-00314-CO-containsAnyNotOfCollectionAllCommon [-Collection Group],
             *      CTC-00315-CO-containsAnyNotOfCollectionAllCommonAndMore [-Collection Group]
             * }
             * @public
             */
            using ContainsOfCollectionClient :: containsAnyNotOf;

        public:
            /**
             * @inherit containsNoneOf ( Collection ) call, inherited from ContainsOfCollectionClient interface
             * @test Suite: CTS-00001, Group: CTG-00300-CO, Test Cases: {
             *      CTC-00316-CO-containsNoneOfCollectionNoneCommon [-Collection Group],
             *      CTC-00317-CO-containsNoneOfCollectionOneCommon [-Collection Group],
             *      CTC-00318-CO-containsNoneOfCollectionMoreCommon [-Collection Group],
             *      CTC-00319-CO-containsNoneOfCollectionAllCommon [-Collection Group],
             *      CTC-00320-CO-containsNoneOfCollectionAllCommonAndMore [-Collection Group]
             * }
             * @public
             */
            using ContainsOfCollectionClient :: containsNoneOf;

        public:
            /**
             * @inherit containsAnyOf ( std :: initializer_list ) call, inherited from ContainsOfInitializerListClient interface
             * @test Suite: CTS-00001, Group: CTG-00300-CO, Test Cases: {
             *      CTC-00301-CO-containsAnyOfCollectionNoneCommon [-InitializerList Group],
             *      CTC-00302-CO-containsAnyOfCollectionOneCommon [-InitializerList Group],
             *      CTC-00303-CO-containsAnyOfCollectionMoreCommon [-InitializerList Group],
             *      CTC-00304-CO-containsAnyOfCollectionAllCommon [-InitializerList Group],
             *      CTC-00305-CO-containsAnyOfCollectionAllCommonAndMore [-InitializerList Group]
             * }
             * @public
             */
            using ContainsOfInitializerListClient :: containsAnyOf;

        public:
            /**
             * @inherit containsAllOf ( std :: initializer_list ) call, inherited from ContainsOfInitializerListClient interface
             * @test Suite: CTS-00001, Group: CTG-00300-CO, Test Cases: {
             *      CTC-00306-CO-containsAllOfCollectionNoneCommon [-InitializerList Group],
             *      CTC-00307-CO-containsAllOfCollectionOneCommon [-InitializerList Group],
             *      CTC-00308-CO-containsAllOfCollectionMoreCommon [-InitializerList Group],
             *      CTC-00309-CO-containsAllOfCollectionAllCommon [-InitializerList Group],
             *      CTC-00310-CO-containsAllOfCollectionAllCommonAndMore [-InitializerList Group]
             * }
             * @public
             */
            using ContainsOfInitializerListClient :: containsAllOf;

        public:
            /**
             * @inherit containsAnyNotOf ( std :: initializer_list ) call, inherited from ContainsOfInitializerListClient interface
             * @test Suite: CTS-00001, Group: CTG-00300-CO, Test Cases: {
             *      CTC-00311-CO-containsAnyNotOfCollectionNoneCommon [-InitializerList Group],
             *      CTC-00312-CO-containsAnyNotOfCollectionOneCommon [-InitializerList Group],
             *      CTC-00313-CO-containsAnyNotOfCollectionMoreCommon [-InitializerList Group],
             *      CTC-00314-CO-containsAnyNotOfCollectionAllCommon [-InitializerList Group],
             *      CTC-00315-CO-containsAnyNotOfCollectionAllCommonAndMore [-InitializerList Group]
             * }
             * @public
             */
            using ContainsOfInitializerListClient :: containsAnyNotOf;

        public:
            /**
             * @inherit containsNoneOf ( std :: initializer_list ) call, inherited from ContainsOfInitializerListClient interface
             * @test Suite: CTS-00001, Group: CTG-00300-CO, Test Cases: {
             *      CTC-00316-CO-containsNoneOfCollectionNoneCommon [-InitializerList Group],
             *      CTC-00317-CO-containsNoneOfCollectionOneCommon [-InitializerList Group],
             *      CTC-00318-CO-containsNoneOfCollectionMoreCommon [-InitializerList Group],
             *      CTC-00319-CO-containsNoneOfCollectionAllCommon [-InitializerList Group],
             *      CTC-00320-CO-containsNoneOfCollectionAllCommonAndMore [-InitializerList Group]
             * }
             * @public
             */
            using ContainsOfInitializerListClient :: containsNoneOf;

        public:
            /**
             * @inherit remove ( ConstIterator ) call, inherited from ConstIteratorPrimitiveClient interface
             * @test Suite: CTS-00001, Group: CTG-00350-RAIT, Test Cases: {
             *      CTC-00351-RAIT-removeAtFront,
             *      CTC-00352-RAIT-removeInBounds,
             *      CTC-00353-RAIT-removeAtEnd,
             *      CTC-00355-RAIT-removeBeforeFront,
             *      CTC-00356-RAIT-removeFromOther
             * }
             * @public
             */
            using ConstIteratorRemoveClient :: remove;

        public:
            /**
             * @inherit removeThat ( maxCount, Predicate ) call, inherited from RemoveByClient interface
             * @test Suite: CTS-00001, Group: CTG-00400-RB, Test Cases: {
             *      CTC-00401-RB-removeThatMatchesNone,
             *      CTC-00402-RB-removeThatMatchesOne,
             *      CTC-00403-RB-removeThatMatchesMoreLessThanLimit,
             *      CTC-00404-RB-removeThatMatchesMoreExact,
             *      CTC-00405-RB-removeThatMatchesMoreThanLimit,
             *      CTC-00406-RB-removeThatMatchesAll,
             *      CTC-00419-RB-memberRemoveThat
             * }
             * @public
             */
            using RemoveByClient :: removeThat;

        public:
            /**
             * @inherit removeFirstThat ( Predicate ) call, inherited from RemoveByClient interface
             * @test Suite: CTS-00001, Group: CTG-00400-RB, Test Cases: {
             *      CTC-00407-RB-removeFirstThatMatchesNone,
             *      CTC-00408-RB-removeFirstThatMatchesOne,
             *      CTC-00409-RB-removeFirstThatMatchesMore,
             *      CTC-00410-RB-removeFirstThatMatchesAll,
             *      CTC-00420-RB-memberRemoveFirstThat
             * }
             * @public
             */
            using RemoveByClient :: removeFirstThat;

        public:
            /**
             * @inherit removeLastThat ( Predicate ) call, inherited from RemoveByClient interface
             * @test Suite: CTS-00001, Group: CTG-00400-RB, Test Cases: {
             *      CTC-00411-RB-removeLastThatMatchesNone,
             *      CTC-00412-RB-removeLastThatMatchesOne,
             *      CTC-00413-RB-removeLastThatMatchesMore,
             *      CTC-00414-RB-removeLastThatMatchesAll,
             *      CTC-00421-RB-memberRemoveLastThat
             * }
             * @public
             */
            using RemoveByClient :: removeLastThat;

        public:
            /**
             * @inherit removeAllThat ( Predicate ) call, inherited from RemoveByClient interface
             * @test Suite: CTS-00001, Group: CTG-00400-RB, Test Cases: {
             *      CTC-00415-RB-removeAllThatMatchesNone,
             *      CTC-00416-RB-removeAllThatMatchesOne,
             *      CTC-00417-RB-removeAllThatMatchesMore,
             *      CTC-00418-RB-removeAllThatMatchesAll,
             *      CTC-00422-RB-memberRemoveAllThat
             * }
             * @public
             */
            using RemoveByClient :: removeAllThat;

        public:
            /**
             * @inherit removeOf ( Collection ) call, inherited from RemoveOfCollectionClient interface
             * @test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: {
             *      CTC-00451-RO-removeOfNoneCommon [-Collection Group],
             *      CTC-00452-RO-removeOfOneCommon [-Collection Group],
             *      CTC-00453-RO-removeOfMoreLessThanLimitCommon [-Collection Group],
             *      CTC-00454-RO-removeOfMoreCommon [-Collection Group],
             *      CTC-00455-RO-removeOfMoreMoreThanLimitCommon [-Collection Group],
             *      CTC-00456-RO-removeOfAllCommon [-Collection Group],
             *      CTC-00457-RO-removeOfAllAndMoreCommon [-Collection Group]
             * }
             * @public
             */
            using RemoveOfCollectionClient :: removeOf;

        public:
            /**
             * @inherit removeFirstOf ( Collection ) call, inherited from RemoveOfCollectionClient interface
             * @test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: {
             *      CTC-00501-RO-removeFirstOfNoneCommon [-Collection Group],
             *      CTC-00502-RO-removeFirstOfOneCommon [-Collection Group],
             *      CTC-00503-RO-removeFirstOfMoreCommon [-Collection Group],
             *      CTC-00504-RO-removeFirstOfAllCommon [-Collection Group],
             *      CTC-00505-RO-removeFirstOfAllAndMoreCommon [-Collection Group]
             * }
             * @public
             */
            using RemoveOfCollectionClient :: removeFirstOf;

        public:
            /**
             * @inherit removeLastOf ( Collection ) call, inherited from RemoveOfCollectionClient interface
             * @test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: {
             *      CTC-00506-RO-removeLastOfNoneCommon [-Collection Group],
             *      CTC-00507-RO-removeLastOfOneCommon [-Collection Group],
             *      CTC-00508-RO-removeLastOfMoreCommon [-Collection Group],
             *      CTC-00509-RO-removeLastOfAllCommon [-Collection Group],
             *      CTC-00510-RO-removeLastOfAllAndMoreCommon [-Collection Group]
             * }
             * @public
             */
            using RemoveOfCollectionClient :: removeLastOf;

        public:
            /**
             * @inherit removeAllOf ( Collection ) call, inherited from RemoveOfCollectionClient interface
             * @test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: {
             *      CTC-00481-RO-removeAllOfNoneCommon [-Collection Group],
             *      CTC-00482-RO-removeAllOfOneCommon [-Collection Group],
             *      CTC-00483-RO-removeAllOfMoreCommon [-Collection Group],
             *      CTC-00484-RO-removeAllOfAllCommon [-Collection Group],
             *      CTC-00485-RO-removeAllOfAllAndMoreCommon [-Collection Group]
             * }
             * @public
             */
            using RemoveOfCollectionClient :: removeAllOf;

        public:
            /**
             * @inherit removeNotOf ( Collection ) call, inherited from RemoveOfCollectionClient interface
             * @test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: {
             *      CTC-00458-RO-removeNotOfNoneCommon [-Collection Group],
             *      CTC-00459-RO-removeNotOfOneCommon [-Collection Group],
             *      CTC-00460-RO-removeNotOfMoreLessThanLimitCommon [-Collection Group],
             *      CTC-00461-RO-removeNotOfMoreCommon [-Collection Group],
             *      CTC-00462-RO-removeNotOfMoreMoreThanLimitCommon [-Collection Group],
             *      CTC-00463-RO-removeNotOfAllCommon [-Collection Group],
             *      CTC-00464-RO-removeNotOfAllAndMoreCommon [-Collection Group]
             * }
             * @public
             */
            using RemoveOfCollectionClient :: removeNotOf;

        public:
            /**
             * @inherit removeFirstNotOf ( Collection ) call, inherited from RemoveOfCollectionClient interface
             * @test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: {
             *      CTC-00511-RO-removeFirstNotOfNoneCommon [-Collection Group],
             *      CTC-00512-RO-removeFirstNotOfOneCommon [-Collection Group],
             *      CTC-00513-RO-removeFirstNotOfMoreCommon [-Collection Group],
             *      CTC-00514-RO-removeFirstNotOfAllCommon [-Collection Group],
             *      CTC-00515-RO-removeFirstNotOfAllAndMoreCommon [-Collection Group]
             * }
             * @public
             */
            using RemoveOfCollectionClient :: removeFirstNotOf;

        public:
            /**
             * @inherit removeLastNotOf ( Collection ) call, inherited from RemoveOfCollectionClient interface
             * @test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: {
             *      CTC-00516-RO-removeLastNotOfNoneCommon [-Collection Group],
             *      CTC-00517-RO-removeLastNotOfOneCommon [-Collection Group],
             *      CTC-00518-RO-removeLastNotOfMoreCommon [-Collection Group],
             *      CTC-00519-RO-removeLastNotOfAllCommon [-Collection Group],
             *      CTC-00520-RO-removeLastNotOfAllAndMoreCommon [-Collection Group]
             * }
             * @public
             */
            using RemoveOfCollectionClient :: removeLastNotOf;

        public:
            /**
             * @inherit removeAllNotOf ( Collection ) call, inherited from RemoveOfCollectionClient interface
             * @test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: {
             *      CTC-00486-RO-removeAllNotOfNoneCommon [-Collection Group],
             *      CTC-00487-RO-removeAllNotOfOneCommon [-Collection Group],
             *      CTC-00488-RO-removeAllNotOfMoreCommon [-Collection Group],
             *      CTC-00489-RO-removeAllNotOfAllCommon [-Collection Group],
             *      CTC-00490-RO-removeAllNotOfAllAndMoreCommon [-Collection Group]
             * }
             * @public
             */
            using RemoveOfCollectionClient :: removeAllNotOf;

        public:
            /**
             * @inherit removeOf ( std :: initializer_list ) call, inherited from RemoveOfInitializerListClient interface
             * @test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: {
             *      CTC-00451-RO-removeOfNoneCommon [-InitializerList Group],
             *      CTC-00452-RO-removeOfOneCommon [-InitializerList Group],
             *      CTC-00453-RO-removeOfMoreLessThanLimitCommon [-InitializerList Group],
             *      CTC-00454-RO-removeOfMoreCommon [-InitializerList Group],
             *      CTC-00455-RO-removeOfMoreMoreThanLimitCommon [-InitializerList Group],
             *      CTC-00456-RO-removeOfAllCommon [-InitializerList Group],
             *      CTC-00457-RO-removeOfAllAndMoreCommon [-InitializerList Group]
             * }
             * @public
             */
            using RemoveOfInitializerListClient :: removeOf;

        public:
            /**
             * @inherit removeFirstOf ( std :: initializer_list ) call, inherited from RemoveOfInitializerListClient interface
             * @test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: {
             *      CTC-00501-RO-removeFirstOfNoneCommon [-InitializerList Group],
             *      CTC-00502-RO-removeFirstOfOneCommon [-InitializerList Group],
             *      CTC-00503-RO-removeFirstOfMoreCommon [-InitializerList Group],
             *      CTC-00504-RO-removeFirstOfAllCommon [-InitializerList Group],
             *      CTC-00505-RO-removeFirstOfAllAndMoreCommon [-InitializerList Group]
             * }
             * @public
             */
            using RemoveOfInitializerListClient :: removeFirstOf;

        public:
            /**
             * @inherit removeLastOf ( std :: initializer_list ) call, inherited from RemoveOfInitializerListClient interface
             * @test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: {
             *      CTC-00506-RO-removeLastOfNoneCommon [-InitializerList Group],
             *      CTC-00507-RO-removeLastOfOneCommon [-InitializerList Group],
             *      CTC-00508-RO-removeLastOfMoreCommon [-InitializerList Group],
             *      CTC-00509-RO-removeLastOfAllCommon [-InitializerList Group],
             *      CTC-00510-RO-removeLastOfAllAndMoreCommon [-InitializerList Group]
             * }
             * @public
             */
            using RemoveOfInitializerListClient :: removeLastOf;

        public:
            /**
             * @inherit removeAllOf ( std :: initializer_list ) call, inherited from RemoveOfInitializerListClient interface
             * @test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: {
             *      CTC-00481-RO-removeAllOfNoneCommon [-InitializerList Group],
             *      CTC-00482-RO-removeAllOfOneCommon [-InitializerList Group],
             *      CTC-00483-RO-removeAllOfMoreCommon [-InitializerList Group],
             *      CTC-00484-RO-removeAllOfAllCommon [-InitializerList Group],
             *      CTC-00485-RO-removeAllOfAllAndMoreCommon [-InitializerList Group]
             * }
             * @public
             */
            using RemoveOfInitializerListClient :: removeAllOf;

        public:
            /**
             * @inherit removeNotOf ( std :: initializer_list ) call, inherited from RemoveOfInitializerListClient interface
             * @test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: {
             *      CTC-00458-RO-removeNotOfNoneCommon [-InitializerList Group],
             *      CTC-00459-RO-removeNotOfOneCommon [-InitializerList Group],
             *      CTC-00460-RO-removeNotOfMoreLessThanLimitCommon [-InitializerList Group],
             *      CTC-00461-RO-removeNotOfMoreCommon [-InitializerList Group],
             *      CTC-00462-RO-removeNotOfMoreMoreThanLimitCommon [-InitializerList Group],
             *      CTC-00463-RO-removeNotOfAllCommon [-InitializerList Group],
             *      CTC-00464-RO-removeNotOfAllAndMoreCommon [-InitializerList Group]
             * }
             * @public
             */
            using RemoveOfInitializerListClient :: removeNotOf;

        public:
            /**
             * @inherit removeFirstNotOf ( std :: initializer_list ) call, inherited from RemoveOfInitializerListClient interface
             * @test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: {
             *      CTC-00511-RO-removeFirstNotOfNoneCommon [-InitializerList Group],
             *      CTC-00512-RO-removeFirstNotOfOneCommon [-InitializerList Group],
             *      CTC-00513-RO-removeFirstNotOfMoreCommon [-InitializerList Group],
             *      CTC-00514-RO-removeFirstNotOfAllCommon [-InitializerList Group],
             *      CTC-00515-RO-removeFirstNotOfAllAndMoreCommon [-InitializerList Group]
             * }
             * @public
             */
            using RemoveOfInitializerListClient :: removeFirstNotOf;

        public:
            /**
             * @inherit removeLastNotOf ( std :: initializer_list ) call, inherited from RemoveOfInitializerListClient interface
             * @test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: {
             *      CTC-00516-RO-removeLastNotOfNoneCommon [-InitializerList Group],
             *      CTC-00517-RO-removeLastNotOfOneCommon [-InitializerList Group],
             *      CTC-00518-RO-removeLastNotOfMoreCommon [-InitializerList Group],
             *      CTC-00519-RO-removeLastNotOfAllCommon [-InitializerList Group],
             *      CTC-00520-RO-removeLastNotOfAllAndMoreCommon [-InitializerList Group]
             * }
             * @public
             */
            using RemoveOfInitializerListClient :: removeLastNotOf;

        public:
            /**
             * @inherit removeAllNotOf ( std :: initializer_list ) call, inherited from RemoveOfInitializerListClient interface
             * @test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: {
             *      CTC-00486-RO-removeAllNotOfNoneCommon [-InitializerList Group],
             *      CTC-00487-RO-removeAllNotOfOneCommon [-InitializerList Group],
             *      CTC-00488-RO-removeAllNotOfMoreCommon [-InitializerList Group],
             *      CTC-00489-RO-removeAllNotOfAllCommon [-InitializerList Group],
             *      CTC-00490-RO-removeAllNotOfAllAndMoreCommon [-InitializerList Group]
             * }
             * @public
             */
            using RemoveOfInitializerListClient :: removeAllNotOf;

        public: using FindByClient :: findThat;
        public: using FindByClient :: findFirstThat;
        public: using FindByClient :: findLastThat;
        public: using FindByClient :: findAllThat;

        public: using FindOfCollectionClient :: findOf;
        public: using FindOfCollectionClient :: findFirstOf;
        public: using FindOfCollectionClient :: findLastOf;
        public: using FindOfCollectionClient :: findAllOf;
        public: using FindOfCollectionClient :: findNotOf;
        public: using FindOfCollectionClient :: findFirstNotOf;
        public: using FindOfCollectionClient :: findLastNotOf;
        public: using FindOfCollectionClient :: findAllNotOf;

        public: using FindOfInitializerListClient :: findOf;
        public: using FindOfInitializerListClient :: findFirstOf;
        public: using FindOfInitializerListClient :: findLastOf;
        public: using FindOfInitializerListClient :: findAllOf;
        public: using FindOfInitializerListClient :: findNotOf;
        public: using FindOfInitializerListClient :: findFirstNotOf;
        public: using FindOfInitializerListClient :: findLastNotOf;
        public: using FindOfInitializerListClient :: findAllNotOf;

        public: using RandomInsertionClient :: add;
        public: using RandomInsertionClient :: addAll;
        public: using RandomInsertionClient :: addAllOf;
        public: using RandomInsertionClient :: insert;
        public: using RandomInsertionClient :: insertAll;
        public: using RandomInsertionClient :: insertAllOf;
        public: using RandomInsertionClient :: emplace;


        public:
            /**
             * @brief Function used to acquire the number of elements in the collection
             * @exceptsafe
             * @return Size = number of elements inside the collection
             * @test Suite: CTS-00001, Group: CTG-00002-MF, Test Cases: { CTC-00004-MF-size, CTC-00010-MF-clear }
             * @public
             */
            __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto size () const noexcept -> Size;

        public:
            /**
             * @brief Function used to check if the collection does not contain any elements ( is empty )
             * @exceptsafe
             * @return bool = true if the collection is empty ( does not contain any elements ), false otherwise
             * @test Suite: CTS-00001, Group: CTG-00002-MF, Test Cases: { CTC-00005-MF-empty, CTC-00010-MF-clear }
             * @public
             */
            __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto empty () const noexcept -> bool;

        public:
            /**
             * @brief Bool cast operator, functionality equal to python's iterable empty check. '(bool) collection' is equivalent to '! collection.empty()'
             * @exceptsafe
             * @return bool = true if collection is not empty, false otherwise
             * @test Suite: CTS-00001, Group: CTG-00002-MF, Test Cases: { CTC-00006-MF-boolCast, CTC-00010-MF-clear }
             * @public
             */
            __CDS_cpplang_VirtualConstexpr __CDS_Explicit operator bool () const noexcept;

        public:
            /**
             * @brief String conversion function, used to obtain String representation of the Collection
             * @exceptsafe
             * @return String = string representation
             * @test Suite: CTS-00001, Group: CTG-00002-MF, Test Cases: { CTC-00003-MF-toString, CTC-00010-MF-clear }
             * @public
             */
            __CDS_NoDiscard auto toString () const noexcept -> String override;

        public:
            /**
             * @brief Hash function, used to obtain the hash value of the Collection
             * @exceptsafe
             * @return Index = hash code value of the instance
             * @test Suite: CTS-00001, Group: CTG-00002-MF, Test Cases: { CTC-00009-MF-hash, CTC-00010-MF-clear }
             * @public
             */
            __CDS_NoDiscard auto hash () const noexcept -> Size override;

        public:
            /**
             * @brief Explicit Comparison Function with generic CDS/Object
             * @param [in] object : Object cref = Constant Reference to an Object-derived instance
             * @exceptsafe
             * @return bool = true if objects are equal, false otherwise
             * @test Suite: CTS-00001, Group: CTG-00002-MF, Test Cases: { CTC-00010-MF-clear, CTC-00011-MF-equalsSelf,
             *      CTC-00012-MF-equalsTrueSameType, CTC-00013-MF-equalsTrueDifferentType, CTC-00014-MF-equalsFalseSameType,
             *      CTC-00015-MF-equalsFalseDifferentType, CTC-00016-MF-equalsFalseNotCollection }
             * @public
             */
            __CDS_NoDiscard auto equals (
                    Object const & object
            ) const noexcept -> bool override;

        public:
            /**
             * @brief Function used to clear the collection, removing all elements from it
             * @exceptsafe
             * @test Suite: CTS-00001, Group: CTG-00002-MF, Test Cases: { CTC-00010-MF-clear }
             * @public
             */
            virtual auto clear () noexcept -> void = 0;

        public:
            /**
             * @brief Function used to check if the collection contains the requested element.
             * @param [in] element : ElementType cref = Constant Reference to the element to be found in the collection
             * @return bool = true if the element exists in the collection, false otherwise
             * @test Suite: CTS-00001, Group: CTG-00002-MF, Test Cases: { CTC-00007-MF-containsTrue, CTC-00008-MF-containsFalse, CTC-00010-MF-clear }
             * @public
             */
            __CDS_NoDiscard virtual auto contains (
                    ElementType const & element
            ) const noexcept -> bool;

        };


    }
}

#include "collection/impl/CollectionConstructs.hpp"
#include "collection/impl/CollectionFunctions.hpp"

#include "shared/delegateIterator/impl/ForwardDelegateWrapperIterator.hpp"
#include "shared/collectionInternalCommunication/channel/impl/CollectionInternalCommunicationChannel.hpp"
#include "shared/collectionInternalCommunication/client/primitive/impl/DelegateForwardConstIterablePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/impl/ConstIteratorRemovePrimitiveClient.hpp"
#include "shared/collectionInternalCommunication/client/primitive/impl/RandomInsertionPrimitiveClient.hpp"

#include "shared/collectionInternalCommunication/client/composite/impl/ContainsOfCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/impl/FindOfImmutableCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/impl/FindByImmutableCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/impl/RemoveOfCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/impl/RemoveByCompositeClient.hpp"
#include "shared/collectionInternalCommunication/client/composite/impl/GenericImmutableStatementsCompositeClient.hpp"

#include "collection/impl/Collection.hpp"

#endif /* __CDS_EX_COLLECTION_HPP__ */
