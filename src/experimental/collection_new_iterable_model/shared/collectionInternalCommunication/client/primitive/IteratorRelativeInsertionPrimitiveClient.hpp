/*
 * Created by loghin on 6/28/22.
 */

#ifndef __CDS_SHARED_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_HPP__
#define __CDS_SHARED_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                /**
                 * @interface Interface for creating Iterator-Relative-To Insertion requests, inserting / emplacing elements before or after a given iterator
                 * @tparam __ReceiverType is the type of implementor class, used for static polymorphism.
                 * Implementor is required to either be derived from the List abstract class or a class
                 * extending the __CollectionInternalCommunicationChannel class, or provide equivalent member
                 * function implementations provided by the __collectionInternalCommunicationChannel class
                 * Note : This Client will request the member functions identified with:
                 *      - __cirt_newBeforeAddress
                 *      - __cirt_newBeforeAddressArray
                 *      - __cirt_newAfterAddress
                 *      - __cirt_newAfterAddressArray
                 *
                 * @tparam __ElementType is the type of elements contained into the Object
                 * @tparam __ReturnType is the type returned by the singular insertion functions
                 *
                 * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: All
                 *
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __ReceiverType,                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType                                  /* NOLINT(bugprone-reserved-identifier) */
                > class __AbstractIteratorRelativeInsertionPrimitiveClient {    /* NOLINT(bugprone-reserved-identifier) */

                private:
                    /**
                     * @typedef alias for __ElementType template parameter
                     * @private
                     */
                    using ElementType       = __ElementType;

                private:
                    /**
                     * @typedef alias for Abstract Iterator type
                     * @private
                     */
                    using AbstractIterator  =
                            __AbstractDelegateWrapperIterator < __ElementType >;

                public:
                    /**
                     * @brief Function used to create a new element before a given iterator by copy
                     * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a copy constructor
                     * @param [in] iterator : AbstractIterator cref = Constant Reference to the iterator to insert before
                     * @param [in] element : ElementType cref = Constant Reference to the element to be inserted via copy
                     * @exceptsafe if ElementType's Copy Constructor is exceptsafe
                     * @return bool = true if insertion was successful, false otherwise
                     *
                     * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                     *      LTC-00401-IT-insertBeforeItCase1SingleValue1OffsetCase1,
                     *      LTC-00402-IT-insertBeforeItCase1SingleValue1OffsetCase2,
                     *      LTC-00403-IT-insertBeforeItCase1SingleValue1OffsetCase3,
                     *      LTC-00404-IT-insertBeforeItCase1SingleValue1OffsetCase4,
                     *      LTC-00405-IT-insertBeforeItCase1SingleValue2OffsetCase1,
                     *      LTC-00406-IT-insertBeforeItCase1SingleValue2OffsetCase2,
                     *      LTC-00407-IT-insertBeforeItCase1SingleValue2OffsetCase3,
                     *      LTC-00408-IT-insertBeforeItCase1SingleValue2OffsetCase4,
                     *      LTC-00409-IT-insertBeforeItCase1SingleValue3OffsetCase1,
                     *      LTC-00410-IT-insertBeforeItCase1SingleValue3OffsetCase2,
                     *      LTC-00411-IT-insertBeforeItCase1SingleValue3OffsetCase3,
                     *      LTC-00412-IT-insertBeforeItCase1SingleValue3OffsetCase4,
                     *      LTC-00413-IT-insertBeforeItCase3SingleValue1OffsetCase1,
                     *      LTC-00414-IT-insertBeforeItCase3SingleValue1OffsetCase2,
                     *      LTC-00415-IT-insertBeforeItCase3SingleValue1OffsetCase3,
                     *      LTC-00416-IT-insertBeforeItCase3SingleValue1OffsetCase4,
                     *      LTC-00417-IT-insertBeforeItCase3SingleValue2OffsetCase1,
                     *      LTC-00418-IT-insertBeforeItCase3SingleValue2OffsetCase2,
                     *      LTC-00419-IT-insertBeforeItCase3SingleValue2OffsetCase3,
                     *      LTC-00420-IT-insertBeforeItCase3SingleValue2OffsetCase4,
                     *      LTC-00421-IT-insertBeforeItCase3SingleValue3OffsetCase1,
                     *      LTC-00422-IT-insertBeforeItCase3SingleValue3OffsetCase2,
                     *      LTC-00423-IT-insertBeforeItCase3SingleValue3OffsetCase3,
                     *      LTC-00424-IT-insertBeforeItCase3SingleValue3OffsetCase4
                     * }
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertBefore (
                            AbstractIterator    const & iterator,
                            ElementType         const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to create a new element before a given iterator by move
                     * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a move constructor
                     * @param [in] iterator : AbstractIterator cref = Constant Reference to the iterator to insert before
                     * @param [in, out] element : ElementType mref = Move Reference to the element to be inserted via move
                     * @exceptsafe if ElementType's Move Constructor is exceptsafe
                     * @return bool = true if insertion was successful, false otherwise
                     *
                     * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                     *      LTC-00401-IT-insertBeforeItCase1SingleValue1OffsetCase1,
                     *      LTC-00402-IT-insertBeforeItCase1SingleValue1OffsetCase2,
                     *      LTC-00403-IT-insertBeforeItCase1SingleValue1OffsetCase3,
                     *      LTC-00404-IT-insertBeforeItCase1SingleValue1OffsetCase4,
                     *      LTC-00405-IT-insertBeforeItCase1SingleValue2OffsetCase1,
                     *      LTC-00406-IT-insertBeforeItCase1SingleValue2OffsetCase2,
                     *      LTC-00407-IT-insertBeforeItCase1SingleValue2OffsetCase3,
                     *      LTC-00408-IT-insertBeforeItCase1SingleValue2OffsetCase4,
                     *      LTC-00409-IT-insertBeforeItCase1SingleValue3OffsetCase1,
                     *      LTC-00410-IT-insertBeforeItCase1SingleValue3OffsetCase2,
                     *      LTC-00411-IT-insertBeforeItCase1SingleValue3OffsetCase3,
                     *      LTC-00412-IT-insertBeforeItCase1SingleValue3OffsetCase4,
                     *      LTC-00413-IT-insertBeforeItCase3SingleValue1OffsetCase1,
                     *      LTC-00414-IT-insertBeforeItCase3SingleValue1OffsetCase2,
                     *      LTC-00415-IT-insertBeforeItCase3SingleValue1OffsetCase3,
                     *      LTC-00416-IT-insertBeforeItCase3SingleValue1OffsetCase4,
                     *      LTC-00417-IT-insertBeforeItCase3SingleValue2OffsetCase1,
                     *      LTC-00418-IT-insertBeforeItCase3SingleValue2OffsetCase2,
                     *      LTC-00419-IT-insertBeforeItCase3SingleValue2OffsetCase3,
                     *      LTC-00420-IT-insertBeforeItCase3SingleValue2OffsetCase4,
                     *      LTC-00421-IT-insertBeforeItCase3SingleValue3OffsetCase1,
                     *      LTC-00422-IT-insertBeforeItCase3SingleValue3OffsetCase2,
                     *      LTC-00423-IT-insertBeforeItCase3SingleValue3OffsetCase3,
                     *      LTC-00424-IT-insertBeforeItCase3SingleValue3OffsetCase4
                     * }
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto insertBefore (
                            AbstractIterator    const & iterator,
                            ElementType              && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to create a new element after a given iterator by copy
                     * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a copy constructor
                     * @param [in] iterator : AbstractIterator cref = Constant Reference to the iterator to insert after
                     * @param [in] element : ElementType cref = Constant Reference to the element to be inserted via copy
                     * @exceptsafe if ElementType's Copy Constructor is exceptsafe
                     * @return bool = true if insertion was successful, false otherwise
                     *
                     * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                     *      LTC-00449-IT-insertAfterItCase1SingleValue1OffsetCase1,
                     *      LTC-00450-IT-insertAfterItCase1SingleValue1OffsetCase2,
                     *      LTC-00451-IT-insertAfterItCase1SingleValue1OffsetCase3,
                     *      LTC-00452-IT-insertAfterItCase1SingleValue1OffsetCase4,
                     *      LTC-00453-IT-insertAfterItCase1SingleValue2OffsetCase1,
                     *      LTC-00454-IT-insertAfterItCase1SingleValue2OffsetCase2,
                     *      LTC-00455-IT-insertAfterItCase1SingleValue2OffsetCase3,
                     *      LTC-00456-IT-insertAfterItCase1SingleValue2OffsetCase4,
                     *      LTC-00457-IT-insertAfterItCase1SingleValue3OffsetCase1,
                     *      LTC-00458-IT-insertAfterItCase1SingleValue3OffsetCase2,
                     *      LTC-00459-IT-insertAfterItCase1SingleValue3OffsetCase3,
                     *      LTC-00460-IT-insertAfterItCase1SingleValue3OffsetCase4,
                     *      LTC-00461-IT-insertAfterItCase3SingleValue1OffsetCase1,
                     *      LTC-00462-IT-insertAfterItCase3SingleValue1OffsetCase2,
                     *      LTC-00463-IT-insertAfterItCase3SingleValue1OffsetCase3,
                     *      LTC-00464-IT-insertAfterItCase3SingleValue1OffsetCase4,
                     *      LTC-00465-IT-insertAfterItCase3SingleValue2OffsetCase1,
                     *      LTC-00466-IT-insertAfterItCase3SingleValue2OffsetCase2,
                     *      LTC-00467-IT-insertAfterItCase3SingleValue2OffsetCase3,
                     *      LTC-00468-IT-insertAfterItCase3SingleValue2OffsetCase4,
                     *      LTC-00469-IT-insertAfterItCase3SingleValue3OffsetCase1,
                     *      LTC-00470-IT-insertAfterItCase3SingleValue3OffsetCase2,
                     *      LTC-00471-IT-insertAfterItCase3SingleValue3OffsetCase3,
                     *      LTC-00472-IT-insertAfterItCase3SingleValue3OffsetCase4
                     * }
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAfter (
                            AbstractIterator    const & iterator,
                            ElementType         const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to create a new element after a given iterator by move
                     * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a move constructor
                     * @param [in] iterator : AbstractIterator cref = Constant Reference to the iterator to insert after
                     * @param [in, out] element : ElementType mref = Move Reference to the element to be inserted via move
                     * @exceptsafe if ElementType's Copy Constructor is exceptsafe
                     * @return bool = true if insertion was successful, false otherwise
                     *
                     * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                     *      LTC-00449-IT-insertAfterItCase1SingleValue1OffsetCase1,
                     *      LTC-00450-IT-insertAfterItCase1SingleValue1OffsetCase2,
                     *      LTC-00451-IT-insertAfterItCase1SingleValue1OffsetCase3,
                     *      LTC-00452-IT-insertAfterItCase1SingleValue1OffsetCase4,
                     *      LTC-00453-IT-insertAfterItCase1SingleValue2OffsetCase1,
                     *      LTC-00454-IT-insertAfterItCase1SingleValue2OffsetCase2,
                     *      LTC-00455-IT-insertAfterItCase1SingleValue2OffsetCase3,
                     *      LTC-00456-IT-insertAfterItCase1SingleValue2OffsetCase4,
                     *      LTC-00457-IT-insertAfterItCase1SingleValue3OffsetCase1,
                     *      LTC-00458-IT-insertAfterItCase1SingleValue3OffsetCase2,
                     *      LTC-00459-IT-insertAfterItCase1SingleValue3OffsetCase3,
                     *      LTC-00460-IT-insertAfterItCase1SingleValue3OffsetCase4,
                     *      LTC-00461-IT-insertAfterItCase3SingleValue1OffsetCase1,
                     *      LTC-00462-IT-insertAfterItCase3SingleValue1OffsetCase2,
                     *      LTC-00463-IT-insertAfterItCase3SingleValue1OffsetCase3,
                     *      LTC-00464-IT-insertAfterItCase3SingleValue1OffsetCase4,
                     *      LTC-00465-IT-insertAfterItCase3SingleValue2OffsetCase1,
                     *      LTC-00466-IT-insertAfterItCase3SingleValue2OffsetCase2,
                     *      LTC-00467-IT-insertAfterItCase3SingleValue2OffsetCase3,
                     *      LTC-00468-IT-insertAfterItCase3SingleValue2OffsetCase4,
                     *      LTC-00469-IT-insertAfterItCase3SingleValue3OffsetCase1,
                     *      LTC-00470-IT-insertAfterItCase3SingleValue3OffsetCase2,
                     *      LTC-00471-IT-insertAfterItCase3SingleValue3OffsetCase3,
                     *      LTC-00472-IT-insertAfterItCase3SingleValue3OffsetCase4
                     * }
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isMoveConstructible < __TElementType > ()
                            > = 0
                    > auto insertAfter (
                            AbstractIterator    const & iterator,
                            ElementType              && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to create a new element before a given iterator by emplacement
                     * @tparam __EmplaceArgumentTypes is the pack of argument types passed to the constructor
                     * @param [in] iterator : AbstractIterator cref = Constant Reference to the iterator to insert before
                     * @param [in] parameters : __EmplaceArgumentTypes fref ... = Pack of forwarding references passed to the constructor
                     * @exceptsafe if ElementType's constructor for given parameters is exceptsafe
                     * @return bool = true if insertion was successful, false otherwise
                     *
                     * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                     *      LTC-00401-IT-insertBeforeItCase1SingleValue1OffsetCase1,
                     *      LTC-00402-IT-insertBeforeItCase1SingleValue1OffsetCase2,
                     *      LTC-00403-IT-insertBeforeItCase1SingleValue1OffsetCase3,
                     *      LTC-00404-IT-insertBeforeItCase1SingleValue1OffsetCase4,
                     *      LTC-00405-IT-insertBeforeItCase1SingleValue2OffsetCase1,
                     *      LTC-00406-IT-insertBeforeItCase1SingleValue2OffsetCase2,
                     *      LTC-00407-IT-insertBeforeItCase1SingleValue2OffsetCase3,
                     *      LTC-00408-IT-insertBeforeItCase1SingleValue2OffsetCase4,
                     *      LTC-00409-IT-insertBeforeItCase1SingleValue3OffsetCase1,
                     *      LTC-00410-IT-insertBeforeItCase1SingleValue3OffsetCase2,
                     *      LTC-00411-IT-insertBeforeItCase1SingleValue3OffsetCase3,
                     *      LTC-00412-IT-insertBeforeItCase1SingleValue3OffsetCase4,
                     *      LTC-00413-IT-insertBeforeItCase3SingleValue1OffsetCase1,
                     *      LTC-00414-IT-insertBeforeItCase3SingleValue1OffsetCase2,
                     *      LTC-00415-IT-insertBeforeItCase3SingleValue1OffsetCase3,
                     *      LTC-00416-IT-insertBeforeItCase3SingleValue1OffsetCase4,
                     *      LTC-00417-IT-insertBeforeItCase3SingleValue2OffsetCase1,
                     *      LTC-00418-IT-insertBeforeItCase3SingleValue2OffsetCase2,
                     *      LTC-00419-IT-insertBeforeItCase3SingleValue2OffsetCase3,
                     *      LTC-00420-IT-insertBeforeItCase3SingleValue2OffsetCase4,
                     *      LTC-00421-IT-insertBeforeItCase3SingleValue3OffsetCase1,
                     *      LTC-00422-IT-insertBeforeItCase3SingleValue3OffsetCase2,
                     *      LTC-00423-IT-insertBeforeItCase3SingleValue3OffsetCase3,
                     *      LTC-00424-IT-insertBeforeItCase3SingleValue3OffsetCase4
                     * }
                     *
                     * @public
                     */
                    template < typename ... __EmplaceArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto emplaceBefore (
                            AbstractIterator        const &     iterator,
                            __EmplaceArgumentTypes       && ... parameters
                    ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to create a new element after a given iterator by emplacement
                     * @tparam __EmplaceArgumentTypes is the pack of argument types passed to the constructor
                     * @param [in] iterator : AbstractIterator cref = Constant Reference to the iterator to insert after
                     * @param [in] parameters : __EmplaceArgumentTypes fref ... = Pack of forwarding references passed to the constructor
                     * @exceptsafe if ElementType's constructor for given parameters is exceptsafe
                     * @return bool = true if insertion was successful, false otherwise
                     *
                     * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                     *      LTC-00449-IT-insertAfterItCase1SingleValue1OffsetCase1,
                     *      LTC-00450-IT-insertAfterItCase1SingleValue1OffsetCase2,
                     *      LTC-00451-IT-insertAfterItCase1SingleValue1OffsetCase3,
                     *      LTC-00452-IT-insertAfterItCase1SingleValue1OffsetCase4,
                     *      LTC-00453-IT-insertAfterItCase1SingleValue2OffsetCase1,
                     *      LTC-00454-IT-insertAfterItCase1SingleValue2OffsetCase2,
                     *      LTC-00455-IT-insertAfterItCase1SingleValue2OffsetCase3,
                     *      LTC-00456-IT-insertAfterItCase1SingleValue2OffsetCase4,
                     *      LTC-00457-IT-insertAfterItCase1SingleValue3OffsetCase1,
                     *      LTC-00458-IT-insertAfterItCase1SingleValue3OffsetCase2,
                     *      LTC-00459-IT-insertAfterItCase1SingleValue3OffsetCase3,
                     *      LTC-00460-IT-insertAfterItCase1SingleValue3OffsetCase4,
                     *      LTC-00461-IT-insertAfterItCase3SingleValue1OffsetCase1,
                     *      LTC-00462-IT-insertAfterItCase3SingleValue1OffsetCase2,
                     *      LTC-00463-IT-insertAfterItCase3SingleValue1OffsetCase3,
                     *      LTC-00464-IT-insertAfterItCase3SingleValue1OffsetCase4,
                     *      LTC-00465-IT-insertAfterItCase3SingleValue2OffsetCase1,
                     *      LTC-00466-IT-insertAfterItCase3SingleValue2OffsetCase2,
                     *      LTC-00467-IT-insertAfterItCase3SingleValue2OffsetCase3,
                     *      LTC-00468-IT-insertAfterItCase3SingleValue2OffsetCase4,
                     *      LTC-00469-IT-insertAfterItCase3SingleValue3OffsetCase1,
                     *      LTC-00470-IT-insertAfterItCase3SingleValue3OffsetCase2,
                     *      LTC-00471-IT-insertAfterItCase3SingleValue3OffsetCase3,
                     *      LTC-00472-IT-insertAfterItCase3SingleValue3OffsetCase4
                     * }
                     *
                     * @public
                     */
                    template < typename ... __EmplaceArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto emplaceAfter (
                            AbstractIterator        const &     iterator,
                            __EmplaceArgumentTypes       && ... parameters
                    ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to insert multiple elements before a given iterator by creating a new before array request
                     * @tparam __ArgumentTypes is the type pack of the values to be inserted
                     * @param [in] iterator : AbstractIterator cref = Constant Reference to the iterator to insert before
                     * @param [in] values : __ArgumentTypes fref ... = Pack of forwarding elements to values, each of the pack to be transformed into an Element via construction and inserted
                     * @exceptsafe if ElementType is exceptsafe constructible with each given value
                     * @return true if insertion was successful, false otherwise
                     *
                     * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                     *      LTC-00593-IT-insertAllBeforeItCase1PackOffsetCase1,
                     *      LTC-00594-IT-insertAllBeforeItCase1PackOffsetCase2,
                     *      LTC-00595-IT-insertAllBeforeItCase1PackOffsetCase3,
                     *      LTC-00596-IT-insertAllBeforeItCase1PackOffsetCase4,
                     *      LTC-00601-IT-insertAllBeforeItCase3PackOffsetCase1,
                     *      LTC-00602-IT-insertAllBeforeItCase3PackOffsetCase2,
                     *      LTC-00603-IT-insertAllBeforeItCase3PackOffsetCase3,
                     *      LTC-00604-IT-insertAllBeforeItCase3PackOffsetCase4
                     * }
                     *
                     * @public
                     */
                    template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllBefore (
                            AbstractIterator    const &     iterator,
                            __ArgumentTypes          && ... values
                    ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool;

                public:
                    /**
                     * @brief Function used to insert multiple elements after a given iterator by creating a new before array request
                     * @tparam __ArgumentTypes is the type pack of the values to be inserted
                     * @param [in] iterator : AbstractIterator cref = Constant Reference to the iterator to insert after
                     * @param [in] values : __ArgumentTypes fref ... = Pack of forwarding elements to values, each of the pack to be transformed into an Element via construction and inserted
                     * @exceptsafe if ElementType is exceptsafe constructible with each given value
                     * @return true if insertion was successful, false otherwise
                     *
                     * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                     *      LTC-00609-IT-insertAllAfterItCase1PackOffsetCase1,
                     *      LTC-00610-IT-insertAllAfterItCase1PackOffsetCase2,
                     *      LTC-00611-IT-insertAllAfterItCase1PackOffsetCase3,
                     *      LTC-00612-IT-insertAllAfterItCase1PackOffsetCase4,
                     *      LTC-00617-IT-insertAllAfterItCase3PackOffsetCase1,
                     *      LTC-00618-IT-insertAllAfterItCase3PackOffsetCase2,
                     *      LTC-00619-IT-insertAllAfterItCase3PackOffsetCase3,
                     *      LTC-00620-IT-insertAllAfterItCase3PackOffsetCase4
                     * }
                     *
                     * @public
                     */
                    template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllAfter (
                            AbstractIterator    const &     iterator,
                            __ArgumentTypes          && ... values
                    ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool;

                public:
                    /**
                     * @brief Function used to insert multiple elements before an iterator of the iterable. This function varies whenever a RandomAccessIterator is given, to be able to efficiently determine
                     * the element count to insert. Otherwise, the distance will be computed iteratively. Insertion is done by extracting
                     * each from a given iterable and inserting each into the received addresses from the add before array request.
                     * @tparam __IterableType is the type of iterable given as parameter
                     * @param [in] iterator : AbstractIterator cref = Constant Reference to the iterator to insert before
                     * @param [in] iterable : __IterableType cref = Constant Reference to the iterable to extract the values from
                     * @exceptsafe if ElementType is exceptsafe constructible
                     *
                     * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                     *      LTC-00497-IT-insertAllOfBeforeItCase1MultipleValues1OffsetCase1,
                     *      LTC-00498-IT-insertAllOfBeforeItCase1MultipleValues1OffsetCase2,
                     *      LTC-00499-IT-insertAllOfBeforeItCase1MultipleValues1OffsetCase3,
                     *      LTC-00500-IT-insertAllOfBeforeItCase1MultipleValues1OffsetCase4,
                     *      LTC-00501-IT-insertAllOfBeforeItCase1MultipleValues2OffsetCase1,
                     *      LTC-00502-IT-insertAllOfBeforeItCase1MultipleValues2OffsetCase2,
                     *      LTC-00503-IT-insertAllOfBeforeItCase1MultipleValues2OffsetCase3,
                     *      LTC-00504-IT-insertAllOfBeforeItCase1MultipleValues2OffsetCase4,
                     *      LTC-00505-IT-insertAllOfBeforeItCase1MultipleValues3OffsetCase1,
                     *      LTC-00506-IT-insertAllOfBeforeItCase1MultipleValues3OffsetCase2,
                     *      LTC-00507-IT-insertAllOfBeforeItCase1MultipleValues3OffsetCase3,
                     *      LTC-00508-IT-insertAllOfBeforeItCase1MultipleValues3OffsetCase4,
                     *      LTC-00509-IT-insertAllOfBeforeItCase3MultipleValues1OffsetCase1,
                     *      LTC-00510-IT-insertAllOfBeforeItCase3MultipleValues1OffsetCase2,
                     *      LTC-00511-IT-insertAllOfBeforeItCase3MultipleValues1OffsetCase3,
                     *      LTC-00512-IT-insertAllOfBeforeItCase3MultipleValues1OffsetCase4,
                     *      LTC-00513-IT-insertAllOfBeforeItCase3MultipleValues2OffsetCase1,
                     *      LTC-00514-IT-insertAllOfBeforeItCase3MultipleValues2OffsetCase2,
                     *      LTC-00515-IT-insertAllOfBeforeItCase3MultipleValues2OffsetCase3,
                     *      LTC-00516-IT-insertAllOfBeforeItCase3MultipleValues2OffsetCase4,
                     *      LTC-00517-IT-insertAllOfBeforeItCase3MultipleValues3OffsetCase1,
                     *      LTC-00518-IT-insertAllOfBeforeItCase3MultipleValues3OffsetCase2,
                     *      LTC-00519-IT-insertAllOfBeforeItCase3MultipleValues3OffsetCase3,
                     *      LTC-00520-IT-insertAllOfBeforeItCase3MultipleValues3OffsetCase4
                     * }
                     *
                     * @public
                     */
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto insertAllOfBefore (
                            AbstractIterator    const & iterator,
                            __IterableType      const & iterable
                    ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to insert multiple elements before an iterator of the iterable. This function varies whenever a RandomAccessIterator is given, to be able to efficiently determine
                     * the element count to insert. Otherwise, the distance will be computed iteratively. Insertion is done by extracting
                     * each from a given iterable and inserting each into the received addresses from the add before array request.
                     * @tparam __IterableType is the type of iterable given as parameter
                     * @param [in] iterator : AbstractIterator cref = Constant Reference to the iterator to insert before
                     * @param [in] iterable : __IterableType cref = Constant Reference to the iterable to extract the values from
                     * @exceptsafe if ElementType is exceptsafe constructible
                     *
                     * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                     *      LTC-00497-IT-insertAllOfBeforeItCase1MultipleValues1OffsetCase1,
                     *      LTC-00498-IT-insertAllOfBeforeItCase1MultipleValues1OffsetCase2,
                     *      LTC-00499-IT-insertAllOfBeforeItCase1MultipleValues1OffsetCase3,
                     *      LTC-00500-IT-insertAllOfBeforeItCase1MultipleValues1OffsetCase4,
                     *      LTC-00501-IT-insertAllOfBeforeItCase1MultipleValues2OffsetCase1,
                     *      LTC-00502-IT-insertAllOfBeforeItCase1MultipleValues2OffsetCase2,
                     *      LTC-00503-IT-insertAllOfBeforeItCase1MultipleValues2OffsetCase3,
                     *      LTC-00504-IT-insertAllOfBeforeItCase1MultipleValues2OffsetCase4,
                     *      LTC-00505-IT-insertAllOfBeforeItCase1MultipleValues3OffsetCase1,
                     *      LTC-00506-IT-insertAllOfBeforeItCase1MultipleValues3OffsetCase2,
                     *      LTC-00507-IT-insertAllOfBeforeItCase1MultipleValues3OffsetCase3,
                     *      LTC-00508-IT-insertAllOfBeforeItCase1MultipleValues3OffsetCase4,
                     *      LTC-00509-IT-insertAllOfBeforeItCase3MultipleValues1OffsetCase1,
                     *      LTC-00510-IT-insertAllOfBeforeItCase3MultipleValues1OffsetCase2,
                     *      LTC-00511-IT-insertAllOfBeforeItCase3MultipleValues1OffsetCase3,
                     *      LTC-00512-IT-insertAllOfBeforeItCase3MultipleValues1OffsetCase4,
                     *      LTC-00513-IT-insertAllOfBeforeItCase3MultipleValues2OffsetCase1,
                     *      LTC-00514-IT-insertAllOfBeforeItCase3MultipleValues2OffsetCase2,
                     *      LTC-00515-IT-insertAllOfBeforeItCase3MultipleValues2OffsetCase3,
                     *      LTC-00516-IT-insertAllOfBeforeItCase3MultipleValues2OffsetCase4,
                     *      LTC-00517-IT-insertAllOfBeforeItCase3MultipleValues3OffsetCase1,
                     *      LTC-00518-IT-insertAllOfBeforeItCase3MultipleValues3OffsetCase2,
                     *      LTC-00519-IT-insertAllOfBeforeItCase3MultipleValues3OffsetCase3,
                     *      LTC-00520-IT-insertAllOfBeforeItCase3MultipleValues3OffsetCase4
                     * }
                     *
                     * @public
                     */
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    ! meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto insertAllOfBefore (
                            AbstractIterator    const & iterator,
                            __IterableType      const & iterable
                    ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to insert multiple elements before an iterator of the iterable, done by extracting
                     * each from a given initializer list and inserting each into the received addresses from the add before array request.
                     * @tparam __IterableType is the type of iterable given as parameter
                     * @param [in] iterator : AbstractIterator cref = Constant Reference to the iterator to insert before
                     * @param [in] list : std :: initializer_list cref = Constant Reference to an initializer list to extract the values from
                     * @exceptsafe if ElementType is exceptsafe constructible
                     *
                     * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                     *      LTC-00497-IT-insertAllOfBeforeItCase1MultipleValues1OffsetCase1,
                     *      LTC-00498-IT-insertAllOfBeforeItCase1MultipleValues1OffsetCase2,
                     *      LTC-00499-IT-insertAllOfBeforeItCase1MultipleValues1OffsetCase3,
                     *      LTC-00500-IT-insertAllOfBeforeItCase1MultipleValues1OffsetCase4,
                     *      LTC-00501-IT-insertAllOfBeforeItCase1MultipleValues2OffsetCase1,
                     *      LTC-00502-IT-insertAllOfBeforeItCase1MultipleValues2OffsetCase2,
                     *      LTC-00503-IT-insertAllOfBeforeItCase1MultipleValues2OffsetCase3,
                     *      LTC-00504-IT-insertAllOfBeforeItCase1MultipleValues2OffsetCase4,
                     *      LTC-00505-IT-insertAllOfBeforeItCase1MultipleValues3OffsetCase1,
                     *      LTC-00506-IT-insertAllOfBeforeItCase1MultipleValues3OffsetCase2,
                     *      LTC-00507-IT-insertAllOfBeforeItCase1MultipleValues3OffsetCase3,
                     *      LTC-00508-IT-insertAllOfBeforeItCase1MultipleValues3OffsetCase4,
                     *      LTC-00509-IT-insertAllOfBeforeItCase3MultipleValues1OffsetCase1,
                     *      LTC-00510-IT-insertAllOfBeforeItCase3MultipleValues1OffsetCase2,
                     *      LTC-00511-IT-insertAllOfBeforeItCase3MultipleValues1OffsetCase3,
                     *      LTC-00512-IT-insertAllOfBeforeItCase3MultipleValues1OffsetCase4,
                     *      LTC-00513-IT-insertAllOfBeforeItCase3MultipleValues2OffsetCase1,
                     *      LTC-00514-IT-insertAllOfBeforeItCase3MultipleValues2OffsetCase2,
                     *      LTC-00515-IT-insertAllOfBeforeItCase3MultipleValues2OffsetCase3,
                     *      LTC-00516-IT-insertAllOfBeforeItCase3MultipleValues2OffsetCase4,
                     *      LTC-00517-IT-insertAllOfBeforeItCase3MultipleValues3OffsetCase1,
                     *      LTC-00518-IT-insertAllOfBeforeItCase3MultipleValues3OffsetCase2,
                     *      LTC-00519-IT-insertAllOfBeforeItCase3MultipleValues3OffsetCase3,
                     *      LTC-00520-IT-insertAllOfBeforeItCase3MultipleValues3OffsetCase4
                     * }
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAllOfBefore (
                            AbstractIterator                            const & iterator,
                            std :: initializer_list < __ElementType >   const & list
                    ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to insert multiple elements after an iterator of the iterable. This function varies whenever a RandomAccessIterator is given, to be able to efficiently determine
                     * the element count to insert. Otherwise, the distance will be computed iteratively. Insertion is done by extracting
                     * each from a given iterable and inserting each into the received addresses from the add after array request.
                     * @tparam __IterableType is the type of iterable given as parameter
                     * @param [in] iterator : AbstractIterator cref = Constant Reference to the iterator to insert after
                     * @param [in] iterable : __IterableType cref = Constant Reference to the iterable to extract the values from
                     * @exceptsafe if ElementType is exceptsafe constructible
                     *
                     * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                     *      LTC-00545-IT-insertAllOfAfterItCase1MultipleValues1OffsetCase1,
                     *      LTC-00546-IT-insertAllOfAfterItCase1MultipleValues1OffsetCase2,
                     *      LTC-00547-IT-insertAllOfAfterItCase1MultipleValues1OffsetCase3,
                     *      LTC-00548-IT-insertAllOfAfterItCase1MultipleValues1OffsetCase4,
                     *      LTC-00549-IT-insertAllOfAfterItCase1MultipleValues2OffsetCase1,
                     *      LTC-00550-IT-insertAllOfAfterItCase1MultipleValues2OffsetCase2,
                     *      LTC-00551-IT-insertAllOfAfterItCase1MultipleValues2OffsetCase3,
                     *      LTC-00552-IT-insertAllOfAfterItCase1MultipleValues2OffsetCase4,
                     *      LTC-00553-IT-insertAllOfAfterItCase1MultipleValues3OffsetCase1,
                     *      LTC-00554-IT-insertAllOfAfterItCase1MultipleValues3OffsetCase2,
                     *      LTC-00555-IT-insertAllOfAfterItCase1MultipleValues3OffsetCase3,
                     *      LTC-00556-IT-insertAllOfAfterItCase1MultipleValues3OffsetCase4,
                     *      LTC-00557-IT-insertAllOfAfterItCase3MultipleValues1OffsetCase1,
                     *      LTC-00558-IT-insertAllOfAfterItCase3MultipleValues1OffsetCase2,
                     *      LTC-00559-IT-insertAllOfAfterItCase3MultipleValues1OffsetCase3,
                     *      LTC-00560-IT-insertAllOfAfterItCase3MultipleValues1OffsetCase4,
                     *      LTC-00561-IT-insertAllOfAfterItCase3MultipleValues2OffsetCase1,
                     *      LTC-00562-IT-insertAllOfAfterItCase3MultipleValues2OffsetCase2,
                     *      LTC-00563-IT-insertAllOfAfterItCase3MultipleValues2OffsetCase3,
                     *      LTC-00564-IT-insertAllOfAfterItCase3MultipleValues2OffsetCase4,
                     *      LTC-00565-IT-insertAllOfAfterItCase3MultipleValues3OffsetCase1,
                     *      LTC-00566-IT-insertAllOfAfterItCase3MultipleValues3OffsetCase2,
                     *      LTC-00567-IT-insertAllOfAfterItCase3MultipleValues3OffsetCase3,
                     *      LTC-00568-IT-insertAllOfAfterItCase3MultipleValues3OffsetCase4
                     * }
                     *
                     * @public
                     */
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto insertAllOfAfter (
                            AbstractIterator    const & iterator,
                            __IterableType      const & iterable
                    ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to insert multiple elements before an iterator of the iterable. This function varies whenever a RandomAccessIterator is given, to be able to efficiently determine
                     * the element count to insert. Otherwise, the distance will be computed iteratively. Insertion is done by extracting
                     * each from a given iterable and inserting each into the received addresses from the add before array request.
                     * @tparam __IterableType is the type of iterable given as parameter
                     * @param [in] iterator : AbstractIterator cref = Constant Reference to the iterator to insert after
                     * @param [in] iterable : __IterableType cref = Constant Reference to the iterable to extract the values from
                     * @exceptsafe if ElementType is exceptsafe constructible
                     *
                     * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                     *      LTC-00545-IT-insertAllOfAfterItCase1MultipleValues1OffsetCase1,
                     *      LTC-00546-IT-insertAllOfAfterItCase1MultipleValues1OffsetCase2,
                     *      LTC-00547-IT-insertAllOfAfterItCase1MultipleValues1OffsetCase3,
                     *      LTC-00548-IT-insertAllOfAfterItCase1MultipleValues1OffsetCase4,
                     *      LTC-00549-IT-insertAllOfAfterItCase1MultipleValues2OffsetCase1,
                     *      LTC-00550-IT-insertAllOfAfterItCase1MultipleValues2OffsetCase2,
                     *      LTC-00551-IT-insertAllOfAfterItCase1MultipleValues2OffsetCase3,
                     *      LTC-00552-IT-insertAllOfAfterItCase1MultipleValues2OffsetCase4,
                     *      LTC-00553-IT-insertAllOfAfterItCase1MultipleValues3OffsetCase1,
                     *      LTC-00554-IT-insertAllOfAfterItCase1MultipleValues3OffsetCase2,
                     *      LTC-00555-IT-insertAllOfAfterItCase1MultipleValues3OffsetCase3,
                     *      LTC-00556-IT-insertAllOfAfterItCase1MultipleValues3OffsetCase4,
                     *      LTC-00557-IT-insertAllOfAfterItCase3MultipleValues1OffsetCase1,
                     *      LTC-00558-IT-insertAllOfAfterItCase3MultipleValues1OffsetCase2,
                     *      LTC-00559-IT-insertAllOfAfterItCase3MultipleValues1OffsetCase3,
                     *      LTC-00560-IT-insertAllOfAfterItCase3MultipleValues1OffsetCase4,
                     *      LTC-00561-IT-insertAllOfAfterItCase3MultipleValues2OffsetCase1,
                     *      LTC-00562-IT-insertAllOfAfterItCase3MultipleValues2OffsetCase2,
                     *      LTC-00563-IT-insertAllOfAfterItCase3MultipleValues2OffsetCase3,
                     *      LTC-00564-IT-insertAllOfAfterItCase3MultipleValues2OffsetCase4,
                     *      LTC-00565-IT-insertAllOfAfterItCase3MultipleValues3OffsetCase1,
                     *      LTC-00566-IT-insertAllOfAfterItCase3MultipleValues3OffsetCase2,
                     *      LTC-00567-IT-insertAllOfAfterItCase3MultipleValues3OffsetCase3,
                     *      LTC-00568-IT-insertAllOfAfterItCase3MultipleValues3OffsetCase4
                     * }
                     *
                     * @public
                     */
                    template <
                            typename __IterableType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    ! meta :: __IterableSizeAvailable < __IterableType > :: value
                            > = 0
                    > auto insertAllOfAfter (
                            AbstractIterator    const & iterator,
                            __IterableType      const & iterable
                    ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to insert multiple elements after an iterator of the iterable, done by extracting
                     * each from a given initializer list and inserting each into the received addresses from the add after array request.
                     * @tparam __IterableType is the type of iterable given as parameter
                     * @param [in] iterator : AbstractIterator cref = Constant Reference to the iterator to insert after
                     * @param [in] list : std :: initializer_list cref = Constant Reference to an initializer list to extract the values from
                     * @exceptsafe if ElementType is exceptsafe constructible
                     *
                     * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                     *      LTC-00545-IT-insertAllOfAfterItCase1MultipleValues1OffsetCase1,
                     *      LTC-00546-IT-insertAllOfAfterItCase1MultipleValues1OffsetCase2,
                     *      LTC-00547-IT-insertAllOfAfterItCase1MultipleValues1OffsetCase3,
                     *      LTC-00548-IT-insertAllOfAfterItCase1MultipleValues1OffsetCase4,
                     *      LTC-00549-IT-insertAllOfAfterItCase1MultipleValues2OffsetCase1,
                     *      LTC-00550-IT-insertAllOfAfterItCase1MultipleValues2OffsetCase2,
                     *      LTC-00551-IT-insertAllOfAfterItCase1MultipleValues2OffsetCase3,
                     *      LTC-00552-IT-insertAllOfAfterItCase1MultipleValues2OffsetCase4,
                     *      LTC-00553-IT-insertAllOfAfterItCase1MultipleValues3OffsetCase1,
                     *      LTC-00554-IT-insertAllOfAfterItCase1MultipleValues3OffsetCase2,
                     *      LTC-00555-IT-insertAllOfAfterItCase1MultipleValues3OffsetCase3,
                     *      LTC-00556-IT-insertAllOfAfterItCase1MultipleValues3OffsetCase4,
                     *      LTC-00557-IT-insertAllOfAfterItCase3MultipleValues1OffsetCase1,
                     *      LTC-00558-IT-insertAllOfAfterItCase3MultipleValues1OffsetCase2,
                     *      LTC-00559-IT-insertAllOfAfterItCase3MultipleValues1OffsetCase3,
                     *      LTC-00560-IT-insertAllOfAfterItCase3MultipleValues1OffsetCase4,
                     *      LTC-00561-IT-insertAllOfAfterItCase3MultipleValues2OffsetCase1,
                     *      LTC-00562-IT-insertAllOfAfterItCase3MultipleValues2OffsetCase2,
                     *      LTC-00563-IT-insertAllOfAfterItCase3MultipleValues2OffsetCase3,
                     *      LTC-00564-IT-insertAllOfAfterItCase3MultipleValues2OffsetCase4,
                     *      LTC-00565-IT-insertAllOfAfterItCase3MultipleValues3OffsetCase1,
                     *      LTC-00566-IT-insertAllOfAfterItCase3MultipleValues3OffsetCase2,
                     *      LTC-00567-IT-insertAllOfAfterItCase3MultipleValues3OffsetCase3,
                     *      LTC-00568-IT-insertAllOfAfterItCase3MultipleValues3OffsetCase4
                     * }
                     *
                     * @public
                     */
                    template <
                            typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                            cds :: meta :: EnableIf <
                                    cds :: meta :: isCopyConstructible < __TElementType > ()
                            > = 0
                    > auto insertAllOfAfter (
                            AbstractIterator                            const & iterator,
                            std :: initializer_list < __ElementType >   const & list
                    ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to insert multiple elements before an iterator of the iterable
                     * by extracting each from a given iterator range and inserting each into the addresses received
                     * from the new before array request.
                     * An extra parameter is available to set the number of values between the given iterators,
                     * either as a limit, or as to avoid the computation of the distance between the two iterators.
                     * @tparam __IteratorType is the type of given iterators
                     * @param [in] iterator : AbstractIterator cref = Constant Reference to the iterator to insert before
                     * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
                     * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
                     * @param [in] count : Size = Distance between begin and end iterators. If 0, distance will be computed
                     * by subtraction, if iterator type is random, or by iteration otherwise
                     * @exceptsafe if ElementType is exceptsafe constructible
                     *
                     * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                     *      LTC-00497-IT-insertAllOfBeforeItCase1MultipleValues1OffsetCase1,
                     *      LTC-00498-IT-insertAllOfBeforeItCase1MultipleValues1OffsetCase2,
                     *      LTC-00499-IT-insertAllOfBeforeItCase1MultipleValues1OffsetCase3,
                     *      LTC-00500-IT-insertAllOfBeforeItCase1MultipleValues1OffsetCase4,
                     *      LTC-00501-IT-insertAllOfBeforeItCase1MultipleValues2OffsetCase1,
                     *      LTC-00502-IT-insertAllOfBeforeItCase1MultipleValues2OffsetCase2,
                     *      LTC-00503-IT-insertAllOfBeforeItCase1MultipleValues2OffsetCase3,
                     *      LTC-00504-IT-insertAllOfBeforeItCase1MultipleValues2OffsetCase4,
                     *      LTC-00505-IT-insertAllOfBeforeItCase1MultipleValues3OffsetCase1,
                     *      LTC-00506-IT-insertAllOfBeforeItCase1MultipleValues3OffsetCase2,
                     *      LTC-00507-IT-insertAllOfBeforeItCase1MultipleValues3OffsetCase3,
                     *      LTC-00508-IT-insertAllOfBeforeItCase1MultipleValues3OffsetCase4,
                     *      LTC-00509-IT-insertAllOfBeforeItCase3MultipleValues1OffsetCase1,
                     *      LTC-00510-IT-insertAllOfBeforeItCase3MultipleValues1OffsetCase2,
                     *      LTC-00511-IT-insertAllOfBeforeItCase3MultipleValues1OffsetCase3,
                     *      LTC-00512-IT-insertAllOfBeforeItCase3MultipleValues1OffsetCase4,
                     *      LTC-00513-IT-insertAllOfBeforeItCase3MultipleValues2OffsetCase1,
                     *      LTC-00514-IT-insertAllOfBeforeItCase3MultipleValues2OffsetCase2,
                     *      LTC-00515-IT-insertAllOfBeforeItCase3MultipleValues2OffsetCase3,
                     *      LTC-00516-IT-insertAllOfBeforeItCase3MultipleValues2OffsetCase4,
                     *      LTC-00517-IT-insertAllOfBeforeItCase3MultipleValues3OffsetCase1,
                     *      LTC-00518-IT-insertAllOfBeforeItCase3MultipleValues3OffsetCase2,
                     *      LTC-00519-IT-insertAllOfBeforeItCase3MultipleValues3OffsetCase3,
                     *      LTC-00520-IT-insertAllOfBeforeItCase3MultipleValues3OffsetCase4
                     * }
                     *
                     * @public
                     */
                    template < typename __OtherIteratorType > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllOfBefore (
                            AbstractIterator    const & iterator,
                            __OtherIteratorType const & begin,
                            __OtherIteratorType const & end,
                            Size                        count = 0ULL
                    ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to insert multiple elements after an iterator of the iterable
                     * by extracting each from a given iterator range and inserting each into the addresses received
                     * from the new after array request.
                     * An extra parameter is available to set the number of values between the given iterators,
                     * either as a limit, or as to avoid the computation of the distance between the two iterators.
                     * @tparam __IteratorType is the type of given iterators
                     * @param [in] iterator : AbstractIterator cref = Constant Reference to the iterator to insert after
                     * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
                     * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
                     * @param [in] count : Size = Distance between begin and end iterators. If 0, distance will be computed
                     * by subtraction, if iterator type is random, or by iteration otherwise
                     * @exceptsafe if ElementType is exceptsafe constructible
                     *
                     * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                     *      LTC-00545-IT-insertAllOfAfterItCase1MultipleValues1OffsetCase1,
                     *      LTC-00546-IT-insertAllOfAfterItCase1MultipleValues1OffsetCase2,
                     *      LTC-00547-IT-insertAllOfAfterItCase1MultipleValues1OffsetCase3,
                     *      LTC-00548-IT-insertAllOfAfterItCase1MultipleValues1OffsetCase4,
                     *      LTC-00549-IT-insertAllOfAfterItCase1MultipleValues2OffsetCase1,
                     *      LTC-00550-IT-insertAllOfAfterItCase1MultipleValues2OffsetCase2,
                     *      LTC-00551-IT-insertAllOfAfterItCase1MultipleValues2OffsetCase3,
                     *      LTC-00552-IT-insertAllOfAfterItCase1MultipleValues2OffsetCase4,
                     *      LTC-00553-IT-insertAllOfAfterItCase1MultipleValues3OffsetCase1,
                     *      LTC-00554-IT-insertAllOfAfterItCase1MultipleValues3OffsetCase2,
                     *      LTC-00555-IT-insertAllOfAfterItCase1MultipleValues3OffsetCase3,
                     *      LTC-00556-IT-insertAllOfAfterItCase1MultipleValues3OffsetCase4,
                     *      LTC-00557-IT-insertAllOfAfterItCase3MultipleValues1OffsetCase1,
                     *      LTC-00558-IT-insertAllOfAfterItCase3MultipleValues1OffsetCase2,
                     *      LTC-00559-IT-insertAllOfAfterItCase3MultipleValues1OffsetCase3,
                     *      LTC-00560-IT-insertAllOfAfterItCase3MultipleValues1OffsetCase4,
                     *      LTC-00561-IT-insertAllOfAfterItCase3MultipleValues2OffsetCase1,
                     *      LTC-00562-IT-insertAllOfAfterItCase3MultipleValues2OffsetCase2,
                     *      LTC-00563-IT-insertAllOfAfterItCase3MultipleValues2OffsetCase3,
                     *      LTC-00564-IT-insertAllOfAfterItCase3MultipleValues2OffsetCase4,
                     *      LTC-00565-IT-insertAllOfAfterItCase3MultipleValues3OffsetCase1,
                     *      LTC-00566-IT-insertAllOfAfterItCase3MultipleValues3OffsetCase2,
                     *      LTC-00567-IT-insertAllOfAfterItCase3MultipleValues3OffsetCase3,
                     *      LTC-00568-IT-insertAllOfAfterItCase3MultipleValues3OffsetCase4
                     * }
                     *
                     * @public
                     */
                    template < typename __OtherIteratorType > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllOfAfter (
                            AbstractIterator    const & iterator,
                            __OtherIteratorType const & begin,
                            __OtherIteratorType const & end,
                            Size                        count = 0ULL
                    ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool;
                };


                /**
                 * @interface Interface for creating Local Iterator-Relative-To Insertion requests, inserting / emplacing elements before or after a given iterator
                 * @tparam __ReceiverType is the type of implementor class, used for static polymorphism.
                 * Implementor is required to either implement an appropriate dispatcher ( __ListServerDispatcher or lower
                 * in hierarchy ) or provide an equivalent set of member functions - __newBeforeAddress,
                 *      __newBeforeAddressArray, __newAfterAddress,
                 *      __newAfterAddressArray - to the one provided by the dispatcher
                 *
                 * @tparam __ElementType is the type of elements contained into the Object
                 * @tparam __ReturnType is the type returned by the singular insertion functions
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __ReceiverType,                            /* NOLINT(bugprone-reserved-identifier) */
                        typename __ElementType,                             /* NOLINT(bugprone-reserved-identifier) */
                        typename __IteratorType                             /* NOLINT(bugprone-reserved-identifier) */
                > class __LocalIteratorRelativeInsertionPrimitiveClient {   /* NOLINT(bugprone-reserved-identifier) */

                private:
                    /**
                     * @typedef alias for __ElementType template parameter
                     * @private
                     */
                    using ElementType       = __ElementType;

                private:
                    /**
                     * @typedef alias for Iterator type
                     * @private
                     */
                    using Iterator          = __IteratorType;

                public:
                    /**
                     * @brief Function used to create a new element before a given iterator by copy
                     * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a copy constructor
                     * @param [in] iterator : Iterator cref = Constant Reference to the iterator to insert before
                     * @param [in] element : ElementType cref = Constant Reference to the element to be inserted via copy
                     * @exceptsafe if ElementType's Copy Constructor is exceptsafe
                     * @return bool = true if insertion was successful, false otherwise
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
                    > auto insertBefore (
                            Iterator    const & iterator,
                            ElementType const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to create a new element before a given iterator by move
                     * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a move constructor
                     * @param [in] iterator : Iterator cref = Constant Reference to the iterator to insert before
                     * @param [in, out] element : ElementType mref = Move Reference to the element to be inserted via move
                     * @exceptsafe if ElementType's Move Constructor is exceptsafe
                     * @return bool = true if insertion was successful, false otherwise
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
                    > auto insertBefore (
                            Iterator    const & iterator,
                            ElementType      && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to create a new element after a given iterator by copy
                     * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a copy constructor
                     * @param [in] iterator : Iterator cref = Constant Reference to the iterator to insert after
                     * @param [in] element : ElementType cref = Constant Reference to the element to be inserted via copy
                     * @exceptsafe if ElementType's Copy Constructor is exceptsafe
                     * @return bool = true if insertion was successful, false otherwise
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
                    > auto insertAfter (
                            Iterator    const & iterator,
                            ElementType const & element
                    ) noexcept ( noexcept ( ElementType ( element ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to create a new element after a given iterator by move
                     * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a move constructor
                     * @param [in] iterator : Iterator cref = Constant Reference to the iterator to insert after
                     * @param [in, out] element : ElementType mref = Move Reference to the element to be inserted via move
                     * @exceptsafe if ElementType's Copy Constructor is exceptsafe
                     * @return bool = true if insertion was successful, false otherwise
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
                    > auto insertAfter (
                            Iterator    const & iterator,
                            ElementType      && element
                    ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to create a new element before a given iterator by emplacement
                     * @tparam __EmplaceArgumentTypes is the pack of argument types passed to the constructor
                     * @param [in] iterator : Iterator cref = Constant Reference to the iterator to insert before
                     * @param [in] parameters : __EmplaceArgumentTypes fref ... = Pack of forwarding references passed to the constructor
                     * @exceptsafe if ElementType's constructor for given parameters is exceptsafe
                     * @return bool = true if insertion was successful, false otherwise
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    template < typename ... __EmplaceArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto emplaceBefore (
                            Iterator                const &     iterator,
                            __EmplaceArgumentTypes       && ... parameters
                    ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to create a new element after a given iterator by emplacement
                     * @tparam __EmplaceArgumentTypes is the pack of argument types passed to the constructor
                     * @param [in] iterator : Iterator cref = Constant Reference to the iterator to insert after
                     * @param [in] parameters : __EmplaceArgumentTypes fref ... = Pack of forwarding references passed to the constructor
                     * @exceptsafe if ElementType's constructor for given parameters is exceptsafe
                     * @return bool = true if insertion was successful, false otherwise
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    template < typename ... __EmplaceArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto emplaceAfter (
                            Iterator                const &     iterator,
                            __EmplaceArgumentTypes       && ... parameters
                    ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to insert multiple elements before a given iterator by creating a new before array request
                     * @tparam __ArgumentTypes is the type pack of the values to be inserted
                     * @param [in] iterator : Iterator cref = Constant Reference to the iterator to insert before
                     * @param [in] values : __ArgumentTypes fref ... = Pack of forwarding elements to values, each of the pack to be transformed into an Element via construction and inserted
                     * @exceptsafe if ElementType is exceptsafe constructible with each given value
                     * @return true if insertion was successful, false otherwise
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllBefore (
                            Iterator            const &     iterator,
                            __ArgumentTypes          && ... values
                    ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool;

                public:
                    /**
                     * @brief Function used to insert multiple elements after a given iterator by creating a new before array request
                     * @tparam __ArgumentTypes is the type pack of the values to be inserted
                     * @param [in] iterator : Iterator cref = Constant Reference to the iterator to insert after
                     * @param [in] values : __ArgumentTypes fref ... = Pack of forwarding elements to values, each of the pack to be transformed into an Element via construction and inserted
                     * @exceptsafe if ElementType is exceptsafe constructible with each given value
                     * @return true if insertion was successful, false otherwise
                     *
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     *
                     * @public
                     */
                    template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllAfter (
                            Iterator            const &     iterator,
                            __ArgumentTypes          && ... values
                    ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool;

                public:
                    /**
                     * @brief Function used to insert multiple elements before an iterator of the iterable. This function varies whenever a RandomAccessIterator is given, to be able to efficiently determine
                     * the element count to insert. Otherwise, the distance will be computed iteratively. Insertion is done by extracting
                     * each from a given iterable and inserting each into the received addresses from the add before array request.
                     * @tparam __IterableType is the type of iterable given as parameter
                     * @param [in] iterator : Iterator cref = Constant Reference to the iterator to insert before
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
                    > auto insertAllOfBefore (
                            Iterator        const & iterator,
                            __IterableType  const & iterable
                    ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to insert multiple elements before an iterator of the iterable. This function varies whenever a RandomAccessIterator is given, to be able to efficiently determine
                     * the element count to insert. Otherwise, the distance will be computed iteratively. Insertion is done by extracting
                     * each from a given iterable and inserting each into the received addresses from the add before array request.
                     * @tparam __IterableType is the type of iterable given as parameter
                     * @param [in] iterator : Iterator cref = Constant Reference to the iterator to insert before
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
                    > auto insertAllOfBefore (
                            Iterator        const & iterator,
                            __IterableType  const & iterable
                    ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to insert multiple elements before an iterator of the iterable, done by extracting
                     * each from a given initializer list and inserting each into the received addresses from the add before array request.
                     * @tparam __IterableType is the type of iterable given as parameter
                     * @param [in] iterator : Iterator cref = Constant Reference to the iterator to insert before
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
                    > auto insertAllOfBefore (
                            Iterator                                    const & iterator,
                            std :: initializer_list < __ElementType >   const & list
                    ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to insert multiple elements after an iterator of the iterable. This function varies whenever a RandomAccessIterator is given, to be able to efficiently determine
                     * the element count to insert. Otherwise, the distance will be computed iteratively. Insertion is done by extracting
                     * each from a given iterable and inserting each into the received addresses from the add after array request.
                     * @tparam __IterableType is the type of iterable given as parameter
                     * @param [in] iterator : Iterator cref = Constant Reference to the iterator to insert after
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
                    > auto insertAllOfAfter (
                            Iterator            const & iterator,
                            __IterableType      const & iterable
                    ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to insert multiple elements before an iterator of the iterable. This function varies whenever a RandomAccessIterator is given, to be able to efficiently determine
                     * the element count to insert. Otherwise, the distance will be computed iteratively. Insertion is done by extracting
                     * each from a given iterable and inserting each into the received addresses from the add before array request.
                     * @tparam __IterableType is the type of iterable given as parameter
                     * @param [in] iterator : Iterator cref = Constant Reference to the iterator to insert after
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
                    > auto insertAllOfAfter (
                            Iterator            const & iterator,
                            __IterableType      const & iterable
                    ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to insert multiple elements after an iterator of the iterable, done by extracting
                     * each from a given initializer list and inserting each into the received addresses from the add after array request.
                     * @tparam __IterableType is the type of iterable given as parameter
                     * @param [in] iterator : Iterator cref = Constant Reference to the iterator to insert after
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
                    > auto insertAllOfAfter (
                            Iterator                                    const & iterator,
                            std :: initializer_list < __ElementType >   const & list
                    ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to insert multiple elements before an iterator of the iterable
                     * by extracting each from a given iterator range and inserting each into the addresses received
                     * from the new before array request.
                     * An extra parameter is available to set the number of values between the given iterators,
                     * either as a limit, or as to avoid the computation of the distance between the two iterators.
                     * @tparam __IteratorType is the type of given iterators
                     * @param [in] iterator : Iterator cref = Constant Reference to the iterator to insert before
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
                    template < typename __OtherIteratorType > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllOfBefore (
                            Iterator            const & iterator,
                            __OtherIteratorType const & begin,
                            __OtherIteratorType const & end,
                            Size                        count = 0ULL
                    ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool;

                public:
                    /**
                     * @brief Function used to insert multiple elements after an iterator of the iterable
                     * by extracting each from a given iterator range and inserting each into the addresses received
                     * from the new after array request.
                     * An extra parameter is available to set the number of values between the given iterators,
                     * either as a limit, or as to avoid the computation of the distance between the two iterators.
                     * @tparam __IteratorType is the type of given iterators
                     * @param [in] iterator : Iterator cref = Constant Reference to the iterator to insert after
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
                    template < typename __OtherIteratorType > /* NOLINT(bugprone-reserved-identifier) */
                    auto insertAllOfAfter (
                            Iterator            const & iterator,
                            __OtherIteratorType const & begin,
                            __OtherIteratorType const & end,
                            Size                        count = 0ULL
                    ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool;
                };

            }
        }
    }
}

#endif /* __CDS_SHARED_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_HPP__ */
