//
// Created by loghin on 6/13/22.
//

#if defined ( __CDS_UNORDERED_SET_HPP__ ) && defined ( CDS_SEQUENCE_HPP )

#ifndef __CDS_UNORDERED_SET_SEQUENCE_IMPL_HPP__
#define __CDS_UNORDERED_SET_SEQUENCE_IMPL_HPP__


namespace cds {

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto UnorderedSet < __ElementType > :: sequence () & noexcept -> Sequence < UnorderedSet < __ElementType > > {

        return Sequence < cds :: meta :: RemoveReference < decltype (*this) > > ( * this );
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto UnorderedSet < __ElementType > :: sequence () const & noexcept -> Sequence < UnorderedSet < __ElementType > const > {

        return Sequence < cds :: meta :: RemoveReference < decltype (*this) > > (*this);
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto UnorderedSet < __ElementType > :: sequence () && noexcept -> Sequence < UnorderedSet < __ElementType > > {

        return Sequence < cds :: meta :: RemoveReference < decltype (*this) > > (std::move(*this));
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto UnorderedSet < __ElementType > :: sequence () const && noexcept -> Sequence < UnorderedSet < __ElementType > const > {

        return Sequence < cds :: meta :: RemoveReference < decltype (*this) > > (std::move(*this));
    }

}

#endif //__CDS_UNORDERED_SET_SEQUENCE_IMPL_HPP__

#endif
