/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_ABSTRACT_DELEGATE_ITERATOR_HPP_IMPL__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_ABSTRACT_DELEGATE_ITERATOR_HPP_IMPL__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            constexpr __AbstractDelegateIterator < __ElementType > :: __AbstractDelegateIterator () noexcept = default;


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_ConstexprDestructor __AbstractDelegateIterator < __ElementType > :: ~__AbstractDelegateIterator () noexcept = default;

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_ABSTRACT_DELEGATE_ITERATOR_HPP_IMPL__ */
