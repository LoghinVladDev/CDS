//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_MUTABLE_COLLECTION_IMPL_HPP__
#define __CDS_MUTABLE_COLLECTION_IMPL_HPP__

namespace cds {

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    constexpr auto MutableCollection < __ElementType > :: acquireDelegate (
            Iterator const & iterator
    ) noexcept -> DelegateIterator const * {

        return reinterpret_cast < DelegateIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) );
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    constexpr auto MutableCollection < __ElementType > :: acquireDelegate (
            ReverseIterator const & iterator
    ) noexcept -> DelegateIterator const * {

        return reinterpret_cast < DelegateIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) );
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto MutableCollection < __ElementType > :: begin () noexcept -> Iterator {

        return Iterator ( this, std :: move ( this->delegateIterator ( DelegateIteratorRequestType :: ForwardBegin ) ) );
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto MutableCollection < __ElementType > :: end () noexcept -> Iterator {

        return Iterator ( this, std :: move ( this->delegateIterator ( DelegateIteratorRequestType :: ForwardEnd ) ) );
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto MutableCollection < __ElementType > :: rbegin () noexcept -> ReverseIterator {

        return Iterator ( this, std :: move ( this->delegateIterator ( DelegateIteratorRequestType :: BackwardBegin ) ) );
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto MutableCollection < __ElementType > :: rend () noexcept -> ReverseIterator {

        return Iterator ( this, std :: move ( this->delegateIterator ( DelegateIteratorRequestType :: BackwardEnd ) ) );
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    constexpr MutableCollection < __ElementType > :: MutableCollection (
            MutableCollection const & collection
    ) noexcept :
            Collection < __ElementType > ( collection ) {

    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    constexpr MutableCollection < __ElementType > :: MutableCollection () noexcept = default;


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    constexpr MutableCollection < __ElementType > :: MutableCollection (
            MutableCollection && collection
    ) noexcept :
            Collection < __ElementType > ( std :: move ( collection ) ) {

    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprDestructor MutableCollection < __ElementType > :: ~MutableCollection () noexcept = default;


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: find (
            Size                                        maxCount,
            ElementType                         const & element,
            __CollectionType < Iterator >             & storeIn
    ) noexcept -> __CollectionType < Iterator > & {

        Size found = 0ULL;
        for ( auto iterator = this->begin(), end = this->end(); iterator != end && found < maxCount; ++ iterator ) {
            if ( meta :: equals ( element, * iterator ) ) {
                ++ found;

                storeIn.add ( iterator );
            }
        }

        return storeIn;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: find (
            Size                                        maxCount,
            ElementType                         const & element
    ) noexcept -> __CollectionType < Iterator > {

        __CollectionType < Iterator > iterators;
        return this-> find ( maxCount, element, iterators );
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findFirst (
            ElementType const & element
    ) noexcept -> Iterator {

        auto end = this->end();
        for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
            if ( meta :: equals ( element, * iterator ) ) {
                return iterator;
            }
        }

        return end;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findLast (
            ElementType const & element
    ) noexcept -> Iterator {

        auto end = this->end();
        auto lastFound = end;
        for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
            if ( meta :: equals ( element, * iterator ) ) {
                lastFound = iterator;
            }
        }

        return lastFound;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findAll (
            ElementType                         const & element,
            __CollectionType < Iterator >             & storeIn
    ) noexcept -> __CollectionType < Iterator > & {

        for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
            if ( meta :: equals ( element, * iterator ) ) {
                storeIn.add ( iterator );
            }
        }

        return storeIn;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findAll (
            ElementType                         const & element
    ) noexcept -> __CollectionType < Iterator > {

        __CollectionType < Iterator > iterators;
        return this-> findAll ( element, iterators );
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findOf (
            Size                                        maxCount,
            Collection < ElementType >          const & elements,
            __CollectionType < Iterator >             & storeIn
    ) noexcept -> __CollectionType < Iterator > & {

        Size found = 0ULL;
        for ( auto iterator = this->begin(), end = this->end(); iterator != end && found < maxCount; ++ iterator ) {
            if ( elements.contains ( * iterator ) ) {
                ++ found;

                storeIn.add ( iterator );
            }
        }

        return storeIn;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findOf (
            Size                                        maxCount,
            Collection < ElementType >          const & elements
    ) noexcept -> __CollectionType < Iterator > {

        __CollectionType < Iterator > iterators;
        return this-> findOf ( maxCount, elements, iterators );
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findFirstOf (
            Collection < ElementType > const & elements
    ) noexcept -> Iterator {

        auto end = this->end();
        for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
            if ( elements.contains ( * iterator ) ) {
                return iterator;
            }
        }

        return end;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findLastOf (
            Collection < ElementType > const & elements
    ) noexcept -> Iterator {

        auto end = this->end();
        auto lastFound = end;
        for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
            if ( elements.contains ( * iterator ) ) {
                lastFound = end;
            }
        }

        return lastFound;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findAllOf (
            Collection < ElementType >          const & elements,
            __CollectionType < Iterator >               & storeIn
    ) noexcept -> __CollectionType < Iterator > & {

        for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
            if ( elements.contains ( * iterator ) ) {
                storeIn.add ( iterator );
            }
        }

        return storeIn;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findAllOf (
            Collection < ElementType >          const & elements
    ) noexcept -> __CollectionType < Iterator > {

        Collection < Iterator > iterators;
        return this->findAllOf ( elements, iterators );
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findNotOf (
            Size                                        maxCount,
            Collection < ElementType >          const & elements,
            __CollectionType < Iterator >             & storeIn
    ) noexcept -> __CollectionType < Iterator > & {

        Size found = 0ULL;
        for ( auto iterator = this->begin(), end = this->end(); iterator != end && found < maxCount; ++ iterator ) {
            if ( ! elements.contains ( * iterator ) ) {
                ++ found;

                storeIn.add ( iterator );
            }
        }

        return storeIn;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findNotOf (
            Size                                        maxCount,
            Collection < ElementType >          const & elements
    ) noexcept -> __CollectionType < Iterator > {

        __CollectionType < Iterator > iterators;
        return this-> findNotOf ( maxCount, elements, iterators );
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findFirstNotOf (
            Collection < ElementType > const & elements
    ) noexcept -> Iterator {

        auto end = this->end();
        for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
            if ( ! elements.contains ( * iterator ) ) {
                return iterator;
            }
        }

        return end;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findLastNotOf (
            Collection < ElementType > const & elements
    ) noexcept -> Iterator {

        auto end = this->end();
        auto lastFound = end;
        for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
            if ( ! elements.contains ( * iterator ) ) {
                lastFound = iterator;
            }
        }

        return lastFound;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findAllNotOf (
            Collection < ElementType >          const & elements,
            __CollectionType < Iterator >             & storeIn
    ) noexcept -> __CollectionType < Iterator > & {

        for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
            if ( ! elements.contains ( * iterator ) ) {
                storeIn.add ( iterator );
            }
        }

        return storeIn;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findAllNotOf (
            Collection < ElementType >  const & elements
    ) noexcept -> __CollectionType < Iterator > {

        __CollectionType < Iterator > iterators;
        return this-> findAllNotOf ( elements, iterators );
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findOf (
            Size                                        maxCount,
            InitializerList                     const & elements,
            __CollectionType < Iterator >             & storeIn
    ) noexcept -> __CollectionType < Iterator > & {

        Size found = 0ULL;
        for ( auto iterator = this->begin(), end = this->end(); iterator != end && found < maxCount; ++ iterator ) {
            if ( __hidden :: __impl :: __initializerListContains ( elements, * iterator ) ) {
                ++ found;

                storeIn.add ( iterator );
            }
        }

        return storeIn;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findOf (
            Size                                        maxCount,
            InitializerList                     const & elements
    ) noexcept -> __CollectionType < Iterator > {

        __CollectionType < Iterator > iterators;
        return this-> findOf ( maxCount, elements, iterators );
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findFirstOf (
            InitializerList const & elements
    ) noexcept -> Iterator {

        auto end = this->end();
        for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
            if ( __hidden :: __impl :: __initializerListContains ( elements, * iterator ) ) {
                return iterator;
            }
        }

        return end;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findLastOf (
            InitializerList const & elements
    ) noexcept -> Iterator {

        auto end = this->end();
        auto lastFound = end;
        for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
            if ( __hidden :: __impl :: __initializerListContains ( elements, * iterator ) ) {
                lastFound = iterator;
            }
        }

        return lastFound;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findAllOf (
            InitializerList                     const & elements,
            __CollectionType < Iterator >               & storeIn
    ) noexcept -> __CollectionType < Iterator > & {

        for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
            if ( __hidden :: __impl :: __initializerListContains ( elements, * iterator ) ) {
                storeIn.add ( iterator );
            }
        }

        return storeIn;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findAllOf (
            InitializerList                     const & elements
    ) noexcept -> __CollectionType < Iterator > {

        Collection < Iterator > iterators;
        return this->findAllOf ( elements, iterators );
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findNotOf (
            Size                                        maxCount,
            InitializerList                     const & elements,
            __CollectionType < Iterator >               & storeIn
    ) noexcept -> __CollectionType < Iterator > & {

        Size found = 0ULL;
        for ( auto iterator = this->begin(), end = this->end(); iterator != end && found < maxCount; ++ iterator ) {
            if ( ! __hidden :: __impl :: __initializerListContains ( elements, * iterator ) ) {
                ++ found;

                storeIn.add ( iterator );
            }
        }

        return storeIn;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findNotOf (
            Size                                        maxCount,
            InitializerList                     const & elements
    ) noexcept -> __CollectionType < Iterator > {

        __CollectionType < Iterator > iterators;
        return this-> findNotOf ( maxCount, elements, iterators );
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findFirstNotOf (
            InitializerList                     const & elements
    ) noexcept -> Iterator {

        auto end = this->end();
        for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
            if ( ! __hidden :: __impl :: __initializerListContains ( elements,  * iterator ) ) {
                return iterator;
            }
        }

        return end;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findLastNotOf (
            InitializerList                     const & elements
    ) noexcept -> Iterator {

        auto end = this->end();
        auto lastFound = end;
        for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
            if ( ! __hidden :: __impl :: __initializerListContains ( elements,  * iterator ) ) {
                lastFound = iterator;
            }
        }

        return lastFound;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findAllNotOf (
            InitializerList                     const & elements,
            __CollectionType < Iterator >               & storeIn
    ) noexcept -> __CollectionType < Iterator > & {

        for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
            if ( ! __hidden :: __impl :: __initializerListContains ( elements,  * iterator ) ) {
                storeIn.add ( iterator );
            }
        }

        return storeIn;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findAllNotOf (
            InitializerList                     const & elements
    ) noexcept -> __CollectionType < Iterator > {

        __CollectionType < Iterator > iterators;
        return this-> findAllNotOf ( elements, iterators );
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType, typename __Predicate > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: find (
            Size                                        maxCount,
            __Predicate                         const & predicate,
            __CollectionType < Iterator >             & storeIn
    ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> __CollectionType < Iterator > & {

        Size matchCount = 0U;
        for ( auto iterator = this->begin(), end = this->end(); iterator != end && matchCount < maxCount; ++ iterator ) {
            if ( predicate ( * iterator ) ) {
                ++ matchCount;
                storeIn.add ( iterator );
            }
        }

        return storeIn;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType, typename __Predicate > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: find (
            Size                                        maxCount,
            __Predicate                         const & predicate
    ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> __CollectionType < Iterator > {

        __CollectionType < Iterator > iterators;
        return this->find ( maxCount, predicate, iterators );
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findFirst (
            __Predicate const & predicate
    ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> Iterator {

        auto end = this->end();
        for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
            if ( predicate ( * iterator ) ) {
                return iterator;
            }
        }

        return end;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findLast (
            __Predicate const & predicate
    ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> Iterator {

        auto end = this->end();
        auto lastFound = end;
        for ( auto iterator = this->begin(); iterator != end; ++ iterator ) {
            if ( predicate ( * iterator ) ) {
                lastFound = iterator;
            }
        }

        return lastFound;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType, typename __Predicate > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findAll (
            __Predicate                           const & predicate,
            __CollectionType < Iterator >               & storeIn
    ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> __CollectionType < Iterator > & {

        for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
            if ( predicate ( * iterator ) ) {
                storeIn.add ( iterator );
            }
        }

        return storeIn;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType, typename __Predicate > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: findAll (
            __Predicate                           const & predicate
    ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> __CollectionType < Iterator > {

        __CollectionType < Iterator > iterators;
        return this->findAll ( predicate, iterators );
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < typename __Action > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: forEach (
            __Action const & action
    ) noexcept ( noexcept ( action ( meta :: referenceOf < ElementType > () ) ) ) -> void {

        for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
            action ( * iterator );
        }
    }

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: some (
            Size                count,
            __Predicate const & predicate
    ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

        Size trueCount = 0ULL;
        for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
            if ( predicate ( * iterator ) ) {
                ++ trueCount;
            }

            if ( trueCount > count ) {
                return false;
            }
        }

        return trueCount == count;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: atLeast (
            Size                count,
            __Predicate const & predicate
    ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

        Size trueCount = 0ULL;
        for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
            if ( predicate ( * iterator ) ) {
                ++ trueCount;
            }

            if ( trueCount >= count ) {
                return true;
            }
        }

        return false;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: atMost (
            Size                count,
            __Predicate const & predicate
    ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

        Size trueCount = 0ULL;
        for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
            if ( predicate ( * iterator ) ) {
                ++ trueCount;
            }

            if ( trueCount > count ) {
                return false;
            }
        }

        return true;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto MutableCollection < __ElementType > :: moreThan (
            Size                count,
            __Predicate const & predicate
    ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

        return this->atLeast ( count + 1, predicate );
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto MutableCollection < __ElementType > :: fewerThan (
            Size                count,
            __Predicate const & predicate
    ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

        return this->atMost ( count - 1, predicate );
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: count (
            __Predicate const & predicate
    ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> Size {

        Size trueCount = 0U;
        for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
            if ( predicate ( * iterator ) ) {
                ++ trueCount;
            }
        }

        return trueCount;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: any (
            __Predicate const & predicate
    ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

        for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
            if ( predicate ( * iterator ) ) {
                return true;
            }
        }

        return false;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: all (
            __Predicate const & predicate
    ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

        for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
            if ( ! predicate ( * iterator ) ) {
                return false;
            }
        }

        return true;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    template < typename __Predicate > // NOLINT(bugprone-reserved-identifier)
    auto MutableCollection < __ElementType > :: none (
            __Predicate const & predicate
    ) noexcept ( noexcept ( predicate ( meta :: referenceOf < ElementType > () ) ) ) -> bool {

        for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
            if ( predicate ( * iterator ) ) {
                return false;
            }
        }

        return true;
    }

}

#endif // __CDS_MUTABLE_COLLECTION_IMPL_HPP__
