//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_EX_COLLECTION_IMPL_HPP__
#define __CDS_EX_COLLECTION_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template < typename __ElementType, typename __LastType > // NOLINT(bugprone-reserved-identifier)
                inline auto __collectionAdd ( // NOLINT(bugprone-reserved-identifier)
                        Collection < __ElementType >    & collection,
                        __LastType                     && element
                ) noexcept -> void {

                    collection.add ( std :: forward < __LastType > ( element ) );
                }


                template < typename __ElementType, typename __FirstType, typename ... __RemainingTypes > // NOLINT(bugprone-reserved-identifier)
                inline auto __collectionAdd ( // NOLINT(bugprone-reserved-identifier)
                        Collection < __ElementType >     &      collection,
                        __FirstType                     &&      firstElement,
                        __RemainingTypes                && ...  remainingElements
                ) noexcept -> void {

                    collection.add ( std :: forward < __FirstType > ( firstElement ) );
                    __collectionAdd ( collection, std :: forward < __RemainingTypes > ( remainingElements ) ... );
                }

            }
        }

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr Collection < __ElementType > :: Collection () noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr Collection < __ElementType > :: Collection (
                Collection const & collection
        ) noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr Collection < __ElementType > :: Collection (
                Collection && collection
        ) noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprDestructor Collection < __ElementType > :: ~Collection () noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_VirtualConstexpr auto Collection < __ElementType > :: size () const noexcept -> Size {

            /* by default, return 0. No pure virtual implementation due to MinGW bug with cpp-14 constexpr */
            return 0ULL;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_VirtualConstexpr auto Collection < __ElementType > :: empty () const noexcept -> bool {

            /* A collection is empty if the size is equal to 0 */
            return this->size() == 0ULL;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_VirtualConstexpr Collection < __ElementType > :: operator bool () const noexcept {

            /* Operation equivalent to empty */
            return this->empty();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Collection < __ElementType > :: toString () const noexcept -> String {

            /* Default toString implementation, store 'Collection at 0x....'. Use a stringstream for simplicity */
            std :: stringstream oss;
            oss << "Collection at " << std :: hex << reinterpret_cast < AddressValueType const > ( this );

            /* converted to std :: string, and to cds :: String afterwards */
            return oss.str();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: hash () const noexcept -> Size {

            /* Default Collection hash computation formula :
             *      ( ... ( ( h(a[0]) * 31 + h(a[1]) ) * 31 + h(a[2]) ) * 31 + ... ) * 31 + h(a[n - 1])
             *      where h(x) represents a cds :: hash computation over x */
            Size totalHash = 0ULL;

            for ( auto iterator = this->cbegin(), end = this->cend(); iterator != end; ++ iterator ) {
                totalHash = totalHash * 31ULL + cds :: hash ( * iterator );
            }

            return totalHash;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: equals (
                Object const & object
        ) const noexcept -> bool {

            /* First compute self comparison */
            if ( this == & object ) {
                return true;
            }

            /* Then, if not same, Compute Collection type identification */
            auto pObject = dynamic_cast < decltype ( this ) > ( & object );
            if ( pObject == nullptr ) {
                return false;
            }

            /* Then, if both are at least Collection, check sizes */
            if ( this->size() != pObject->size() ) {
                return false;
            }

            /* If sizes are equal, compare each element */
            for (
                    auto
                            leftIt  = this->cbegin(),    leftEnd = this->cend(),
                            rightIt = pObject->cbegin();
                    leftIt != leftEnd;
                    ++ leftIt, ++ rightIt
            ) {

                /* If, by forward iteration, one pair's elements are different, not equal */
                if ( ! this->__cf_equals ( * leftIt, * rightIt ) ) {
                    return false;
                }
            }

            /* Otherwise, objects are equal content-wise */
            return true;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Collection < __ElementType > :: contains (
                ElementType const & element
        ) const noexcept -> bool {

            /* Parse object via forward iteration */
            for ( auto iterator = this->cbegin(), end = this->cend(); iterator != end; ++ iterator ) {

                /* If object found, the object is contained in the collection */
                if ( this->__cf_equals ( element, * iterator ) ) {
                    return true;
                }
            }

            /* If full parse complete and not found, object not contained in the collection */
            return false;
        }

    }
}


#endif // __CDS_EX_COLLECTION_IMPL_HPP__
