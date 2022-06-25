//
// Created by loghin on 6/13/22.
//

#if defined ( __CDS_HASH_SET_HPP__ ) && defined ( CDS_SEQUENCE_HPP )

#ifndef __CDS_SHARED_HASH_SET_SEQUENCE_IMPL_HPP__
#define __CDS_SHARED_HASH_SET_SEQUENCE_IMPL_HPP__


namespace cds {

    template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashSet < __ElementType, __HashCalculator > :: sequence () & noexcept -> Sequence < HashSet < __ElementType, __HashCalculator > > {

        return Sequence < cds :: meta :: RemoveReference < decltype (*this) > > ( * this );
    }


    template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashSet < __ElementType, __HashCalculator > :: sequence () const & noexcept -> Sequence < HashSet < __ElementType, __HashCalculator > const > {

        return Sequence < cds :: meta :: RemoveReference < decltype (*this) > > (*this);
    }


    template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashSet < __ElementType, __HashCalculator > :: sequence () && noexcept -> Sequence < HashSet < __ElementType, __HashCalculator > > {

        return Sequence < cds :: meta :: RemoveReference < decltype (*this) > > (std::move(*this));
    }


    template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashSet < __ElementType, __HashCalculator > :: sequence () const && noexcept -> Sequence < HashSet < __ElementType, __HashCalculator > const > {

        return Sequence < cds :: meta :: RemoveReference < decltype (*this) > > (std::move(*this));
    }

}

#endif //__CDS_SHARED_HASH_SET_SEQUENCE_IMPL_HPP__

#endif
