//
// Created by loghin on 6/9/22.
//

#ifndef __CDS_HASH_BASE_HPP__
#define __CDS_HASH_BASE_HPP__

#include "../../string/StringUtils.hpp"

namespace cds {

    template < typename T, typename = void >
    struct Hash {

        __CDS_NoDiscard constexpr static auto hash (
                T const & object
        ) noexcept -> Size {

            return 0ULL;
        }
    };

    template < typename T >
    struct Hash < T, cds :: meta :: EnableIf < cds :: meta :: isObjectDerived < T > (), void > > {

        __CDS_NoDiscard constexpr static auto hash (
                T const & object
        ) noexcept -> Size {

            return object.hash();
        }
    };

    template <>
    struct Hash < StringLiteral > {

        __CDS_NoDiscard constexpr static auto hash ( StringLiteral object ) noexcept -> Size {

            return StringView ( object ).hash();
        }
    };

    template < typename T >
    __CDS_NoDiscard constexpr auto hash (
            T && object
    ) noexcept -> Size {

        return Hash < cds :: meta :: Decay < T > > :: hash ( std :: forward < T > ( object ) );
    }

}

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

    template <>
    struct Hash < uint8 > {

        __CDS_NoDiscard constexpr static auto hash (
                uint8 value
        ) noexcept -> Size {

            return static_cast < Size > ( value );
        }
    };

    template <>
    struct Hash < uint16 > {

        __CDS_NoDiscard constexpr static auto hash (
                uint16 value
        ) noexcept -> Size {

            return static_cast < Size > ( value );
        }
    };

    template <>
    struct Hash < uint32 > {

        __CDS_NoDiscard constexpr static auto hash (
                uint32 value
        ) noexcept -> Size {

            return static_cast < Size > ( value );
        }
    };

    template <>
    struct Hash < uint64 > {

        __CDS_NoDiscard constexpr static auto hash (
                uint64 value
        ) noexcept -> Size {

            return static_cast < Size > ( value );
        }
    };

    template <>
    struct Hash < sint8 > {

        __CDS_NoDiscard constexpr static auto hash (
                sint8 value
        ) noexcept -> Size {

            return static_cast < Size > ( value );
        }
    };

    template <>
    struct Hash < sint16 > {

        __CDS_NoDiscard constexpr static auto hash (
                sint16 value
        ) noexcept -> Size {

            return static_cast < Size > ( value );
        }
    };

    template <>
    struct Hash < sint32 > {

        __CDS_NoDiscard constexpr static auto hash (
                sint32 value
        ) noexcept -> Size {

            return static_cast < Size > ( value );
        }
    };

    template <>
    struct Hash < sint64 > {

        __CDS_NoDiscard constexpr static auto hash (
                sint64 value
        ) noexcept -> Size {

            return static_cast < Size > ( value );
        }
    };

    __CDS_WarningSuppression_ArithmeticOverflow_SuppressEnable

    template <>
    struct Hash < float > {

        __CDS_NoDiscard constexpr static auto hash (
                float value
        ) noexcept -> Size {

            return static_cast < Size > ( value * 1000.0f );
        }
    };

    __CDS_WarningSuppression_ArithmeticOverflow_SuppressDisable

    template <>
    struct Hash < double > {

        __CDS_NoDiscard constexpr static auto hash (
                double value
        ) noexcept -> Size {

            return static_cast < Size > ( value * 100000.0 );
        }
    };

#if defined(CDS_GLM)

    template < glm :: length_t l, typename T, glm :: qualifier q >
    struct Hash < glm :: vec < l, T, q > > {

        __CDS_NoDiscard constexpr static auto hash (
                glm :: vec < l, T, q > const & value
        ) noexcept -> Size {

            return static_cast < Size > ( value * 100000.0 );
        }
    };

    template < glm::length_t l, typename T, glm::qualifier q >
    auto hash ( glm::vec < l, T , q > const & v ) noexcept -> Size {
        if constexpr ( l == 1 )         return hash (v.x);
        else if constexpr ( l == 2 )    return hash (v.x) * 100 + hash (v.y);
        else if constexpr ( l == 3 )    return hash (v.x) * 10000 + hash (v.y) * 100 + hash(v.z);
        else if constexpr ( l == 4 )    return hash (v.x) * 1000000 + hash (v.y) * 10000 + hash(v.z) * 100 + hash(v.w);
        else return 0;
    }

#endif

}

#endif // __CDS_HASH_BASE_HPP__
