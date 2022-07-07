//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ADDRESS_ITERATOR_HPP_IMPL__
#define __CDS_SHARED_ADDRESS_ITERATOR_HPP_IMPL__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr ForwardAddressIterator < __ElementType > :: ForwardAddressIterator () noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr ForwardAddressIterator < __ElementType > :: ForwardAddressIterator (
                Address address
        ) noexcept :
                _currentAddress ( address ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr ForwardAddressIterator < __ElementType > :: ForwardAddressIterator (
                ForwardAddressIterator const & iterator
        ) noexcept :
                _currentAddress ( iterator._currentAddress ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr ForwardAddressIterator < __ElementType > :: ForwardAddressIterator (
                ForwardAddressIterator && iterator
        ) noexcept :
                _currentAddress ( cds :: exchange ( iterator._currentAddress, nullptr ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardAddressIterator < __ElementType > :: operator = (
                ForwardAddressIterator const & iterator
        ) noexcept -> ForwardAddressIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->_currentAddress = iterator._currentAddress;
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardAddressIterator < __ElementType > :: operator = (
                ForwardAddressIterator && iterator
        ) noexcept -> ForwardAddressIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->_currentAddress = cds :: exchange ( iterator._currentAddress, nullptr );
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ForwardAddressIterator < __ElementType > :: operator == (
                ForwardAddressIterator const & iterator
        ) const noexcept -> bool {

            return this->_currentAddress == iterator._currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ForwardAddressIterator < __ElementType > :: operator != (
                ForwardAddressIterator const & iterator
        ) const noexcept -> bool {

            return this->_currentAddress != iterator._currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ForwardAddressIterator < __ElementType > :: operator * () const noexcept -> __ElementType & {

            return * this->_currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ForwardAddressIterator < __ElementType > :: operator -> () const noexcept -> __ElementType * {

            return this->_currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardAddressIterator < __ElementType > :: operator ++ () noexcept -> ForwardAddressIterator & {

            ++ this->_currentAddress;
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardAddressIterator < __ElementType > :: operator ++ (int) noexcept -> ForwardAddressIterator {

            auto copy = * this;
            ++ this->_currentAddress;
            return copy;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardAddressIterator < __ElementType > :: operator -- () noexcept -> ForwardAddressIterator & {

            -- this->_currentAddress;
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardAddressIterator < __ElementType > :: operator -- (int) noexcept -> ForwardAddressIterator {

            auto copy = * this;
            -- this->_currentAddress;
            return copy;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __NumericType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ForwardAddressIterator < __ElementType > :: operator + (
                __NumericType value
        ) const noexcept -> ForwardAddressIterator {

            return ForwardAddressIterator ( this->_currentAddress + value );
        }


        template < typename __FElementType, typename __NumericType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto operator + (
                __NumericType                               value,
                ForwardAddressIterator < __FElementType >  const & iterator
        ) noexcept -> ForwardAddressIterator < __FElementType > {

            return ForwardAddressIterator ( iterator._currentAddress + value );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __NumericType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ForwardAddressIterator < __ElementType > :: operator - (
                __NumericType value
        ) const noexcept -> ForwardAddressIterator {

            return ForwardAddressIterator ( this->_currentAddress - value );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ForwardAddressIterator < __ElementType > :: operator - (
                ForwardAddressIterator const & iterator
        ) const noexcept -> Size {

            return this->_currentAddress - iterator._currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ForwardAddressIterator < __ElementType > :: operator > (
                ForwardAddressIterator const & iterator
        ) const noexcept -> bool {

            return this->_currentAddress > iterator._currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ForwardAddressIterator < __ElementType > :: operator < (
                ForwardAddressIterator const & iterator
        ) const noexcept -> bool {

            return this->_currentAddress < iterator._currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ForwardAddressIterator < __ElementType > :: operator >= (
                ForwardAddressIterator const & iterator
        ) const noexcept -> bool {

            return this->_currentAddress >= iterator._currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ForwardAddressIterator < __ElementType > :: operator <= (
                ForwardAddressIterator const & iterator
        ) const noexcept -> bool {

            return this->_currentAddress <= iterator._currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __NumericType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ForwardAddressIterator < __ElementType > :: operator [] (
                __NumericType index
        ) const noexcept -> ElementType & {

            return this->_currentAddress [ index ];
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr ForwardAddressIterator < __ElementType > :: operator bool () const noexcept {

            return this->_currentAddress != nullptr;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr BackwardAddressIterator < __ElementType > :: BackwardAddressIterator () noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr BackwardAddressIterator < __ElementType > :: BackwardAddressIterator (
                Address address
        ) noexcept :
                _currentAddress ( address ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr BackwardAddressIterator < __ElementType > :: BackwardAddressIterator (
                BackwardAddressIterator const & iterator
        ) noexcept :
                _currentAddress ( iterator._currentAddress ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr BackwardAddressIterator < __ElementType > :: BackwardAddressIterator (
                BackwardAddressIterator && iterator
        ) noexcept :
                _currentAddress ( cds :: exchange ( iterator._currentAddress, nullptr ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardAddressIterator < __ElementType > :: operator = (
                BackwardAddressIterator const & iterator
        ) noexcept -> BackwardAddressIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->_currentAddress = iterator._currentAddress;
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardAddressIterator < __ElementType > :: operator = (
                BackwardAddressIterator && iterator
        ) noexcept -> BackwardAddressIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->_currentAddress = cds :: exchange ( iterator._currentAddress, nullptr );
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto BackwardAddressIterator < __ElementType > :: operator == (
                BackwardAddressIterator const & iterator
        ) const noexcept -> bool {

            return this->_currentAddress == iterator._currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto BackwardAddressIterator < __ElementType > :: operator != (
                BackwardAddressIterator const & iterator
        ) const noexcept -> bool {

            return this->_currentAddress != iterator._currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto BackwardAddressIterator < __ElementType > :: operator * () const noexcept -> __ElementType & {

            return * this->_currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto BackwardAddressIterator < __ElementType > :: operator -> () const noexcept -> __ElementType * {

            return this->_currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardAddressIterator < __ElementType > :: operator ++ () noexcept -> BackwardAddressIterator & {

            -- this->_currentAddress;
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardAddressIterator < __ElementType > :: operator ++ (int) noexcept -> BackwardAddressIterator {

            auto copy = * this;
            -- this->_currentAddress;
            return copy;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardAddressIterator < __ElementType > :: operator -- () noexcept -> BackwardAddressIterator & {

            ++ this->_currentAddress;
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardAddressIterator < __ElementType > :: operator -- (int) noexcept -> BackwardAddressIterator {

            auto copy = * this;
            ++ this->_currentAddress;
            return copy;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __NumericType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto BackwardAddressIterator < __ElementType > :: operator + (
                __NumericType value
        ) const noexcept -> BackwardAddressIterator {

            return BackwardAddressIterator ( this->_currentAddress - value );
        }


        template < typename __FElementType, typename __NumericType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto operator + (
                __NumericType                                       value,
                BackwardAddressIterator < __FElementType >  const & iterator
        ) noexcept -> BackwardAddressIterator < __FElementType > {

            return BackwardAddressIterator ( iterator._currentAddress - value );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __NumericType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto BackwardAddressIterator < __ElementType > :: operator - (
                __NumericType value
        ) const noexcept -> BackwardAddressIterator {

            return BackwardAddressIterator ( this->_currentAddress + value );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto BackwardAddressIterator < __ElementType > :: operator - (
                BackwardAddressIterator const & iterator
        ) const noexcept -> Size {

            return this->_currentAddress + iterator._currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto BackwardAddressIterator < __ElementType > :: operator > (
                BackwardAddressIterator const & iterator
        ) const noexcept -> bool {

            return this->_currentAddress <= iterator._currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto BackwardAddressIterator < __ElementType > :: operator < (
                BackwardAddressIterator const & iterator
        ) const noexcept -> bool {

            return this->_currentAddress >= iterator._currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto BackwardAddressIterator < __ElementType > :: operator >= (
                BackwardAddressIterator const & iterator
        ) const noexcept -> bool {

            return this->_currentAddress < iterator._currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto BackwardAddressIterator < __ElementType > :: operator <= (
                BackwardAddressIterator const & iterator
        ) const noexcept -> bool {

            return this->_currentAddress > iterator._currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __NumericType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto BackwardAddressIterator < __ElementType > :: operator [] (
                __NumericType index
        ) const noexcept -> ElementType & {

            return * ( this->_currentAddress - index );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr BackwardAddressIterator < __ElementType > :: operator bool () const noexcept {

            return this->_currentAddress != nullptr;
        }

    }
}

#endif // __CDS_SHARED_ADDRESS_ITERATOR_HPP_IMPL__
