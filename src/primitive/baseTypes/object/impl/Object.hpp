//
// Created by loghin on 4/27/22.
//

#ifndef __CDS_OBJECT_IMPL_HPP__
#define __CDS_OBJECT_IMPL_HPP__

namespace cds {

    __CDS_cpplang_VirtualConstexpr auto Object :: hash () const noexcept -> Index {

        return 0;
    }

    __CDS_cpplang_VirtualConstexpr auto Object :: equals (
            Object const & object
    ) const noexcept -> bool {

        return this == & object;
    }
}

#endif // __CDS_OBJECT_IMPL_HPP__