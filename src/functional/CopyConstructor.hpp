/*
 * Created by loghin on 6/22/22.
 */

#ifndef __CDS_COPY_CONSTRUCTOR_HPP__
#define __CDS_COPY_CONSTRUCTOR_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {

    namespace utility {         /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template < typename __Type >                                                        /* NOLINT(bugprone-reserved-identifier) */
                constexpr auto __copyConstructHint ( __Type &, __Type const & ) noexcept -> void {  /* NOLINT(bugprone-reserved-identifier) */

                    /* function implementation left as dummy on purpose. clang-10, gcc-9 and gcc-10 detect this as
                     * a used function, when it is only declared for SFINAE purposes. It will still return
                     * a value acquired from an undefined function to avoid usage in compiled code. */
                    (void) cds :: meta :: referenceOf < __Type > ();
                }

            }
        }

        template < typename __Type > /* NOLINT(bugprone-reserved-identifier) */
        using CopyConstructorFunction = decltype (
                & cds :: utility :: __hidden :: __impl :: __copyConstructHint < __Type >
        );
    }

    template < typename __Type, cds :: utility :: CopyConstructorFunction < __Type > __copyConstructor > /* NOLINT(bugprone-reserved-identifier) */
    class FunctionCopyConstructor {

    public:
        __CDS_cpplang_ConstexprNonLiteralReturn auto operator () (
                __Type       & destination,
                __Type const & source
        ) const noexcept ( noexcept ( __copyConstructor ( destination, source ) ) ) -> void {

            return __copyConstructor ( destination, source );
        }
    };

}

#endif /* __CDS_COPY_CONSTRUCTOR_HPP__ */
