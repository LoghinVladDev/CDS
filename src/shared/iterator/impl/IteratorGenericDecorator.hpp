/*
 * Created by loghin on 14/08/22.
 */

#ifndef __CDS_SHARED_ITERATOR_GENERIC_DECORATOR_HPP_IMPL__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_ITERATOR_GENERIC_DECORATOR_HPP_IMPL__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */

    template <
            typename                                                                            __DecoratedIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename                                                                            __ValueAtType,              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __hidden :: __impl :: __ValueAtFunction < __DecoratedIteratorType, __ValueAtType >  __valueAt                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr ForwardIteratorGenericDecorator <
            __DecoratedIteratorType,
            __ValueAtType,
            __valueAt
    > :: ForwardIteratorGenericDecorator () noexcept = default;


    template <
            typename                                                                            __DecoratedIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename                                                                            __ValueAtType,              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __hidden :: __impl :: __ValueAtFunction < __DecoratedIteratorType, __ValueAtType >  __valueAt                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr ForwardIteratorGenericDecorator <
            __DecoratedIteratorType,
            __ValueAtType,
            __valueAt
    > :: ForwardIteratorGenericDecorator (
            __DecoratedIteratorType const & iterator
    ) noexcept :
            _iterator ( iterator ) {

    }


    template <
            typename                                                                            __DecoratedIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename                                                                            __ValueAtType,              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __hidden :: __impl :: __ValueAtFunction < __DecoratedIteratorType, __ValueAtType >  __valueAt                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr ForwardIteratorGenericDecorator <
            __DecoratedIteratorType,
            __ValueAtType,
            __valueAt
    > :: ForwardIteratorGenericDecorator (
            __DecoratedIteratorType && iterator
    ) noexcept :
            _iterator ( std :: move ( iterator ) ) {

    }


    template <
            typename                                                                            __DecoratedIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename                                                                            __ValueAtType,              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __hidden :: __impl :: __ValueAtFunction < __DecoratedIteratorType, __ValueAtType >  __valueAt                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr ForwardIteratorGenericDecorator <
            __DecoratedIteratorType,
            __ValueAtType,
            __valueAt
    > :: ForwardIteratorGenericDecorator (
            ForwardIteratorGenericDecorator const & iterator
    ) noexcept :
            _iterator ( iterator._iterator ) {

    }


    template <
            typename                                                                            __DecoratedIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename                                                                            __ValueAtType,              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __hidden :: __impl :: __ValueAtFunction < __DecoratedIteratorType, __ValueAtType >  __valueAt                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr ForwardIteratorGenericDecorator <
            __DecoratedIteratorType,
            __ValueAtType,
            __valueAt
    > :: ForwardIteratorGenericDecorator (
            ForwardIteratorGenericDecorator && iterator
    ) noexcept :
            _iterator ( std :: move ( iterator._iterator ) ) {

    }


    template <
            typename                                                                            __DecoratedIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename                                                                            __ValueAtType,              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __hidden :: __impl :: __ValueAtFunction < __DecoratedIteratorType, __ValueAtType >  __valueAt                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardIteratorGenericDecorator <
            __DecoratedIteratorType,
            __ValueAtType,
            __valueAt
    > :: operator = (
            ForwardIteratorGenericDecorator const & iterator
    ) noexcept -> ForwardIteratorGenericDecorator & {

        if ( this == & iterator ) {
            return * this;
        }

        this->_iterator = iterator._iterator;
        return * this;
    }


    template <
            typename                                                                            __DecoratedIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename                                                                            __ValueAtType,              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __hidden :: __impl :: __ValueAtFunction < __DecoratedIteratorType, __ValueAtType >  __valueAt                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardIteratorGenericDecorator <
            __DecoratedIteratorType,
            __ValueAtType,
            __valueAt
    > :: operator = (
            ForwardIteratorGenericDecorator && iterator
    ) noexcept -> ForwardIteratorGenericDecorator & {

        if ( this == & iterator ) {
            return * this;
        }

        this->_iterator = std :: move ( iterator._iterator );
        return * this;
    }


    template <
            typename                                                                            __DecoratedIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename                                                                            __ValueAtType,              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __hidden :: __impl :: __ValueAtFunction < __DecoratedIteratorType, __ValueAtType >  __valueAt                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr auto ForwardIteratorGenericDecorator <
            __DecoratedIteratorType,
            __ValueAtType,
            __valueAt
    > :: operator * () const noexcept -> __ValueAtType & {

        return __valueAt ( this->_iterator );
    }


    template <
            typename                                                                            __DecoratedIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename                                                                            __ValueAtType,              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __hidden :: __impl :: __ValueAtFunction < __DecoratedIteratorType, __ValueAtType >  __valueAt                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr auto ForwardIteratorGenericDecorator <
            __DecoratedIteratorType,
            __ValueAtType,
            __valueAt
    > :: operator -> () const noexcept -> __ValueAtType * {

        return & ( __valueAt ( this->_iterator ) );
    }


    template <
            typename                                                                            __DecoratedIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename                                                                            __ValueAtType,              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __hidden :: __impl :: __ValueAtFunction < __DecoratedIteratorType, __ValueAtType >  __valueAt                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr auto ForwardIteratorGenericDecorator <
            __DecoratedIteratorType,
            __ValueAtType,
            __valueAt
    > :: operator == (
            ForwardIteratorGenericDecorator const & iterator
    ) const noexcept -> bool {

        return this->_iterator == iterator._iterator;
    }


    template <
            typename                                                                            __DecoratedIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename                                                                            __ValueAtType,              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __hidden :: __impl :: __ValueAtFunction < __DecoratedIteratorType, __ValueAtType >  __valueAt                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr auto ForwardIteratorGenericDecorator <
            __DecoratedIteratorType,
            __ValueAtType,
            __valueAt
    > :: operator != (
            ForwardIteratorGenericDecorator const & iterator
    ) const noexcept -> bool {

        return this->_iterator != iterator._iterator;
    }


    template <
            typename                                                                            __DecoratedIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename                                                                            __ValueAtType,              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __hidden :: __impl :: __ValueAtFunction < __DecoratedIteratorType, __ValueAtType >  __valueAt                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardIteratorGenericDecorator <
            __DecoratedIteratorType,
            __ValueAtType,
            __valueAt
    > :: operator ++ () noexcept -> ForwardIteratorGenericDecorator & {

        ++ this->_iterator;
        return * this;
    }


    template <
            typename                                                                            __DecoratedIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename                                                                            __ValueAtType,              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __hidden :: __impl :: __ValueAtFunction < __DecoratedIteratorType, __ValueAtType >  __valueAt                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardIteratorGenericDecorator <
            __DecoratedIteratorType,
            __ValueAtType,
            __valueAt
    > :: operator ++ (int) noexcept -> ForwardIteratorGenericDecorator {

        auto copy = * this;
        ++ this->_iterator;
        return copy;
    }


    template <
            typename                                                                            __DecoratedIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename                                                                            __ValueAtType,              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __hidden :: __impl :: __ValueAtFunction < __DecoratedIteratorType, __ValueAtType >  __valueAt                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr ForwardIteratorGenericDecorator <
            __DecoratedIteratorType,
            __ValueAtType,
            __valueAt
    > :: operator bool () const noexcept {

        return static_cast < bool > ( this->_iterator );
    }


    template <
            typename                                                                            __DecoratedIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename                                                                            __ValueAtType,              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __hidden :: __impl :: __ValueAtFunction < __DecoratedIteratorType, __ValueAtType >  __valueAt                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr auto ForwardIteratorGenericDecorator <
            __DecoratedIteratorType,
            __ValueAtType,
            __valueAt
    > :: iterator () const noexcept -> __DecoratedIteratorType const & {

        return this->_iterator;
    }


    template <
            typename                                                                            __DecoratedIteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename                                                                            __ValueAtType,              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __hidden :: __impl :: __ValueAtFunction < __DecoratedIteratorType, __ValueAtType >  __valueAt                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardIteratorGenericDecorator <
            __DecoratedIteratorType,
            __ValueAtType,
            __valueAt
    > :: iterator () noexcept -> __DecoratedIteratorType & {

        return this->_iterator;
    }

} /* namespace cds */

#endif /* __CDS_SHARED_ITERATOR_GENERIC_DECORATOR_HPP_IMPL__ */
