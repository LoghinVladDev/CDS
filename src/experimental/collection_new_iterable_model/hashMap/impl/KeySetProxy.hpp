/*
 * Created by loghin on 14/08/22.
 */

#ifndef __CDS_EX_HASH_MAP_KEY_SET_PROXY_IMPL_HPP__
#define __CDS_EX_HASH_MAP_KEY_SET_PROXY_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprOverride auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: KeySetProxy :: __cicch_obtainGenericHandler (
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) noexcept -> __GenericHandler {

            return this->__ss_handlers() [ static_cast < uint32 > ( requestType ) ];
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprOverride auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: KeySetProxy :: __cicch_obtainGenericConstHandler (
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) const noexcept -> __GenericConstHandler {

            return this->__ss_constHandlers() [ static_cast < uint32 > ( requestType ) ];
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > constexpr HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: KeySetProxy :: KeySetProxy (
                HashMap < __KeyType, __ValueType, __Hasher > * pMap
        ) noexcept :
                AbstractKeySetProxy ( pMap ) {

        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprDestructor HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: KeySetProxy :: ~KeySetProxy () noexcept = default;


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > constexpr auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: KeySetProxy :: __cbeginLocal () const noexcept -> ConstIterator {

            return ConstIterator ( this->template map < HashMapBase > ()->__cbegin() );
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > constexpr auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: KeySetProxy :: __cendLocal () const noexcept -> ConstIterator {

            return ConstIterator ( this->template map < HashMapBase > ()->__cend() );
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: KeySetProxy :: __cbegin () const noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < __KeyType const > * {

            return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < __KeyType const, ConstIterator > > (
                    ConstIterator ( this->template map < HashMapBase > ()->__cbeginLocal() )
            );
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: KeySetProxy :: __cend () const noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < __KeyType const > * {

            return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < __KeyType const, ConstIterator > > (
                    ConstIterator ( this->template map < HashMapBase > ()->__cendLocal() )
            );
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: KeySetProxy :: __removeConst (
                ConstIterator const * pIterator
        ) noexcept -> bool {

            return this->template map < HashMapBase > ()->__removeConst ( & pIterator->iterator() );
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: KeySetProxy :: __findConst (
                __KeyType const & key
        ) const noexcept -> ConstIterator {

            return ConstIterator ( this->template map < HashMapBase > ()->__findConst ( key ) );
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: KeySetProxy :: __equals (
                KeySetProxy const & set
        ) const noexcept -> bool {

            if ( this == & set ) {
                return true;
            }

            if ( this->size() != set.size() ) {
                return false;
            }

            for (
                    auto
                        leftIt  = this->begin(),    rightIt     = set.begin(),
                        leftEnd = this->end(),      rightEnd    = set.end();

                    leftIt != leftEnd;
                    ++ leftIt, ++ rightIt
            ) {
                if ( ! cds :: meta :: equals ( * leftIt, * rightIt ) ) {
                    return false;
                }
            }

            return true;
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: KeySetProxy :: operator == (
                KeySetProxy const & set
        ) const noexcept -> bool {

            return this->__equals ( set );
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: KeySetProxy :: operator != (
                KeySetProxy const & set
        ) const noexcept -> bool {

            return ! this->__equals ( set );
        }

    }
}

#endif /* __CDS_EX_HASH_MAP_KEY_SET_PROXY_IMPL_HPP__ */
