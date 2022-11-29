/* NOLINT(llvm-header-guard)
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_COLLECTION_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_COLLECTION_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Function used to insert a pack of values into a collection via forwarding pack expansion. This is the final call of the chain
             * @tparam __ElementType type of elements contained in the collection
             * @tparam __LastType type of the value to be inserted
             * @param [out] collection : Collection ref = Reference to the collection to insert the value in
             * @param [in] element : __LastType fref = Forward Reference to the value to be inserted
             * @exceptsafe
             * @namespace cds :: experimental :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename __ElementType,                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __LastType                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_MaybeUnused inline auto __collectionAdd (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    Collection < __ElementType >    & collection,
                    __LastType                     && element
            ) noexcept -> void {

                /* forward reference into container */
                (void) collection.emplace ( std :: forward < __LastType > ( element ) );
            }


            /**
             * @brief Function used to insert a pack of values into a collection via forwarding pack expansion. This generates all calls for > 3 params
             * @tparam __ElementType type of elements contained in the collection
             * @tparam __FirstType type of the first value in the pack to be inserted
             * @tparam __RemainingTypes type pack of the remaining values to be inserted
             * @param [out] collection : Collection ref = Reference to the collection to insert the value in
             * @param [in] firstElement : __LastType fref = Forward Reference to the first value of the pack to be inserted
             * @param [in] remainingElement : __RemainingTypes fref = Parameter Pack of Forwarding References to the remaining parameters to be inserted
             * @exceptsafe
             * @namespace cds :: experimental :: __hidden :: __impl
             * @internal library-private
             */
            template <
                    typename     __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename     __FirstType,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename ... __RemainingTypes   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > inline auto __collectionAdd (         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    Collection < __ElementType >     &      collection,
                    __FirstType                     &&      firstElement,
                    __RemainingTypes                && ...  remainingElements
            ) noexcept -> void {

                /* forward reference into container */
                (void) collection.emplace ( std :: forward < __FirstType > ( firstElement ) );

                /* forward remaining references to a new insert call */
                __collectionAdd ( collection, std :: forward < __RemainingTypes > ( remainingElements ) ... );
            }

        } /* namespace __impl */
    } /* namespace __hidden */

    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr Collection < __ElementType > :: Collection () noexcept = default;


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr Collection < __ElementType > :: Collection (
            Collection const & collection
    ) noexcept = default;


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr Collection < __ElementType > :: Collection (
            Collection && collection
    ) noexcept = default;


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprDestructor Collection < __ElementType > :: ~Collection () noexcept = default;


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_VirtualConstexpr auto Collection < __ElementType > :: empty () const noexcept -> bool {

        /* A collection is empty if the size is equal to 0 */
        return this->size() == 0ULL;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_VirtualConstexpr Collection < __ElementType > :: operator bool () const noexcept {

        /* Operation equivalent to empty */
        return this->empty();
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto Collection < __ElementType > :: toString () const noexcept -> String {

        /* Default toString implementation, store 'Collection at 0x....'. Use a stringstream for simplicity */
        std :: stringstream oss;
        oss << "Collection at " << std :: hex << reinterpret_cast < AddressValueType const > ( this ); /* NOLINT(clion-misra-cpp2008-5-2-8, *-reinterpret-cast, clion-misra-cpp2008-5-2-5, clion-misra-cpp2008-5-2-9) */

        /* converted to std :: string, and to cds :: String afterwards */
        return oss.str();
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    auto Collection < __ElementType > :: hash () const noexcept -> Size {

        /* Default Collection hash computation formula :
         *      ( ... ( ( h(a[0]) * 31 + h(a[1]) ) * 31 + h(a[2]) ) * 31 + ... ) * 31 + h(a[n - 1])
         *      where h(x) represents a cds :: hash computation over x */
        Size totalHash = 0ULL;
        constexpr uint8 primeFactor = 31U;

        for ( auto iterator = this->cbegin(), end = this->cend(); iterator != end; ++ iterator ) { /* NOLINT(clion-misra-cpp2008-8-0-1) */
            totalHash = totalHash * primeFactor + cds :: hash ( * iterator );
        }

        return totalHash;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    auto Collection < __ElementType > :: equals (
            Object const & object
    ) const noexcept -> bool {

        /* First compute self comparison */
        if ( this == & object ) {
            return true;
        }

        /* Then, if not same, Compute Collection type identification */
        auto const * pObject = dynamic_cast < decltype ( this ) > ( & object ); /* NOLINT(clion-misra-cpp2008-5-2-8, *-reinterpret-cast, clion-misra-cpp2008-5-2-5, clion-misra-cpp2008-5-2-9) */
        if ( pObject == nullptr ) {
            return false;
        }

        /* Then, if both are at least Collection, check sizes */
        if ( this->size() != pObject->size() ) {
            return false;
        }

        /* If sizes are equal, compare each element */
        for (
                auto                                                            /* NOLINT(clion-misra-cpp2008-8-0-1) */
                        leftIt  = this->cbegin(),    leftEnd = this->cend(),
                        rightIt = pObject->cbegin();
                leftIt != leftEnd;
                ++ leftIt, ++ rightIt                                           /* NOLINT(clion-misra-cpp2008-5-18-1) */
        ) {

            /* If, by forward iteration, one pair's elements are different, not equal */
            if ( ! Collection :: __cf_equals ( * leftIt, * rightIt ) ) {        /* NOLINT(clion-misra-cpp2008-5-3-1) */
                return false;
            }
        }

        /* Otherwise, objects are equal content-wise */
        return true;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto Collection < __ElementType > :: contains (
            ElementType const & element
    ) const noexcept -> bool {

        /* Parse object via forward iteration */
        for ( auto iterator = this->cbegin(), end = this->cend(); iterator != end; ++ iterator ) {  /* NOLINT(clion-misra-cpp2008-8-0-1) */

            /* If object found, the object is contained in the collection */
            if ( Collection :: __cf_equals ( element, * iterator ) ) {
                return true;
            }
        }

        /* If full parse complete and not found, object not contained in the collection */
        return false;
    }

} /* namespace cds */


#endif /* __CDS_COLLECTION_IMPL_HPP__ */
