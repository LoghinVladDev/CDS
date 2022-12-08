/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_FORWARD_DELEGATE_WRAPPER_ITERATOR_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_FORWARD_DELEGATE_WRAPPER_ITERATOR_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include "../iterator/IteratorModel.hpp"
#include "AbstractDelegateIterator.hpp"
#include "AbstractDelegateWrapperIterator.hpp"

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @class Wrapper Iterator type for Abstract Iterators that satisfy the 'Forward Iterable' Model
             * @tparam __ElementType is the type of the enclosed element at the wrapped abstract iterator. Must not be decayed, as it can represent a const iterator
             *
             * @extends __AbstractDelegateWrapperIterator - base class containing Collection information
             * @implements meta :: ForwardIterator - model
             *
             * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
             * @namespace cds :: experimental :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            class __CDS_InheritsEBOs __ForwardDelegateWrapperIterator : /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    public __AbstractDelegateWrapperIterator < __ElementType >,
                    public meta :: ForwardIterator {

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @typedef Alias for the __ElementType template parameter
                 * @protected
                 * */
                using ElementType = __ElementType;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Default Constructor, constexpr
                 * @exceptsafe
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00054-IT-e_begin_end, CTC-00055-IT-e_cbegin_cend, CTC-00056-IT-e_emptyRange }
                 * @public
                 */
                constexpr __ForwardDelegateWrapperIterator () noexcept;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Constructor used in creating wrapper iterators in Delegate Clients.
                 * @param [in] pOwner : Object cptr = Immutable Pointer to the owner object, used to identify iterators passed to functions from outside collection.
                 * @param [in] pDelegate : __AbstractDelegateIterator = Pointer to the delegate that is to be wrapped. Ownership of the wrapped abstract iterator will be granted to the wrapper.
                 * @exceptsafe
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @public
                 */
                constexpr __ForwardDelegateWrapperIterator (
                        Object                                          const * pOwner,
                        __AbstractDelegateIterator < __ElementType >          * pDelegate
                ) noexcept;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Copy Constructor.
                 * @param [in] iterator : __ForwardDelegateWrapperIterator cref = Constant Reference to the Iterator to copy from. Will create a new abstract iterator for the new wrapper to own.
                 * @exceptsafe
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00051-IT-range }
                 * @public
                 */
                __ForwardDelegateWrapperIterator (
                        __ForwardDelegateWrapperIterator const & iterator
                ) noexcept;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Move Constructor.
                 * @param [in, out] iterator : __ForwardDelegateWrapperIterator mref = Move Reference to the Iterator to acquire items from. Ownership of the abstract wrapped iterator passed to the newly created wrapper. Given iterator as parameter should not be used anymore, as it will not contain and wrapped abstract iterator
                 * @exceptsafe
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All, as move will be called by copy elision
                 * @public
                 */
                constexpr __ForwardDelegateWrapperIterator (
                        __ForwardDelegateWrapperIterator && iterator
                ) noexcept;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Destructor. Releases ownership of the owned wrapped abstract iterator, if any owned
                 * @exceptsafe
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @public
                 */
                ~__ForwardDelegateWrapperIterator () noexcept override;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Copy Assignment Operator.
                 * @param [in] iterator : __ForwardDelegateWrapperIterator cref = Constant Reference to the Iterator to copy from. Will create a new abstract iterator for the left hand wrapper to own.
                 * @exceptsafe
                 * @return __ForwardDelegateWrapperIterator ref = Reference to the newly modified left-hand iterator
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00051-IT-range }
                 * @public
                 */
                auto operator = (
                        __ForwardDelegateWrapperIterator const & iterator
                ) noexcept -> __ForwardDelegateWrapperIterator &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Move Assignment Operator.
                 * @param [in, out] iterator : __ForwardDelegateWrapperIterator mref = Move Reference to the Iterator to move from. Will transfer ownership of the wrapped abstract iterator from right hand wrapper to left hand wrapper.
                 * @exceptsafe
                 * @return __ForwardDelegateWrapperIterator ref = Reference to the newly modified left-hand iterator
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00051-IT-range }
                 * @public
                 */
                auto operator = (
                        __ForwardDelegateWrapperIterator && iterator
                ) noexcept -> __ForwardDelegateWrapperIterator &;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Equality Comparison Operator.
                 * @param [in] iterator : __ForwardDelegateWrapperIterator cref = Constant Reference to the Iterator to compare current Iterator to
                 * @exceptsafe
                 * @return bool = true if iterators are equal, false otherwise
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @public
                 */
                __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto operator == ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */
                        __ForwardDelegateWrapperIterator const & iterator
                ) const noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Inequality Comparison Operator.
                 * @param [in] iterator : __ForwardDelegateWrapperIterator cref = Constant Reference to the Iterator to compare current Iterator to
                 * @exceptsafe
                 * @return bool = false if iterators are equal, true otherwise
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @public
                 */
                __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto operator != (
                        __ForwardDelegateWrapperIterator const & iterator
                ) const noexcept -> bool;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Prefix Increment Operator. Operation will advance iterator with one position. Postfix not indicated as it will create a copy -> allocation of new abstract iterator.
                 * To prevent generation of range-based loop using postfixed increment, it is not generated.
                 * @exceptsafe
                 * @return __ForwardDelegateWrapperIterator ref = Reference to the modified iterator
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @public
                 */
                __CDS_cpplang_ConstexprPureAbstract auto operator ++ () noexcept -> __ForwardDelegateWrapperIterator &;
            };

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_FORWARD_DELEGATE_WRAPPER_ITERATOR_HPP__ */
