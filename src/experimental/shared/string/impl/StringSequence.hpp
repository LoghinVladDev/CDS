//
// Created by loghin on 6/7/22.
//

#if defined ( __CDS_EX_STRING_BASE_HPP__ ) && defined ( CDS_SEQUENCE_HPP )

#ifndef __CDS_EX_BASE_STRING_SEQEUENCE_IMPL_HPP__
#define __CDS_EX_BASE_STRING_SEQEUENCE_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl { // NOLINT(bugprone-reserved-identifier)

                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: sequence () & noexcept -> Sequence < __BaseString < __CharType > > {

                    return Sequence < meta :: RemoveReference < decltype (*this) > > ( * this );
                }

                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: sequence () && noexcept -> Sequence < __BaseString < __CharType > > {

                    return Sequence < meta :: RemoveReference < decltype (*this) > > ( std :: move ( * this ) );
                }

                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: sequence () const & noexcept -> Sequence < __BaseString < __CharType > const > {

                    return Sequence < meta :: RemoveReference < decltype (*this) > > ( * this );
                }

                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_OptimalInline auto __BaseString < __CharType > :: sequence () const && noexcept -> Sequence < __BaseString < __CharType > const > {

                    return Sequence < meta :: RemoveReference < decltype (*this) > > ( std :: move ( * this ) );
                }

            }
        }
    }
}

#endif

#endif
