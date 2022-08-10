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

            return 0ULL;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_VirtualConstexpr auto Collection < __ElementType > :: empty () const noexcept -> bool {

            return this->size() == 0ULL;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_VirtualConstexpr Collection < __ElementType > :: operator bool () const noexcept {

            return this->empty();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Collection < __ElementType > :: toString () const noexcept -> String {

            std :: stringstream oss;
            oss << "Collection at " << std :: hex << reinterpret_cast < AddressValueType const > ( this );
            return oss.str();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Collection < __ElementType > :: hash () const noexcept -> Size {

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

            if ( this == & object ) {
                return true;
            }

            auto pObject = dynamic_cast < decltype ( this ) > ( & object );
            if ( pObject == nullptr ) {
                return false;
            }

            if ( this->size() != pObject->size() ) {
                return false;
            }

            for (
                    auto
                            leftIt  = this->cbegin(),    leftEnd = this->cend(),
                            rightIt = pObject->cbegin();
                    leftIt != leftEnd;
                    ++ leftIt, ++ rightIt
            ) {
                if ( this->__cf_equals ( * leftIt, * rightIt ) ) {
                    return false;
                }
            }

            return true;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Collection < __ElementType > :: remove (
                ElementType const & element
        ) noexcept -> bool {

            for ( auto iterator = this->cbegin(), end = this->cend(); iterator != end; ++ iterator ) {
                if ( this->__cf_equals ( element, * iterator ) ) {
                    return this->remove ( iterator );
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Collection < __ElementType > :: find (
                ElementType const & element
        ) const noexcept -> ConstIterator {

            auto end = this->cend();
            for ( auto iterator = this->cbegin(); iterator != end; ++ iterator ) {
                if ( this->__cf_equals ( element, * iterator ) ) {
                    return iterator;
                }
            }

            return end;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Collection < __ElementType > :: contains (
                ElementType const & element
        ) const noexcept -> bool {

            for ( auto iterator = this->cbegin(), end = this->cend(); iterator != end; ++ iterator ) {
                if ( this->__cf_equals ( element, * iterator ) ) {
                    return true;
                }
            }

            return false;
        }

    }
}


#endif // __CDS_EX_COLLECTION_IMPL_HPP__
