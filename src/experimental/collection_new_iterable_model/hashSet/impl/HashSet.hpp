//
// Created by loghin on 10/08/22.
//

#ifndef __CDS_HASH_SET_HPP__
#define __CDS_HASH_SET_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template <
                typename __ElementType, // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_cpplang_ConstexprOverride auto HashSet <
                __ElementType,
                __Hasher
        > :: __cicch_obtainGenericHandler (
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) noexcept -> __GenericHandler {

            return this->__ss_handlers() [ static_cast < uint32 > ( requestType ) ];
        }


        template <
                typename __ElementType, // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_cpplang_ConstexprOverride auto HashSet <
                __ElementType,
                __Hasher
        > :: __cicch_obtainGenericConstHandler (
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) const noexcept -> __GenericConstHandler {

            return this->__ss_constHandlers() [ static_cast < uint32 > ( requestType ) ];
        }


        template <
                typename __ElementType, // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > constexpr HashSet <
                __ElementType,
                __Hasher
        > :: HashSet () noexcept = default;


        template <
                typename __ElementType,     // NOLINT(bugprone-reserved-identifier)
                typename __Hasher           // NOLINT(bugprone-reserved-identifier)
        > template <
                typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                >
        > __CDS_OptimalInline HashSet <
                __ElementType,
                __Hasher
        > :: HashSet (
                HashSet const & set
        ) noexcept {

        };


        template <
                typename __ElementType, // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_OptimalInline HashSet <
                __ElementType,
                __Hasher
        > :: ~HashSet () noexcept {

            this->__ht_clear ();
        }


        template <
                typename __ElementType, // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_cpplang_ConstexprOverride auto HashSet <
                __ElementType,
                __Hasher
        > :: size () const noexcept -> Size {

            return this->__ht_size ();
        }


        template <
                typename __ElementType, // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > constexpr auto HashSet <
                __ElementType,
                __Hasher
        > :: begin () const noexcept -> ConstIterator {

            return this->cbegin();
        }


        template <
                typename __ElementType, // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > constexpr auto HashSet <
                __ElementType,
                __Hasher
        > :: end () const noexcept -> ConstIterator {

            return this->cend();
        }


        template <
                typename __ElementType, // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > constexpr auto HashSet <
                __ElementType,
                __Hasher
        > :: cbegin () const noexcept -> ConstIterator {

            return this->__ht_cbegin();
        }


        template <
                typename __ElementType, // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > constexpr auto HashSet <
                __ElementType,
                __Hasher
        > :: cend () const noexcept -> ConstIterator {

            return this->__ht_cend();
        }


        template <
                typename __ElementType, // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_OptimalInline auto HashSet <
                __ElementType,
                __Hasher
        > :: clear () noexcept -> void {

            return this->__ht_clear();
        }


        template <
                typename __ElementType, // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_OptimalInline auto HashSet <
                __ElementType,
                __Hasher
        > :: remove (
                __ElementType const & element
        ) noexcept -> bool {

            return this->__ht_remove ( element );
        }

    }
}

#endif // __CDS_HASH_SET_HPP__
