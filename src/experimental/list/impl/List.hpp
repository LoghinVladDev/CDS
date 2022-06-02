//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_LIST_IMPL_HPP__
#define __CDS_LIST_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace impl {

                template < typename T, meta :: EnableIf < meta :: isMoveAssignable < T > () > = 0 >
                __CDS_cpplang_NonConstConstexprMemberFunction auto assign (
                        T & left,
                        T & right
                ) noexcept -> T & {
                    left = std :: move ( right );
                    return * left;
                }

                template < typename T, meta :: EnableIf < ! meta :: isMoveAssignable < T > () > = 0 >
                __CDS_cpplang_NonConstConstexprMemberFunction auto assign (
                        T & left,
                        T & right
                ) noexcept -> T & {
                    left = right;
                    return * left;
                }

                template < typename T, meta :: EnableIf < meta :: isMoveConstructible < T > () && meta :: isMoveAssignable < T > () > = 0 >
                __CDS_cpplang_ConstexprNonLiteralReturn auto swap (
                        T & left,
                        T & right
                ) noexcept -> void {

                    auto aux    = std :: move ( left );
                    left        = std :: move ( right );
                    right       = std :: move ( aux );
                }

                template < typename T, meta :: EnableIf < ! meta :: isMoveConstructible < T > () && ! meta :: isMoveAssignable < T > () > = 0 >
                __CDS_cpplang_ConstexprNonLiteralReturn auto swap (
                        T & left,
                        T & right
                ) noexcept -> void {

                    auto aux    = left;
                    left        = right;
                    right       = aux;
                }

                template < typename IteratorType, typename ComparatorFunction >
                auto quickSortPartition (
                        IteratorType        const & from,
                        IteratorType        const & to,
                        ComparatorFunction  const & function
                ) noexcept -> IteratorType {

                    auto pivot = * to;
                    auto partitionIterator = from;
                    IteratorType previous;

                    for (auto it = from; it != to; ++ it ) {
                        if ( function ( * it, pivot ) ) {
                            swap ( * partitionIterator, * it );
                            previous = partitionIterator;
                            ++ partitionIterator;
                        }
                    }

                    swap ( * partitionIterator, * to );
                    if ( ! previous.valid() ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                        return partitionIterator;
                    }

                    return previous;
                }

                template < typename IteratorType, typename ComparatorFunction >
                auto quickSort (
                        IteratorType        const & from,
                        IteratorType        const & to,
                        ComparatorFunction  const & function
                ) noexcept -> void {

                    if ( to.valid() ) {
                        auto actualEnd = to;
                        if ( from == ++ actualEnd ) {
                            return;
                        }
                    }

                    if ( from != to && from.valid() && to.valid() ) {
                        auto partitionIterator = quickSortPartition (from, to, function );

                        quickSort ( from, partitionIterator, function );
                        if ( ! partitionIterator.valid() ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                            return;
                        }

                        if ( partitionIterator == from ) {
                            if ( ( ++ partitionIterator ).valid() ) {
                                quickSort ( partitionIterator, to, function );
                            }

                            return;
                        }

                        if ( ! ( ++ partitionIterator ).valid() ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                            return;
                        }

                        quickSort ( ++ partitionIterator, to, function );
                    }
                }

            }
        }

        template < typename T >
        constexpr auto List < T > :: acquireDelegate (
                Iterator const & iterator
        ) noexcept -> DelegateIterator const * {

            return reinterpret_cast < DelegateIterator const * > ( Collection < T > :: acquireDelegate ( iterator ) );
        }


        template < typename T >
        constexpr auto List < T > :: acquireDelegate (
                ReverseIterator const & iterator
        ) noexcept -> DelegateIterator const * {

            return reinterpret_cast < DelegateIterator const * > ( Collection < T > :: acquireDelegate ( iterator ) );
        }


        template < typename T >
        __CDS_OptimalInline auto List < T > :: begin () noexcept -> Iterator {

            return Iterator ( this, std :: move ( this->delegateIterator ( DelegateIteratorRequestType :: ForwardBegin ) ) );
        }


        template < typename T >
        __CDS_OptimalInline auto List < T > :: end () noexcept -> Iterator {

            return Iterator ( this, std :: move ( this->delegateIterator ( DelegateIteratorRequestType :: ForwardEnd ) ) );
        }


        template < typename T >
        __CDS_OptimalInline auto List < T > :: rbegin () noexcept -> ReverseIterator {

            return Iterator ( this, std :: move ( this->delegateIterator ( DelegateIteratorRequestType :: BackwardBegin ) ) );
        }


        template < typename T >
        __CDS_OptimalInline auto List < T > :: rend () noexcept -> ReverseIterator {

            return Iterator ( this, std :: move ( this->delegateIterator ( DelegateIteratorRequestType :: BackwardEnd ) ) );
        }


        template < typename T >
        constexpr List < T > :: List (
                List const & list
        ) noexcept :
                _size ( list._size ) {

        }


        template < typename T >
        constexpr List < T > :: List (
                List && list
        ) noexcept :
                _size ( cds :: exchange ( list._size, 0ULL ) ) {

        }


        template < typename T >
        constexpr List < T > :: List (
                Size size
        ) noexcept :
                _size ( size ) {

        }


        template < typename T >
        __CDS_OptimalInline auto List < T > :: equals (
                Object const & object
        ) const noexcept -> bool {

            if ( this == & object ) {
                return true;
            }

            auto pObject = dynamic_cast < decltype ( this ) > ( & object );
            if ( pObject != nullptr ) {
                if ( this->_size != pObject->_size ) {
                    return false;
                }
            }

            return Collection < T > :: equals ( object );
        }


        template < typename T >
        __CDS_OptimalInline auto List < T > :: pNewInsert () noexcept -> ElementType * & {

            return this->pNewBack();
        }


        template < typename T >
        template < typename ListType, typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () && meta :: isDerivedFrom < ListType, Collection < T > > () > >
        auto List < T > :: sub (
                ListType  & storeIn,
                Index       from,
                Index       to
        ) const noexcept -> ListType & {

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


        template < typename T >
        template < typename ListType, typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () && meta :: isDerivedFrom < ListType, Collection < T > > () > >
        __CDS_OptimalInline auto List < T > :: sub (
                Index from,
                Index to
        ) const noexcept -> ListType {

            ListType list;
            return this->sub ( list, from, to );
        }


        template < typename T >
        template < template < typename ... > class ListType, typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () && meta :: isDerivedFrom < ListType < T >, Collection < T > > () > >
        __CDS_OptimalInline auto List < T > :: sub (
                Index from,
                Index to
        ) const noexcept -> ListType < ElementType > {

            return this->sub < ListType < T > > ( from, to );
        }


        template < typename T >
        __CDS_OptimalInline auto List < T > :: operator [] (
                Index index
        ) noexcept (false) -> ElementType & {

            return this->get ( index );
        }


        template < typename T >
        __CDS_OptimalInline auto List < T > :: operator [] (
                Index index
        ) const noexcept (false) -> ElementType const & {

            return this->get ( index );
        }


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: pushBack (
                ElementType const & element
        ) noexcept -> ElementType & {

            auto & pNew = this->pNewBack();
            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( element );
            return * pNew;
        }


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: pushBack (
                ElementType && element
        ) noexcept -> ElementType & {

            auto & pNew = this->pNewBack();
            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( std :: move ( element ) );
            return * pNew;
        }


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: pushFront (
                ElementType const & element
        ) noexcept -> ElementType & {

            auto & pNew = this->pNewFront();
            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( element );
            return * pNew;
        }


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: pushFront (
                ElementType && element
        ) noexcept -> ElementType & {

            auto & pNew = this->pNewFront();
            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( std :: move ( element ) );
            return * pNew;
        }


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: insertBefore (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: insertBefore (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: insertAfter (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: insertAfter (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: insertBefore (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: insertBefore (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: insertAfter (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: insertAfter (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: insertBefore (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: insertBefore (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: insertAfter (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: insertAfter (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: insertBefore (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: insertBefore (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: insertAfter (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: insertAfter (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: append (
                ElementType const & element
        ) noexcept -> ElementType & {

            return this->pushBack ( element );
        }


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: append (
                ElementType && element
        ) noexcept -> ElementType & {

            return this->pushBack ( std :: move ( element ) );
        }


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: prepend (
                ElementType const & element
        ) noexcept -> ElementType & {

            return this->pushFront ( element );
        }


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: prepend (
                ElementType && element
        ) noexcept -> ElementType & {

            return this->pushFront ( std :: move ( element ) );
        }


        template < typename T >
        template < typename ComparatorFunction >
        __CDS_OptimalInline auto List < T > :: sort (
                ComparatorFunction const & comparatorFunction
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

            hidden :: impl :: quickSort ( this->begin(), last, comparatorFunction );
        }


        template < typename T >
        constexpr auto List < T > :: size () const noexcept -> Size {
            return this->_size;
        }


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyAssignable < V > () > >
        auto List < T > :: replace (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyAssignable < V > () > >
        auto List < T > :: replaceAll (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyAssignable < V > () > >
        auto List < T > :: replaceFirst (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveAssignable < V > () > >
        auto List < T > :: replaceFirst (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyAssignable < V > () > >
        auto List < T > :: replaceLast (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveAssignable < V > () > >
        auto List < T > :: replaceLast (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyAssignable < V > () > >
        auto List < T > :: replaceOf (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyAssignable < V > () > >
        auto List < T > :: replaceAllOf (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyAssignable < V > () > >
        auto List < T > :: replaceFirstOf (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveAssignable < V > () > >
        auto List < T > :: replaceFirstOf (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyAssignable < V > () > >
        auto List < T > :: replaceLastOf (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveAssignable < V > () > >
        auto List < T > :: replaceLastOf (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyAssignable < V > () > >
        auto List < T > :: replaceNotOf (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyAssignable < V > () > >
        auto List < T > :: replaceAllNotOf (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyAssignable < V > () > >
        auto List < T > :: replaceFirstNotOf (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveAssignable < V > () > >
        auto List < T > :: replaceFirstNotOf (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyAssignable < V > () > >
        auto List < T > :: replaceLastNotOf (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveAssignable < V > () > >
        auto List < T > :: replaceLastNotOf (
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


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyAssignable < V > () > >
        auto List < T > :: replaceOf (
                Size                                count,
                InitializerList             const & of,
                ElementType                 const & with
        ) noexcept -> Size {

            Size replacedCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( replacedCount < count ) {
                    if ( hidden :: impl :: initializerListContains ( of, * iterator ) ) {
                        * iterator = with;
                        ++ replacedCount;
                    }

                } else {
                    return count;
                }
            }

            return replacedCount;
        }


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyAssignable < V > () > >
        auto List < T > :: replaceAllOf (
                InitializerList             const & of,
                ElementType                 const & with
        ) noexcept -> Size {

            Size replacedCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( hidden :: impl :: initializerListContains ( of, * iterator ) ) {
                    * iterator = with;
                    ++ replacedCount;
                }
            }

            return replacedCount;
        }


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyAssignable < V > () > >
        auto List < T > :: replaceFirstOf (
                InitializerList             const & of,
                ElementType                 const & with
        ) noexcept -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( hidden :: impl :: initializerListContains ( of, * iterator ) ) {
                    * iterator = with;
                    return true;
                }
            }

            return false;
        }


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveAssignable < V > () > >
        auto List < T > :: replaceFirstOf (
                InitializerList             const & of,
                ElementType                      && with
        ) noexcept -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( hidden :: impl :: initializerListContains ( of, * iterator ) ) {
                    * iterator = std :: move ( with );
                    return true;
                }
            }

            return false;
        }


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyAssignable < V > () > >
        auto List < T > :: replaceLastOf (
                InitializerList             const & of,
                ElementType                 const & with
        ) noexcept -> bool {

            for ( auto iterator = this->rbegin(), end = this->rend(); iterator != end; ++ iterator ) {
                if ( hidden :: impl :: initializerListContains ( of, * iterator ) ) {
                    * iterator = with;
                    return true;
                }
            }

            return false;
        }


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveAssignable < V > () > >
        auto List < T > :: replaceLastOf (
                InitializerList             const & of,
                ElementType                      && with
        ) noexcept -> bool {

            for ( auto iterator = this->rbegin(), end = this->rend(); iterator != end; ++ iterator ) {
                if ( hidden :: impl :: initializerListContains ( of, * iterator ) ) {
                    * iterator = std :: move ( with );
                    return true;
                }
            }

            return false;
        }


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyAssignable < V > () > >
        auto List < T > :: replaceNotOf (
                Size                                count,
                InitializerList             const & of,
                ElementType                 const & with
        ) noexcept -> Size {

            Size replacedCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( replacedCount < count ) {
                    if ( ! hidden :: impl :: initializerListContains ( of, * iterator ) ) {
                        * iterator = with;
                        ++ replacedCount;
                    }

                } else {
                    return count;
                }
            }

            return replacedCount;
        }


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyAssignable < V > () > >
        auto List < T > :: replaceAllNotOf (
                InitializerList             const & of,
                ElementType                 const & with
        ) noexcept -> Size {

            Size replacedCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! hidden :: impl :: initializerListContains ( of, * iterator ) ) {
                    * iterator = with;
                    ++ replacedCount;
                }
            }

            return replacedCount;
        }


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyAssignable < V > () > >
        auto List < T > :: replaceFirstNotOf (
                InitializerList             const & of,
                ElementType                 const & with
        ) noexcept -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! hidden :: impl :: initializerListContains ( of, * iterator ) ) {
                    * iterator = with;
                    return true;
                }
            }

            return false;
        }


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveAssignable < V > () > >
        auto List < T > :: replaceFirstNotOf (
                InitializerList             const & of,
                ElementType                      && with
        ) noexcept -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! hidden :: impl :: initializerListContains ( of, * iterator ) ) {
                    * iterator = std :: move ( with );
                    return true;
                }
            }

            return false;
        }


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyAssignable < V > () > >
        auto List < T > :: replaceLastNotOf (
                InitializerList             const & of,
                ElementType                 const & with
        ) noexcept -> bool {

            for ( auto iterator = this->rbegin(), end = this->rend(); iterator != end; ++ iterator ) {
                if ( ! hidden :: impl :: initializerListContains ( of, * iterator ) ) {
                    * iterator = with;
                    return true;
                }
            }

            return false;
        }


        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveAssignable < V > () > >
        auto List < T > :: replaceLastNotOf (
                InitializerList             const & of,
                ElementType                      && with
        ) noexcept -> bool {

            for ( auto iterator = this->rbegin(), end = this->rend(); iterator != end; ++ iterator ) {
                if ( ! hidden :: impl :: initializerListContains ( of, * iterator ) ) {
                    * iterator = std :: move ( with );
                    return true;
                }
            }

            return false;
        }


        template < typename T >
        template < typename Predicate, typename V, meta :: EnableIf < meta :: isCopyAssignable < V > () > >
        auto List < T > :: replace (
                Size                count,
                Predicate   const & predicate,
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


        template < typename T >
        template < typename Predicate, typename V, meta :: EnableIf < meta :: isCopyAssignable < V > () > >
        auto List < T > :: replaceAll (
                Predicate   const & predicate,
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


        template < typename T >
        template < typename Predicate, typename V, meta :: EnableIf < meta :: isCopyAssignable < V > () > >
        auto List < T > :: replaceFirst (
                Predicate   const & predicate,
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


        template < typename T >
        template < typename Predicate, typename V, meta :: EnableIf < meta :: isMoveAssignable < V > () > >
        auto List < T > :: replaceFirst (
                Predicate   const & predicate,
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


        template < typename T >
        template < typename Predicate, typename V, meta :: EnableIf < meta :: isCopyAssignable < V > () > >
        auto List < T > :: replaceLast (
                Predicate   const & predicate,
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


        template < typename T >
        template < typename Predicate, typename V, meta :: EnableIf < meta :: isMoveAssignable < V > () > >
        auto List < T > :: replaceLast (
                Predicate   const & predicate,
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


        template < typename T >
        template < typename Predicate, typename Supplier >
        auto List < T > :: replace (
                Size                count,
                Predicate   const & predicate,
                Supplier    const & supplier
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( meta :: referenceOf < ElementType > () ) ) ) -> Size {

            Size replacedCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( replacedCount < count ) {
                    if ( predicate ( * iterator ) ) {
                        (void) hidden :: impl :: assign ( * iterator, supplier ( std :: move ( * iterator ) ) );
                        ++ replacedCount;
                    }

                } else {
                    return count;
                }
            }

            return replacedCount;
        }


        template < typename T >
        template < typename Predicate, typename Supplier >
        auto List < T > :: replaceAll (
                Predicate   const & predicate,
                Supplier    const & supplier
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( meta :: referenceOf < ElementType > () ) ) ) -> Size {

            Size replacedCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    (void) hidden :: impl :: assign ( * iterator, supplier ( std :: move ( * iterator ) ) );
                    ++ replacedCount;
                }
            }

            return replacedCount;
        }


        template < typename T >
        template < typename Predicate, typename Supplier >
        auto List < T > :: replaceFirst (
                Predicate   const & predicate,
                Supplier    const & supplier
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    (void) hidden :: impl :: assign ( * iterator, supplier ( std :: move ( * iterator ) ) );
                    return true;
                }
            }

            return false;
        }


        template < typename T >
        template < typename Predicate, typename Supplier >
        auto List < T > :: replaceLast (
                Predicate   const & predicate,
                Supplier    const & supplier
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) && noexcept ( supplier ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

            for ( auto iterator = this->rbegin(), end = this->rend(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    (void) hidden :: impl :: assign ( * iterator, supplier ( std :: move ( * iterator ) ) );
                    return true;
                }
            }

            return false;
        }


        template < typename T >
        constexpr auto List < T > :: empty () const noexcept -> bool {
            return this->_size == 0ULL;
        }


        template < typename T >
        auto List < T > :: toString () const noexcept -> String {
            if ( this->empty() ) {
                return {"[ ]"};
            }

            std::stringstream out;
            out << "[ ";

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                Type < T > :: streamPrint ( out, * iterator ) << ", ";
            }

            auto asString = out.str();
            return asString.substr(0u, asString.length() - 2u).append(" ]");
        }


        template < typename T >
        template < typename ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType, Collection < Index > > () > >
        auto List < T > :: indices (
                Size                  count,
                ListType            & storeIn,
                ElementType   const & element
        ) const noexcept -> ListType & {

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


        template < typename T >
        template < typename ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType, Collection < Index > > () > >
        __CDS_OptimalInline auto List < T > :: indices (
                Size                count,
                ElementType const & element
        ) const noexcept -> ListType {

            ListType list;
            return this->indices ( count, list, element );
        }


        template < typename T >
        template < template < typename ... > class ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType < Index >, Collection < Index > > () > >
        __CDS_OptimalInline auto List < T > :: indices (
                Size                count,
                ElementType const & element
        ) const noexcept -> ListType < Index > {

            return this->indices < ListType < T > > ( count, element );
        }


        template < typename T >
        auto List < T > :: firstIndex (
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


        template < typename T >
        auto List < T > :: lastIndex (
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


        template < typename T >
        template < typename ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType, Collection < Index > > () > >
        auto List < T > :: allIndices (
                ListType            & storeIn,
                ElementType   const & element
        ) const noexcept -> ListType & {

            Index index = 0;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator, ++ index ) {
                if ( meta :: equals ( * iterator, element ) ) {
                    storeIn.add ( index );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < typename ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType, Collection < Index > > () > >
        __CDS_OptimalInline auto List < T > :: allIndices (
                ElementType const & element
        ) const noexcept -> ListType {

            ListType list;
            return this->allIndices ( list, element );
        }


        template < typename T >
        template < template < typename ... > class ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType < Index >, Collection < Index > > () > >
        __CDS_OptimalInline auto List < T > :: allIndices (
                ElementType const & element
        ) const noexcept -> ListType < Index > {

            return this->allIndices < ListType < T > > ( element );
        }


        template < typename T >
        template < typename Predicate, typename ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType, Collection < Index > > () > >
        auto List < T > :: indices (
                Size                  count,
                ListType            & storeIn,
                Predicate     const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> ListType & {

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


        template < typename T >
        template < typename Predicate, typename ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType, Collection < Index > > () > >
        __CDS_OptimalInline auto List < T > :: indices (
                Size                count,
                Predicate   const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> ListType {

            ListType list;
            return this->indices ( count, list, predicate );
        }


        template < typename T >
        template < typename Predicate, template < typename ... > class ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType < Index >, Collection < Index > > () > >
        __CDS_OptimalInline auto List < T > :: indices (
                Size                count,
                Predicate   const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> ListType < Index > {

            return this->indices < ListType < T > > ( count, predicate );
        }


        template < typename T >
        template < typename Predicate >
        auto List < T > :: firstIndex (
                Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> Index {

            Index index = 0;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator, ++ index ) {
                if ( predicate ( * iterator ) ) {
                    return index;
                }
            }

            return List :: invalidIndex;
        }


        template < typename T >
        template < typename Predicate >
        auto List < T > :: lastIndex (
                Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> Index {

            Index index = static_cast < Index > ( this->size() ) - 1;
            for ( auto iterator = this->rbegin(), end = this->rend(); iterator != end; ++ iterator, -- index ) {
                if ( predicate ( * iterator ) ) {
                    return index;
                }
            }

            return List :: invalidIndex;
        }


        template < typename T >
        template < typename Predicate, typename ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType, Collection < Index > > () > >
        auto List < T > :: allIndices (
                ListType            & storeIn,
                Predicate     const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> ListType & {

            Index index = 0;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator, ++ index ) {
                if ( predicate ( * iterator ) ) {
                    storeIn.add ( index );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < typename Predicate, typename ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType, Collection < Index > > () > >
        __CDS_OptimalInline auto List < T > :: allIndices (
                Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> ListType {

            ListType list;
            return this->allIndices ( list, predicate );
        }


        template < typename T >
        template < typename Predicate, template < typename ... > class ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType < Index >, Collection < Index > > () > >
        __CDS_OptimalInline auto List < T > :: allIndices (
                Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType const > () ) ) ) -> ListType < Index > {

            return this->allIndices < ListType < Index > > ( predicate );
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto List < T > :: find (
                Size                                        maxCount,
                ElementType                         const & element,
                CollectionType < Iterator >               & storeIn
        ) noexcept -> CollectionType < Iterator > & {

            Size found = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && found < maxCount; ++ iterator ) {
                if ( meta :: equals ( element, * iterator ) ) {
                    ++ found;

                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto List < T > :: find (
                Size                                        maxCount,
                ElementType                         const & element
        ) noexcept -> CollectionType < Iterator > {

            CollectionType < Iterator > iterators;
            return this-> find ( maxCount, element, iterators );
        }


        template < typename T >
        auto List < T > :: findFirst (
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


        template < typename T >
        auto List < T > :: findLast (
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


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto List < T > :: findAll (
                ElementType                         const & element,
                CollectionType < Iterator >               & storeIn
        ) noexcept -> CollectionType < Iterator > & {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( meta :: equals ( element, * iterator ) ) {
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto List < T > :: findAll (
                ElementType                         const & element
        ) noexcept -> CollectionType < Iterator > {

            CollectionType < Iterator > iterators;
            return this-> findAll ( element, iterators );
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto List < T > :: findOf (
                Size                                        maxCount,
                Collection < ElementType >          const & elements,
                CollectionType < Iterator >               & storeIn
        ) noexcept -> CollectionType < Iterator > & {

            Size found = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && found < maxCount; ++ iterator ) {
                if ( elements.contains ( * iterator ) ) {
                    ++ found;

                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto List < T > :: findOf (
                Size                                        maxCount,
                Collection < ElementType >          const & elements
        ) noexcept -> CollectionType < Iterator > {

            CollectionType < Iterator > iterators;
            return this-> findOf ( maxCount, elements, iterators );
        }


        template < typename T >
        auto List < T > :: findFirstOf (
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


        template < typename T >
        auto List < T > :: findLastOf (
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


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto List < T > :: findAllOf (
                Collection < ElementType >          const & elements,
                CollectionType < Iterator >               & storeIn
        ) noexcept -> CollectionType < Iterator > & {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( elements.contains ( * iterator ) ) {
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto List < T > :: findAllOf (
                Collection < ElementType >          const & elements
        ) noexcept -> CollectionType < Iterator > {

            Collection < Iterator > iterators;
            return this->findAllOf ( elements, iterators );
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto List < T > :: findNotOf (
                Size                                        maxCount,
                Collection < ElementType >          const & elements,
                CollectionType < Iterator >               & storeIn
        ) noexcept -> CollectionType < Iterator > & {

            Size found = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && found < maxCount; ++ iterator ) {
                if ( ! elements.contains ( * iterator ) ) {
                    ++ found;

                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto List < T > :: findNotOf (
                Size                                        maxCount,
                Collection < ElementType >          const & elements
        ) noexcept -> CollectionType < Iterator > {

            CollectionType < Iterator > iterators;
            return this-> findNotOf ( maxCount, elements, iterators );
        }


        template < typename T >
        auto List < T > :: findFirstNotOf (
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


        template < typename T >
        auto List < T > :: findLastNotOf (
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


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto List < T > :: findAllNotOf (
                Collection < ElementType >          const & elements,
                CollectionType < Iterator >               & storeIn
        ) noexcept -> CollectionType < Iterator > & {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! elements.contains ( * iterator ) ) {
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto List < T > :: findAllNotOf (
                Collection < ElementType >  const & elements
        ) noexcept -> CollectionType < Iterator > {

            CollectionType < Iterator > iterators;
            return this-> findAllNotOf ( elements, iterators );
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto List < T > :: findOf (
                Size                                        maxCount,
                InitializerList                     const & elements,
                CollectionType < Iterator >               & storeIn
        ) noexcept -> CollectionType < Iterator > & {

            Size found = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && found < maxCount; ++ iterator ) {
                if ( hidden :: impl :: initializerListContains ( elements, * iterator ) ) {
                    ++ found;

                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto List < T > :: findOf (
                Size                                        maxCount,
                InitializerList                     const & elements
        ) noexcept -> CollectionType < Iterator > {

            CollectionType < Iterator > iterators;
            return this-> findOf ( maxCount, elements, iterators );
        }


        template < typename T >
        auto List < T > :: findFirstOf (
                InitializerList const & elements
        ) noexcept -> Iterator {

            auto end = this->end();
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( hidden :: impl :: initializerListContains ( elements, * iterator ) ) {
                    return iterator;
                }
            }

            return end;
        }


        template < typename T >
        auto List < T > :: findLastOf (
                InitializerList const & elements
        ) noexcept -> Iterator {

            auto end = this->end();
            auto lastFound = end;
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( hidden :: impl :: initializerListContains ( elements, * iterator ) ) {
                    lastFound = iterator;
                }
            }

            return lastFound;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto List < T > :: findAllOf (
                InitializerList                     const & elements,
                CollectionType < Iterator >               & storeIn
        ) noexcept -> CollectionType < Iterator > & {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( elements.contains ( * iterator ) ) {
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto List < T > :: findAllOf (
                InitializerList                     const & elements
        ) noexcept -> CollectionType < Iterator > {

            Collection < Iterator > iterators;
            return this->findAllOf ( elements, iterators );
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto List < T > :: findNotOf (
                Size                                        maxCount,
                InitializerList                     const & elements,
                CollectionType < Iterator >               & storeIn
        ) noexcept -> CollectionType < Iterator > & {

            Size found = 0ULL;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && found < maxCount; ++ iterator ) {
                if ( ! hidden :: impl :: initializerListContains ( elements, * iterator ) ) {
                    ++ found;

                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto List < T > :: findNotOf (
                Size                                        maxCount,
                InitializerList                     const & elements
        ) noexcept -> CollectionType < Iterator > {

            CollectionType < Iterator > iterators;
            return this-> findNotOf ( maxCount, elements, iterators );
        }


        template < typename T >
        auto List < T > :: findFirstNotOf (
                InitializerList                     const & elements
        ) noexcept -> Iterator {

            auto end = this->end();
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( ! hidden :: impl :: initializerListContains ( elements,  * iterator ) ) {
                    return iterator;
                }
            }

            return end;
        }


        template < typename T >
        auto List < T > :: findLastNotOf (
                InitializerList                     const & elements
        ) noexcept -> Iterator {

            auto end = this->end();
            auto lastFound = end;
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( ! hidden :: impl :: initializerListContains ( elements,  * iterator ) ) {
                    lastFound = iterator;
                }
            }

            return lastFound;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto List < T > :: findAllNotOf (
                InitializerList                     const & elements,
                CollectionType < Iterator >               & storeIn
        ) noexcept -> CollectionType < Iterator > & {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! hidden :: impl :: initializerListContains ( elements,  * iterator ) ) {
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < template < typename ... > class CollectionType >
        auto List < T > :: findAllNotOf (
                InitializerList                     const & elements
        ) noexcept -> CollectionType < Iterator > {

            CollectionType < Iterator > iterators;
            return this-> findAllNotOf ( elements, iterators );
        }


        template < typename T >
        template < template < typename ... > class CollectionType, typename Predicate >
        auto List < T > :: find (
                Size                                        maxCount,
                Predicate                           const & predicate,
                CollectionType < Iterator >               & storeIn
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> CollectionType < Iterator > & {

            Size matchCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end && matchCount < maxCount; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    ++ matchCount;
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < template < typename ... > class CollectionType, typename Predicate >
        auto List < T > :: find (
                Size                                        maxCount,
                Predicate                           const & predicate
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> CollectionType < Iterator > {

            CollectionType < Iterator > iterators;
            return this->find ( maxCount, predicate, iterators );
        }


        template < typename T >
        template < typename Predicate >
        auto List < T > :: findFirst (
                Predicate const & predicate
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> Iterator {

            auto end = this->end();
            for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    return iterator;
                }
            }

            return end;
        }


        template < typename T >
        template < typename Predicate >
        auto List < T > :: findLast (
                Predicate const & predicate
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


        template < typename T >
        template < template < typename ... > class CollectionType, typename Predicate >
        auto List < T > :: findAll (
                Predicate                           const & predicate,
                CollectionType < Iterator >               & storeIn
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> CollectionType < Iterator > & {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    storeIn.add ( iterator );
                }
            }

            return storeIn;
        }


        template < typename T >
        template < template < typename ... > class CollectionType, typename Predicate >
        auto List < T > :: findAll (
                Predicate                           const & predicate
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> CollectionType < Iterator > {

            CollectionType < Iterator > iterators;
            return this->findAll ( predicate, iterators );
        }


        template < typename T >
        template < typename Action >
        auto List < T > :: forEach (
                Action const & action
        ) noexcept ( noexcept ( action ( meta :: referenceOf < ElementType > () ) ) ) -> void {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                action ( * iterator );
            }
        }

        template < typename T >
        template < typename Predicate >
        auto List < T > :: some (
                Size                count,
                Predicate   const & predicate
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


        template < typename T >
        template < typename Predicate >
        auto List < T > :: atLeast (
                Size                count,
                Predicate   const & predicate
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


        template < typename T >
        template < typename Predicate >
        auto List < T > :: atMost (
                Size                count,
                Predicate   const & predicate
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


        template < typename T >
        template < typename Predicate >
        auto List < T > :: moreThan (
                Size                count,
                Predicate   const & predicate
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

            return this->atLeast ( count + 1, predicate );
        }


        template < typename T >
        template < typename Predicate >
        auto List < T > :: fewerThan (
                Size                count,
                Predicate   const & predicate
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

            return this->atMost ( count - 1, predicate );
        }


        template < typename T >
        template < typename Predicate >
        auto List < T > :: count (
                Predicate const & predicate
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> Size {

            Size trueCount = 0U;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    ++ trueCount;
                }
            }

            return trueCount;
        }


        template < typename T >
        template < typename Predicate >
        auto List < T > :: any (
                Predicate const & predicate
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    return true;
                }
            }

            return false;
        }


        template < typename T >
        template < typename Predicate >
        auto List < T > :: all (
                Predicate const & predicate
        ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! predicate ( * iterator ) ) {
                    return false;
                }
            }

            return true;
        }


        template < typename T >
        template < typename Predicate >
        auto List < T > :: none (
                Predicate const & predicate
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
