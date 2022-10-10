/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_DELEGATE_ITERATOR_HPP__
#define __CDS_SHARED_DELEGATE_ITERATOR_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            namespace meta {

                /**
                 * @struct Meta-Class used to check the wrapped iterator's directional type - if unidirectional
                 * Default Meta-Value : False -> Forward
                 *
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 *
                 * @namespace cds :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename,
                        typename = void
                > struct __WrappedIteratorBidirectional : cds :: meta :: FalseType {}; /* NOLINT(bugprone-reserved-identifier) */

                /**
                 * @struct Meta-Class used to check the wrapped iterator's directional type - if bidirectional
                 * @tparam __TWrappedIteratorType is the type of the given iterator. Will only apply if 'operator --' is possible for this type
                 * Default Meta-Value : True -> Bidirectional
                 *
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 *
                 * @namespace cds :: __hidden :: __impl
                 * @internal library-private
                 */
                template <
                        typename __TWrappedIteratorType /* NOLINT(bugprone-reserved-identifier) */
                > struct __WrappedIteratorBidirectional < __TWrappedIteratorType, cds :: meta :: Void < decltype ( -- cds :: meta :: referenceOf < __TWrappedIteratorType > () ) > > : cds :: meta :: TrueType {}; /* NOLINT(bugprone-reserved-identifier) */
            }

            /**
             * @class Delegate Iterator, adapter-wrapper for any derived class iterator. Interface for __AbstractDelegateIterator -> __WrappedIteratorType
             * @tparam __ElementType is the type of the element the iterator indicates to
             * @tparam __WrappedIteratorType is the type of the iterator obtained from the derived class
             * @implements __AbstractDelegateIterator
             *
             * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
             *
             * @namespace cds :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __ElementType,                                                     /* NOLINT(bugprone-reserved-identifier) */
                    typename __WrappedIteratorType                                              /* NOLINT(bugprone-reserved-identifier) */
            > class __DelegateIterator : public __AbstractDelegateIterator < __ElementType > {  /* NOLINT(bugprone-reserved-identifier) */

            public:
                /**
                 * @typedef Alias for template parameter __ElementType
                 * @public
                 */
                using ElementType   = __ElementType;

            public:
                /**
                 * @typedef Alias for template parameter __WrappedIteratorType
                 * @public
                 */
                using IteratorType  = __WrappedIteratorType;

            private:
                /**
                 * @brief Wrapped Collection-derived iterator
                 * @private
                 */
                IteratorType _wrappedIterator;

            public:
                /**
                 * @brief Default Constructor, constexpr
                 * @exceptsafe
                 *
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 *
                 * @public
                 */
                constexpr __DelegateIterator () noexcept;

            public:
                /**
                 * @brief Initialization Constructor, constexpr
                 * @param [in] iterator : IteratorType cref = Constant Reference to an iterator value to be wrapped
                 * @exceptsafe
                 *
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 *
                 * @public
                 */
                __CDS_Explicit constexpr __DelegateIterator (
                        IteratorType const & iterator
                ) noexcept;

            public:
                /**
                 * @brief Initialization Constructor, constexpr
                 * @param [in, out] iterator : IteratorType mref = Move Reference to an iterator value to be wrapped
                 * @exceptsafe
                 *
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 *
                 * @public
                 */
                __CDS_Explicit constexpr __DelegateIterator (
                        IteratorType && iterator
                ) noexcept;

            public:
                /**
                 * @brief Copy Constructor, constexpr
                 * @param [in] iterator : __DelegateIterator cref = Constant Reference to an iterator to copy the wrapped iterator from
                 * @exceptsafe
                 *
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 *
                 * @public
                 */
                constexpr __DelegateIterator (
                        __DelegateIterator const & iterator
                ) noexcept;

            public:
                /**
                 * @brief Move Constructor, constexpr
                 * @param [in, out] iterator : __DelegateIterator mref = Move Reference to an iterator to move the wrapped iterator from
                 * @exceptsafe
                 *
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 *
                 * @public
                 */
                constexpr __DelegateIterator (
                        __DelegateIterator && iterator
                ) noexcept;

            public:
                /**
                 * @brief Destructor
                 * @exceptsafe
                 *
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 *
                 * @public
                 */
                __CDS_cpplang_ConstexprDestructor ~__DelegateIterator () noexcept override;

            public:
                /**
                 * @brief Function used to acquire the wrapped iterator's address as a generic iterator
                 * @exceptsafe
                 * @return __GenericIterator = address of the wrapped iterator, a 'generic' iterator
                 *
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 *
                 * @public
                 */
                __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto iterator () const noexcept -> __GenericIterator override;

            private:
                /**
                 * @brief Function used to advance the iterator backwards, applicable if the iterator is bidirectional. This is the variant where the wrapped iterator is bidirectional
                 * @tparam __TWrappedIteratorType the type of the wrapped iterator, renamed to invoke substitution
                 * @exceptsafe
                 *
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 *
                 * @private
                 */
                template <
                        typename __TWrappedIteratorType = __WrappedIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf < meta :: __WrappedIteratorBidirectional < __TWrappedIteratorType > :: value > = 0
                > __CDS_cpplang_ConstexprNonLiteralReturn auto __advanceBackwards () noexcept -> void; /* NOLINT(bugprone-reserved-identifier) */

            private:
                /**
                 * @brief Function used to advance the iterator backwards, applicable if the iterator is bidirectional. This is the variant where the wrapped iterator is not bidirectional, and will not do anything
                 * @tparam __TWrappedIteratorType the type of the wrapped iterator, renamed to invoke substitution
                 * @exceptsafe
                 *
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 *
                 * @private
                 */
                template <
                        typename __TWrappedIteratorType = __WrappedIteratorType,  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: meta :: EnableIf < ! meta :: __WrappedIteratorBidirectional < __TWrappedIteratorType > :: value > = 0
                > __CDS_cpplang_ConstexprNonLiteralReturn auto __advanceBackwards () noexcept -> void; /* NOLINT(bugprone-reserved-identifier) */

            public:
                /**
                 * @brief Function used to advance the iterator in a given direction
                 * @param [in] direction : __IteratorAdvanceDirection = the direction to advance the iterator into
                 * @exceptsafe
                 *
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 *
                 * @public
                 */
                __CDS_cpplang_ConstexprPureAbstract auto advance (
                        __IteratorAdvanceDirection direction
                ) noexcept -> void override;

            public:
                /**
                 * @brief Function used to compare the iterator with a given iterator
                 * @param [in] iterator : __AbstractDelegateIterator cref = Constant Reference to another iterator
                 * @exceptsafe
                 * @return bool = true if iterators are equal, false otherwise
                 *
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 *
                 * @public
                 */
                __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto equals (
                        __AbstractDelegateIterator < __ElementType > const & iterator
                ) const noexcept -> bool override;

            public:
                /**
                 * @brief Function used to check if the iterator is valid ( in bounds )
                 * @exceptsafe
                 * @return bool = true if iterator is valid, false otherwise
                 *
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 *
                 * @public
                 */
                __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto valid () const noexcept -> bool override;

            public:
                /**
                 * @brief Function used to acquire a copy of the iterator, used in caller __AbstractDelegateIterator wrappers
                 * @exceptsafe
                 * @return __AbstractDelegateIterator ptr = Address to a new iterator, a copy of the caller
                 *
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 *
                 * @public
                 */
                __CDS_NoDiscard auto copy () const noexcept -> __AbstractDelegateIterator < __ElementType > * override;

            public:
                /**
                 * @brief Function used to acquire the value the iterator is indicating to
                 * @exceptsafe
                 * @return ElementType cref = Constant Reference to the element the iterator is indicating to
                 *
                 * @test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
                 *
                 * @public
                 */
                __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto value () const noexcept -> ElementType & override;
            };

        }
    }
}

#endif /* __CDS_SHARED_DELEGATE_ITERATOR_HPP__ */
