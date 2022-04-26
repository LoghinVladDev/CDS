//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_LIST_IMPL_HPP__
#define __CDS_LIST_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

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
        template < typename V, EnableIf < Type < V > :: copyConstructible > >
        __CDS_OptimalInline auto List < T > :: append ( ElementType const & element ) noexcept -> ElementType & {
            return this->pushBack ( element );
        }

        template < typename T >
        template < typename V, EnableIf < Type < V > :: moveConstructible > >
        __CDS_OptimalInline auto List < T > :: append ( ElementType && element ) noexcept -> ElementType & {
            return this->pushBack ( cds :: forward < ElementType > ( element ) );
        }

        template < typename T >
        template < typename V, EnableIf < Type < V > :: copyConstructible > >
        __CDS_OptimalInline auto List < T > :: prepend ( ElementType const & element ) noexcept -> ElementType & {
            return this->pushFront ( element );
        }

        template < typename T >
        template < typename V, EnableIf < Type < V > :: moveConstructible > >
        __CDS_OptimalInline auto List < T > :: prepend ( ElementType && element ) noexcept -> ElementType & {
            return this->pushFront ( cds :: forward < ElementType > ( element ) );
        }

        template < typename T >
        template < typename V, EnableIf < Type < V > :: copyConstructible > >
        __CDS_OptimalInline auto List < T > :: pushBack ( ElementType const & element ) noexcept -> ElementType & {
            auto & pNew = this->pNewBack();

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( element );
            return * pNew;
        }

        template < typename T >
        template < typename V, EnableIf < Type < V > :: moveConstructible > >
        __CDS_OptimalInline auto List < T > :: pushBack ( ElementType && element ) noexcept -> ElementType & {
            auto & pNew = this->pNewBack();

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( cds :: forward < ElementType > ( element ) );
            return * pNew;
        }

        template < typename T >
        template < typename V, EnableIf < Type < V > :: copyConstructible > >
        __CDS_OptimalInline auto List < T > :: pushFront ( ElementType const & element ) noexcept -> ElementType & {
            auto & pNew = this->pNewFront();

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( element );
            return * pNew;
        }

        template < typename T >
        template < typename V, EnableIf < Type < V > :: moveConstructible > >
        __CDS_OptimalInline auto List < T > :: pushFront ( ElementType && element ) noexcept -> ElementType & {
            auto & pNew = this->pNewFront();

            if ( pNew != nullptr ) {
                return * pNew;
            }

            pNew = Memory :: instance().create < ElementType > ( cds :: forward < ElementType > ( element ) );
            return * pNew;
        }

        template < typename T >
        template < typename V, EnableIf < Type < V > :: copyConstructible > >
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
        template < typename V, EnableIf < Type < V > :: moveConstructible > >
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
        template < typename V, EnableIf < Type < V > :: copyConstructible > >
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
        template < typename V, EnableIf < Type < V > :: moveConstructible > >
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
        template < typename V, EnableIf < Type < V > :: copyConstructible > >
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
        template < typename V, EnableIf < Type < V > :: moveConstructible > >
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
        template < typename V, EnableIf < Type < V > :: copyConstructible > >
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
        template < typename V, EnableIf < Type < V > :: moveConstructible > >
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
        template < typename V, EnableIf < Type < V > :: copyConstructible > >
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
        template < typename V, EnableIf < Type < V > :: moveConstructible > >
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
        template < typename V, EnableIf < Type < V > :: copyConstructible > >
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
        template < typename V, EnableIf < Type < V > :: moveConstructible > >
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
        template < typename V, EnableIf < Type < V > :: copyConstructible > >
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
        template < typename V, EnableIf < Type < V > :: moveConstructible > >
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
        template < typename V, EnableIf < Type < V > :: copyConstructible > >
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
        template < typename V, EnableIf < Type < V > :: moveConstructible > >
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

    }
}

#endif // __CDS_LIST_IMPL_HPP__
