/*
 * Created by loghin on 10/10/22.
 */

#if defined ( __CDS_LINKED_HASH_MAP_HPP__ ) && defined ( CDS_SEQUENCE_HPP )

#ifndef __CDS_SHARED_LINKED_HASH_MAP_SEQUENCE_IMPL_HPP__
#define __CDS_SHARED_LINKED_HASH_MAP_SEQUENCE_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {

    template < typename __KeyType, typename __ValueType, typename __Hasher > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_OptimalInline auto LinkedHashMap < __KeyType, __ValueType, __Hasher > :: sequence () & noexcept -> Sequence < LinkedHashMap < __KeyType, __ValueType, __Hasher > > {

        return Sequence < cds :: meta :: RemoveReference < decltype (*this) > > ( * this );
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_OptimalInline auto LinkedHashMap < __KeyType, __ValueType, __Hasher > :: sequence () const & noexcept -> Sequence < LinkedHashMap < __KeyType, __ValueType, __Hasher > const > {

        return Sequence < cds :: meta :: RemoveReference < decltype (*this) > > ( * this );
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_OptimalInline auto LinkedHashMap < __KeyType, __ValueType, __Hasher > :: sequence () && noexcept -> Sequence < LinkedHashMap < __KeyType, __ValueType, __Hasher > > {

        return Sequence < cds :: meta :: RemoveReference < decltype (*this) > > ( * this );
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_OptimalInline auto LinkedHashMap < __KeyType, __ValueType, __Hasher > :: sequence () const && noexcept -> Sequence < LinkedHashMap < __KeyType, __ValueType, __Hasher > const > {

        return Sequence < cds :: meta :: RemoveReference < decltype (*this) > > ( * this );
    }

}

#endif /* __CDS_SHARED_LINKED_HASH_MAP_SEQUENCE_IMPL_HPP__ */

#endif
