/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_FORWARD_DELEGATE_WRAPPER_ITERATOR_HPP__
#define __CDS_SHARED_FORWARD_DELEGATE_WRAPPER_ITERATOR_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include "../iterator/IteratorModel.hpp"
#include "AbstractDelegateIterator.hpp"
#include "AbstractDelegateWrapperIterator.hpp"

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

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
            template < typename __ElementType >         /* NOLINT(bugprone-reserved-identifier) */
            class __ForwardDelegateWrapperIterator :    /* NOLINT(bugprone-reserved-identifier) */
                    public __AbstractDelegateWrapperIterator < __ElementType >,
                    public meta :: ForwardIterator {

            protected:
                /**
                 * @typedef Alias for the __ElementType template parameter
                 * @protected
                 * */
                using ElementType = __ElementType;

            public:
                /**
                 * @brief Default Constructor, constexpr
                 * @exceptsafe
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00054-IT-e_begin_end, CTC-00055-IT-e_cbegin_cend, CTC-00056-IT-e_emptyRange }
                 * @public
                 */
                constexpr __ForwardDelegateWrapperIterator () noexcept;

            public:
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

            public:
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

            public:
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

            public:
                /**
                 * @brief Destructor. Releases ownership of the owned wrapped abstract iterator, if any owned
                 * @exceptsafe
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @public
                 */
                ~__ForwardDelegateWrapperIterator () noexcept override;

            public:
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

            public:
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

            public:
                /**
                 * @brief Equality Comparison Operator.
                 * @param [in] iterator : __ForwardDelegateWrapperIterator cref = Constant Reference to the Iterator to compare current Iterator to
                 * @exceptsafe
                 * @return bool = true if iterators are equal, false otherwise
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @public
                 */
                __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto operator == (
                        __ForwardDelegateWrapperIterator const & iterator
                ) const noexcept -> bool;

            public:
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

            public:
                /**
                 * @brief Prefix Increment Operator. Operation will advance iterator with one position. Postfix not indicated as it will create a copy -> allocation of new abstract iterator.
                 * To prevent generation of range-based loop using postfixed increment, it is not generated.
                 * @exceptsafe
                 * @return __ForwardDelegateWrapperIterator ref = Reference to the modified iterator
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @public
                 */
                __CDS_cpplang_ConstexprPureAbstract auto operator ++ () noexcept -> __ForwardDelegateWrapperIterator &;

            public:
                /**
                 * @brief Dereference Operator. Will acquire value at given iterator.
                 * @exceptsafe
                 * @return __ElementType ref = Reference to element at iterator
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @public
                 */
                __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto operator * () const noexcept -> ElementType &;

            public:
                /**
                 * @brief Address Member Operator. Will acquire address of element at given iterator.
                 * @exceptsafe
                 * @return __ElementType ptr = Pointer to element at iterator
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00057-IT-addressOperator }
                 * @public
                 */
                __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto operator -> () const noexcept -> ElementType *;
            };

        }
    }
}

#endif /* __CDS_SHARED_FORWARD_DELEGATE_WRAPPER_ITERATOR_HPP__ */
