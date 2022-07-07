//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ADDRESS_ITERATOR_HPP_IMPL__
#define __CDS_SHARED_ADDRESS_ITERATOR_HPP_IMPL__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr AbstractAddressIterator < __ElementType > :: AbstractAddressIterator () noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr AbstractAddressIterator < __ElementType > :: AbstractAddressIterator (
                Address address
        ) noexcept :
                _currentAddress ( address ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr AbstractAddressIterator < __ElementType > :: AbstractAddressIterator (
                AbstractAddressIterator const & iterator
        ) noexcept :
                _currentAddress ( iterator._currentAddress ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr AbstractAddressIterator < __ElementType > :: AbstractAddressIterator (
                AbstractAddressIterator && iterator
        ) noexcept :
                _currentAddress ( cds :: exchange ( iterator._currentAddress, nullptr ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto AbstractAddressIterator < __ElementType > :: current () const noexcept -> Address {

            return this->_currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto AbstractAddressIterator < __ElementType > :: copy (
                AbstractAddressIterator const & iterator
        ) noexcept -> void {

            this->_currentAddress = iterator._currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto AbstractAddressIterator < __ElementType > :: move (
                AbstractAddressIterator && iterator
        ) noexcept -> void {

            this->_currentAddress = cds :: exchange ( iterator._currentAddress, nullptr );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto AbstractAddressIterator < __ElementType > :: increment () noexcept -> void {

            ++ this->_currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto AbstractAddressIterator < __ElementType > :: decrement () noexcept -> void{

            -- this->_currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto AbstractAddressIterator < __ElementType > :: operator * () const noexcept -> __ElementType & {

            return * this->_currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto AbstractAddressIterator < __ElementType > :: operator -> () const noexcept -> __ElementType * {

            return this->_currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto AbstractAddressIterator < __ElementType > :: operator - (
                AbstractAddressIterator const & iterator
        ) const noexcept -> Size {

            return
                    this->_currentAddress > iterator._currentAddress ?
                    this->_currentAddress - iterator._currentAddress :
                    iterator._currentAddress - this->_currentAddress;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __NumericType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto AbstractAddressIterator < __ElementType > :: operator [] (
                __NumericType index
        ) const noexcept -> ElementType & {

            return this->_currentAddress [ index ];
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr AbstractAddressIterator < __ElementType > :: operator bool () const noexcept {

            return this->_currentAddress != nullptr;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr ForwardAddressIterator < __ElementType > :: ForwardAddressIterator () noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr ForwardAddressIterator < __ElementType > :: ForwardAddressIterator (
                Address address
        ) noexcept :
                AbstractAddressIterator < __ElementType > ( address ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr ForwardAddressIterator < __ElementType > :: ForwardAddressIterator (
                ForwardAddressIterator const & iterator
        ) noexcept :
                AbstractAddressIterator < __ElementType > ( iterator ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr ForwardAddressIterator < __ElementType > :: ForwardAddressIterator (
                ForwardAddressIterator && iterator
        ) noexcept :
                AbstractAddressIterator < __ElementType > ( std :: move ( iterator ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardAddressIterator < __ElementType > :: operator = (
                ForwardAddressIterator const & iterator
        ) noexcept -> ForwardAddressIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->copy ( iterator );
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardAddressIterator < __ElementType > :: operator = (
                ForwardAddressIterator && iterator
        ) noexcept -> ForwardAddressIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->move ( std :: move ( iterator ) );
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ForwardAddressIterator < __ElementType > :: operator == (
                ForwardAddressIterator const & iterator
        ) const noexcept -> bool {

            return this->current() == iterator.current();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ForwardAddressIterator < __ElementType > :: operator != (
                ForwardAddressIterator const & iterator
        ) const noexcept -> bool {

            return this->current() != iterator.current();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardAddressIterator < __ElementType > :: operator ++ () noexcept -> ForwardAddressIterator & {

            this->increment();
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardAddressIterator < __ElementType > :: operator ++ (int) noexcept -> ForwardAddressIterator {

            auto copy = * this;
            this->increment();
            return copy;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardAddressIterator < __ElementType > :: operator -- () noexcept -> ForwardAddressIterator & {

            this->decrement();
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardAddressIterator < __ElementType > :: operator -- (int) noexcept -> ForwardAddressIterator {

            auto copy = * this;
            this->decrement();
            return copy;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __NumericType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ForwardAddressIterator < __ElementType > :: operator + (
                __NumericType value
        ) const noexcept -> ForwardAddressIterator {

            return ForwardAddressIterator ( this->current() + value );
        }


        template < typename __FElementType, typename __NumericType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto operator + (
                __NumericType                               value,
                ForwardAddressIterator < __FElementType >  const & iterator
        ) noexcept -> ForwardAddressIterator < __FElementType > {

            return ForwardAddressIterator ( iterator.current() + value );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __NumericType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ForwardAddressIterator < __ElementType > :: operator - (
                __NumericType value
        ) const noexcept -> ForwardAddressIterator {

            return ForwardAddressIterator ( this->current() - value );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ForwardAddressIterator < __ElementType > :: operator > (
                ForwardAddressIterator const & iterator
        ) const noexcept -> bool {

            return this->current() > iterator.current();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ForwardAddressIterator < __ElementType > :: operator < (
                ForwardAddressIterator const & iterator
        ) const noexcept -> bool {

            return this->current() < iterator.current();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ForwardAddressIterator < __ElementType > :: operator >= (
                ForwardAddressIterator const & iterator
        ) const noexcept -> bool {

            return this->current() >= iterator.current();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ForwardAddressIterator < __ElementType > :: operator <= (
                ForwardAddressIterator const & iterator
        ) const noexcept -> bool {

            return this->current() <= iterator.current();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr BackwardAddressIterator < __ElementType > :: BackwardAddressIterator () noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr BackwardAddressIterator < __ElementType > :: BackwardAddressIterator (
                Address address
        ) noexcept :
                AbstractAddressIterator < __ElementType > ( address ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr BackwardAddressIterator < __ElementType > :: BackwardAddressIterator (
                BackwardAddressIterator const & iterator
        ) noexcept :
                AbstractAddressIterator < __ElementType > ( iterator ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr BackwardAddressIterator < __ElementType > :: BackwardAddressIterator (
                BackwardAddressIterator && iterator
        ) noexcept :
                AbstractAddressIterator < __ElementType > ( std :: move ( iterator ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardAddressIterator < __ElementType > :: operator = (
                BackwardAddressIterator const & iterator
        ) noexcept -> BackwardAddressIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->copy ( iterator );
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardAddressIterator < __ElementType > :: operator = (
                BackwardAddressIterator && iterator
        ) noexcept -> BackwardAddressIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->move ( std :: move ( iterator ) );
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto BackwardAddressIterator < __ElementType > :: operator == (
                BackwardAddressIterator const & iterator
        ) const noexcept -> bool {

            return this->current() == iterator.current();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto BackwardAddressIterator < __ElementType > :: operator != (
                BackwardAddressIterator const & iterator
        ) const noexcept -> bool {

            return this->current() != iterator.current();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardAddressIterator < __ElementType > :: operator ++ () noexcept -> BackwardAddressIterator & {

            this->decrement();
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardAddressIterator < __ElementType > :: operator ++ (int) noexcept -> BackwardAddressIterator {

            auto copy = * this;
            this->decrement();
            return copy;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardAddressIterator < __ElementType > :: operator -- () noexcept -> BackwardAddressIterator & {

            this->increment();
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardAddressIterator < __ElementType > :: operator -- (int) noexcept -> BackwardAddressIterator {

            auto copy = * this;
            this->increment();
            return copy;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __NumericType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto BackwardAddressIterator < __ElementType > :: operator + (
                __NumericType value
        ) const noexcept -> BackwardAddressIterator {

            return BackwardAddressIterator ( this->current() - value );
        }


        template < typename __FElementType, typename __NumericType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto operator + (
                __NumericType                                       value,
                BackwardAddressIterator < __FElementType >  const & iterator
        ) noexcept -> BackwardAddressIterator < __FElementType > {

            return BackwardAddressIterator ( iterator.current() - value );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __NumericType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto BackwardAddressIterator < __ElementType > :: operator - (
                __NumericType value
        ) const noexcept -> BackwardAddressIterator {

            return BackwardAddressIterator ( this->current() + value );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto BackwardAddressIterator < __ElementType > :: operator > (
                BackwardAddressIterator const & iterator
        ) const noexcept -> bool {

            return this->current() <= iterator.current();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto BackwardAddressIterator < __ElementType > :: operator < (
                BackwardAddressIterator const & iterator
        ) const noexcept -> bool {

            return this->current() >= iterator.current();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto BackwardAddressIterator < __ElementType > :: operator >= (
                BackwardAddressIterator const & iterator
        ) const noexcept -> bool {

            return this->current() < iterator.current();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto BackwardAddressIterator < __ElementType > :: operator <= (
                BackwardAddressIterator const & iterator
        ) const noexcept -> bool {

            return this->current() > iterator.current();
        }

    }
}

#endif // __CDS_SHARED_ADDRESS_ITERATOR_HPP_IMPL__
