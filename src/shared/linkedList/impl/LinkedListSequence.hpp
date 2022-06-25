//
// Created by loghin on 6/3/22.
//

#if defined ( __CDS_LINKED_LIST_HPP__ ) && defined ( CDS_SEQUENCE_HPP )

#ifndef __CDS_SHARED_LINKED_LIST_SEQUENCE_IMPL_HPP__
#define __CDS_SHARED_LINKED_LIST_SEQUENCE_IMPL_HPP__


namespace cds {

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto LinkedList < __ElementType > :: sequence () & noexcept -> Sequence < LinkedList < __ElementType > > {

        return Sequence < meta :: RemoveReference < decltype (*this) > > ( * this );
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto LinkedList < __ElementType > :: sequence () const & noexcept -> Sequence < LinkedList < __ElementType > const > {

        return Sequence < meta :: RemoveReference < decltype (*this) > > (*this);
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto LinkedList < __ElementType > :: sequence () && noexcept -> Sequence < LinkedList < __ElementType > > {

        return Sequence < meta :: RemoveReference < decltype (*this) > > (std::move(*this));
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto LinkedList < __ElementType > :: sequence () const && noexcept -> Sequence < LinkedList < __ElementType > const > {

        return Sequence < meta :: RemoveReference < decltype (*this) > > (std::move(*this));
    }

}


#endif // __CDS_SHARED_LINKED_LIST_SEQUENCE_IMPL_HPP__

#endif
