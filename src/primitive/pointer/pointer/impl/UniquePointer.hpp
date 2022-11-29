/* NOLINT(llvm-header-guard)
 * Created by loghin on 27/11/22.
 */

#ifndef __CDS_UNIQUE_POINTER_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_UNIQUE_POINTER_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr UniquePointer <
            __ElementType,
            __Deleter
    > :: UniquePointer (
            __ElementType * pointer
    ) noexcept :
            _pObject ( pointer ) {

    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr UniquePointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: UniquePointer (
            __ElementType * pointer
    ) noexcept :
            _pObject ( pointer ) {

    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr UniquePointer <
            __ElementType,
            __Deleter
    > :: UniquePointer (
            UniquePointer && pointer
    ) noexcept :
            _pObject ( cds :: exchange ( pointer._pObject, nullptr ) ) {

    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr UniquePointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: UniquePointer (
            UniquePointer && pointer
    ) noexcept :
            _pObject ( cds :: exchange ( pointer._pObject, nullptr ) ) {

    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprDestructor UniquePointer <
            __ElementType,
            __Deleter
    > :: ~UniquePointer () noexcept {

        __Deleter () (this->_pObject);
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprDestructor UniquePointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: ~UniquePointer () noexcept {

        __Deleter () (this->_pObject);
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto UniquePointer <
            __ElementType,
            __Deleter
    > :: operator = (
            __ElementType * pointer
    ) noexcept -> UniquePointer & {

        this->reset (pointer);
        return * this;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto UniquePointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator = (
            __ElementType * pointer
    ) noexcept -> UniquePointer & {

        this->reset (pointer);
        return * this;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto UniquePointer <
            __ElementType,
            __Deleter
    > :: operator = (
            UniquePointer && pointer
    ) noexcept -> UniquePointer & {

        if ( this == & pointer ) {
            return * this;
        }

        this->reset (pointer.release());
        return * this;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto UniquePointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator = (
            UniquePointer && pointer
    ) noexcept -> UniquePointer & {

        if ( this == & pointer ) {
            return * this;
        }

        this->reset (pointer.release());
        return * this;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto UniquePointer <
            __ElementType,
            __Deleter
    > :: operator == (
            __ElementType const * pointer
    ) const noexcept -> bool {

        return this->_pObject == pointer;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto UniquePointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator == (
            __ElementType const * pointer
    ) const noexcept -> bool {

        return this->_pObject == pointer;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto UniquePointer <
            __ElementType,
            __Deleter
    > :: operator != (
            __ElementType const * pointer
    ) const noexcept -> bool {

        return this->_pObject != pointer;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto UniquePointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator != (
            __ElementType const * pointer
    ) const noexcept -> bool {

        return this->_pObject != pointer;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_VirtualConstexpr auto UniquePointer <
            __ElementType,
            __Deleter
    > :: operator == (
            Base const & pointer
    ) const noexcept -> bool {

        return this->_pObject == pointer.get();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_VirtualConstexpr auto UniquePointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator == (
            Base const & pointer
    ) const noexcept -> bool {

        return this->_pObject == pointer.get();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_VirtualConstexpr auto UniquePointer <
            __ElementType,
            __Deleter
    > :: operator != (
            Base const & pointer
    ) const noexcept -> bool {

        return this->_pObject != pointer.get();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_VirtualConstexpr auto UniquePointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator != (
            Base const & pointer
    ) const noexcept -> bool {

        return this->_pObject != pointer.get();
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto UniquePointer <
            __ElementType,
            __Deleter
    > :: operator == (
            UniquePointer const & pointer
    ) const noexcept -> bool {

        return this->_pObject == pointer._pObject;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto UniquePointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator == (
            UniquePointer const & pointer
    ) const noexcept -> bool {

        return this->_pObject == pointer._pObject;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto UniquePointer <
            __ElementType,
            __Deleter
    > :: operator != (
            UniquePointer const & pointer
    ) const noexcept -> bool {

        return this->_pObject != pointer._pObject;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto UniquePointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator != (
            UniquePointer const & pointer
    ) const noexcept -> bool {

        return this->_pObject != pointer._pObject;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto UniquePointer <
            __ElementType,
            __Deleter
    > :: operator == (
            std :: nullptr_t pointer
    ) const noexcept -> bool {

        return this->_pObject == pointer;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto UniquePointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator == (
            std :: nullptr_t pointer
    ) const noexcept -> bool {

        return this->_pObject == pointer;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto UniquePointer <
            __ElementType,
            __Deleter
    > :: operator != (
            std :: nullptr_t pointer
    ) const noexcept -> bool {

        return this->_pObject != pointer;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto UniquePointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: operator != (
            std :: nullptr_t pointer
    ) const noexcept -> bool {

        return this->_pObject != pointer;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprOverride auto UniquePointer <
            __ElementType,
            __Deleter
    > :: valueAt () const noexcept (false) -> __ElementType & {

        if ( this->_pObject == nullptr ) {
            throw NullPointerException ();
        }

        return * this->_pObject;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprOverride auto UniquePointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: valueAt () const noexcept (false) -> __ElementType & {

        if ( this->_pObject == nullptr ) {
            throw NullPointerException ();
        }

        return * this->_pObject;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprOverride auto UniquePointer <
            __ElementType,
            __Deleter
    > :: get () const noexcept -> __ElementType * {

        return this->_pObject;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprOverride auto UniquePointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: get () const noexcept -> __ElementType * {

        return this->_pObject;
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprOverride auto UniquePointer <
            __ElementType,
            __Deleter
    > :: exchange (
            __ElementType * pointer
    ) noexcept -> __ElementType * {

        return cds :: exchange ( this->_pObject, pointer );
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprOverride auto UniquePointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: exchange (
            __ElementType * pointer
    ) noexcept -> __ElementType * {

        return cds :: exchange ( this->_pObject, pointer );
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprOverride auto UniquePointer <
            __ElementType,
            __Deleter
    > :: release () noexcept -> __ElementType * {

        return this->exchange ( nullptr );
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprOverride auto UniquePointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: release () noexcept -> __ElementType * {

        return this->exchange ( nullptr );
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto UniquePointer <
            __ElementType,
            __Deleter
    > :: reset () noexcept -> void {

        __Deleter () (this->release());
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto UniquePointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: reset () noexcept -> void {

        __Deleter () (this->release());
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto UniquePointer <
            __ElementType,
            __Deleter
    > :: reset (
            __ElementType * pointer
    ) noexcept -> void {

        __Deleter () (this->exchange(pointer));
    }


    template < typename __ElementType, typename __Deleter > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto UniquePointer <
            __ElementType [],                               /* NOLINT(*-avoid-c-arrays) */
            __Deleter
    > :: reset (
            __ElementType * pointer
    ) noexcept -> void {

        __Deleter () (this->exchange(pointer));
    }

} /* namespace cds */

#endif /* __CDS_UNIQUE_POINTER_IMPL_HPP__ */
