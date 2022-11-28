/*
 * Created by loghin on 27/11/22.
 */

#ifndef __CDS_UNIQUE_POINTER_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_UNIQUE_POINTER_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template < typename __ElementType, typename __Deleter >
    constexpr UniquePointer <
            __ElementType,
            __Deleter
    > :: UniquePointer (
            __ElementType * pointer
    ) noexcept :
            Base ( pointer ) {

    }


    template < typename __ElementType, typename __Deleter >
    constexpr UniquePointer <
            __ElementType [],
            __Deleter
    > :: UniquePointer (
            __ElementType * pointer
    ) noexcept :
            Base ( pointer ) {

    }


    template < typename __ElementType, typename __Deleter >
    constexpr UniquePointer <
            __ElementType,
            __Deleter
    > :: UniquePointer (
            UniquePointer && pointer
    ) noexcept :
            Base ( std :: move ( pointer ) ) {

    }


    template < typename __ElementType, typename __Deleter >
    constexpr UniquePointer <
            __ElementType [],
            __Deleter
    > :: UniquePointer (
            UniquePointer && pointer
    ) noexcept :
            Base ( std :: move ( pointer ) ) {

    }


    template < typename __ElementType, typename __Deleter >
    __CDS_cpplang_ConstexprDestructor UniquePointer <
            __ElementType,
            __Deleter
    > :: ~UniquePointer () noexcept {

        __Deleter () (this->_pObject);
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_cpplang_ConstexprDestructor UniquePointer <
            __ElementType [],
            __Deleter
    > :: ~UniquePointer () noexcept {

        __Deleter () (this->_pObject);
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto UniquePointer <
            __ElementType,
            __Deleter
    > :: operator = (
            __ElementType * pointer
    ) noexcept -> UniquePointer & {

        this->reset (pointer);
        return * this;
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto UniquePointer <
            __ElementType [],
            __Deleter
    > :: operator = (
            __ElementType * pointer
    ) noexcept -> UniquePointer & {

        this->reset (pointer);
        return * this;
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto UniquePointer <
            __ElementType [],
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


    template < typename __ElementType, typename __Deleter >
    __CDS_cpplang_NonConstConstexprMemberFunction auto UniquePointer <
            __ElementType,
            __Deleter
    > :: exchange (
            __ElementType * pointer
    ) noexcept -> __ElementType * {

        return cds :: exchange ( this->_pObject, pointer );
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_cpplang_NonConstConstexprMemberFunction auto UniquePointer <
            __ElementType [],
            __Deleter
    > :: exchange (
            __ElementType * pointer
    ) noexcept -> __ElementType * {

        return cds :: exchange ( this->_pObject, pointer );
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_cpplang_ConstexprOverride auto UniquePointer <
            __ElementType,
            __Deleter
    > :: release () noexcept -> __ElementType * {

        return this->exchange ( nullptr );
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_cpplang_ConstexprOverride auto UniquePointer <
            __ElementType [],
            __Deleter
    > :: release () noexcept -> __ElementType * {

        return this->exchange ( nullptr );
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto UniquePointer <
            __ElementType,
            __Deleter
    > :: reset () noexcept -> void {

        __Deleter () (this->release());
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto UniquePointer <
            __ElementType [],
            __Deleter
    > :: reset () noexcept -> void {

        __Deleter () (this->release());
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto UniquePointer <
            __ElementType,
            __Deleter
    > :: reset (
            __ElementType * pointer
    ) noexcept -> void {

        __Deleter () (this->exchange(pointer));
    }


    template < typename __ElementType, typename __Deleter >
    __CDS_OptimalInline auto UniquePointer <
            __ElementType [],
            __Deleter
    > :: reset (
            __ElementType * pointer
    ) noexcept -> void {

        __Deleter () (this->exchange(pointer));
    }


    template < typename __ElementType, typename __Deleter >
    template < typename __NumericType >
    constexpr auto UniquePointer <
            __ElementType [],
            __Deleter
    > :: operator [] (
            __NumericType index
    ) const noexcept -> __ElementType & {

        return this->_pObject [ index ];
    }

} /* namespace cds */

#endif /* __CDS_UNIQUE_POINTER_IMPL_HPP__ */
