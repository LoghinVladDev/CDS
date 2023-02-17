/* NOLINT(llvm-header-guard)
 * Created by loghin on 16/02/23.
 */

#ifndef __CDS_STATIC_ARRAY_BASE_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_STATIC_ARRAY_BASE_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename                                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    Size                                                                                __size,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __ElementType const &, __ElementType const & >    __equals,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __MemoryContainer   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline __StaticArrayBase <
                    __ElementType,
                    __size,
                    __equals,
                    __MemoryContainer
            > :: __StaticArrayBase (
                    __StaticArrayBase const & array
            ) noexcept {

                this->__sab_copy (array);
            }


            template <
                    typename                                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    Size                                                                                __size,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __ElementType const &, __ElementType const & >    __equals,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __MemoryContainer   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline __StaticArrayBase <
                    __ElementType,
                    __size,
                    __equals,
                    __MemoryContainer
            > :: __StaticArrayBase (
                    __StaticArrayBase && array
            ) noexcept {

                this->__sab_move (std :: move (array));
            }


            template <
                    typename                                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    Size                                                                                __size,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __ElementType const &, __ElementType const & >    __equals,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __MemoryContainer   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __StaticArrayBase <
                    __ElementType,
                    __size,
                    __equals,
                    __MemoryContainer
            > :: operator = (
                    __StaticArrayBase const & array
            ) noexcept -> __StaticArrayBase & {

                if (this == & array) {
                    return * this;
                }

                this->__sab_copy (array);
                return * this;
            }


            template <
                    typename                                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    Size                                                                                __size,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __ElementType const &, __ElementType const & >    __equals,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __MemoryContainer   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __StaticArrayBase <
                    __ElementType,
                    __size,
                    __equals,
                    __MemoryContainer
            > :: operator = (
                    __StaticArrayBase && array
            ) noexcept -> __StaticArrayBase & {

                if (this == & array) {
                    return * this;
                }

                this->__sab_move (std :: move (array));
                return * this;
            }


            template <
                    typename                                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    Size                                                                                __size,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __ElementType const &, __ElementType const & >    __equals,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __MemoryContainer   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __StaticArrayBase <
                    __ElementType,
                    __size,
                    __equals,
                    __MemoryContainer
            > :: __sab_size () const noexcept -> Size {

                return __size;
            }


            template <
                    typename                                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    Size                                                                                __size,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __ElementType const &, __ElementType const & >    __equals,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __MemoryContainer   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __StaticArrayBase <
                    __ElementType,
                    __size,
                    __equals,
                    __MemoryContainer
            > :: __sab_get (
                    Index index
            ) noexcept -> __ElementType * {

                return this->_sab_memory._samc_data [index];
            }


            template <
                    typename                                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    Size                                                                                __size,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __ElementType const &, __ElementType const & >    __equals,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __MemoryContainer   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __StaticArrayBase <
                    __ElementType,
                    __size,
                    __equals,
                    __MemoryContainer
            > :: __sab_get (
                    Index index
            ) const noexcept -> __ElementType const * {

                return this->_sab_memory._samc_data [index];
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_STATIC_ARRAY_BASE_IMPL_HPP__ */
