/*
 * Created by loghin on 28/11/22.
 */

#ifndef __CDS_WEAK_POINTER_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_WEAK_POINTER_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline WeakPointer <
            __ElementType,
            __Deleter
    > :: WeakPointer (
            WeakPointer const & pointer
    ) noexcept :
            _pControl ( pointer._pControl == nullptr ? nullptr : pointer._pControl->__observe () ) {

    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline WeakPointer <
            __ElementType [],
            __Deleter
    > :: WeakPointer (
            WeakPointer const & pointer
    ) noexcept :
            _pControl ( pointer._pControl == nullptr ? nullptr : pointer._pControl->__observe () ) {

    }


    template < typename __ElementType, typename __Deleter >
    constexpr WeakPointer <
            __ElementType,
            __Deleter
    > :: WeakPointer (
            WeakPointer && pointer
    ) noexcept :
            _pControl ( cds :: exchange ( pointer._pControl, nullptr ) ) {

    }


    template < typename __ElementType, typename __Deleter >
    constexpr WeakPointer <
            __ElementType [],
            __Deleter
    > :: WeakPointer (
            WeakPointer && pointer
    ) noexcept :
            _pControl ( cds :: exchange ( pointer._pControl, nullptr ) ) {

    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline WeakPointer <
            __ElementType,
            __Deleter
    > :: ~WeakPointer () noexcept {

        if ( this->_pControl != nullptr ) {
            this->_pControl->__disposeObserver();
        }
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline WeakPointer <
            __ElementType [],
            __Deleter
    > :: ~WeakPointer () noexcept {

        if ( this->_pControl != nullptr ) {
            this->_pControl->__disposeObserver();
        }
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: operator = (
            std :: nullptr_t /* pointer */
    ) noexcept -> WeakPointer & {

        this->reset();
        return * this;
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType [],
            __Deleter
    > :: operator = (
            std :: nullptr_t /* pointer */
    ) noexcept -> WeakPointer & {

        this->reset ();
        return * this;
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: operator = (
            WeakPointer const & pointer
    ) noexcept -> WeakPointer & {

        this->reset ( pointer );
        return * this;
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType [],
            __Deleter
    > :: operator = (
            WeakPointer const & pointer
    ) noexcept -> WeakPointer & {

        this->reset ( pointer );
        return * this;
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_cpplang_NonConstConstexprMemberFunction auto WeakPointer <
            __ElementType,
            __Deleter
    > :: operator = (
            WeakPointer && pointer
    ) noexcept -> WeakPointer & {

        this->reset ( std :: move ( pointer ) );
        return * this;
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_cpplang_NonConstConstexprMemberFunction auto WeakPointer <
            __ElementType [],
            __Deleter
    > :: operator = (
            WeakPointer && pointer
    ) noexcept -> WeakPointer & {

        this->reset ( std :: move ( pointer ) );
        return * this;
    }


    template < typename __ElementType, typename __Deleter >
    constexpr auto WeakPointer <
            __ElementType,
            __Deleter
    > :: operator == (
            WeakPointer const & pointer
    ) const noexcept -> bool {

        return this->_pControl == pointer._pControl;
    }


    template < typename __ElementType, typename __Deleter >
    constexpr auto WeakPointer <
            __ElementType [],
            __Deleter
    > :: operator == (
            WeakPointer const & pointer
    ) const noexcept -> bool {

        return this->_pControl == pointer._pControl;
    }


    template < typename __ElementType, typename __Deleter >
    constexpr auto WeakPointer <
            __ElementType,
            __Deleter
    > :: operator != (
            WeakPointer const & pointer
    ) const noexcept -> bool {

        return this->_pControl == pointer._pControl;
    }


    template < typename __ElementType, typename __Deleter >
    constexpr auto WeakPointer <
            __ElementType [],
            __Deleter
    > :: operator != (
            WeakPointer const & pointer
    ) const noexcept -> bool {

        return this->_pControl == pointer._pControl;
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: reset () noexcept -> void {

        if ( this->_pControl != nullptr ) {
            cds :: exchange ( this->_pControl, nullptr )->__disposeObserver();
        }
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType [],
            __Deleter
    > :: reset () noexcept -> void {

        if ( this->_pControl != nullptr ) {
            cds :: exchange ( this->_pControl, nullptr )->__disposeObserver();
        }
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: reset (
            WeakPointer const & pointer
    ) noexcept -> void {

        if ( this == & pointer ) {
            return;
        }

        if ( this->_pControl != nullptr ) {
            this->_pControl->__disposeObserver();
        }

        this->_pControl = pointer == nullptr ? nullptr : pointer._pControl->__observe();
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType [],
            __Deleter
    > :: reset (
            WeakPointer const & pointer
    ) noexcept -> void {

        if ( this == & pointer ) {
            return;
        }

        if ( this->_pControl != nullptr ) {
            this->_pControl->__disposeObserver();
        }

        this->_pControl = pointer == nullptr ? nullptr : pointer._pControl->__observe();
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: reset (
            WeakPointer && pointer
    ) noexcept -> void {

        if ( this == & pointer ) {
            return;
        }

        this->_pControl = cds :: exchange ( pointer._pControl, nullptr );
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType [],
            __Deleter
    > :: reset (
            WeakPointer && pointer
    ) noexcept -> void {

        if ( this == & pointer ) {
            return;
        }

        this->_pControl = cds :: exchange ( pointer._pControl, nullptr );
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: expired () const noexcept -> bool {

        if ( this->_pControl == nullptr ) {
            return true;
        }

        return this->_pControl->__expired ();
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType [],
            __Deleter
    > :: expired () const noexcept -> bool {

        if ( this->_pControl == nullptr ) {
            return true;
        }

        return this->_pControl->__expired ();
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: toString () const noexcept -> String {

        auto pValue     = this->_pControl == nullptr ? nullptr : this->_pControl->__get();
        auto expired    = this->_pControl == nullptr ? true : this->_pControl->__expired();

        if ( expired ) {
            return "< Weak Pointer to Expired Memory >";
        } else {
            std :: stringstream oss;
            oss << "< Weak Pointer to Memory at 0x" << std :: hex <<
                    reinterpret_cast < Size > ( pValue ) << std :: dec << " >";
            return oss.str();
        }
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType [],
            __Deleter
    > :: toString () const noexcept -> String {

        auto pValue     = this->_pControl == nullptr ? nullptr : this->_pControl->__get();
        auto expired    = this->_pControl == nullptr ? true : this->_pControl->__expired();

        if ( expired ) {
            return "< Weak Pointer to Expired Memory >";
        } else {
            std :: stringstream oss;
            oss << "< Weak Pointer to Memory at 0x" << std :: hex <<
                    reinterpret_cast < Size > ( pValue ) << std :: dec << " >";
            return oss.str();
        }
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: equals (
            Object const & object
    ) const noexcept -> bool {

        if ( this == & object ) {
            return true;
        }

        auto pWeakPointer = dynamic_cast < decltype (this) > ( & object );
        if ( pWeakPointer == nullptr ) {
            return false;
        }

        return this->_pControl == pWeakPointer->_pControl;
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType [],
            __Deleter
    > :: equals (
            Object const & object
    ) const noexcept -> bool {

        if ( this == & object ) {
            return true;
        }

        auto pWeakPointer = dynamic_cast < decltype (this) > ( & object );
        if ( pWeakPointer == nullptr ) {
            return false;
        }

        return this->_pControl == pWeakPointer->_pControl;
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: hash () const noexcept -> Size {

        return reinterpret_cast < Size > ( this->_pControl );
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto WeakPointer <
            __ElementType [],
            __Deleter
    > :: hash () const noexcept -> Size {

        return reinterpret_cast < Size > ( this->_pControl );
    }

} /* namespace cds */

#endif /* __CDS_WEAK_POINTER_HPP__ */
