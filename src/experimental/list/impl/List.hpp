//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_LIST_IMPL_HPP__
#define __CDS_LIST_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

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
        constexpr auto List < T > :: acquireDelegate ( Iterator const & iterator ) noexcept -> DelegateIterator const * {
            return reinterpret_cast < DelegateIterator const * > ( Collection < T > :: acquireDelegate ( iterator ) );
        }

        template < typename T >
        constexpr auto List < T > :: acquireDelegate ( ReverseIterator const & iterator ) noexcept -> DelegateIterator const * {
            return reinterpret_cast < DelegateIterator const * > ( Collection < T > :: acquireDelegate ( iterator ) );
        }

        template < typename T >
        constexpr auto List < T > :: size () const noexcept -> Size {
            return this->_size;
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

                for ( auto const & element __CDS_MaybeUnused : (*this) ) {
                Type < T > :: streamPrint(out, element ) << ", ";
            }

            auto asString = out.str();
            return asString.substr(0u, asString.length() - 2u).append(" ]");
        }

        template < typename T >
        __CDS_OptimalInline auto List < T > :: equals ( Object const & object ) const noexcept -> bool {
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
        constexpr List < T > :: List ( List const & list ) noexcept :
                _size ( list._size ) {

        }

        template < typename T >
        constexpr List < T > :: List ( List && list ) noexcept :
                _size ( cds :: exchange ( list._size, 0ULL ) ) {

        }

        template < typename T >
        constexpr List < T > :: List ( Size size ) noexcept :
                _size ( size ) {

        }

        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: append ( ElementType const & element ) noexcept -> ElementType & {
            return this->pushBack ( element );
        }

        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: append ( ElementType && element ) noexcept -> ElementType & {
            return this->pushBack ( cds :: forward < ElementType > ( element ) );
        }

        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: prepend ( ElementType const & element ) noexcept -> ElementType & {
            return this->pushFront ( element );
        }

        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: prepend ( ElementType && element ) noexcept -> ElementType & {
            return this->pushFront ( cds :: forward < ElementType > ( element ) );
        }

        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: pushBack ( ElementType const & element ) noexcept -> ElementType & {
            auto & pNew = this->pNewBack();

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( element );
            return * pNew;
        }

        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: pushBack ( ElementType && element ) noexcept -> ElementType & {
            auto & pNew = this->pNewBack();

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( cds :: forward < ElementType > ( element ) );
            return * pNew;
        }

        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: pushFront ( ElementType const & element ) noexcept -> ElementType & {
            auto & pNew = this->pNewFront();

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( element );
            return * pNew;
        }

        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isMoveConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: pushFront ( ElementType && element ) noexcept -> ElementType & {
            auto & pNew = this->pNewFront();

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( cds :: forward < ElementType > ( element ) );
            return * pNew;
        }

        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: insertBefore ( Iterator const & iterator, ElementType const & element ) noexcept (false) -> ElementType & {
            if ( ! iterator.of ( this ) ) {
                throw IllegalArgumentException ( "Iterator not of this Collection" );
            }

            if ( iterator == this->begin() ) {
                return this->pNewFront();
            }

            if ( iterator == this->end() ) {
                return this->pNewBack();
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
        __CDS_OptimalInline auto List < T > :: insertBefore ( Iterator const & iterator, ElementType && element ) noexcept (false) -> ElementType & {
            if ( ! iterator.of ( this ) ) {
                throw IllegalArgumentException ( "Iterator not of this Collection" );
            }

            if ( iterator == this->begin() ) {
                return this->pNewFront();
            }

            if ( iterator == this->end() ) {
                return this->pNewBack();
            }

            if ( ! iterator.valid () ) {
                throw OutOfBoundsException ( "Iterator out of bounds" );
            }

            auto & pNew = this->pNewBefore ( iterator );

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( cds :: forward < ElementType > ( element ) );
            return * pNew;
        }

        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: insertAfter ( Iterator const & iterator, ElementType const & element ) noexcept (false) -> ElementType & {
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
        __CDS_OptimalInline auto List < T > :: insertAfter ( Iterator const & iterator, ElementType && element ) noexcept (false) -> ElementType & {
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

            pNew = Memory :: instance().create < ElementType > ( cds :: forward < ElementType > ( element ) );
            return * pNew;
        }

        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: insertBefore ( ConstIterator const & iterator, ElementType const & element ) noexcept (false) -> ElementType & {
            if ( ! iterator.of ( this ) ) {
                throw IllegalArgumentException ( "Iterator not of this Collection" );
            }

            if ( iterator == this->begin() ) {
                return this->pNewFront();
            }

            if ( iterator == this->end() ) {
                return this->pNewBack();
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
        __CDS_OptimalInline auto List < T > :: insertBefore ( ConstIterator const & iterator, ElementType && element ) noexcept (false) -> ElementType & {
            if ( ! iterator.of ( this ) ) {
                throw IllegalArgumentException ( "Iterator not of this Collection" );
            }

            if ( iterator == this->begin() ) {
                return this->pNewFront();
            }

            if ( iterator == this->end() ) {
                return this->pNewBack();
            }

            if ( ! iterator.valid () ) {
                throw OutOfBoundsException ( "Iterator out of bounds" );
            }

            auto & pNew = this->pNewBefore ( iterator );

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( cds :: forward < ElementType > ( element ) );
            return * pNew;
        }

        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: insertAfter ( ConstIterator const & iterator, ElementType const & element ) noexcept (false) -> ElementType & {
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
        __CDS_OptimalInline auto List < T > :: insertAfter ( ConstIterator const & iterator, ElementType && element ) noexcept (false) -> ElementType & {
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

            pNew = Memory :: instance().create < ElementType > ( cds :: forward < ElementType > ( element ) );
            return * pNew;
        }

        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: insertBefore ( ReverseIterator const & iterator, ElementType const & element ) noexcept (false) -> ElementType & {
            if ( ! iterator.of ( this ) ) {
                throw IllegalArgumentException ( "Iterator not of this Collection" );
            }

            if ( iterator == this->begin() ) {
                return this->pNewFront();
            }

            if ( iterator == this->end() ) {
                return this->pNewBack();
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
        __CDS_OptimalInline auto List < T > :: insertBefore ( ReverseIterator const & iterator, ElementType && element ) noexcept (false) -> ElementType & {
            if ( ! iterator.of ( this ) ) {
                throw IllegalArgumentException ( "Iterator not of this Collection" );
            }

            if ( iterator == this->begin() ) {
                return this->pNewFront();
            }

            if ( iterator == this->end() ) {
                return this->pNewBack();
            }

            if ( ! iterator.valid () ) {
                throw OutOfBoundsException ( "Iterator out of bounds" );
            }

            auto & pNew = this->pNewBefore ( iterator );

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( cds :: forward < ElementType > ( element ) );
            return * pNew;
        }

        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: insertAfter ( ReverseIterator const & iterator, ElementType const & element ) noexcept (false) -> ElementType & {
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
        __CDS_OptimalInline auto List < T > :: insertAfter ( ReverseIterator const & iterator, ElementType && element ) noexcept (false) -> ElementType & {
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

            pNew = Memory :: instance().create < ElementType > ( cds :: forward < ElementType > ( element ) );
            return * pNew;
        }

        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: insertBefore ( ConstReverseIterator const & iterator, ElementType const & element ) noexcept (false) -> ElementType & {
            if ( ! iterator.of ( this ) ) {
                throw IllegalArgumentException ( "Iterator not of this Collection" );
            }

            if ( iterator == this->begin() ) {
                return this->pNewFront();
            }

            if ( iterator == this->end() ) {
                return this->pNewBack();
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
        __CDS_OptimalInline auto List < T > :: insertBefore ( ConstReverseIterator const & iterator, ElementType && element ) noexcept (false) -> ElementType & {
            if ( ! iterator.of ( this ) ) {
                throw IllegalArgumentException ( "Iterator not of this Collection" );
            }

            if ( iterator == this->begin() ) {
                return this->pNewFront();
            }

            if ( iterator == this->end() ) {
                return this->pNewBack();
            }

            if ( ! iterator.valid () ) {
                throw OutOfBoundsException ( "Iterator out of bounds" );
            }

            auto & pNew = this->pNewBefore ( iterator );

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( cds :: forward < ElementType > ( element ) );
            return * pNew;
        }

        template < typename T >
        template < typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () > >
        __CDS_OptimalInline auto List < T > :: insertAfter ( ConstReverseIterator const & iterator, ElementType const & element ) noexcept (false) -> ElementType & {
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
        __CDS_OptimalInline auto List < T > :: insertAfter ( ConstReverseIterator const & iterator, ElementType && element ) noexcept (false) -> ElementType & {
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

            pNew = Memory :: instance().create < ElementType > ( cds :: forward < ElementType > ( element ) );
            return * pNew;
        }

        template < typename T >
        __CDS_OptimalInline auto List < T > :: pNewInsert () noexcept -> ElementType * & {
            return this->pNewBack();
        }

        template < typename T >
        template < typename ListType, typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () && meta :: isDerivedFrom < ListType, Collection < T > > () > >
        auto List < T > :: sub ( Index from, Index to, ListType & list ) const noexcept (false) -> ListType & {

            list.clear();

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
                    list.add ( * iterator );
                }

                ++ index;
            }

            return list;
        }

        template < typename T >
        template < typename ListType, typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () && meta :: isDerivedFrom < ListType, Collection < T > > () > >
        auto List < T > :: sub ( Index from, Index to ) const noexcept (false) -> ListType {
            ListType list;

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
                    list.add ( * iterator );
                }

                ++ index;
            }

            return list;
        }

        template < typename T >
        template < template < typename ... > class ListType, typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () && meta :: isDerivedFrom < ListType < T >, Collection < T > > () > >
        __CDS_OptimalInline auto List < T > :: sub ( Index from, Index to, ListType < ElementType > & list ) const noexcept (false) -> ListType < ElementType > & {
            return this->sub < ListType < T > > ( from, to, list );
        }

        template < typename T >
        template < template < typename ... > class ListType, typename V, meta :: EnableIf < meta :: isCopyConstructible < V > () && meta :: isDerivedFrom < ListType < T >, Collection < T > > () > >
        __CDS_OptimalInline auto List < T > :: sub ( Index from, Index to ) const noexcept (false) -> ListType < ElementType > {
            return this->sub < ListType < T > > ( from, to );
        }

        template < typename T >
        template < typename ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType, Collection < Index > > () > >
        auto List < T > :: indices ( ElementType const & element, ListType & list ) const noexcept -> ListType & {
            list.clear ();

            Index index = 0;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator, ++ index ) {
                if ( Type < ElementType > :: compare ( * iterator, element ) ) {
                    list.add ( index );
                }
            }

            return list;
        }

        template < typename T >
        template < typename ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType, Collection < Index > > () > >
        auto List < T > :: indices ( ElementType const & element ) const noexcept -> ListType {
            ListType list;

            Index index = 0;
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator, ++ index ) {
                if ( Type < ElementType > :: compare ( * iterator, element ) ) {
                    list.add ( index );
                }
            }

            return list;
        }

        template < typename T >
        template < template < typename ... > class ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType < Index >, Collection < Index > > () > >
        __CDS_OptimalInline auto List < T > :: indices ( ElementType const & element, ListType < Index > & list ) const noexcept -> ListType < Index > & {
            return this->indices < ListType < T > > ( element, list );
        }

        template < typename T >
        template < template < typename ... > class ListType, meta :: EnableIf < meta :: isDerivedFrom < ListType < Index >, Collection < Index > > () > >
        __CDS_OptimalInline auto List < T > :: indices ( ElementType const & element ) const noexcept -> ListType < Index > {
            return this->indices < ListType < T > > ( element );
        }

        template < typename T >
        __CDS_OptimalInline auto List < T > :: operator [] ( Index index ) noexcept (false) -> ElementType & {
            return this->get ( index );
        }

        template < typename T >
        __CDS_OptimalInline auto List < T > :: operator [] ( Index index ) const noexcept (false) -> ElementType const & {
            return this->get ( index );
        }

        template < typename T >
        template < typename ComparatorFunction >
        __CDS_OptimalInline auto List < T > :: sort ( ComparatorFunction const & comparatorFunction ) noexcept -> void {
            if ( this->size() < 2 ) {
                return;
            }

            Iterator last = -- this->end();
            if ( last == this->end() ) {
                for ( auto it = this->begin(), end = this->end(); it != end; ++ it ) { // NOLINT(clion-misra-cpp2008-8-0-1)
                    last = it;
                }
            }

            List < T > :: quickSort ( this->begin(), last, comparatorFunction );
        }

        template < typename T >
        template < typename ComparatorFunction >
        auto List < T > :: quickSort ( Iterator const & from, Iterator const & to, ComparatorFunction const & function ) noexcept -> void {
            if ( to.valid() ) {
                auto actualEnd = to;
                if ( from == ++ actualEnd ) {
                    return;
                }
            }

            if (from != to && from.valid() && to.valid() ) {
                auto partitionIterator = List < T > :: quickSortPartition (from, to, function );

                List < T > :: quickSort ( from, partitionIterator, function );
                if ( ! partitionIterator.valid() ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                    return;
                }

                if ( partitionIterator == from ) {
                    if ( ( ++ partitionIterator ).valid() ) {
                        List < T > :: quickSort ( partitionIterator, to, function );
                    }

                    return;
                }

                if ( ! ( ++ partitionIterator ).valid() ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                    return;
                }

                List < T > :: quickSort (++ partitionIterator, to, function );
            }
        }

        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace impl {
                template < typename T, EnableIf < Type < T > :: moveConstructible && Type < T > :: moveAssignable > = 0 >
                __CDS_cpplang_ConstexprNonLiteralReturn auto swap ( T && left, T && right ) noexcept -> void {
                    auto aux    = cds :: forward < T > ( left );
                    left        = cds :: forward < T > ( right );
                    right       = cds :: forward < T > ( aux );
                }

                template < typename T >
                __CDS_cpplang_ConstexprNonLiteralReturn auto swap ( T & left, T & right ) noexcept -> void {
                    auto aux    = left;
                    left        = right;
                    right       = aux;
                }
            }
        }

        template < typename T >
        template < typename ComparatorFunction >
        auto List < T > :: quickSortPartition ( Iterator const & from, Iterator const & to, ComparatorFunction const & function ) noexcept -> Iterator {

            auto pivot = * to;
            auto partitionIterator = from;
            Iterator previous;

            for (auto it = from; it != to; ++ it ) {
                if ( function ( * it, pivot ) ) {
                    hidden :: impl :: swap ( * partitionIterator, * it );
                    previous = partitionIterator;
                    ++ partitionIterator;
                }
            }

            hidden :: impl :: swap ( * partitionIterator, * to );
            if ( ! previous.valid() ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                return partitionIterator;
            }

            return previous;
        }

        template < typename T >
        template < typename Action >
        auto List < T > :: forEach ( Action const & action ) noexcept ( noexcept ( meta :: valueOf < Action > () ( meta :: referenceOf < ElementType > () ) ) ) -> void {
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                action ( * iterator );
            }
        }

        template < typename T >
        template < typename Predicate >
        auto List < T > :: some (
                Size                count,
                Predicate   const & predicate
        ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

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
        ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

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
        ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

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
        ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> bool {
            return this->atLeast ( count + 1, predicate );
        }

        template < typename T >
        template < typename Predicate >
        auto List < T > :: lessThan (
                Size                count,
                Predicate   const & predicate
        ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> bool {
            return this->atMost ( count - 1, predicate );
        }

        template < typename T >
        template < typename Predicate >
        auto List < T > :: count (
                Predicate const & predicate
        ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> Size {
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
        ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> bool {
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
        ) noexcept ( noexcept ( meta :: valueOf < Predicate > () ( meta :: referenceOf < ElementType > () ) ) ) -> bool {
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! predicate ( * iterator ) ) {
                    return false;
                }
            }

            return true;
        }

    }
}

#endif // __CDS_LIST_IMPL_HPP__
