/* NOLINT(llvm-header-guard)
 * Created by loghin on 28/11/22.
 */

#ifndef __CDS_WEAK_POINTER_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_WEAK_POINTER_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline WeakPointer <
            __ElementType,
            __Deleter
    > :: WeakPointer (
            WeakPointer const & pointer
    ) noexcept :
            _pControl ( pointer._pControl == nullptr ? nullptr : pointer._pControl->__observe () ) {

    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline WeakPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: WeakPointer (
            WeakPointer const & pointer
    ) noexcept :
            _pControl ( pointer._pControl == nullptr ? nullptr : pointer._pControl->__observe () ) {

    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr WeakPointer <
            __ElementType,
            __Deleter
    > :: WeakPointer (
            WeakPointer && pointer
    ) noexcept :
            _pControl ( cds :: exchange ( pointer._pControl, nullptr ) ) {

    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr WeakPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: WeakPointer (
            WeakPointer && pointer
    ) noexcept :
            _pControl ( cds :: exchange ( pointer._pControl, nullptr ) ) {

    }


    template < typename __ElementType, typename __Deleter >             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    template < typename __OtherElementType, typename __OtherDeleter >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline WeakPointer <
            __ElementType,
            __Deleter
    > :: WeakPointer (
            WeakPointer < __OtherElementType, __OtherDeleter > const & pointer
    ) noexcept :
            _pControl ( pointer._pControl == nullptr ? nullptr : pointer._pControl->__observe()->template __cast < __ElementType > () ) {

    }


    template < typename __ElementType, typename __Deleter >             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    template < typename __OtherElementType, typename __OtherDeleter >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr WeakPointer <
            __ElementType,
            __Deleter
    > :: WeakPointer (
            WeakPointer < __OtherElementType, __OtherDeleter > && pointer
    ) noexcept :
            _pControl ( cds :: exchange ( pointer._pControl, nullptr )->template __cast < __ElementType > () ) {

    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline WeakPointer <
            __ElementType,
            __Deleter
    > :: ~WeakPointer () noexcept {

        if ( this->_pControl != nullptr ) {
            this->_pControl->__disposeObserver();
        }
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline WeakPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: ~WeakPointer () noexcept {

        if ( this->_pControl != nullptr ) {
            this->_pControl->__disposeObserver();
        }
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: operator = (
            std :: nullptr_t /* pointer */
    ) noexcept -> WeakPointer & {

        this->reset();
        return * this;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto WeakPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator = (
            std :: nullptr_t /* pointer */
    ) noexcept -> WeakPointer & {

        this->reset ();
        return * this;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: operator = (                                       /* NOLINT(*-unhandled-self-assignment, cert-oop54-cpp) */
            WeakPointer const & pointer
    ) noexcept -> WeakPointer & {

        this->reset ( pointer );
        return * this;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto WeakPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator = (                                       /* NOLINT(*-unhandled-self-assignment, cert-oop54-cpp) */
            WeakPointer const & pointer
    ) noexcept -> WeakPointer & {

        this->reset ( pointer );
        return * this;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto WeakPointer <
            __ElementType,
            __Deleter
    > :: operator = (
            WeakPointer && pointer
    ) noexcept -> WeakPointer & {

        this->reset ( std :: move ( pointer ) );
        return * this;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto WeakPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator = (
            WeakPointer && pointer
    ) noexcept -> WeakPointer & {

        this->reset ( std :: move ( pointer ) );
        return * this;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    template < typename __OtherElementType, typename __OtherDeleter >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: operator = (                                       /* NOLINT(*-unhandled-self-assignment, cert-oop54-cpp) */
            WeakPointer < __OtherElementType, __OtherDeleter > const & pointer
    ) noexcept -> WeakPointer & {

        this->reset ( pointer );
        return * this;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    template < typename __OtherElementType, typename __OtherDeleter >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto WeakPointer <
            __ElementType,
            __Deleter
    > :: operator = (
            WeakPointer < __OtherElementType, __OtherDeleter > && pointer
    ) noexcept -> WeakPointer & {

        this->reset ( std :: move ( pointer ) );
        return * this;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto WeakPointer <
            __ElementType,
            __Deleter
    > :: operator == (
            WeakPointer const & pointer
    ) const noexcept -> bool {

        return this->_pControl == pointer._pControl;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto WeakPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator == (
            WeakPointer const & pointer
    ) const noexcept -> bool {

        return this->_pControl == pointer._pControl;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto WeakPointer <
            __ElementType,
            __Deleter
    > :: operator != (
            WeakPointer const & pointer
    ) const noexcept -> bool {

        return this->_pControl == pointer._pControl;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto WeakPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator != (
            WeakPointer const & pointer
    ) const noexcept -> bool {

        return this->_pControl == pointer._pControl;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: reset () noexcept -> void {

        if ( this->_pControl != nullptr ) {
            cds :: exchange ( this->_pControl, nullptr )->__disposeObserver();
        }
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto WeakPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: reset () noexcept -> void {

        if ( this->_pControl != nullptr ) {
            cds :: exchange ( this->_pControl, nullptr )->__disposeObserver();
        }
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto WeakPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
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


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto WeakPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: reset (
            WeakPointer && pointer
    ) noexcept -> void {

        if ( this == & pointer ) {
            return;
        }

        this->_pControl = cds :: exchange ( pointer._pControl, nullptr );
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    template < typename __OtherElementType, typename __OtherDeleter >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: reset (
            WeakPointer < __OtherElementType, __OtherDeleter > const & pointer
    ) noexcept -> void {

        if ( this == & pointer ) {
            return;
        }

        if ( this->_pControl != nullptr ) {
            this->_pControl->__disposeObserver();
        }

        this->_pControl = pointer == nullptr ? nullptr : pointer._pControl->__observe()->template __cast < __ElementType > ();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    template < typename __OtherElementType, typename __OtherDeleter >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: reset (
            WeakPointer < __OtherElementType, __OtherDeleter > && pointer
    ) noexcept -> void {

        if ( this == & pointer ) {
            return;
        }

        this->_pControl = cds :: exchange ( pointer._pControl, nullptr )->template __cast < __ElementType > ();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: expired () const noexcept -> bool {

        if ( this->_pControl == nullptr ) {
            return true;
        }

        return this->_pControl->__expired ();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto WeakPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: expired () const noexcept -> bool {

        if ( this->_pControl == nullptr ) {
            return true;
        }

        return this->_pControl->__expired ();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: toString () const noexcept -> String {

        auto pValue     = this->_pControl == nullptr ? nullptr : this->_pControl->__get();
        auto expired    = this->_pControl == nullptr || this->_pControl->__expired();

        if ( expired ) {
            return "< Weak Pointer to Expired Memory >";
        }

        std :: stringstream oss;
        oss << "< Weak Pointer to Memory at 0x" << std :: hex <<
                reinterpret_cast < Size > ( pValue ) << std :: dec << " >"; /* NOLINT(clion-misra-cpp2008-5-2-8, *-reinterpret-cast, clion-misra-cpp2008-5-2-5, clion-misra-cpp2008-5-2-9) */
        return oss.str();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto WeakPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: toString () const noexcept -> String {

        auto pValue     = this->_pControl == nullptr ? nullptr : this->_pControl->__get();
        auto expired    = this->_pControl == nullptr || this->_pControl->__expired();

        if ( expired ) {
            return "< Weak Pointer to Expired Memory >";
        }

        std :: stringstream oss;
        oss << "< Weak Pointer to Memory at 0x" << std :: hex <<
                reinterpret_cast < Size > ( pValue ) << std :: dec << " >"; /* NOLINT(clion-misra-cpp2008-5-2-8, *-reinterpret-cast, clion-misra-cpp2008-5-2-5, clion-misra-cpp2008-5-2-9) */
        return oss.str();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: equals (
            Object const & object
    ) const noexcept -> bool {

        if ( this == & object ) {
            return true;
        }

        auto const * pWeakPointer = dynamic_cast < decltype (this) > ( & object );  /* NOLINT(clion-misra-cpp2008-5-2-8, *-reinterpret-cast, clion-misra-cpp2008-5-2-5, clion-misra-cpp2008-5-2-9) */
        if ( pWeakPointer == nullptr ) {
            return false;
        }

        return this->_pControl == pWeakPointer->_pControl;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto WeakPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: equals (
            Object const & object
    ) const noexcept -> bool {

        if ( this == & object ) {
            return true;
        }

        auto const * pWeakPointer = dynamic_cast < decltype (this) > ( & object );  /* NOLINT(clion-misra-cpp2008-5-2-8, *-reinterpret-cast, clion-misra-cpp2008-5-2-5, clion-misra-cpp2008-5-2-9) */
        if ( pWeakPointer == nullptr ) {
            return false;
        }

        return this->_pControl == pWeakPointer->_pControl;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: hash () const noexcept -> Size {

        return reinterpret_cast < Size > ( this->_pControl );   /* NOLINT(clion-misra-cpp2008-5-2-8, *-reinterpret-cast, clion-misra-cpp2008-5-2-5, clion-misra-cpp2008-5-2-9) */
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto WeakPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: hash () const noexcept -> Size {

        return reinterpret_cast < Size > ( this->_pControl );   /* NOLINT(clion-misra-cpp2008-5-2-8, *-reinterpret-cast, clion-misra-cpp2008-5-2-5, clion-misra-cpp2008-5-2-9) */
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: ownerCount () const noexcept -> Size {

        return this->_pControl == nullptr ? 0ULL : this->_pControl->__ownerCount();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto WeakPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: ownerCount () const noexcept -> Size {

        return this->_pControl == nullptr ? 0ULL : this->_pControl->__ownerCount();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto WeakPointer <
            __ElementType,
            __Deleter
    > :: observerCount () const noexcept -> Size {

        return this->_pControl == nullptr ? 0ULL : this->_pControl->__observerCount();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto WeakPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: observerCount () const noexcept -> Size {

        return this->_pControl == nullptr ? 0ULL : this->_pControl->__observerCount();
    }

} /* namespace cds */

#endif /* __CDS_WEAK_POINTER_IMPL_HPP__ */
