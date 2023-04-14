/*
 * Created by stefan on 28.08.2022.
 */

#ifndef __CDS_TREE_SET_IMPL_HPP__
#define __CDS_TREE_SET_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */

    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprOverride auto TreeSet <
            __ElementType,
            __Comparator
    > :: __iicch_obtainGenericHandler (    /* NOLINT(bugprone-reserved-identifier) */
            cds :: __hidden :: __impl :: __IterableInternalRequestType requestType
    ) noexcept -> __GenericHandler {

        return this->__ss_handlers() [ static_cast < uint32 > ( requestType ) ];
    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprOverride auto TreeSet <
            __ElementType,
            __Comparator
    > :: __iicch_obtainGenericConstHandler (   /* NOLINT(bugprone-reserved-identifier) */
            cds :: __hidden :: __impl :: __IterableInternalRequestType requestType
    ) const noexcept -> __GenericConstHandler {

        return this->__ss_constHandlers() [ static_cast < uint32 > ( requestType ) ];
    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
    > constexpr TreeSet <
            __ElementType,
            __Comparator
    > :: TreeSet () noexcept = default;


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline TreeSet <
            __ElementType,
            __Comparator
    > :: TreeSet (
            TreeSet const & set
    ) noexcept {

        this-> template __rbt_copyCleared < & __hidden :: __impl :: __treeSetCopyConstructor < __ElementType > > ( set );
    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
    > constexpr TreeSet <
            __ElementType,
            __Comparator
    > :: TreeSet (
            TreeSet && set
    ) noexcept :
            Implementation ( std :: move ( set ) ) {

    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
    > template <
            typename __IteratorType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __TElementType,     /* NOLINT(bugprone-reserved-identifier) */
            cds :: meta :: EnableIf <
                    cds :: meta :: isCopyConstructible < __TElementType > ()
            >
    > __CDS_OptimalInline TreeSet <
            __ElementType,
            __Comparator
    > :: TreeSet (
            __IteratorType const & begin,
            __IteratorType const & end,
            Size                   count
    ) noexcept {

        for ( auto iterator = begin; iterator != end; ++ iterator ) {
            this->insert ( * iterator );
        }
    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
    > template <
            typename __TElementType,     /* NOLINT(bugprone-reserved-identifier) */
            cds :: meta :: EnableIf <
                    cds :: meta :: isCopyConstructible < __TElementType > ()
            >
    > __CDS_OptimalInline TreeSet <
            __ElementType,
            __Comparator
    > :: TreeSet (
            std :: initializer_list < __ElementType > const & initializerList
    ) noexcept :
        TreeSet (
                initializerList.begin(),
                initializerList.end()
        ) {

    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
    >
    template < typename __IterableType >     /* NOLINT(bugprone-reserved-identifier) */
    __CDS_OptimalInline TreeSet <
            __ElementType,
            __Comparator
    > :: TreeSet (
            __IterableType const & iterable
    ) noexcept :
        TreeSet (
                iterable.begin(),
                iterable.end()
        ) {

    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprDestructor TreeSet <
            __ElementType,
            __Comparator
    > :: ~TreeSet () noexcept {

        this->__rbt_clear();
    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto TreeSet <
            __ElementType,
            __Comparator
    > :: operator = (  /* NOLINT(bugprone-reserved-identifier) */
            TreeSet const & set
    ) noexcept -> TreeSet & {

        this->template __rbt_copy <
                & __hidden :: __impl :: __treeSetCopyConstructor < __ElementType >
        > ( set );
        return * this;
    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto TreeSet <
            __ElementType,
            __Comparator
    > :: operator = (  /* NOLINT(bugprone-reserved-identifier) */
            TreeSet && set
    ) noexcept -> TreeSet & {

        this->__rbt_move ( std :: move ( set ) );
        return * this;
    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprOverride auto TreeSet <
            __ElementType,
            __Comparator
    > :: contains (
            __ElementType const & element
    ) const noexcept -> bool {

        return this->__rbt_get ( element ) != nullptr;
    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprOverride auto TreeSet <
            __ElementType,
            __Comparator
    > :: size ()  const noexcept -> Size {

        return this->__rbt_size();
    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto TreeSet <
            __ElementType,
            __Comparator
    > :: clear () noexcept -> void {

        this->__rbt_clear();
    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
    >__CDS_OptimalInline auto TreeSet <
            __ElementType,
            __Comparator
    > :: remove (
            __ElementType const & element
    ) noexcept -> bool {

        return this->__rbt_remove ( element );
    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
    >__CDS_cpplang_ConstexprConditioned auto TreeSet <
            __ElementType,
            __Comparator
    > :: operator == (
            TreeSet const & set
    ) const noexcept -> bool {

        if ( this == & set ) {
            return true;
        }

        return this->__rbt_equals (set);
    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __Comparator       /* NOLINT(bugprone-reserved-identifier) */
    >__CDS_cpplang_ConstexprConditioned auto TreeSet <
            __ElementType,
            __Comparator
    > :: operator != (
            TreeSet const & set
    ) const noexcept -> bool {

        if ( this == & set ) {
            return false;
        }

        return ! this->__rbt_equals (set);
    }

}

#endif /* __CDS_TREE_SET_IMPL_HPP__ */
