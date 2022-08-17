//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ABSTRACT_DELEGATE_ITERATOR_HPP__
#define __CDS_SHARED_ABSTRACT_DELEGATE_ITERATOR_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include "IteratorAdvanceDirection.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                /**
                 * @typedef Alias for a generic delegate iterator. Unknown, intentional, as iterator server will generate a derived delegate iterator
                 * */
                using __GenericIterator = void const *; /* NOLINT(bugprone-reserved-identifier) */


                /**
                 * @class Abstract Delegate Iterator, without defined proper type, abstract only, as Collection must not know the type of delegate.
                 * @tparam __ElementType is the type of the enclosed element. Must not be decayed, as it can represent a const iterator
                 *
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @namespace cds :: experimental :: __hidden :: __impl
                 * @internal library-private
                 */
                template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
                class __AbstractDelegateIterator {      /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    /**
                     * @brief Default Constructor, constexpr
                     * @exceptsafe
                     * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00054-IT-e_begin_end, CTC-00055-IT-e_cbegin_cend, CTC-00056-IT-e_emptyRange }
                     * @protected
                     */
                    constexpr __AbstractDelegateIterator() noexcept;

                public:
                    /**
                     * @brief Virtual Destructor.
                     * @exceptsafe
                     * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                     * @public
                     */
                    __CDS_cpplang_ConstexprDestructor virtual ~__AbstractDelegateIterator() noexcept;

                public:
                    /**
                     * @brief Advance Function. Operation will advance iterator with one position, in requested direction. Called by Wrapper
                     * @param [in] direction : __IteratorAdvanceDirection = the direction to advance the iterator in
                     * @exceptsafe
                     * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                     * @public
                     */
                    __CDS_cpplang_ConstexprPureAbstract virtual auto advance (
                            __IteratorAdvanceDirection direction
                    ) noexcept -> void = 0;

                public:
                    /**
                     * @brief Equality Function. Called by Wrapper
                     * @param [in] iterator : __AbstractDelegateIterator cref = Constant Reference to the Iterator to compare current Iterator to
                     * @exceptsafe
                     * @return bool = true if iterators are equal, false otherwise
                     * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                     * @protected
                     */
                    __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto equals (
                            __AbstractDelegateIterator const & iterator
                    ) const noexcept -> bool = 0;

                public:
                    /**
                     * @brief Validity Function. Checks if delegate is valid for the base derived collection. Called by Wrapper
                     * @exceptsafe
                     * @return bool = true if iterator is valid, false otherwise
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @public
                     */
                    __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto valid () const noexcept -> bool = 0;

                public:
                    /**
                     * @brief Function used to obtain the base iterator of the derived class, used in extraction of base iterator, such as Collection :: remove ( abstract ) -> Array :: remove ( base iterator )
                     * @exceptsafe
                     * @return __GenericIterator = unknown type, pointer to iterator. To be returned by delegates and to be reinterpreted by base derived class functions
                     * @test Suite: TBA, Group: TBA, Test Cases: TBA
                     * @public
                     */
                    __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto iterator () const noexcept -> __GenericIterator;

                public:
                    /**
                     * @brief Function used to create a copy of the current wrapper. Called by Wrapper at copy creation
                     * @exceptsafe
                     * @return __AbstractDelegateIterator ptr = Pointer to the newly created Delegate
                     * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00051-IT-range }
                     * @public
                     */
                    __CDS_NoDiscard virtual auto copy () const noexcept -> __AbstractDelegateIterator * = 0;

                public:
                    /**
                     * @brief Value Acquisition Function. Will acquire value at given iterator. Called by Wrapper
                     * @exceptsafe
                     * @return __ElementType ref = Reference to element at iterator
                     * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                     * @protected
                     */
                    __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto value () const noexcept -> __ElementType & = 0;
                };

            }
        }
    }
}

#endif /* __CDS_SHARED_ABSTRACT_DELEGATE_ITERATOR_HPP__ */
