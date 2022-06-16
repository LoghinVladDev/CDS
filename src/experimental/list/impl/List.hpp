//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_LIST_IMPL_HPP__
#define __CDS_LIST_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl { // NOLINT(bugprone-reserved-identifier)

                template < typename __ElementType, cds :: meta :: EnableIf < cds :: meta :: isMoveAssignable < __ElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction auto __assign ( // NOLINT(bugprone-reserved-identifier)
                        __ElementType & left,
                        __ElementType & right
                ) noexcept -> __ElementType & {
                    left = std :: move ( right );
                    return * left;
                }
                

                template < typename __ElementType, meta :: EnableIf < ! meta :: isMoveAssignable < __ElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction auto __assign ( // NOLINT(bugprone-reserved-identifier)
                        __ElementType & left,
                        __ElementType & right
                ) noexcept -> __ElementType & {
                    left = right;
                    return * left;
                }
                

                template < typename __ElementType, meta :: EnableIf < meta :: isMoveConstructible < __ElementType > () && meta :: isMoveAssignable < __ElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprNonLiteralReturn auto __swap ( // NOLINT(bugprone-reserved-identifier)
                        __ElementType & left,
                        __ElementType & right
                ) noexcept -> void {

                    auto aux    = std :: move ( left );
                    left        = std :: move ( right );
                    right       = std :: move ( aux );
                }
                

                template < typename __ElementType, meta :: EnableIf < ! meta :: isMoveConstructible < __ElementType > () && ! meta :: isMoveAssignable < __ElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_ConstexprNonLiteralReturn auto __swap ( // NOLINT(bugprone-reserved-identifier)
                        __ElementType & left,
                        __ElementType & right
                ) noexcept -> void {

                    auto aux    = left;
                    left        = right;
                    right       = aux;
                }

                
                template < typename __IteratorType, typename __ComparatorFunction > // NOLINT(bugprone-reserved-identifier)
                auto __quickSortPartition ( // NOLINT(bugprone-reserved-identifier)
                        __IteratorType        const & from,
                        __IteratorType        const & to,
                        __ComparatorFunction  const & function
                ) noexcept -> __IteratorType {

                    auto pivot = * to;
                    auto partitionIterator = from;
                    __IteratorType previous;

                    for (auto it = from; it != to; ++ it ) {
                        if ( function ( * it, pivot ) ) {
                            __swap ( * partitionIterator, * it );
                            previous = partitionIterator;
                            ++ partitionIterator;
                        }
                    }

                    __swap ( * partitionIterator, * to );
                    if ( ! previous.valid() ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                        return partitionIterator;
                    }

                    return previous;
                }

                
                template < typename __IteratorType, typename __ComparatorFunction > // NOLINT(bugprone-reserved-identifier)
                auto __quickSort ( // NOLINT(bugprone-reserved-identifier)
                        __IteratorType        const & from,
                        __IteratorType        const & to,
                        __ComparatorFunction  const & function
                ) noexcept -> void {

                    if ( to.valid() ) {
                        auto actualEnd = to;
                        if ( from == ++ actualEnd ) {
                            return;
                        }
                    }

                    if ( from != to && from.valid() && to.valid() ) {
                        auto partitionIterator = __quickSortPartition (from, to, function );

                        __quickSort ( from, partitionIterator, function );
                        if ( ! partitionIterator.valid() ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                            return;
                        }

                        if ( partitionIterator == from ) {
                            if ( ( ++ partitionIterator ).valid() ) {
                                __quickSort ( partitionIterator, to, function );
                            }

                            return;
                        }

                        if ( ! ( ++ partitionIterator ).valid() ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                            return;
                        }

                        __quickSort ( ++ partitionIterator, to, function );
                    }
                }

            }
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        Index const List < __ElementType > :: invalidIndex;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto List < __ElementType > :: acquireDelegate (
                Iterator const & iterator
        ) noexcept -> DelegateIterator const * {

            return reinterpret_cast < DelegateIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto List < __ElementType > :: acquireDelegate (
                ReverseIterator const & iterator
        ) noexcept -> DelegateIterator const * {

            return reinterpret_cast < DelegateIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: begin () noexcept -> Iterator {

            return Iterator ( this, std :: move ( this->delegateIterator ( DelegateIteratorRequestType :: ForwardBegin ) ) );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: end () noexcept -> Iterator {

            return Iterator ( this, std :: move ( this->delegateIterator ( DelegateIteratorRequestType :: ForwardEnd ) ) );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: rbegin () noexcept -> ReverseIterator {

            return Iterator ( this, std :: move ( this->delegateIterator ( DelegateIteratorRequestType :: BackwardBegin ) ) );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: rend () noexcept -> ReverseIterator {

            return Iterator ( this, std :: move ( this->delegateIterator ( DelegateIteratorRequestType :: BackwardEnd ) ) );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr List < __ElementType > :: List (
                List const & list
        ) noexcept :
                Collection < __ElementType > ( list ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr List < __ElementType > :: List (
                List && list
        ) noexcept :
                Collection < __ElementType > ( std :: move ( list ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr List < __ElementType > :: List (
                Size size
        ) noexcept :
                Collection < __ElementType > ( size ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: pNewInsert (
                ElementType const & referenceElement
        ) noexcept -> ElementType * & {

            (void) referenceElement;
            return this->pNewBack();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __CollectionType, typename __VElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () && meta :: isDerivedFrom < __CollectionType, Collection < __ElementType > > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: sub (
                __CollectionType  & storeIn,
                Index               from,
                Index               to
        ) const noexcept -> __CollectionType & {

            if ( from > to ) {
                std :: swap ( from, to );
            }

            if ( from < 0 ) {
                from = 0;
            }

            if ( to >= this->size() ) {
                to = this->size();
            }

            Index index __CDS_MaybeUnused = 0;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if (index >= from && index < to ) {
                    storeIn.add ( * iterator );
                }

                ++ index;
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __CollectionType, typename __VElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () && meta :: isDerivedFrom < __CollectionType, Collection < __ElementType > > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: sub (
                Index from,
                Index to
        ) const noexcept -> __CollectionType {

            __CollectionType list;
            return this->sub ( list, from, to );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType, typename __VElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () && meta :: isDerivedFrom < __CollectionType < __ElementType >, Collection < __ElementType > > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: sub (
                Index from,
                Index to
        ) const noexcept -> __CollectionType < ElementType > {

            return this->sub < __CollectionType < __ElementType > > ( from, to );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: operator [] (
                Index index
        ) noexcept (false) -> ElementType & {

            return this->get ( index );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: operator [] (
                Index index
        ) const noexcept (false) -> ElementType const & {

            return this->get ( index );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: pushBack (
                ElementType const & element
        ) noexcept -> ElementType & {

            auto & pNew = this->pNewBack();
            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( element );
            return * pNew;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: pushBack (
                ElementType && element
        ) noexcept -> ElementType & {

            auto & pNew = this->pNewBack();
            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( std :: move ( element ) );
            return * pNew;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: pushFront (
                ElementType const & element
        ) noexcept -> ElementType & {

            auto & pNew = this->pNewFront();
            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( element );
            return * pNew;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: pushFront (
                ElementType && element
        ) noexcept -> ElementType & {

            auto & pNew = this->pNewFront();
            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( std :: move ( element ) );
            return * pNew;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: insertBefore (
                Iterator    const & iterator,
                ElementType const & element
        ) noexcept (false) -> ElementType & {

            if ( ! iterator.of ( this ) ) {
                throw IllegalArgumentException ( "Iterator not of this Collection" );
            }

            if ( iterator == this->begin() ) {
                return this->pushFront ( element );
            }

            if ( iterator == this->end() ) {
                return this->pushBack ( element );
            }

            if ( ! iterator.valid () ) {
                throw OutOfBoundsException ( "Iterator out of bounds" );
            }

            auto & pNew = this->pNewBefore ( iterator );

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( element );
            return * pNew;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: insertBefore (
                Iterator    const & iterator,
                ElementType      && element
        ) noexcept (false) -> ElementType & {

            if ( ! iterator.of ( this ) ) {
                throw IllegalArgumentException ( "Iterator not of this Collection" );
            }

            if ( iterator == this->begin() ) {
                return this->pushFront ( std :: move ( element ) );
            }

            if ( iterator == this->end() ) {
                return this->pushBack ( std :: move ( element ) );
            }

            if ( ! iterator.valid () ) {
                throw OutOfBoundsException ( "Iterator out of bounds" );
            }

            auto & pNew = this->pNewBefore ( iterator );

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( std :: move ( element ) );
            return * pNew;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: insertAfter (
                Iterator    const & iterator,
                ElementType const & element
        ) noexcept (false) -> ElementType & {

            if ( ! iterator.of ( this ) ) {
                throw IllegalArgumentException ( "Iterator not of this Collection" );
            }

            if ( ! iterator.valid () ) {
                throw OutOfBoundsException ( "Iterator out of bounds" );
            }

            auto & pNew = this->pNewAfter ( iterator );

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( element );
            return * pNew;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: insertAfter (
                Iterator    const & iterator,
                ElementType      && element
        ) noexcept (false) -> ElementType & {

            if ( ! iterator.of ( this ) ) {
                throw IllegalArgumentException ( "Iterator not of this Collection" );
            }

            if ( ! iterator.valid () ) {
                throw OutOfBoundsException ( "Iterator out of bounds" );
            }

            auto & pNew = this->pNewAfter ( iterator );

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( std :: move ( element ) );
            return * pNew;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: insertBefore (
                ConstIterator   const & iterator,
                ElementType     const & element
        ) noexcept (false) -> ElementType & {

            if ( ! iterator.of ( this ) ) {
                throw IllegalArgumentException ( "Iterator not of this Collection" );
            }

            if ( iterator == this->cbegin() ) {
                return this->pushFront ( element );
            }

            if ( iterator == this->cend() ) {
                return this->pushBack ( element );
            }

            if ( ! iterator.valid () ) {
                throw OutOfBoundsException ( "Iterator out of bounds" );
            }

            auto & pNew = this->pNewBefore ( iterator );

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( element );
            return * pNew;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: insertBefore (
                ConstIterator  const & iterator,
                ElementType         && element
        ) noexcept (false) -> ElementType & {

            if ( ! iterator.of ( this ) ) {
                throw IllegalArgumentException ( "Iterator not of this Collection" );
            }

            if ( iterator == this->cbegin() ) {
                return this->pushFront ( std :: move ( element ) );
            }

            if ( iterator == this->cend() ) {
                return this->pushBack ( std :: move ( element ) );
            }

            if ( ! iterator.valid () ) {
                throw OutOfBoundsException ( "Iterator out of bounds" );
            }

            auto & pNew = this->pNewBefore ( iterator );

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( std :: move ( element ) );
            return * pNew;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: insertAfter (
                ConstIterator   const & iterator,
                ElementType     const & element
        ) noexcept (false) -> ElementType & {

            if ( ! iterator.of ( this ) ) {
                throw IllegalArgumentException ( "Iterator not of this Collection" );
            }

            if ( ! iterator.valid () ) {
                throw OutOfBoundsException ( "Iterator out of bounds" );
            }

            auto & pNew = this->pNewAfter ( iterator );

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( element );
            return * pNew;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: insertAfter (
                ConstIterator  const & iterator,
                ElementType         && element
        ) noexcept (false) -> ElementType & {

            if ( ! iterator.of ( this ) ) {
                throw IllegalArgumentException ( "Iterator not of this Collection" );
            }

            if ( ! iterator.valid () ) {
                throw OutOfBoundsException ( "Iterator out of bounds" );
            }

            auto & pNew = this->pNewAfter ( iterator );

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( std :: move ( element ) );
            return * pNew;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: insertBefore (
                ReverseIterator const & iterator,
                ElementType     const & element
        ) noexcept (false) -> ElementType & {

            if ( ! iterator.of ( this ) ) {
                throw IllegalArgumentException ( "Iterator not of this Collection" );
            }

            if ( iterator == this->rbegin() ) {
                return this->pushFront ( element );
            }

            if ( iterator == this->rend() ) {
                return this->pushBack ( element );
            }

            if ( ! iterator.valid () ) {
                throw OutOfBoundsException ( "Iterator out of bounds" );
            }

            auto & pNew = this->pNewBefore ( iterator );

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( element );
            return * pNew;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: insertBefore (
                ReverseIterator const & iterator,
                ElementType          && element
        ) noexcept (false) -> ElementType & {

            if ( ! iterator.of ( this ) ) {
                throw IllegalArgumentException ( "Iterator not of this Collection" );
            }

            if ( iterator == this->begin() ) {
                return this->pushFront ( std :: move ( element ) );
            }

            if ( iterator == this->end() ) {
                return this->pushBack ( std :: move ( element ) );
            }

            if ( ! iterator.valid () ) {
                throw OutOfBoundsException ( "Iterator out of bounds" );
            }

            auto & pNew = this->pNewBefore ( iterator );

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( std :: move ( element ) );
            return * pNew;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: insertAfter (
                ReverseIterator const & iterator,
                ElementType     const & element
        ) noexcept (false) -> ElementType & {

            if ( ! iterator.of ( this ) ) {
                throw IllegalArgumentException ( "Iterator not of this Collection" );
            }

            if ( ! iterator.valid () ) {
                throw OutOfBoundsException ( "Iterator out of bounds" );
            }

            auto & pNew = this->pNewAfter ( iterator );

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( element );
            return * pNew;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: insertAfter (
                ReverseIterator const & iterator,
                ElementType          && element
        ) noexcept (false) -> ElementType & {

            if ( ! iterator.of ( this ) ) {
                throw IllegalArgumentException ( "Iterator not of this Collection" );
            }

            if ( ! iterator.valid () ) {
                throw OutOfBoundsException ( "Iterator out of bounds" );
            }

            auto & pNew = this->pNewAfter ( iterator );

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( std :: move ( element ) );
            return * pNew;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: insertBefore (
                ConstReverseIterator    const & iterator,
                ElementType             const & element
        ) noexcept (false) -> ElementType & {

            if ( ! iterator.of ( this ) ) {
                throw IllegalArgumentException ( "Iterator not of this Collection" );
            }

            if ( iterator == this->crbegin() ) {
                return this->pushFront ( element );
            }

            if ( iterator == this->crend() ) {
                return this->pushBack ( element );
            }

            if ( ! iterator.valid () ) {
                throw OutOfBoundsException ( "Iterator out of bounds" );
            }

            auto & pNew = this->pNewBefore ( iterator );

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( element );
            return * pNew;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: insertBefore (
                ConstReverseIterator const & iterator,
                ElementType               && element
        ) noexcept (false) -> ElementType & {

            if ( ! iterator.of ( this ) ) {
                throw IllegalArgumentException ( "Iterator not of this Collection" );
            }

            if ( iterator == this->crbegin() ) {
                return this->pushFront ( std :: move ( element ) );
            }

            if ( iterator == this->crend() ) {
                return this->pushBack ( std :: move ( element ) );
            }

            if ( ! iterator.valid () ) {
                throw OutOfBoundsException ( "Iterator out of bounds" );
            }

            auto & pNew = this->pNewBefore ( iterator );

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( std :: move ( element ) );
            return * pNew;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: insertAfter (
                ConstReverseIterator    const & iterator,
                ElementType             const & element
        ) noexcept (false) -> ElementType & {

            if ( ! iterator.of ( this ) ) {
                throw IllegalArgumentException ( "Iterator not of this Collection" );
            }

            if ( ! iterator.valid () ) {
                throw OutOfBoundsException ( "Iterator out of bounds" );
            }

            auto & pNew = this->pNewAfter ( iterator );

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( element );
            return * pNew;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: insertAfter (
                ConstReverseIterator const & iterator,
                ElementType               && element
        ) noexcept (false) -> ElementType & {

            if ( ! iterator.of ( this ) ) {
                throw IllegalArgumentException ( "Iterator not of this Collection" );
            }

            if ( ! iterator.valid () ) {
                throw OutOfBoundsException ( "Iterator out of bounds" );
            }

            auto & pNew = this->pNewAfter ( iterator );

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( std :: move ( element ) );
            return * pNew;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: append (
                ElementType const & element
        ) noexcept -> ElementType & {

            return this->pushBack ( element );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: append (
                ElementType && element
        ) noexcept -> ElementType & {

            return this->pushBack ( std :: move ( element ) );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: prepend (
                ElementType const & element
        ) noexcept -> ElementType & {

            return this->pushFront ( element );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isMoveConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: prepend (
                ElementType && element
        ) noexcept -> ElementType & {

            return this->pushFront ( std :: move ( element ) );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __ComparatorFunction > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: sort (
                __ComparatorFunction const & comparatorFunction
        ) noexcept ( noexcept ( comparatorFunction ( meta :: valueOf < ElementType > (), meta :: valueOf < ElementType > () ) ) ) -> void {

            if ( this->size() < 2 ) {
                return;
            }

            Iterator last = -- this->end();
            if ( last == this->end() ) {
                for ( auto it = this->begin(), end = this->end(); it != end; ++ it ) { // NOLINT(clion-misra-cpp2008-8-0-1)
                    last = it;
                }
            }

            __hidden :: __impl :: __quickSort ( this->begin(), last, comparatorFunction );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replace (
                Size                count,
                ElementType const & what,
                ElementType const & with
        ) noexcept -> Size {

            Size replacedCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( replacedCount < count ) {
                    if ( meta :: equals ( * iterator, what ) ) {
                        * iterator = with;
                        ++ replacedCount;
                    }

                } else {
                    return count;
                }
            }

            return replacedCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceAll (
                ElementType const & what,
                ElementType const & with
        ) noexcept -> Size {

            Size replacedCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( meta :: equals ( * iterator, what ) ) {
                    * iterator = with;
                    ++ replacedCount;
                }
            }

            return replacedCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceFirst (
                ElementType const & what,
                ElementType const & with
        ) noexcept -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( meta :: equals ( * iterator, what ) ) {
                    * iterator = with;
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isMoveAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceFirst (
                ElementType const & what,
                ElementType      && with
        ) noexcept -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( meta :: equals ( * iterator, what ) ) {
                    * iterator = std :: move ( with );
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceLast (
                ElementType const & what,
                ElementType const & with
        ) noexcept -> bool {

            for ( auto iterator = this->rbegin(), end = this->rend(); iterator != end; ++ iterator ) {
                if ( meta :: equals ( * iterator, what ) ) {
                    * iterator = with;
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isMoveAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceLast (
                ElementType const & what,
                ElementType      && with
        ) noexcept -> bool {

            for ( auto iterator = this->rbegin(), end = this->rend(); iterator != end; ++ iterator ) {
                if ( meta :: equals ( * iterator, what ) ) {
                    * iterator = std :: move ( with );
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceOf (
                Size                                count,
                Collection < ElementType >  const & of,
                ElementType                 const & with
        ) noexcept -> Size {

            Size replacedCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( replacedCount < count ) {
                    if ( of.contains ( * iterator ) ) {
                        * iterator = with;
                        ++ replacedCount;
                    }

                } else {
                    return count;
                }
            }

            return replacedCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceAllOf (
                Collection < ElementType >  const & of,
                ElementType                 const & with
        ) noexcept -> Size {

            Size replacedCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( of.contains ( * iterator ) ) {
                    * iterator = with;
                    ++ replacedCount;
                }
            }

            return replacedCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceFirstOf (
                Collection < ElementType >  const & of,
                ElementType                 const & with
        ) noexcept -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( of.contains ( * iterator ) ) {
                    * iterator = with;
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isMoveAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceFirstOf (
                Collection < ElementType >  const & of,
                ElementType                      && with
        ) noexcept -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( of.contains ( * iterator ) ) {
                    * iterator = std :: move ( with );
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceLastOf (
                Collection < ElementType >  const & of,
                ElementType                 const & with
        ) noexcept -> bool {

            for ( auto iterator = this->rbegin(), end = this->rend(); iterator != end; ++ iterator ) {
                if ( of.contains ( * iterator ) ) {
                    * iterator = with;
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isMoveAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceLastOf (
                Collection < ElementType >  const & of,
                ElementType                      && with
        ) noexcept -> bool {

            for ( auto iterator = this->rbegin(), end = this->rend(); iterator != end; ++ iterator ) {
                if ( of.contains ( * iterator ) ) {
                    * iterator = std :: move ( with );
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceNotOf (
                Size                                count,
                Collection < ElementType >  const & of,
                ElementType                 const & with
        ) noexcept -> Size {

            Size replacedCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( replacedCount < count ) {
                    if ( ! of.contains ( * iterator ) ) {
                        * iterator = with;
                        ++ replacedCount;
                    }

                } else {
                    return count;
                }
            }

            return replacedCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceAllNotOf (
                Collection < ElementType >  const & of,
                ElementType                 const & with
        ) noexcept -> Size {

            Size replacedCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! of.contains ( * iterator ) ) {
                    * iterator = with;
                    ++ replacedCount;
                }
            }

            return replacedCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceFirstNotOf (
                Collection < ElementType >  const & of,
                ElementType                 const & with
        ) noexcept -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! of.contains ( * iterator ) ) {
                    * iterator = with;
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isMoveAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceFirstNotOf (
                Collection < ElementType >  const & of,
                ElementType                      && with
        ) noexcept -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! of.contains ( * iterator ) ) {
                    * iterator = std :: move ( with );
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceLastNotOf (
                Collection < ElementType >  const & of,
                ElementType                 const & with
        ) noexcept -> bool {

            for ( auto iterator = this->rbegin(), end = this->rend(); iterator != end; ++ iterator ) {
                if ( ! of.contains ( * iterator ) ) {
                    * iterator = with;
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isMoveAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceLastNotOf (
                Collection < ElementType >  const & of,
                ElementType                      && with
        ) noexcept -> bool {

            for ( auto iterator = this->rbegin(), end = this->rend(); iterator != end; ++ iterator ) {
                if ( ! of.contains ( * iterator ) ) {
                    * iterator = std :: move ( with );
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceOf (
                Size                                count,
                InitializerList             const & of,
                ElementType                 const & with
        ) noexcept -> Size {

            Size replacedCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( replacedCount < count ) {
                    if ( __hidden :: __impl :: __initializerListContains ( of, * iterator ) ) {
                        * iterator = with;
                        ++ replacedCount;
                    }

                } else {
                    return count;
                }
            }

            return replacedCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceAllOf (
                InitializerList             const & of,
                ElementType                 const & with
        ) noexcept -> Size {

            Size replacedCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( __hidden :: __impl :: __initializerListContains ( of, * iterator ) ) {
                    * iterator = with;
                    ++ replacedCount;
                }
            }

            return replacedCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceFirstOf (
                InitializerList             const & of,
                ElementType                 const & with
        ) noexcept -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( __hidden :: __impl :: __initializerListContains ( of, * iterator ) ) {
                    * iterator = with;
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isMoveAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceFirstOf (
                InitializerList             const & of,
                ElementType                      && with
        ) noexcept -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( __hidden :: __impl :: __initializerListContains ( of, * iterator ) ) {
                    * iterator = std :: move ( with );
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceLastOf (
                InitializerList             const & of,
                ElementType                 const & with
        ) noexcept -> bool {

            for ( auto iterator = this->rbegin(), end = this->rend(); iterator != end; ++ iterator ) {
                if ( __hidden :: __impl :: __initializerListContains ( of, * iterator ) ) {
                    * iterator = with;
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isMoveAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceLastOf (
                InitializerList             const & of,
                ElementType                      && with
        ) noexcept -> bool {

            for ( auto iterator = this->rbegin(), end = this->rend(); iterator != end; ++ iterator ) {
                if ( __hidden :: __impl :: __initializerListContains ( of, * iterator ) ) {
                    * iterator = std :: move ( with );
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceNotOf (
                Size                                count,
                InitializerList             const & of,
                ElementType                 const & with
        ) noexcept -> Size {

            Size replacedCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( replacedCount < count ) {
                    if ( ! __hidden :: __impl :: __initializerListContains ( of, * iterator ) ) {
                        * iterator = with;
                        ++ replacedCount;
                    }

                } else {
                    return count;
                }
            }

            return replacedCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceAllNotOf (
                InitializerList             const & of,
                ElementType                 const & with
        ) noexcept -> Size {

            Size replacedCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! __hidden :: __impl :: __initializerListContains ( of, * iterator ) ) {
                    * iterator = with;
                    ++ replacedCount;
                }
            }

            return replacedCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceFirstNotOf (
                InitializerList             const & of,
                ElementType                 const & with
        ) noexcept -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! __hidden :: __impl :: __initializerListContains ( of, * iterator ) ) {
                    * iterator = with;
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isMoveAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceFirstNotOf (
                InitializerList             const & of,
                ElementType                      && with
        ) noexcept -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! __hidden :: __impl :: __initializerListContains ( of, * iterator ) ) {
                    * iterator = std :: move ( with );
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceLastNotOf (
                InitializerList             const & of,
                ElementType                 const & with
        ) noexcept -> bool {

            for ( auto iterator = this->rbegin(), end = this->rend(); iterator != end; ++ iterator ) {
                if ( ! __hidden :: __impl :: __initializerListContains ( of, * iterator ) ) {
                    * iterator = with;
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isMoveAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceLastNotOf (
                InitializerList             const & of,
                ElementType                      && with
        ) noexcept -> bool {

            for ( auto iterator = this->rbegin(), end = this->rend(); iterator != end; ++ iterator ) {
                if ( ! __hidden :: __impl :: __initializerListContains ( of, * iterator ) ) {
                    * iterator = std :: move ( with );
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate, typename __VElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replace (
                Size                count,
                __Predicate const & predicate,
                ElementType const & with
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> Size {

            Size replacedCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( replacedCount < count ) {
                    if ( predicate ( * iterator ) ) {
                        * iterator = with;
                        ++ replacedCount;
                    }

                } else {
                    return count;
                }
            }

            return replacedCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate, typename __VElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceAll (
                __Predicate const & predicate,
                ElementType const & with
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> Size {

            Size replacedCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    * iterator = with;
                    ++ replacedCount;
                }
            }

            return replacedCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate, typename __VElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceFirst (
                __Predicate const & predicate,
                ElementType const & with
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    * iterator = with;
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate, typename __VElementType, meta :: EnableIf < meta :: isMoveAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceFirst (
                __Predicate const & predicate,
                ElementType      && with
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    * iterator = std :: move ( with );
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate, typename __VElementType, meta :: EnableIf < meta :: isCopyAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceLast (
                __Predicate const & predicate,
                ElementType const & with
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

            for ( auto iterator = this->rbegin(), end = this->rend(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    * iterator = with;
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate, typename __VElementType, meta :: EnableIf < meta :: isMoveAssignable < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceLast (
                __Predicate const & predicate,
                ElementType      && with
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

            for ( auto iterator = this->rbegin(), end = this->rend(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    * iterator = std :: move ( with );
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate, typename __Supplier > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replace (
                Size                count,
                __Predicate const & predicate,
                __Supplier  const & supplier
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( meta :: referenceOf < ElementType > () ) ) ) -> Size {

            Size replacedCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( replacedCount < count ) {
                    if ( predicate ( * iterator ) ) {
                        (void) __hidden :: __impl :: __assign ( * iterator, supplier ( std :: move ( * iterator ) ) );
                        ++ replacedCount;
                    }

                } else {
                    return count;
                }
            }

            return replacedCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate, typename __Supplier > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceAll (
                __Predicate const & predicate,
                __Supplier  const & supplier
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( meta :: referenceOf < ElementType > () ) ) ) -> Size {

            Size replacedCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    (void) __hidden :: __impl :: __assign ( * iterator, supplier ( std :: move ( * iterator ) ) );
                    ++ replacedCount;
                }
            }

            return replacedCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate, typename __Supplier > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceFirst (
                __Predicate const & predicate,
                __Supplier  const & supplier
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    (void) __hidden :: __impl :: __assign ( * iterator, supplier ( std :: move ( * iterator ) ) );
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate, typename __Supplier > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: replaceLast (
                __Predicate const & predicate,
                __Supplier  const & supplier
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

            for ( auto iterator = this->rbegin(), end = this->rend(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    (void) __hidden :: __impl :: __assign ( * iterator, supplier ( std :: move ( * iterator ) ) );
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: toString () const noexcept -> String {
            
            if ( this->empty() ) {
                return {"[]"};
            }

            std::stringstream out;
            out << "[ ";

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {

                meta :: print ( out, * iterator ) << ", ";
            }

            auto asString = out.str();

            asString [ asString.length() - 2U ] = ' ';
            asString [ asString.length() - 1U ] = ']';

            return asString;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __CollectionType, meta :: EnableIf < meta :: isDerivedFrom < __CollectionType, Collection < Index > > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: indices (
                Size                  count,
                __CollectionType    & storeIn,
                ElementType   const & element
        ) const noexcept -> __CollectionType & {

            Index index = 0;
            Size foundCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && foundCount < count; ++ iterator, ++ index ) {
                if ( meta :: equals ( * iterator, element ) ) {
                    storeIn.add ( index );
                    ++ foundCount;
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __CollectionType, meta :: EnableIf < meta :: isDerivedFrom < __CollectionType, Collection < Index > > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: indices (
                Size                count,
                ElementType const & element
        ) const noexcept -> __CollectionType {

            __CollectionType list;
            return this->indices ( count, list, element );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType, meta :: EnableIf < meta :: isDerivedFrom < __CollectionType < Index >, Collection < Index > > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: indices (
                Size                count,
                ElementType const & element
        ) const noexcept -> __CollectionType < Index > {

            return this->indices < __CollectionType < __ElementType > > ( count, element );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: firstIndex (
                ElementType const & element
        ) const noexcept -> Index {

            Index index = 0;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator, ++ index ) {
                if ( meta :: equals ( * iterator, element ) ) {
                    return index;
                }
            }

            return List :: invalidIndex;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: lastIndex (
                ElementType const & element
        ) const noexcept -> Index {

            Index index = static_cast < Index > ( this->size() ) - 1;
            for ( auto iterator = this->rbegin(), end = this->rend(); iterator != end; ++ iterator, -- index ) {
                if ( meta :: equals ( * iterator, element ) ) {
                    return index;
                }
            }

            return List :: invalidIndex;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __CollectionType, meta :: EnableIf < meta :: isDerivedFrom < __CollectionType, Collection < Index > > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: allIndices (
                __CollectionType    & storeIn,
                ElementType   const & element
        ) const noexcept -> __CollectionType & {

            Index index = 0;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator, ++ index ) {
                if ( meta :: equals ( * iterator, element ) ) {
                    storeIn.add ( index );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __CollectionType, meta :: EnableIf < meta :: isDerivedFrom < __CollectionType, Collection < Index > > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: allIndices (
                ElementType const & element
        ) const noexcept -> __CollectionType {

            __CollectionType list;
            return this->allIndices ( list, element );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType, meta :: EnableIf < meta :: isDerivedFrom < __CollectionType < Index >, Collection < Index > > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: allIndices (
                ElementType const & element
        ) const noexcept -> __CollectionType < Index > {

            return this->allIndices < __CollectionType < __ElementType > > ( element );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate, typename __CollectionType, meta :: EnableIf < meta :: isDerivedFrom < __CollectionType, Collection < Index > > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: indices (
                Size                  count,
                __CollectionType    & storeIn,
                __Predicate   const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType & {

            Index index = 0;
            Size foundCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && foundCount < count; ++ iterator, ++ index ) {
                if ( predicate ( * iterator ) ) {
                    storeIn.add ( index );
                    ++ foundCount;
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate, typename __CollectionType, meta :: EnableIf < meta :: isDerivedFrom < __CollectionType, Collection < Index > > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: indices (
                Size                count,
                __Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType {

            __CollectionType list;
            return this->indices ( count, list, predicate );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate, template < typename ... > class __CollectionType, meta :: EnableIf < meta :: isDerivedFrom < __CollectionType < Index >, Collection < Index > > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: indices (
                Size                count,
                __Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType < Index > {

            return this->indices < __CollectionType < __ElementType > > ( count, predicate );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: firstIndex (
                __Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> Index {

            Index index = 0;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator, ++ index ) {
                if ( predicate ( * iterator ) ) {
                    return index;
                }
            }

            return List :: invalidIndex;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: lastIndex (
                __Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> Index {

            Index index = static_cast < Index > ( this->size() ) - 1;
            for ( auto iterator = this->rbegin(), end = this->rend(); iterator != end; ++ iterator, -- index ) {
                if ( predicate ( * iterator ) ) {
                    return index;
                }
            }

            return List :: invalidIndex;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate, typename __CollectionType, meta :: EnableIf < meta :: isDerivedFrom < __CollectionType, Collection < Index > > () > > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: allIndices (
                __CollectionType    & storeIn,
                __Predicate   const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType & {

            Index index = 0;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator, ++ index ) {
                if ( predicate ( * iterator ) ) {
                    storeIn.add ( index );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate, typename __CollectionType, meta :: EnableIf < meta :: isDerivedFrom < __CollectionType, Collection < Index > > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: allIndices (
                __Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType {

            __CollectionType list;
            return this->allIndices ( list, predicate );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate, template < typename ... > class __CollectionType, meta :: EnableIf < meta :: isDerivedFrom < __CollectionType < Index >, Collection < Index > > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: allIndices (
                __Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> __CollectionType < Index > {

            return this->allIndices < __CollectionType < Index > > ( predicate );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: find (
                Size                                        maxCount,
                ElementType                         const & element,
                __CollectionType < Iterator >             & storeIn
        ) noexcept -> __CollectionType < Iterator > & {

            Size found = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && found < maxCount; ++ iterator ) {
                if ( meta :: equals ( element, * iterator ) ) {
                    ++ found;

                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: find (
                Size                                        maxCount,
                ElementType                         const & element
        ) noexcept -> __CollectionType < Iterator > {

            __CollectionType < Iterator > iterators;
            return this-> find ( maxCount, element, iterators );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findFirst (
                ElementType const & element
        ) noexcept -> Iterator {

            auto end = this->end();
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( meta :: equals ( element, * iterator ) ) {
                    return iterator;
                }
            }

            return end;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findLast (
                ElementType const & element
        ) noexcept -> Iterator {

            auto end = this->end();
            auto lastFound = end;
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( meta :: equals ( element, * iterator ) ) {
                    lastFound = iterator;
                }
            }

            return lastFound;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findAll (
                ElementType                         const & element,
                __CollectionType < Iterator >             & storeIn
        ) noexcept -> __CollectionType < Iterator > & {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( meta :: equals ( element, * iterator ) ) {
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findAll (
                ElementType                         const & element
        ) noexcept -> __CollectionType < Iterator > {

            __CollectionType < Iterator > iterators;
            return this-> findAll ( element, iterators );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findOf (
                Size                                        maxCount,
                Collection < ElementType >          const & elements,
                __CollectionType < Iterator >             & storeIn
        ) noexcept -> __CollectionType < Iterator > & {

            Size found = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && found < maxCount; ++ iterator ) {
                if ( elements.contains ( * iterator ) ) {
                    ++ found;

                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findOf (
                Size                                        maxCount,
                Collection < ElementType >          const & elements
        ) noexcept -> __CollectionType < Iterator > {

            __CollectionType < Iterator > iterators;
            return this-> findOf ( maxCount, elements, iterators );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findFirstOf (
                Collection < ElementType > const & elements
        ) noexcept -> Iterator {

            auto end = this->end();
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( elements.contains ( * iterator ) ) {
                    return iterator;
                }
            }

            return end;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findLastOf (
                Collection < ElementType > const & elements
        ) noexcept -> Iterator {

            auto end = this->end();
            auto lastFound = end;
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( elements.contains ( * iterator ) ) {
                    lastFound = end;
                }
            }

            return lastFound;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findAllOf (
                Collection < ElementType >          const & elements,
                __CollectionType < Iterator >               & storeIn
        ) noexcept -> __CollectionType < Iterator > & {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( elements.contains ( * iterator ) ) {
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findAllOf (
                Collection < ElementType >          const & elements
        ) noexcept -> __CollectionType < Iterator > {

            Collection < Iterator > iterators;
            return this->findAllOf ( elements, iterators );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findNotOf (
                Size                                        maxCount,
                Collection < ElementType >          const & elements,
                __CollectionType < Iterator >             & storeIn
        ) noexcept -> __CollectionType < Iterator > & {

            Size found = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && found < maxCount; ++ iterator ) {
                if ( ! elements.contains ( * iterator ) ) {
                    ++ found;

                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findNotOf (
                Size                                        maxCount,
                Collection < ElementType >          const & elements
        ) noexcept -> __CollectionType < Iterator > {

            __CollectionType < Iterator > iterators;
            return this-> findNotOf ( maxCount, elements, iterators );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findFirstNotOf (
                Collection < ElementType > const & elements
        ) noexcept -> Iterator {

            auto end = this->end();
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( ! elements.contains ( * iterator ) ) {
                    return iterator;
                }
            }

            return end;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findLastNotOf (
                Collection < ElementType > const & elements
        ) noexcept -> Iterator {

            auto end = this->end();
            auto lastFound = end;
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( ! elements.contains ( * iterator ) ) {
                    lastFound = iterator;
                }
            }

            return lastFound;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findAllNotOf (
                Collection < ElementType >          const & elements,
                __CollectionType < Iterator >             & storeIn
        ) noexcept -> __CollectionType < Iterator > & {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! elements.contains ( * iterator ) ) {
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findAllNotOf (
                Collection < ElementType >  const & elements
        ) noexcept -> __CollectionType < Iterator > {

            __CollectionType < Iterator > iterators;
            return this-> findAllNotOf ( elements, iterators );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findOf (
                Size                                        maxCount,
                InitializerList                     const & elements,
                __CollectionType < Iterator >             & storeIn
        ) noexcept -> __CollectionType < Iterator > & {

            Size found = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && found < maxCount; ++ iterator ) {
                if ( __hidden :: __impl :: __initializerListContains ( elements, * iterator ) ) {
                    ++ found;

                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findOf (
                Size                                        maxCount,
                InitializerList                     const & elements
        ) noexcept -> __CollectionType < Iterator > {

            __CollectionType < Iterator > iterators;
            return this-> findOf ( maxCount, elements, iterators );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findFirstOf (
                InitializerList const & elements
        ) noexcept -> Iterator {

            auto end = this->end();
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( __hidden :: __impl :: __initializerListContains ( elements, * iterator ) ) {
                    return iterator;
                }
            }

            return end;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findLastOf (
                InitializerList const & elements
        ) noexcept -> Iterator {

            auto end = this->end();
            auto lastFound = end;
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( __hidden :: __impl :: __initializerListContains ( elements, * iterator ) ) {
                    lastFound = iterator;
                }
            }

            return lastFound;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findAllOf (
                InitializerList                     const & elements,
                __CollectionType < Iterator >               & storeIn
        ) noexcept -> __CollectionType < Iterator > & {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( __hidden :: __impl :: __initializerListContains ( elements, * iterator ) ) {
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findAllOf (
                InitializerList                     const & elements
        ) noexcept -> __CollectionType < Iterator > {

            Collection < Iterator > iterators;
            return this->findAllOf ( elements, iterators );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findNotOf (
                Size                                        maxCount,
                InitializerList                     const & elements,
                __CollectionType < Iterator >               & storeIn
        ) noexcept -> __CollectionType < Iterator > & {

            Size found = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && found < maxCount; ++ iterator ) {
                if ( ! __hidden :: __impl :: __initializerListContains ( elements, * iterator ) ) {
                    ++ found;

                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findNotOf (
                Size                                        maxCount,
                InitializerList                     const & elements
        ) noexcept -> __CollectionType < Iterator > {

            __CollectionType < Iterator > iterators;
            return this-> findNotOf ( maxCount, elements, iterators );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findFirstNotOf (
                InitializerList                     const & elements
        ) noexcept -> Iterator {

            auto end = this->end();
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( ! __hidden :: __impl :: __initializerListContains ( elements,  * iterator ) ) {
                    return iterator;
                }
            }

            return end;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findLastNotOf (
                InitializerList                     const & elements
        ) noexcept -> Iterator {

            auto end = this->end();
            auto lastFound = end;
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( ! __hidden :: __impl :: __initializerListContains ( elements,  * iterator ) ) {
                    lastFound = iterator;
                }
            }

            return lastFound;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findAllNotOf (
                InitializerList                     const & elements,
                __CollectionType < Iterator >               & storeIn
        ) noexcept -> __CollectionType < Iterator > & {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! __hidden :: __impl :: __initializerListContains ( elements,  * iterator ) ) {
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findAllNotOf (
                InitializerList                     const & elements
        ) noexcept -> __CollectionType < Iterator > {

            __CollectionType < Iterator > iterators;
            return this-> findAllNotOf ( elements, iterators );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType, typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: find (
                Size                                        maxCount,
                __Predicate                         const & predicate,
                __CollectionType < Iterator >             & storeIn
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> __CollectionType < Iterator > & {

            Size matchCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && matchCount < maxCount; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    ++ matchCount;
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType, typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: find (
                Size                                        maxCount,
                __Predicate                         const & predicate
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> __CollectionType < Iterator > {

            __CollectionType < Iterator > iterators;
            return this->find ( maxCount, predicate, iterators );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findFirst (
                __Predicate const & predicate
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> Iterator {

            auto end = this->end();
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    return iterator;
                }
            }

            return end;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findLast (
                __Predicate const & predicate
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> Iterator {

            auto end = this->end();
            auto lastFound = end;
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    lastFound = iterator;
                }
            }

            return lastFound;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType, typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findAll (
                __Predicate                           const & predicate,
                __CollectionType < Iterator >               & storeIn
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> __CollectionType < Iterator > & {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < template < typename ... > class __CollectionType, typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: findAll (
                __Predicate                           const & predicate
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> __CollectionType < Iterator > {

            __CollectionType < Iterator > iterators;
            return this->findAll ( predicate, iterators );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Action > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: forEach (
                __Action const & action
        ) noexcept ( noexcept ( action ( meta :: referenceOf < ElementType > () ) ) ) -> void {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                action ( * iterator );
            }
        }

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: some (
                Size                count,
                __Predicate const & predicate
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

            Size trueCount = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    ++ trueCount;
                }

                if ( trueCount > count ) {
                    return false;
                }
            }

            return trueCount == count;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: atLeast (
                Size                count,
                __Predicate const & predicate
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

            Size trueCount = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    ++ trueCount;
                }

                if ( trueCount >= count ) {
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: atMost (
                Size                count,
                __Predicate const & predicate
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

            Size trueCount = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    ++ trueCount;
                }

                if ( trueCount > count ) {
                    return false;
                }
            }

            return true;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: moreThan (
                Size                count,
                __Predicate const & predicate
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

            return this->atLeast ( count + 1, predicate );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto List < __ElementType > :: fewerThan (
                Size                count,
                __Predicate const & predicate
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

            return this->atMost ( count - 1, predicate );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: count (
                __Predicate const & predicate
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> Size {

            Size trueCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    ++ trueCount;
                }
            }

            return trueCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: any (
                __Predicate const & predicate
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: all (
                __Predicate const & predicate
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! predicate ( * iterator ) ) {
                    return false;
                }
            }

            return true;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
        auto List < __ElementType > :: none (
                __Predicate const & predicate
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    return false;
                }
            }

            return true;
        }

    }
}

#endif // __CDS_LIST_IMPL_HPP__
