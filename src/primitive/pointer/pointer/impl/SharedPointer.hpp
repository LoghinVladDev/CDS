/*
 * Created by loghin on 28/11/22.
 */

#ifndef __CDS_SHARED_POINTER_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_POINTER_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline SharedPointer <
            __ElementType,
            __Deleter
    > :: SharedPointer () noexcept = default;


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline SharedPointer <
            __ElementType [],
            __Deleter
    > :: SharedPointer () noexcept = default;


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline SharedPointer <
            __ElementType,
            __Deleter
    > :: SharedPointer (
            __ElementType * pointer
    ) noexcept :
            _pControl ( ControlBlock :: __new (pointer) ) {

    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline SharedPointer <
            __ElementType [],
            __Deleter
    > :: SharedPointer (
            __ElementType * pointer
    ) noexcept :
            _pControl ( ControlBlock :: __new (pointer) ) {

    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline SharedPointer <
            __ElementType,
            __Deleter
    > :: SharedPointer (
            std :: nullptr_t /* pointer */
    ) noexcept :
            _pControl ( nullptr ) {

    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline SharedPointer <
            __ElementType [],
            __Deleter
    > :: SharedPointer (
            std :: nullptr_t /* pointer */
    ) noexcept :
            _pControl ( nullptr ) {

    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline SharedPointer <
            __ElementType,
            __Deleter
    > :: SharedPointer (
            SharedPointer const & pointer
    ) noexcept :
            _pControl ( pointer._pControl == nullptr ? nullptr : pointer._pControl->__use() ) {

    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline SharedPointer <
            __ElementType [],
            __Deleter
    > :: SharedPointer (
            SharedPointer const & pointer
    ) noexcept :
            _pControl ( pointer._pControl == nullptr ? nullptr : pointer._pControl->__use() ) {

    }


    template < typename __ElementType, typename __Deleter >
    constexpr SharedPointer <
            __ElementType,
            __Deleter
    > :: SharedPointer (
            SharedPointer && pointer
    ) noexcept :
            _pControl ( cds :: exchange ( pointer._pControl, nullptr ) ) {

    }


    template < typename __ElementType, typename __Deleter >
    constexpr SharedPointer <
            __ElementType [],
            __Deleter
    > :: SharedPointer (
            SharedPointer && pointer
    ) noexcept :
            _pControl ( cds :: exchange ( pointer._pControl, nullptr ) ) {

    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline SharedPointer <
            __ElementType,
            __Deleter
    > :: ~SharedPointer () noexcept {

        if ( this->_pControl != nullptr ) {
            __Deleter () ( this->_pControl->__release() );
        }
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline SharedPointer <
            __ElementType [],
            __Deleter
    > :: ~SharedPointer () noexcept {

        if ( this->_pControl != nullptr ) {
            __Deleter () ( this->_pControl->__release() );
        }
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto SharedPointer <
            __ElementType,
            __Deleter
    > :: operator = (
            __ElementType * pointer
    ) noexcept -> SharedPointer & {

        this->reset ( pointer );
        return * this;
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto SharedPointer <
            __ElementType [],
            __Deleter
    > :: operator = (
            __ElementType * pointer
    ) noexcept -> SharedPointer & {

        this->reset ( pointer );
        return * this;
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto SharedPointer <
            __ElementType,
            __Deleter
    > :: operator = (
            std :: nullptr_t pointer
    ) noexcept -> SharedPointer & {

        this->reset ( pointer );
        return * this;
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto SharedPointer <
            __ElementType [],
            __Deleter
    > :: operator = (
            std :: nullptr_t pointer
    ) noexcept -> SharedPointer & {

        this->reset ( pointer );
        return * this;
    }


    template < typename __ElementType, typename __Deleter >
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

        this->_pControl = pointer._pControl.__use ();
        return * this;
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto SharedPointer <
            __ElementType [],
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

        this->_pControl = pointer._pControl.__use ();
        return * this;
    }


    template < typename __ElementType, typename __Deleter >
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


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto SharedPointer <
            __ElementType [],
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


    template < typename __ElementType, typename __Deleter >
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


    template < typename __ElementType, typename __Deleter >
    constexpr auto SharedPointer <
            __ElementType [],
            __Deleter
    > :: operator == (
            __ElementType const * pointer
    ) const noexcept -> bool {

        return
                this->_pControl == nullptr && pointer == nullptr ||
                this->_pControl->__get() == pointer;
    }


    template < typename __ElementType, typename __Deleter >
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


    template < typename __ElementType, typename __Deleter >
    constexpr auto SharedPointer <
            __ElementType [],
            __Deleter
    > :: operator != (
            __ElementType const * pointer
    ) const noexcept -> bool {

        return
                this->_pControl == nullptr && pointer != nullptr ||
                this->_pControl->__get() != pointer;
    }


    template < typename __ElementType, typename __Deleter >
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


    template < typename __ElementType, typename __Deleter >
    __CDS_cpplang_VirtualConstexpr auto SharedPointer <
            __ElementType [],
            __Deleter
    > :: operator == (
            Base const & pointer
    ) const noexcept -> bool {

        return
                this->_pControl == nullptr && pointer.isNull() ||
                this->_pControl->__get() == pointer.get();
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_cpplang_VirtualConstexpr auto SharedPointer <
            __ElementType,
            __Deleter
    > :: operator != (
            Base const & pointer
    ) const noexcept -> bool {

        return
                this->_pControl == nullptr && ! pointer.isNull() ||
                this->_pControl->__get() != pointer.get();
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_cpplang_VirtualConstexpr auto SharedPointer <
            __ElementType [],
            __Deleter
    > :: operator != (
            Base const & pointer
    ) const noexcept -> bool {

        return
                this->_pControl == nullptr && ! pointer.isNull() ||
                this->_pControl->__get() != pointer.get();
    }


    template < typename __ElementType, typename __Deleter >
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


    template < typename __ElementType, typename __Deleter >
    constexpr auto SharedPointer <
            __ElementType [],
            __Deleter
    > :: operator == (
            SharedPointer const & pointer
    ) const noexcept -> bool {

        return
                this->_pControl == pointer._pControl ||
                this->_pControl != nullptr &&
                this->_pControl->__get() == pointer._pControl->__get();
    }


    template < typename __ElementType, typename __Deleter >
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


    template < typename __ElementType, typename __Deleter >
    constexpr auto SharedPointer <
            __ElementType [],
            __Deleter
    > :: operator != (
            SharedPointer const & pointer
    ) const noexcept -> bool {

        return
                this->_pControl != pointer._pControl ||
                this->_pControl != nullptr &&
                this->_pControl->__get() != pointer._pControl->__get();
    }


    template < typename __ElementType, typename __Deleter >
    constexpr auto SharedPointer <
            __ElementType,
            __Deleter
    > :: operator == (
            std :: nullptr_t pointer
    ) const noexcept -> bool {

        return this->_pControl == nullptr || this->_pControl->__get() == pointer;
    }


    template < typename __ElementType, typename __Deleter >
    constexpr auto SharedPointer <
            __ElementType [],
            __Deleter
    > :: operator == (
            std :: nullptr_t pointer
    ) const noexcept -> bool {

        return this->_pControl == nullptr || this->_pControl->__get() == pointer;
    }


    template < typename __ElementType, typename __Deleter >
    constexpr auto SharedPointer <
            __ElementType,
            __Deleter
    > :: operator != (
            std :: nullptr_t pointer
    ) const noexcept -> bool {

        return this->_pControl != nullptr || this->_pControl->__get() != pointer;
    }


    template < typename __ElementType, typename __Deleter >
    constexpr auto SharedPointer <
            __ElementType [],
            __Deleter
    > :: operator != (
            std :: nullptr_t pointer
    ) const noexcept -> bool {

        return this->_pControl != nullptr || this->_pControl->__get() != pointer;
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_cpplang_ConstexprOverride auto SharedPointer <
            __ElementType,
            __Deleter
    > :: valueAt () const noexcept (false) -> __ElementType & {

        if ( this->_pControl == nullptr || this->_pControl->__get() == nullptr ) {
            throw NullPointerException ();
        }

        return * this->_pControl->__get();
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_cpplang_ConstexprOverride auto SharedPointer <
            __ElementType [],
            __Deleter
    > :: valueAt () const noexcept (false) -> __ElementType & {

        if ( this->_pControl == nullptr || this->_pControl->__get() == nullptr ) {
            throw NullPointerException ();
        }

        return * this->_pControl->__get();
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_cpplang_ConstexprOverride auto SharedPointer <
            __ElementType,
            __Deleter
    > :: get () const noexcept -> __ElementType * {

        if ( this->_pControl == nullptr ) {
            return nullptr;
        }

        return this->_pControl->__get();
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_cpplang_ConstexprOverride auto SharedPointer <
            __ElementType [],
            __Deleter
    > :: get () const noexcept -> __ElementType * {

        if ( this->_pControl == nullptr ) {
            return nullptr;
        }

        return this->_pControl->__get();
    }


    template < typename __ElementType, typename __Deleter >
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


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto SharedPointer <
            __ElementType [],
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


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto SharedPointer <
            __ElementType,
            __Deleter
    > :: exchange (
            std :: nullptr_t pointer
    ) noexcept -> __ElementType * {

        if ( this->_pControl == nullptr ) {
            return nullptr;
        }

        return cds :: exchange ( this->_pControl, nullptr )->__release ();
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto SharedPointer <
            __ElementType [],
            __Deleter
    > :: exchange (
            std :: nullptr_t pointer
    ) noexcept -> __ElementType * {

        if ( this->_pControl == nullptr ) {
            return nullptr;
        }

        return cds :: exchange ( this->_pControl, nullptr )->__release ();
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto SharedPointer <
            __ElementType,
            __Deleter
    > :: release () noexcept -> __ElementType * {

        if ( this->_pControl == nullptr ) {
            return nullptr;
        }

        return this->_pControl->__release ();
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto SharedPointer <
            __ElementType [],
            __Deleter
    > :: release () noexcept -> __ElementType * {

        if ( this->_pControl == nullptr ) {
            return nullptr;
        }

        return this->_pControl->__release ();
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto SharedPointer <
            __ElementType,
            __Deleter
    > :: reset () noexcept -> void {

        if ( this->_pControl == nullptr ) {
            return;
        }

        __Deleter () ( cds :: exchange ( this->_pControl, nullptr )->__release () );
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto SharedPointer <
            __ElementType [],
            __Deleter
    > :: reset () noexcept -> void {

        if ( this->_pControl == nullptr ) {
            return;
        }

        __Deleter () ( cds :: exchange ( this->_pControl, nullptr )->__release () );
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto SharedPointer <
            __ElementType,
            __Deleter
    > :: reset (
            __ElementType * pointer
    ) noexcept -> void {

        if ( this->_pControl == nullptr ) {
            return;
        }

        __Deleter () ( cds :: exchange ( this->_pControl, ControlBlock :: __new ( pointer ) )->__release () );
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto SharedPointer <
            __ElementType [],
            __Deleter
    > :: reset (
            __ElementType * pointer
    ) noexcept -> void {

        if ( this->_pControl == nullptr ) {
            return;
        }

        __Deleter () ( cds :: exchange ( this->_pControl, ControlBlock :: __new ( pointer ) )->__release () );
    }


    template < typename __ElementType, typename __Deleter >
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


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto SharedPointer <
            __ElementType [],
            __Deleter
    > :: reset (
            std :: nullptr_t /* pointer */
    ) noexcept -> void {

        if ( this->_pControl == nullptr ) {
            return;
        }

        __Deleter () ( cds :: exchange ( this->_pControl, nullptr )->__release () );
    }

} /* namespace cds */

#endif /* __CDS_SHARED_POINTER_IMPL_HPP__ */
