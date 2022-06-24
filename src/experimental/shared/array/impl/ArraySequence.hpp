//
// Created by loghin on 6/3/22.
//

#if defined ( __CDS_EX_ARRAY_HPP__ ) && defined ( CDS_SEQUENCE_HPP )

#ifndef __CDS_EX_ARRAY_SEQUENCE_IMPL_HPP__
#define __CDS_EX_ARRAY_SEQUENCE_IMPL_HPP__


namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: sequence () & noexcept -> Sequence < Array < __ElementType > > {

            return Sequence < meta :: RemoveReference < decltype (*this) > > ( * this );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: sequence () const & noexcept -> Sequence < Array < __ElementType > const > {

            return Sequence < meta :: RemoveReference < decltype (*this) > > (*this);
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: sequence () && noexcept -> Sequence < Array < __ElementType > > {

            return Sequence < meta :: RemoveReference < decltype (*this) > > (std::move(*this));
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: sequence () const && noexcept -> Sequence < Array < __ElementType > const > {

            return Sequence < meta :: RemoveReference < decltype (*this) > > (std::move(*this));
        }

    }
}


#endif // __CDS_EX_ARRAY_SEQUENCE_IMPL_HPP__

#endif
