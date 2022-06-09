//
// Created by loghin on 6/3/22.
//

#if defined ( __CDS_EX_ARRAY_HPP__ ) && defined ( CDS_SEQUENCE_HPP )

#ifndef __CDS_EX_ARRAY_SEQUENCE_IMPL_HPP__
#define __CDS_EX_ARRAY_SEQUENCE_IMPL_HPP__


namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        __CDS_OptimalInline auto Array < T > :: sequence () & noexcept -> Sequence < Array < T > > {
            return Sequence < meta :: RemoveReference < decltype (*this) > > ( * this );
        }

        template < typename T >
        __CDS_OptimalInline auto Array < T > :: sequence () const & noexcept -> Sequence < Array < T > const > {
            return Sequence < meta :: RemoveReference < decltype (*this) > > (*this);
        }

        template < typename T >
        __CDS_OptimalInline auto Array < T > :: sequence () && noexcept -> Sequence < Array < T > > {
            return Sequence < meta :: RemoveReference < decltype (*this) > > (std::move(*this));
        }

        template < typename T >
        __CDS_OptimalInline auto Array < T > :: sequence () const && noexcept -> Sequence < Array < T > const > {
            return Sequence < meta :: RemoveReference < decltype (*this) > > (std::move(*this));
        }

    }
}


#endif // __CDS_EX_ARRAY_SEQUENCE_IMPL_HPP__

#endif
