/* NOLINT(llvm-header-guard)
 * Created by loghin on 29/11/22.
 */

#if !defined(__CDS_POINTER_WEAK_SHARED_POINTER_IMPL_HPP__) && defined(__CDS_WEAK_POINTER_HPP__) && defined(__CDS_SHARED_POINTER_HPP__)
#define __CDS_POINTER_WEAK_SHARED_POINTER_IMPL_HPP__

namespace cds {

    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline SharedPointer <
            __ElementType,
            __Deleter
    > :: SharedPointer (
            WeakPointer < __ElementType, __Deleter > const & pointer
    ) noexcept {

        * this = std :: move ( pointer.acquire () );
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline SharedPointer <
            __ElementType [],
            __Deleter
    > :: SharedPointer (
            WeakPointer < __ElementType [], __Deleter > const & pointer
    ) noexcept {

        * this = std :: move ( pointer.acquire () );
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline SharedPointer <
            __ElementType,
            __Deleter
    > :: SharedPointer (
            WeakPointer < __ElementType, __Deleter > && pointer
    ) noexcept {

        * this = std :: move ( pointer.acquire () );

        if ( pointer._pControl != nullptr ) {
            pointer._pControl->__disposeObserver ();
        }
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline SharedPointer <
            __ElementType [],
            __Deleter
    > :: SharedPointer (
            WeakPointer < __ElementType [], __Deleter > && pointer
    ) noexcept {

        * this = std :: move ( pointer.acquire () );

        if ( pointer._pControl != nullptr ) {
            pointer._pControl->__disposeObserver ();
        }
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto SharedPointer <
            __ElementType,
            __Deleter
    > :: operator = (
            WeakPointer < __ElementType, __Deleter > const & pointer
    ) noexcept -> SharedPointer & {

        return this->operator = ( std :: move ( pointer.acquire() ) );
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto SharedPointer <
            __ElementType [],
            __Deleter
    > :: operator = (
            WeakPointer < __ElementType [], __Deleter > const & pointer
    ) noexcept -> SharedPointer & {

        return this->operator = ( std :: move ( pointer.acquire() ) );
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto SharedPointer <
            __ElementType,
            __Deleter
    > :: operator = (
            WeakPointer < __ElementType, __Deleter > && pointer
    ) noexcept -> SharedPointer & {

        this->operator = ( std :: move ( pointer.acquire() ) );

        if ( pointer._pControl != nullptr ) {
            pointer._pControl->__disposeObserver ();
        }

        return * this;
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto SharedPointer <
            __ElementType [],
            __Deleter
    > :: operator = (
            WeakPointer < __ElementType [], __Deleter > && pointer
    ) noexcept -> SharedPointer & {

        return this->operator = ( std :: move ( pointer.acquire() ) );

        if ( pointer._pControl != nullptr ) {
            pointer._pControl->__disposeObserver ();
        }

        return * this;
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline WeakPointer <
            __ElementType,
            __Deleter
    > :: WeakPointer (
            SharedPointer < __ElementType, __Deleter > const & pointer
    ) noexcept :
            _pControl ( pointer._pControl == nullptr ? nullptr : pointer._pControl->__observe() ) {

    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline WeakPointer <
            __ElementType [],
            __Deleter
    > :: WeakPointer (
            SharedPointer < __ElementType [], __Deleter > const & pointer
    ) noexcept :
            _pControl ( pointer._pControl == nullptr ? nullptr : pointer._pControl->__observe() ) {

    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline WeakPointer <
            __ElementType,
            __Deleter
    > :: WeakPointer (
            SharedPointer < __ElementType, __Deleter > && pointer
    ) noexcept {

        if ( pointer._pControl != nullptr ) {
            this->_pControl = cds :: exchange ( pointer._pControl, nullptr )->__observe();
            __Deleter () ( this->_pControl->__release() );
        }
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline WeakPointer <
            __ElementType [],
            __Deleter
    > :: WeakPointer (
            SharedPointer < __ElementType [], __Deleter > && pointer
    ) noexcept {

        if ( pointer._pControl != nullptr ) {
            this->_pControl = cds :: exchange ( pointer._pControl, nullptr )->__observe();
            __Deleter () ( this->_pControl->__release() );
        }
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: operator = (
            SharedPointer < __ElementType, __Deleter > const & pointer
    ) noexcept -> WeakPointer & {

        this->reset (pointer);
        return * this;
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType [],
            __Deleter
    > :: operator = (
            SharedPointer < __ElementType [], __Deleter > const & pointer
    ) noexcept -> WeakPointer & {

        this->reset (pointer);
        return * this;
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: operator = (
            SharedPointer < __ElementType, __Deleter > && pointer
    ) noexcept -> WeakPointer & {

        this->reset ( std :: move ( pointer ) );
        return * this;
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType [],
            __Deleter
    > :: operator = (
            SharedPointer < __ElementType [], __Deleter > && pointer
    ) noexcept -> WeakPointer & {

        this->reset ( std :: move ( pointer ) );
        return * this;
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: reset (
            SharedPointer < __ElementType, __Deleter > const & pointer
    ) noexcept -> void {

        if ( this->_pControl == pointer._pControl ) {
            return;
        }

        if ( this->_pControl != nullptr ) {
            this->_pControl->__disposeObserver();
        }

        this->_pControl = pointer._pControl->__observe();
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType [],
            __Deleter
    > :: reset (
            SharedPointer < __ElementType [], __Deleter > const & pointer
    ) noexcept -> void {

        if ( this->_pControl == pointer._pControl ) {
            return;
        }

        if ( this->_pControl != nullptr ) {
            this->_pControl->__disposeObserver();
        }

        this->_pControl = pointer._pControl->__observe();
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: reset (
            SharedPointer < __ElementType, __Deleter > && pointer
    ) noexcept -> void {

        if ( this->_pControl != nullptr ) {
            cds :: exchange ( this->_pControl, nullptr )->__disposeObserver();
        }

        if ( pointer._pControl != nullptr ) {
            this->_pControl = cds :: exchange ( pointer._pControl, nullptr )->__observe();
            __Deleter () ( this->_pControl->__release() );
        }
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType [],
            __Deleter
    > :: reset (
            SharedPointer < __ElementType [], __Deleter > && pointer
    ) noexcept -> void {

        if ( this->_pControl != nullptr ) {
            cds :: exchange ( this->_pControl, nullptr )->__disposeObserver();
        }

        if ( pointer._pControl != nullptr ) {
            this->_pControl = cds :: exchange ( pointer._pControl, nullptr )->__observe();
            __Deleter () ( this->_pControl->__release() );
        }
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: acquire () const noexcept -> SharedPointer < __ElementType, __Deleter > {

        SharedPointer < __ElementType, __Deleter > emptyShared;
        emptyShared._pControl = this->_pControl->__checkAndUse();
        return emptyShared;
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType [],
            __Deleter
    > :: acquire () const noexcept -> SharedPointer < __ElementType [], __Deleter > {

        SharedPointer < __ElementType, __Deleter > emptyShared;
        emptyShared._pControl = this->_pControl->__checkAndUse();
        return emptyShared;
    }

} /* namespace cds */

#endif /* __CDS_POINTER_WEAK_SHARED_POINTER_IMPL_HPP__ */
