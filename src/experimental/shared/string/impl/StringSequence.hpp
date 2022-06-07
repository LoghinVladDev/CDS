//
// Created by loghin on 6/7/22.
//

#if defined ( __CDS_EX_STRING_BASE_HPP__ ) && defined ( CDS_SEQUENCE_HPP )

#ifndef __CDS_EX_BASE_STRING_SEQEUENCE_IMPL_HPP__
#define __CDS_EX_BASE_STRING_SEQEUENCE_IMPL_HPP__

namespace cds {
    namespace experimental {
        namespace hidden {
            namespace impl {

                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: sequence () & noexcept -> Sequence < BaseString < CharType > > {

                    return Sequence < RemoveReference < decltype (*this) > > ( * this );
                }

                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: sequence () && noexcept -> Sequence < BaseString < CharType > > {

                    return Sequence < RemoveReference < decltype (*this) > > ( std :: move ( * this ) );
                }

                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: sequence () const & noexcept -> Sequence < BaseString < CharType > const > {

                    return Sequence < RemoveReference < decltype (*this) > > ( * this );
                }

                template < typename CharType >
                __CDS_OptimalInline auto BaseString < CharType > :: sequence () const && noexcept -> Sequence < BaseString < CharType > const > {

                    return Sequence < RemoveReference < decltype (*this) > > ( std :: move ( * this ) );
                }

            }
        }
    }
}

#endif

#endif
