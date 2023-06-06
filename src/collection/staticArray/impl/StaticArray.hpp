/*  NOLINT(llvm-header-guard)
 * Created by loghin on 16/02/23.
 */

#ifndef __CDS_STATIC_ARRAY_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_STATIC_ARRAY_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprOverride auto StaticArray <
            __ElementType,
            __size
    > :: __iicch_obtainGenericHandler (
            __hidden :: __impl :: __IterableInternalRequestType requestType
    ) noexcept -> __GenericHandler {

        return this->__is_handlers () [static_cast <uint32> (requestType)];
    }


    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprOverride auto StaticArray <
            __ElementType,
            __size
    > :: __iicch_obtainGenericConstHandler (
            __hidden :: __impl :: __IterableInternalRequestType requestType
    ) const noexcept -> __GenericConstHandler {

        return this->__is_constHandlers () [static_cast <uint32> (requestType)];
    }


    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprConstructorNonEmptyBody StaticArray <
            __ElementType,
            __size
    > :: StaticArray (
            std :: initializer_list < __ElementType > const & initializerList
    ) noexcept :
            Implementation () {

        Size index = 0U;
        for (auto const & element : initializerList) {
            if (index == __size) {
                break;
            }

            * this->__sab_get (index ++) = element;
        }
    }


    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    template < typename __Iterable >
    __CDS_cpplang_ConstexprConstructorNonEmptyBody StaticArray <
            __ElementType,
            __size
    > :: StaticArray (
            __Iterable const & iterable
    ) noexcept :
            Implementation () {

        Size index = 0U;
        for (auto const & element : iterable) {
            if (index == __size) {
                break;
            }

            * this->__sab_get (index ++) = element;
        }
    }


    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    template < typename __Iterable >
    __CDS_cpplang_NonConstConstexprMemberFunction auto StaticArray <
            __ElementType,
            __size
    > :: operator = (
            __Iterable const & iterable
    ) noexcept -> StaticArray & {

        Size index = 0U;
        for (auto const & element : iterable) {
            if (index == __size) {
                break;
            }

            * this->__sab_get (index ++) = element;
        }
    }


    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto StaticArray <
            __ElementType,
            __size
    > :: operator = (
            std :: initializer_list < __ElementType > const & initializerList
    ) noexcept -> StaticArray & {

        Size index = 0U;
        for (auto const & element : initializerList) {
            if (index == __size) {
                break;
            }

            * this->__sab_get (index ++) = element;
        }
    }


    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprConditioned auto StaticArray <
            __ElementType,
            __size
    > :: operator == (
            StaticArray const & array
    ) const noexcept -> bool {

        return this->__sab_equals (array);
    }


    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprConditioned auto StaticArray <
            __ElementType,
            __size
    > :: operator != (
            StaticArray const & array
    ) const noexcept -> bool {

        return ! this->__sab_equals (array);
    }


    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto StaticArray <
            __ElementType,
            __size
    > :: size () const noexcept -> Size {

        return this->__sab_size ();
    }


    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto StaticArray <
            __ElementType,
            __size
    > :: front () noexcept (false) -> __ElementType & {

        if (__size == 0ULL) {
            throw OutOfBoundsException (0ULL, 0ULL);
        }

        return * this->__sab_get (0);
    }


    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto StaticArray <
            __ElementType,
            __size
    > :: back () noexcept (false) -> __ElementType & {

        if (__size == 0ULL) {
            throw OutOfBoundsException (0ULL, 0ULL);
        }

        return * this->__sab_get (__size - 1ULL);
    }


    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto StaticArray <
            __ElementType,
            __size
    > :: front () const noexcept (false) -> __ElementType const & {

        if (__size == 0ULL) {
            throw OutOfBoundsException (0ULL, 0ULL);
        }

        return * this->__sab_get (0);
    }


    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto StaticArray <
            __ElementType,
            __size
    > :: back () const noexcept (false) -> __ElementType const & {

        if (__size == 0ULL) {
            throw OutOfBoundsException (0ULL, 0ULL);
        }

        return * this->__sab_get (__size - 1ULL);
    }


    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprConditioned auto StaticArray <
            __ElementType,
            __size
    > :: get (
            Index index
    ) noexcept (false) -> __ElementType & {

        if (__size == 0ULL) {
            throw OutOfBoundsException (0ULL, 0ULL);
        }

        return * this->__sab_get (this->circularAdjustedIndex(index));
    }


    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprConditioned auto StaticArray <
            __ElementType,
            __size
    > :: get (
            Index index
    ) const noexcept (false) -> __ElementType const & {

        if (__size == 0ULL) {
            throw OutOfBoundsException (0ULL, 0ULL);
        }

        return * this->__sab_get (this->circularAdjustedIndex(index));
    }


    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprConditioned auto StaticArray <
            __ElementType,
            __size
    > :: operator [] (
            Index index
    ) noexcept (false) -> __ElementType & {

        return this->get (index);
    }


    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprConditioned auto StaticArray <
            __ElementType,
            __size
    > :: operator [] (
            Index index
    ) const noexcept (false) -> __ElementType const & {

        return this->get (index);
    }


    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto StaticArray <
            __ElementType,
            __size
    > :: data () noexcept -> __ElementType * {

        return this->__sab_data ();
    }


    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto StaticArray <
            __ElementType,
            __size
    > :: data () const noexcept -> __ElementType const * {

        return this->__sab_data ();
    }


    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    template < typename __Comparator >
    __CDS_OptimalInline auto StaticArray <
            __ElementType,
            __size
    > :: sort (
            __Comparator const & comparator
    ) noexcept -> void {

        this->__sab_sort (comparator);
    }


    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto StaticArray <
            __ElementType,
            __size
    > :: toString () const noexcept(false) -> String {
        /* List represented by values enclosed in square brackets. If Empty, return bracket set */
        if ( __size == 0ULL ) {
            return {"[]"};
        }

        /* use a StringStream to output the contents for maximum compatibility. Start with open bracket */
        std::stringstream out;
        out << "[ ";

        /* iterate through Set and append iterator value to Stream */
        for (Size index = 0ULL; index < __size; ++ index) { /* NOLINT(clion-misra-cpp2008-8-0-1) */
            cds :: meta :: print ( out, * this->__sab_get (index) ) << ", ";
        }

        /* transform to std string */
        auto asString = out.str();

        /* replace ", " with " ]" */
        asString [ asString.length() - 2U ] = ' ';
        asString [ asString.length() - 1U ] = ']';

        /* return std :: string to be reused as cds :: String */
        return asString;
    }


    template < typename __ElementType, Size __size >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprConditioned auto StaticArray <
            __ElementType,
            __size
    > :: circularAdjustedIndex (
            Index index
    ) const noexcept -> Index {

        /* if given negative index, wrap to the nearest positive index by skipping minimum no. of 'size' blocks */
        if ( index < 0 ) {
            index += ( ( - index ) / this->size() + 1 ) * this->size();
        }

        /* if greater than size, use remainder. */
        if ( index >= static_cast < Index > ( this->size() ) ) {
            index = index % this->size();
        }

        /* return bounded index */
        return index;
    }

} /* namespace cds */

#endif /* __CDS_STATIC_ARRAY_IMPL_HPP__ */
