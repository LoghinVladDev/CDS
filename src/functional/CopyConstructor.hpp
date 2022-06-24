//
// Created by loghin on 6/22/22.
//

#ifndef __CDS_COPY_CONSTRUCTOR_HPP__
#define __CDS_COPY_CONSTRUCTOR_HPP__

namespace cds {

    namespace utility {         // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename __Type > // NOLINT(bugprone-reserved-identifier)
                constexpr auto __copyConstructHint ( __Type &, __Type const & ) noexcept -> void;

            }
        }

        template < typename __Type > // NOLINT(bugprone-reserved-identifier)
        using CopyConstructorFunction = decltype (
                & cds :: utility :: __hidden :: __impl :: __copyConstructHint < __Type >
        );
    }

    template < typename __Type, cds :: utility :: CopyConstructorFunction < __Type > __copyConstructor > // NOLINT(bugprone-reserved-identifier)
    class FunctionCopyConstructor {

    public:
        constexpr auto operator () (
                __Type       & destination,
                __Type const & source
        ) const noexcept ( noexcept ( __copyConstructor ( destination, source ) ) ) -> void {

            return __copyConstructor ( destination, source );
        }
    };

}

#endif // __CDS_COPY_CONSTRUCTOR_HPP__
