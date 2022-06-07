//
// Created by loghin on 6/7/22.
//

#if defined ( __CDS_EX_BASE_STRING_VIEW_HPP__ ) && defined ( CDS_SEQUENCE_HPP )

#ifndef __CDS_EX_BASE_STRING_VIEW_SEQEUENCE_IMPL_HPP__
#define __CDS_EX_BASE_STRING_VIEW_SEQEUENCE_IMPL_HPP__

namespace cds {
    namespace experimental {
        namespace hidden {
            namespace impl {

                template < typename CharType >
                __CDS_OptimalInline auto BaseStringView < CharType > :: sequence () const & noexcept -> Sequence < BaseStringView < CharType > const > {

                    return Sequence < RemoveReference < decltype (*this) > > ( * this );
                }

                template < typename CharType >
                __CDS_OptimalInline auto BaseStringView < CharType > :: sequence () const && noexcept -> Sequence < BaseStringView < CharType > const > {

                    return Sequence < RemoveReference < decltype (*this) > > ( std :: move ( * this ) );
                }

            }
        }
    }
}

#endif

#endif
