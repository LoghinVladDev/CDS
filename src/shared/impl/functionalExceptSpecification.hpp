/*
 * Created by loghin on 12/05/2022.
 * 
 * Workaround header for MSVC not invoking SFINAE in noexcept () calls
 * Example: 
 * noexcept ( 
 *     noexcept ( __findAllThat < __IteratorType, __CollectionType, __Predicate > (
 *         cds :: meta :: addressOf < __IterableType const > ()->cbegin(),
 *         cds :: meta :: addressOf < __IterableType const > ()->cend(),
 *         cds :: meta :: referenceOf < __CollectionType < ConstIterator > > (),
 *         predicate
 *     )
 * )
 * 
 * Will not invoke SFINAE, required
 * due to __findAllThat having multiple
 * definitions based on __Predicate type - global function, functor, member function, etc.
 */

#ifndef __CDS_SHARED_FUNCTIONAL_EXCEPT_SPECIFICATION_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_FUNCTIONAL_EXCEPT_SPECIFICATION_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
	namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
		namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

			template < typename __ElementType, typename __Predicate, bool = cds :: meta :: isFunction < __Predicate > (), bool = cds :: meta :: isMemberFunctionPointer < __Predicate > () >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
			struct __PredicateExceptSpecTraits {                                                                                                                                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                constexpr static bool const __noexceptSpec = false;                                                                                                                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            };

            template < typename __ElementType, typename __Predicate >                                                                                                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __PredicateExceptSpecTraits < __ElementType, __Predicate, true, false > {                                                                                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                constexpr static bool const __noexceptSpec = noexcept ( cds :: meta :: referenceOf < __Predicate const > () ( cds :: meta :: referenceOf < __ElementType > () ) );              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            };

            template < typename __ElementType, typename __Predicate >                                                                                                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __PredicateExceptSpecTraits < __ElementType, __Predicate, false, true > {                                                                                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                constexpr static bool const __noexceptSpec = noexcept ( ( cds :: meta :: referenceOf < __ElementType > () .* cds :: meta :: referenceOf < __Predicate const > () ) () );        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            };


			template < typename __ElementType, typename __Consumer, bool = cds :: meta :: isFunction < __Consumer > (), bool = cds :: meta :: isMemberFunctionPointer < __Consumer > () >       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
			struct __ConsumerExceptSpecTraits {                                                                                                                                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                constexpr static bool const __noexceptSpec = false;                                                                                                                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            };

            template < typename __ElementType, typename __Consumer >                                                                                                                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __ConsumerExceptSpecTraits < __ElementType, __Consumer, true, false > {                                                                                                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                constexpr static bool const __noexceptSpec = noexcept ( cds :: meta :: referenceOf < __Consumer const > () ( cds :: meta :: referenceOf < __ElementType > () ) );               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            };

            template < typename __ElementType, typename __Consumer >                                                                                                                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __ConsumerExceptSpecTraits < __ElementType, __Consumer, false, true > {                                                                                                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                constexpr static bool const __noexceptSpec = noexcept ( ( cds :: meta :: referenceOf < __ElementType > () .* cds :: meta :: referenceOf < __Consumer const > () ) () );         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            };

		} /* namespace __impl */
	} /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_FUNCTIONAL_EXCEPT_SPECIFICATION_HPP__ */
