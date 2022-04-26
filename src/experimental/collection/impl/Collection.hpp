//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_IMPL_HPP__
#define __CDS_COLLECTION_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: begin () noexcept -> Iterator {
            return Iterator ( this, std :: move ( this->delegateIterator ( DelegateIteratorRequestType :: ForwardBegin ) ) );
        }

        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: end () noexcept -> Iterator {
            return Iterator ( this, std :: move ( this->delegateIterator ( DelegateIteratorRequestType :: ForwardEnd ) ) );
        }

        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: begin () const noexcept -> ConstIterator {
            return this->cbegin();
        }

        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: end () const noexcept -> ConstIterator {
            return this->cend();
        }

        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: cbegin () const noexcept -> ConstIterator {
            return ConstIterator ( this, std :: move ( this->delegateConstIterator ( DelegateIteratorRequestType :: ForwardBegin ) ) );
        }

        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: cend () const noexcept -> ConstIterator {
            return ConstIterator ( this, std :: move ( this->delegateConstIterator ( DelegateIteratorRequestType :: ForwardEnd ) ) );
        }

        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: rbegin () noexcept -> ReverseIterator {
            return ReverseIterator ( this, std :: move ( this->delegateIterator ( DelegateIteratorRequestType :: BackwardBegin ) ) );
        }

        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: rend () noexcept -> ReverseIterator {
            return ReverseIterator ( this, std :: move ( this->delegateIterator ( DelegateIteratorRequestType :: BackwardEnd ) ) );
        }

        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: rbegin () const noexcept -> ConstReverseIterator {
            return this->crbegin();
        }

        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: rend () const noexcept -> ConstReverseIterator {
            return this->crend();
        }

        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: crbegin () const noexcept -> ConstReverseIterator {
            return ConstReverseIterator ( this, std :: move ( this->delegateConstIterator ( DelegateIteratorRequestType :: BackwardBegin ) ) );
        }

        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: crend () const noexcept -> ConstReverseIterator {
            return ConstReverseIterator ( this, std :: move ( this->delegateConstIterator ( DelegateIteratorRequestType :: BackwardEnd ) ) );
        }

        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: equals ( Object const & object ) const noexcept -> bool {
            auto pObject = dynamic_cast < decltype ( this ) > ( & object );
            if ( pObject == nullptr ) {
                return false;
            }

            if ( this->size() != pObject->size() ) {
                return false;
            }

            for (
                    auto
                        leftIt  = this->begin(),    leftEnd     = this->end(),
                        rightIt = pObject->begin();
                    leftIt != leftEnd;
                    ++ leftIt, ++ rightIt
            ) {
                if ( ! Type < T > :: compare ( * leftIt, * rightIt ) ) {
                    return false;
                }
            }

            return true;
        }

        template < typename T >
        __CDS_cpplang_ConstexprPureAbstract auto Collection < T > :: empty () const noexcept -> bool {
            return this->size() == 0ULL;
        }

        template < typename T >
        auto Collection < T > :: hash () const noexcept -> Index {
            Index finalHashValue __CDS_MaybeUnused = 0;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                finalHashValue += cds :: hash ( * iterator );
            }

            return finalHashValue;
        }

        template < typename T >
        constexpr auto Collection < T > :: acquireDelegate ( Iterator const & iterator ) noexcept -> DelegateIterator * {
            return reinterpret_cast < DelegateIterator * > ( iterator._pDelegate.get() );
        }

        template < typename T >
        constexpr auto Collection < T > :: acquireDelegate ( ConstIterator const & iterator ) noexcept -> DelegateConstIterator * {
            return reinterpret_cast < DelegateConstIterator * > ( iterator._pDelegate.get() );
        }

        template < typename T >
        constexpr auto Collection < T > :: acquireDelegate ( ReverseIterator const & iterator ) noexcept -> DelegateIterator * {
            return reinterpret_cast < DelegateIterator * > ( iterator._pDelegate.get() );
        }

        template < typename T >
        constexpr auto Collection < T > :: acquireDelegate ( ConstReverseIterator const & iterator ) noexcept -> DelegateConstIterator * {
            return reinterpret_cast < DelegateConstIterator * > ( iterator._pDelegate.get() );
        }

        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: contains ( ElementType const & element ) const noexcept -> bool {
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( Type < ElementType > :: compare ( * iterator, element ) ) {
                    return true;
                }
            }

            return false;
        }

    }
}

#endif // __CDS_COLLECTION_IMPL_HPP__
