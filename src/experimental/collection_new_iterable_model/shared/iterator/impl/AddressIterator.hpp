/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_SHARED_ADDRESS_ITERATOR_HPP_IMPL__
#define __CDS_SHARED_ADDRESS_ITERATOR_HPP_IMPL__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr AbstractAddressIterator < __ElementType > :: AbstractAddressIterator () noexcept = default;


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr AbstractAddressIterator < __ElementType > :: AbstractAddressIterator (
                Address pElement
        ) noexcept :
                _currentAddress ( pElement ) {

            /* copy given address value */
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr AbstractAddressIterator < __ElementType > :: AbstractAddressIterator (
                AbstractAddressIterator const & iterator
        ) noexcept :
                _currentAddress ( iterator._currentAddress ) {

            /* copy iterator address value */
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr AbstractAddressIterator < __ElementType > :: AbstractAddressIterator (
                AbstractAddressIterator && iterator
        ) noexcept :
                _currentAddress ( cds :: exchange ( iterator._currentAddress, nullptr ) ) {

            /* move iterator address value */
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto AbstractAddressIterator < __ElementType > :: current () const noexcept -> Address {

            /* return current address */
            return this->_currentAddress;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto AbstractAddressIterator < __ElementType > :: copy (
                AbstractAddressIterator const & iterator
        ) noexcept -> void {

            /* copy given iterator address value */
            this->_currentAddress = iterator._currentAddress;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto AbstractAddressIterator < __ElementType > :: move (
                AbstractAddressIterator && iterator
        ) noexcept -> void {

            /* move given iterator address value */
            this->_currentAddress = cds :: exchange ( iterator._currentAddress, nullptr );
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto AbstractAddressIterator < __ElementType > :: operator * () const noexcept -> __ElementType & {

            /* return value at given address */
            return * this->_currentAddress;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto AbstractAddressIterator < __ElementType > :: operator -> () const noexcept -> __ElementType * {

            /* return address of the element directly */
            return this->_currentAddress;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto AbstractAddressIterator < __ElementType > :: operator == (
                AbstractAddressIterator < __ElementType > const & iterator
        ) const noexcept -> bool {

            /* iterators are equal if addresses are equal */
            return this->current() == iterator.current();
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto AbstractAddressIterator < __ElementType > :: operator != (
                AbstractAddressIterator < __ElementType > const & iterator
        ) const noexcept -> bool {

            /* iterators are not equal if addresses are not equal */
            return this->current() != iterator.current();
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto AbstractAddressIterator < __ElementType > :: operator - (
                AbstractAddressIterator const & iterator
        ) const noexcept -> Size {

            /* return the difference in absolute value */
            return
                    this->_currentAddress > iterator._currentAddress ?
                    this->_currentAddress - iterator._currentAddress :
                    iterator._currentAddress - this->_currentAddress;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        template < typename __NumericType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto AbstractAddressIterator < __ElementType > :: operator [] (
                __NumericType index
        ) const noexcept -> ElementType & {

            /* return the element at given offset */
            return this->_currentAddress [ index ];
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr AbstractAddressIterator < __ElementType > :: operator bool () const noexcept {

            /* iterator is valid if not null */
            return this->_currentAddress != nullptr;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr ForwardAddressIterator < __ElementType > :: ForwardAddressIterator () noexcept = default;


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr ForwardAddressIterator < __ElementType > :: ForwardAddressIterator (
                Address address
        ) noexcept :
                AbstractAddressIterator < __ElementType > ( address ) {

            /* pass the address to the base class to be copied */
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr ForwardAddressIterator < __ElementType > :: ForwardAddressIterator (
                ForwardAddressIterator const & iterator
        ) noexcept :
                AbstractAddressIterator < __ElementType > ( iterator ) {

            /* pass the iterator to the base class to be copied */
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr ForwardAddressIterator < __ElementType > :: ForwardAddressIterator (
                ForwardAddressIterator && iterator
        ) noexcept :
                AbstractAddressIterator < __ElementType > ( std :: move ( iterator ) ) {

            /* pass the iterator to the base class to be moved */
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardAddressIterator < __ElementType > :: operator = (
                ForwardAddressIterator const & iterator
        ) noexcept -> ForwardAddressIterator & {

            /* if same iterator, copy is unnecessary */
            if ( this == & iterator ) {
                return * this;
            }

            /* otherwise, pass iterator to base class function to be copied */
            this->copy ( iterator );
            return * this;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardAddressIterator < __ElementType > :: operator = (
                ForwardAddressIterator && iterator
        ) noexcept -> ForwardAddressIterator & {

            /* if same iterator, move is unnecessary */
            if ( this == & iterator ) {
                return * this;
            }

            /* otherwise, pass iterator to base class function to be moved */
            this->move ( std :: move ( iterator ) );
            return * this;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto ForwardAddressIterator < __ElementType > :: operator == (
                ForwardAddressIterator const & iterator
        ) const noexcept -> bool {

            /* iterators are equal if addresses are equal */
            return this->_currentAddress == iterator._currentAddress;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto ForwardAddressIterator < __ElementType > :: operator != (
                ForwardAddressIterator const & iterator
        ) const noexcept -> bool {

            /* iterators are not equal if addresses are not equal */
            return this->_currentAddress != iterator._currentAddress;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardAddressIterator < __ElementType > :: operator ++ () noexcept -> ForwardAddressIterator & {

            /* Forward Iterator - advance forward */
            ++ this->_currentAddress;
            return * this;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardAddressIterator < __ElementType > :: operator ++ (int) noexcept -> ForwardAddressIterator {

            /* Forward Iterator - create copy, advance forward, return copy */
            auto copy = * this;
            ++ this->_currentAddress;
            return copy;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardAddressIterator < __ElementType > :: operator -- () noexcept -> ForwardAddressIterator & {

            /* Forward Iterator - advance backward */
            -- this->_currentAddress;
            return * this;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardAddressIterator < __ElementType > :: operator -- (int) noexcept -> ForwardAddressIterator {

            /* Forward Iterator - create copy, advance backward, return copy */
            auto copy = * this;
            -- this->_currentAddress;
            return copy;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        template < typename __NumericType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto ForwardAddressIterator < __ElementType > :: operator + (
                __NumericType value
        ) const noexcept -> ForwardAddressIterator {

            /* Forward Iterator - positive offset from current address */
            return ForwardAddressIterator ( this->_currentAddress + value );
        }


        template < typename __FElementType, typename __NumericType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto operator + (
                __NumericType                                      value,
                ForwardAddressIterator < __FElementType >  const & iterator
        ) noexcept -> ForwardAddressIterator < __FElementType > {

            /* Forward Iterator - positive offset from given iterator address */
            return ForwardAddressIterator ( iterator._currentAddress + value );
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        template < typename __NumericType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto ForwardAddressIterator < __ElementType > :: operator - (
                __NumericType value
        ) const noexcept -> ForwardAddressIterator {

            /* Forward Iterator - negative offset from given iterator address */
            return ForwardAddressIterator ( this->_currentAddress - value );
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto ForwardAddressIterator < __ElementType > :: operator - (
                ForwardAddressIterator const & iterator
        ) const noexcept -> Size {

            /* Compute absolute distance between iterators */
            return
                    this->_currentAddress > iterator._currentAddress ?
                    this->_currentAddress - iterator._currentAddress :
                    iterator._currentAddress - this->_currentAddress;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto ForwardAddressIterator < __ElementType > :: operator > (
                ForwardAddressIterator const & iterator
        ) const noexcept -> bool {

            /* Forward Iterator - greater than iterator is same as greater than address */
            return this->_currentAddress > iterator._currentAddress;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto ForwardAddressIterator < __ElementType > :: operator < (
                ForwardAddressIterator const & iterator
        ) const noexcept -> bool {

            /* Forward Iterator - less than iterator is same as less than address */
            return this->_currentAddress < iterator._currentAddress;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto ForwardAddressIterator < __ElementType > :: operator >= (
                ForwardAddressIterator const & iterator
        ) const noexcept -> bool {

            /* Forward Iterator - greater than or equal to iterator is same as greater than or equal to address */
            return this->_currentAddress >= iterator._currentAddress;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto ForwardAddressIterator < __ElementType > :: operator <= (
                ForwardAddressIterator const & iterator
        ) const noexcept -> bool {

            /* Forward Iterator - less than or equal to iterator is same as less than or equal to address */
            return this->_currentAddress <= iterator._currentAddress;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr BackwardAddressIterator < __ElementType > :: BackwardAddressIterator () noexcept = default;


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr BackwardAddressIterator < __ElementType > :: BackwardAddressIterator (
                Address address
        ) noexcept :
                AbstractAddressIterator < __ElementType > ( address ) {

            /* pass the address to the base class to be copied */
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr BackwardAddressIterator < __ElementType > :: BackwardAddressIterator (
                BackwardAddressIterator const & iterator
        ) noexcept :
                AbstractAddressIterator < __ElementType > ( iterator ) {

            /* pass the iterator to the base class to be copied */
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr BackwardAddressIterator < __ElementType > :: BackwardAddressIterator (
                BackwardAddressIterator && iterator
        ) noexcept :
                AbstractAddressIterator < __ElementType > ( std :: move ( iterator ) ) {

            /* pass the iterator to the base class to be moved */
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardAddressIterator < __ElementType > :: operator = (
                BackwardAddressIterator const & iterator
        ) noexcept -> BackwardAddressIterator & {

            /* if same iterator, copy is unnecessary */
            if ( this == & iterator ) {
                return * this;
            }

            /* otherwise, pass iterator to base class function to be copied */
            this->copy ( iterator );
            return * this;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardAddressIterator < __ElementType > :: operator = (
                BackwardAddressIterator && iterator
        ) noexcept -> BackwardAddressIterator & {

            /* if same iterator, move is unnecessary */
            if ( this == & iterator ) {
                return * this;
            }

            /* otherwise, pass iterator to base class function to be moved */
            this->move ( std :: move ( iterator ) );
            return * this;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto BackwardAddressIterator < __ElementType > :: operator == (
                BackwardAddressIterator const & iterator
        ) const noexcept -> bool {

            /* iterators are equal if addresses are equal */
            return this->_currentAddress == iterator._currentAddress;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto BackwardAddressIterator < __ElementType > :: operator != (
                BackwardAddressIterator const & iterator
        ) const noexcept -> bool {

            /* iterators are not equal if addresses are not equal */
            return this->_currentAddress != iterator._currentAddress;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardAddressIterator < __ElementType > :: operator ++ () noexcept -> BackwardAddressIterator & {

            /* Backward Iterator - advance backward */
            -- this->_currentAddress;
            return * this;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardAddressIterator < __ElementType > :: operator ++ (int) noexcept -> BackwardAddressIterator {

            /* Backward Iterator - create copy, advance backward, return copy */
            auto copy = * this;
            -- this->_currentAddress;
            return copy;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardAddressIterator < __ElementType > :: operator -- () noexcept -> BackwardAddressIterator & {

            /* Backward Iterator - advance forward */
            ++ this->_currentAddress;
            return * this;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardAddressIterator < __ElementType > :: operator -- (int) noexcept -> BackwardAddressIterator {

            /* BackwardIterator - create copy, advance forward, return copy */
            auto copy = * this;
            ++ this->_currentAddress;
            return copy;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        template < typename __NumericType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto BackwardAddressIterator < __ElementType > :: operator + (
                __NumericType value
        ) const noexcept -> BackwardAddressIterator {

            /* Backward Iterator - negative offset from current address */
            return BackwardAddressIterator ( this->_currentAddress - value );
        }


        template < typename __FElementType, typename __NumericType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto operator + (
                __NumericType                                       value,
                BackwardAddressIterator < __FElementType >  const & iterator
        ) noexcept -> BackwardAddressIterator < __FElementType > {

            /* Backward Iterator - negative offset from given iterator address */
            return BackwardAddressIterator ( iterator._currentAddress - value );
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        template < typename __NumericType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto BackwardAddressIterator < __ElementType > :: operator - (
                __NumericType value
        ) const noexcept -> BackwardAddressIterator {

            /* Backward Iterator - positive offset from given iterator address */
            return BackwardAddressIterator ( this->_currentAddress + value );
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto BackwardAddressIterator < __ElementType > :: operator - (
                BackwardAddressIterator const & iterator
        ) const noexcept -> Size {

            /* Compute absolute distance between iterators */
            return
                    this->_currentAddress > iterator._currentAddress ?
                    this->_currentAddress - iterator._currentAddress :
                    iterator._currentAddress - this->_currentAddress;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto BackwardAddressIterator < __ElementType > :: operator > (
                BackwardAddressIterator const & iterator
        ) const noexcept -> bool {

            /* Backward Iterator - greater than iterator is same as less than address */
            return this->_currentAddress < iterator._currentAddress;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto BackwardAddressIterator < __ElementType > :: operator < (
                BackwardAddressIterator const & iterator
        ) const noexcept -> bool {

            /* Backward Iterator - less than iterator is same as greater than address */
            return this->_currentAddress > iterator._currentAddress;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto BackwardAddressIterator < __ElementType > :: operator >= (
                BackwardAddressIterator const & iterator
        ) const noexcept -> bool {

            /* Forward Iterator - greater than or equal to iterator is same as less than or equal to address */
            return this->_currentAddress <= iterator._currentAddress;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto BackwardAddressIterator < __ElementType > :: operator <= (
                BackwardAddressIterator const & iterator
        ) const noexcept -> bool {

            /* Forward Iterator - less than or equal to iterator is same as greater than or equal to address */
            return this->_currentAddress >= iterator._currentAddress;
        }

    }
}

#endif /* __CDS_SHARED_ADDRESS_ITERATOR_HPP_IMPL__ */
