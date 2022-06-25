//
// Created by loghin on 6/13/22.
//

#if defined ( __CDS_ORDERED_SET_HPP__ ) && defined ( CDS_SEQUENCE_HPP )

#ifndef __CDS_SHARED_ORDERED_SET_SEQUENCE_IMPL_HPP__
#define __CDS_SHARED_ORDERED_SET_SEQUENCE_IMPL_HPP__


namespace cds {

    template < typename __ElementType, typename __ComparatorFunction > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto OrderedSet < __ElementType, __ComparatorFunction > :: sequence () & noexcept -> Sequence < OrderedSet < __ElementType, __ComparatorFunction > > {

        return Sequence < cds :: meta :: RemoveReference < decltype (*this) > > ( * this );
    }


    template < typename __ElementType, typename __ComparatorFunction > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto OrderedSet < __ElementType, __ComparatorFunction > :: sequence () const & noexcept -> Sequence < OrderedSet < __ElementType, __ComparatorFunction > const > {

        return Sequence < cds :: meta :: RemoveReference < decltype (*this) > > (*this);
    }


    template < typename __ElementType, typename __ComparatorFunction > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto OrderedSet < __ElementType, __ComparatorFunction > :: sequence () && noexcept -> Sequence < OrderedSet < __ElementType, __ComparatorFunction > > {

        return Sequence < cds :: meta :: RemoveReference < decltype (*this) > > (std::move(*this));
    }


    template < typename __ElementType, typename __ComparatorFunction > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto OrderedSet < __ElementType, __ComparatorFunction > :: sequence () const && noexcept -> Sequence < OrderedSet < __ElementType, __ComparatorFunction > const > {

        return Sequence < cds :: meta :: RemoveReference < decltype (*this) > > (std::move(*this));
    }

}

#endif //__CDS_SHARED_ORDERED_SET_SEQUENCE_IMPL_HPP__

#endif
