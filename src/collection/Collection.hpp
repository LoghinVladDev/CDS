/*
 * Created by loghin on 15.01.2021.
 */

#ifndef __CDS_COLLECTION_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_COLLECTION_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Iterable>                                                                                                 /* NOLINT(llvm-include-order) */
#include <CDS/FunctionalInterface>

#include "collection/Functions.hpp"

#include "../shared/iterableInternalCommunication/client/primitive/ConstIteratorRemovePrimitiveClient.hpp"
#include "../shared/iterableInternalCommunication/client/primitive/RandomInsertionPrimitiveClient.hpp"

#include "../shared/iterableInternalCommunication/client/composite/RemoveOfCompositeClient.hpp"                         /* NOLINT(llvm-include-order) */
#include "../shared/iterableInternalCommunication/client/composite/RemoveByCompositeClient.hpp"

#include "collection/Constructs.hpp"

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */

    /**
     * @class Abstract Object representing any Iterable Container of given elements
     * @tparam __ElementType is the type of elements contained into Collection
     *
     * @extends [public]            Iterable - Base class representing a potentially infinite iterable object. In this case, finite, since it's a container
     * @extends [public,implicit]   Object - base cds Class, inherited from __CollectionCommunicationChannel
     *
     * @implements [public]         __CollectionConstIteratorRemoveClient - Abstract Iterator Remove Client - remove
     * @implements [public]         __CollectionRandomInsertionClient - Insertion without specified position Client - <strike>add</strike> / <strike>addAll</strike> / <strike>addAllOf</strike> / insert / insertAll / insertAllOf / emplace
     * @implements [public]         __CollectionRemoveOfCollectionClient - Remove Of Functions for Collection parameter Client - removeOf / removeFirstOf / removeLastOf / removeAllOf / removeNotOf / removeFirstNotOf / removeLastNotOf / removeAllNotOf
     * @implements [public]         __CollectionRemoveOfInitializerListClient - Remove Of Functions for std :: initializer_list parameter Client - removeOf / removeFirstOf / removeLastOf / removeAllOf / removeNotOf / removeFirstNotOf / removeLastNotOf / removeAllNotOf
     * @implements [public]         __CollectionGenericStatementsClient - Generic Functional Statements for Predicates - forEach / some / atLeast / atMost / moreThat / fewerThan / count / any / all / none
     *
     * @test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
     * @namespace cds
     * @public
     */
    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class Collection :                  /* NOLINT(*-virtual-class-destructor) */
            public Iterable < __ElementType >,
            public __hidden :: __impl :: __CollectionConstIteratorRemoveClient < __ElementType >,
            public __hidden :: __impl :: __CollectionRandomInsertionClient < __ElementType >,
            public __hidden :: __impl :: __CollectionRemoveOfCollectionClient < __ElementType >,
            public __hidden :: __impl :: __CollectionRemoveOfInitializerListClient < __ElementType >,
            public __hidden :: __impl :: __CollectionRemoveByClient < __ElementType > {

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef public alias for __ElementType, the type of the contained elements,
         * publicly accessible, useful in sfinae statements - decltype ( Collection ) :: ElementType
         * @public
         */
        using ElementType                           = __ElementType;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef protected alias for __CollectionConstIteratorRemoveClient base interface - providing remove for Abstract Iterators
         * @protected
         */
        using ConstIteratorRemoveClient             = __hidden :: __impl :: __CollectionConstIteratorRemoveClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef protected alias for __CollectionRandomInsertionClient base interface - providing insertion functions - <strike>add</strike> / <strike>addAll</strike> / <strike>addAllOf</strike> / insert / insertAll / insertAllOf / emplace
         * @protected
         */
        using RandomInsertionClient                 = __hidden :: __impl :: __CollectionRandomInsertionClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef protected alias for __CollectionRemoveOfCollectionClient base interface - providing remove-of functions with a Collection parameter - removeOf / removeFirstOf / removeLastOf / removeAllOf / removeNotOf / removeFirstNotOf / removeLastNotOf / removeAllNotOf
         * @protected
         */
        using RemoveOfCollectionClient              = __hidden :: __impl :: __CollectionRemoveOfCollectionClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef protected alias for __CollectionRemoveOfInitializerListClient base interface - providing remove-of functions with a std :: initializer_list parameter - removeOf / removeFirstOf / removeLastOf / removeAllOf / removeNotOf / removeFirstNotOf / removeLastNotOf / removeAllNotOf
         * @protected
         */
        using RemoveOfInitializerListClient         = __hidden :: __impl :: __CollectionRemoveOfInitializerListClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @typedef protected alias for __CollectionRemoveByClient base interface - providing remove-by-predicate functions - removeThat / removeFirstThat / removeLastThat / removeAllThat
         * @protected
         */
        using RemoveByClient                        = __hidden :: __impl :: __CollectionRemoveByClient < __ElementType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Default Constructor
         * @exceptsafe
         * @test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
         * @protected
         */
        constexpr Collection () noexcept;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
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

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Move Constructor
         * @param [in, out] collection : Collection mref = Move Reference to a collection to move data from
         * @exceptsafe
         * @test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
         * @protected
         */
        constexpr Collection (
                Collection && collection
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Destructor
         * @exceptsafe
         * @test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
         * @public
         */
        __CDS_cpplang_ConstexprDestructor ~Collection() noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Deleted Copy Assignment Operator
         * @param [in] collection : Collection cref = Constant Reference to a collection to copy data from
         * @exceptsafe
         * @return Collection ref = Reference to the modified object
         *
         * @test N/A
         * @public
         */
        auto operator = (
                Collection const &
        ) noexcept -> Collection & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Deleted Move Assignment Operator
         * @param [in, out] collection : Collection mref = Move Reference to a collection to move data from
         * @exceptsafe
         * @return Collection ref = Reference to the modified object
         *
         * @test N/A
         * @public
         */
        auto operator = (
                Collection &&
        ) noexcept -> Collection & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit add ( copy / move ) call, inherited from RandomInsertionClient interface
         * @deprecated 'Collection :: add' has been deprecated. Use 'Collection :: insert' instead
         * @test Not Applicable
         * @public
         */
        using RandomInsertionClient :: add;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit addAll ( pack ) call, inherited from RandomInsertionClient interface
         * @deprecated 'Collection :: addAll' has been deprecated. Use 'Collection :: insertAll' instead
         * @test Not Applicable
         * @public
         */
        using RandomInsertionClient :: addAll;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit addAllOf ( begin + end / iterable / initializer_list ) call, inherited from RandomInsertionClient interface
         * @deprecated 'Collection :: addAllOf' has been deprecated. Use 'Collection :: insertAllOf' instead
         * @test Not Applicable
         * @public
         */
        using RandomInsertionClient :: addAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit insert ( copy / move ) call, inherited from RandomInsertionClient interface
         * @test Suite: CTS-00001, Group: CTG-00800-RI, Test Cases: {
         *      CTC-00801-RI-insertByCopy,
         *      CTC-00802-RI-insertByMove
         * }
         * @public
         */
        using RandomInsertionClient :: insert;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit insertAll ( pack ) call, inherited from RandomInsertionClient interface
         * @test Suite: CTS-00001, Group: CTG-00800-RI, Test Cases: {
         *      CTC-00804-RI-insertByPack
         * }
         * @public
         */
        using RandomInsertionClient :: insertAll;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit insertAllOf ( begin + end / iterable / initializer_list ) call, inherited from RandomInsertionClient interface
         * @test Suite: CTS-00001, Group: CTG-00800-RI, Test Cases: {
         *      CTC-00805-RI-insertByInsertAllIterable,
         *      CTC-00806-RI-insertByInsertAllList,
         *      CTC-00807-RI-insertByRange1,
         *      CTC-00808-RI-insertByRange2,
         *      CTC-00809-RI-insertByRange3
         * }
         * @public
         */
        using RandomInsertionClient :: insertAllOf;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @inherit emplace ( forwarded arguments ) call, inherited from RandomInsertionClient interface
         * @test Suite: CTS-00001, Group: CTG-00800-RI, Test Cases: {
         *      CTC-00803-RI-insertByEmplace
         * }
         * @public
         */
        using RandomInsertionClient :: emplace;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to acquire the number of elements in the collection
         * @exceptsafe
         * @return Size = number of elements inside the collection
         * @test Suite: CTS-00001, Group: CTG-00002-MF, Test Cases: { CTC-00004-MF-size, CTC-00010-MF-clear }
         * @public
         */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto size () const noexcept -> Size = 0;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to check if the collection does not contain any elements ( is empty )
         * @exceptsafe
         * @return bool = true if the collection is empty ( does not contain any elements ), false otherwise
         * @test Suite: CTS-00001, Group: CTG-00002-MF, Test Cases: { CTC-00005-MF-empty, CTC-00010-MF-clear }
         * @public
         */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto empty () const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Bool cast operator, functionality equal to python's iterable empty check. '(bool) collection' is equivalent to '! collection.empty()'
         * @exceptsafe
         * @return bool = true if collection is not empty, false otherwise
         * @test Suite: CTS-00001, Group: CTG-00002-MF, Test Cases: { CTC-00006-MF-boolCast, CTC-00010-MF-clear }
         * @public
         */
        __CDS_cpplang_VirtualConstexpr __CDS_Explicit operator bool () const noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief String conversion function, used to obtain String representation of the Collection
         * @exceptsafe
         * @return String = string representation
         * @test Suite: CTS-00001, Group: CTG-00002-MF, Test Cases: { CTC-00003-MF-toString, CTC-00010-MF-clear }
         * @public
         */
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Hash function, used to obtain the hash value of the Collection
         * @exceptsafe
         * @return Index = hash code value of the instance
         * @test Suite: CTS-00001, Group: CTG-00002-MF, Test Cases: { CTC-00009-MF-hash, CTC-00010-MF-clear }
         * @public
         */
        __CDS_NoDiscard auto hash () const noexcept -> Size override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
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

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Function used to clear the collection, removing all elements from it
         * @exceptsafe
         * @test Suite: CTS-00001, Group: CTG-00002-MF, Test Cases: { CTC-00010-MF-clear }
         * @public
         */
        virtual auto clear () noexcept -> void = 0;

    };

} /* namespace cds */

#include "../shared/iterableInternalCommunication/client/primitive/impl/ConstIteratorRemovePrimitiveClient.hpp"
#include "../shared/iterableInternalCommunication/client/primitive/impl/RandomInsertionPrimitiveClient.hpp"

#include "../shared/iterableInternalCommunication/client/composite/impl/RemoveOfCompositeClient.hpp"            /* NOLINT(llvm-include-order) */
#include "../shared/iterableInternalCommunication/client/composite/impl/RemoveByCompositeClient.hpp"

#include "collection/impl/Collection.hpp"

#endif /* __CDS_COLLECTION_HPP__ */
