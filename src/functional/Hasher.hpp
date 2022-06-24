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

}

namespace cds {

    template <typename K, Size hashBoundary>
    class __CDS_DeprecatedHint("Bounded Hash Functions are not to be used anymore. Use FunctionHasher construct") HashCalculator {
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

#if defined(CDS_EASY_HASH_DEBUG)

        template <class K> using HighCollisionDefaultHashFunction __CDS_DeprecatedHint("Bounded Hash Functions are not to be used anymore. Use FunctionHasher construct") = void;
        template <class K> using MediumCollisionDefaultHashFunction __CDS_DeprecatedHint("Bounded Hash Functions are not to be used anymore. Use FunctionHasher construct") = void;
        template <class K> using LowCollisionDefaultHashFunction __CDS_DeprecatedHint("Bounded Hash Functions are not to be used anymore. Use FunctionHasher construct") = void;

#else

        template < typename K > using HighCollisionDefaultHashFunction __CDS_DeprecatedHint("Bounded Hash Functions are not to be used anymore. Use FunctionHasher construct") = void;
        template < typename K > using MediumCollisionDefaultHashFunction __CDS_DeprecatedHint("Bounded Hash Functions are not to be used anymore. Use FunctionHasher construct") = void;
        template < typename K > using LowCollisionDefaultHashFunction __CDS_DeprecatedHint("Bounded Hash Functions are not to be used anymore. Use FunctionHasher construct") = void;

#endif

    }
}

namespace cds {

    namespace utility {

        template < typename __Type > // NOLINT(bugprone-reserved-identifier)
        using HashFunction = decltype ( & cds :: hash < __Type > );

    }

    template < typename __Type, utility :: HashFunction < __Type > __hashFunction > // NOLINT(bugprone-reserved-identifier)
    class FunctionHasher {

    public:
        __CDS_NoDiscard constexpr auto operator () (
                __Type const & value
        ) const noexcept ( noexcept ( __hashFunction ( value ) ) ) -> Size {

            return __hashFunction ( value );
        }
    };

}

#if __CDS_cpplang_Concepts_available == true

    template < typename H >
    concept HashCalculatorHasBoundaryFunction = requires (H hashCalculator) {
        { hashCalculator.getBoundary() };
    };

#endif

#endif //CDS_HASHER_HPP
