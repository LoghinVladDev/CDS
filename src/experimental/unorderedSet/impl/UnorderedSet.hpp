//
// Created by loghin on 6/15/22.
//

#ifndef __CDS_EX_UNORDERED_SET_IMPL_HPP__
#define __CDS_EX_UNORDERED_SET_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr UnorderedSet < __ElementType > :: UnorderedSet () noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline UnorderedSet < __ElementType > :: UnorderedSet (
                UnorderedSet const & set
        ) noexcept :
                ListSet < __ElementType > ( set ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr UnorderedSet < __ElementType > :: UnorderedSet (
                UnorderedSet && set
        ) noexcept :
                ListSet < __ElementType > ( std :: move ( set ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __IteratorType, cds :: meta :: EnableIf < cds :: meta :: isIterator < __IteratorType > () > > // NOLINT(bugprone-reserved-identifier)
        UnorderedSet < __ElementType > :: UnorderedSet (
                __IteratorType          const & begin,
                __IteratorType          const & end
        ) noexcept {

            for ( auto iterator = begin; iterator != end; ++ iterator ) {
                this->insert ( * iterator );
            }
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline UnorderedSet < __ElementType > :: UnorderedSet (
                InitializerList         const & initializerList
        ) noexcept :
                UnorderedSet (
                        initializerList.begin(),
                        initializerList.end()
                ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline UnorderedSet < __ElementType > :: UnorderedSet (
                Collection < __OtherElementType >   const & collection
        ) noexcept :
                UnorderedSet (
                        collection.begin(),
                        collection.end()
                ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        UnorderedSet < __ElementType > :: ~UnorderedSet() noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto UnorderedSet < __ElementType > :: pNewInsert (
                ElementType const & referenceElement
        ) noexcept -> ElementType * & {

            if ( this->empty() ) {

                this->_pFront           = Memory :: instance().create < Node > ();
                this->_pFront->_pData   = nullptr;
                this->_pFront->_pNext   = nullptr;
                this->_size             = 1ULL;

                return this->_pFront->_pData;
            }

            if ( cds :: meta :: equals ( * this->_pFront->_pData, referenceElement ) ) {
                return this->_pFront->_pData;
            }

            auto pHead = this->_pFront;
            while ( pHead->_pNext != nullptr ) {
                if ( cds :: meta :: equals ( * pHead->_pNext->_pData, referenceElement ) ) {
                    return pHead->_pNext->_pData;
                }

                pHead = pHead->_pNext;
            }

            auto pNode      = Memory :: instance().create < Node > ();
            pNode->_pNext   = nullptr;
            pNode->_pData   = nullptr;
            pHead->_pNext   = pNode;
            ++ this->_size;

            return pNode->_pData;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto UnorderedSet < __ElementType > :: operator == (
                UnorderedSet const & set
        ) const noexcept -> bool {

            if ( this == & set ) {
                return true;
            }

            if ( this->size() != set.size() ) {
                return false;
            }

            auto pThisHead    = this->_pFront;
            auto pOtherHead   = set._pFront;

            while ( pThisHead != nullptr ) {

                if ( ! cds :: meta :: equals ( * pThisHead->_pData, * pOtherHead->_pData ) ) {
                    return false;
                }

                pThisHead   = pThisHead->_pNext;
                pOtherHead  = pOtherHead->_pNext;
            }

            return true;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto UnorderedSet < __ElementType > :: operator != (
                UnorderedSet const & set
        ) const noexcept -> bool {

            return ! this->operator== ( set );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto UnorderedSet < __ElementType > :: operator = (
                UnorderedSet const & set
        ) noexcept -> UnorderedSet & {

            if ( this == & set ) {
                return * this;
            }

            this->clear();

            Node * pLocalBack = nullptr;
            for ( auto pOtherHead = set._pFront; pOtherHead != nullptr; pOtherHead = pOtherHead->_pNext ) {

                auto pNewNode = Memory :: instance().create < Node > ();
                pNewNode->_pNext = nullptr;
                pNewNode->_pData = Memory :: instance().create < __ElementType > ( * pOtherHead._pData );

                if ( this->_pFront == nullptr ) {
                    this->_pFront       = pNewNode;
                    pLocalBack          = pNewNode;
                } else {
                    pLocalBack->_pNext  = pNewNode;
                    pLocalBack          = pNewNode;
                }
            }

            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto UnorderedSet < __ElementType > :: operator = (
                UnorderedSet && set
        ) noexcept -> UnorderedSet & {

            if ( this == & set ) {
                return * this;
            }

            this->clear();

            this->_pFront   = cds :: exchange ( set._pFront, nullptr );
            this->_size     = cds ::exchange ( set._size, 0ULL );

            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto UnorderedSet < __ElementType > :: operator = (
                Collection < __OtherElementType > const & collection
        ) noexcept -> UnorderedSet & {

            this->clear();

            for ( auto iterator = collection.begin(), end = collection.end(); iterator != end; ++ iterator ) {
                this->insert ( * iterator );
            }

            return * this;
        }

    }
}

#endif // __CDS_EX_UNORDERED_SET_IMPL_HPP__
