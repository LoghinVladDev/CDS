/*
 * Created by loghin on 6/13/22.
 */

#if defined ( __CDS_EX_HASH_SET_HPP__ ) && defined ( CDS_SEQUENCE_HPP )

#ifndef __CDS_SHARED_HASH_SET_SEQUENCE_IMPL_HPP__
#define __CDS_SHARED_HASH_SET_SEQUENCE_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */


namespace cds {
    namespace experimental {

        template < typename __ElementType, typename __Hasher > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_OptimalInline auto HashSet < __ElementType, __Hasher > :: sequence () & noexcept -> Sequence < HashSet < __ElementType, __Hasher > > {

            return Sequence < cds :: meta :: RemoveReference < decltype (*this) > > ( * this );
        }


        template < typename __ElementType, typename __Hasher > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_OptimalInline auto HashSet < __ElementType, __Hasher > :: sequence () const & noexcept -> Sequence < HashSet < __ElementType, __Hasher > const > {

            return Sequence < cds :: meta :: RemoveReference < decltype (*this) > > (*this);
        }


        template < typename __ElementType, typename __Hasher > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_OptimalInline auto HashSet < __ElementType, __Hasher > :: sequence () && noexcept -> Sequence < HashSet < __ElementType, __Hasher > > {

            return Sequence < cds :: meta :: RemoveReference < decltype (*this) > > (std::move(*this));
        }


        template < typename __ElementType, typename __Hasher > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_OptimalInline auto HashSet < __ElementType, __Hasher > :: sequence () const && noexcept -> Sequence < HashSet < __ElementType, __Hasher > const > {

            return Sequence < cds :: meta :: RemoveReference < decltype (*this) > > (std::move(*this));
        }

    }
}

#endif /* __CDS_SHARED_HASH_SET_SEQUENCE_IMPL_HPP__ */

#endif
