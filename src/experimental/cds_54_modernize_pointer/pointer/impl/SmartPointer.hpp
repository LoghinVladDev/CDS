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
    __CDS_cpplang_VirtualConstexpr auto SmartPointer < __ElementType > :: isNull () const noexcept -> bool {

        return this->get() == nullptr;
    }


    template < typename __ElementType >
    __CDS_cpplang_VirtualConstexpr auto SmartPointer < __ElementType [] > :: isNull () const noexcept -> bool {

        return this->get() == nullptr;
    }


    template < typename __ElementType >
    __CDS_cpplang_VirtualConstexpr auto SmartPointer < __ElementType > :: operator * () const noexcept (false) -> __ElementType & {

        return this->valueAt();
    }


    template < typename __ElementType >
    __CDS_cpplang_VirtualConstexpr auto SmartPointer < __ElementType [] > :: operator * () const noexcept (false) -> __ElementType & {

        return this->valueAt();
    }


    template < typename __ElementType >
    __CDS_cpplang_VirtualConstexpr auto SmartPointer < __ElementType > :: operator -> () const noexcept (false) -> __ElementType * {

        if ( this->_pObject == nullptr ) {
            throw NullPointerException ();
        }

        return this->get();
    }


    template < typename __ElementType >
    __CDS_cpplang_VirtualConstexpr auto SmartPointer < __ElementType [] > :: operator -> () const noexcept (false) -> __ElementType * {

        if ( this->_pObject == nullptr ) {
            throw NullPointerException ();
        }

        return this->get();
    }


    template < typename __ElementType >
    __CDS_cpplang_VirtualConstexpr SmartPointer < __ElementType > :: operator bool () const noexcept {

        return ! this->isNull();
    }


    template < typename __ElementType >
    __CDS_cpplang_VirtualConstexpr SmartPointer < __ElementType [] > :: operator bool () const noexcept {

        return ! this->isNull();
    }


    template < typename __ElementType >
    __CDS_cpplang_VirtualConstexpr SmartPointer < __ElementType > :: operator __ElementType * () const noexcept {

        return this->get();
    }


    template < typename __ElementType >
    __CDS_cpplang_VirtualConstexpr SmartPointer < __ElementType [] > :: operator __ElementType * () const noexcept {

        return this->get();
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

        return this->get() == pPointer->get();
    }


    template < typename __ElementType >
    auto SmartPointer < __ElementType [] > :: equals (
            Object const & object
    ) const noexcept -> bool {

        if ( this == & object ) {
            return false;
        }

        auto pPointer = dynamic_cast < decltype (this) > ( & object );
        if ( pPointer == nullptr ) {
            return false;
        }

        return this->get() == pPointer->get();
    }


    template < typename __ElementType >
    auto SmartPointer < __ElementType > :: toString () const noexcept -> String {

        std :: stringstream oss;
        __hidden :: __impl :: __ptrStringRep ( oss, this->get() );
        return oss.str();
    }


    template < typename __ElementType >
    auto SmartPointer < __ElementType [] > :: toString () const noexcept -> String {

        std :: stringstream oss;
        __hidden :: __impl :: __ptrStringRep ( oss, this->get() );
        return oss.str();
    }


    template < typename __ElementType >
    __CDS_cpplang_ConstexprOverride auto SmartPointer < __ElementType > :: hash () const noexcept -> Size {

        return reinterpret_cast < Size > ( this->get() );
    }


    template < typename __ElementType >
    __CDS_cpplang_ConstexprOverride auto SmartPointer < __ElementType [] > :: hash () const noexcept -> Size {

        return reinterpret_cast < Size > ( this->get() );
    }


    template < typename __ElementType >
    template < typename __NumericType >
    __CDS_cpplang_VirtualConstexpr auto SmartPointer < __ElementType [] > :: operator [] (
            __NumericType index
    ) const noexcept -> __ElementType & {

        return this->get() [index];
    }

} /* namespace cds */

#endif /* __CDS_SMART_POINTER_IMPL_HPP__ */
