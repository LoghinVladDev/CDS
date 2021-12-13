//
// Created by loghin on 10.11.2021.
//

#ifndef CDS_HASHER_HPP
#define CDS_HASHER_HPP

#include <string>
#include <cstring>
#include <CDS/std-types>

#include <CDS/Compiler>
#include <CDS/Options>

namespace cds {

    class Object;
    class String;

}

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

    template<class T> constexpr static auto hash(T const &) noexcept -> Index {
        return 0;     
    }

    template<> auto hash<String>(String const &object) noexcept -> Index;
    template<> auto hash<Object>(Object const &object) noexcept -> Index;
    template<> __CDS_cpplang_IfConstexpr auto hash<CString>(CString const &object) noexcept -> Index { 
        return static_cast < Index > ( std::char_traits<char>::length(object) ); 
    }

    template<> __CDS_cpplang_IfConstexpr auto hash<StringLiteral>(StringLiteral const &object) noexcept -> Index { 
        return static_cast < Index > ( std::char_traits<char>::length(object) );
    }

    template<> constexpr auto hash<uint8>(uint8 const &object) noexcept -> Index { 
        return static_cast < Index const > ( object ); 
    }

    template<> constexpr auto hash<uint16>(uint16 const &object) noexcept -> Index { 
        return static_cast < Index const > ( object ); 
    }

    template<> constexpr auto hash<uint32>(uint32 const &object) noexcept -> Index { 
        return static_cast < Index const > ( object ); 
    }

    template<> constexpr auto hash<uint64>(uint64 const &object) noexcept -> Index { 
        return static_cast < Index const > ( object ); 
    }

    template<> constexpr auto hash<sint8>(sint8 const &object) noexcept -> Index { 
        return object;
    }

    template<> constexpr auto hash<sint16>(sint16 const &object) noexcept -> Index { 
        return object; 
    }

    template<> constexpr auto hash<sint32>(sint32 const &object) noexcept -> Index { 
        return object; 
    }

    template<> constexpr auto hash<sint64>(sint64 const &object) noexcept -> Index { 
        return object; 
    }

    __CDS_WarningSuppression_ArithmeticOverflow_SuppressEnable

    template <> constexpr auto hash<float> (float const & object) noexcept -> Index { 
        return static_cast < Index> ( object * 1000.0f ); 
    }

    __CDS_WarningSuppression_ArithmeticOverflow_SuppressDisable

    template <> constexpr auto hash<double> (double const & object) noexcept -> Index { 
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

namespace cds {

    template <typename K, Size hashBoundary>
    class HashCalculator {
    public:
        using Value                 = K;
        using ValueConstReference   = Value const &;

        using HashValue             = Index;

        virtual auto operator ()(ValueConstReference) const noexcept -> HashValue = 0;

        __CDS_NoDiscard virtual __CDS_cpplang_VirtualConstexpr auto getBoundary () const noexcept -> Size { 
            return hashBoundary; 
        }
    };

}

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility {

        template <class K, Size hashBoundary>
        class DefaultHashFunction : public HashCalculator<K, hashBoundary> {
        public:
            using AddressValue __CDS_MaybeUnused = std::size_t;

            auto operator ()(typename HashCalculator<K, hashBoundary>::ValueConstReference value) const noexcept -> typename HashCalculator<K, hashBoundary>::HashValue {
                return hash(value) % hashBoundary;
            }
        };

#if defined(CDS_EASY_HASH_DEBUG)

        template <class K> using HighCollisionDefaultHashFunction = DefaultHashFunction<K, 1>;
        template <class K> using MediumCollisionDefaultHashFunction = DefaultHashFunction<K, 1>;
        template <class K> using LowCollisionDefaultHashFunction = DefaultHashFunction<K, 1>;

#else

        template < typename K > using HighCollisionDefaultHashFunction = DefaultHashFunction < K, 256u >;
        template < typename K > using MediumCollisionDefaultHashFunction = DefaultHashFunction < K, 4096u >;
        template < typename K > using LowCollisionDefaultHashFunction = DefaultHashFunction < K, 32768u >;

#endif

    }
}

#if __CDS_cpplang_Concepts_available == true

    template < typename H >
    concept HashCalculatorHasBoundaryFunction = requires (H hashCalculator) {
        { hashCalculator.getBoundary() };
    };

#endif

#endif //CDS_HASHER_HPP
