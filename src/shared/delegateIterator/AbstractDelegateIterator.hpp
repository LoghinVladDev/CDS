/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_ABSTRACT_DELEGATE_ITERATOR_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_ABSTRACT_DELEGATE_ITERATOR_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include "IteratorAdvanceDirection.hpp"

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @interface Abstract Delegate Iterator, without defined proper type, abstract only, as Collection must not know the type of delegate.
             * @tparam __ElementType is the type of the enclosed element. Must not be decayed, as it can represent a const iterator
             *
             * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
             * @namespace cds :: experimental :: __hidden :: __impl
             * @internal library-private
             */
            template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            class __AbstractDelegateIterator {      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Default Constructor, constexpr
                 * @exceptsafe
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00054-IT-e_begin_end, CTC-00055-IT-e_cbegin_cend, CTC-00056-IT-e_emptyRange }
                 * @protected
                 */
                constexpr __AbstractDelegateIterator() noexcept;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Implicit Copy Constructor, constexpr
                 * @param iterator : __AbstractDelegateIterator cref = Constant Reference to the delegate to copy data from
                 * @exceptsafe
                 * @test N/A
                 * @protected
                 */
                __AbstractDelegateIterator(__AbstractDelegateIterator const &) noexcept = default;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Implicit Move Constructor, constexpr
                 * @param iterator : __AbstractDelegateIterator mref = Move Reference to the delegate to move data from
                 * @exceptsafe
                 * @test N/A
                 * @protected
                 */
                __AbstractDelegateIterator(__AbstractDelegateIterator &&) noexcept = default;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Implicit Copy Assignment Operator, constexpr
                 * @param iterator : __AbstractDelegateIterator cref = Constant Reference to the delegate to copy data from
                 * @exceptsafe
                 * @return __AbstractDelegateIterator ref = Reference to the modified object
                 * @test N/A
                 * @protected
                 */
                auto operator = (
                        __AbstractDelegateIterator const & /* iterator */
                ) noexcept -> __AbstractDelegateIterator & = default;

            protected:  /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Implicit Move Assignment Operator, constexpr
                 * @param iterator : __AbstractDelegateIterator mref = Move Reference to the delegate to move data from
                 * @exceptsafe
                 * @return __AbstractDelegateIterator ref = Reference to the modified object
                 * @test N/A
                 * @protected
                 */
                auto operator = (
                        __AbstractDelegateIterator && /* iterator */
                ) noexcept -> __AbstractDelegateIterator & = default;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Virtual Destructor.
                 * @exceptsafe
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @public
                 */
                __CDS_cpplang_ConstexprDestructor virtual ~__AbstractDelegateIterator() noexcept;

            public: /* NOLINT(readability-redundant-access-specifiers) */
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

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Equality Function. Called by Wrapper
                 * @param [in] iterator : __AbstractDelegateIterator cref = Constant Reference to the Iterator to compare current Iterator to
                 * @exceptsafe
                 * @return bool = true if iterators are equal, false otherwise
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @protected
                 */
                __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto equals ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */
                        __AbstractDelegateIterator const & iterator
                ) const noexcept -> bool = 0;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Validity Function. Checks if delegate is valid for the base derived collection. Called by Wrapper
                 * @exceptsafe
                 * @return bool = true if iterator is valid, false otherwise
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @public
                 */
                __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto valid () const noexcept -> bool = 0;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to obtain the base iterator of the derived class, used in extraction of base iterator, such as Collection :: remove ( abstract ) -> Array :: remove ( base iterator )
                 * @exceptsafe
                 * @return cds :: meta :: Iterator cptr = pointer to const iterator. To be returned by delegates and to be reinterpreted by base derived class functions
                 * @test Suite: TBA, Group: TBA, Test Cases: TBA
                 * @public
                 */
                __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto iterator () const noexcept -> cds :: meta :: Iterator const * = 0; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Function used to create a copy of the current wrapper. Called by Wrapper at copy creation
                 * @exceptsafe
                 * @return __AbstractDelegateIterator ptr = Pointer to the newly created Delegate
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00051-IT-range }
                 * @public
                 */
                __CDS_NoDiscard virtual auto copy () const noexcept -> __AbstractDelegateIterator * = 0;

            public: /* NOLINT(readability-redundant-access-specifiers) */
                /**
                 * @brief Value Acquisition Function. Will acquire value at given iterator. Called by Wrapper
                 * @exceptsafe
                 * @return __ElementType ref = Reference to element at iterator
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 * @protected
                 */
                __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto value () const noexcept -> __ElementType & = 0;
            };

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_ABSTRACT_DELEGATE_ITERATOR_HPP__ */
