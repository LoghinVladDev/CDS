//
// Created by loghin on 6/7/22.
//

#if defined ( __CDS_BASE_STRING_VIEW_HPP__ ) && defined ( CDS_SEQUENCE_HPP )

#ifndef __CDS_SHARED_BASE_STRING_VIEW_SEQEUENCE_IMPL_HPP__
#define __CDS_SHARED_BASE_STRING_VIEW_SEQEUENCE_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl { // NOLINT(bugprone-reserved-identifier)

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: sequence () const & noexcept -> Sequence < __BaseStringView < __CharType > const > {

                return Sequence < meta :: RemoveReference < decltype (*this) > > ( * this );
            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __BaseStringView < __CharType > :: sequence () const && noexcept -> Sequence < __BaseStringView < __CharType > const > {

                return Sequence < meta :: RemoveReference < decltype (*this) > > ( std :: move ( * this ) );
            }

        }
    }
}

#endif // __CDS_SHARED_BASE_STRING_VIEW_SEQEUENCE_IMPL_HPP__

#endif
