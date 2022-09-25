/*
 * Created by loghin on 6/28/22.
 */

#ifndef __CDS_SHARED_BOUNDARY_INSERTION_PRIMITIVE_CLIENT_HPP__
#define __CDS_SHARED_BOUNDARY_INSERTION_PRIMITIVE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                /**
                 * @interface Interface for creating Boundary Insertion requests, inserting / emplacing elements at the back or front of the list
                 * @tparam __ReceiverType is the type of implementor class, used for static polymorphism.
                 * Implementor is required to either be derived from the List abstract class or a class
                 * extending the __CollectionInternalCommunicationChannel class, or provide equivalent member
                 * function implementations provided by the __collectionInternalCommunicationChannel class
                 * Note : This Client will request the member functions identified with:
                 *      - __cirt_newFrontAddress
                 *      - __cirt_newBackAddress
                 *      - __cirt_newFrontAddressArray
                 *      - __cirt_newBackAddressArray
                 *
                 * @tparam __ElementType is the type of elements contained into the Object
                 * @tparam __ReturnType is the type returned by the singular insertion functions
                 *
                 * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: All
                 *
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __ReceiverType,                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                 /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType                   /* NOLINT(bugprone-reserved-identifier) */
                > class __BoundaryInsertionPrimitiveClient {    /* NOLINT(bugprone-reserved-identifier) */

                private:
                    /**
                     * @typedef alias for __ElementType template parameter
                     * @private
                     */
                    using ElementType       = __ElementType;

                private:
                    /**
                     * @typedef alias for __ReturnType template parameter reference
                     * @private
                     */
                    using ElementReference  = __ReturnType &;

                public:
                    /**
                     * @brief Function used to create a new element at the front of the iterable by copy
                     * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a copy constructor
                     * @param [in] element : ElementType cref = Constant Reference to the element to be inserted via copy
                     * @exceptsafe if ElementType's Copy Constructor is exceptsafe
                     * @return ElementReference = Reference to the newly inserted element
                     *
                     * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
                     *      LTC-00306-IT-pushFrontCopy1,
                     *      LTC-00307-IT-pushFrontCopy2,
                     *      LTC-00308-IT-pushFrontCopy3
                     * }
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto pushFront (
                            ElementType const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> ElementReference;

                public:
                    /**
                     * @brief Function used to create a new element at the front of the iterable by move
                     * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a move constructor
                     * @param [in, out] element : ElementType mref = Move Reference to the element to be inserted via move
                     * @exceptsafe if ElementType's Move Constructor is exceptsafe
                     * @return ElementReference = Reference to the newly inserted element
                     *
                     * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
                     *      LTC-00306-IT-pushFrontMove1,
                     *      LTC-00307-IT-pushFrontMove2
                     * }
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto pushFront (
                            ElementType && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> ElementReference;

                public:
                    /**
                     * @brief Function used to create a new element at the back of the iterable by copy
                     * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a copy constructor
                     * @param [in] element : ElementType cref = Constant Reference to the element to be inserted via copy
                     * @exceptsafe if ElementType's Copy Constructor is exceptsafe
                     * @return ElementReference = Reference to the newly inserted element
                     *
                     * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
                     *      LTC-00301-IT-pushBackCopy1,
                     *      LTC-00302-IT-pushBackCopy2,
                     *      LTC-00303-IT-pushBackCopy3
                     * }
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto pushBack (
                            ElementType const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> ElementReference;

                public:
                    /**
                     * @brief Function used to create a new element at the back of the iterable by move
                     * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a move constructor
                     * @param [in, out] element : ElementType mref = Move Reference to the element to be inserted via move
                     * @exceptsafe if ElementType's Move Constructor is exceptsafe
                     * @return ElementReference = Reference to the newly inserted element
                     *
                     * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
                     *      LTC-00304-IT-pushBackMove1,
                     *      LTC-00305-IT-pushBackMove2
                     * }
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto pushBack (
                            ElementType && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> ElementReference;

                public:
                    /**
                     * @deprecated 'prepend' function deprecated, kept for support. Replaced by 'pushFront', same functionality
                     * @brief Function used to create a new element at the front of the iterable by copy
                     * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a copy constructor
                     * @param [in] element : ElementType cref = Constant Reference to the element to be inserted via copy
                     * @exceptsafe if ElementType's Copy Constructor is exceptsafe
                     * @return ElementReference = Reference to the newly inserted element
                     *
                     * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
                     *      LTC-00306-IT-pushFrontCopy1,
                     *      LTC-00307-IT-pushFrontCopy2,
                     *      LTC-00308-IT-pushFrontCopy3
                     * }
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > __CDS_DeprecatedHint ("'List :: prepend' has been deprecated. Use 'List :: pushFront' instead") auto prepend (
                            ElementType const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> ElementReference;

                public:
                    /**
                     * @deprecated 'prepend' function deprecated, kept for support. Replaced by 'pushFront', same functionality
                     * @brief Function used to create a new element at the front of the iterable by move
                     * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a move constructor
                     * @param [in, out] element : ElementType mref = Move Reference to the element to be inserted via move
                     * @exceptsafe if ElementType's Move Constructor is exceptsafe
                     * @return ElementReference = Reference to the newly inserted element
                     *
                     * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
                     *      LTC-00306-IT-pushFrontMove1,
                     *      LTC-00307-IT-pushFrontMove2
                     * }
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > __CDS_DeprecatedHint ("'List :: prepend' has been deprecated. Use 'List :: pushFront' instead") auto prepend (
                            ElementType && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> ElementReference;

                public:
                    /**
                     * @deprecated 'append' function deprecated, kept for support. Replaced by 'pushBack', same functionality
                     * @brief Function used to create a new element at the back of the iterable by copy
                     * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a copy constructor
                     * @param [in] element : ElementType cref = Constant Reference to the element to be inserted via copy
                     * @exceptsafe if ElementType's Copy Constructor is exceptsafe
                     * @return ElementReference = Reference to the newly inserted element
                     *
                     * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
                     *      LTC-00301-IT-pushBackCopy1,
                     *      LTC-00302-IT-pushBackCopy2,
                     *      LTC-00303-IT-pushBackCopy3
                     * }
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > __CDS_DeprecatedHint ("'List :: append' has been deprecated. Use 'List :: pushBack' instead") auto append (
                            ElementType const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> ElementReference;

                public:
                    /**
                     * @deprecated 'append' function deprecated, kept for support. Replaced by 'pushBack', same functionality
                     * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a move constructor
                     * @param [in, out] element : ElementType mref = Move Reference to the element to be inserted via move
                     * @exceptsafe if ElementType's Move Constructor is exceptsafe
                     * @return ElementReference = Reference to the newly inserted element
                     *
                     * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
                     *      LTC-00304-IT-pushBackMove1,
                     *      LTC-00305-IT-pushBackMove2
                     * }
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > __CDS_DeprecatedHint ("'List :: append' has been deprecated. Use 'List :: pushBack' instead") auto append (
                            ElementType && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> ElementReference;

                public:
                    /**
                     * @brief Function used to create a request to emplace an element ( construct with given parameters ) at the front of the iterable
                     * @tparam __EmplaceArgumentTypes is the type pack of the construction argument types
                     * @param [in] parameters : __EmplaceArgumentTypes fref ... = Pack of forwarding references to given parameters for element emplace construction
                     * @exceptsafe if ElementType is exceptsafe constructible with given parameters
                     * @return ElementReference = Reference to an element, new or non-replaceable, const or not, depending on use-case.
                     *
                     * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
                     *      LTC-00323-IT-emplaceFront
                     * }
                     *
                     * @public
                     */
                    template < typename ... __EmplaceArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto emplaceFront (
                            __EmplaceArgumentTypes && ... parameters
                    ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> ElementReference;

                public:
                    /**
                     * @brief Function used to create a request to emplace an element ( construct with given parameters ) at the back of the iterable
                     * @tparam __EmplaceArgumentTypes is the type pack of the construction argument types
                     * @param [in] parameters : __EmplaceArgumentTypes fref ... = Pack of forwarding references to given parameters for element emplace construction
                     * @exceptsafe if ElementType is exceptsafe constructible with given parameters
                     * @return ElementReference = Reference to an element, new or non-replaceable, const or not, depending on use-case.
                     *
                     * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
                     *      LTC-00324-IT-emplaceBack
                     * }
                     *
                     * @public
                     */
                    template < typename ... __EmplaceArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto emplaceBack (
                            __EmplaceArgumentTypes && ... parameters
                    ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> ElementReference;

                public:
                    /**
                     * @brief Function used to insert multiple elements at the front of the iterable by creating a new front array request
                     * @tparam __ArgumentTypes is the type pack of the values to be inserted
                     * @param [in] values : __ArgumentTypes fref ... = Pack of forwarding elements to values, each of the pack to be transformed into an Element via construction and inserted
                     * @exceptsafe if ElementType is exceptsafe constructible with each given value
                     *
                     * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
                     *      LTC-00312-IT-pushFrontValues
                     * }
                     *
                     * @public
                     */
                    template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto pushFrontAll (
                            __ArgumentTypes && ... values
                    ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> void;

                public:
                    /**
                     * @brief Function used to insert multiple elements at the back of the iterable by creating a new back array request
                     * @tparam __ArgumentTypes is the type pack of the values to be inserted
                     * @param [in] values : __ArgumentTypes fref ... = Pack of forwarding elements to values, each of the pack to be transformed into an Element via construction and inserted
                     * @exceptsafe if ElementType is exceptsafe constructible with each given value
                     *
                     * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
                     *      LTC-00311-IT-pushBackValues
                     * }
                     *
                     * @public
                     */
                    template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto pushBackAll (
                            __ArgumentTypes && ... values
                    ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> void;

                public:
                    /**
                     * @brief Function used to insert multiple elements at the front of the iterable. This function varies whenever a RandomAccessIterator is given, to be able to efficiently determine
                     * the element count to insert. Otherwise, the distance will be computed iteratively. Insertion is done by extracting
                     * each from a given iterable and inserting each into the received addresses from the add front array request.
                     * @tparam __IterableType is the type of iterable given as parameter
                     * @param [in] iterable : __IterableType cref = Constant Reference to the iterable to extract the values from
                     * @exceptsafe if ElementType is exceptsafe constructible
                     *
                     * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
                     *      LTC-00314-IT-pushFrontAllOfColl
                     * }
                     *
                     * @public
                     */
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto pushFrontAllOf (
                            __IterableType const & iterable
                    ) noexcept ( noexcept ( __ElementType ( * iterable.begin() ) ) ) -> void;

                public:
                    /**
                     * @brief Function used to insert multiple elements at the front of the iterable. This function varies whenever a RandomAccessIterator is given, to be able to efficiently determine
                     * the element count to insert. Otherwise, the distance will be computed iteratively. Insertion is done by extracting
                     * each from a given iterable and inserting each into the received addresses from the add front array request.
                     * @tparam __IterableType is the type of iterable given as parameter
                     * @param [in] iterable : __IterableType cref = Constant Reference to the iterable to extract the values from
                     * @exceptsafe if ElementType is exceptsafe constructible
                     *
                     * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
                     *      LTC-00314-IT-pushFrontAllOfColl
                     * }
                     *
                     * @public
                     */
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    ! meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto pushFrontAllOf (
                            __IterableType const & iterable
                    ) noexcept ( noexcept ( __ElementType ( * iterable.begin() ) ) ) -> void;

                public:
                    /**
                     * @brief Function used to insert multiple elements at the front of the iterable, done by extracting
                     * each from a given initializer list and inserting each into the received addresses from the add front array request.
                     * @tparam __IterableType is the type of iterable given as parameter
                     * @param [in] list : std :: initializer_list cref = Constant Reference to an initializer list to extract the values from
                     * @exceptsafe if ElementType is exceptsafe constructible
                     *
                     * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
                     *      LTC-00314-IT-pushFrontAllOfInitList
                     * }
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto pushFrontAllOf (
                            std :: initializer_list < __ElementType > const & list
                    ) noexcept ( noexcept ( __ElementType ( * list.begin() ) ) ) -> void;

                public:
                    /**
                     * @brief Function used to insert multiple elements at the back of the iterable. This function varies whenever a RandomAccessIterator is given, to be able to efficiently determine
                     * the element count to insert. Otherwise, the distance will be computed iteratively. Insertion is done by extracting
                     * each from a given iterable and inserting each into the received addresses from the add back array request.
                     * @tparam __IterableType is the type of iterable given as parameter
                     * @param [in] iterable : __IterableType cref = Constant Reference to the iterable to extract the values from
                     * @exceptsafe if ElementType is exceptsafe constructible
                     *
                     * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
                     *      LTC-00312-IT-pushBackAllOfColl
                     * }
                     *
                     * @public
                     */
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto pushBackAllOf (
                            __IterableType const & iterable
                    ) noexcept ( noexcept ( __ElementType ( * iterable.begin() ) ) ) -> void;

                public:
                    /**
                     * @brief Function used to insert multiple elements at the back of the iterable. This function varies whenever a RandomAccessIterator is given, to be able to efficiently determine
                     * the element count to insert. Otherwise, the distance will be computed iteratively. Insertion is done by extracting
                     * each from a given iterable and inserting each into the received addresses from the add back array request.
                     * @tparam __IterableType is the type of iterable given as parameter
                     * @param [in] iterable : __IterableType cref = Constant Reference to the iterable to extract the values from
                     * @exceptsafe if ElementType is exceptsafe constructible
                     *
                     * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
                     *      LTC-00312-IT-pushBackAllOfColl
                     * }
                     *
                     * @public
                     */
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    ! meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto pushBackAllOf (
                            __IterableType const & iterable
                    ) noexcept ( noexcept ( __ElementType ( * iterable.begin() ) ) ) -> void;

                public:
                    /**
                     * @brief Function used to insert multiple elements at the back of the iterable, done by extracting
                     * each from a given initializer list and inserting each into the received addresses from the add back array request.
                     * @tparam __IterableType is the type of iterable given as parameter
                     * @param [in] list : std :: initializer_list cref = Constant Reference to an initializer list to extract the values from
                     * @exceptsafe if ElementType is exceptsafe constructible
                     *
                     * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
                     *      LTC-00311-IT-pushBackAllOfInitList
                     * }
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto pushBackAllOf (
                            std :: initializer_list < __ElementType > const & list
                    ) noexcept ( noexcept ( __ElementType ( * list.begin() ) ) ) -> void;

                public:
                    /**
                     * @brief Function used to insert multiple elements at the front of the iterable
                     * by extracting each from a given iterator range and inserting each into the addresses received
                     * from the new front array request.
                     * An extra parameter is available to set the number of values between the given iterators,
                     * either as a limit, or as to avoid the computation of the distance between the two iterators.
                     * @tparam __IteratorType is the type of given iterators
                     * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
                     * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
                     * @param [in] count : Size = Distance between begin and end iterators. If 0, distance will be computed
                     * by subtraction, if iterator type is random, or by iteration otherwise
                     * @exceptsafe if ElementType is exceptsafe constructible
                     *
                     * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
                     *      LTC-00316-IT-pushFrontItRange1,
                     *      LTC-00318-IT-pushFrontItRange2,
                     *      LTC-00320-IT-pushFrontItRange3
                     * }
                     *
                     * @public
                     */
                    template < typename __IteratorType > /* NOLINT(bugprone-reserved-identifier) */
                    auto pushFrontAllOf (
                            __IteratorType const & begin,
                            __IteratorType const & end,
                            Size                   count = 0ULL
                    ) noexcept ( noexcept ( __ElementType ( * begin ) ) ) -> void;

                public:
                    /**
                     * @brief Function used to insert multiple elements at the back of the iterable
                     * by extracting each from a given iterator range and inserting each into the addresses received
                     * from the new back array request.
                     * An extra parameter is available to set the number of values between the given iterators,
                     * either as a limit, or as to avoid the computation of the distance between the two iterators.
                     * @tparam __IteratorType is the type of given iterators
                     * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
                     * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
                     * @param [in] count : Size = Distance between begin and end iterators. If 0, distance will be computed
                     * by subtraction, if iterator type is random, or by iteration otherwise
                     * @exceptsafe if ElementType is exceptsafe constructible
                     *
                     * @test Suite: LTS-00001, Group: LTG-00300-BI, Test Cases: {
                     *      LTC-00315-IT-pushBackItRange1,
                     *      LTC-00317-IT-pushBackItRange2,
                     *      LTC-00319-IT-pushBackItRange3
                     * }
                     *
                     * @public
                     */
                    template < typename __IteratorType > /* NOLINT(bugprone-reserved-identifier) */
                    auto pushBackAllOf (
                            __IteratorType const & begin,
                            __IteratorType const & end,
                            Size                   count = 0ULL
                    ) noexcept ( noexcept ( __ElementType ( * begin ) ) ) -> void;
                };


                /**
                 * @interface Interface for creating Local Boundary Insertion requests, inserting / emplacing elements at the back or front of the iterable list
                 * @tparam __ReceiverType is the type of implementor class, used for static polymorphism.
                 * Implementor is required to either implement an appropriate dispatcher ( __ListServerDispatcher or lower
                 * in hierarchy ) or provide an equivalent set of member functions - __newFrontAddress, __newBackAddress,
                 *      __newFrontAddressArray, __newBackAddressArray - to the one provided by the dispatcher
                 *
                 * @tparam __ElementType is the type of elements contained into the Object
                 * @tparam __ReturnType is the type returned by the singular insertion functions
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __ReceiverType,                    /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                     /* NOLINT(bugprone-reserved-identifier) */
                        typename __ReturnType                       /* NOLINT(bugprone-reserved-identifier) */
                > class __LocalBoundaryInsertionPrimitiveClient {   /* NOLINT(bugprone-reserved-identifier) */

                private:
                    /**
                     * @typedef alias for __ElementType template parameter
                     * @private
                     */
                    using ElementType       = __ElementType;

                private:
                    /**
                     * @typedef alias for __ReturnType template parameter reference
                     * @private
                     */
                    using ElementReference  = __ReturnType &;

                public:
                    /**
                     * @brief Function used to create a new element at the front of the iterable by copy
                     * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a copy constructor
                     * @param [in] element : ElementType cref = Constant Reference to the element to be inserted via copy
                     * @exceptsafe if ElementType's Copy Constructor is exceptsafe
                     * @return ElementReference = Reference to the newly inserted element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto pushFront (
                            ElementType const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> ElementReference;

                public:
                    /**
                     * @brief Function used to create a new element at the front of the iterable by move
                     * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a move constructor
                     * @param [in, out] element : ElementType mref = Move Reference to the element to be inserted via move
                     * @exceptsafe if ElementType's Move Constructor is exceptsafe
                     * @return ElementReference = Reference to the newly inserted element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto pushFront (
                            ElementType && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> ElementReference;

                public:
                    /**
                     * @brief Function used to create a new element at the back of the iterable by copy
                     * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a copy constructor
                     * @param [in] element : ElementType cref = Constant Reference to the element to be inserted via copy
                     * @exceptsafe if ElementType's Copy Constructor is exceptsafe
                     * @return ElementReference = Reference to the newly inserted element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto pushBack (
                            ElementType const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> ElementReference;

                public:
                    /**
                     * @brief Function used to create a new element at the back of the iterable by move
                     * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a move constructor
                     * @param [in, out] element : ElementType mref = Move Reference to the element to be inserted via move
                     * @exceptsafe if ElementType's Move Constructor is exceptsafe
                     * @return ElementReference = Reference to the newly inserted element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto pushBack (
                            ElementType && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> ElementReference;

                public:
                    /**
                     * @deprecated 'prepend' function deprecated, kept for support. Replaced by 'pushFront', same functionality
                     * @brief Function used to create a new element at the front of the iterable by copy
                     * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a copy constructor
                     * @param [in] element : ElementType cref = Constant Reference to the element to be inserted via copy
                     * @exceptsafe if ElementType's Copy Constructor is exceptsafe
                     * @return ElementReference = Reference to the newly inserted element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > __CDS_DeprecatedHint ("'List :: prepend' has been deprecated. Use 'List :: pushFront' instead") auto prepend (
                            ElementType const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> ElementReference;

                public:
                    /**
                     * @deprecated 'prepend' function deprecated, kept for support. Replaced by 'pushFront', same functionality
                     * @brief Function used to create a new element at the front of the iterable by move
                     * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a move constructor
                     * @param [in, out] element : ElementType mref = Move Reference to the element to be inserted via move
                     * @exceptsafe if ElementType's Move Constructor is exceptsafe
                     * @return ElementReference = Reference to the newly inserted element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > __CDS_DeprecatedHint ("'List :: prepend' has been deprecated. Use 'List :: pushFront' instead") auto prepend (
                            ElementType && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> ElementReference;

                public:
                    /**
                     * @deprecated 'append' function deprecated, kept for support. Replaced by 'pushBack', same functionality
                     * @brief Function used to create a new element at the back of the iterable by copy
                     * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a copy constructor
                     * @param [in] element : ElementType cref = Constant Reference to the element to be inserted via copy
                     * @exceptsafe if ElementType's Copy Constructor is exceptsafe
                     * @return ElementReference = Reference to the newly inserted element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > __CDS_DeprecatedHint ("'List :: append' has been deprecated. Use 'List :: pushBack' instead") auto append (
                            ElementType const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> ElementReference;

                public:
                    /**
                     * @deprecated 'append' function deprecated, kept for support. Replaced by 'pushBack', same functionality
                     * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a move constructor
                     * @param [in, out] element : ElementType mref = Move Reference to the element to be inserted via move
                     * @exceptsafe if ElementType's Move Constructor is exceptsafe
                     * @return ElementReference = Reference to the newly inserted element
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > __CDS_DeprecatedHint ("'List :: append' has been deprecated. Use 'List :: pushBack' instead") auto append (
                            ElementType && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> ElementReference;

                public:
                    /**
                     * @brief Function used to create a request to emplace an element ( construct with given parameters ) at the front of the iterable
                     * @tparam __EmplaceArgumentTypes is the type pack of the construction argument types
                     * @param [in] parameters : __EmplaceArgumentTypes fref ... = Pack of forwarding references to given parameters for element emplace construction
                     * @exceptsafe if ElementType is exceptsafe constructible with given parameters
                     * @return ElementReference = Reference to an element, new or non-replaceable, const or not, depending on use-case.
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    template < typename ... __EmplaceArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto emplaceFront (
                            __EmplaceArgumentTypes && ... parameters
                    ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> ElementReference;

                public:
                    /**
                     * @brief Function used to create a request to emplace an element ( construct with given parameters ) at the back of the iterable
                     * @tparam __EmplaceArgumentTypes is the type pack of the construction argument types
                     * @param [in] parameters : __EmplaceArgumentTypes fref ... = Pack of forwarding references to given parameters for element emplace construction
                     * @exceptsafe if ElementType is exceptsafe constructible with given parameters
                     * @return ElementReference = Reference to an element, new or non-replaceable, const or not, depending on use-case.
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    template < typename ... __EmplaceArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto emplaceBack (
                            __EmplaceArgumentTypes && ... parameters
                    ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> ElementReference;

                public:
                    /**
                     * @brief Function used to insert multiple elements at the front of the iterable by creating a new front array request
                     * @tparam __ArgumentTypes is the type pack of the values to be inserted
                     * @param [in] values : __ArgumentTypes fref ... = Pack of forwarding elements to values, each of the pack to be transformed into an Element via construction and inserted
                     * @exceptsafe if ElementType is exceptsafe constructible with each of the given parameter types
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto pushFrontAll (
                            __ArgumentTypes && ... values
                    ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> void;

                public:
                    /**
                     * @brief Function used to insert multiple elements at the back of the iterable by creating a new back array request
                     * @tparam __ArgumentTypes is the type pack of the values to be inserted
                     * @param [in] values : __ArgumentTypes fref ... = Pack of forwarding elements to values, each of the pack to be transformed into an Element via construction and inserted
                     * @exceptsafe if ElementType is exceptsafe constructible with each of the given parameter types
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto pushBackAll (
                            __ArgumentTypes && ... values
                    ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> void;

                public:
                    /**
                     * @brief Function used to insert multiple elements at the front of the iterable. This function varies whenever a RandomAccessIterator is given, to be able to efficiently determine
                     * the element count to insert. Otherwise, the distance will be computed iteratively. Insertion is done by extracting
                     * each from a given iterable and inserting each into the received addresses from the add front array request.
                     * @tparam __IterableType is the type of iterable given as parameter
                     * @param [in] iterable : __IterableType cref = Constant Reference to the iterable to extract the values from
                     * @exceptsafe if ElementType is exceptsafe constructible
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto pushFrontAllOf (
                            __IterableType const & iterable
                    ) noexcept ( noexcept ( __ElementType ( * iterable.begin() ) ) ) -> void;

                public:
                    /**
                     * @brief Function used to insert multiple elements at the front of the iterable. This function varies whenever a RandomAccessIterator is given, to be able to efficiently determine
                     * the element count to insert. Otherwise, the distance will be computed iteratively. Insertion is done by extracting
                     * each from a given iterable and inserting each into the received addresses from the add front array request.
                     * @tparam __IterableType is the type of iterable given as parameter
                     * @param [in] iterable : __IterableType cref = Constant Reference to the iterable to extract the values from
                     * @exceptsafe if ElementType is exceptsafe constructible
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    ! meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto pushFrontAllOf (
                            __IterableType const & iterable
                    ) noexcept ( noexcept ( __ElementType ( * iterable.begin() ) ) ) -> void;

                public:
                    /**
                     * @brief Function used to insert multiple elements at the front of the iterable, done by extracting
                     * each from a given initializer list and inserting each into the received addresses from the add front array request.
                     * @tparam __IterableType is the type of iterable given as parameter
                     * @param [in] list : std :: initializer_list cref = Constant Reference to an initializer list to extract the values from
                     * @exceptsafe if ElementType is exceptsafe constructible
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto pushFrontAllOf (
                            std :: initializer_list < __ElementType > const & list
                    ) noexcept ( noexcept ( __ElementType ( * list.begin() ) ) ) -> void;

                public:
                    /**
                     * @brief Function used to insert multiple elements at the back of the iterable. This function varies whenever a RandomAccessIterator is given, to be able to efficiently determine
                     * the element count to insert. Otherwise, the distance will be computed iteratively. Insertion is done by extracting
                     * each from a given iterable and inserting each into the received addresses from the add back array request.
                     * @tparam __IterableType is the type of iterable given as parameter
                     * @param [in] iterable : __IterableType cref = Constant Reference to the iterable to extract the values from
                     * @exceptsafe if ElementType is exceptsafe constructible
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto pushBackAllOf (
                            __IterableType const & iterable
                    ) noexcept ( noexcept ( __ElementType ( * iterable.begin() ) ) ) -> void;

                public:
                    /**
                     * @brief Function used to insert multiple elements at the back of the iterable. This function varies whenever a RandomAccessIterator is given, to be able to efficiently determine
                     * the element count to insert. Otherwise, the distance will be computed iteratively. Insertion is done by extracting
                     * each from a given iterable and inserting each into the received addresses from the add back array request.
                     * @tparam __IterableType is the type of iterable given as parameter
                     * @param [in] iterable : __IterableType cref = Constant Reference to the iterable to extract the values from
                     * @exceptsafe if ElementType is exceptsafe constructible
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    ! meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto pushBackAllOf (
                            __IterableType const & iterable
                    ) noexcept ( noexcept ( __ElementType ( * iterable.begin() ) ) ) -> void;

                public:
                    /**
                     * @brief Function used to insert multiple elements at the back of the iterable, done by extracting
                     * each from a given initializer list and inserting each into the received addresses from the add back array request.
                     * @tparam __IterableType is the type of iterable given as parameter
                     * @param [in] list : std :: initializer_list cref = Constant Reference to an initializer list to extract the values from
                     * @exceptsafe if ElementType is exceptsafe constructible
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto pushBackAllOf (
                            std :: initializer_list < __ElementType > const & list
                    ) noexcept ( noexcept ( __ElementType ( * list.begin() ) ) ) -> void;

                public:
                    /**
                     * @brief Function used to insert multiple elements at the front of the iterable
                     * by extracting each from a given iterator range and inserting each into the addresses received
                     * from the new front array request.
                     * An extra parameter is available to set the number of values between the given iterators,
                     * either as a limit, or as to avoid the computation of the distance between the two iterators.
                     * @tparam __IteratorType is the type of given iterators
                     * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
                     * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
                     * @param [in] count : Size = Distance between begin and end iterators. If 0, distance will be computed
                     * by subtraction, if iterator type is random, or by iteration otherwise
                     * @exceptsafe if ElementType is exceptsafe constructible
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    template < typename __IteratorType > /* NOLINT(bugprone-reserved-identifier) */
                    auto pushFrontAllOf (
                            __IteratorType const & begin,
                            __IteratorType const & end,
                            Size                   count = 0ULL
                    ) noexcept ( noexcept ( __ElementType ( * begin ) ) ) -> void;

                public:
                    /**
                     * @brief Function used to insert multiple elements at the back of the iterable
                     * by extracting each from a given iterator range and inserting each into the addresses received
                     * from the new back array request.
                     * An extra parameter is available to set the number of values between the given iterators,
                     * either as a limit, or as to avoid the computation of the distance between the two iterators.
                     * @tparam __IteratorType is the type of given iterators
                     * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
                     * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
                     * @param [in] count : Size = Distance between begin and end iterators. If 0, distance will be computed
                     * by subtraction, if iterator type is random, or by iteration otherwise
                     * @exceptsafe if ElementType is exceptsafe constructible
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    template < typename __IteratorType > /* NOLINT(bugprone-reserved-identifier) */
                    auto pushBackAllOf (
                            __IteratorType const & begin,
                            __IteratorType const & end,
                            Size                   count = 0ULL
                    ) noexcept ( noexcept ( __ElementType ( * begin ) ) ) -> void;
                };

            }
        }
    }
}

#endif /* __CDS_SHARED_BOUNDARY_INSERTION_PRIMITIVE_CLIENT_HPP__ */
