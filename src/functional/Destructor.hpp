//
// Created by loghin on 6/22/22.
//

#ifndef __CDS_DESTRUCTOR_HPP__
#define __CDS_DESTRUCTOR_HPP__

namespace cds {

    namespace utility {         // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename __Type > // NOLINT(bugprone-reserved-identifier)
                constexpr auto __destructHint ( __Type & ) noexcept -> void;

            }
        }

        template < typename __Type > // NOLINT(bugprone-reserved-identifier)
        using DestructorFunction = decltype (
                & cds :: utility :: __hidden :: __impl :: __destructHint < __Type >
        );
    }

    template < typename __Type, cds :: utility :: DestructorFunction < __Type > __destructor >  // NOLINT(bugprone-reserved-identifier)
    class FunctionDestructor {

    public:
        constexpr auto operator () (
                __Type & value
        ) const noexcept ( noexcept ( __destructor ( value ) ) ) -> void {

            return __destructor ( value );
        }
    };

}

#endif // __CDS_DESTRUCTOR_HPP__
