//
// Created by loghin on 6/23/22.
//

#if defined ( __CDS_EX_HASH_MAP_HPP__ ) && defined ( CDS_SEQUENCE_HPP )

#ifndef __CDS_EX_HASH_MAP_SEQUENCE_IMPL_HPP__
#define __CDS_EX_HASH_MAP_SEQUENCE_IMPL_HPP__


namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: sequence () & noexcept -> Sequence < HashMap < __KeyType, __ValueType, __Hasher > > {

            return Sequence < cds :: meta :: RemoveReference < decltype ( * this ) > > ( * this );
        }

        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: sequence () && noexcept -> Sequence < HashMap < __KeyType, __ValueType, __Hasher > > {

            return Sequence < cds :: meta :: RemoveReference < decltype ( * this ) > > ( std :: move ( * this ) );
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: sequence () const & noexcept -> Sequence < HashMap < __KeyType, __ValueType, __Hasher > const > {

            return Sequence < cds :: meta :: RemoveReference < decltype ( * this ) > > ( * this );
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: sequence () const && noexcept -> Sequence < HashMap < __KeyType, __ValueType, __Hasher > const > {

            return Sequence < cds :: meta :: RemoveReference < decltype ( * this ) > > ( std :: move ( * this ) );
        }

    }
}


#endif // __CDS_EX_HASH_MAP_SEQUENCE_IMPL_HPP__

#endif // defined ( __CDS_EX_HASH_MAP_HPP__ ) && defined ( CDS_SEQUENCE_HPP )
