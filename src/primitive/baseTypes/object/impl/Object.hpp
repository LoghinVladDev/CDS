/*
 * Created by loghin on 4/27/22.
 */

#ifndef __CDS_OBJECT_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_OBJECT_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    __CDS_cpplang_VirtualConstexpr auto Object :: hash () const noexcept -> Size {

        return 0;
    }

    __CDS_cpplang_VirtualConstexpr auto Object :: equals (
            Object const & object
    ) const noexcept -> bool {

        return this == & object;
    }

} /* namespace cds */

__CDS_Meta_RegisterParseType(Object) /* NOLINT(clion-misra-cpp2008-8-0-1, cppcoreguidelines-avoid-non-const-global-variables) */

#endif /* __CDS_OBJECT_IMPL_HPP__ */
