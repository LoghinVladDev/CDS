/*
 * Created by loghin on 6/22/22.
 */

#ifndef __CDS_DESTRUCTOR_HPP__
#define __CDS_DESTRUCTOR_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {

    namespace utility {         /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template < typename __Type >                            /* NOLINT(bugprone-reserved-identifier) */
                __CDS_cpplang_ConstexprNonLiteralReturn auto __destructHint ( __Type & ) -> void {    /* NOLINT(bugprone-reserved-identifier) */

                    /* function implementation left as dummy on purpose. clang-10, gcc-9 and gcc-10 detect this as
                     * a used function, when it is only declared for SFINAE purposes. It will still return
                     * a value acquired from an undefined function to avoid usage in compiled code. */
                    (void) cds :: meta :: referenceOf < __Type > ();
                }

            }
        }

        template < typename __Type > /* NOLINT(bugprone-reserved-identifier) */
        using DestructorFunction = decltype (
                & cds :: utility :: __hidden :: __impl :: __destructHint < __Type >
        );
    }

    template < typename __Type, cds :: utility :: DestructorFunction < __Type > __destructor >  /* NOLINT(bugprone-reserved-identifier) */
    class FunctionDestructor {

    public:
        __CDS_cpplang_ConstexprNonLiteralReturn auto operator () (
                __Type & value
        ) const noexcept ( noexcept ( __destructor ( value ) ) ) -> void {

            return __destructor ( value );
        }
    };

}

#endif /* __CDS_DESTRUCTOR_HPP__ */
