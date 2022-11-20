/*
 * Created by loghin on 20/11/22.
 */

#ifndef __CDS_SMART_POINTER_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SMART_POINTER_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename __ElementType,
                    cds :: meta :: EnableIf <
                            cds :: meta :: isPrintable < __ElementType > ()
                    > = 0
            > auto __ptrStringRep (
                    std :: ostream      & oss,
                    __ElementType const * pointer
            ) noexcept -> std :: ostream & {

                oss << "< 0x" << std :: hex << reinterpret_cast < Size > ( pointer ) << std :: dec << ": ";
                if ( pointer == nullptr ) {
                    oss << "null";
                } else {
                    oss << * pointer;
                }

                return ( oss << " >" );
            }


            template <
                    typename __ElementType,
                    cds :: meta :: EnableIf <
                            ! cds :: meta :: isPrintable < __ElementType > ()
                    > = 0
            > auto __ptrStringRep (
                    std :: ostream      & oss,
                    __ElementType const * pointer
            ) noexcept -> std :: ostream & {

                oss << "< 0x" << std :: hex << reinterpret_cast < Size > ( pointer ) << std :: dec << ": ";
                if ( pointer == nullptr ) {
                    oss << "null";
                } else {
                    oss << "unknown";
                }

                return ( oss << " >" );
            }

        } /* namespace __impl */
    } /* namespace __hidden */

    template < typename __ElementType >
    constexpr SmartPointer < __ElementType > :: SmartPointer (
            __ElementType * pObject
    ) noexcept :
            _pObject ( pObject ) {

    }


    template < typename __ElementType >
    constexpr SmartPointer < __ElementType > :: SmartPointer (
            SmartPointer < __ElementType > const & pointer
    ) noexcept :
            _pObject ( pointer._pObject ) {

    }


    template < typename __ElementType >
    constexpr SmartPointer < __ElementType > :: SmartPointer (
            SmartPointer < __ElementType > && pointer
    ) noexcept :
            _pObject ( cds :: exchange ( pointer._pObject, nullptr ) ) {

    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto SmartPointer < __ElementType > :: operator = (
            SmartPointer < __ElementType > const & pointer
    ) noexcept -> SmartPointer & {

        if ( this == & pointer ) {
            return * this;
        }

        this->_pObject = pointer._pObject;
        return * this;
    }


    template < typename __ElementType >
    __CDS_cpplang_NonConstConstexprMemberFunction auto SmartPointer < __ElementType > :: operator = (
            SmartPointer < __ElementType > && pointer
    ) noexcept -> SmartPointer & {

        if ( this == & pointer ) {
            return * this;
        }

        this->_pObject = cds :: exchange ( pointer._pObject, nullptr );
        return * this;
    }


    template < typename __ElementType >
    constexpr auto SmartPointer < __ElementType > :: operator == (
            SmartPointer const & pointer
    ) const noexcept -> bool {

        return this->_pObject == pointer._pObject;
    }


    template < typename __ElementType >
    constexpr auto SmartPointer < __ElementType > :: operator != (
            SmartPointer const & pointer
    ) const noexcept -> bool {

        return this->_pObject != pointer._pObject;
    }


    template < typename __ElementType >
    constexpr auto SmartPointer < __ElementType > :: operator == (
            __ElementType const * pointer
    ) const noexcept -> bool {

        return this->_pObject == pointer;
    }


    template < typename __ElementType >
    constexpr auto SmartPointer < __ElementType > :: operator != (
            __ElementType const * pointer
    ) const noexcept -> bool {

        return this->_pObject != pointer;
    }


    template < typename __ElementType >
    constexpr auto SmartPointer < __ElementType > :: operator == (
            std :: nullptr_t pointer
    ) const noexcept -> bool {

        return this->_pObject == pointer;
    }


    template < typename __ElementType >
    constexpr auto SmartPointer < __ElementType > :: operator != (
            std :: nullptr_t pointer
    ) const noexcept -> bool {

        return this->_pObject != pointer;
    }


    template < typename __ElementType >
    constexpr auto SmartPointer < __ElementType > :: isNull () const noexcept -> bool {

        return this->_pObject == nullptr;
    }


    template < typename __ElementType >
    __CDS_cpplang_ConstexprConditioned auto SmartPointer < __ElementType > :: operator * () const noexcept (false) -> __ElementType & {

        if ( this->_pObject == nullptr ) {
            throw NullPointerException ();
        }

        return * this->_pObject;
    }


    template < typename __ElementType >
    __CDS_cpplang_ConstexprConditioned auto SmartPointer < __ElementType > :: valueAt () const noexcept (false) -> __ElementType & {

        if ( this->_pObject == nullptr ) {
            throw NullPointerException ();
        }

        return * this->_pObject;
    }


    template < typename __ElementType >
    __CDS_cpplang_ConstexprConditioned auto SmartPointer < __ElementType > :: operator -> () const noexcept (false) -> __ElementType * {

        if ( this->_pObject == nullptr ) {
            throw NullPointerException ();
        }

        return this->_pObject;
    }


    template < typename __ElementType >
    constexpr auto SmartPointer < __ElementType > :: get () const noexcept -> __ElementType * {

        return this->_pObject;
    }


    template < typename __ElementType >
    constexpr SmartPointer < __ElementType > :: operator bool () const noexcept {

        return this->_pObject != nullptr;
    }


    template < typename __ElementType >
    constexpr SmartPointer < __ElementType > :: operator __ElementType * () const noexcept {

        return this->_pObject;
    }


    template < typename __ElementType >
    auto SmartPointer < __ElementType > :: equals (
            Object const & object
    ) const noexcept -> bool {

        if ( this == & object ) {
            return false;
        }

        auto pPointer = dynamic_cast < decltype (this) > ( & object );
        if ( pPointer == nullptr ) {
            return false;
        }

        return this->_pObject == pPointer->_pObject;
    }


    template < typename __ElementType >
    auto SmartPointer < __ElementType > :: toString () const noexcept -> String {

        std :: stringstream oss;
        __hidden :: __impl :: __ptrStringRep ( oss, this->_pObject );
        return oss.str();
    }


    template < typename __ElementType >
    auto SmartPointer < __ElementType > :: hash () const noexcept -> Size {

        return reinterpret_cast < Size > ( this->_pObject );
    }

} /* namespace cds */

#endif /* __CDS_SMART_POINTER_IMPL_HPP__ */
