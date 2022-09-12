/*
 * Created by stefan on 28.08.2022.
 */

#ifndef __CDS_TREE_SET_HPP__
#define __CDS_TREE_SET_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template < typename __ElementType >                                                                 /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_ConstexprOverride auto TreeSet < __ElementType > :: __cicch_obtainGenericHandler (    /* NOLINT(bugprone-reserved-identifier) */
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) noexcept -> __GenericHandler {

            return this->__ss_handlers() [ static_cast < uint32 > ( requestType ) ];
        }

        template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_ConstexprOverride auto TreeSet < __ElementType > :: __cicch_obtainGenericConstHandler (   /* NOLINT(bugprone-reserved-identifier) */
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) const noexcept -> __GenericConstHandler {

            return this->__ss_constHandlers() [ static_cast < uint32 > ( requestType ) ];
        }

        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        TreeSet < __ElementType > :: TreeSet () noexcept = default;


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        TreeSet < __ElementType > :: TreeSet (
                TreeSet const & set
        ) noexcept {

            this->__rbt_copyCleared (
                    set,
                    & __hidden :: __impl :: __treeSetCopyConstructor < __ElementType >
            );
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr TreeSet < __ElementType > :: TreeSet (
                TreeSet && set
        ) noexcept :
                Implementation ( std :: move ( set ) ) {

        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        auto TreeSet < __ElementType > :: contains (
                __ElementType const & element
        ) const noexcept -> bool {

            return this -> __rbt_get ( element ) != nullptr;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto TreeSet < __ElementType > :: size ()  const noexcept -> Size {

            return this->__rbt_size();
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        auto TreeSet < __ElementType > :: clear () noexcept -> void {

            this->__rbt_clear();
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        auto TreeSet < __ElementType > :: remove (
                __ElementType const & element
        ) noexcept -> bool {

            return this->__rbt_remove ( element );
        }
    }
}

#endif /* __CDS_TREE_SET_HPP__ */
