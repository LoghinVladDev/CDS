/*
 * Created by loghin on 6/28/22.
 */

#ifndef __CDS_SHARED_CONST_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_CONST_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @interface Interface for creating Const-Iterator-Relative-To Insertion requests, inserting / emplacing elements before or after a given iterator
             * @tparam __ReceiverType is the type of implementor class, used for static polymorphism.
             * Implementor is required to either be derived from the List abstract class or a class
             * extending the __CollectionInternalCommunicationChannel class, or provide equivalent member
             * function implementations provided by the __collectionInternalCommunicationChannel class
             * Note : This Client will request the member functions identified with:
             *      - __cirt_newBeforeConstAddress
             *      - __cirt_newBeforeConstAddressArray
             *      - __cirt_newAfterConstAddress
             *      - __cirt_newAfterConstAddressArray
             *
             * @tparam __ElementType is the type of elements contained into the Object
             * @tparam __ReturnType is the type returned by the singular insertion functions
             *
             * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: All
             *
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __ReceiverType,                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType                                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > class __AbstractConstIteratorRelativeInsertionPrimitiveClient {   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @typedef alias for __ElementType template parameter
                 * @private
                 */
                using ElementType       = __ElementType;

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @typedef alias for Abstract Const Iterator type
                 * @private
                 */
                using AbstractConstIterator  =
                        __AbstractDelegateWrapperIterator < __ElementType const >;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to create a new element before a given iterator by copy
                 * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a copy constructor
                 * @param [in] iterator : AbstractConstIterator cref = Constant Reference to the iterator to insert before
                 * @param [in] element : ElementType cref = Constant Reference to the element to be inserted via copy
                 * @exceptsafe if ElementType's Copy Constructor is exceptsafe
                 * @return bool = true if insertion was successful, false otherwise
                 *
                 * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                 *      LTC-00425-IT-insertBeforeItCase2SingleValue1OffsetCase1,
                 *      LTC-00426-IT-insertBeforeItCase2SingleValue1OffsetCase2,
                 *      LTC-00427-IT-insertBeforeItCase2SingleValue1OffsetCase3,
                 *      LTC-00428-IT-insertBeforeItCase2SingleValue1OffsetCase4,
                 *      LTC-00429-IT-insertBeforeItCase2SingleValue2OffsetCase1,
                 *      LTC-00430-IT-insertBeforeItCase2SingleValue2OffsetCase2,
                 *      LTC-00431-IT-insertBeforeItCase2SingleValue2OffsetCase3,
                 *      LTC-00432-IT-insertBeforeItCase2SingleValue2OffsetCase4,
                 *      LTC-00433-IT-insertBeforeItCase2SingleValue3OffsetCase1,
                 *      LTC-00434-IT-insertBeforeItCase2SingleValue3OffsetCase2,
                 *      LTC-00435-IT-insertBeforeItCase2SingleValue3OffsetCase3,
                 *      LTC-00436-IT-insertBeforeItCase2SingleValue3OffsetCase4,
                 *      LTC-00437-IT-insertBeforeItCase4SingleValue1OffsetCase1,
                 *      LTC-00438-IT-insertBeforeItCase4SingleValue1OffsetCase2,
                 *      LTC-00439-IT-insertBeforeItCase4SingleValue1OffsetCase3,
                 *      LTC-00440-IT-insertBeforeItCase4SingleValue1OffsetCase4,
                 *      LTC-00441-IT-insertBeforeItCase4SingleValue2OffsetCase1,
                 *      LTC-00442-IT-insertBeforeItCase4SingleValue2OffsetCase2,
                 *      LTC-00443-IT-insertBeforeItCase4SingleValue2OffsetCase3,
                 *      LTC-00444-IT-insertBeforeItCase4SingleValue2OffsetCase4,
                 *      LTC-00445-IT-insertBeforeItCase4SingleValue3OffsetCase1,
                 *      LTC-00446-IT-insertBeforeItCase4SingleValue3OffsetCase2,
                 *      LTC-00447-IT-insertBeforeItCase4SingleValue3OffsetCase3,
                 *      LTC-00448-IT-insertBeforeItCase4SingleValue3OffsetCase4
                 * }
                 *
                 * @public
                 */
                template <
                        typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        > = 0
                > auto insertBefore (
                        AbstractConstIterator   const & iterator,
                        ElementType             const & element
                ) noexcept ( noexcept ( ElementType ( element ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to create a new element before a given iterator by move
                 * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a move constructor
                 * @param [in] iterator : AbstractConstIterator cref = Constant Reference to the iterator to insert before
                 * @param [in, out] element : ElementType mref = Move Reference to the element to be inserted via move
                 * @exceptsafe if ElementType's Move Constructor is exceptsafe
                 * @return bool = true if insertion was successful, false otherwise
                 *
                 * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                 *      LTC-00425-IT-insertBeforeItCase2SingleValue1OffsetCase1,
                 *      LTC-00426-IT-insertBeforeItCase2SingleValue1OffsetCase2,
                 *      LTC-00427-IT-insertBeforeItCase2SingleValue1OffsetCase3,
                 *      LTC-00428-IT-insertBeforeItCase2SingleValue1OffsetCase4,
                 *      LTC-00429-IT-insertBeforeItCase2SingleValue2OffsetCase1,
                 *      LTC-00430-IT-insertBeforeItCase2SingleValue2OffsetCase2,
                 *      LTC-00431-IT-insertBeforeItCase2SingleValue2OffsetCase3,
                 *      LTC-00432-IT-insertBeforeItCase2SingleValue2OffsetCase4,
                 *      LTC-00433-IT-insertBeforeItCase2SingleValue3OffsetCase1,
                 *      LTC-00434-IT-insertBeforeItCase2SingleValue3OffsetCase2,
                 *      LTC-00435-IT-insertBeforeItCase2SingleValue3OffsetCase3,
                 *      LTC-00436-IT-insertBeforeItCase2SingleValue3OffsetCase4,
                 *      LTC-00437-IT-insertBeforeItCase4SingleValue1OffsetCase1,
                 *      LTC-00438-IT-insertBeforeItCase4SingleValue1OffsetCase2,
                 *      LTC-00439-IT-insertBeforeItCase4SingleValue1OffsetCase3,
                 *      LTC-00440-IT-insertBeforeItCase4SingleValue1OffsetCase4,
                 *      LTC-00441-IT-insertBeforeItCase4SingleValue2OffsetCase1,
                 *      LTC-00442-IT-insertBeforeItCase4SingleValue2OffsetCase2,
                 *      LTC-00443-IT-insertBeforeItCase4SingleValue2OffsetCase3,
                 *      LTC-00444-IT-insertBeforeItCase4SingleValue2OffsetCase4,
                 *      LTC-00445-IT-insertBeforeItCase4SingleValue3OffsetCase1,
                 *      LTC-00446-IT-insertBeforeItCase4SingleValue3OffsetCase2,
                 *      LTC-00447-IT-insertBeforeItCase4SingleValue3OffsetCase3,
                 *      LTC-00448-IT-insertBeforeItCase4SingleValue3OffsetCase4
                 * }
                 *
                 * @public
                 */
                template <
                        typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveConstructible < __TElementType > ()
                        > = 0
                > auto insertBefore (
                        AbstractConstIterator    const & iterator,
                        ElementType                   && element
                ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to create a new element after a given iterator by copy
                 * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a copy constructor
                 * @param [in] iterator : AbstractConstIterator cref = Constant Reference to the iterator to insert after
                 * @param [in] element : ElementType cref = Constant Reference to the element to be inserted via copy
                 * @exceptsafe if ElementType's Copy Constructor is exceptsafe
                 * @return bool = true if insertion was successful, false otherwise
                 *
                 * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                 *      LTC-00473-IT-insertAfterItCase2SingleValue1OffsetCase1,
                 *      LTC-00474-IT-insertAfterItCase2SingleValue1OffsetCase2,
                 *      LTC-00475-IT-insertAfterItCase2SingleValue1OffsetCase3,
                 *      LTC-00476-IT-insertAfterItCase2SingleValue1OffsetCase4,
                 *      LTC-00477-IT-insertAfterItCase2SingleValue2OffsetCase1,
                 *      LTC-00478-IT-insertAfterItCase2SingleValue2OffsetCase2,
                 *      LTC-00479-IT-insertAfterItCase2SingleValue2OffsetCase3,
                 *      LTC-00480-IT-insertAfterItCase2SingleValue2OffsetCase4,
                 *      LTC-00481-IT-insertAfterItCase2SingleValue3OffsetCase1,
                 *      LTC-00482-IT-insertAfterItCase2SingleValue3OffsetCase2,
                 *      LTC-00483-IT-insertAfterItCase2SingleValue3OffsetCase3,
                 *      LTC-00484-IT-insertAfterItCase2SingleValue3OffsetCase4,
                 *      LTC-00485-IT-insertAfterItCase4SingleValue1OffsetCase1,
                 *      LTC-00486-IT-insertAfterItCase4SingleValue1OffsetCase2,
                 *      LTC-00487-IT-insertAfterItCase4SingleValue1OffsetCase3,
                 *      LTC-00488-IT-insertAfterItCase4SingleValue1OffsetCase4,
                 *      LTC-00489-IT-insertAfterItCase4SingleValue2OffsetCase1,
                 *      LTC-00490-IT-insertAfterItCase4SingleValue2OffsetCase2,
                 *      LTC-00491-IT-insertAfterItCase4SingleValue2OffsetCase3,
                 *      LTC-00492-IT-insertAfterItCase4SingleValue2OffsetCase4,
                 *      LTC-00493-IT-insertAfterItCase4SingleValue3OffsetCase1,
                 *      LTC-00494-IT-insertAfterItCase4SingleValue3OffsetCase2,
                 *      LTC-00495-IT-insertAfterItCase4SingleValue3OffsetCase3,
                 *      LTC-00496-IT-insertAfterItCase4SingleValue3OffsetCase4
                 * }
                 *
                 * @public
                 */
                template <
                        typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        > = 0
                > auto insertAfter (
                        AbstractConstIterator   const & iterator,
                        ElementType             const & element
                ) noexcept ( noexcept ( ElementType ( element ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to create a new element after a given iterator by move
                 * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a move constructor
                 * @param [in] iterator : AbstractConstIterator cref = Constant Reference to the iterator to insert after
                 * @param [in, out] element : ElementType mref = Move Reference to the element to be inserted via move
                 * @exceptsafe if ElementType's Copy Constructor is exceptsafe
                 * @return bool = true if insertion was successful, false otherwise
                 *
                 * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                 *      LTC-00473-IT-insertAfterItCase2SingleValue1OffsetCase1,
                 *      LTC-00474-IT-insertAfterItCase2SingleValue1OffsetCase2,
                 *      LTC-00475-IT-insertAfterItCase2SingleValue1OffsetCase3,
                 *      LTC-00476-IT-insertAfterItCase2SingleValue1OffsetCase4,
                 *      LTC-00477-IT-insertAfterItCase2SingleValue2OffsetCase1,
                 *      LTC-00478-IT-insertAfterItCase2SingleValue2OffsetCase2,
                 *      LTC-00479-IT-insertAfterItCase2SingleValue2OffsetCase3,
                 *      LTC-00480-IT-insertAfterItCase2SingleValue2OffsetCase4,
                 *      LTC-00481-IT-insertAfterItCase2SingleValue3OffsetCase1,
                 *      LTC-00482-IT-insertAfterItCase2SingleValue3OffsetCase2,
                 *      LTC-00483-IT-insertAfterItCase2SingleValue3OffsetCase3,
                 *      LTC-00484-IT-insertAfterItCase2SingleValue3OffsetCase4,
                 *      LTC-00485-IT-insertAfterItCase4SingleValue1OffsetCase1,
                 *      LTC-00486-IT-insertAfterItCase4SingleValue1OffsetCase2,
                 *      LTC-00487-IT-insertAfterItCase4SingleValue1OffsetCase3,
                 *      LTC-00488-IT-insertAfterItCase4SingleValue1OffsetCase4,
                 *      LTC-00489-IT-insertAfterItCase4SingleValue2OffsetCase1,
                 *      LTC-00490-IT-insertAfterItCase4SingleValue2OffsetCase2,
                 *      LTC-00491-IT-insertAfterItCase4SingleValue2OffsetCase3,
                 *      LTC-00492-IT-insertAfterItCase4SingleValue2OffsetCase4,
                 *      LTC-00493-IT-insertAfterItCase4SingleValue3OffsetCase1,
                 *      LTC-00494-IT-insertAfterItCase4SingleValue3OffsetCase2,
                 *      LTC-00495-IT-insertAfterItCase4SingleValue3OffsetCase3,
                 *      LTC-00496-IT-insertAfterItCase4SingleValue3OffsetCase4
                 * }
                 *
                 * @public
                 */
                template <
                        typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveConstructible < __TElementType > ()
                        > = 0
                > auto insertAfter (
                        AbstractConstIterator    const & iterator,
                        ElementType                   && element
                ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to create a new element before a given iterator by emplacement
                 * @tparam __EmplaceArgumentTypes is the pack of argument types passed to the constructor
                 * @param [in] iterator : AbstractConstIterator cref = Constant Reference to the iterator to insert before
                 * @param [in] parameters : __EmplaceArgumentTypes fref ... = Pack of forwarding references passed to the constructor
                 * @exceptsafe if ElementType's constructor for given parameters is exceptsafe
                 * @return bool = true if insertion was successful, false otherwise
                 *
                 * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                 *      LTC-00425-IT-insertBeforeItCase2SingleValue1OffsetCase1,
                 *      LTC-00426-IT-insertBeforeItCase2SingleValue1OffsetCase2,
                 *      LTC-00427-IT-insertBeforeItCase2SingleValue1OffsetCase3,
                 *      LTC-00428-IT-insertBeforeItCase2SingleValue1OffsetCase4,
                 *      LTC-00429-IT-insertBeforeItCase2SingleValue2OffsetCase1,
                 *      LTC-00430-IT-insertBeforeItCase2SingleValue2OffsetCase2,
                 *      LTC-00431-IT-insertBeforeItCase2SingleValue2OffsetCase3,
                 *      LTC-00432-IT-insertBeforeItCase2SingleValue2OffsetCase4,
                 *      LTC-00433-IT-insertBeforeItCase2SingleValue3OffsetCase1,
                 *      LTC-00434-IT-insertBeforeItCase2SingleValue3OffsetCase2,
                 *      LTC-00435-IT-insertBeforeItCase2SingleValue3OffsetCase3,
                 *      LTC-00436-IT-insertBeforeItCase2SingleValue3OffsetCase4,
                 *      LTC-00437-IT-insertBeforeItCase4SingleValue1OffsetCase1,
                 *      LTC-00438-IT-insertBeforeItCase4SingleValue1OffsetCase2,
                 *      LTC-00439-IT-insertBeforeItCase4SingleValue1OffsetCase3,
                 *      LTC-00440-IT-insertBeforeItCase4SingleValue1OffsetCase4,
                 *      LTC-00441-IT-insertBeforeItCase4SingleValue2OffsetCase1,
                 *      LTC-00442-IT-insertBeforeItCase4SingleValue2OffsetCase2,
                 *      LTC-00443-IT-insertBeforeItCase4SingleValue2OffsetCase3,
                 *      LTC-00444-IT-insertBeforeItCase4SingleValue2OffsetCase4,
                 *      LTC-00445-IT-insertBeforeItCase4SingleValue3OffsetCase1,
                 *      LTC-00446-IT-insertBeforeItCase4SingleValue3OffsetCase2,
                 *      LTC-00447-IT-insertBeforeItCase4SingleValue3OffsetCase3,
                 *      LTC-00448-IT-insertBeforeItCase4SingleValue3OffsetCase4
                 * }
                 *
                 * @public
                 */
                template < typename ... __EmplaceArgumentTypes > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto emplaceBefore (
                        AbstractConstIterator        const &     iterator,
                        __EmplaceArgumentTypes            && ... parameters
                ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to create a new element after a given iterator by emplacement
                 * @tparam __EmplaceArgumentTypes is the pack of argument types passed to the constructor
                 * @param [in] iterator : AbstractConstIterator cref = Constant Reference to the iterator to insert after
                 * @param [in] parameters : __EmplaceArgumentTypes fref ... = Pack of forwarding references passed to the constructor
                 * @exceptsafe if ElementType's constructor for given parameters is exceptsafe
                 * @return bool = true if insertion was successful, false otherwise
                 *
                 * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                 *      LTC-00473-IT-insertAfterItCase2SingleValue1OffsetCase1,
                 *      LTC-00474-IT-insertAfterItCase2SingleValue1OffsetCase2,
                 *      LTC-00475-IT-insertAfterItCase2SingleValue1OffsetCase3,
                 *      LTC-00476-IT-insertAfterItCase2SingleValue1OffsetCase4,
                 *      LTC-00477-IT-insertAfterItCase2SingleValue2OffsetCase1,
                 *      LTC-00478-IT-insertAfterItCase2SingleValue2OffsetCase2,
                 *      LTC-00479-IT-insertAfterItCase2SingleValue2OffsetCase3,
                 *      LTC-00480-IT-insertAfterItCase2SingleValue2OffsetCase4,
                 *      LTC-00481-IT-insertAfterItCase2SingleValue3OffsetCase1,
                 *      LTC-00482-IT-insertAfterItCase2SingleValue3OffsetCase2,
                 *      LTC-00483-IT-insertAfterItCase2SingleValue3OffsetCase3,
                 *      LTC-00484-IT-insertAfterItCase2SingleValue3OffsetCase4,
                 *      LTC-00485-IT-insertAfterItCase4SingleValue1OffsetCase1,
                 *      LTC-00486-IT-insertAfterItCase4SingleValue1OffsetCase2,
                 *      LTC-00487-IT-insertAfterItCase4SingleValue1OffsetCase3,
                 *      LTC-00488-IT-insertAfterItCase4SingleValue1OffsetCase4,
                 *      LTC-00489-IT-insertAfterItCase4SingleValue2OffsetCase1,
                 *      LTC-00490-IT-insertAfterItCase4SingleValue2OffsetCase2,
                 *      LTC-00491-IT-insertAfterItCase4SingleValue2OffsetCase3,
                 *      LTC-00492-IT-insertAfterItCase4SingleValue2OffsetCase4,
                 *      LTC-00493-IT-insertAfterItCase4SingleValue3OffsetCase1,
                 *      LTC-00494-IT-insertAfterItCase4SingleValue3OffsetCase2,
                 *      LTC-00495-IT-insertAfterItCase4SingleValue3OffsetCase3,
                 *      LTC-00496-IT-insertAfterItCase4SingleValue3OffsetCase4
                 * }
                 *
                 * @public
                 */
                template < typename ... __EmplaceArgumentTypes > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto emplaceAfter (
                        AbstractConstIterator        const &     iterator,
                        __EmplaceArgumentTypes            && ... parameters
                ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to insert multiple elements before a given iterator by creating a new before array request
                 * @tparam __ArgumentTypes is the type pack of the values to be inserted
                 * @param [in] iterator : AbstractConstIterator cref = Constant Reference to the iterator to insert before
                 * @param [in] values : __ArgumentTypes fref ... = Pack of forwarding elements to values, each of the pack to be transformed into an Element via construction and inserted
                 * @exceptsafe if ElementType is exceptsafe constructible with each given value
                 * @return true if insertion was successful, false otherwise
                 *
                 * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                 *      LTC-00597-IT-insertAllBeforeItCase2PackOffsetCase1,
                 *      LTC-00598-IT-insertAllBeforeItCase2PackOffsetCase2,
                 *      LTC-00599-IT-insertAllBeforeItCase2PackOffsetCase3,
                 *      LTC-00600-IT-insertAllBeforeItCase2PackOffsetCase4,
                 *      LTC-00605-IT-insertAllBeforeItCase4PackOffsetCase1,
                 *      LTC-00606-IT-insertAllBeforeItCase4PackOffsetCase2,
                 *      LTC-00607-IT-insertAllBeforeItCase4PackOffsetCase3,
                 *      LTC-00608-IT-insertAllBeforeItCase4PackOffsetCase4
                 * }
                 *
                 * @public
                 */
                template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto insertAllBefore (
                        AbstractConstIterator    const &     iterator,
                        __ArgumentTypes               && ... values
                ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to insert multiple elements after a given iterator by creating a new before array request
                 * @tparam __ArgumentTypes is the type pack of the values to be inserted
                 * @param [in] iterator : AbstractConstIterator cref = Constant Reference to the iterator to insert after
                 * @param [in] values : __ArgumentTypes fref ... = Pack of forwarding elements to values, each of the pack to be transformed into an Element via construction and inserted
                 * @exceptsafe if ElementType is exceptsafe constructible with each given value
                 * @return true if insertion was successful, false otherwise
                 *
                 * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                 *      LTC-00613-IT-insertAllAfterItCase2PackOffsetCase1,
                 *      LTC-00614-IT-insertAllAfterItCase2PackOffsetCase2,
                 *      LTC-00615-IT-insertAllAfterItCase2PackOffsetCase3,
                 *      LTC-00616-IT-insertAllAfterItCase2PackOffsetCase4,
                 *      LTC-00621-IT-insertAllAfterItCase4PackOffsetCase1,
                 *      LTC-00622-IT-insertAllAfterItCase4PackOffsetCase2,
                 *      LTC-00623-IT-insertAllAfterItCase4PackOffsetCase3,
                 *      LTC-00624-IT-insertAllAfterItCase4PackOffsetCase4
                 * }
                 *
                 * @public
                 */
                template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto insertAllAfter (
                        AbstractConstIterator    const &     iterator,
                        __ArgumentTypes               && ... values
                ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to insert multiple elements before an iterator of the iterable. This function varies whenever a RandomAccessIterator is given, to be able to efficiently determine
                 * the element count to insert. Otherwise, the distance will be computed iteratively. Insertion is done by extracting
                 * each from a given iterable and inserting each into the received addresses from the add before array request.
                 * @tparam __IterableType is the type of iterable given as parameter
                 * @param [in] iterator : AbstractConstIterator cref = Constant Reference to the iterator to insert before
                 * @param [in] iterable : __IterableType cref = Constant Reference to the iterable to extract the values from
                 * @exceptsafe if ElementType is exceptsafe constructible
                 *
                 * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                 *      LTC-00521-IT-insertAllOfBeforeItCase2MultipleValues1OffsetCase1,
                 *      LTC-00522-IT-insertAllOfBeforeItCase2MultipleValues1OffsetCase2,
                 *      LTC-00523-IT-insertAllOfBeforeItCase2MultipleValues1OffsetCase3,
                 *      LTC-00524-IT-insertAllOfBeforeItCase2MultipleValues1OffsetCase4,
                 *      LTC-00525-IT-insertAllOfBeforeItCase2MultipleValues2OffsetCase1,
                 *      LTC-00526-IT-insertAllOfBeforeItCase2MultipleValues2OffsetCase2,
                 *      LTC-00527-IT-insertAllOfBeforeItCase2MultipleValues2OffsetCase3,
                 *      LTC-00528-IT-insertAllOfBeforeItCase2MultipleValues2OffsetCase4,
                 *      LTC-00529-IT-insertAllOfBeforeItCase2MultipleValues3OffsetCase1,
                 *      LTC-00530-IT-insertAllOfBeforeItCase2MultipleValues3OffsetCase2,
                 *      LTC-00531-IT-insertAllOfBeforeItCase2MultipleValues3OffsetCase3,
                 *      LTC-00532-IT-insertAllOfBeforeItCase2MultipleValues3OffsetCase4,
                 *      LTC-00533-IT-insertAllOfBeforeItCase4MultipleValues1OffsetCase1,
                 *      LTC-00534-IT-insertAllOfBeforeItCase4MultipleValues1OffsetCase2,
                 *      LTC-00535-IT-insertAllOfBeforeItCase4MultipleValues1OffsetCase3,
                 *      LTC-00536-IT-insertAllOfBeforeItCase4MultipleValues1OffsetCase4,
                 *      LTC-00537-IT-insertAllOfBeforeItCase4MultipleValues2OffsetCase1,
                 *      LTC-00538-IT-insertAllOfBeforeItCase4MultipleValues2OffsetCase2,
                 *      LTC-00539-IT-insertAllOfBeforeItCase4MultipleValues2OffsetCase3,
                 *      LTC-00540-IT-insertAllOfBeforeItCase4MultipleValues2OffsetCase4,
                 *      LTC-00541-IT-insertAllOfBeforeItCase4MultipleValues3OffsetCase1,
                 *      LTC-00542-IT-insertAllOfBeforeItCase4MultipleValues3OffsetCase2,
                 *      LTC-00543-IT-insertAllOfBeforeItCase4MultipleValues3OffsetCase3,
                 *      LTC-00544-IT-insertAllOfBeforeItCase4MultipleValues3OffsetCase4
                 * }
                 *
                 * @public
                 */
                template <
                        typename __IterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                meta :: __IterableSizeAvailable < __IterableType > :: value
                        > = 0
                > auto insertAllOfBefore (
                        AbstractConstIterator   const & iterator,
                        __IterableType          const & iterable
                ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to insert multiple elements before an iterator of the iterable. This function varies whenever a RandomAccessIterator is given, to be able to efficiently determine
                 * the element count to insert. Otherwise, the distance will be computed iteratively. Insertion is done by extracting
                 * each from a given iterable and inserting each into the received addresses from the add before array request.
                 * @tparam __IterableType is the type of iterable given as parameter
                 * @param [in] iterator : AbstractConstIterator cref = Constant Reference to the iterator to insert before
                 * @param [in] iterable : __IterableType cref = Constant Reference to the iterable to extract the values from
                 * @exceptsafe if ElementType is exceptsafe constructible
                 *
                 * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                 *      LTC-00521-IT-insertAllOfBeforeItCase2MultipleValues1OffsetCase1,
                 *      LTC-00522-IT-insertAllOfBeforeItCase2MultipleValues1OffsetCase2,
                 *      LTC-00523-IT-insertAllOfBeforeItCase2MultipleValues1OffsetCase3,
                 *      LTC-00524-IT-insertAllOfBeforeItCase2MultipleValues1OffsetCase4,
                 *      LTC-00525-IT-insertAllOfBeforeItCase2MultipleValues2OffsetCase1,
                 *      LTC-00526-IT-insertAllOfBeforeItCase2MultipleValues2OffsetCase2,
                 *      LTC-00527-IT-insertAllOfBeforeItCase2MultipleValues2OffsetCase3,
                 *      LTC-00528-IT-insertAllOfBeforeItCase2MultipleValues2OffsetCase4,
                 *      LTC-00529-IT-insertAllOfBeforeItCase2MultipleValues3OffsetCase1,
                 *      LTC-00530-IT-insertAllOfBeforeItCase2MultipleValues3OffsetCase2,
                 *      LTC-00531-IT-insertAllOfBeforeItCase2MultipleValues3OffsetCase3,
                 *      LTC-00532-IT-insertAllOfBeforeItCase2MultipleValues3OffsetCase4,
                 *      LTC-00533-IT-insertAllOfBeforeItCase4MultipleValues1OffsetCase1,
                 *      LTC-00534-IT-insertAllOfBeforeItCase4MultipleValues1OffsetCase2,
                 *      LTC-00535-IT-insertAllOfBeforeItCase4MultipleValues1OffsetCase3,
                 *      LTC-00536-IT-insertAllOfBeforeItCase4MultipleValues1OffsetCase4,
                 *      LTC-00537-IT-insertAllOfBeforeItCase4MultipleValues2OffsetCase1,
                 *      LTC-00538-IT-insertAllOfBeforeItCase4MultipleValues2OffsetCase2,
                 *      LTC-00539-IT-insertAllOfBeforeItCase4MultipleValues2OffsetCase3,
                 *      LTC-00540-IT-insertAllOfBeforeItCase4MultipleValues2OffsetCase4,
                 *      LTC-00541-IT-insertAllOfBeforeItCase4MultipleValues3OffsetCase1,
                 *      LTC-00542-IT-insertAllOfBeforeItCase4MultipleValues3OffsetCase2,
                 *      LTC-00543-IT-insertAllOfBeforeItCase4MultipleValues3OffsetCase3,
                 *      LTC-00544-IT-insertAllOfBeforeItCase4MultipleValues3OffsetCase4
                 * }
                 *
                 * @public
                 */
                template <
                        typename __IterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                ! meta :: __IterableSizeAvailable < __IterableType > :: value
                        > = 0
                > auto insertAllOfBefore (
                        AbstractConstIterator   const & iterator,
                        __IterableType          const & iterable
                ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to insert multiple elements before an iterator of the iterable, done by extracting
                 * each from a given initializer list and inserting each into the received addresses from the add before array request.
                 * @tparam __IterableType is the type of iterable given as parameter
                 * @param [in] iterator : AbstractConstIterator cref = Constant Reference to the iterator to insert before
                 * @param [in] list : std :: initializer_list cref = Constant Reference to an initializer list to extract the values from
                 * @exceptsafe if ElementType is exceptsafe constructible
                 *
                 * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                 *      LTC-00521-IT-insertAllOfBeforeItCase2MultipleValues1OffsetCase1,
                 *      LTC-00522-IT-insertAllOfBeforeItCase2MultipleValues1OffsetCase2,
                 *      LTC-00523-IT-insertAllOfBeforeItCase2MultipleValues1OffsetCase3,
                 *      LTC-00524-IT-insertAllOfBeforeItCase2MultipleValues1OffsetCase4,
                 *      LTC-00525-IT-insertAllOfBeforeItCase2MultipleValues2OffsetCase1,
                 *      LTC-00526-IT-insertAllOfBeforeItCase2MultipleValues2OffsetCase2,
                 *      LTC-00527-IT-insertAllOfBeforeItCase2MultipleValues2OffsetCase3,
                 *      LTC-00528-IT-insertAllOfBeforeItCase2MultipleValues2OffsetCase4,
                 *      LTC-00529-IT-insertAllOfBeforeItCase2MultipleValues3OffsetCase1,
                 *      LTC-00530-IT-insertAllOfBeforeItCase2MultipleValues3OffsetCase2,
                 *      LTC-00531-IT-insertAllOfBeforeItCase2MultipleValues3OffsetCase3,
                 *      LTC-00532-IT-insertAllOfBeforeItCase2MultipleValues3OffsetCase4,
                 *      LTC-00533-IT-insertAllOfBeforeItCase4MultipleValues1OffsetCase1,
                 *      LTC-00534-IT-insertAllOfBeforeItCase4MultipleValues1OffsetCase2,
                 *      LTC-00535-IT-insertAllOfBeforeItCase4MultipleValues1OffsetCase3,
                 *      LTC-00536-IT-insertAllOfBeforeItCase4MultipleValues1OffsetCase4,
                 *      LTC-00537-IT-insertAllOfBeforeItCase4MultipleValues2OffsetCase1,
                 *      LTC-00538-IT-insertAllOfBeforeItCase4MultipleValues2OffsetCase2,
                 *      LTC-00539-IT-insertAllOfBeforeItCase4MultipleValues2OffsetCase3,
                 *      LTC-00540-IT-insertAllOfBeforeItCase4MultipleValues2OffsetCase4,
                 *      LTC-00541-IT-insertAllOfBeforeItCase4MultipleValues3OffsetCase1,
                 *      LTC-00542-IT-insertAllOfBeforeItCase4MultipleValues3OffsetCase2,
                 *      LTC-00543-IT-insertAllOfBeforeItCase4MultipleValues3OffsetCase3,
                 *      LTC-00544-IT-insertAllOfBeforeItCase4MultipleValues3OffsetCase4
                 * }
                 *
                 * @public
                 */
                template <
                        typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        > = 0
                > auto insertAllOfBefore (
                        AbstractConstIterator                       const & iterator,
                        std :: initializer_list < __ElementType >   const & list
                ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to insert multiple elements after an iterator of the iterable. This function varies whenever a RandomAccessIterator is given, to be able to efficiently determine
                 * the element count to insert. Otherwise, the distance will be computed iteratively. Insertion is done by extracting
                 * each from a given iterable and inserting each into the received addresses from the add after array request.
                 * @tparam __IterableType is the type of iterable given as parameter
                 * @param [in] iterator : AbstractConstIterator cref = Constant Reference to the iterator to insert after
                 * @param [in] iterable : __IterableType cref = Constant Reference to the iterable to extract the values from
                 * @exceptsafe if ElementType is exceptsafe constructible
                 *
                 * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                 *      LTC-00569-IT-insertAllOfAfterItCase2MultipleValues1OffsetCase1,
                 *      LTC-00570-IT-insertAllOfAfterItCase2MultipleValues1OffsetCase2,
                 *      LTC-00571-IT-insertAllOfAfterItCase2MultipleValues1OffsetCase3,
                 *      LTC-00572-IT-insertAllOfAfterItCase2MultipleValues1OffsetCase4,
                 *      LTC-00573-IT-insertAllOfAfterItCase2MultipleValues2OffsetCase1,
                 *      LTC-00574-IT-insertAllOfAfterItCase2MultipleValues2OffsetCase2,
                 *      LTC-00575-IT-insertAllOfAfterItCase2MultipleValues2OffsetCase3,
                 *      LTC-00576-IT-insertAllOfAfterItCase2MultipleValues2OffsetCase4,
                 *      LTC-00577-IT-insertAllOfAfterItCase2MultipleValues3OffsetCase1,
                 *      LTC-00578-IT-insertAllOfAfterItCase2MultipleValues3OffsetCase2,
                 *      LTC-00579-IT-insertAllOfAfterItCase2MultipleValues3OffsetCase3,
                 *      LTC-00580-IT-insertAllOfAfterItCase2MultipleValues3OffsetCase4,
                 *      LTC-00581-IT-insertAllOfAfterItCase4MultipleValues1OffsetCase1,
                 *      LTC-00582-IT-insertAllOfAfterItCase4MultipleValues1OffsetCase2,
                 *      LTC-00583-IT-insertAllOfAfterItCase4MultipleValues1OffsetCase3,
                 *      LTC-00584-IT-insertAllOfAfterItCase4MultipleValues1OffsetCase4,
                 *      LTC-00585-IT-insertAllOfAfterItCase4MultipleValues2OffsetCase1,
                 *      LTC-00586-IT-insertAllOfAfterItCase4MultipleValues2OffsetCase2,
                 *      LTC-00587-IT-insertAllOfAfterItCase4MultipleValues2OffsetCase3,
                 *      LTC-00588-IT-insertAllOfAfterItCase4MultipleValues2OffsetCase4,
                 *      LTC-00589-IT-insertAllOfAfterItCase4MultipleValues3OffsetCase1,
                 *      LTC-00590-IT-insertAllOfAfterItCase4MultipleValues3OffsetCase2,
                 *      LTC-00591-IT-insertAllOfAfterItCase4MultipleValues3OffsetCase3,
                 *      LTC-00592-IT-insertAllOfAfterItCase4MultipleValues3OffsetCase4
                 * }
                 *
                 * @public
                 */
                template <
                        typename __IterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                meta :: __IterableSizeAvailable < __IterableType > :: value
                        > = 0
                > auto insertAllOfAfter (
                        AbstractConstIterator   const & iterator,
                        __IterableType          const & iterable
                ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to insert multiple elements before an iterator of the iterable. This function varies whenever a RandomAccessIterator is given, to be able to efficiently determine
                 * the element count to insert. Otherwise, the distance will be computed iteratively. Insertion is done by extracting
                 * each from a given iterable and inserting each into the received addresses from the add before array request.
                 * @tparam __IterableType is the type of iterable given as parameter
                 * @param [in] iterator : AbstractConstIterator cref = Constant Reference to the iterator to insert after
                 * @param [in] iterable : __IterableType cref = Constant Reference to the iterable to extract the values from
                 * @exceptsafe if ElementType is exceptsafe constructible
                 *
                 * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                 *      LTC-00569-IT-insertAllOfAfterItCase2MultipleValues1OffsetCase1,
                 *      LTC-00570-IT-insertAllOfAfterItCase2MultipleValues1OffsetCase2,
                 *      LTC-00571-IT-insertAllOfAfterItCase2MultipleValues1OffsetCase3,
                 *      LTC-00572-IT-insertAllOfAfterItCase2MultipleValues1OffsetCase4,
                 *      LTC-00573-IT-insertAllOfAfterItCase2MultipleValues2OffsetCase1,
                 *      LTC-00574-IT-insertAllOfAfterItCase2MultipleValues2OffsetCase2,
                 *      LTC-00575-IT-insertAllOfAfterItCase2MultipleValues2OffsetCase3,
                 *      LTC-00576-IT-insertAllOfAfterItCase2MultipleValues2OffsetCase4,
                 *      LTC-00577-IT-insertAllOfAfterItCase2MultipleValues3OffsetCase1,
                 *      LTC-00578-IT-insertAllOfAfterItCase2MultipleValues3OffsetCase2,
                 *      LTC-00579-IT-insertAllOfAfterItCase2MultipleValues3OffsetCase3,
                 *      LTC-00580-IT-insertAllOfAfterItCase2MultipleValues3OffsetCase4,
                 *      LTC-00581-IT-insertAllOfAfterItCase4MultipleValues1OffsetCase1,
                 *      LTC-00582-IT-insertAllOfAfterItCase4MultipleValues1OffsetCase2,
                 *      LTC-00583-IT-insertAllOfAfterItCase4MultipleValues1OffsetCase3,
                 *      LTC-00584-IT-insertAllOfAfterItCase4MultipleValues1OffsetCase4,
                 *      LTC-00585-IT-insertAllOfAfterItCase4MultipleValues2OffsetCase1,
                 *      LTC-00586-IT-insertAllOfAfterItCase4MultipleValues2OffsetCase2,
                 *      LTC-00587-IT-insertAllOfAfterItCase4MultipleValues2OffsetCase3,
                 *      LTC-00588-IT-insertAllOfAfterItCase4MultipleValues2OffsetCase4,
                 *      LTC-00589-IT-insertAllOfAfterItCase4MultipleValues3OffsetCase1,
                 *      LTC-00590-IT-insertAllOfAfterItCase4MultipleValues3OffsetCase2,
                 *      LTC-00591-IT-insertAllOfAfterItCase4MultipleValues3OffsetCase3,
                 *      LTC-00592-IT-insertAllOfAfterItCase4MultipleValues3OffsetCase4
                 * }
                 *
                 * @public
                 */
                template <
                        typename __IterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                ! meta :: __IterableSizeAvailable < __IterableType > :: value
                        > = 0
                > auto insertAllOfAfter (
                        AbstractConstIterator   const & iterator,
                        __IterableType          const & iterable
                ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to insert multiple elements after an iterator of the iterable, done by extracting
                 * each from a given initializer list and inserting each into the received addresses from the add after array request.
                 * @tparam __IterableType is the type of iterable given as parameter
                 * @param [in] iterator : AbstractConstIterator cref = Constant Reference to the iterator to insert after
                 * @param [in] list : std :: initializer_list cref = Constant Reference to an initializer list to extract the values from
                 * @exceptsafe if ElementType is exceptsafe constructible
                 *
                 * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                 *      LTC-00569-IT-insertAllOfAfterItCase2MultipleValues1OffsetCase1,
                 *      LTC-00570-IT-insertAllOfAfterItCase2MultipleValues1OffsetCase2,
                 *      LTC-00571-IT-insertAllOfAfterItCase2MultipleValues1OffsetCase3,
                 *      LTC-00572-IT-insertAllOfAfterItCase2MultipleValues1OffsetCase4,
                 *      LTC-00573-IT-insertAllOfAfterItCase2MultipleValues2OffsetCase1,
                 *      LTC-00574-IT-insertAllOfAfterItCase2MultipleValues2OffsetCase2,
                 *      LTC-00575-IT-insertAllOfAfterItCase2MultipleValues2OffsetCase3,
                 *      LTC-00576-IT-insertAllOfAfterItCase2MultipleValues2OffsetCase4,
                 *      LTC-00577-IT-insertAllOfAfterItCase2MultipleValues3OffsetCase1,
                 *      LTC-00578-IT-insertAllOfAfterItCase2MultipleValues3OffsetCase2,
                 *      LTC-00579-IT-insertAllOfAfterItCase2MultipleValues3OffsetCase3,
                 *      LTC-00580-IT-insertAllOfAfterItCase2MultipleValues3OffsetCase4,
                 *      LTC-00581-IT-insertAllOfAfterItCase4MultipleValues1OffsetCase1,
                 *      LTC-00582-IT-insertAllOfAfterItCase4MultipleValues1OffsetCase2,
                 *      LTC-00583-IT-insertAllOfAfterItCase4MultipleValues1OffsetCase3,
                 *      LTC-00584-IT-insertAllOfAfterItCase4MultipleValues1OffsetCase4,
                 *      LTC-00585-IT-insertAllOfAfterItCase4MultipleValues2OffsetCase1,
                 *      LTC-00586-IT-insertAllOfAfterItCase4MultipleValues2OffsetCase2,
                 *      LTC-00587-IT-insertAllOfAfterItCase4MultipleValues2OffsetCase3,
                 *      LTC-00588-IT-insertAllOfAfterItCase4MultipleValues2OffsetCase4,
                 *      LTC-00589-IT-insertAllOfAfterItCase4MultipleValues3OffsetCase1,
                 *      LTC-00590-IT-insertAllOfAfterItCase4MultipleValues3OffsetCase2,
                 *      LTC-00591-IT-insertAllOfAfterItCase4MultipleValues3OffsetCase3,
                 *      LTC-00592-IT-insertAllOfAfterItCase4MultipleValues3OffsetCase4
                 * }
                 *
                 * @public
                 */
                template <
                        typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        > = 0
                > auto insertAllOfAfter (
                        AbstractConstIterator                       const & iterator,
                        std :: initializer_list < __ElementType >   const & list
                ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to insert multiple elements before an iterator of the iterable
                 * by extracting each from a given iterator range and inserting each into the addresses received
                 * from the new before array request.
                 * An extra parameter is available to set the number of values between the given iterators,
                 * either as a limit, or as to avoid the computation of the distance between the two iterators.
                 * @tparam __IteratorType is the type of given iterators
                 * @param [in] iterator : AbstractConstIterator cref = Constant Reference to the iterator to insert before
                 * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
                 * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
                 * @param [in] count : Size = Distance between begin and end iterators. If 0, distance will be computed
                 * by subtraction, if iterator type is random, or by iteration otherwise
                 * @exceptsafe if ElementType is exceptsafe constructible
                 *
                 * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                 *      LTC-00521-IT-insertAllOfBeforeItCase2MultipleValues1OffsetCase1,
                 *      LTC-00522-IT-insertAllOfBeforeItCase2MultipleValues1OffsetCase2,
                 *      LTC-00523-IT-insertAllOfBeforeItCase2MultipleValues1OffsetCase3,
                 *      LTC-00524-IT-insertAllOfBeforeItCase2MultipleValues1OffsetCase4,
                 *      LTC-00525-IT-insertAllOfBeforeItCase2MultipleValues2OffsetCase1,
                 *      LTC-00526-IT-insertAllOfBeforeItCase2MultipleValues2OffsetCase2,
                 *      LTC-00527-IT-insertAllOfBeforeItCase2MultipleValues2OffsetCase3,
                 *      LTC-00528-IT-insertAllOfBeforeItCase2MultipleValues2OffsetCase4,
                 *      LTC-00529-IT-insertAllOfBeforeItCase2MultipleValues3OffsetCase1,
                 *      LTC-00530-IT-insertAllOfBeforeItCase2MultipleValues3OffsetCase2,
                 *      LTC-00531-IT-insertAllOfBeforeItCase2MultipleValues3OffsetCase3,
                 *      LTC-00532-IT-insertAllOfBeforeItCase2MultipleValues3OffsetCase4,
                 *      LTC-00533-IT-insertAllOfBeforeItCase4MultipleValues1OffsetCase1,
                 *      LTC-00534-IT-insertAllOfBeforeItCase4MultipleValues1OffsetCase2,
                 *      LTC-00535-IT-insertAllOfBeforeItCase4MultipleValues1OffsetCase3,
                 *      LTC-00536-IT-insertAllOfBeforeItCase4MultipleValues1OffsetCase4,
                 *      LTC-00537-IT-insertAllOfBeforeItCase4MultipleValues2OffsetCase1,
                 *      LTC-00538-IT-insertAllOfBeforeItCase4MultipleValues2OffsetCase2,
                 *      LTC-00539-IT-insertAllOfBeforeItCase4MultipleValues2OffsetCase3,
                 *      LTC-00540-IT-insertAllOfBeforeItCase4MultipleValues2OffsetCase4,
                 *      LTC-00541-IT-insertAllOfBeforeItCase4MultipleValues3OffsetCase1,
                 *      LTC-00542-IT-insertAllOfBeforeItCase4MultipleValues3OffsetCase2,
                 *      LTC-00543-IT-insertAllOfBeforeItCase4MultipleValues3OffsetCase3,
                 *      LTC-00544-IT-insertAllOfBeforeItCase4MultipleValues3OffsetCase4
                 * }
                 *
                 * @public
                 */
                template < typename __OtherIteratorType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto insertAllOfBefore (
                        AbstractConstIterator   const & iterator,
                        __OtherIteratorType     const & begin,
                        __OtherIteratorType     const & end,
                        Size                            count = 0ULL
                ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to insert multiple elements after an iterator of the iterable
                 * by extracting each from a given iterator range and inserting each into the addresses received
                 * from the new after array request.
                 * An extra parameter is available to set the number of values between the given iterators,
                 * either as a limit, or as to avoid the computation of the distance between the two iterators.
                 * @tparam __IteratorType is the type of given iterators
                 * @param [in] iterator : AbstractConstIterator cref = Constant Reference to the iterator to insert after
                 * @param [in] begin : __IteratorType cref = Constant Reference to the begin iterator of the range
                 * @param [in] end : __IteratorType cref = Constant Reference to the end iterator of the range
                 * @param [in] count : Size = Distance between begin and end iterators. If 0, distance will be computed
                 * by subtraction, if iterator type is random, or by iteration otherwise
                 * @exceptsafe if ElementType is exceptsafe constructible
                 *
                 * @test Suite: LTS-00001, Group: LTG-00400-RI, Test Cases: {
                 *      LTC-00569-IT-insertAllOfAfterItCase2MultipleValues1OffsetCase1,
                 *      LTC-00570-IT-insertAllOfAfterItCase2MultipleValues1OffsetCase2,
                 *      LTC-00571-IT-insertAllOfAfterItCase2MultipleValues1OffsetCase3,
                 *      LTC-00572-IT-insertAllOfAfterItCase2MultipleValues1OffsetCase4,
                 *      LTC-00573-IT-insertAllOfAfterItCase2MultipleValues2OffsetCase1,
                 *      LTC-00574-IT-insertAllOfAfterItCase2MultipleValues2OffsetCase2,
                 *      LTC-00575-IT-insertAllOfAfterItCase2MultipleValues2OffsetCase3,
                 *      LTC-00576-IT-insertAllOfAfterItCase2MultipleValues2OffsetCase4,
                 *      LTC-00577-IT-insertAllOfAfterItCase2MultipleValues3OffsetCase1,
                 *      LTC-00578-IT-insertAllOfAfterItCase2MultipleValues3OffsetCase2,
                 *      LTC-00579-IT-insertAllOfAfterItCase2MultipleValues3OffsetCase3,
                 *      LTC-00580-IT-insertAllOfAfterItCase2MultipleValues3OffsetCase4,
                 *      LTC-00581-IT-insertAllOfAfterItCase4MultipleValues1OffsetCase1,
                 *      LTC-00582-IT-insertAllOfAfterItCase4MultipleValues1OffsetCase2,
                 *      LTC-00583-IT-insertAllOfAfterItCase4MultipleValues1OffsetCase3,
                 *      LTC-00584-IT-insertAllOfAfterItCase4MultipleValues1OffsetCase4,
                 *      LTC-00585-IT-insertAllOfAfterItCase4MultipleValues2OffsetCase1,
                 *      LTC-00586-IT-insertAllOfAfterItCase4MultipleValues2OffsetCase2,
                 *      LTC-00587-IT-insertAllOfAfterItCase4MultipleValues2OffsetCase3,
                 *      LTC-00588-IT-insertAllOfAfterItCase4MultipleValues2OffsetCase4,
                 *      LTC-00589-IT-insertAllOfAfterItCase4MultipleValues3OffsetCase1,
                 *      LTC-00590-IT-insertAllOfAfterItCase4MultipleValues3OffsetCase2,
                 *      LTC-00591-IT-insertAllOfAfterItCase4MultipleValues3OffsetCase3,
                 *      LTC-00592-IT-insertAllOfAfterItCase4MultipleValues3OffsetCase4
                 * }
                 *
                 * @public
                 */
                template < typename __OtherIteratorType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto insertAllOfAfter (
                        AbstractConstIterator   const & iterator,
                        __OtherIteratorType     const & begin,
                        __OtherIteratorType     const & end,
                        Size                            count = 0ULL
                ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool;
            };


            /**
             * @interface Interface for creating Local Const-Iterator-Relative-To Insertion requests, inserting / emplacing elements before or after a given iterator
             * @tparam __ReceiverType is the type of implementor class, used for static polymorphism.
             * Implementor is required to either implement an appropriate dispatcher ( __ListServerDispatcher or lower
             * in hierarchy ) or provide an equivalent set of member functions - __newBeforeConstAddress,
             *      __newBeforeConstAddressArray, __newAfterConstAddress,
             *      __newAfterConstAddressArray - to the one provided by the dispatcher
             *
             * @tparam __ElementType is the type of elements contained into the Object
             * @tparam __ReturnType is the type returned by the singular insertion functions
             *
             * @test Suite: TBA, Group: TBA, Test Cases: TBA
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __ReceiverType,                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ElementType,                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __IteratorType                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > class __LocalConstIteratorRelativeInsertionPrimitiveClient {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @typedef alias for __ElementType template parameter
                 * @private
                 */
                using ElementType       = __ElementType;

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @typedef alias for Const Iterator type
                 * @private
                 */
                using ConstIterator = __IteratorType;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to create a new element before a given iterator by copy
                 * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a copy constructor
                 * @param [in] iterator : ConstIterator cref = Constant Reference to the iterator to insert before
                 * @param [in] element : ElementType cref = Constant Reference to the element to be inserted via copy
                 * @exceptsafe if ElementType's Copy Constructor is exceptsafe
                 * @return bool = true if insertion was successful, false otherwise
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 *
                 * @public
                 */
                template <
                        typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        > = 0
                > auto insertBefore (
                        ConstIterator   const & iterator,
                        ElementType     const & element
                ) noexcept ( noexcept ( ElementType ( element ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to create a new element before a given iterator by move
                 * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a move constructor
                 * @param [in] iterator : ConstIterator cref = Constant Reference to the iterator to insert before
                 * @param [in, out] element : ElementType mref = Move Reference to the element to be inserted via move
                 * @exceptsafe if ElementType's Move Constructor is exceptsafe
                 * @return bool = true if insertion was successful, false otherwise
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 *
                 * @public
                 */
                template <
                        typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveConstructible < __TElementType > ()
                        > = 0
                > auto insertBefore (
                        ConstIterator    const & iterator,
                        ElementType           && element
                ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to create a new element after a given iterator by copy
                 * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a copy constructor
                 * @param [in] iterator : ConstIterator cref = Constant Reference to the iterator to insert after
                 * @param [in] element : ElementType cref = Constant Reference to the element to be inserted via copy
                 * @exceptsafe if ElementType's Copy Constructor is exceptsafe
                 * @return bool = true if insertion was successful, false otherwise
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 *
                 * @public
                 */
                template <
                        typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        > = 0
                > auto insertAfter (
                        ConstIterator   const & iterator,
                        ElementType     const & element
                ) noexcept ( noexcept ( ElementType ( element ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to create a new element after a given iterator by move
                 * @tparam __TElementType is an alias to __ElementType, used to disable the function when the given type does not implement a move constructor
                 * @param [in] iterator : ConstIterator cref = Constant Reference to the iterator to insert after
                 * @param [in, out] element : ElementType mref = Move Reference to the element to be inserted via move
                 * @exceptsafe if ElementType's Copy Constructor is exceptsafe
                 * @return bool = true if insertion was successful, false otherwise
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 *
                 * @public
                 */
                template <
                        typename __TElementType = ElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isMoveConstructible < __TElementType > ()
                        > = 0
                > auto insertAfter (
                        ConstIterator    const & iterator,
                        ElementType           && element
                ) noexcept ( noexcept ( ElementType ( std :: move ( element ) ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to create a new element before a given iterator by emplacement
                 * @tparam __EmplaceArgumentTypes is the pack of argument types passed to the constructor
                 * @param [in] iterator : ConstIterator cref = Constant Reference to the iterator to insert before
                 * @param [in] parameters : __EmplaceArgumentTypes fref ... = Pack of forwarding references passed to the constructor
                 * @exceptsafe if ElementType's constructor for given parameters is exceptsafe
                 * @return bool = true if insertion was successful, false otherwise
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 *
                 * @public
                 */
                template < typename ... __EmplaceArgumentTypes > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto emplaceBefore (
                        ConstIterator                const &     iterator,
                        __EmplaceArgumentTypes            && ... parameters
                ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to create a new element after a given iterator by emplacement
                 * @tparam __EmplaceArgumentTypes is the pack of argument types passed to the constructor
                 * @param [in] iterator : ConstIterator cref = Constant Reference to the iterator to insert after
                 * @param [in] parameters : __EmplaceArgumentTypes fref ... = Pack of forwarding references passed to the constructor
                 * @exceptsafe if ElementType's constructor for given parameters is exceptsafe
                 * @return bool = true if insertion was successful, false otherwise
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 *
                 * @public
                 */
                template < typename ... __EmplaceArgumentTypes > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto emplaceAfter (
                        ConstIterator                const &     iterator,
                        __EmplaceArgumentTypes            && ... parameters
                ) noexcept ( noexcept ( ElementType ( std :: forward < __EmplaceArgumentTypes > ( parameters ) ... ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to insert multiple elements before a given iterator by creating a new before array request
                 * @tparam __ArgumentTypes is the type pack of the values to be inserted
                 * @param [in] iterator : ConstIterator cref = Constant Reference to the iterator to insert before
                 * @param [in] values : __ArgumentTypes fref ... = Pack of forwarding elements to values, each of the pack to be transformed into an Element via construction and inserted
                 * @exceptsafe if ElementType is exceptsafe constructible with each given value
                 * @return true if insertion was successful, false otherwise
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 *
                 * @public
                 */
                template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto insertAllBefore (
                        ConstIterator            const &     iterator,
                        __ArgumentTypes               && ... values
                ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to insert multiple elements after a given iterator by creating a new before array request
                 * @tparam __ArgumentTypes is the type pack of the values to be inserted
                 * @param [in] iterator : ConstIterator cref = Constant Reference to the iterator to insert after
                 * @param [in] values : __ArgumentTypes fref ... = Pack of forwarding elements to values, each of the pack to be transformed into an Element via construction and inserted
                 * @exceptsafe if ElementType is exceptsafe constructible with each given value
                 * @return true if insertion was successful, false otherwise
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 *
                 * @public
                 */
                template < typename ... __ArgumentTypes > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto insertAllAfter (
                        ConstIterator            const &     iterator,
                        __ArgumentTypes               && ... values
                ) noexcept ( __ConstructExceptSpecMultiple < __ElementType, __ArgumentTypes ... > :: value ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to insert multiple elements before an iterator of the iterable. This function varies whenever a RandomAccessIterator is given, to be able to efficiently determine
                 * the element count to insert. Otherwise, the distance will be computed iteratively. Insertion is done by extracting
                 * each from a given iterable and inserting each into the received addresses from the add before array request.
                 * @tparam __IterableType is the type of iterable given as parameter
                 * @param [in] iterator : ConstIterator cref = Constant Reference to the iterator to insert before
                 * @param [in] iterable : __IterableType cref = Constant Reference to the iterable to extract the values from
                 * @exceptsafe if ElementType is exceptsafe constructible
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 *
                 * @public
                 */
                template <
                        typename __IterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                meta :: __IterableSizeAvailable < __IterableType > :: value
                        > = 0
                > auto insertAllOfBefore (
                        ConstIterator   const & iterator,
                        __IterableType  const & iterable
                ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to insert multiple elements before an iterator of the iterable. This function varies whenever a RandomAccessIterator is given, to be able to efficiently determine
                 * the element count to insert. Otherwise, the distance will be computed iteratively. Insertion is done by extracting
                 * each from a given iterable and inserting each into the received addresses from the add before array request.
                 * @tparam __IterableType is the type of iterable given as parameter
                 * @param [in] iterator : ConstIterator cref = Constant Reference to the iterator to insert before
                 * @param [in] iterable : __IterableType cref = Constant Reference to the iterable to extract the values from
                 * @exceptsafe if ElementType is exceptsafe constructible
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 *
                 * @public
                 */
                template <
                        typename __IterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                ! meta :: __IterableSizeAvailable < __IterableType > :: value
                        > = 0
                > auto insertAllOfBefore (
                        ConstIterator   const & iterator,
                        __IterableType  const & iterable
                ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to insert multiple elements before an iterator of the iterable, done by extracting
                 * each from a given initializer list and inserting each into the received addresses from the add before array request.
                 * @tparam __IterableType is the type of iterable given as parameter
                 * @param [in] iterator : ConstIterator cref = Constant Reference to the iterator to insert before
                 * @param [in] list : std :: initializer_list cref = Constant Reference to an initializer list to extract the values from
                 * @exceptsafe if ElementType is exceptsafe constructible
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 *
                 * @public
                 */
                template <
                        typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        > = 0
                > auto insertAllOfBefore (
                        ConstIterator                               const & iterator,
                        std :: initializer_list < __ElementType >   const & list
                ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to insert multiple elements after an iterator of the iterable. This function varies whenever a RandomAccessIterator is given, to be able to efficiently determine
                 * the element count to insert. Otherwise, the distance will be computed iteratively. Insertion is done by extracting
                 * each from a given iterable and inserting each into the received addresses from the add after array request.
                 * @tparam __IterableType is the type of iterable given as parameter
                 * @param [in] iterator : ConstIterator cref = Constant Reference to the iterator to insert after
                 * @param [in] iterable : __IterableType cref = Constant Reference to the iterable to extract the values from
                 * @exceptsafe if ElementType is exceptsafe constructible
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 *
                 * @public
                 */
                template <
                        typename __IterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                meta :: __IterableSizeAvailable < __IterableType > :: value
                        > = 0
                > auto insertAllOfAfter (
                        ConstIterator           const & iterator,
                        __IterableType          const & iterable
                ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to insert multiple elements before an iterator of the iterable. This function varies whenever a RandomAccessIterator is given, to be able to efficiently determine
                 * the element count to insert. Otherwise, the distance will be computed iteratively. Insertion is done by extracting
                 * each from a given iterable and inserting each into the received addresses from the add before array request.
                 * @tparam __IterableType is the type of iterable given as parameter
                 * @param [in] iterator : ConstIterator cref = Constant Reference to the iterator to insert after
                 * @param [in] iterable : __IterableType cref = Constant Reference to the iterable to extract the values from
                 * @exceptsafe if ElementType is exceptsafe constructible
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 *
                 * @public
                 */
                template <
                        typename __IterableType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                ! meta :: __IterableSizeAvailable < __IterableType > :: value
                        > = 0
                > auto insertAllOfAfter (
                        ConstIterator           const & iterator,
                        __IterableType          const & iterable
                ) noexcept ( noexcept ( ElementType ( * iterable.begin() ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to insert multiple elements after an iterator of the iterable, done by extracting
                 * each from a given initializer list and inserting each into the received addresses from the add after array request.
                 * @tparam __IterableType is the type of iterable given as parameter
                 * @param [in] iterator : ConstIterator cref = Constant Reference to the iterator to insert after
                 * @param [in] list : std :: initializer_list cref = Constant Reference to an initializer list to extract the values from
                 * @exceptsafe if ElementType is exceptsafe constructible
                 *
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 *
                 * @public
                 */
                template <
                        typename __TElementType = __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        cds :: meta :: EnableIf <
                                cds :: meta :: isCopyConstructible < __TElementType > ()
                        > = 0
                > auto insertAllOfAfter (
                        ConstIterator                               const & iterator,
                        std :: initializer_list < __ElementType >   const & list
                ) noexcept ( noexcept ( ElementType ( * list.begin() ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to insert multiple elements before an iterator of the iterable
                 * by extracting each from a given iterator range and inserting each into the addresses received
                 * from the new before array request.
                 * An extra parameter is available to set the number of values between the given iterators,
                 * either as a limit, or as to avoid the computation of the distance between the two iterators.
                 * @tparam __IteratorType is the type of given iterators
                 * @param [in] iterator : ConstIterator cref = Constant Reference to the iterator to insert before
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
                template < typename __OtherIteratorType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto insertAllOfBefore (
                        ConstIterator           const & iterator,
                        __OtherIteratorType     const & begin,
                        __OtherIteratorType     const & end,
                        Size                            count = 0ULL
                ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to insert multiple elements after an iterator of the iterable
                 * by extracting each from a given iterator range and inserting each into the addresses received
                 * from the new after array request.
                 * An extra parameter is available to set the number of values between the given iterators,
                 * either as a limit, or as to avoid the computation of the distance between the two iterators.
                 * @tparam __IteratorType is the type of given iterators
                 * @param [in] iterator : ConstIterator cref = Constant Reference to the iterator to insert after
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
                template < typename __OtherIteratorType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                auto insertAllOfAfter (
                        ConstIterator           const & iterator,
                        __OtherIteratorType     const & begin,
                        __OtherIteratorType     const & end,
                        Size                            count = 0ULL
                ) noexcept ( noexcept ( ElementType ( * begin ) ) ) -> bool;
            };

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_CONST_ITERATOR_RELATIVE_INSERTION_PRIMITIVE_CLIENT_HPP__ */
