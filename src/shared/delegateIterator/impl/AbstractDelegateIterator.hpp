/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_ABSTRACT_DELEGATE_ITERATOR_HPP_IMPL__
#define __CDS_SHARED_ABSTRACT_DELEGATE_ITERATOR_HPP_IMPL__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
            constexpr __AbstractDelegateIterator < __ElementType > :: __AbstractDelegateIterator () noexcept = default;


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
            __CDS_cpplang_ConstexprDestructor __AbstractDelegateIterator < __ElementType > :: ~__AbstractDelegateIterator () noexcept = default;


            template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
            __CDS_cpplang_VirtualConstexpr auto __AbstractDelegateIterator < __ElementType > :: iterator () const noexcept -> __GenericIterator {

                /* Intended as pure abstract, made as abstract due to MinGW-cpp14-constexpr pure virtual limitation */
                return nullptr;
            }

        }
    }
}

#endif /* __CDS_SHARED_ABSTRACT_DELEGATE_ITERATOR_HPP_IMPL__ */
