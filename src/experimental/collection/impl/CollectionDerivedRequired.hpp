//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_DERIVED_REQUIRED_HPP__
#define __CDS_COLLECTION_DERIVED_REQUIRED_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        template < typename Predicate >
        auto Collection < T > :: remove ( Predicate const & predicate, Size count ) noexcept -> Size {

            Iterator * pIteratorBuffer = Memory :: instance().createArray < Iterator > ( count );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iteratorCount < count && iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }
            }

            auto removedCount = this->remove ( & pIteratorBuffer[0], iteratorCount );
            Memory :: instance().destroyArray ( pIteratorBuffer );

            return removedCount;
        }

        template < typename T >
        template < typename Predicate >
        auto Collection < T > :: removeFirst ( Predicate const & predicate ) noexcept -> bool {
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    return this->remove ( iterator );
                }
            }

            return false;
        }

        template < typename T >
        template < typename Predicate >
        auto Collection < T > :: removeLast ( Predicate const & predicate ) noexcept -> bool {
            Iterator toRemove;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    toRemove = iterator;
                }
            }

            return toRemove.valid() && this->remove ( toRemove );
        }

        template < typename T >
        template < typename Predicate >
        auto Collection < T > :: removeAll ( Predicate const & predicate ) noexcept -> Size {

            Iterator * pIteratorBuffer = Memory :: instance().createArray < Iterator > ( this->size() );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( predicate ( * iterator ) ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }
            }

            auto removedCount = this->remove ( & pIteratorBuffer[0], iteratorCount );
            Memory :: instance().destroyArray ( pIteratorBuffer );

            return removedCount;
        }

        template < typename T >
        auto Collection < T > :: removeOf ( Collection < T > const & collection, Size count ) noexcept -> Size {

            if ( this == & collection ) {
                if ( this->size() <= count ) {
                    this->clear();
                    return true;
                }

                Iterator * pIteratorBuffer = Memory :: instance().createArray < Iterator > ( count );
                Size iteratorCount = 0U;

                for ( auto iterator = this->begin(), end = this->end(); iteratorCount < count && iterator != end; ++ iterator ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }

                auto removedCount = this->remove ( & pIteratorBuffer[0], iteratorCount );
                Memory :: instance().destroyArray ( pIteratorBuffer );

                return removedCount;
            }

            Iterator * pIteratorBuffer = Memory :: instance().createArray < Iterator > ( count );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( collection.contains ( * iterator ) ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }

                if ( iteratorCount >= count ) {
                    break;
                }
            }

            auto removedCount = this->remove ( & pIteratorBuffer[0], iteratorCount );
            Memory :: instance().destroyArray ( pIteratorBuffer );

            return removedCount;
        }

        template < typename T >
        auto Collection < T > :: removeFirstOf ( Collection < T > const & collection ) noexcept -> bool {
            if ( this == & collection ) {
                return this->remove ( this->begin() );
            }

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( collection.contains ( * iterator ) ) {
                    return this->remove ( iterator );
                }
            }

            return false;
        }

        template < typename T >
        auto Collection < T > :: removeLastOf ( Collection < T > const & collection ) noexcept -> bool {
            Iterator toRemove;

            if ( this == & collection ) {
                for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                    toRemove = iterator;
                }

                return this->remove ( toRemove );
            }

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( collection.contains ( * iterator ) ) {
                    toRemove = iterator;
                }
            }

            return toRemove.valid() && this->remove ( toRemove );
        }

        template < typename T >
        auto Collection < T > :: removeAllOf ( Collection < T > const & collection ) noexcept -> Size {
            if ( this == & collection ) {
                auto removedCount = this->size();
                this->clear();
                return removedCount;
            }

            Iterator * pIteratorBuffer = Memory :: instance().createArray < Iterator > ( this->size() );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( collection.contains ( * iterator ) ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }
            }

            auto removedCount = this->remove ( & pIteratorBuffer[0], iteratorCount );
            Memory :: instance().destroyArray ( pIteratorBuffer );

            return removedCount;
        }

        template < typename T >
        auto Collection < T > :: removeNotOf ( Collection < T > const & collection, Size count ) noexcept -> Size {

            if ( this == & collection ) {
                return 0ULL;
            }

            Iterator * pIteratorBuffer = Memory :: instance().createArray < Iterator > ( count );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! collection.contains ( * iterator ) ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }

                if ( iteratorCount >= count ) {
                    break;
                }
            }

            auto removedCount = this->remove ( & pIteratorBuffer[0], iteratorCount );
            Memory :: instance().destroyArray ( pIteratorBuffer );

            return removedCount;
        }

        template < typename T >
        auto Collection < T > :: removeFirstNotOf ( Collection < T > const & collection ) noexcept -> bool {
            if ( this == & collection ) {
                return false;
            }

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! collection.contains ( * iterator ) ) {
                    return this->remove ( iterator );
                }
            }

            return false;
        }

        template < typename T >
        auto Collection < T > :: removeLastNotOf ( Collection < T > const & collection ) noexcept -> bool {
            if ( this == & collection ) {
                return false;
            }

            Iterator toRemove;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! collection.contains ( * iterator ) ) {
                    toRemove = iterator;
                }
            }

            return toRemove.valid() && this->remove ( toRemove );
        }

        template < typename T >
        auto Collection < T > :: removeAllNotOf ( Collection < T > const & collection ) noexcept -> Size {
            if ( this == & collection ) {
                return 0ULL;
            }

            Iterator * pIteratorBuffer = Memory :: instance().createArray < Iterator > ( this->size() );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! collection.contains ( * iterator ) ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }
            }

            auto removedCount = this->remove ( & pIteratorBuffer[0], iteratorCount );
            Memory :: instance().destroyArray ( pIteratorBuffer );

            return removedCount;
        }

        namespace hidden {
            namespace impl {

                template < typename T >
                __CDS_OptimalInline static auto initializerListContains ( std :: initializer_list < T > const & list, T const & element ) noexcept -> bool {
                    for ( auto const & e : list ) {
                        if ( Type < T > :: compare ( e, element ) ) {
                            return true;
                        }
                    }

                    return false;
                }

            }
        }

        template < typename T >
        auto Collection < T > :: removeOf ( InitializerList const & list, Size count ) noexcept -> Size {

            Iterator * pIteratorBuffer = Memory :: instance().createArray < Iterator > ( count );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( hidden :: impl :: initializerListContains ( list, * iterator ) ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }

                if ( iteratorCount >= count ) {
                    break;
                }
            }

            auto removedCount = this->remove ( & pIteratorBuffer[0], iteratorCount );
            Memory :: instance().destroyArray ( pIteratorBuffer );

            return removedCount;
        }

        template < typename T >
        auto Collection < T > :: removeFirstOf ( InitializerList const & list ) noexcept -> bool {
            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( hidden :: impl :: initializerListContains ( list, * iterator ) ) {
                    return this->remove ( iterator );
                }
            }

            return false;
        }

        template < typename T >
        auto Collection < T > :: removeLastOf ( InitializerList const & list ) noexcept -> bool {
            Iterator toRemove;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( hidden :: impl :: initializerListContains ( list, * iterator ) ) {
                    toRemove = iterator;
                }
            }

            return toRemove.valid() && this->remove ( toRemove );
        }

        template < typename T >
        auto Collection < T > :: removeAllOf ( InitializerList const & list ) noexcept -> Size {

            Iterator * pIteratorBuffer = Memory :: instance().createArray < Iterator > ( this->size() );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( hidden :: impl :: initializerListContains ( list, * iterator ) ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }
            }

            auto removedCount = this->remove ( & pIteratorBuffer[0], iteratorCount );
            Memory :: instance().destroyArray ( pIteratorBuffer );

            return removedCount;
        }

        template < typename T >
        auto Collection < T > :: removeNotOf ( InitializerList const & list, Size count ) noexcept -> Size {

            Iterator * pIteratorBuffer = Memory :: instance().createArray < Iterator > ( count );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! hidden :: impl :: initializerListContains ( list, * iterator ) ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }

                if ( iteratorCount >= count ) {
                    break;
                }
            }

            auto removedCount = this->remove ( & pIteratorBuffer[0], iteratorCount );
            Memory :: instance().destroyArray ( pIteratorBuffer );

            return removedCount;
        }

        template < typename T >
        auto Collection < T > :: removeFirstNotOf ( InitializerList const & list ) noexcept -> bool {

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! hidden :: impl :: initializerListContains ( list, * iterator ) ) {
                    return this->remove ( iterator );
                }
            }

            return false;
        }

        template < typename T >
        auto Collection < T > :: removeLastNotOf ( InitializerList const & list ) noexcept -> bool {
            Iterator toRemove;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! hidden :: impl :: initializerListContains ( list, * iterator ) ) {
                    toRemove = iterator;
                }
            }

            return toRemove.valid() && this->remove ( toRemove );
        }

        template < typename T >
        auto Collection < T > :: removeAllNotOf ( InitializerList const & list ) noexcept -> Size {
            Iterator * pIteratorBuffer = Memory :: instance().createArray < Iterator > ( this->size() );
            Size iteratorCount = 0U;

            for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
                if ( ! hidden :: impl :: initializerListContains ( list, * iterator ) ) {
                    pIteratorBuffer [ iteratorCount ++ ] = iterator;
                }
            }

            auto removedCount = this->remove ( & pIteratorBuffer[0], iteratorCount );
            Memory :: instance().destroyArray ( pIteratorBuffer );

            return removedCount;
        }

    }
}

#endif //__CDS_COLLECTION_DERIVED_REQUIRED_HPP__
