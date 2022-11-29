/*
 * Created by loghin on 28/11/22.
 */

#ifndef __CDS_RAW_POINTER_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_RAW_POINTER_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template < typename __ElementType >
    constexpr RawPointer < __ElementType > :: RawPointer (
            __ElementType * pointer
    ) noexcept :
            _pObject ( pointer ) {

    }


    template < typename __ElementType >
    constexpr RawPointer < __ElementType [] > :: RawPointer (
            __ElementType * pointer
    ) noexcept :
            _pObject ( pointer ) {

    }


    template < typename __ElementType >
    constexpr RawPointer < __ElementType > :: RawPointer (
            RawPointer const & pointer
    ) noexcept :
            _pObject ( pointer._pObject ) {

    }


    template < typename __ElementType >
    constexpr RawPointer < __ElementType [] > :: RawPointer (
            RawPointer const & pointer
    ) noexcept :
            _pObject ( pointer._pObject ) {

    }


    template < typename __ElementType >
    constexpr RawPointer < __ElementType > :: RawPointer (
            RawPointer && pointer
    ) noexcept :
            _pObject ( cds :: exchange ( pointer._pObject, nullptr ) ) {

    }


    template < typename __ElementType >
    constexpr RawPointer < __ElementType [] > :: RawPointer (
            RawPointer && pointer
    ) noexcept :
            _pObject ( cds :: exchange ( pointer._pObject, nullptr ) ) {

    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto RawPointer < __ElementType > :: operator = (
            __ElementType * pointer
    ) noexcept -> RawPointer & {

        this->_pObject = pointer;
        return * this;
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto RawPointer < __ElementType [] > :: operator = (
            __ElementType * pointer
    ) noexcept -> RawPointer & {

        this->_pObject = pointer;
        return * this;
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto RawPointer < __ElementType > :: operator = (
            RawPointer const & pointer
    ) noexcept -> RawPointer & {

        this->_pObject = pointer._pObject;
        return * this;
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto RawPointer < __ElementType [] > :: operator = (
            RawPointer const & pointer
    ) noexcept -> RawPointer & {

        this->_pObject = pointer._pObject;
        return * this;
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto RawPointer < __ElementType > :: operator = (
            RawPointer && pointer
    ) noexcept -> RawPointer & {

        this->_pObject = cds :: exchange ( pointer._pObject, nullptr );
        return * this;
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto RawPointer < __ElementType [] > :: operator = (
            RawPointer && pointer
    ) noexcept -> RawPointer & {

        this->_pObject = cds :: exchange ( pointer._pObject, nullptr );
        return * this;
    }


    template < typename __ElementType >
    constexpr auto RawPointer < __ElementType > :: operator == (
            __ElementType const * pointer
    ) const noexcept -> bool {

        return this->_pObject == pointer;
    }


    template < typename __ElementType >
    constexpr auto RawPointer < __ElementType [] > :: operator == (
            __ElementType const * pointer
    ) const noexcept -> bool {

        return this->_pObject == pointer;
    }


    template < typename __ElementType >
    constexpr auto RawPointer < __ElementType > :: operator != (
            __ElementType const * pointer
    ) const noexcept -> bool {

        return this->_pObject != pointer;
    }


    template < typename __ElementType >
    constexpr auto RawPointer < __ElementType [] > :: operator != (
            __ElementType const * pointer
    ) const noexcept -> bool {

        return this->_pObject != pointer;
    }


    template < typename __ElementType >
    __CDS_cpplang_VirtualConstexpr auto RawPointer < __ElementType > :: operator == (
            Base const & pointer
    ) const noexcept -> bool {

        return this->_pObject == pointer.get();
    }


    template < typename __ElementType >
    __CDS_cpplang_VirtualConstexpr auto RawPointer < __ElementType [] > :: operator == (
            Base const & pointer
    ) const noexcept -> bool {

        return this->_pObject == pointer.get();
    }


    template < typename __ElementType >
    __CDS_cpplang_VirtualConstexpr auto RawPointer < __ElementType > :: operator != (
            Base const & pointer
    ) const noexcept -> bool {

        return this->_pObject != pointer.get();
    }


    template < typename __ElementType >
    __CDS_cpplang_VirtualConstexpr auto RawPointer < __ElementType [] > :: operator != (
            Base const & pointer
    ) const noexcept -> bool {

        return this->_pObject != pointer.get();
    }


    template < typename __ElementType >
    constexpr auto RawPointer < __ElementType > :: operator == (
            RawPointer const & pointer
    ) const noexcept -> bool {

        return this->_pObject == pointer._pObject;
    }


    template < typename __ElementType >
    constexpr auto RawPointer < __ElementType [] > :: operator == (
            RawPointer const & pointer
    ) const noexcept -> bool {

        return this->_pObject == pointer._pObject;
    }


    template < typename __ElementType >
    constexpr auto RawPointer < __ElementType > :: operator != (
            RawPointer const & pointer
    ) const noexcept -> bool {

        return this->_pObject != pointer._pObject;
    }


    template < typename __ElementType >
    constexpr auto RawPointer < __ElementType [] > :: operator != (
            RawPointer const & pointer
    ) const noexcept -> bool {

        return this->_pObject != pointer._pObject;
    }


    template < typename __ElementType >
    constexpr auto RawPointer < __ElementType > :: operator == (
            std :: nullptr_t pointer
    ) const noexcept -> bool {

        return this->_pObject == pointer;
    }


    template < typename __ElementType >
    constexpr auto RawPointer < __ElementType [] > :: operator == (
            std :: nullptr_t pointer
    ) const noexcept -> bool {

        return this->_pObject == pointer;
    }


    template < typename __ElementType >
    constexpr auto RawPointer < __ElementType > :: operator != (
            std :: nullptr_t pointer
    ) const noexcept -> bool {

        return this->_pObject != pointer;
    }


    template < typename __ElementType >
    constexpr auto RawPointer < __ElementType [] > :: operator != (
            std :: nullptr_t pointer
    ) const noexcept -> bool {

        return this->_pObject != pointer;
    }


    template < typename __ElementType >
    __CDS_cpplang_ConstexprOverride auto RawPointer < __ElementType > :: valueAt () const noexcept (false) -> __ElementType & {

        if ( this->_pObject == nullptr ) {
            throw NullPointerException ();
        }

        return * this->_pObject;
    }


    template < typename __ElementType >
    __CDS_cpplang_ConstexprOverride auto RawPointer < __ElementType [] > :: valueAt () const noexcept (false) -> __ElementType & {

        if ( this->_pObject == nullptr ) {
            throw NullPointerException ();
        }

        return * this->_pObject;
    }


    template < typename __ElementType >
    __CDS_cpplang_ConstexprOverride auto RawPointer < __ElementType > :: get () const noexcept -> __ElementType * {

        return this->_pObject;
    }


    template < typename __ElementType >
    __CDS_cpplang_ConstexprOverride auto RawPointer < __ElementType [] > :: get () const noexcept -> __ElementType * {

        return this->_pObject;
    }


    template < typename __ElementType >
    __CDS_cpplang_ConstexprOverride auto RawPointer < __ElementType > :: exchange (
            __ElementType * pointer
    ) noexcept -> __ElementType * {

        return cds :: exchange ( this->_pObject, pointer );
    }


    template < typename __ElementType >
    __CDS_cpplang_ConstexprOverride auto RawPointer < __ElementType [] > :: exchange (
            __ElementType * pointer
    ) noexcept -> __ElementType * {

        return cds :: exchange ( this->_pObject, pointer );
    }


    template < typename __ElementType >
    __CDS_cpplang_ConstexprOverride auto RawPointer < __ElementType > :: release () noexcept -> __ElementType * {

        return cds :: exchange ( this->_pObject, nullptr );
    }


    template < typename __ElementType >
    __CDS_cpplang_ConstexprOverride auto RawPointer < __ElementType [] > :: release () noexcept -> __ElementType * {

        return cds :: exchange ( this->_pObject, nullptr );
    }


    template < typename __ElementType >
    __CDS_cpplang_ConstexprOverride auto RawPointer < __ElementType > :: reset () noexcept -> void {

        this->_pObject = nullptr;
    }


    template < typename __ElementType >
    __CDS_cpplang_ConstexprOverride auto RawPointer < __ElementType [] > :: reset () noexcept -> void {

        this->_pObject = nullptr;
    }


    template < typename __ElementType >
    __CDS_cpplang_ConstexprOverride auto RawPointer < __ElementType > :: reset (
            __ElementType * pointer
    ) noexcept -> void {

        this->_pObject = pointer;
    }


    template < typename __ElementType >
    __CDS_cpplang_ConstexprOverride auto RawPointer < __ElementType [] > :: reset (
            __ElementType * pointer
    ) noexcept -> void {

        this->_pObject = pointer;
    }

} /* namespace cds */

#endif /* __CDS_RAW_POINTER_IMPL_HPP__ */
