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

#include "../shared/HashBaseFunction.hpp"

namespace cds {

    class Object;

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
