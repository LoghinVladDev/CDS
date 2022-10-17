/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_ABSTRACT_DELEGATE_WRAPPER_ITERATOR_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_ABSTRACT_DELEGATE_WRAPPER_ITERATOR_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @class Abstract Wrapper Iterator type for Abstract Iterators that does not satisfy any Iterable Model. It is only a generic container
             * @tparam __ElementType is the type of the enclosed element at the wrapped abstract iterator. Must not be decayed, as it can represent a const iterator
             *
             * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
             * @namespace cds :: experimental :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            class __AbstractDelegateWrapperIterator {   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                /* Client that requires the use of private objects to acquire contained delegate address for iterator extraction */
                template < typename, typename >
                friend class __AbstractIteratorRelativeInsertionPrimitiveClient;         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                /* Client that requires the use of private objects to acquire contained delegate address for iterator extraction */
                template < typename, typename >
                friend class __AbstractConstIteratorRelativeInsertionPrimitiveClient;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                /* Client that requires the use of private objects to acquire contained delegate address for iterator extraction */
                template < typename, typename >
                friend class __AbstractIteratorRemovePrimitiveClient;                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                /* Client that requires the use of private objects to acquire contained delegate address for iterator extraction */
                template < typename, typename >
                friend class __AbstractConstIteratorRemovePrimitiveClient;               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief The iterator owner object
                 * @private
                 * */
                Object                                          const * _pOwner     { nullptr };

            private:    /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief The abstract delegate contained by the wrapper
                 * @private
                 * */
                __AbstractDelegateIterator < __ElementType >          * _pDelegate  { nullptr };

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Default Constructor, constexpr
                 * @exceptsafe
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00054-IT-e_begin_end, CTC-00055-IT-e_cbegin_cend, CTC-00056-IT-e_emptyRange }
                 * @protected
                 */
                constexpr __AbstractDelegateWrapperIterator() noexcept;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Constructor used in creating wrapper iterators in Delegate Clients.
                 * @param [in] pOwner : Object cptr = Immutable Pointer to the owner object, used to identify iterators passed to functions from outside collection.
                 * @param [in] pDelegate : __AbstractDelegateIterator = Pointer to the delegate that is to be wrapped. Ownership of the wrapped abstract iterator will be granted to the wrapper.
                 * @exceptsafe
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @protected
                 */
                constexpr __AbstractDelegateWrapperIterator(
                        Object                                          const * pOwner,
                        __AbstractDelegateIterator < __ElementType >          * pDelegate
                ) noexcept;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Copy Constructor.
                 * @param [in] iterator : __AbstractDelegateWrapperIterator cref = Constant Reference to the Iterator to copy from. Will create a new abstract iterator for the new wrapper to own.
                 * @exceptsafe
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00051-IT-range }
                 * @protected
                 */
                __AbstractDelegateWrapperIterator (
                        __AbstractDelegateWrapperIterator const & iterator
                ) noexcept;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Move Constructor.
                 * @param [in, out] iterator : __AbstractDelegateWrapperIterator mref = Move Reference to the Iterator to acquire items from. Ownership of the abstract wrapped iterator passed to the newly created wrapper. Given iterator as parameter should not be used anymore, as it will not contain and wrapped abstract iterator
                 * @exceptsafe
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All, as move will be called by copy elision
                 * @protected
                 */
                constexpr __AbstractDelegateWrapperIterator (
                        __AbstractDelegateWrapperIterator && iterator
                ) noexcept;

            public:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Deleted Copy Assignment Operator, constexpr
                 * @param iterator : __AbstractDelegateWrapperIterator cref = Constant Reference to the delegate to copy data from
                 * @exceptsafe
                 * @return __AbstractDelegateWrapperIterator ref = Reference to the modified object
                 * @test N/A
                 * @protected
                 */
                auto operator = (
                        __AbstractDelegateWrapperIterator const & /* iterator */
                ) noexcept -> __AbstractDelegateWrapperIterator & = delete;

            public:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Deleted Move Assignment Operator, constexpr
                 * @param iterator : __AbstractDelegateWrapperIterator mref = Move Reference to the delegate to move data from
                 * @exceptsafe
                 * @return __AbstractDelegateWrapperIterator ref = Reference to the modified object
                 * @test N/A
                 * @protected
                 */
                auto operator = (
                        __AbstractDelegateWrapperIterator && /* iterator */
                ) noexcept -> __AbstractDelegateWrapperIterator & = delete;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Virtual Destructor. Releases ownership of the owned wrapped abstract iterator, if any owned
                 * @exceptsafe
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @public
                 */
                virtual ~__AbstractDelegateWrapperIterator() noexcept;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to verify if iterator was obtained from the given Object
                 * @param [in] pObject : Object cptr = Address to an Immutable Object
                 * @exceptsafe
                 * @return bool = true if iterator was created from the given object, false otherwise
                 * @test Suite: CTS-00001, Group: CTG-00350-RAIT, Test Cases: All
                 * @test Suite: CTS-00001, Group: CTG-00400-RB, Test Cases: All
                 * @test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: All
                 * @public
                 */
                __CDS_NoDiscard constexpr auto of (
                        Object const * pObject
                ) const noexcept -> bool;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Advance Function. Operation will advance iterator with one position, in requested direction.
                 * @param [in] direction : __IteratorAdvanceDirection = the direction to advance the iterator in
                 * @exceptsafe
                 * @return __AbstractDelegateWrapperIterator ref = Reference to the modified iterator
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @protected
                 */
                __CDS_cpplang_ConstexprPureAbstract auto advance (
                        __IteratorAdvanceDirection direction
                ) noexcept -> __AbstractDelegateWrapperIterator &;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Equality Function.
                 * @param [in] iterator : __AbstractDelegateWrapperIterator cref = Constant Reference to the Iterator to compare current Iterator to
                 * @exceptsafe
                 * @return bool = true if iterators are equal, false otherwise
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @protected
                 */
                __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto equals ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */
                        __AbstractDelegateWrapperIterator const & iterator
                ) const noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Validity Function. Checks if an iterator has an abstract wrapped iterator and it is in bounds.
                 * @exceptsafe
                 * @return bool = true if iterator is valid, false otherwise
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @public
                 */
                __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto valid () const noexcept -> bool; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Value Acquisition Function. Will acquire value at given iterator.
                 * @exceptsafe
                 * @return __ElementType ref = Reference to element at iterator
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @protected
                 */
                __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto value () const noexcept -> __ElementType &;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Copy Function.
                 * @param [in] iterator : __AbstractDelegateWrapperIterator cref = Constant Reference to the Iterator to copy from. Will create a new abstract iterator for the left hand wrapper to own.
                 * @exceptsafe
                 * @return __AbstractDelegateWrapperIterator ref = Reference to the newly modified left-hand iterator
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00051-IT-range }
                 * @protected
                 */
                auto copy (
                        __AbstractDelegateWrapperIterator const & iterator
                ) noexcept -> __AbstractDelegateWrapperIterator &;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Move Assignment Operator.
                 * @param [in, out] iterator : __AbstractDelegateWrapperIterator mref = Move Reference to the Iterator to move from. Will transfer ownership of the wrapped abstract iterator from right hand wrapper to left hand wrapper.
                 * @exceptsafe
                 * @return __AbstractDelegateWrapperIterator ref = Reference to the newly modified left-hand iterator
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00051-IT-range }
                 * @protected
                 */
                auto move (
                        __AbstractDelegateWrapperIterator && iterator
                ) noexcept -> __AbstractDelegateWrapperIterator &;
            };

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_ABSTRACT_DELEGATE_WRAPPER_ITERATOR_HPP__ */
