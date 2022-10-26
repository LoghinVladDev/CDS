/*
 * Created by loghin on 14/08/22.
 */

#ifndef __CDS_SHARED_ITERATOR_GENERIC_DECORATOR_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_ITERATOR_GENERIC_DECORATOR_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __DecoratedIteratorType,                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueAtType                                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __valueAtHint (                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __DecoratedIteratorType const & /* baseIterator */
            ) noexcept -> __ValueAtType & {

                /* function implementation left as dummy on purpose. clang-10, gcc-9 and gcc-10 detect this as
                 * a used function, when it is only declared for SFINAE purposes. It will still return
                 * a value acquired from an undefined function to avoid usage in compiled code. */
                return cds :: meta :: referenceOf < __ValueAtType > ();
            }


            template <
                    typename __DecoratedIteratorType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ValueAtType              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > using __ValueAtFunction =                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    decltype ( & __valueAtHint < __DecoratedIteratorType, __ValueAtType > );

        } /* namespace __impl */
    } /* namespace __hidden */

    template <
            typename                                                                            __DecoratedIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename                                                                            __ValueAtType,              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __hidden :: __impl :: __ValueAtFunction < __DecoratedIteratorType, __ValueAtType >  __valueAt                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > class ForwardIteratorGenericDecorator : public meta :: ForwardIterator {

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __DecoratedIteratorType _iterator;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr ForwardIteratorGenericDecorator () noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Explicit constexpr ForwardIteratorGenericDecorator (
                __DecoratedIteratorType const & iterator
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Explicit constexpr ForwardIteratorGenericDecorator (
                __DecoratedIteratorType && iterator
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr ForwardIteratorGenericDecorator (
                ForwardIteratorGenericDecorator const & iterator
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr ForwardIteratorGenericDecorator (
                ForwardIteratorGenericDecorator && iterator
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        ~ForwardIteratorGenericDecorator () noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( /* NOLINT(cppcoreguidelines-c-copy-assignment-signature, misc-unconventional-assign-operator) */
                ForwardIteratorGenericDecorator const &
        ) noexcept -> ForwardIteratorGenericDecorator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( /* NOLINT(cppcoreguidelines-c-copy-assignment-signature, misc-unconventional-assign-operator) */
                ForwardIteratorGenericDecorator &&
        ) noexcept -> ForwardIteratorGenericDecorator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator * () const noexcept -> __ValueAtType &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator -> () const noexcept -> __ValueAtType *;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator == (
                ForwardIteratorGenericDecorator const & iterator
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator != (
                ForwardIteratorGenericDecorator const & iterator
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ForwardIteratorGenericDecorator &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> ForwardIteratorGenericDecorator;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_Explicit constexpr operator bool () const noexcept; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto iterator () const noexcept -> __DecoratedIteratorType const &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto iterator () noexcept -> __DecoratedIteratorType &; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */
    };

} /* namespace cds */

#endif /* __CDS_SHARED_ITERATOR_GENERIC_DECORATOR_HPP__ */
