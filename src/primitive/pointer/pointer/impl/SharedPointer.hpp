/* NOLINT(llvm-header-guard)
 * Created by loghin on 28/11/22.
 */

#ifndef __CDS_SHARED_POINTER_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_POINTER_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline SharedPointer <
            __ElementType,
            __Deleter
    > :: SharedPointer () noexcept = default;


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: SharedPointer () noexcept = default;


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline SharedPointer <
            __ElementType,
            __Deleter
    > :: SharedPointer (
            __ElementType * pointer
    ) noexcept :
            _pControl ( ControlBlock :: __new (pointer) ) {

    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: SharedPointer (
            __ElementType * pointer
    ) noexcept :
            _pControl ( ControlBlock :: __new (pointer) ) {

    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline SharedPointer <
            __ElementType,
            __Deleter
    > :: SharedPointer (                                    /* NOLINT(clion-misra-cpp2008-12-1-3) */
            std :: nullptr_t /* pointer */
    ) noexcept :
            _pControl ( nullptr ) {

    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: SharedPointer (                                    /* NOLINT(clion-misra-cpp2008-12-1-3) */
            std :: nullptr_t /* pointer */
    ) noexcept :
            _pControl ( nullptr ) {

    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline SharedPointer <
            __ElementType,
            __Deleter
    > :: SharedPointer (
            SharedPointer const & pointer
    ) noexcept :
            _pControl ( pointer._pControl == nullptr ? nullptr : pointer._pControl->__use() ) {

    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: SharedPointer (
            SharedPointer const & pointer
    ) noexcept :
            _pControl ( pointer._pControl == nullptr ? nullptr : pointer._pControl->__use() ) {

    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr SharedPointer <
            __ElementType,
            __Deleter
    > :: SharedPointer (
            SharedPointer && pointer
    ) noexcept :
            _pControl ( cds :: exchange ( pointer._pControl, nullptr ) ) {

    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: SharedPointer (
            SharedPointer && pointer
    ) noexcept :
            _pControl ( cds :: exchange ( pointer._pControl, nullptr ) ) {

    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    template < typename __OtherElementType, typename __OtherDeleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline SharedPointer <
            __ElementType,
            __Deleter
    > :: SharedPointer (
            SharedPointer < __OtherElementType, __OtherDeleter > const & pointer
    ) noexcept :
            _pControl ( pointer._pControl == nullptr ? nullptr : pointer._pControl->__use()->template __cast < __ElementType > () ) {

    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    template < typename __OtherElementType, typename __OtherDeleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline SharedPointer <
            __ElementType,                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: SharedPointer (
            SharedPointer < __OtherElementType, __OtherDeleter > && pointer
    ) noexcept :
            _pControl ( cds :: exchange ( pointer._pControl, nullptr )->template __cast < __ElementType > () ) {

    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline SharedPointer <
            __ElementType,
            __Deleter
    > :: ~SharedPointer () noexcept {

        if ( this->_pControl != nullptr ) {
            __Deleter () ( this->_pControl->__release() );
        }
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: ~SharedPointer () noexcept {

        if ( this->_pControl != nullptr ) {
            __Deleter () ( this->_pControl->__release() );
        }
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType,
            __Deleter
    > :: operator = (
            __ElementType * pointer
    ) noexcept -> SharedPointer & {

        this->reset ( pointer );
        return * this;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator = (
            __ElementType * pointer
    ) noexcept -> SharedPointer & {

        this->reset ( pointer );
        return * this;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType,
            __Deleter
    > :: operator = (
            std :: nullptr_t pointer
    ) noexcept -> SharedPointer & {

        this->reset ( pointer );
        return * this;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator = (
            std :: nullptr_t pointer
    ) noexcept -> SharedPointer & {

        this->reset ( pointer );
        return * this;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType,
            __Deleter
    > :: operator = (
            SharedPointer const & pointer
    ) noexcept -> SharedPointer & {

        if ( this == & pointer || this->_pControl == pointer._pControl ) {
            return * this;
        }

        if ( this->_pControl != nullptr ) {
            __Deleter () ( this->_pControl->__release() );
        }

        this->_pControl = pointer._pControl == nullptr ? nullptr : pointer._pControl->__use();
        return * this;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator = (
            SharedPointer const & pointer
    ) noexcept -> SharedPointer & {

        if ( this == & pointer || this->_pControl == pointer._pControl ) {
            return * this;
        }

        if ( this->_pControl != nullptr ) {
            __Deleter () ( this->_pControl->__release() );
        }

        this->_pControl = pointer._pControl == nullptr ? nullptr : pointer._pControl->__use();
        return * this;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType,
            __Deleter
    > :: operator = (
            SharedPointer && pointer
    ) noexcept -> SharedPointer & {

        if ( this == & pointer || this->_pControl == pointer._pControl ) {
            return * this;
        }

        if ( this->_pControl != nullptr ) {
            __Deleter () ( this->_pControl->__release() );
        }

        this->_pControl = cds :: exchange ( pointer._pControl, nullptr );
        return * this;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator = (
            SharedPointer && pointer
    ) noexcept -> SharedPointer & {

        if ( this == & pointer || this->_pControl == pointer._pControl ) {
            return * this;
        }

        if ( this->_pControl != nullptr ) {
            __Deleter () ( this->_pControl->__release() );
        }

        this->_pControl = cds :: exchange ( pointer._pControl, nullptr );
        return * this;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    template < typename __OtherElementType, typename __OtherDeleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType,
            __Deleter
    > :: operator = (
            SharedPointer < __OtherElementType, __OtherDeleter > const & pointer
    ) noexcept -> SharedPointer & {

        if ( this->_pControl != nullptr ) {
            __Deleter () ( this->_pControl->__release() );
        }

        this->_pControl = pointer._pControl == nullptr ? nullptr : pointer._pControl->__use()->template __cast < __ElementType > ();
        return * this;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    template < typename __OtherElementType, typename __OtherDeleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType,
            __Deleter
    > :: operator = (
            SharedPointer < __OtherElementType, __OtherDeleter > && pointer
    ) noexcept -> SharedPointer & {

        if ( this->_pControl != nullptr ) {
            __Deleter () ( this->_pControl->__release() );
        }

        this->_pControl = cds :: exchange ( pointer._pControl, nullptr )->template __cast < __ElementType > ();
        return * this;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto SharedPointer <
            __ElementType,
            __Deleter
    > :: operator == (
            __ElementType const * pointer
    ) const noexcept -> bool {

        return
                this->_pControl == nullptr && pointer == nullptr ||
                this->_pControl->__get() == pointer;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator == (
            __ElementType const * pointer
    ) const noexcept -> bool {

        return
                this->_pControl == nullptr && pointer == nullptr ||
                this->_pControl->__get() == pointer;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto SharedPointer <
            __ElementType,
            __Deleter
    > :: operator != (
            __ElementType const * pointer
    ) const noexcept -> bool {

        return
                this->_pControl == nullptr && pointer != nullptr ||
                this->_pControl->__get() != pointer;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator != (
            __ElementType const * pointer
    ) const noexcept -> bool {

        return
                this->_pControl == nullptr && pointer != nullptr ||
                this->_pControl->__get() != pointer;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_VirtualConstexpr auto SharedPointer <
            __ElementType,
            __Deleter
    > :: operator == (
            Base const & pointer
    ) const noexcept -> bool {

        return
                this->_pControl == nullptr && pointer.isNull() ||
                this->_pControl->__get() == pointer.get();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_VirtualConstexpr auto SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator == (
            Base const & pointer
    ) const noexcept -> bool {

        return
                this->_pControl == nullptr && pointer.isNull() ||
                this->_pControl->__get() == pointer.get();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_VirtualConstexpr auto SharedPointer <
            __ElementType,
            __Deleter
    > :: operator != (
            Base const & pointer
    ) const noexcept -> bool {

        return
                this->_pControl == nullptr && ! pointer.isNull() ||     /* NOLINT(clion-misra-cpp2008-5-3-1) */
                this->_pControl->__get() != pointer.get();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_VirtualConstexpr auto SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator != (
            Base const & pointer
    ) const noexcept -> bool {

        return
                this->_pControl == nullptr && ! pointer.isNull() ||     /* NOLINT(clion-misra-cpp2008-5-3-1) */
                this->_pControl->__get() != pointer.get();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto SharedPointer <
            __ElementType,
            __Deleter
    > :: operator == (
            SharedPointer const & pointer
    ) const noexcept -> bool {

        return
                this->_pControl == pointer._pControl ||
                this->_pControl != nullptr &&
                this->_pControl->__get() == pointer._pControl->__get();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator == (
            SharedPointer const & pointer
    ) const noexcept -> bool {

        return
                this->_pControl == pointer._pControl ||
                this->_pControl != nullptr &&
                this->_pControl->__get() == pointer._pControl->__get();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto SharedPointer <
            __ElementType,
            __Deleter
    > :: operator != (
            SharedPointer const & pointer
    ) const noexcept -> bool {

        return
                this->_pControl != pointer._pControl ||
                this->_pControl != nullptr &&
                this->_pControl->__get() != pointer._pControl->__get();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator != (
            SharedPointer const & pointer
    ) const noexcept -> bool {

        return
                this->_pControl != pointer._pControl ||
                this->_pControl != nullptr &&
                this->_pControl->__get() != pointer._pControl->__get();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto SharedPointer <
            __ElementType,
            __Deleter
    > :: operator == (
            std :: nullptr_t pointer
    ) const noexcept -> bool {

        return this->_pControl == nullptr || this->_pControl->__get() == pointer;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator == (
            std :: nullptr_t pointer
    ) const noexcept -> bool {

        return this->_pControl == nullptr || this->_pControl->__get() == pointer;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto SharedPointer <
            __ElementType,
            __Deleter
    > :: operator != (
            std :: nullptr_t pointer
    ) const noexcept -> bool {

        return this->_pControl != nullptr || this->_pControl->__get() != pointer;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator != (
            std :: nullptr_t pointer
    ) const noexcept -> bool {

        return this->_pControl != nullptr || this->_pControl->__get() != pointer;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprOverride auto SharedPointer <
            __ElementType,
            __Deleter
    > :: valueAt () const noexcept (false) -> __ElementType & {

        if ( this->_pControl == nullptr || this->_pControl->__get() == nullptr ) {
            throw NullPointerException ();
        }

        return * this->_pControl->__get();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprOverride auto SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: valueAt () const noexcept (false) -> __ElementType & {

        if ( this->_pControl == nullptr || this->_pControl->__get() == nullptr ) {
            throw NullPointerException ();
        }

        return * this->_pControl->__get();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprOverride auto SharedPointer <
            __ElementType,
            __Deleter
    > :: get () const noexcept -> __ElementType * {

        if ( this->_pControl == nullptr ) {
            return nullptr;
        }

        return this->_pControl->__get();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprOverride auto SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: get () const noexcept -> __ElementType * {

        if ( this->_pControl == nullptr ) {
            return nullptr;
        }

        return this->_pControl->__get();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType,
            __Deleter
    > :: exchange (
            __ElementType * pointer
    ) noexcept -> __ElementType * {

        if ( this->_pControl == nullptr ) {
            this->_pControl = ControlBlock :: __new ( pointer );
            return nullptr;
        }

        if ( this->_pControl->__get() == pointer ) {
            return pointer;
        }

        return cds :: exchange ( this->_pControl, ControlBlock :: __new ( pointer ) )->__release ();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: exchange (
            __ElementType * pointer
    ) noexcept -> __ElementType * {

        if ( this->_pControl == nullptr ) {
            this->_pControl = ControlBlock :: __new ( pointer );
            return nullptr;
        }

        if ( this->_pControl->__get() == pointer ) {
            return pointer;
        }

        return cds :: exchange ( this->_pControl, ControlBlock :: __new ( pointer ) )->__release ();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType,
            __Deleter
    > :: exchange (
            std :: nullptr_t /* pointer */
    ) noexcept -> __ElementType * {

        if ( this->_pControl == nullptr ) {
            return nullptr;
        }

        return cds :: exchange ( this->_pControl, nullptr )->__release ();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: exchange (
            std :: nullptr_t /* pointer */
    ) noexcept -> __ElementType * {

        if ( this->_pControl == nullptr ) {
            return nullptr;
        }

        return cds :: exchange ( this->_pControl, nullptr )->__release ();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType,
            __Deleter
    > :: release () noexcept -> __ElementType * {

        if ( this->_pControl == nullptr ) {
            return nullptr;
        }

        return cds :: exchange ( this->_pControl, nullptr )->__release ();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: release () noexcept -> __ElementType * {

        if ( this->_pControl == nullptr ) {
            return nullptr;
        }

        return cds :: exchange ( this->_pControl, nullptr )->__release ();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType,
            __Deleter
    > :: reset () noexcept -> void {

        if ( this->_pControl == nullptr ) {
            return;
        }

        __Deleter () ( cds :: exchange ( this->_pControl, nullptr )->__release () );
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: reset () noexcept -> void {

        if ( this->_pControl == nullptr ) {
            return;
        }

        __Deleter () ( cds :: exchange ( this->_pControl, nullptr )->__release () );
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType,
            __Deleter
    > :: reset (
            __ElementType * pointer
    ) noexcept -> void {

        if ( this->_pControl != nullptr ) {
            __Deleter () ( cds :: exchange ( this->_pControl, ControlBlock :: __new ( pointer ) )->__release () );
        } else {
            this->_pControl = ControlBlock :: __new ( pointer );
        }
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: reset (
            __ElementType * pointer
    ) noexcept -> void {

        if ( this->_pControl != nullptr ) {
            __Deleter () ( cds :: exchange ( this->_pControl, ControlBlock :: __new ( pointer ) )->__release () );
        } else {
            this->_pControl = ControlBlock :: __new ( pointer );
        }
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType,
            __Deleter
    > :: reset (
            std :: nullptr_t /* pointer */
    ) noexcept -> void {

        if ( this->_pControl == nullptr ) {
            return;
        }

        __Deleter () ( cds :: exchange ( this->_pControl, nullptr )->__release () );
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: reset (
            std :: nullptr_t /* pointer */
    ) noexcept -> void {

        if ( this->_pControl == nullptr ) {
            return;
        }

        __Deleter () ( cds :: exchange ( this->_pControl, nullptr )->__release () );
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType,
            __Deleter
    > :: ownerCount () const noexcept -> Size {

        return this->_pControl == nullptr ? 0ULL : this->_pControl->__ownerCount();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: ownerCount () const noexcept -> Size {

        return this->_pControl == nullptr ? 0ULL : this->_pControl->__ownerCount();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType,
            __Deleter
    > :: observerCount () const noexcept -> Size {

        return this->_pControl == nullptr ? 0ULL : this->_pControl->__observerCount();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto SharedPointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: observerCount () const noexcept -> Size {

        return this->_pControl == nullptr ? 0ULL : this->_pControl->__observerCount();
    }


    template < typename __ElementType, typename ... __ConstructionArguments >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    inline auto makeShared (
            __ConstructionArguments && ... arguments
    ) noexcept (
            noexcept ( __ElementType ( std :: forward < __ConstructionArguments > ( arguments ) ... ) )
    ) -> cds :: meta :: EnableIf <
            ! cds :: meta :: isArray < __ElementType > (),                      /* NOLINT(clion-misra-cpp2008-5-3-1) */
            SharedPointer < __ElementType, __hidden :: __impl :: __DefaultSmartPointerDeleter < __ElementType > >
    > {

        return SharedPointer < __ElementType > (
                new __ElementType ( std :: forward < __ConstructionArguments > ( arguments ) ... ) /* NOLINT(clion-misra-cpp2008-18-4-1) */
        );
    }


    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            cds :: meta :: EnableIf <
                    cds :: meta :: isUnboundedArray < __ElementType > ()
            >
    > inline auto makeShared (
            Size size
    ) noexcept -> SharedPointer < __ElementType, __hidden :: __impl :: __DefaultSmartPointerDeleter < __ElementType > > {

        return SharedPointer < __ElementType > (
                new cds :: meta :: RemoveExtent < __ElementType > [size]    /* NOLINT(clion-misra-cpp2008-18-4-1) */
        );
    }


    template <
            typename __ElementType,                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            cds :: meta :: EnableIf <
                    ! cds :: meta :: isArray < __ElementType > ()   /* NOLINT(clion-misra-cpp2008-5-3-1) */
            >
    > inline auto makeSharedDefault () noexcept ( noexcept ( __ElementType () ) ) -> SharedPointer < __ElementType, __hidden :: __impl :: __DefaultSmartPointerDeleter < __ElementType > > {

        return SharedPointer < __ElementType > (
                new __ElementType ()    /* NOLINT(clion-misra-cpp2008-18-4-1) */
        );
    }


    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            cds :: meta :: EnableIf <
                    cds :: meta :: isUnboundedArray < __ElementType > ()
            >
    > __CDS_NoDiscard auto makeSharedDefault (
            Size size
    ) noexcept -> SharedPointer < __ElementType, __hidden :: __impl :: __DefaultSmartPointerDeleter < __ElementType > > {

        return SharedPointer < __ElementType > (
                new cds :: meta :: RemoveExtent < __ElementType > [size] () /* NOLINT(clion-misra-cpp2008-18-4-1) */
        );
    }

} /* namespace cds */

#endif /* __CDS_SHARED_POINTER_IMPL_HPP__ */
