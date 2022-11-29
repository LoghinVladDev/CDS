/* NOLINT(llvm-header-guard)
 * Created by loghin on 14/08/22.
 */

#ifndef __CDS_MAP_ABSTRACT_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_MAP_ABSTRACT_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_MaybeUnused constexpr Map <
            __KeyType,
            __ValueType
    > :: AbstractValueMutableCollectionProxy :: AbstractValueMutableCollectionProxy (
            Map < __KeyType, __ValueType > * pMap
    ) noexcept :
            ProxyBase ( pMap ) {

    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto Map <
            __KeyType,
            __ValueType
    > :: AbstractValueMutableCollectionProxy :: clear () noexcept -> void {

        this->map()->clear();
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprDestructor Map <
            __KeyType,
            __ValueType
    > :: AbstractValueMutableCollectionProxy :: ~AbstractValueMutableCollectionProxy () noexcept = default;


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_VirtualConstexpr auto Map <
            __KeyType,
            __ValueType
    > :: AbstractValueMutableCollectionProxy :: size () const noexcept -> Size {

        return this->map()->size();
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > auto Map <
            __KeyType,
            __ValueType
    > :: AbstractValueMutableCollectionProxy :: toString () const noexcept -> String {

        /* Reused from CDS/List */
        /* Value Mutable Collection acts as a partial list represented by values enclosed in square brackets. If Empty, return bracket set */
        if ( this->empty() ) {
            return {"[]"};
        }

        /* use a StringStream to output the contents for maximum compatibility. Start with open bracket */
        std::stringstream out;
        out << "[ ";

        /* iterate through iterable and append iterator value to Stream */
        for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) { /* NOLINT(clion-misra-cpp2008-8-0-1) */
            cds :: meta :: print ( out, * iterator ) << ", ";
        }

        /* transform to std string */
        auto asString = out.str();

        /* replace ", " with " ]" */
        asString [ asString.length() - 2U ] = ' ';
        asString [ asString.length() - 1U ] = ']';

        /* return std :: string to be reused as cds :: String */
        return asString;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto Map <
            __KeyType,
            __ValueType
    > :: AbstractValueMutableCollectionProxy :: __newAddress (
            __ValueType const * pReferenceKey,
            bool              * pIsNew        /* NOLINT(readability-non-const-parameter) */
    ) noexcept (false) -> __ValueType * {

        (void) pReferenceKey;
        (void) pIsNew;

        throw cds :: UnsupportedOperationException (
                cds :: String ( "Cannot insert a value into a Map Value Collection" )
        );
    }

} /* namespace cds */

#endif /* __CDS_MAP_ABSTRACT_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__ */
