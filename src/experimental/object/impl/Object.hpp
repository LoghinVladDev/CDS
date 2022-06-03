//
// Created by loghin on 4/27/22.
//

#ifndef __CDS_OBJECT_IMPL_HPP__
#define __CDS_OBJECT_IMPL_HPP__

namespace cds {

    template <> auto hash < experimental :: Object > (
            experimental :: Object const & object
    ) noexcept -> Index {
        return object.hash();
    }

}

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        inline auto Object :: toString () const noexcept -> String {
            std :: stringstream oss;
            oss << "Object at 0x" << std :: hex << reinterpret_cast < AddressValueType const > ( this );
            return oss.str();
        }

        inline Object :: operator String () const noexcept {
            return this->toString();
        }

        inline auto operator << (
                std :: ostream        & out,
                Object          const & object
        ) noexcept -> std::ostream & {
            return (out << object.toString());
        }

        __CDS_cpplang_VirtualConstexpr auto Object :: hash () const noexcept -> Index {
            return 0;
        }

        __CDS_cpplang_VirtualConstexpr auto Object :: equals (
                Object const & object
        ) const noexcept -> bool {
            return this == & object;
        }
    }
}

#endif // __CDS_OBJECT_IMPL_HPP__
