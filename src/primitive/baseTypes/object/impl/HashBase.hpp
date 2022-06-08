//
// Created by loghin on 6/9/22.
//

#ifndef __CDS_HASH_BASE_HPP__
#define __CDS_HASH_BASE_HPP__

#include "../../../../shared/HashBaseFunction.hpp"

namespace cds {

    template <>
    constexpr auto hash < Object > (
            Object const & object
    ) noexcept -> Index {

        return object.hash();
    }

}

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

    template <>
    __CDS_cpplang_IfConstexpr auto hash < StringLiteral > (
            StringLiteral const & object
    ) noexcept -> Index {

        return static_cast < Index > ( std :: char_traits < char > :: length ( object ) );
    }

    template <>
    constexpr auto hash < uint8 > (
            uint8 const & object
    ) noexcept -> Index {

        return static_cast < Index const > ( object );
    }

    template <>
    constexpr auto hash < uint16 > (
            uint16 const & object
    ) noexcept -> Index {

        return static_cast < Index const > ( object );
    }

    template <>
    constexpr auto hash < uint32 > (
            uint32 const & object
    ) noexcept -> Index {

        return static_cast < Index const > ( object );
    }

    template <>
    constexpr auto hash < uint64 > (
            uint64 const & object
    ) noexcept -> Index {

        return static_cast < Index const > ( object );
    }

    template <>
    constexpr auto hash < sint8 > (
            sint8 const & object
    ) noexcept -> Index {

        return object;
    }

    template <>
    constexpr auto hash < sint16 > (
            sint16 const & object
    ) noexcept -> Index {

        return object;
    }

    template <>
    constexpr auto hash < sint32 > (
            sint32 const & object
    ) noexcept -> Index {

        return object;
    }

    template <> constexpr auto hash < sint64 > (
            sint64 const & object
    ) noexcept -> Index {

        return object;
    }

    __CDS_WarningSuppression_ArithmeticOverflow_SuppressEnable

    template <>
    constexpr auto hash < float > (
            float const & object
    ) noexcept -> Index {

        return static_cast < Index> ( object * 1000.0f );
    }

    __CDS_WarningSuppression_ArithmeticOverflow_SuppressDisable

    template <>
    constexpr auto hash < double > (
            double const & object
    ) noexcept -> Index {

        return static_cast < Index > ( object * 100000.0 );
    }

#if defined(CDS_GLM)

    template < glm::length_t l, typename T, glm::qualifier q >
    auto hash ( glm::vec < l, T , q > const & v ) noexcept -> Index {
        if constexpr ( l == 1 )         return hash (v.x);
        else if constexpr ( l == 2 )    return hash (v.x) * 100 + hash (v.y);
        else if constexpr ( l == 3 )    return hash (v.x) * 10000 + hash (v.y) * 100 + hash(v.z);
        else if constexpr ( l == 4 )    return hash (v.x) * 1000000 + hash (v.y) * 10000 + hash(v.z) * 100 + hash(v.w);
        else return 0;
    }

#endif

}

#endif // __CDS_HASH_BASE_HPP__
