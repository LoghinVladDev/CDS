/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_BIDIRECTIONAL_DELEGATE_WRAPPER_ITERATOR_HPP__
#define __CDS_SHARED_BIDIRECTIONAL_DELEGATE_WRAPPER_ITERATOR_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include "../iterator/IteratorModel.hpp"
#include "AbstractDelegateIterator.hpp"
#include "AbstractDelegateWrapperIterator.hpp"

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            /**
             * @class Wrapper Iterator type for Abstract Iterators that satisfy the 'Bidirectional Iterable' Model
             * @tparam __ElementType is the type of the enclosed element at the wrapped abstract iterator. Must not be decayed, as it can represent a const iterator
             *
             * @extends __AbstractDelegateWrapperIterator - base class containing Collection information
             * @implements meta :: BidirectionalIterator - model
             *
             * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: All
             * @namespace cds :: experimental :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier) */
            class __BidirectionalDelegateWrapperIterator :  /* NOLINT(bugprone-reserved-identifier) */
                    public __AbstractDelegateWrapperIterator < __ElementType >,
                    public cds :: experimental :: meta :: BidirectionalIterator {

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
                 * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: All
                 * @public
                 */
                constexpr __BidirectionalDelegateWrapperIterator () noexcept;

            public:
                /**
                 * @brief Constructor used in creating wrapper iterators in Delegate Clients.
                 * @param [in] pOwner : Object cptr = Immutable Pointer to the owner object, used to identify iterators passed to functions from outside collection.
                 * @param [in] pDelegate : __AbstractDelegateIterator = Pointer to the delegate that is to be wrapped. Ownership of the wrapped abstract iterator will be granted to the wrapper.
                 * @exceptsafe
                 * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: All
                 * @public
                 */
                constexpr __BidirectionalDelegateWrapperIterator (
                        Object                                          const * pOwner,
                        __AbstractDelegateIterator < __ElementType >          * pDelegate
                ) noexcept;

            public:
                /**
                 * @brief Copy Constructor.
                 * @param [in] iterator : __BidirectionalDelegateWrapperIterator cref = Constant Reference to the Iterator to copy from. Will create a new abstract iterator for the new wrapper to own.
                 * @exceptsafe
                 * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: All
                 * @public
                 */
                __BidirectionalDelegateWrapperIterator (
                        __BidirectionalDelegateWrapperIterator const & iterator
                ) noexcept;

            public:
                /**
                 * @brief Move Constructor.
                 * @param [in, out] iterator : __BidirectionalDelegateWrapperIterator mref = Move Reference to the Iterator to acquire items from. Ownership of the abstract wrapped iterator passed to the newly created wrapper. Given iterator as parameter should not be used anymore, as it will not contain and wrapped abstract iterator
                 * @exceptsafe
                 * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: All
                 * @public
                 */
                constexpr __BidirectionalDelegateWrapperIterator (
                        __BidirectionalDelegateWrapperIterator && iterator
                ) noexcept;

            public:
                /**
                 * @brief Destructor. Releases ownership of the owned wrapped abstract iterator, if any owned
                 * @exceptsafe
                 * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: All
                 * @public
                 */
                ~__BidirectionalDelegateWrapperIterator () noexcept override;

            public:
                /**
                 * @brief Copy Assignment Operator.
                 * @param [in] iterator : __BidirectionalDelegateWrapperIterator cref = Constant Reference to the Iterator to copy from. Will create a new abstract iterator for the left hand wrapper to own.
                 * @exceptsafe
                 * @return __BidirectionalDelegateWrapperIterator ref = Reference to the newly modified left-hand iterator
                 * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: All
                 * @public
                 */
                auto operator = (
                        __BidirectionalDelegateWrapperIterator const & iterator
                ) noexcept -> __BidirectionalDelegateWrapperIterator &;

            public:
                /**
                 * @brief Move Assignment Operator.
                 * @param [in, out] iterator : __BidirectionalDelegateWrapperIterator mref = Move Reference to the Iterator to move from. Will transfer ownership of the wrapped abstract iterator from right hand wrapper to left hand wrapper.
                 * @exceptsafe
                 * @return __BidirectionalDelegateWrapperIterator ref = Reference to the newly modified left-hand iterator
                 * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: All
                 * @public
                 */
                auto operator = (
                        __BidirectionalDelegateWrapperIterator && iterator
                ) noexcept -> __BidirectionalDelegateWrapperIterator &;

            public:
                /**
                 * @brief Equality Comparison Operator.
                 * @param [in] iterator : __BidirectionalDelegateWrapperIterator cref = Constant Reference to the Iterator to compare current Iterator to
                 * @exceptsafe
                 * @return bool = true if iterators are equal, false otherwise
                 * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: All
                 * @public
                 */
                __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto operator == (
                        __BidirectionalDelegateWrapperIterator const & iterator
                ) const noexcept -> bool;

            public:
                /**
                 * @brief Inequality Comparison Operator.
                 * @param [in] iterator : __BidirectionalDelegateWrapperIterator cref = Constant Reference to the Iterator to compare current Iterator to
                 * @exceptsafe
                 * @return bool = false if iterators are equal, true otherwise
                 * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: All
                 * @public
                 */
                __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto operator != (
                        __BidirectionalDelegateWrapperIterator const & iterator
                ) const noexcept -> bool;

            public:
                /**
                 * @brief Prefix Increment Operator. Operation will advance iterator with one position. Postfix not indicated as it will create a copy -> allocation of new abstract iterator.
                 * To prevent generation of range-based loop using postfixed increment, it is not generated.
                 * @exceptsafe
                 * @return __BidirectionalDelegateWrapperIterator ref = Reference to the modified iterator
                 * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
                 *      LTC-00201-IT-perValueCheck,
                 *      LTC-00202-IT-perValueImmCheck,
                 *      LTC-00203-IT-perValueRevCheck,
                 *      LTC-00204-IT-perValueRevImmCheck,
                 *      LTC-00209-IT-itMutabilityRange,
                 *      LTC-00210-IT-itMutabilityStd,
                 *      LTC-00211-IT-itMutabilityStdRev
                 * }
                 * @public
                 */
                __CDS_cpplang_ConstexprPureAbstract auto operator ++ () noexcept -> __BidirectionalDelegateWrapperIterator &;

            public:
                /**
                 * @brief Prefix Decrement Operator. Operation will reverse iterator with one position. Postfix not indicated as it will create a copy -> allocation of new abstract iterator.
                 * To keep in line with the model of __ForwardDelegateWrapperIterator, the postfix will not be created.
                 * @exceptsafe
                 * @return __BidirectionalDelegateWrapperIterator ref = Reference to the modified iterator
                 * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: {
                 *      LTC-00205-IT-perValueBwdCheck,
                 *      LTC-00206-IT-perValueBwdImmCheck,
                 *      LTC-00207-IT-perValueRevBwdCheck,
                 *      LTC-00208-IT-perValueRevBwdImmCheck
                 * }
                 * @public
                 */
                __CDS_cpplang_ConstexprPureAbstract auto operator -- () noexcept -> __BidirectionalDelegateWrapperIterator &;

            public:
                /**
                 * @brief Dereference Operator. Will acquire value at given iterator.
                 * @exceptsafe
                 * @return __ElementType ref = Reference to element at iterator
                 * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: All
                 * @public
                 */
                __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto operator * () const noexcept -> ElementType &;

            public:
                /**
                 * @brief Address Member Operator. Will acquire address of element at given iterator.
                 * @exceptsafe
                 * @return __ElementType ptr = Pointer to element at iterator
                 * @test Suite: LTS-00001, Group: LTG-00200-IT, Test Cases: All
                 * @public
                 */
                __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto operator -> () const noexcept -> ElementType *;
            };

        }
    }
}

#endif /* __CDS_SHARED_BIDIRECTIONAL_DELEGATE_WRAPPER_ITERATOR_HPP__ */
