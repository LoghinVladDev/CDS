//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ADDRESS_ITERATOR_HPP_IMPL__
#define __CDS_SHARED_ADDRESS_ITERATOR_HPP_IMPL__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr AddressIterator < __ElementType > :: AddressIterator () noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr AddressIterator < __ElementType > :: AddressIterator (
                Address address
        ) noexcept :
                _currentAddress ( address ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr AddressIterator < __ElementType > :: AddressIterator (
                AddressIterator const & iterator
        ) noexcept :
                _currentAddress ( iterator._currentAddress ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr AddressIterator < __ElementType > :: AddressIterator (
                AddressIterator && iterator
        ) noexcept :
                _currentAddress ( cds :: exchange ( iterator._currentAddress, nullptr ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto AddressIterator < __ElementType > :: operator = (
                AddressIterator const & iterator
        ) noexcept -> AddressIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->_currentAddress = iterator._currentAddress;
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto AddressIterator < __ElementType > :: operator = (
                AddressIterator && iterator
        ) noexcept -> AddressIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->_currentAddress = cds :: exchange ( iterator._currentAddress, nullptr );
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto AddressIterator < __ElementType > :: operator == (
                AddressIterator const & iterator
        ) const noexcept -> bool {

            return this->_currentAddress == iterator._currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto AddressIterator < __ElementType > :: operator != (
                AddressIterator const & iterator
        ) const noexcept -> bool {

            return this->_currentAddress != iterator._currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto AddressIterator < __ElementType > :: operator * () const noexcept -> __ElementType & {

            return * this->_currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto AddressIterator < __ElementType > :: operator -> () const noexcept -> __ElementType * {

            return this->_currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto AddressIterator < __ElementType > :: operator ++ () noexcept -> AddressIterator & {

            ++ this->_currentAddress;
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto AddressIterator < __ElementType > :: operator ++ (int) noexcept -> AddressIterator {

            auto copy = * this;
            ++ this->_currentAddress;
            return copy;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto AddressIterator < __ElementType > :: operator -- () noexcept -> AddressIterator & {

            -- this->_currentAddress;
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto AddressIterator < __ElementType > :: operator -- (int) noexcept -> AddressIterator {

            auto copy = * this;
            -- this->_currentAddress;
            return copy;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __NumericType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto AddressIterator < __ElementType > :: operator + (
                __NumericType value
        ) const noexcept -> AddressIterator {

            return AddressIterator ( this->_currentAddress + value );
        }


        template < typename __FElementType, typename __NumericType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto operator + (
                __NumericType                               value,
                AddressIterator < __FElementType >  const & iterator
        ) noexcept -> AddressIterator < __FElementType > {

            return AddressIterator ( iterator._currentAddress + value );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __NumericType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto AddressIterator < __ElementType > :: operator - (
                __NumericType value
        ) const noexcept -> AddressIterator {

            return AddressIterator ( this->_currentAddress - value );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto AddressIterator < __ElementType > :: operator - (
                AddressIterator const & iterator
        ) const noexcept -> Size {

            return this->_currentAddress - iterator._currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto AddressIterator < __ElementType > :: operator > (
                AddressIterator const & iterator
        ) const noexcept -> bool {

            return this->_currentAddress > iterator._currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto AddressIterator < __ElementType > :: operator < (
                AddressIterator const & iterator
        ) const noexcept -> bool {

            return this->_currentAddress < iterator._currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto AddressIterator < __ElementType > :: operator >= (
                AddressIterator const & iterator
        ) const noexcept -> bool {

            return this->_currentAddress >= iterator._currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto AddressIterator < __ElementType > :: operator <= (
                AddressIterator const & iterator
        ) const noexcept -> bool {

            return this->_currentAddress <= iterator._currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __NumericType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto AddressIterator < __ElementType > :: operator [] (
                __NumericType index
        ) const noexcept -> ElementType & {

            return this->_currentAddress [ index ];
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr AddressIterator < __ElementType > :: operator bool () const noexcept {

            return this->_currentAddress != nullptr;
        }

    }
}

#endif // __CDS_SHARED_ADDRESS_ITERATOR_HPP_IMPL__
