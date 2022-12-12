/*
 * Created by loghin on 04/12/22.
 */

#ifndef __CDS_UNION_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_UNION_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template < typename ... __Types >
    template <
            typename __ElementType,
            cds :: meta :: EnableIf <
                    ! cds :: meta :: isSame < cds :: meta :: Decay < __ElementType >, Union < __Types ... > > ()
            >
    > __CDS_cpplang_ConstexprConstructorNonEmptyBody Union <
            __Types ...
    > :: Union (
            __ElementType && value
    ) noexcept :
            __hidden :: __impl :: __VariadicUnion < __Types ... > ( std :: forward < __ElementType > ( value ) ) {

    }


    template < typename ... __Types >
    template <
            typename __ElementType,
            cds :: meta :: EnableIf <
                    ! cds :: meta :: isSame < cds :: meta :: Decay < __ElementType >, Union < __Types ... > > ()
            >
    > __CDS_cpplang_NonConstConstexprMemberFunction auto Union <
            __Types ...
    > :: operator = (
            __ElementType && value
    ) noexcept -> Union & {

        this->__vu_reset (
                std :: forward < __ElementType > ( value )
        );

        return * this;
    }


    template < typename ... __Types >
    constexpr auto Union <
            __Types ...
    > :: index () const noexcept -> Size {

        return this->__vu_holder ();
    }


    template < typename ... __Types >
    constexpr auto Union <
            __Types ...
    > :: empty () const noexcept -> bool {

        return this->__vu_valueless ();
    }


    template < typename ... __Types >
    template < typename __ElementType, typename ... __ConstructionArguments >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Union <
            __Types ...
    > :: emplace (
            __ConstructionArguments && ... arguments
    ) noexcept ( noexcept ( __ElementType ( std :: forward < __ConstructionArguments > ( arguments ) ... ) ) ) -> typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType & {

        return this->template __vu_emplace < typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType > (
                std :: forward < __ConstructionArguments > ( arguments ) ...
        );
    }


    template < typename ... __Types >
    template < typename __ElementType, typename __ListElementType, typename ... __ConstructionArguments >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Union <
            __Types ...
    > :: emplace (
            std :: initializer_list < __ListElementType > const &       list,
            __ConstructionArguments                            && ...   arguments
    ) noexcept ( noexcept ( __ElementType ( list, std :: forward < __ConstructionArguments > ( arguments ) ... ) ) ) -> typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType & {

        return this->template __vu_emplace < typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType > (
                list,
                std :: forward < __ConstructionArguments > ( arguments ) ...
        );
    }


    template < typename ... __Types >
    template < Size __index, typename __ListElementType, typename ... __ConstructionArguments >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Union <
            __Types ...
    > :: emplace (
            std :: initializer_list < __ListElementType > const &       list,
            __ConstructionArguments                            && ...   arguments
    ) noexcept ( noexcept ( typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type ( list, std :: forward < __ConstructionArguments > ( arguments ) ... ) ) ) -> typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type & {

        return this->template __vu_emplace < typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type > (
                list,
                std :: forward < __ConstructionArguments > ( arguments ) ...
        );
    }


    template < typename ... __Types >
    template < Size __index, typename ... __ConstructionArguments >
    __CDS_cpplang_NonConstConstexprMemberFunction auto Union <
            __Types ...
    > :: emplace (
            __ConstructionArguments && ... arguments
    ) noexcept ( noexcept ( typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type ( std :: forward < __ConstructionArguments > ( arguments ) ... ) ) ) -> typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type & {

        return this->template __vu_emplace < typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type > (
                std :: forward < __ConstructionArguments > ( arguments ) ...
        );
    }


    template < typename ... __Types >
    template < typename __ElementType >
    __CDS_cpplang_ConstexprConditioned auto Union <
            __Types ...
    > :: get () const noexcept ( false ) -> typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType const & {

        auto pObject = this->template __vu_getConst < typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType > ();
        if ( pObject == nullptr ) {
            throw TypeException ( String ( "Union does not contain requested Type. Current Type is Type at index : " ) + this->index() );
        }

        return * pObject;
    }


    template < typename ... __Types >
    template < Size __index >
    __CDS_cpplang_ConstexprConditioned auto Union <
            __Types ...
    > :: get () const noexcept ( false ) -> typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type const & {

        auto pObject = this->template __vu_getConst < typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type > ();
        if ( pObject == nullptr ) {
            throw TypeException ( String ( "Union does not contain requested Type. Current Type is Type at index : " ) + this->index() );
        }

        return * pObject;
    }


    template < typename ... __Types >
    template < typename __ElementType >
    __CDS_cpplang_ConstexprConditioned auto Union <
            __Types ...
    > :: get () noexcept ( false ) -> typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType & {

        auto pObject = this->template __vu_get < typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType > ();
        if ( pObject == nullptr ) {
            throw TypeException ( String ( "Union does not contain requested Type. Current Type is Type at index : " ) + this->index() );
        }

        return * pObject;
    }


    template < typename ... __Types >
    template < Size __index >
    __CDS_cpplang_ConstexprConditioned auto Union <
            __Types ...
    > :: get () noexcept ( false ) -> typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type & {

        auto pObject = this->template __vu_get < typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type > ();
        if ( pObject == nullptr ) {
            throw TypeException ( String ( "Union does not contain requested Type. Current Type is Type at index : " ) + this->index() );
        }

        return * pObject;
    }


    template < typename ... __Types >
    template < typename __ElementType >
    __CDS_cpplang_ConstexprConditioned auto Union <
            __Types ...
    > :: getPointer () const noexcept -> typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType const * {

        return this->template __vu_getConst < typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType > ();
    }


    template < typename ... __Types >
    template < Size __index >
    __CDS_cpplang_ConstexprConditioned auto Union <
            __Types ...
    > :: getPointer () const noexcept -> typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type const * {

        return this->template __vu_getConst < typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type > ();
    }


    template < typename ... __Types >
    template < typename __ElementType >
    __CDS_cpplang_ConstexprConditioned auto Union <
            __Types ...
    > :: getPointer () noexcept -> typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType * {

        return this->template __vu_get < typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType > ();
    }


    template < typename ... __Types >
    template < Size __index >
    __CDS_cpplang_ConstexprConditioned auto Union <
            __Types ...
    > :: getPointer () noexcept -> typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type * {

        return this->template __vu_get < typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type > ();
    }


    template < typename ... __Types >
    template < typename __ElementType >
    constexpr auto Union <
            __Types ...
    > :: is () const noexcept -> bool {

        return this->template is < __hidden :: __impl :: __UnionPackTypeTraits < __ElementType > :: __directInitIndex > ();
    }


    template < typename ... __Types >
    template < Size __index >
    constexpr auto Union <
            __Types ...
    > :: is () const noexcept -> bool {

        return this->index() == __index;
    }


    template < typename ... __Types >
    template < typename __ElementType, typename __Consumer >
    __CDS_cpplang_ConstexprConditioned auto Union <
            __Types ...
    > :: ifIs (
            __Consumer const & consumer
    ) noexcept ( noexcept ( consumer ( cds :: meta :: referenceOf < typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType > () ) ) ) -> void {

        auto pObject = this->template __vu_get < typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType > ();
        if ( pObject == nullptr ) {
            return;
        }

        consumer ( * pObject );
    }


    template < typename ... __Types >
    template < Size __index, typename __Consumer >
    __CDS_cpplang_ConstexprConditioned auto Union <
            __Types ...
    > :: ifIs (
            __Consumer const & consumer
    ) noexcept ( noexcept ( consumer ( cds :: meta :: referenceOf < typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type > () ) ) ) -> void {

        auto pObject = this->template __vu_get < typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type > ();
        if ( pObject == nullptr ) {
            return;
        }

        consumer ( * pObject );
    }


    template < typename ... __Types >
    template < typename __ElementType, typename __Consumer >
    __CDS_cpplang_ConstexprConditioned auto Union <
            __Types ...
    > :: ifIs (
            __Consumer const & consumer
    ) const noexcept ( noexcept ( consumer ( cds :: meta :: referenceOf < typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType const > () ) ) ) -> void {

        auto pObject = this->template __vu_getConst < typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType > ();
        if ( pObject == nullptr ) {
            return;
        }

        consumer ( * pObject );
    }


    template < typename ... __Types >
    template < Size __index, typename __Consumer >
    __CDS_cpplang_ConstexprConditioned auto Union <
            __Types ...
    > :: ifIs (
            __Consumer const & consumer
    ) const noexcept ( noexcept ( consumer ( cds :: meta :: referenceOf < typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type const > () ) ) ) -> void {

        auto pObject = this->template __vu_getConst < typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type > ();
        if ( pObject == nullptr ) {
            return;
        }

        consumer ( * pObject );
    }


    template < typename ... __Types >
    __CDS_OptimalInline auto Union <
            __Types ...
    > :: toString () const noexcept -> String {

        return this->__vu_toString ();
    }


    template < typename ... __Types >
    __CDS_cpplang_ConstexprOverride auto Union <
            __Types ...
    > :: hash () const noexcept -> Size {

        return this->__vu_hash ();
    }


    template < typename ... __Types >
    __CDS_OptimalInline auto Union <
            __Types ...
    > :: equals (
            Object const & object
    ) const noexcept -> bool {

        if ( this == & object ) {
            return true;
        }

        auto pUnion = dynamic_cast < decltype (this) > ( & object );
        if ( pUnion == nullptr ) {
            return false;
        }

        return this->__vu_equals ( * pUnion );
    }


    template < typename ... __Types >
    constexpr auto Union <
            __Types ...
    > :: operator == (
            Union const & object
    ) const noexcept -> bool {

        return
                this == & object ||
                this->__vu_equals ( object );
    }


    template < typename ... __Types >
    constexpr auto Union <
            __Types ...
    > :: operator != (
            Union const & object
    ) const noexcept -> bool {

        return
                this != & object &&
                ! this->__vu_equals ( object );
    }


    template < typename ... __Types >
    template < typename __ElementType >
    constexpr auto Union <
            __Types ...
    > :: operator == (
            __ElementType const & object
    ) const noexcept -> bool {

        return
                ! this->empty() &&
                this->index() == __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __directInitIndex &&
                * this->template __vu_getConst < typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType > () == object;
    }


    template < typename ... __Types >
    template < typename __ElementType >
    constexpr auto Union <
            __Types ...
    > :: operator != (
            __ElementType const & object
    ) const noexcept -> bool {

        return
                this->empty() ||
                this->index() != __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __directInitIndex ||
                * this->template __vu_getConst < typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType > () != object;
    }

} /* namespace cds */

#endif /* __CDS_UNION_IMPL_HPP__ */
