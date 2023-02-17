/*  NOLINT(llvm-header-guard)
 * Created by loghin on 16/02/23.
 */

#ifndef __CDS_STATIC_ARRAY_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_STATIC_ARRAY_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprOverride auto StaticArray <
            __ElementType,
            __size
    > :: __iicch_obtainGenericHandler (
            __hidden :: __impl :: __IterableInternalRequestType requestType
    ) noexcept -> __GenericHandler {

        return this->__is_handlers () [static_cast <uint32> (requestType)];
    }


    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprOverride auto StaticArray <
            __ElementType,
            __size
    > :: __iicch_obtainGenericConstHandler (
            __hidden :: __impl :: __IterableInternalRequestType requestType
    ) const noexcept -> __GenericConstHandler {

        return this->__is_constHandlers () [static_cast <uint32> (requestType)];
    }

} /* namespace cds */

#endif /* __CDS_STATIC_ARRAY_IMPL_HPP__ */
