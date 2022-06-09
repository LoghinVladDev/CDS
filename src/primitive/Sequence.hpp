//
// Created by loghin on 02.06.2021.
//

#ifndef CDS_SEQUENCE_HPP
#define CDS_SEQUENCE_HPP

#include <CDS/Object>

#include <CDS/smartPointers/SharedPointer>
#include <CDS/Boolean>
#include <CDS/Optional>
#include <CDS/Pair>
#include <CDS/Map>
#include <CDS/Array>
#include <CDS/LinkedList>
#include <CDS/Set>
#include <CDS/Types>
#include <CDS/Double>
#include <CDS/Function>
#include <CDS/Memory>

#include "SequencePrivate.hpp"

namespace cds {

    template < typename C >
    class Sequence : public Object {
    public:
        using CollectionType = C;

    private:

        using ClassName                 = meta :: RemoveReference < C >;
        using IterableValue             = decltype ( * ( meta :: valueOf < typename ClassName::Iterator > () ) );

    public:
        using ElementType               = meta :: RemoveReference < IterableValue >;

    private:
        using StoredPredicate           = Function < bool (IterableValue) >;
        using StoredMapper              = Function < meta :: RemoveReference < IterableValue > (IterableValue) >;

        using StoredIndexedPredicate    = Function < bool (Index, IterableValue) >;
        using StoredIndexedMapper       = Function < meta :: RemoveReference < IterableValue > (Index, IterableValue) >;

        friend class Iterator;
        friend class ConstIterator;

        /**
         * can be:
         *      Unique < Foreign > representing lack of ownership, a view created over a structure outside its scope
         *      Unique < Unique > representing ownership, a structure created by the view to iterate upon
         */
        UniquePointer < SmartPointer < C > > pCollection { nullptr };
        uint16                              chainCount  { 0 }; // used to determine order of operations

        LinkedList < Pair < SharedPointer < StoredPredicate >,  Index > >       storedPredicates;
        LinkedList < Pair < SharedPointer < StoredMapper >,     Index > >       storedMappers;

        LinkedList < Pair < SharedPointer < StoredIndexedPredicate >, Index > > storedIndexedPredicates;
        LinkedList < Pair < SharedPointer < StoredIndexedMapper >,    Index > > storedIndexedMappers;

    public:
        class Iterator : public Object {
        public:
            using CollectionIterator = meta :: Conditional <
                    meta :: isConst < CollectionType > (),
                    typename CollectionType :: ConstIterator,
                    typename CollectionType :: Iterator
            >;

            using CollectionElementType = typename Sequence::ElementType;

        private:
            ForeignPointer < Sequence > pSeq;
            CollectionIterator it;
            Index index {0};

            UniquePointer < CollectionElementType > precomputed;

            auto skipFiltered () noexcept -> void;

        public:

    #if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_17

            __CDS_NoDiscard auto toString () const noexcept -> String override;
            __CDS_NoDiscard auto hash () const noexcept -> Index override;

    #else

            template < typename U = C, meta :: EnableIf < meta :: isPrintable < decltype ( Sequence < U > :: Iterator :: it ) > () > = 0 >
            __CDS_NoDiscard auto toString () const noexcept -> String {
                std::stringstream oss;
                oss << "Sequence::Iterator { pSequence = " << this->pSeq.toString() << ", it = " << this->it << " }";
                return oss.str();
            }

            template < typename U = C, meta :: EnableIf < ! meta :: isPrintable < decltype ( Sequence < U > :: Iterator :: it ) > () > = 0 >
            __CDS_NoDiscard auto toString () const noexcept -> String {
                std::stringstream oss;
                oss << "Sequence::Iterator { pSequence = " << this->pSeq.toString() << ", value = " << * this->it << " }";
                return oss.str();
            }

            template < typename U = C, meta :: EnableIf < meta :: isObjectDerived < Sequence < U > :: Iterator :: it > () > = 0 >
            __CDS_NoDiscard auto hash () const noexcept -> Index {
                return this->it.hash();
            }

            template < typename U = C, meta :: EnableIf < ! meta :: isObjectDerived < Sequence < U > :: Iterator :: it > () && meta :: isObjectDerived < decltype ( * meta :: valueOf < decltype ( Sequence < U > :: Iterator :: it ) > () ) > () > = 0 >
            __CDS_NoDiscard auto hash () const noexcept -> Index {
                return (* this->it).hash();
            }

            template < typename U = C, meta :: EnableIf < ! meta :: isObjectDerived < Sequence < U > :: Iterator :: it > () && ! meta :: isObjectDerived < decltype ( * meta :: valueOf < decltype ( Sequence < U > :: Iterator :: it ) > () ) > () > = 0 >
            __CDS_NoDiscard auto hash () const noexcept -> Index {
                return 0;
            }

    #endif
            __CDS_NoDiscard auto equals (Object const &) const noexcept -> bool override;

            Iterator () noexcept = delete;
            __CDS_OptimalInline Iterator (Iterator const & otherIt) noexcept :
                    pSeq ( otherIt.pSeq ),
                    it (otherIt.it),
                    precomputed ( Memory::instance () .create < CollectionElementType > ( * otherIt.precomputed ) ),
                    index (otherIt.index){

            }

            __CDS_OptimalInline Iterator (Iterator &&) noexcept = default;
            Iterator (Sequence *, CollectionIterator const &) noexcept;
            ~Iterator () noexcept override = default;

            auto value () const noexcept -> CollectionElementType;
            auto next () noexcept -> Iterator &;
            auto equals ( Iterator const & ) const noexcept -> Boolean;

            auto operator == ( Iterator const & ) const noexcept -> bool;
            auto operator != ( Iterator const & ) const noexcept -> bool;
            auto operator ++ () noexcept -> Iterator &;
            auto operator ++ (int) noexcept -> Iterator;
            auto operator * () const noexcept -> CollectionElementType;
        };

        class ConstIterator : public Object {
        public:
            using CollectionIterator = typename CollectionType::ConstIterator;
            using CollectionElementType = typename Sequence::ElementType;

        private:
            ForeignPointer < Sequence const > pSeq;
            CollectionIterator it;
            Index index {0};

            UniquePointer < CollectionElementType > precomputed;

            auto skipFiltered () noexcept -> void;

        public:

    #if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_17

            __CDS_NoDiscard auto toString () const noexcept -> String override;
            __CDS_NoDiscard auto hash () const noexcept -> Index override;

    #else

            template < typename U = C, meta :: EnableIf < meta :: isPrintable < decltype ( Sequence < U > :: ConstIterator :: it ) > () > = 0 >
            __CDS_NoDiscard auto toString () const noexcept -> String {
                std::stringstream oss;
                oss << "Sequence::Iterator { pSequence = " << this->pSeq.toString() << ", it = " << this->it << " }";
                return oss.str();
            }

            template < typename U = C, meta :: EnableIf < ! meta :: isPrintable < decltype ( Sequence < U > :: ConstIterator :: it ) > () > = 0 >
            __CDS_NoDiscard auto toString () const noexcept -> String {
                std::stringstream oss;
                oss << "Sequence::Iterator { pSequence = " << this->pSeq.toString() << ", value = " << * this->it << " }";
                return oss.str();
            }

            template < typename U = C, meta :: EnableIf < meta :: isObjectDerived < Sequence < U > :: ConstIterator :: it > () > = 0 >
            __CDS_NoDiscard auto hash () const noexcept -> Index {
                return this->it.hash();
            }

            template < typename U = C, meta :: EnableIf < ! meta :: isObjectDerived < Sequence < U > :: ConstIterator :: it > () && meta :: isObjectDerived < decltype ( * meta :: valueOf < decltype ( Sequence < U > :: ConstIterator :: it ) > () ) > () > = 0 >
            __CDS_NoDiscard auto hash () const noexcept -> Index {
                return (* this->it).hash();
            }

            template < typename U = C, meta :: EnableIf < ! meta :: isObjectDerived < Sequence < U > :: ConstIterator :: it > () && ! meta :: isObjectDerived < decltype ( * meta :: valueOf < decltype ( Sequence < U > :: ConstIterator :: it ) > () ) > () > = 0 >
            __CDS_NoDiscard auto hash () const noexcept -> Index {
                return 0;
            }
    #endif

            __CDS_NoDiscard auto equals (Object const &) const noexcept -> bool override;

            ConstIterator () noexcept = delete;
            ConstIterator (ConstIterator const &) noexcept = default;
            ConstIterator (ConstIterator &&) noexcept = default;
            ConstIterator (Sequence const *, CollectionIterator const &) noexcept;
            ~ConstIterator () noexcept override = default;

            auto value () const noexcept -> CollectionElementType;
            auto next () noexcept -> ConstIterator &;
            auto equals ( ConstIterator const & ) const noexcept -> Boolean;

            auto operator == ( ConstIterator const & ) const noexcept -> bool;
            auto operator != ( ConstIterator const & ) const noexcept -> bool;
            auto operator ++ () noexcept -> ConstIterator &;
            auto operator ++ (int) noexcept -> ConstIterator;
            auto operator * () const noexcept -> CollectionElementType;
        };

    private:
        auto clear () noexcept -> void;

    public:
        __CDS_MaybeUnused Sequence () noexcept = delete;
        __CDS_MaybeUnused Sequence (Sequence const &) noexcept;
        __CDS_MaybeUnused Sequence (Sequence &&) noexcept;

        __CDS_MaybeUnused explicit Sequence ( C & ) noexcept;
        __CDS_MaybeUnused explicit Sequence ( C && ) noexcept;

        ~Sequence () noexcept override = default;

        auto operator = (Sequence const &) noexcept -> Sequence &;
        auto operator = (Sequence &&) noexcept -> Sequence &;

        __CDS_MaybeUnused auto begin () noexcept -> Iterator;
        __CDS_MaybeUnused auto end () noexcept -> Iterator;

        __CDS_MaybeUnused auto begin () const noexcept -> ConstIterator;
        __CDS_MaybeUnused auto end () const noexcept -> ConstIterator;
        __CDS_MaybeUnused auto cbegin () const noexcept -> ConstIterator;
        __CDS_MaybeUnused auto cend () const noexcept -> ConstIterator;

        __CDS_NoDiscard __CDS_MaybeUnused auto toString () const noexcept -> String override;
        __CDS_NoDiscard __CDS_MaybeUnused auto hash () const noexcept -> Index override;
        __CDS_NoDiscard __CDS_MaybeUnused auto equals (Object const &) const noexcept -> bool override;

        __CDS_MaybeUnused auto contains ( ElementType const & element ) const noexcept -> Boolean
        __CDS_Requires ( ForwardIterable < C > ) {

            for ( auto v : * this )
                if ( meta :: equals ( element, v ) )
                    return true;
            return false;
        }

        __CDS_MaybeUnused auto elementAt ( Index i ) const noexcept -> Optional < ElementType >
        __CDS_Requires ( ForwardIterable < C > ) {

            Index at = 0;
            for ( auto v : * this )
                if ( at == i )
                    return { v };
                else
                    at ++;

            return { };
        }

        __CDS_MaybeUnused auto elementAtOr ( Index i, ElementType const & replacement ) const noexcept -> ElementType
        __CDS_Requires ( ForwardIterable < C > ) {
            Index at = 0;
            for ( auto v : * this )
                if ( at == i )
                    return v;
                else
                    at ++;

            return replacement;
        }

        template < typename T = ElementType, meta :: EnableIf < meta :: isPointer < T > () > = 0 >
        __CDS_MaybeUnused auto elementAtOrNull ( Index i ) const noexcept -> ElementType
        __CDS_Requires ( ForwardIterable < C > ) {

            Index at = 0;
            for ( auto v : * this )
                if ( at == i )
                    return v;
                else
                    at ++;

            return nullptr;
        }


        __CDS_MaybeUnused auto indexOf ( ElementType const & element ) const noexcept -> Index
        __CDS_Requires ( ForwardIterable < C > ) {

            Index i = 0;
            for ( auto v : * this )
                if ( meta :: equals ( element, v ) )
                    return i;
                else
                    i++;

            return -1;
        }

        __CDS_MaybeUnused auto lastIndexOf ( ElementType const & element ) const noexcept -> Index
        __CDS_Requires ( ForwardIterable < C > ) {

            Index i = 0, last = -1;
            for ( auto v : * this ) {
                if ( meta :: equals ( element, v ) )
                    last = i;
                i++;
            }

            return last;
        }

        __CDS_MaybeUnused auto indicesOf ( ElementType const & element ) const noexcept -> LinkedList < Index >
        __CDS_Requires ( ForwardIterable < C > ) {

            LinkedList < Index > result;
            Index i = 0;
            for ( auto v : * this ) {
                if ( meta :: equals ( element, v ) )
                    result.append(i);
                i++;
            }

            return result;
        }


        template < typename Action >
        __CDS_MaybeUnused auto apply ( Action const & action ) && noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && ActionOver < Action, Sequence > ) {

            action(* this);
            LinkedList < ElementType > container;

            Index i = 0;
            for ( auto e : * this )
                container.append(e);

            return std::move(Sequence < LinkedList < ElementType > > (std::move(container)));
        }

        template < typename Action >
        __CDS_MaybeUnused auto also ( Action const & action ) && noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && EmptyAction < Action > ) {

            action();
            LinkedList < ElementType > container;

            for ( auto e : * this )
                container.append(e);

            return std::move(Sequence < LinkedList < ElementType > > (std::move(container)));
        }

        template < typename Action >
        __CDS_MaybeUnused auto apply ( Action const & action ) & noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && ActionOver < Action, Sequence > ) {

            Sequence copy(* this);
            action(copy);
            LinkedList < ElementType > container;

            for ( auto e : copy )
                container.append(e);

            return std::move(Sequence < LinkedList < ElementType > > (std::move(container)));
        }

        template < typename Action >
        __CDS_MaybeUnused auto also ( Action const & action ) & noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && EmptyAction < Action > ) {

            action();
            LinkedList < ElementType > container;

            for ( auto e : * this )
                container.append(e);

            return std::move(Sequence < LinkedList < ElementType > > (std::move(container)));
        }


        template < typename Predicate = Function < bool ( ElementType const & ) > >
        __CDS_MaybeUnused auto first (
                Predicate const & predicate = [](ElementType const &) noexcept -> bool { return true; }
        ) const noexcept -> Optional < ElementType >
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            for ( auto e : * this )
                if ( predicate ( e ) )
                    return { e };
            return { };
        }

        template < typename Predicate >
        __CDS_MaybeUnused __CDS_OptimalInline auto find ( Predicate const & predicate ) const noexcept -> Optional < ElementType >
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            return this->first(predicate);
        }

        template < typename Predicate = Function < bool ( ElementType const & ) > >
        __CDS_MaybeUnused auto firstOr (
                ElementType const & replacement,
                Predicate   const & predicate = [] ( ElementType const & ) noexcept -> bool { return true; }
        ) const noexcept -> ElementType
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            for ( auto v : * this )
                if ( predicate (v) )
                    return v;
            return replacement;
        }

        template < typename Predicate = Function < bool ( ElementType const & ) > >
        __CDS_MaybeUnused auto last (
                Predicate const & predicate = [] ( ElementType const & predicate ) noexcept -> bool { return true; }
        ) const noexcept -> Optional < ElementType >
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            ElementType v;
            Boolean found = false;
            for ( auto e : * this )
                if ( predicate(e) ) {
                    found = true;
                    v = e;
                }

            if ( found )
                return { v };
            return { };
        }

        template < typename Predicate >
        __CDS_MaybeUnused __CDS_OptimalInline auto findLast ( Predicate const & predicate ) const noexcept -> Optional < ElementType >
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            return this->last(predicate);
        }

        template < typename Predicate = Function < bool ( ElementType const & ) > >
        __CDS_MaybeUnused auto lastOr (
                ElementType const & replacement,
                Predicate   const & predicate = [](ElementType const &) noexcept -> bool { return true; }
        ) const noexcept -> ElementType
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            ElementType v;
            Boolean found = false;
            for ( auto e : * this )
                if ( predicate(e) ) {
                    found = true;
                    v = e;
                }

            if ( found )
                return v;
            return replacement;
        }


        __CDS_MaybeUnused __CDS_OptimalInline auto single () const noexcept -> Optional < ElementType >
        __CDS_Requires ( ForwardIterable < C > ) {

            if ( this->pCollection.valueAt().valueAt().size() != 1 )
                return { };
            return this->begin().value();
        }

        __CDS_MaybeUnused __CDS_OptimalInline auto singleOr ( ElementType const & replacement ) const noexcept -> ElementType
        __CDS_Requires ( ForwardIterable < C > ) {

            if ( this->pCollection.valueAt().valueAt().size() != 1 )
                return replacement;
            return this->begin().value();
        }

        template < typename Predicate >
        __CDS_MaybeUnused auto single ( Predicate const & predicate ) const noexcept -> Optional < ElementType >
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            ElementType v;
            Boolean found = false;
            for ( auto e : * this )
                if ( predicate ( e ) ) {
                    if (!found) {
                        found = true;
                        v = e;
                    } else {
                        return { };
                    }
                }

            if ( found ) return { v };
            return { };
        }

        template < typename Predicate >
        __CDS_MaybeUnused auto singleOr ( ElementType const & replacement, Predicate const & predicate ) const noexcept -> ElementType
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            ElementType v;
            Boolean found = false;
            for ( auto e : * this )
                if ( predicate ( e ) ) {
                    if (!found) {
                        found = true;
                        v = e;
                    } else {
                        return replacement;
                    }
                }

            if ( found ) return v;
            return replacement;
        }


        __CDS_MaybeUnused auto drop (Size count) && noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > ) {

            LinkedList < ElementType > remaining;

            Index i = 0;
            for ( auto e : * this ) {
                if ( i < count ) {
                    i++;
                    continue;
                }

                remaining.append(e);
            }

            return std::move(Sequence < LinkedList < ElementType > > (std::move(remaining)));
        }

        __CDS_MaybeUnused auto drop (Size count) & noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > ) {

            LinkedList < ElementType > remaining;

            Index i = 0;
            for ( auto e : * this ) {
                if ( i < count ) {
                    i++;
                    continue;
                }

                remaining.append(e);
            }

            return std::move(Sequence < LinkedList < ElementType > > (std::move(remaining)));
        }

        __CDS_MaybeUnused auto dropLast (Size count) && noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > ) {

            LinkedList < ElementType > remaining;
            auto currentSize = this->pCollection.valueAt().valueAt().size();

            for ( auto e : * this ) {
                if ( currentSize > count ) {
                    currentSize --;
                    remaining.append(e);
                }
            }

            return std::move(Sequence < LinkedList < ElementType > > (std::move(remaining)));
        }

        __CDS_MaybeUnused auto dropLast (Size count) & noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > ) {

            LinkedList < ElementType > remaining;
            auto currentSize = this->pCollection.valueAt().valueAt().size();

            for ( auto e : * this ) {
                if ( currentSize > count ) {
                    currentSize --;
                    remaining.append(e);
                }
            }

            return std::move(Sequence < LinkedList < ElementType > > (std::move(remaining)));
        }

        template < typename Predicate >
        __CDS_MaybeUnused auto dropWhile (
                Predicate const & p,
                Size count          = UINT64_MAX
        ) && noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            LinkedList < ElementType > remaining;

            Index i = 0;

            for ( auto e : * this ) {
                if ( i < count && p (e) ) {
                    i ++;
                    continue;
                }

                remaining.append(e);
            }

            return std::move(Sequence < LinkedList < ElementType > > (std::move(remaining)));
        }

        template < typename Predicate >
        __CDS_MaybeUnused auto dropWhile (
                Predicate const & p,
                Size count          = UINT64_MAX
        ) & noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            LinkedList < ElementType > remaining;

            Index i = 0;

            for ( auto e : * this ) {
                if ( i < count && p (e) ) {
                    i ++;
                    continue;
                }

                remaining.append(e);
            }

            return std::move(Sequence < LinkedList < ElementType > > (std::move(remaining)));
        }

        template < typename Predicate >
        __CDS_MaybeUnused auto dropLastWhile (
                Predicate const & p,
                Size count          = UINT64_MAX
        ) && noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            LinkedList < ElementType > all;
            LinkedList < ElementType > remaining;

            for ( auto e : * this )
                all.append(e);

            Index i = 0;

            for ( auto it = all.rbegin(); it != all.rend(); ++ it ) {
                if ( i < count && p (it.value()) ) {
                    i ++;
                    continue;
                }

                remaining.pushFront(it.value());
            }

            return std::move(Sequence < LinkedList < ElementType > > (std::move(remaining)));
        }

        template < typename Predicate >
        __CDS_MaybeUnused auto dropLastWhile (
                Predicate const & p,
                Size count          = UINT64_MAX
        ) & noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            LinkedList < ElementType > all;
            LinkedList < ElementType > remaining;

            for ( auto e : * this )
                all.append(e);

            Index i = 0;

            for ( auto it = all.rbegin(); it != all.rend(); ++ it ) {
                if ( i < count && p (* it) ) {
                    i ++;
                    continue;
                }

                remaining.pushFront(* it);
            }

            return std::move(Sequence < LinkedList < ElementType > > (std::move(remaining)));
        }

        __CDS_MaybeUnused auto take (Size count) && noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > ) {

            LinkedList < ElementType > remaining;

            Index i = 0;

            for ( auto e : * this ) {
                if ( i < count ) {
                    remaining.append(e);
                    i++;
                    continue;
                }
                break;
            }

            return std::move ( Sequence < LinkedList < ElementType > > (std::move(remaining)) );
        }

        __CDS_MaybeUnused auto take (Size count) & noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > ) {

            LinkedList < ElementType > remaining;

            Index i = 0;

            for ( auto e : * this ) {
                if ( i < count ) {
                    remaining.append(e);
                    i++;
                    continue;
                }
                break;
            }

            return std::move ( Sequence < LinkedList < ElementType > > (std::move(remaining)) );
        }

        __CDS_MaybeUnused auto takeLast (Size count) && noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > ) {

            Size current = this->pCollection.valueAt().valueAt().size();
            LinkedList < ElementType > remaining;

            Index i = 0;

            for ( auto e : * this ) {
                if ( count < current )
                    -- current;
                else
                    remaining.append(e);
            }

            return std::move ( Sequence < LinkedList < ElementType > > (std::move(remaining)) );
        }

        __CDS_MaybeUnused auto takeLast (Size count) & noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > ) {

            Size current = this->pCollection.valueAt().valueAt().size();
            LinkedList < ElementType > remaining;

            Index i = 0;

            for ( auto e : * this ) {
                if ( count < current )
                    -- current;
                else
                    remaining.append(e);
            }

            return std::move ( Sequence < LinkedList < ElementType > > (std::move(remaining)) );
        }

        template < typename Predicate >
        __CDS_MaybeUnused auto takeWhile (
                Predicate const & predicate,
                Size              count     = UINT64_MAX
        ) && noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            LinkedList < ElementType > remaining;
            Index i = 0;

            for ( auto e : * this ) {
                if ( i < count && predicate ( e ) ) {
                    remaining.append(e);
                    i++;
                    continue;
                }
                break;
            }

            return std::move ( Sequence < LinkedList < ElementType > > ( std::move ( remaining ) ) );
        }


        template < typename Predicate >
        __CDS_MaybeUnused auto takeWhile (
                Predicate const & predicate,
                Size              count     = UINT64_MAX
        ) & noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            LinkedList < ElementType > remaining;
            Index i = 0;

            for ( auto e : * this ) {
                if ( i < count && predicate ( e ) ) {
                    remaining.append(e);
                    i++;
                    continue;
                }
                break;
            }

            return std::move ( Sequence < LinkedList < ElementType > > ( std::move ( remaining ) ) );
        }

        template < typename Predicate >
        __CDS_MaybeUnused auto takeLastWhile (
                Predicate const & p,
                Size count          = UINT64_MAX
        ) && noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            LinkedList < ElementType > container;

            for ( auto e : * this )
                container.append(e);

            LinkedList < ElementType > remaining;

            Index i = 0;
            for ( auto it = container.rbegin(); it != container.rend(); ++ it )
                if ( i < count && p ( it.value() ) )
                    remaining.pushFront ( it.value() );

            return std::move(Sequence < LinkedList < ElementType > > (std::move(remaining)));
        }

        template < typename Predicate >
        __CDS_MaybeUnused auto takeLastWhile (
                Predicate const & p,
                Size count          = UINT64_MAX
        ) & noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            LinkedList < ElementType > container;

            for ( auto e : * this )
                container.append(e);

            LinkedList < ElementType > remaining;

            Index i = 0;
            for ( auto it = container.rbegin(); it != container.rend(); ++ it )
                if ( i < count && p ( * it ) )
                    remaining.pushFront ( * it );

            return std::move(Sequence < LinkedList < ElementType > > (std::move(remaining)));
        }


        template < typename Predicate >
        __CDS_MaybeUnused __CDS_OptimalInline auto filter ( Predicate const & predicate ) && noexcept -> Sequence
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            this->storedPredicates.append({ { Memory :: instance().create < StoredPredicate > (predicate)}, this->chainCount });
            return std::move ( * this );
        }

        template < typename Predicate >
        __CDS_MaybeUnused auto filter ( Predicate const & predicate ) & noexcept -> Sequence
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            Sequence < C > copy (* this );
            copy.storedPredicates.append({ { Memory :: instance ().create < StoredPredicate > (predicate)}, this->chainCount });
            return std::move (copy);
        }

        template < typename IndexedPredicate >
        __CDS_MaybeUnused auto filterIndexed ( IndexedPredicate const & indexedPredicate ) && noexcept -> Sequence
        __CDS_Requires ( ForwardIterable < C > && IndexedPredicateOver < IndexedPredicate, ElementType > ) {

            this->storedIndexedPredicates.append({ { Memory :: instance().create < StoredIndexedPredicate > (indexedPredicate)}, this->chainCount });
            return std::move ( * this );
        }

        template < typename IndexedPredicate >
        __CDS_MaybeUnused auto filterIndexed ( IndexedPredicate const & indexedPredicate ) & noexcept -> Sequence
        __CDS_Requires ( ForwardIterable < C > && IndexedPredicateOver < IndexedPredicate, ElementType > ) {

            Sequence < C > copy (* this);
            copy.storedIndexedPredicates.append({ { Memory :: instance().create < StoredIndexedPredicate > (indexedPredicate)}, this->chainCount });
            return std::move ( copy );
        }

        template < typename Predicate >
        __CDS_MaybeUnused auto filterTo (
                Collection < ElementType >        & collection,
                Predicate                   const & predicate
        ) const noexcept -> Collection < ElementType > &
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            for ( auto e : * this )
                if ( predicate(e) )
                    collection.add(e);

            return collection;
        }

        template < typename IndexedPredicate >
        __CDS_MaybeUnused auto filterIndexedTo (
                Collection < ElementType >        & collection,
                IndexedPredicate            const & predicate
        ) const noexcept -> Collection < ElementType > &
        __CDS_Requires ( ForwardIterable < C > && IndexedPredicateOver < IndexedPredicate, ElementType > ) {

            Index i = 0;
            for ( auto e : * this )
                if ( predicate(i++, e) )
                    collection.add(e);

            return collection;
        }

        template < typename NewType, typename OT = ElementType, typename NT = NewType, meta :: EnableIf < meta :: isBasicPointer < OT > () > = 0 >
        __CDS_MaybeUnused auto filterIsDerived () && noexcept -> Sequence < LinkedList < NewType > >
        __CDS_Requires(
                ForwardIterable < C > &&
                Pointer < ElementType > &&
                Pointer < NewType > &&
                DerivedFrom < meta :: RemovePointer < NewType >, meta :: RemovePointer < ElementType > >
        ) {

            LinkedList < NewType > container;
            for ( auto e : * this ) {
                auto p = dynamic_cast < NewType > (e);
                if ( p != nullptr )
                    container.add(p);
            }

            return std::move ( Sequence < LinkedList < NewType > > ( std::move ( container ) ) );
        }

        template < typename NewType, typename OT = ElementType, typename NT = NewType, meta :: EnableIf < meta :: isBasicPointer < OT > () > = 0 >
        __CDS_MaybeUnused auto filterIsDerived () & noexcept -> Sequence < LinkedList < NewType > >
        __CDS_Requires(
                ForwardIterable < C > &&
                Pointer < ElementType > &&
                Pointer < NewType > &&
                DerivedFrom < meta :: RemovePointer < NewType >, meta :: RemovePointer < ElementType > >
        ) {

            LinkedList < NewType > container;
            for ( auto e : * this ) {
                auto p = dynamic_cast < NewType > (e);
                if ( p != nullptr )
                    container.add(p);
            }

            return std::move ( Sequence < LinkedList < NewType > > ( std::move ( container ) ) );
        }

        template < typename NewType, typename OT = ElementType, typename NT = NewType, typename BaseType = meta :: RemovePointer < meta :: RemoveReference < NT > >, meta :: EnableIf < meta :: isSmartPointer < OT > () > = 0 >
        __CDS_MaybeUnused auto filterIsDerived () && noexcept -> Sequence < LinkedList < UniquePointer < BaseType > > >
        __CDS_Requires(
                ForwardIterable < C > &&
                Pointer < OT > &&
                Pointer < NT > &&
                DerivedFrom < meta :: RemovePointer < NewType >, meta :: RemovePointer < typename OT :: Pointer > >
        ) {

            LinkedList < UniquePointer < BaseType > > container;
            for ( auto e : * this ) {
                auto p = dynamic_cast < NT > (e.release());
                if ( p != nullptr )
                    container.add( UniquePointer < BaseType > ( p ) );
            }

            return std::move ( Sequence < LinkedList < ForeignPointer < BaseType > > > ( std::move ( container ) ) );
        }

        template <
                typename NewType,
                typename OT = ElementType,
                typename NT = NewType,
                typename BaseType = meta :: RemovePointer < meta :: RemoveReference < NT > >,
                typename AsUniquePointer = UniquePointer < BaseType >,
                typename AsForeignPointer = ForeignPointer < BaseType >,
                meta :: EnableIf < meta :: isSmartPointer < OT > () > = 0
        > __CDS_MaybeUnused auto filterIsDerived () & noexcept -> Sequence < LinkedList < AsForeignPointer > >
        __CDS_Requires(
                ForwardIterable < C > &&
                Pointer < OT > &&
                Pointer < NT > &&
                DerivedFrom < meta :: RemovePointer < NewType >, meta :: RemovePointer < typename OT :: Pointer > >
        ) {

            LinkedList < AsForeignPointer > container;
            for ( auto e : * this ) {
                auto p = dynamic_cast < NT > (e.get());
                if ( p != nullptr )
                    container.add( AsForeignPointer ( p ) );
            }

            return std::move ( Sequence < LinkedList < AsForeignPointer > > ( std::move ( container ) ) );
        }

        template < typename NewType, typename CT = NewType, typename OT = ElementType, meta :: EnableIf < meta :: isBasicPointer < OT > () > = 0 >
        __CDS_MaybeUnused auto filterIsDerivedTo (
                Collection < CT > & collection
        ) const noexcept -> Collection < CT > &
        __CDS_Requires (
                ForwardIterable < C > &&
                Pointer < ElementType > &&
                Pointer < NewType > &&
                DerivedFrom < meta :: RemovePointer < NewType >, meta :: RemovePointer < ElementType > >
        ) {

            for ( auto e : * this ) {
                auto p = dynamic_cast < NewType > (e);
                if ( p != nullptr )
                    collection.add(p);
            }

            return collection;
        }

        template < typename NewType, typename CT, typename OT = ElementType, meta :: EnableIf < meta :: isSmartPointer < OT > () > = 0 >
        __CDS_MaybeUnused auto filterIsDerivedTo (
                Collection < CT > & collection
        ) const noexcept -> Collection < CT > &
        __CDS_Requires (
                ForwardIterable < C > &&
                Pointer < ElementType > &&
                Pointer < NewType > &&
                DerivedFrom < meta :: RemovePointer < NewType >, meta :: RemovePointer < typename OT :: Pointer > >
        ) {

            for ( auto e : * this ) {
                auto p = dynamic_cast < NewType > (e.get());
                if ( p != nullptr )
                    collection.add(CT(p));
            }

            return collection;
        }

        template < typename T = ElementType, meta :: EnableIf < meta :: isBasicPointer < T > () > = 0 >
        __CDS_MaybeUnused auto filterNotNull () & noexcept -> Sequence < LinkedList < T > >
        __CDS_Requires( ForwardIterable < C > && Pointer < T > ) {

            LinkedList < T > container;
            for ( auto e : * this )
                if ( e != nullptr )
                    container.add( e );

            return std::move ( Sequence < LinkedList < T > > ( std::move ( container ) ) );
        }

        template < typename T = ElementType, meta :: EnableIf < meta :: isBasicPointer < T > () > = 0 >
        __CDS_MaybeUnused auto filterNotNull () && noexcept -> Sequence < LinkedList < T > >
        __CDS_Requires( ForwardIterable < C > && Pointer < T > ) {

            LinkedList < T > container;
            for ( auto e : * this )
                if ( e != nullptr )
                    container.add( e );

            return std::move ( Sequence < LinkedList < T > > ( std::move ( container ) ) );
        }

        template < typename T = ElementType, meta :: EnableIf < meta :: isSmartPointer < T > () > = 0 >
        __CDS_MaybeUnused auto filterNotNull () & noexcept -> Sequence < LinkedList < T > >
        __CDS_Requires( ForwardIterable < C > && Pointer < T > ) {

            LinkedList < T > container;
            for ( auto e : * this )
                if ( ! e.isNull() )
                    container.add( e );

            return std::move ( Sequence < LinkedList < T > > ( std::move ( container ) ) );
        }

        template < typename T = ElementType, meta :: EnableIf < meta :: isSmartPointer < T > () > = 0 >
        __CDS_MaybeUnused auto filterNotNull () && noexcept -> Sequence < LinkedList < T > >
        __CDS_Requires( ForwardIterable < C > && Pointer < T > ) {

            LinkedList < T > container;
            for ( auto e : * this )
                if ( ! e.isNull() )
                    container.add( e );

            return std::move ( Sequence < LinkedList < T > > ( std::move ( container ) ) );
        }

        template < typename T = ElementType, meta :: EnableIf < meta :: isBasicPointer < T > () > = 0 >
        __CDS_MaybeUnused auto filterNotNullTo (Collection < T > & collection) const noexcept -> Collection < T > &
        __CDS_Requires( ForwardIterable < C > && Pointer < T > ) {

            for ( auto e : * this )
                if ( e != nullptr )
                    collection.add(e);

            return collection;
        }

        template < typename T = ElementType, meta :: EnableIf < meta :: isSmartPointer < T > () > = 0 >
        __CDS_MaybeUnused auto filterNotNullTo (Collection < T > & collection) const noexcept -> Collection < T > &
        __CDS_Requires( ForwardIterable < C > && Pointer < T > ) {

            for ( auto e : * this )
                if ( ! e.isNull() )
                    collection.add(T(e.get()));

            return collection;
        }

        template < typename Predicate >
        __CDS_MaybeUnused __CDS_OptimalInline auto filterNot ( Predicate const & predicate ) && noexcept -> Sequence
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            return this->filter( [& predicate] (ElementType e) noexcept -> bool { return ! predicate(e); } );
        }

        template < typename Predicate >
        __CDS_MaybeUnused __CDS_OptimalInline auto filterNot ( Predicate const & predicate ) & noexcept -> Sequence
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            return this->filter( [& predicate] (ElementType e) noexcept -> bool { return ! predicate(e); } );
        }

        template < typename IndexedPredicate >
        __CDS_MaybeUnused __CDS_OptimalInline auto filterNotIndexed ( IndexedPredicate const & indexedPredicate ) && noexcept -> Sequence
        __CDS_Requires ( ForwardIterable < C > && IndexedPredicateOver < IndexedPredicate, ElementType > ) {

            return this->filterIndexed( [& indexedPredicate] (Index index, ElementType e) noexcept -> bool {
                return ! indexedPredicate ( index, e );
            });
        }

        template < typename IndexedPredicate >
        __CDS_MaybeUnused __CDS_OptimalInline auto filterNotIndexed ( IndexedPredicate const & indexedPredicate ) & noexcept -> Sequence
        __CDS_Requires ( ForwardIterable < C > && IndexedPredicateOver < IndexedPredicate, ElementType > ) {

            return this->filterIndexed( [& indexedPredicate] (Index index, ElementType e) noexcept -> bool {
                return ! indexedPredicate ( index, e );
            });
        }

        template < typename Predicate >
        __CDS_MaybeUnused auto filterNotTo (
                Collection < ElementType >        & collection,
                Predicate                   const & predicate
        ) const noexcept -> Collection < ElementType > &
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            for ( auto e : * this )
                if ( ! predicate ( e ) )
                    collection.add( e );

            return collection;
        }

        template < typename IndexedPredicate >
        __CDS_MaybeUnused auto filterNotIndexedTo (
                Collection < ElementType >        & collection,
                IndexedPredicate            const & indexedPredicate
        ) const noexcept -> Collection < ElementType > &
        __CDS_Requires ( ForwardIterable < C > && IndexedPredicateOver < IndexedPredicate, ElementType > ) {
            Index i = 0;
            for ( auto e : * this )
                if ( ! indexedPredicate ( i++, e ) )
                    collection.add ( e );

            return collection;
        }


        template < typename Predicate >
        __CDS_MaybeUnused auto indexOfFirst ( Predicate const & predicate ) const noexcept -> Index
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            Index i = 0;
            for ( auto e : * this ) {
                if ( predicate (e) )
                    return i;
                i++;
            }

            return -1;
        }

        template < typename Predicate >
        __CDS_MaybeUnused auto indexOfLast ( Predicate const & predicate ) const noexcept -> Index
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            Index i = 0;
            Index l = -1;
            for ( auto e : * this ) {
                if ( predicate (e) )
                    l = i;
                i++;
            }

            return l;
        }

        template < typename Predicate >
        __CDS_MaybeUnused auto indicesOfAll ( Predicate const & predicate ) const noexcept -> LinkedList < Index >
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            Index i = 0;
            LinkedList < Index > indices;
            for ( auto e : * this ) {
                if ( predicate( e ) )
                    indices.add ( i );
                i++;
            }

            return indices;
        }

        template < typename Predicate = Function < bool (ElementType const &) > >
        __CDS_MaybeUnused auto any (
                Predicate const & predicate = []( ElementType const & ) noexcept -> bool { return true; }
        ) const noexcept -> Boolean
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            for ( auto e : * this )
                if ( predicate ( e ) )
                    return true;
            return false;
        }

        template < typename Predicate >
        __CDS_MaybeUnused auto all ( Predicate const & predicate ) const noexcept -> Boolean
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            for ( auto e : * this )
                if ( ! predicate ( e ) )
                    return false;

            return true;
        }

        template < typename Predicate = Function < bool ( ElementType const & ) > >
        __CDS_MaybeUnused auto count (
                Predicate const & predicate = [](ElementType const &) noexcept -> bool { return true; }
        ) const noexcept -> Int
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            Int count = 0;
            for ( auto e : * this )
                if ( predicate ( e ) )
                    count ++;

            return count;
        }

        template < typename Predicate = Function < bool ( ElementType const & ) > >
        __CDS_MaybeUnused auto none (
                Predicate const & predicate = [](ElementType const &) noexcept -> bool { return true; }
        ) const noexcept -> Boolean
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            for ( auto e : * this )
                if ( predicate ( e ) )
                    return false;
            return true;
        }

        template < typename Predicate = Function < bool ( ElementType const & ) > >
        __CDS_MaybeUnused auto one (
                Predicate const & predicate = [](ElementType const &) noexcept -> bool { return true; }
        ) const noexcept -> Boolean
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            Boolean found = false;

            for ( auto e : * this )
                if ( predicate ( e ) ) {
                    if (!found)
                        found = true;
                    else
                        return false;
                }

            return found;
        }

        template < typename Transformer, meta :: EnableIf < meta :: isPair < meta :: ReturnOf < Transformer > > () > = 0 >
        __CDS_MaybeUnused auto associate (
                Transformer const & transformer
        ) && noexcept -> Sequence < LinkedList < meta :: ReturnOf < Transformer > > >
        __CDS_Requires (
                ForwardIterable < C > &&
                PairType < meta :: ReturnOf < Transformer > > &&
                TransformerOver < Transformer, ElementType >
        ) {

            LinkedList < meta :: ReturnOf < Transformer > > container;
            for ( auto e : * this )
                container.add ( transformer ( e ) );

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        template < typename Transformer, meta :: EnableIf < meta :: isPair < meta :: ReturnOf < Transformer > > () > = 0 >
        __CDS_MaybeUnused auto associate (
                Transformer const & transformer
        ) & noexcept -> Sequence < LinkedList < meta :: ReturnOf < Transformer > > >
        __CDS_Requires (
                ForwardIterable < C > &&
                PairType < meta :: ReturnOf < Transformer > > &&
                TransformerOver < Transformer, ElementType >
        ) {

            LinkedList < meta :: ReturnOf < Transformer > > container;
            for ( auto e : * this )
                container.add ( transformer ( e ) );

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        template < typename KeyGenerator >
        __CDS_MaybeUnused auto associateBy (
                KeyGenerator const & keyGenerator
        ) && noexcept -> Sequence < LinkedList < Pair < meta :: ReturnOf < KeyGenerator >, ElementType > > >
        __CDS_Requires (
                ForwardIterable < C > &&
                FunctionOver < KeyGenerator, meta :: ReturnOf < KeyGenerator >, ElementType >
        ) {

            LinkedList < Pair < meta :: ReturnOf < KeyGenerator >, ElementType > > container;
            for ( auto e : * this )
                container.add ( { keyGenerator ( e ), e } );

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        template < typename KeyGenerator >
        __CDS_MaybeUnused auto associateBy (
                KeyGenerator const & keyGenerator
        ) & noexcept -> Sequence < LinkedList < Pair < meta :: ReturnOf < KeyGenerator >, ElementType > > >
        __CDS_Requires (
                ForwardIterable < C > &&
                FunctionOver < KeyGenerator, meta :: ReturnOf < KeyGenerator >, ElementType >
        ) {

            LinkedList < Pair < meta :: ReturnOf < KeyGenerator >, ElementType > > container;
            for ( auto e : * this )
                container.add ( { keyGenerator ( e ), e } );

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        template < typename KeyGenerator, typename ValueMapper >
        __CDS_MaybeUnused auto associateBy (
                KeyGenerator    const & keyGenerator,
                ValueMapper     const & valueMapper
        ) && noexcept -> Sequence < LinkedList < Pair < meta :: ReturnOf < KeyGenerator >, meta :: ReturnOf < ValueMapper > > > >
        __CDS_Requires (
                ForwardIterable < C > &&
                FunctionOver < KeyGenerator, meta :: ReturnOf < KeyGenerator >, ElementType > &&
                FunctionOver < ValueMapper, meta :: ReturnOf < ValueMapper >, ElementType >
        ) {

            LinkedList < Pair < meta :: ReturnOf < KeyGenerator >, meta :: ReturnOf < ValueMapper > > > container;
            for ( auto e : * this )
                container.add( { keyGenerator ( e ), valueMapper ( e ) } );

            return std::move ( Sequence < decltype ( container ) > (std::move( container )) );
        }

        template < typename KeyGenerator, typename ValueMapper >
        __CDS_MaybeUnused auto associateBy (
                KeyGenerator    const & keyGenerator,
                ValueMapper     const & valueMapper
        ) & noexcept -> Sequence < LinkedList < Pair < meta :: ReturnOf < KeyGenerator >, meta :: ReturnOf < ValueMapper > > > >
        __CDS_Requires (
                ForwardIterable < C > &&
                FunctionOver < KeyGenerator, meta :: ReturnOf < KeyGenerator >, ElementType > &&
                FunctionOver < ValueMapper, meta :: ReturnOf < ValueMapper >, ElementType >
        ) {

            LinkedList < Pair < meta :: ReturnOf < KeyGenerator >, meta :: ReturnOf < ValueMapper > > > container;
            for ( auto e : * this )
                container.add( { keyGenerator ( e ), valueMapper ( e ) } );

            return std::move ( Sequence < decltype ( container ) > (std::move( container )) );
        }

        template < typename KeyGenerator >
        __CDS_MaybeUnused __CDS_OptimalInline auto associateByTo (
                Map < meta :: ReturnOf < KeyGenerator >, ElementType >        & m,
                KeyGenerator                                    const & keyGenerator
        ) const noexcept -> Map < meta :: ReturnOf < KeyGenerator >, ElementType > &
        __CDS_Requires (
                ForwardIterable < C > &&
                FunctionOver < KeyGenerator, meta :: ReturnOf < KeyGenerator >, ElementType >
        ) {

            for ( auto e : * this )
                m [ keyGenerator (e) ] = e;
            return m;
        }

        template < typename KeyGenerator, typename ValueMapper >
        __CDS_MaybeUnused __CDS_OptimalInline auto associateByTo (
                Map < meta :: ReturnOf < KeyGenerator >, meta :: ReturnOf < ValueMapper > >       & m,
                KeyGenerator                                                const & keyGenerator,
                ValueMapper                                                 const & valueMapper
        ) const noexcept -> Map < meta :: ReturnOf < KeyGenerator >, meta :: ReturnOf < ValueMapper > > &
        __CDS_Requires (
                ForwardIterable < C > &&
                FunctionOver < KeyGenerator, meta :: ReturnOf < KeyGenerator >, ElementType > &&
                FunctionOver < ValueMapper, meta :: ReturnOf < ValueMapper >, ElementType >
        ) {

            for ( auto e : * this )
                m [ keyGenerator (e) ] = valueMapper(e);
            return m;
        }

        template < typename Transformer, typename K, typename V >
        __CDS_MaybeUnused auto associateTo (
                Map < K, V >          & m,
                Transformer     const & t
        ) const noexcept -> Map < K, V > &
        __CDS_Requires (
                ForwardIterable < C > &&
                PairType < meta :: ReturnOf < Transformer > > &&
                TransformerOver < Transformer, ElementType >
        ) {

            for ( auto e : * this ) {
                auto p = t(e);
                m[p.first()] = p.second();
            }

            return m;
        }

        template < typename ValueMapper >
        __CDS_MaybeUnused auto associateWith (
                ValueMapper const & valueMapper
        ) && noexcept -> Sequence < LinkedList < Pair < ElementType, meta :: ReturnOf < ValueMapper > > > >
        __CDS_Requires (
                ForwardIterable < C > &&
                FunctionOver < ValueMapper, meta :: ReturnOf < ValueMapper >, ElementType >
        ) {

            LinkedList < Pair < ElementType, meta :: ReturnOf < ValueMapper > > > container;
            for ( auto e : * this )
                container.add( { e, valueMapper(e) } );

            return std::move ( Sequence < decltype ( container ) > (std::move(container)) );
        }

        template < typename ValueMapper >
        __CDS_MaybeUnused auto associateWith (
                ValueMapper const & valueMapper
        ) & noexcept -> Sequence < LinkedList < Pair < ElementType, meta :: ReturnOf < ValueMapper > > > >
        __CDS_Requires (
                ForwardIterable < C > &&
                FunctionOver < ValueMapper, meta :: ReturnOf < ValueMapper >, ElementType >
        ) {

            LinkedList < Pair < ElementType, meta :: ReturnOf < ValueMapper > > > container;
            for ( auto e : * this )
                container.add( { e, valueMapper(e) } );

            return std::move ( Sequence < decltype ( container ) > (std::move(container)) );
        }

        template < typename ValueMapper >
        __CDS_MaybeUnused auto associateWithTo (
                Map < ElementType, meta :: ReturnOf < ValueMapper > >         & m,
                ValueMapper                                     const & mapper
        ) const noexcept -> Map < ElementType , meta :: ReturnOf < ValueMapper > > &
        __CDS_Requires (
                ForwardIterable < C > &&
                FunctionOver < ValueMapper, meta :: ReturnOf < ValueMapper >, ElementType >
        ) {

            for ( auto e : * this )
                m[e] = mapper(e);
            return m;
        }

        template < typename Comparator = Function < bool (ElementType const &, ElementType const &) > >
        __CDS_MaybeUnused auto sorted (
                Comparator const & comparator = []( ElementType const & a, ElementType const & b) noexcept -> bool { return a < b; }
        ) && noexcept -> Sequence < Array < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && ComparatorFor < Comparator, ElementType > ) {

            Array < ElementType > container;
            for ( auto e: * this )
                container.add(e);

            container.shrinkToSize(container.size());
            container.sort(comparator);

            return std::move ( Sequence < Array < ElementType > > (std::move(container)) );
        }

        template < typename Comparator = Function < bool (ElementType const &, ElementType const &) > >
        __CDS_MaybeUnused auto sorted (
                Comparator const & comparator = []( ElementType const & a, ElementType const & b) noexcept -> bool { return a < b; }
        ) & noexcept -> Sequence < Array < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && ComparatorFor < Comparator, ElementType > ) {

            Array < ElementType > container;
            for ( auto e: * this )
                container.add(e);

            container.shrinkToSize(container.size());
            container.sort(comparator);

            return std::move ( Sequence < Array < ElementType > > (std::move(container)) );
        }

        template < typename Selector >
        __CDS_MaybeUnused __CDS_OptimalInline auto sortedBy (
                Selector const & selector
        ) && noexcept -> Sequence < Array < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && AscendingSelectorFor < Selector, ElementType > ) {

            return this->sorted([& selector](ElementType const & a, ElementType const & b) noexcept -> bool {
                return selector(a) < selector(b);
            });
        }

        template < typename Selector >
        __CDS_MaybeUnused __CDS_OptimalInline auto sortedBy (
                Selector const & selector
        ) & noexcept -> Sequence < Array < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && AscendingSelectorFor < Selector, ElementType > ) {

            return this->sorted([& selector](ElementType const & a, ElementType const & b) noexcept -> bool {
                return selector(a) < selector(b);
            });
        }

        template < typename Selector >
        __CDS_MaybeUnused __CDS_OptimalInline auto sortedByDescending (
                Selector const & selector
        ) && noexcept -> Sequence < Array < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && DescendingSelectorFor < Selector, ElementType > ) {

            return this->sorted([& selector](ElementType const & a, ElementType const & b) noexcept -> bool {
                return selector(a) > selector(b);
            });
        }

        template < typename Selector >
        __CDS_MaybeUnused __CDS_OptimalInline auto sortedByDescending (
                Selector const & selector
        ) & noexcept -> Sequence < Array < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && DescendingSelectorFor < Selector, ElementType > ) {

            return this->sorted([& selector](ElementType const & a, ElementType const & b) noexcept -> bool {
                return selector(a) > selector(b);
            });
        }

        template <
                typename Selector,
                typename Comparator = Function < bool ( meta :: ReturnOf < Selector > const &, meta :: ReturnOf < Selector > const & ) >
        >
        __CDS_MaybeUnused auto sortedByWith (
                Selector    const & selector,
                Comparator  const & comparator = [](
                        meta :: ReturnOf < Selector > const & a,
                        meta :: ReturnOf < Selector > const & b
                ) noexcept -> bool { return a < b; }
        ) && noexcept -> Sequence < Array < ElementType > >
        __CDS_Requires (
                ForwardIterable < C > &&
                SelectorFor < Selector, ElementType > &&
                ComparatorFor < Comparator, meta :: ReturnOf < Selector > >
        ) {

            return this->sorted([& selector, & comparator](ElementType const & a, ElementType const & b){
                return comparator(selector(a), selector(b));
            });
        }

        template <
                typename Selector,
                typename Comparator = Function < bool ( meta :: ReturnOf < Selector > const &, meta :: ReturnOf < Selector > const & ) >
        >
        __CDS_MaybeUnused auto sortedByWith (
                Selector    const & selector,
                Comparator  const & comparator = [](
                        meta :: ReturnOf < Selector > const & a,
                        meta :: ReturnOf < Selector > const & b
                ) noexcept -> bool { return a < b; }
        ) & noexcept -> Sequence < Array < ElementType > >
        __CDS_Requires (
                ForwardIterable < C > &&
                SelectorFor < Selector, ElementType > &&
                ComparatorFor < Comparator, meta :: ReturnOf < Selector > >
        ) {

            return this->sorted([& selector, & comparator](ElementType const & a, ElementType const & b){
                return comparator(selector(a), selector(b));
            });
        }

        template < typename CollectionType >
        __CDS_MaybeUnused auto toCollection () const noexcept -> CollectionType
        __CDS_Requires (
                ForwardIterable < C > &&
                DerivedFrom < CollectionType, Collection < ElementType > >
        ) {

            CollectionType c;
            for ( auto e : * this )
                c.add(e);
            return c;
        }

        __CDS_MaybeUnused auto toLinkedList () const noexcept -> LinkedList < ElementType >
        __CDS_Requires ( ForwardIterable < C > ) {

            return this->toCollection<LinkedList<ElementType>>();
        }

        __CDS_MaybeUnused auto toArray () const noexcept -> Array < ElementType >
        __CDS_Requires ( ForwardIterable < C > ) {

            return this->toCollection<Array<ElementType>>();
        }

        template < typename Comparator >
        __CDS_MaybeUnused auto toOrderedSet () const noexcept -> OrderedSet < ElementType, Comparator >
        __CDS_Requires ( ForwardIterable < C > )  {

            return this->toCollection<OrderedSet<ElementType, Comparator>>();
        }

        __CDS_MaybeUnused auto toUnorderedSet () const noexcept -> UnorderedSet < ElementType >
        __CDS_Requires ( ForwardIterable < C > )  {

            return this->toCollection<UnorderedSet<ElementType>>();
        }

        template <
                typename U = C,
                meta :: EnableIf < utility :: hidden :: sequenceImpl::containedTypeIsPair < U > () > = 0,
                typename FirstType = typename utility :: hidden :: sequenceImpl::ContainedTypeAsPair < U > :: FirstType,
                typename SecondType = typename utility :: hidden :: sequenceImpl::ContainedTypeAsPair < U > :: SecondType,
                typename PType = typename utility :: hidden :: sequenceImpl::ContainedTypeAsPair < U > :: Type
        >
        __CDS_MaybeUnused auto toHashMap () const noexcept -> HashMap < FirstType, SecondType >
        __CDS_Requires( ForwardIterable < C > && PairType < PType > ) {

            HashMap < FirstType, SecondType > map;

            for ( auto e : * this )
                map[e.first()] = e.second();

            return map;
        }

        template <
                typename U = C,
                meta :: EnableIf < utility :: hidden :: sequenceImpl :: containedTypeIsPair < U > () > = 0,
                typename FirstType = typename utility :: hidden :: sequenceImpl::ContainedTypeAsPair < U > :: FirstType,
                typename SecondType = typename utility :: hidden :: sequenceImpl::ContainedTypeAsPair < U > :: SecondType,
                typename PType = typename utility :: hidden :: sequenceImpl::ContainedTypeAsPair < U > :: Type
        >
        __CDS_MaybeUnused auto unzip () const noexcept -> Pair < LinkedList < FirstType >, LinkedList < SecondType > >
        __CDS_Requires ( ForwardIterable < C > && PairType < PType > ) {

            Pair < LinkedList < FirstType >, LinkedList < SecondType > > result;

            for ( auto e : * this ) {
                result.first().append(e.first());
                result.second().append(e.second());
            }

            return result;
        }

        template < typename CollectionType >
        __CDS_MaybeUnused __CDS_OptimalInline auto toCollection (CollectionType & c) const noexcept -> CollectionType &
        __CDS_Requires (
                ForwardIterable < C > &&
                DerivedFrom < CollectionType, Collection < ElementType > >
        ) {

            for ( auto e : * this )
                c.add(e);
            return c;
        }

        __CDS_MaybeUnused __CDS_OptimalInline auto toList (
                List <ElementType> & a
        ) const noexcept -> List < ElementType > &
        __CDS_Requires ( ForwardIterable < C > ) {

            return this->toCollection<List<ElementType>>(a);
        }

        __CDS_MaybeUnused __CDS_OptimalInline auto toLinkedList (
                LinkedList < ElementType > & l
        ) const noexcept -> LinkedList < ElementType > &
        __CDS_Requires ( ForwardIterable < C > ) {

            return this->toCollection<LinkedList<ElementType>>(l);
        }

        __CDS_MaybeUnused __CDS_OptimalInline auto toArray (
                Array <ElementType> & a
        ) const noexcept -> Array < ElementType > &
        __CDS_Requires ( ForwardIterable < C > ) {

            return this->toCollection<Array<ElementType>>(a);
        }

        __CDS_MaybeUnused __CDS_OptimalInline auto toListSet (
                ListSet < ElementType > & a
        ) const noexcept -> ListSet < ElementType > &
        __CDS_Requires ( ForwardIterable < C > ) {

            return this->toCollection<ListSet<ElementType>>(a);
        }

        template < typename Comparator >
        __CDS_MaybeUnused __CDS_OptimalInline auto toOrderedSet (
                OrderedSet <ElementType, Comparator> & s
        ) const noexcept -> OrderedSet < ElementType, Comparator > &
        __CDS_Requires ( ForwardIterable < C > ) {

            return this->toCollection<OrderedSet<ElementType, Comparator>>( s );
        }

        __CDS_MaybeUnused __CDS_OptimalInline auto toUnorderedSet (
                UnorderedSet <ElementType> & s
        ) const noexcept -> UnorderedSet < ElementType > &
        __CDS_Requires ( ForwardIterable < C > ) {

            return this->toCollection<UnorderedSet<ElementType>>(s);
        }

        template <
                typename U = C,
                meta :: EnableIf < utility :: hidden :: sequenceImpl::containedTypeIsPair < U > () > = 0,
                typename FirstType = typename utility :: hidden :: sequenceImpl::ContainedTypeAsPair < U > :: FirstType,
                typename SecondType = typename utility :: hidden :: sequenceImpl::ContainedTypeAsPair < U > :: SecondType,
                typename PType = typename utility :: hidden :: sequenceImpl::ContainedTypeAsPair < U > :: Type
        >
        __CDS_MaybeUnused auto toMap (
                Map < FirstType, SecondType > & map
        ) const noexcept -> Map < FirstType, SecondType > &
        __CDS_Requires( ForwardIterable < C > && PairType < PType > ) {

            for ( auto e : * this )
                map [e.first()] = e.second();

            return map;
        }

        template <
                typename U = C,
                meta :: EnableIf < utility :: hidden :: sequenceImpl::containedTypeIsPair < U > () > = 0,
                typename FirstType = typename utility :: hidden :: sequenceImpl::ContainedTypeAsPair < U > :: FirstType,
                typename SecondType = typename utility :: hidden :: sequenceImpl::ContainedTypeAsPair < U > :: SecondType,
                typename PType = typename utility :: hidden :: sequenceImpl::ContainedTypeAsPair < U > :: Type
        >
        __CDS_MaybeUnused auto toHashMap (
                HashMap < FirstType, SecondType > & map
        ) const noexcept -> HashMap < FirstType, SecondType > &
        __CDS_Requires( ForwardIterable < C > && PairType < PType > ) {

            for ( auto e : * this )
                map [e.first()] = e.second();

            return map;
        }

        template < typename Transformer >
        __CDS_MaybeUnused auto flatMap (
                Transformer const & transformer
        ) && noexcept -> Sequence < LinkedList < utility :: hidden :: sequenceImpl :: FlatMapDeducedType < Transformer > > >
        __CDS_Requires (
                ForwardIterable < C > &&
                ForwardIterable < meta :: ReturnOf < Transformer > > &&
                TransformerOver < Transformer, ElementType >
        ) {

            LinkedList < utility :: hidden :: sequenceImpl :: FlatMapDeducedType < Transformer > > container;

            for ( auto e : * this )
                for ( auto const & s : transformer(e) )
                    container.add( s );
            return std::move ( Sequence < decltype(container) > ( std::move(container) ) );
        }

        template < typename Transformer >
        __CDS_MaybeUnused auto flatMap (
                Transformer const & transformer
        ) & noexcept -> Sequence < LinkedList < utility :: hidden :: sequenceImpl :: FlatMapDeducedType < Transformer > > >
        __CDS_Requires (
                ForwardIterable < C > &&
                ForwardIterable < meta :: ReturnOf < Transformer > > &&
                TransformerOver < Transformer, ElementType >
        ) {

            LinkedList < utility :: hidden :: sequenceImpl :: FlatMapDeducedType < Transformer > > container;

            for ( auto e : * this )
                for ( auto const & s : transformer(e) )
                    container.add( s );
            return std::move ( Sequence < decltype(container) > ( std::move(container) ) );
        }

        template < typename IndexedTransformer >
        __CDS_MaybeUnused auto flatMapIndexed (
                IndexedTransformer const & transformer
        ) && noexcept -> Sequence < LinkedList < utility :: hidden :: sequenceImpl :: FlatMapDeducedType < IndexedTransformer > > > __CDS_Requires (
                ForwardIterable < C > &&
                ForwardIterable < meta :: ReturnOf < IndexedTransformer > > &&
                TransformerOver < IndexedTransformer, Index, ElementType >
        ) {

            LinkedList < utility :: hidden :: sequenceImpl :: FlatMapDeducedType < IndexedTransformer > > container;
            Index i = 0;

            for ( auto e : * this )
                for ( auto const & s : transformer(i ++, e) )
                    container.add( s );
            return std::move ( Sequence < decltype(container) > ( std::move(container) ) );
        }

        template < typename IndexedTransformer >
        __CDS_MaybeUnused auto flatMapIndexed (
                IndexedTransformer const & transformer
        ) & noexcept -> Sequence < LinkedList < utility :: hidden :: sequenceImpl :: FlatMapDeducedType < IndexedTransformer > > > __CDS_Requires (
                ForwardIterable < C > &&
                ForwardIterable < meta :: ReturnOf < IndexedTransformer > > &&
                TransformerOver < IndexedTransformer, Index, ElementType >
        ) {

            LinkedList < utility :: hidden :: sequenceImpl :: FlatMapDeducedType < IndexedTransformer > > container;
            Index i = 0;

            for ( auto e : * this )
                for ( auto const & s : transformer(i ++, e) )
                    container.add( s );
            return std::move ( Sequence < decltype(container) > ( std::move(container) ) );
        }

        template < typename Transformer >
        __CDS_MaybeUnused auto flatMapTo (
                Collection < utility :: hidden :: sequenceImpl :: FlatMapDeducedType < Transformer > >       & collection,
                Transformer                                                         const & transformer
        ) const noexcept -> Collection < utility :: hidden :: sequenceImpl :: FlatMapDeducedType < Transformer > > & __CDS_Requires (
                ForwardIterable < C > &&
                ForwardIterable < meta :: ReturnOf < Transformer > > &&
                TransformerOver < Transformer, ElementType >
        ) {

            for ( auto i : * this )
                for ( auto const & e : transformer(i) )
                    collection.add(e);

            return collection;
        }

        template < typename IndexedTransformer >
        __CDS_MaybeUnused auto flatMapIndexedTo (
                Collection < utility :: hidden :: sequenceImpl :: FlatMapDeducedType < IndexedTransformer > >        & collection,
                IndexedTransformer                                                          const & transformer
        ) const noexcept -> Collection < utility :: hidden :: sequenceImpl :: FlatMapDeducedType < IndexedTransformer > > & __CDS_Requires (
                ForwardIterable < C > &&
                ForwardIterable < meta :: ReturnOf < IndexedTransformer > > &&
                TransformerOver < IndexedTransformer, Index, ElementType >
        ) {

            Index j = 0;
            for ( auto i : * this )
                for ( auto const & e : transformer(j++, i) )
                    collection.add(e);

            return collection;
        }

        template < typename KeySelector >
        __CDS_MaybeUnused auto groupBy (
                KeySelector const & keySelector
        ) && noexcept -> Sequence < HashMap < meta :: ReturnOf < KeySelector >, LinkedList < ElementType > > >
        __CDS_Requires (
                ForwardIterable < C > &&
                FunctionOver < KeySelector, meta :: ReturnOf < KeySelector >, ElementType >
        ) {

            HashMap < meta :: ReturnOf < KeySelector >, LinkedList < ElementType > > container;

            for ( auto e : * this ) {
                auto k = keySelector ( e );
                if ( container.containsKey(k) )
                    container[k].add(e);
                else
                    container[k] = { e };
            }

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        template < typename KeySelector >
        __CDS_MaybeUnused auto groupBy (
                KeySelector const & keySelector
        ) & noexcept -> Sequence < HashMap < meta :: ReturnOf < KeySelector >, LinkedList < ElementType > > >
        __CDS_Requires (
                ForwardIterable < C > &&
                FunctionOver < KeySelector, meta :: ReturnOf < KeySelector >, ElementType >
        ) {

            HashMap < meta :: ReturnOf < KeySelector >, LinkedList < ElementType > > container;

            for ( auto e : * this ) {
                auto k = keySelector ( e );
                if ( container.containsKey(k) )
                    container[k].add(e);
                else
                    container[k] = { e };
            }

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        template < typename KeySelector, typename ValueMapper >
        __CDS_MaybeUnused auto groupBy (
                KeySelector const & keySelector,
                ValueMapper const & valueMapper
        ) && noexcept -> Sequence < HashMap < meta :: ReturnOf < KeySelector >, LinkedList < meta :: ReturnOf < ValueMapper > > > >
        __CDS_Requires (
                ForwardIterable < C > &&
                FunctionOver < KeySelector, meta :: ReturnOf < KeySelector >, ElementType > &&
                FunctionOver < ValueMapper, meta :: ReturnOf < ValueMapper >, ElementType >
        ) {

            HashMap < meta :: ReturnOf < KeySelector >, LinkedList < meta :: ReturnOf < ValueMapper > > > container;

            for ( auto e : * this ) {
                auto k = keySelector ( e ); auto v = valueMapper ( e );
                if ( container.containsKey( k ) )
                    container[k].add(v);
                else
                    container[k] = {v};
            }

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        template < typename KeySelector, typename ValueMapper >
        __CDS_MaybeUnused auto groupBy (
                KeySelector const & keySelector,
                ValueMapper const & valueMapper
        ) & noexcept -> Sequence < HashMap < meta :: ReturnOf < KeySelector >, LinkedList < meta :: ReturnOf < ValueMapper > > > >
        __CDS_Requires (
                ForwardIterable < C > &&
                FunctionOver < KeySelector, meta :: ReturnOf < KeySelector >, ElementType > &&
                FunctionOver < ValueMapper, meta :: ReturnOf < ValueMapper >, ElementType >
        ) {

            HashMap < meta :: ReturnOf < KeySelector >, LinkedList < meta :: ReturnOf < ValueMapper > > > container;

            for ( auto e : * this ) {
                auto k = keySelector ( e ); auto v = valueMapper ( e );
                if ( container.containsKey( k ) )
                    container[k].add(v);
                else
                    container[k] = {v};
            }

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        template < typename KeySelector >
        __CDS_MaybeUnused auto groupByTo (
                Map < meta :: ReturnOf < KeySelector >, LinkedList < ElementType > >          & map,
                KeySelector                                                     const & keySelector
        ) const noexcept -> Map < meta :: ReturnOf < KeySelector >, LinkedList < ElementType > > &
        __CDS_Requires (
                ForwardIterable < C > &&
                FunctionOver < KeySelector, meta :: ReturnOf < KeySelector >, ElementType >
        ) {

            for ( auto e : * this ) {
                auto k = keySelector ( e );
                if ( map.containsKey( k ) )
                    map[k].add ( e );
                else
                    map[k] = { e };
            }

            return map;
        }

        template < typename KeySelector, typename ValueMapper >
        __CDS_MaybeUnused auto groupByTo (
                Map < meta :: ReturnOf < KeySelector >, LinkedList < meta :: ReturnOf < ValueMapper > > >         & map,
                KeySelector                                                                 const & keySelector,
                ValueMapper                                                                 const & valueMapper
        ) const noexcept -> Map < meta :: ReturnOf < KeySelector >, LinkedList < meta :: ReturnOf < ValueMapper > > > &
        __CDS_Requires (
                ForwardIterable < C > &&
                FunctionOver < KeySelector, meta :: ReturnOf < KeySelector >, ElementType > &&
                FunctionOver < ValueMapper, meta :: ReturnOf < ValueMapper >, ElementType >
        ) {

            for ( auto e : * this ) {
                auto k = keySelector ( e ); auto v = valueMapper ( e );
                if ( map.containsKey( k ) )
                    map[k].add ( v );
                else
                    map[k] = { v };
            }

            return map;
        }



    //    template < typename C1 = C, typename std :: enable_if < utility :: hidden :: sequenceImpl :: isFlattable < C1 > (), int > :: type = 0 >
    //    __CDS_NoDiscard __CDS_MaybeUnused auto flatten () noexcept -> Sequence < typename utility :: hidden :: sequenceImpl :: ContainedType < C1 > :: Type >;

        /**
         * Two versions of map, one for storage of mappers when keeping same type, another for switching to another data type
         */

        template < typename Mapper, meta :: EnableIf < ! utility :: hidden :: sequenceImpl :: mapToSameType < Mapper, C > () > = 0 >
        __CDS_MaybeUnused auto map (
                Mapper const & mapper
        ) && noexcept -> Sequence < LinkedList < meta :: ReturnOf < Mapper > > >
        __CDS_Requires ( ForwardIterable < C > && MapperFor < Mapper, ElementType > ) {

            LinkedList < meta :: ReturnOf < Mapper > > container;
            for ( auto e : * this )
                container.append(mapper(e));

            return std::move(Sequence < LinkedList < meta :: ReturnOf < Mapper > > > (std::move(container)));
        }

        template < typename Mapper, meta :: EnableIf < utility :: hidden :: sequenceImpl :: mapToSameType < Mapper, C > () > = 0 >
        __CDS_MaybeUnused __CDS_OptimalInline auto map (
                Mapper const & mapper
        ) && noexcept -> Sequence < C >
        __CDS_Requires ( ForwardIterable < C > && MapperFor < Mapper, ElementType > ) {

            this->storedMappers.append({ { Memory :: instance().create < StoredMapper > (mapper) }, this->chainCount });
            return std::move ( * this );
        }

        template < typename Mapper, meta :: EnableIf < ! utility :: hidden :: sequenceImpl :: mapToSameType < Mapper, C > () > = 0 >
        __CDS_MaybeUnused auto map (
                Mapper const & mapper
        ) & noexcept -> Sequence < LinkedList < meta :: ReturnOf < Mapper > > >
        __CDS_Requires ( ForwardIterable < C > && MapperFor < Mapper, ElementType > ) {

            LinkedList < meta :: ReturnOf < Mapper > > container;
            for ( auto e : * this )
                container.append(mapper(e));

            return std::move(Sequence < LinkedList < meta :: ReturnOf < Mapper > > > (std::move(container)));
        }

        template < typename Mapper, meta :: EnableIf < utility :: hidden :: sequenceImpl :: mapToSameType < Mapper, C > () > = 0 >
        __CDS_MaybeUnused auto map (
                Mapper const & mapper
        ) & noexcept -> Sequence < C >
        __CDS_Requires ( ForwardIterable < C > && MapperFor < Mapper, ElementType > ) {

            Sequence < C > copy ( *this );
            copy.storedMappers.append({ { Memory :: instance().create < StoredMapper >(mapper) }, this->chainCount });
            return std::move(copy);
        }


        template < typename IndexedMapper, meta :: EnableIf < ! utility :: hidden :: sequenceImpl :: mapToSameType < IndexedMapper, C > () > = 0 >
        __CDS_MaybeUnused auto mapIndexed (
                IndexedMapper const & indexedMapper
        ) && noexcept -> Sequence < LinkedList < meta :: ReturnOf < IndexedMapper > > >
        __CDS_Requires ( ForwardIterable < C > && MapperFor < IndexedMapper, Index, ElementType > ) {

            LinkedList < meta :: ReturnOf < IndexedMapper > > container;
            Index i = 0;
            for ( auto e : * this )
                container.append(mapper(i++, e));

            return std::move(Sequence < LinkedList < meta :: ReturnOf < IndexedMapper > > > (std::move(container)));
        }

        template < typename IndexedMapper, meta :: EnableIf < ! utility :: hidden :: sequenceImpl :: mapToSameType < IndexedMapper, C > () > = 0 >
        __CDS_MaybeUnused auto mapIndexed (
                IndexedMapper const & mapper
        ) & noexcept -> Sequence < LinkedList < meta :: ReturnOf < IndexedMapper > > >
        __CDS_Requires ( ForwardIterable < C > && MapperFor < IndexedMapper, Index, ElementType > ) {

            LinkedList < meta :: ReturnOf < IndexedMapper > > container;
            Index i = 0;
            for ( auto e : * this )
                container.append(mapper(i++, e));

            return std::move(Sequence < LinkedList < meta :: ReturnOf < IndexedMapper > > > (std::move(container)));
        }

        template < typename IndexedMapper, meta :: EnableIf < utility :: hidden :: sequenceImpl :: mapToSameType < IndexedMapper, C > () > = 0 >
        __CDS_MaybeUnused auto mapIndexed (
                IndexedMapper const & mapper
        ) && noexcept -> Sequence < C >
        __CDS_Requires ( ForwardIterable < C > && MapperFor < IndexedMapper, Index, ElementType > ) {

            this->storedIndexedMappers.append({ { Memory :: instance().create < StoredIndexedMapper >(mapper) }, this->chainCount });
            return std::move ( * this );
        }

        template < typename IndexedMapper, meta :: EnableIf < utility :: hidden :: sequenceImpl :: mapToSameType < IndexedMapper, C > () > = 0 >
        __CDS_MaybeUnused auto mapIndexed (
                IndexedMapper const & mapper
        ) & noexcept -> Sequence < C >
        __CDS_Requires ( ForwardIterable < C > && MapperFor < IndexedMapper, Index, ElementType > ) {

            Sequence < C > newSequence (* this);
            newSequence.storedIndexedMappers.append({ { Memory::instance().create < StoredIndexedMapper >(mapper) }, this->chainCount });
            return std::move ( newSequence );
        }

        template < typename Mapper, typename R >
        __CDS_MaybeUnused auto mapTo (
                Collection < R >          & collection,
                Mapper              const & mapper
        ) const noexcept -> Collection < R > &
        __CDS_Requires (
                ForwardIterable < C > &&
                MapperFor < Mapper, ElementType > &&
                ConvertibleTo < meta :: ReturnOf < Mapper >, R >
        ) {

            for ( auto e : * this )
                collection.add ( mapper(e) );
            return collection;
        }

        template < typename IndexedMapper, typename R >
        __CDS_MaybeUnused auto mapIndexedTo (
                Collection < R >          & collection,
                IndexedMapper       const & mapper
        ) const noexcept -> Collection < R > &
        __CDS_Requires (
                ForwardIterable < C > &&
                MapperFor < IndexedMapper, Index, ElementType > &&
                ConvertibleTo < meta :: ReturnOf < IndexedMapper >, R >
        ) {

            Index i = 0;
            for ( auto e : * this )
                collection.add ( mapper(i++, e) );
            return collection;
        }


        __CDS_MaybeUnused auto indexed () && noexcept -> Sequence < LinkedList < Pair < Index, ElementType > > >
        __CDS_Requires ( ForwardIterable < C > ) {

            LinkedList < Pair < Index, ElementType > > container;
            Index i = 0;
            for ( auto e : * this )
                container.add ( { i++, e } );

            return std::move ( Sequence < LinkedList < Pair < Index, ElementType > > > ( std::move ( container ) ) );
        }

        __CDS_MaybeUnused auto indexed () & noexcept -> Sequence < LinkedList < Pair < Index, ElementType > > >
        __CDS_Requires ( ForwardIterable < C > ) {

            LinkedList < Pair < Index, ElementType > > container;
            Index i = 0;
            for ( auto e : * this )
                container.add ( { i++, e } );

            return std::move ( Sequence < LinkedList < Pair < Index, ElementType > > > ( std::move ( container ) ) );
        }

        __CDS_MaybeUnused auto distinct () && noexcept -> Sequence < UnorderedSet < ElementType > >
        __CDS_Requires ( ForwardIterable < C > ) {

            UnorderedSet < ElementType > container;
            for ( auto e : * this )
                container.add ( e );
            return std::move ( Sequence < decltype (container) > ( std::move ( container ) ) );
        }

        __CDS_MaybeUnused auto distinct () & noexcept -> Sequence < UnorderedSet < ElementType > >
        __CDS_Requires ( ForwardIterable < C > ) {

            UnorderedSet < ElementType > container;
            for ( auto e : * this )
                container.add ( e );
            return std::move ( Sequence < decltype (container) > ( std::move ( container ) ) );
        }


        template < typename Selector >
        __CDS_MaybeUnused auto distinctBy (Selector const & selector) && noexcept -> Sequence < UnorderedSet < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && TransformerOver < Selector, ElementType > ) {

            UnorderedSet < ElementType > container;
            for ( auto e : * this )
                if ( ! this->contains(selector(e)) )
                    container.add ( e );
            return std::move ( Sequence < decltype (container) > ( std::move ( container ) ) );
        }

        template < typename Selector >
        __CDS_MaybeUnused auto distinctBy (Selector const & selector) & noexcept -> Sequence < UnorderedSet < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && TransformerOver < Selector, ElementType > ) {

            UnorderedSet < ElementType > container;
            for ( auto e : * this )
                if ( ! container.any([&](ElementType const & cE){ return meta :: equals ( selector(cE), selector(e) ); }) )
                    container.add ( e );
            return std::move ( Sequence < decltype (container) > ( std::move ( container ) ) );
        }

        template < typename Action >
        __CDS_MaybeUnused auto forEach ( Action const & action ) const noexcept -> void
        __CDS_Requires ( ForwardIterable < C > && ActionOver < Action, ElementType > ) {

            for ( auto e : * this )
                action (e);
        }

        template < typename IndexedAction >
        __CDS_MaybeUnused auto forEachIndexed ( IndexedAction const & indexedAction ) const noexcept -> void
        __CDS_Requires ( ForwardIterable < C > && IndexedActionOver < IndexedAction, ElementType > ) {

            Index i = 0;
            for ( auto e : * this )
                indexedAction (i++, e);
        }

        template < typename Action >
        __CDS_MaybeUnused auto onEach ( Action const & action ) && noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && ActionOver < Action, ElementType > ) {

            LinkedList < ElementType > container;
            for ( auto e : * this ) {
                action (e);
                container.append(e);
            }

            return std::move(Sequence < LinkedList < ElementType > > (std::move(container)));
        }

        template < typename IndexedAction >
        __CDS_MaybeUnused auto onEachIndexed (
                IndexedAction const & indexedAction
        ) && noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && IndexedActionOver < IndexedAction, ElementType > ) {

            LinkedList < ElementType > container;
            Index i = 0;
            for ( auto e : * this ) {
                indexedAction (i++, e);
                container.append(e);
            }

            return std::move(Sequence < LinkedList < ElementType > > (std::move(container)));
        }

        template < typename Action >
        __CDS_MaybeUnused auto onEach ( Action const & action ) & noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && ActionOver < Action, ElementType > ) {

            Sequence copy (*this);

            LinkedList < ElementType > container;
            for ( auto e : copy ) {
                action (e);
                container.append(e);
            }

            return std::move(Sequence < LinkedList < ElementType > > (std::move(container)));
        }

        template < typename IndexedAction >
        __CDS_MaybeUnused auto onEachIndexed (
                IndexedAction const & indexedAction
        ) & noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && IndexedActionOver < IndexedAction, ElementType > ) {

            Sequence copy (*this);

            LinkedList < ElementType > container;
            Index i = 0;
            for ( auto e : copy ) {
                indexedAction (i++, e);
                container.append(e);
            }

            return std::move(Sequence < LinkedList < ElementType > > (std::move(container)));
        }

    #if defined(_MSC_VER)
    #pragma push_macro("min")
    #pragma push_macro("max")
    #undef min
    #undef max
    #endif

        template < typename Comparator = Function < bool (ElementType const &, ElementType const &) > >
        __CDS_MaybeUnused auto max (
                Comparator const & comparator = [](ElementType const & a, ElementType const & b) noexcept -> bool { return a < b; }
        ) const noexcept -> Optional < ElementType >
        __CDS_Requires ( ForwardIterable < C > && ComparatorFor < Comparator, ElementType > ) {

            if ( this->pCollection.valueAt().valueAt().size() == 0 ) return {  };

            auto it = this->begin();
            ElementType max = it.value();

            for (it.next(); it != this->end(); ++it) {
                auto v = it.value();
                if ( comparator (max, v) )
                    max = v;
            }

            return {max};
        }

        template < typename Selector >
        __CDS_MaybeUnused auto maxBy ( Selector const & selector ) const noexcept -> Optional < ElementType >
        __CDS_Requires (
                ForwardIterable < C > &&
                AscendingSelectorFor < Selector, ElementType >
        ) {

            if ( this->pCollection.valueAt().valueAt().size() == 0 ) return { };

            auto it = this->begin();
            auto max = Pair < decltype( selector(it.value()) ), decltype( it.value() ) > ( selector (it.value()), it.value() );

            for ( it.next(); it != this->end(); ++ it ) {
                auto v = selector (it.value());
                if ( max.first() < v )
                    max = { v, it.value() };
            }

            return {max.second()};
        }

        template < typename Selector >
        __CDS_MaybeUnused auto maxOf ( Selector const & selector ) const noexcept -> Optional < meta :: ReturnOf < Selector > >
        __CDS_Requires (
                ForwardIterable < C > &&
                AscendingSelectorFor < Selector, ElementType >
        ) {

            if ( this->pCollection.valueAt().valueAt().size() == 0 ) return { };

            auto it = this->begin();
            auto max = Pair < decltype( selector(it.value()) ), decltype( it.value() ) > ( selector (it.value()), it.value() );

            for ( it.next(); it != this->end(); ++ it ) {
                auto v = selector (it.value());
                if ( max.first() < v )
                    max = { v, it.value() };
            }

            return {max.first()};
        }

        template < typename Comparator = Function < bool (ElementType const &, ElementType const &) > >
        __CDS_MaybeUnused __CDS_OptimalInline auto maxOr (
                ElementType const & e,
                Comparator  const & comparator = [](ElementType const & a, ElementType const & b) noexcept -> bool { return a < b; }
        ) const noexcept -> ElementType
        __CDS_Requires ( ForwardIterable < C > && ComparatorFor < Comparator, ElementType > ) {

            auto v = this->max ( comparator );
            return v.isPresent() ? v.value() : e;
        }

        template < typename Selector >
        __CDS_MaybeUnused auto maxByOr (
                ElementType const & e,
                Selector    const & selector
        ) const noexcept -> ElementType __CDS_Requires (
                ForwardIterable < C > &&
                AscendingSelectorFor < Selector, ElementType >
        ) {

            auto v = this->maxBy ( selector );
            return v.isPresent() ? v.value() : e;
        }

        template < typename Selector >
        __CDS_MaybeUnused auto maxOfOr (
                meta :: ReturnOf < Selector >   const & e,
                Selector                const & selector
        ) const noexcept -> meta :: ReturnOf < Selector > __CDS_Requires (
                ForwardIterable < C > &&
                AscendingSelectorFor < Selector, ElementType >
        ) {

            auto v = this->maxOf ( selector );
            return v.isPresent() ? v.value() : e;
        }

        template < typename Comparator = Function < bool (ElementType const &, ElementType const &) > >
        __CDS_MaybeUnused auto min (
                Comparator const & comparator = [](ElementType const & a, ElementType const & b) noexcept -> bool { return a < b; }
        ) const noexcept -> Optional < ElementType >
        __CDS_Requires ( ForwardIterable < C > && ComparatorFor < Comparator, ElementType > )  {

            if ( this->pCollection.valueAt().valueAt().size() == 0 ) return {  };

            auto it = this->begin();
            ElementType min = it.value();

            for (it.next(); it != this->end(); ++it) {
                auto v = it.value();
                if ( comparator (v, min) )
                    min = v;
            }

            return {min};
        }

        template < typename Selector >
        __CDS_MaybeUnused auto minBy (
                Selector const & selector
        ) const noexcept -> Optional < ElementType > __CDS_Requires (
                ForwardIterable < C > &&
                AscendingSelectorFor < Selector, ElementType >
        ) {

            if ( this->pCollection.valueAt().valueAt().size() == 0 ) return { };

            auto it = this->begin();
            auto min = Pair < decltype(selector(it.value())), decltype(it.value()) > (selector (it.value()), it.value() );

            for ( it.next(); it != this->end(); ++ it ) {
                auto v = selector (it.value());
                if ( v < min.first() )
                    min = {v, it.value() };
            }

            return {min.second()};
        }

        template < typename Selector >
        __CDS_MaybeUnused auto minOf ( Selector const & selector ) const noexcept -> Optional < meta :: ReturnOf < Selector > >
        __CDS_Requires (
                ForwardIterable < C > &&
                AscendingSelectorFor < Selector, ElementType >
        ) {

            if ( this->pCollection.valueAt().valueAt().size() == 0 ) return { };

            auto it = this->begin();
            auto min = Pair < decltype(selector(it.value())), decltype(it.value()) > (selector (it.value()), it.value() );

            for ( it.next(); it != this->end(); ++ it ) {
                auto v = selector (it.value());
                if ( v < min.first() )
                    min = {v, it.value() };
            }

            return {min.first()};
        }

        template < typename Comparator = Function < bool (ElementType const &, ElementType const &) > >
        __CDS_MaybeUnused auto minOr (
                ElementType const & e,
                Comparator  const & comparator = [](ElementType const & a, ElementType const & b) noexcept -> bool { return a < b; }
        ) const noexcept -> ElementType
        __CDS_Requires ( ForwardIterable < C > && ComparatorFor < Comparator, ElementType > ) {

            auto v = this->min ( comparator );
            return v.isPresent() ? v.value() : e;
        }

        template < typename Selector >
        __CDS_MaybeUnused auto minByOr (
                ElementType const & e,
                Selector    const & selector
        ) const noexcept -> ElementType
        __CDS_Requires (
                ForwardIterable < C > &&
                AscendingSelectorFor < Selector, ElementType >
        ) {

            auto v = this->minBy ( selector );
            return v.isPresent() ? v.value() : e;
        }

        template < typename Selector >
        __CDS_MaybeUnused auto minOfOr (
                meta :: ReturnOf < Selector >   const & e,
                Selector                const & selector
        ) const noexcept -> meta :: ReturnOf < Selector >
        __CDS_Requires (
                ForwardIterable < C > &&
                AscendingSelectorFor < Selector, ElementType >
        ) {

            auto v = this->minOf ( selector );
            return v.isPresent() ? v.value() : e;
        }

    #if defined(_MSC_VER)
        #pragma pop_macro("max")
        #pragma pop_macro("min")
    #endif

        template < typename Accumulator, typename AccumulatedType >
        __CDS_MaybeUnused auto fold (
                AccumulatedType const & startingValue,
                Accumulator     const & accumulator
        ) const noexcept -> AccumulatedType
        __CDS_Requires (
                ForwardIterable < C > &&
                AccumulatorFor < Accumulator, AccumulatedType, ElementType >
        ) {

            AccumulatedType result = startingValue;

            for ( auto e : * this )
                result = accumulator ( result, e );

            return result;
        }

        template < typename IndexedAccumulator, typename AccumulatedType >
        __CDS_MaybeUnused auto foldIndexed (
                AccumulatedType     const & startingValue,
                IndexedAccumulator  const & indexedAccumulator
        ) const noexcept -> AccumulatedType
        __CDS_Requires (
                ForwardIterable < C > &&
                IndexedAccumulatorFor < IndexedAccumulator, AccumulatedType, ElementType >
        ) {
            AccumulatedType result = startingValue;
            Index i = 0;

            for ( auto e : * this )
                result = indexedAccumulator ( i++, result, e );

            return result;
        }

        template < typename Accumulator, typename AccumulatedType >
        __CDS_MaybeUnused auto runningFold (
                AccumulatedType const & initialValue,
                Accumulator     const & accumulator
        ) && noexcept -> Sequence < LinkedList < AccumulatedType > >
        __CDS_Requires (
                ForwardIterable < C > &&
                AccumulatorFor < Accumulator, AccumulatedType, ElementType >
        ) {

            LinkedList < AccumulatedType > results = { initialValue };

            for ( auto e : * this )
                results.add ( accumulator ( results.back(), e ) );

            return std::move ( Sequence < decltype ( results ) > ( std::move ( results ) ) );
        }

        template < typename IndexedAccumulator, typename AccumulatedType >
        __CDS_MaybeUnused auto runningFoldIndexed (
                AccumulatedType     const & initialValue,
                IndexedAccumulator  const & indexedAccumulator
        ) && noexcept -> Sequence < LinkedList < AccumulatedType > >
        __CDS_Requires (
                ForwardIterable < C > &&
                IndexedAccumulatorFor < IndexedAccumulator, AccumulatedType, ElementType >
        ) {

            LinkedList < AccumulatedType > results = { initialValue };
            Index i = 0;

            for ( auto e : * this )
                results.add ( indexedAccumulator ( i++, results.back(), e ) );

            return std::move ( Sequence < decltype ( results ) > ( std::move ( results ) ) );
        }

        template < typename Accumulator, typename AccumulatedType >
        __CDS_MaybeUnused auto runningFold (
                AccumulatedType const & initialValue,
                Accumulator     const & accumulator
        ) & noexcept -> Sequence < LinkedList < AccumulatedType > >
        __CDS_Requires (
                ForwardIterable < C > &&
                AccumulatorFor < Accumulator, AccumulatedType, ElementType >
        ) {

            LinkedList < AccumulatedType > results = { initialValue };

            for ( auto e : * this )
                results.add ( accumulator ( results.back(), e ) );

            return std::move ( Sequence < decltype ( results ) > ( std::move ( results ) ) );
        }

        template < typename IndexedAccumulator, typename AccumulatedType >
        __CDS_MaybeUnused auto runningFoldIndexed (
                AccumulatedType     const & initialValue,
                IndexedAccumulator  const & indexedAccumulator
        ) & noexcept -> Sequence < LinkedList < AccumulatedType > >
        __CDS_Requires (
                ForwardIterable < C > &&
                IndexedAccumulatorFor < IndexedAccumulator, AccumulatedType, ElementType >
        ) {

            LinkedList < AccumulatedType > results = { initialValue };
            Index i = 0;

            for ( auto e : * this )
                results.add ( indexedAccumulator ( i++, results.back(), e ) );

            return std::move ( Sequence < decltype ( results ) > ( std::move ( results ) ) );
        }

        template < typename Accumulator >
        __CDS_MaybeUnused auto reduce (
                Accumulator const & accumulator
        ) const noexcept (false) -> meta :: ReturnOf < Accumulator >
        __CDS_Requires (
                ForwardIterable < C > &&
                AccumulatorFor < Accumulator, ElementType, ElementType > &&
                ConvertibleTo < ElementType, meta :: ReturnOf < Accumulator > >
        ) {

            if ( this->pCollection.valueAt().valueAt().size() == 0 )
                throw OutOfBoundsException ("reduce used on empty Sequence");

            auto it = this->begin();
            meta :: ReturnOf < Accumulator > result = it.value();

            for ( it.next(); it != this->end(); ++ it )
                result = accumulator ( result, it.value() );

            return result;
        }

        template < typename IndexedAccumulator >
        __CDS_MaybeUnused auto reduceIndexed (
                IndexedAccumulator const & indexedAccumulator
        ) const noexcept (false) -> meta :: ReturnOf < IndexedAccumulator >
        __CDS_Requires (
                ForwardIterable < C > &&
                IndexedAccumulatorFor < IndexedAccumulator, ElementType, ElementType > &&
                ConvertibleTo < ElementType, meta :: ReturnOf < IndexedAccumulator > >
        ) {

            if ( this->pCollection.valueAt().valueAt().size() == 0 )
                throw OutOfBoundsException ("reduceIndexed used on empty Sequence");

            auto it = this->begin();
            meta :: ReturnOf < IndexedAccumulator > result = it.value();
            Index i = 1;

            for ( it.next(); it != this->end(); ++ it )
                result = indexedAccumulator ( i ++, result, it.value() );

            return result;
        }

        template < typename Accumulator >
        __CDS_MaybeUnused auto runningReduce (
                Accumulator const & accumulator
        ) && noexcept -> Sequence < LinkedList < meta :: ReturnOf < Accumulator > > >
        __CDS_Requires (
                ForwardIterable < C > &&
                AccumulatorFor < Accumulator, ElementType, ElementType > &&
                ConvertibleTo < ElementType, meta :: ReturnOf < Accumulator > >
        ) {

            LinkedList < meta :: ReturnOf < Accumulator > > results = { };

            if ( this->pCollection.valueAt().valueAt().size() > 0 ) {
                auto it = this->begin();
                results.add(it.value());

                for (it.next(); it != this->end(); ++it)
                    results.add(accumulator(results.back(), it.value()));
            }

            return std::move ( Sequence < decltype ( results ) > ( std::move ( results ) ) );
        }

        template < typename IndexedAccumulator >
        __CDS_MaybeUnused auto runningReduceIndexed (
                IndexedAccumulator const & indexedAccumulator
        ) && noexcept -> Sequence < LinkedList < meta :: ReturnOf < IndexedAccumulator > > >
        __CDS_Requires (
                ForwardIterable < C > &&
                IndexedAccumulatorFor < IndexedAccumulator, ElementType, ElementType > &&
                ConvertibleTo < ElementType, meta :: ReturnOf < IndexedAccumulator > >
        ) {

            LinkedList < meta :: ReturnOf < IndexedAccumulator > > results = { };

            if ( this->pCollection.valueAt().valueAt().size() > 0 ) {
                auto it = this->begin();
                Index i = 1;

                results.add(it.value());

                for (it.next(); it != this->end(); ++it)
                    results.add(indexedAccumulator(i++, results.back(), it.value()));
            }

            return std::move ( Sequence < decltype ( results ) > ( std::move ( results ) ) );
        }


        template < typename Accumulator >
        __CDS_MaybeUnused auto runningReduce (
                Accumulator const & accumulator
        ) & noexcept -> Sequence < LinkedList < meta :: ReturnOf < Accumulator > > >
        __CDS_Requires (
                ForwardIterable < C > &&
                AccumulatorFor < Accumulator, ElementType, ElementType > &&
                ConvertibleTo < ElementType, meta :: ReturnOf < Accumulator > >
        ) {

            LinkedList < meta :: ReturnOf < Accumulator > > results = { };

            if ( this->pCollection.valueAt().valueAt().size() > 0 ) {
                auto it = this->begin();
                results.add(it.value());

                for (it.next(); it != this->end(); ++it)
                    results.add(accumulator(results.back(), it.value()));
            }

            return std::move ( Sequence < decltype ( results ) > ( std::move ( results ) ) );
        }

        template < typename IndexedAccumulator >
        __CDS_MaybeUnused auto runningReduceIndexed (
                IndexedAccumulator const & indexedAccumulator
        ) & noexcept -> Sequence < LinkedList < meta :: ReturnOf < IndexedAccumulator > > >
        __CDS_Requires (
                ForwardIterable < C > &&
                IndexedAccumulatorFor < IndexedAccumulator, ElementType, ElementType > &&
                ConvertibleTo < ElementType, meta :: ReturnOf < IndexedAccumulator > >
        ) {

            LinkedList < meta :: ReturnOf < IndexedAccumulator > > results = { };

            if ( this->pCollection.valueAt().valueAt().size() > 0 ) {
                auto it = this->begin();
                Index i = 1;

                results.add(it.value());

                for (it.next(); it != this->end(); ++it)
                    results.add(indexedAccumulator(i++, results.back(), it.value()));
            }

            return std::move ( Sequence < decltype ( results ) > ( std::move ( results ) ) );
        }

        template < typename Accumulator, typename AccumulatedType >
        __CDS_MaybeUnused __CDS_OptimalInline auto scan (
                AccumulatedType const & initialValue,
                Accumulator     const & accumulator
        ) && noexcept -> Sequence < LinkedList < AccumulatedType > >
        __CDS_Requires (
                ForwardIterable < C > &&
                AccumulatorFor < Accumulator, ElementType, ElementType >
        ) {

            return this->runningFold( initialValue, accumulator );
        }

        template < typename Accumulator, typename AccumulatedType >
        __CDS_MaybeUnused auto scan (
                AccumulatedType const & initialValue,
                Accumulator     const & accumulator
        ) & noexcept -> Sequence < LinkedList < AccumulatedType > >
        __CDS_Requires (
                ForwardIterable < C > &&
                AccumulatorFor < Accumulator, ElementType, ElementType >
        ) {

            return this->runningFold( initialValue, accumulator );
        }

        template < typename IndexedAccumulator, typename AccumulatedType >
        __CDS_MaybeUnused auto scanIndexed (
                AccumulatedType     const & initialValue,
                IndexedAccumulator  const & indexedAccumulator
        ) && noexcept -> Sequence < LinkedList < AccumulatedType > >
        __CDS_Requires (
                ForwardIterable < C > &&
                IndexedAccumulatorFor < IndexedAccumulator, ElementType, ElementType >
        ) {

            return this->runningFoldIndexed ( initialValue, indexedAccumulator );
        }

        template < typename IndexedAccumulator, typename AccumulatedType >
        __CDS_MaybeUnused auto scanIndexed (
                AccumulatedType     const & initialValue,
                IndexedAccumulator  const & indexedAccumulator
        ) & noexcept -> Sequence < LinkedList < AccumulatedType > >
        __CDS_Requires (
                ForwardIterable < C > &&
                IndexedAccumulatorFor < IndexedAccumulator, ElementType, ElementType >
        ) {

            return this->runningFoldIndexed ( initialValue, indexedAccumulator );
        }

        template < typename E = ElementType, meta :: EnableIf < meta :: isArithmetic < E > () > = 0 >
        __CDS_NoDiscard __CDS_MaybeUnused auto sum () const noexcept -> ElementType
        __CDS_Requires ( ForwardIterable < C > && Integral < ElementType > ) {
            ElementType sum = 0;
            for ( auto e : * this )
                sum = sum + e;

            return sum;
        }

        template < typename E = ElementType, meta :: EnableIf < ! meta :: isArithmetic < E > () && meta :: isDefaultConstructible < E > () > = 0 >
        __CDS_NoDiscard __CDS_MaybeUnused auto sum () const noexcept -> ElementType
        __CDS_Requires ( ForwardIterable < C > ) {

            ElementType sum;
            for ( auto e : * this )
                sum = sum + e;

            return sum;
        }

        template < typename Selector >
        __CDS_MaybeUnused auto sumBy ( Selector const & selector ) const noexcept -> meta :: ReturnOf < Selector >
        __CDS_Requires (
                ForwardIterable < C > &&
                MapperFor < Selector, ElementType > &&
                Summable < meta :: ReturnOf < Selector > >
        ) {

            auto it = this->begin();
            auto sum = selector ( it.value() );

            for (it.next(); it != this->end(); ++ it)
                sum = sum + selector(it.value());

            return sum;
        }

        template < typename U = C, meta :: EnableIf < utility :: hidden :: sequenceImpl :: IsArithmetic < typename utility :: hidden :: sequenceImpl :: ContainedType < U > > :: Value > = 0 >
        __CDS_NoDiscard __CDS_MaybeUnused auto average () const noexcept -> Double
        __CDS_Requires ( ForwardIterable < C > && ConvertibleTo < double, ElementType > ) {
            double average = 0.0; int eCount = 0;
            for ( auto e : * this ) {
                ++ eCount;
                average += static_cast < double > ( e );
            }

            return average / static_cast < double > ( eCount );
        }


        __CDS_MaybeUnused auto chunked (Size chunkSize) && noexcept -> Sequence < LinkedList < Array < ElementType > > >
        __CDS_Requires ( ForwardIterable < C > ) {

            LinkedList < Array < ElementType > > container;
            Array < ElementType > subContainer;
            Index subContainerPos = 0;
            subContainer.resize(chunkSize);

            for ( auto e : * this ) {
                subContainer[subContainerPos++] = e;

                if ( subContainerPos >= chunkSize ){
                    container.add(subContainer);
                    subContainer.clear();
                    subContainer.resize(chunkSize);
                    subContainerPos = 0;
                }
            }

            if ( ! subContainer.empty() && subContainerPos > 0 ) {
                subContainer.resize(subContainerPos);
                container.add(subContainer);
            }

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        __CDS_MaybeUnused auto chunked (Size chunkSize) & noexcept -> Sequence < LinkedList < Array < ElementType > > >
        __CDS_Requires ( ForwardIterable < C > ) {

            LinkedList < Array < ElementType > > container;
            Array < ElementType > subContainer;
            Index subContainerPos = 0;
            subContainer.resize(chunkSize);

            for ( auto e : * this ) {
                subContainer[subContainerPos++] = e;

                if ( subContainerPos >= chunkSize ){
                    container.add(subContainer);
                    subContainer.clear();
                    subContainer.resize(chunkSize);
                    subContainerPos = 0;
                }
            }

            if ( ! subContainer.empty() && subContainerPos > 0 ) {
                subContainer.resize(subContainerPos);
                container.add(subContainer);
            }

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        template < typename ListTransformer >
        __CDS_MaybeUnused auto chunked (
                Size                    chunkSize,
                ListTransformer const & listTransformer
        ) && noexcept -> Sequence < LinkedList < meta :: ReturnOf < ListTransformer > > >
        __CDS_Requires ( ForwardIterable < C > && TransformerOver < ListTransformer, List < ElementType > > ) {

            LinkedList < meta :: ReturnOf < ListTransformer > > container;
            Array < ElementType > subContainer;
            Index subContainerPos = 0;
            subContainer.resize(chunkSize);

            for ( auto e : * this ) {
                subContainer[subContainerPos++] = e;

                if ( subContainerPos >= chunkSize ) {
                    container.add ( listTransformer ( subContainer ) );
                    subContainer.clear();
                    subContainer.resize(chunkSize);
                    subContainerPos = 0;
                }
            }

            if ( ! subContainer.empty() && subContainerPos > 0 ) {
                subContainer.resize(subContainerPos);
                container.add ( listTransformer ( subContainer ) );
            }

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        template < typename ListTransformer >
        __CDS_MaybeUnused auto chunked (
                Size                    chunkSize,
                ListTransformer const & listTransformer
        ) & noexcept -> Sequence < LinkedList < meta :: ReturnOf < ListTransformer > > >
        __CDS_Requires ( ForwardIterable < C > && TransformerOver < ListTransformer, List < ElementType > > ) {

            LinkedList < meta :: ReturnOf < ListTransformer > > container;
            Array < ElementType > subContainer;
            Index subContainerPos = 0;
            subContainer.resize(chunkSize);

            for ( auto e : * this ) {
                subContainer[subContainerPos++] = e;

                if ( subContainerPos >= chunkSize ) {
                    container.add ( listTransformer ( subContainer ) );
                    subContainer.clear();
                    subContainer.resize(chunkSize);
                    subContainerPos = 0;
                }
            }

            if ( ! subContainer.empty() && subContainerPos > 0 ) {
                subContainer.resize(subContainerPos);
                container.add ( listTransformer ( subContainer ) );
            }

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }


        __CDS_MaybeUnused auto minus (
                ElementType const & toRemove
        ) && noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > ) {

            LinkedList < ElementType > container;
            Boolean found = false;

            for ( auto e : * this )
                if ( found || e != toRemove )
                    container.add( e );
                else
                    found = true;

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        __CDS_MaybeUnused auto minus (
                Collection < ElementType > const & toRemove
        ) && noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > ) {

            LinkedList < ElementType > container;

            for ( auto e : * this )
                if ( ! toRemove.contains(e) )
                    container.add(e);

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }


        template < typename OC, typename OtherType = typename Sequence < C > :: ElementType >
        __CDS_MaybeUnused auto minus (
                Sequence < OC > const & sequence
        ) && noexcept -> Sequence < LinkedList < OtherType > >
        __CDS_Requires (
                ForwardIterable < C > &&
                ForwardIterable < OC > &&
                EqualsComparable < ElementType, OtherType >
        ) {

            LinkedList < ElementType > container;

            for ( auto e : * this ) {
                Boolean found = false;
                for (auto v : sequence)
                    if ( v == e ) {
                        found = true;
                        break;
                    }

                if ( ! found )
                    container.add( e );
            }

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        __CDS_MaybeUnused auto minus (
                ElementType const & toRemove
        ) & noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > ) {

            LinkedList < ElementType > container;
            Boolean found = false;

            for ( auto e : * this )
                if ( found || e != toRemove )
                    container.add( e );
                else
                    found = true;

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        __CDS_MaybeUnused auto minus (
                Collection < ElementType > const & toRemove
        ) & noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > ) {

            LinkedList < ElementType > container;

            for ( auto e : * this )
                if ( ! toRemove.contains(e) )
                    container.add(e);

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        template < typename OC, typename OtherType = typename Sequence < C > :: ElementType >
        __CDS_MaybeUnused auto minus (
                Sequence < OC > const & sequence
        ) & noexcept -> Sequence < LinkedList < OtherType > >
        __CDS_Requires (
                ForwardIterable < C > &&
                ForwardIterable < OC > &&
                EqualsComparable < ElementType, OtherType >
        ) {

            LinkedList < ElementType > container;

            for ( auto e : * this ) {
                Boolean found = false;
                for (auto v : sequence)
                    if ( v == e ) {
                        found = true;
                        break;
                    }

                if ( ! found )
                    container.add( e );
            }

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }


        __CDS_MaybeUnused auto plus (
                ElementType const & toAdd
        ) && noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > ) {

            LinkedList < ElementType > container;

            for ( auto e : * this )
                container.add(e);
            container.add(toAdd);

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        __CDS_MaybeUnused auto plus (
                Collection < ElementType > const & toAdd
        ) && noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > ) {

            LinkedList < ElementType > container;

            for ( auto e : * this )
                container.add(e);

            toAdd.forEach([& container](ElementType const & e){container.add(e);});

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        template < typename OC >
        __CDS_MaybeUnused auto plus (
                Sequence < OC > const & toAdd
        ) && noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && ForwardIterable < OC > ) {

            LinkedList < ElementType > container;

            for ( auto e : * this )
                container.add(e);
            for ( auto e : toAdd )
                container.add(e);

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        __CDS_MaybeUnused auto plus (
                ElementType const & toAdd
        ) & noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > ) {

            LinkedList < ElementType > container;

            for ( auto e : * this )
                container.add(e);
            container.add(toAdd);

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        __CDS_MaybeUnused auto plus (
                Collection < ElementType > const & toAdd
        ) & noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > ) {

            LinkedList < ElementType > container;

            for ( auto e : * this )
                container.add(e);

            toAdd.forEach([& container](ElementType const & e){container.add(e);});

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        template < typename OC >
        __CDS_MaybeUnused auto plus (
                Sequence < OC > const & toAdd
        ) & noexcept -> Sequence < LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && ForwardIterable < OC > ) {

            LinkedList < ElementType > container;

            for ( auto e : * this )
                container.add(e);
            for ( auto e : toAdd )
                container.add(e);

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }


        template < typename Predicate >
        __CDS_MaybeUnused auto partition (
                Predicate const & predicate
        ) const noexcept -> Pair < LinkedList < ElementType >, LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && PredicateOver < Predicate, ElementType > ) {

            Pair < LinkedList < ElementType >, LinkedList < ElementType > > partitions;

            for ( auto e : * this )
                if ( predicate (e) )
                    partitions.getFirst().add(e);
                else
                    partitions.getSecond().add(e);

            return partitions;
        }

        template < typename IndexedPredicate >
        __CDS_MaybeUnused auto partitionIndexed (
                IndexedPredicate const & indexedPredicate
        ) const noexcept -> Pair < LinkedList < ElementType >, LinkedList < ElementType > >
        __CDS_Requires ( ForwardIterable < C > && IndexedPredicateOver < IndexedPredicate, ElementType > )  {

            Pair < LinkedList < ElementType >, LinkedList < ElementType > > partitions;
            Index i = 0;

            for ( auto e : * this )
                if ( indexedPredicate (i++,e) )
                    partitions.getFirst().add(e);
                else
                    partitions.getSecond().add(e);

            return partitions;
        }

        __CDS_MaybeUnused auto windowed (
                Size            size,
                Size            step            = 1,
                Boolean const & partialWindows  = false
        ) && noexcept -> Sequence < LinkedList < Array < ElementType > > >
        __CDS_Requires ( ForwardIterable < C > ) {

            LinkedList < Array < ElementType > > container;
            Array < ElementType > window;
            auto it = this->begin();


            for ( ; it != this->end(); ) {
                Index i = 0;
                window.resize(size);

                for ( auto wIt = it; wIt != this->end() && i < size; ++wIt ) {
                    window[i++] = wIt.value();
                }

                if ( i == size )
                    container.add(window);
                else if ( partialWindows ) {
                    window.resize(i);
                    container.add(window);
                }

                window.clear();

                for ( i = 0; i < step && it != this->end(); i++ )
                    ++it;
            }

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        __CDS_MaybeUnused auto windowed (
                Size            size,
                Size            step            = 1,
                Boolean const & partialWindows  = false
        ) & noexcept -> Sequence < LinkedList < Array < ElementType > > >
        __CDS_Requires ( ForwardIterable < C > ) {

            LinkedList < Array < ElementType > > container;
            Array < ElementType > window;
            auto it = this->begin();


            for ( ; it != this->end(); ) {
                Index i = 0;
                window.resize(size);

                for ( auto wIt = it; wIt != this->end() && i < size; ++wIt ) {
                    window[i++] = wIt.value();
                }

                if ( i == size )
                    container.add(window);
                else if ( partialWindows ) {
                    window.resize(i);
                    container.add(window);
                }

                window.clear();

                for ( i = 0; i < step && it != this->end(); i++ )
                    ++it;
            }

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        template < typename ListTransformer >
        __CDS_MaybeUnused auto windowed (
                ListTransformer const & transformer,
                Size                    size,
                Size                    step            = 1,
                Boolean         const & partialWindows  = false
        ) && noexcept -> Sequence < LinkedList < meta :: ReturnOf < ListTransformer > > >
        __CDS_Requires ( ForwardIterable < C > && TransformerOver < ListTransformer, List < ElementType > > )  {

            LinkedList < meta :: ReturnOf < ListTransformer > > container;
            utility :: hidden :: sequenceImpl :: Windowed :: type < ListTransformer > window;

            auto it = this->begin();
            for (; it != this->end();) {
                Index i = 0;
                for (auto wIt = it; wIt != this->end() && i < size; ++wIt) {
                    window.add(wIt.value());
                }

                if (i == size || partialWindows)
                    container.add(transformer(window));

                window.clear();
                for (i = 0; i < step && it != this->end(); i++)
                    ++it;
            }

            return std::move(Sequence<decltype(container)>(std::move(container)));
        }

        template < typename ListTransformer >
        __CDS_MaybeUnused auto windowed (
                ListTransformer const & transformer,
                Size                    size,
                Size                    step            = 1,
                Boolean         const & partialWindows  = false
        ) & noexcept -> Sequence < LinkedList < meta :: ReturnOf < ListTransformer > > >
        __CDS_Requires ( ForwardIterable < C > && TransformerOver < ListTransformer, List < ElementType > > ) {

            LinkedList < meta :: ReturnOf < ListTransformer > > container;
            utility :: hidden :: sequenceImpl :: Windowed :: type < ListTransformer > window;

            auto it = this->begin();
            for (; it != this->end();) {
                Index i = 0;
                for (auto wIt = it; wIt != this->end() && i < size; ++wIt) {
                    window.add(wIt.value());
                }

                if (i == size || partialWindows)
                    container.add(transformer(window));

                window.clear();
                for (i = 0; i < step && it != this->end(); i++)
                    ++it;
            }

            return std::move(Sequence<decltype(container)>(std::move(container)));
        }

        template < typename OC >
        __CDS_MaybeUnused auto zip (
                Sequence < OC > const & other
        ) && noexcept -> Sequence < LinkedList < Pair < ElementType, typename Sequence < OC > :: ElementType > > >
        __CDS_Requires ( ForwardIterable < C > && ForwardIterable < OC > ) {

            auto it1 = this->begin();
            auto it2 = other.begin();

            LinkedList < Pair < decltype(it1.value()), decltype(it2.value()) > > container;

            for (; it1 != this->end() && it2 != other.end(); ++ it1, ++ it2 )
                container.add ( { it1.value(), it2.value() } );

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        template < typename OC >
        __CDS_MaybeUnused auto zip (
                Sequence < OC > const & other
        ) & noexcept -> Sequence < LinkedList < Pair < ElementType, typename Sequence < OC > :: ElementType > > >
        __CDS_Requires ( ForwardIterable < C > && ForwardIterable < OC > ) {

            auto it1 = this->begin();
            auto it2 = other.begin();

            LinkedList < Pair < decltype(it1.value()), decltype(it2.value()) > > container;

            for (; it1 != this->end() && it2 != other.end(); ++ it1, ++ it2 )
                container.add ( { it1.value(), it2.value() } );

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        template < typename OC, typename Transformer >
        __CDS_MaybeUnused auto zip (
                Sequence < OC > const & other,
                Transformer     const & transformer
        ) && noexcept -> Sequence < LinkedList < meta :: ReturnOf < Transformer > > >
        __CDS_Requires (
                ForwardIterable < C > &&
                ForwardIterable < OC > &&
                TransformerOver < Transformer, ElementType, typename OC :: ElementType >
        ) {

            auto it1 = this->begin();
            auto it2 = other.begin();

            LinkedList < meta :: ReturnOf < Transformer > > container;

            for (; it1 != this->end() && it2 != other.end(); ++ it1, ++ it2 )
                container.add ( transformer( it1.value(), it2.value() ) );

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        template < typename OC, typename Transformer >
        __CDS_MaybeUnused auto zip (
                Sequence < OC > const & other,
                Transformer     const & transformer
        ) & noexcept -> Sequence < LinkedList < meta :: ReturnOf < Transformer > > >
        __CDS_Requires (
                ForwardIterable < C > &&
                ForwardIterable < OC > &&
                TransformerOver < Transformer, ElementType, typename OC :: ElementType >
        ) {

            auto it1 = this->begin();
            auto it2 = other.begin();

            LinkedList < meta :: ReturnOf < Transformer > > container;

            for (; it1 != this->end() && it2 != other.end(); ++ it1, ++ it2 )
                container.add ( transformer( it1.value(), it2.value() ) );

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }


        __CDS_MaybeUnused auto zipWithNext () && noexcept -> Sequence < LinkedList < Pair < ElementType, ElementType > > >
        __CDS_Requires ( ForwardIterable < C > ) {

            LinkedList < Pair < ElementType, ElementType > > container;

            auto it = this->begin();
            auto v = it.value();

            for ( it.next(); it != this->end(); ++ it ) {
                container.add ( { v, it.value() } );
                v = it.value();
            }

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        template < typename Transformer >
        __CDS_MaybeUnused auto zipWithNext (
                Transformer const & transformer
        ) && noexcept -> Sequence < LinkedList < meta :: ReturnOf < Transformer > > >
        __CDS_Requires ( ForwardIterable < C > && TransformerOver < Transformer, ElementType, ElementType > ) {

            LinkedList < meta :: ReturnOf < Transformer > > container;

            auto it = this->begin();
            auto v = it.value();

            for ( it.next(); it != this->end(); ++ it ) {
                container.add ( transformer ( v, it.value() ) );
                v = it.value();
            }

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        __CDS_MaybeUnused auto zipWithNext () & noexcept -> Sequence < LinkedList < Pair < ElementType, ElementType > > >
        __CDS_Requires ( ForwardIterable < C > ) {

            LinkedList < Pair < ElementType, ElementType > > container;

            auto it = this->begin();
            auto v = it.value();

            for ( it.next(); it != this->end(); ++ it ) {
                container.add ( { v, it.value() } );
                v = it.value();
            }

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        template < typename Transformer >
        __CDS_MaybeUnused auto zipWithNext (
                Transformer const & transformer
        ) & noexcept -> Sequence < LinkedList < meta :: ReturnOf < Transformer > > >
        __CDS_Requires ( ForwardIterable < C > && TransformerOver < Transformer, ElementType, ElementType > ) {

            LinkedList < meta :: ReturnOf < Transformer > > container;

            auto it = this->begin();
            auto v = it.value();

            for ( it.next(); it != this->end(); ++ it ) {
                container.add ( transformer ( v, it.value() ) );
                v = it.value();
            }

            return std::move ( Sequence < decltype ( container ) > ( std::move ( container ) ) );
        }

        __CDS_NoDiscard __CDS_MaybeUnused auto shuffled () const noexcept -> Sequence < Array < ElementType > >
        __CDS_Requires ( ForwardIterable < C > ) {

            Array < ElementType > container;
            for ( auto e : * this )
                container.add( e );

            for ( auto _ : Range(Int::random(container.size(), container.size() * 2), Int::random(container.size() * 3, container.size() * 10)) )
                std :: swap ( container[Int::random(0, container.size() - 1)], container[Int::random(0, container.size() - 1)] );

            return std :: move ( Sequence < Array < ElementType > > ( std :: move ( container ) ) );
        }
    };

}

/// region Ctors Dtors Copy Move Clear

#if !defined(_MSC_VER)

template < typename C >
__CDS_OptimalInline cds :: Sequence < C > ::Sequence ( cds :: Sequence < C > const & s ) noexcept :
        pCollection ( cds :: Memory::instance().create < ForeignPointer < meta :: RemoveReference < decltype (s.pCollection.valueAt().valueAt() ) > > > ( s.pCollection.valueAt().get() ) ),
        chainCount ( s.chainCount ),
        storedMappers ( s.storedMappers ),
        storedPredicates ( s.storedPredicates ),
        storedIndexedMappers ( s.storedIndexedMappers ),
        storedIndexedPredicates ( s.storedIndexedPredicates ){

}

#else

template < typename C >
__CDS_OptimalInline cds :: Sequence < C > :: Sequence(cds :: Sequence < C > const & s) noexcept :
 //   pCollection(Memory::instance().create < ForeignPointer < typename std::remove_reference < decltype (s.pCollection.valueAt().valueAt()) > ::type > >(s.pCollection.valueAt().get())),
    chainCount(s.chainCount),
    storedMappers(s.storedMappers),
    storedPredicates(s.storedPredicates),
    storedIndexedMappers(s.storedIndexedMappers),
    storedIndexedPredicates(s.storedIndexedPredicates) {

    using TypeOf = cds :: RemoveReference < decltype (s.pCollection.valueAt().valueAt()) >;
    auto collection = s.pCollection.valueAt().get();

    this->pCollection = cds :: Memory::instance().create < ForeignPointer < TypeOf > >(collection);
}

#endif

template < typename C >
__CDS_OptionalInline cds :: Sequence < C > ::Sequence ( cds :: Sequence < C > && s ) noexcept :
        chainCount ( cds :: exchange ( s.chainCount, 0 ) + 1 ),
        storedMappers ( std::move ( s.storedMappers ) ),
        storedPredicates ( std::move ( s.storedPredicates ) ),
        storedIndexedMappers ( std::move ( s.storedIndexedMappers ) ),
        storedIndexedPredicates ( std::move ( s.storedIndexedPredicates ) ) {

#if !defined (_MSC_VER)

    if (dynamic_cast < cds :: UniquePointer < C > *> (s.pCollection.get()) != nullptr)
        this->pCollection = cds :: Memory::instance().create < cds :: UniquePointer < meta :: RemoveReference < decltype (s.pCollection.valueAt().valueAt()) > > >(s.pCollection.valueAt().release());
    else
        this->pCollection = cds :: Memory::instance().create < cds :: ForeignPointer < meta :: RemoveReference < decltype (s.pCollection.valueAt().valueAt()) > > >(s.pCollection.valueAt().get());

#else

    /// surpising nobody, MSVC cannot handle complex statements. Either statement commented below is not generated by the template substitution system, or it is skipped in assemby. Not nice.

    using TypeOf = cds :: RemoveReference < decltype (s.pCollection.valueAt().valueAt()) >;

    if (dynamic_cast < cds :: UniquePointer < C > *> (s.pCollection.get()) != nullptr) {
        auto collection = s.pCollection.valueAt().release();
        this->pCollection = Memory::instance().create < cds :: UniquePointer < TypeOf >> (collection);

       // this->pCollection = Memory::instance().create < UniquePointer < typename std::remove_reference < decltype (s.pCollection.valueAt().valueAt()) > ::type > >(s.pCollection.valueAt().release());
    } else {
        auto collection = s.pCollection.valueAt().get();
        this->pCollection = cds :: Memory::instance().create < cds :: ForeignPointer < TypeOf >> (collection);

        // this->pCollection = Memory::instance().create < ForeignPointer < typename std::remove_reference < decltype (s.pCollection.valueAt().valueAt()) > ::type > >(s.pCollection.valueAt().get());
    }

#endif

}

template < typename C >
__CDS_OptimalInline cds :: Sequence < C > ::Sequence ( C & c ) noexcept :
        pCollection ( cds :: Memory :: instance().create < cds :: ForeignPointer < meta :: RemoveReference < decltype ( c ) > > > ( & c ) ),
        chainCount ( 0u ) {

}

template < typename C >
__CDS_OptimalInline cds :: Sequence < C > ::Sequence ( C && c ) noexcept :
        pCollection ( cds :: Memory :: instance().create < cds :: UniquePointer < meta :: RemoveReference < decltype ( c ) > > > ( cds :: Memory :: instance().create < C > (std :: forward < C > (c)) ) ),
        chainCount ( 0u ) {

}

template < typename C >
__CDS_OptionalInline auto cds :: Sequence < C > ::operator = ( cds :: Sequence < C > const & s ) noexcept -> cds :: Sequence < C > & {
    if ( this == & s ) return * this;

    this->clear();

    this->pCollection.reset( cds :: Memory :: instance().create < cds :: ForeignPointer < decltype ( s.pCollection.valueAt().get() ) > > ( s.pCollection.valueAt().valueAt() ) );
    this->chainCount                = s.chainCount;

    this->storedMappers             = s.storedMappers;
    this->storedPredicates          = s.storedPredicates;

    this->storedIndexedMappers      = s.storedIndexedMappers;
    this->storedIndexedPredicates   = s.storedIndexedPredicates;

    return * this;
}

template < typename C >
__CDS_OptionalInline auto cds :: Sequence < C > ::operator = ( cds :: Sequence < C > && s ) noexcept -> cds :: Sequence < C > & {
    if ( this == & s ) return * this;

    this->clear();

    this->pCollection.reset( cds :: Memory :: instance().create < cds :: UniquePointer < decltype ( s.pCollection.valueAt().get() ) > > ( s.pCollection.valueAt().release() ) );
    this->chainCount                = cds :: exchange ( s.chainCount, 0 ) + 1;

    this->storedMappers             = std::move (s.storedMappers);
    this->storedPredicates          = std::move (s.storedPredicates);

    this->storedIndexedMappers      = std::move (s.storedIndexedMappers);
    this->storedIndexedPredicates   = std::move (s.storedIndexedPredicates);

    return * this;
}

template < typename C >
__CDS_OptionalInline auto cds :: Sequence < C > ::clear() noexcept -> void {
    this->pCollection.reset();
    this->chainCount = 0;

    this->storedMappers.clear();
    this->storedPredicates.clear();

    this->storedIndexedMappers.clear();
    this->storedIndexedPredicates.clear();
}

/// endregion

/// region Iterator Support

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > ::begin() noexcept -> cds :: Sequence < C > :: Iterator {
    return cds :: Sequence < C > :: Iterator ( this, this->pCollection.valueAt().valueAt().begin() );
}

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > ::end() noexcept -> cds :: Sequence < C > :: Iterator {
    return cds :: Sequence < C > :: Iterator ( this, this->pCollection.valueAt().valueAt().end() );
}

template < typename C >
__CDS_OptimalInline cds :: Sequence < C > :: Iterator :: Iterator ( cds :: Sequence < C > * pSequence, cds :: Sequence < C > :: Iterator :: CollectionIterator const & it) noexcept :
        pSeq ( pSequence ),
        it (it) {

    this->skipFiltered();
}

template < typename C >
auto cds :: Sequence < C >::Iterator::skipFiltered() noexcept -> void {
    cds :: Boolean skip = true;

    while ( skip && this->it != this->pSeq->pCollection->valueAt().end() ) {
        this->precomputed = cds :: Memory :: instance().create < CollectionElementType > ( * this->it );
        skip = false;

        auto currentMapperIterator = this->pSeq.valueAt().storedMappers.begin();
        auto currentFilterIterator = this->pSeq.valueAt().storedPredicates.begin();

        auto currentIndexedMapperIterator = this->pSeq.valueAt().storedIndexedMappers.begin();
        auto currentIndexedFilterIterator = this->pSeq.valueAt().storedIndexedPredicates.begin();

        for ( cds :: uint32 i = 0; i < this->pSeq.valueAt().chainCount; i ++ ) {

            if (
                    currentMapperIterator != this->pSeq.valueAt().storedMappers.end() &&
                    ( * currentMapperIterator ).getSecond() == i
            ) {
                * this->precomputed = ( * ( * currentMapperIterator ).getFirst() ) ( * this->precomputed );
                ++ currentMapperIterator;

            } else if (
                    currentIndexedMapperIterator != this->pSeq.valueAt().storedIndexedMappers.end() &&
                    ( * currentIndexedMapperIterator ).getSecond() == i
            ) {
                * this->precomputed = ( * ( * currentIndexedMapperIterator ).getFirst() ) (
                        this->index,
                        * this->precomputed
                );

                ++ currentIndexedMapperIterator;

            } else if (
                    currentFilterIterator != this->pSeq.valueAt().storedPredicates.end() &&
                    ( * currentFilterIterator ).getSecond() == i
            ) {
                if ( ! (* ( * currentFilterIterator ).getFirst())( * this->precomputed ) ) {
                    skip = true;
                    break;
                }

                ++ currentFilterIterator;

            } else if (
                    currentIndexedFilterIterator != this->pSeq.valueAt().storedIndexedPredicates.end() &&
                    ( * currentIndexedFilterIterator ).getSecond() == i
            ) {
                if ( ! ( * ( * currentIndexedFilterIterator).getFirst()) (this->index, * this->precomputed) ) {
                    skip = true;
                    break;
                }

                ++ currentIndexedFilterIterator;

            } else if (
                    currentFilterIterator           == this->pSeq.valueAt().storedPredicates.end()      &&
                    currentMapperIterator           == this->pSeq.valueAt().storedMappers.end()         &&
                    currentIndexedMapperIterator    == this->pSeq.valueAt().storedIndexedMappers.end()  &&
                    currentIndexedFilterIterator    == this->pSeq.valueAt().storedIndexedPredicates.end()
            )
                break;
        }

        if ( ! skip ) {

            for ( cds :: Index i = 0; i < this->pSeq.valueAt().chainCount; i++ ) {
                if (
                        currentMapperIterator != this->pSeq.valueAt().storedMappers.end() &&
                        ( * currentMapperIterator ).getSecond() == i
                ) {
                    * this->precomputed = ( * ( * currentMapperIterator ).getFirst())(* this->precomputed);
                    ++ currentMapperIterator;
                } else if (
                        currentIndexedMapperIterator != this->pSeq.valueAt().storedIndexedMappers.end() &&
                        ( * currentIndexedMapperIterator ).getSecond() == i
                ) {
                    * this->precomputed = (* ( * currentIndexedMapperIterator ).getFirst())(
                            this->index,
                            * this->precomputed
                    );

                    ++ currentIndexedMapperIterator;
                }
            }

        }
        else {
            ++ this->it;
        }

        this->index ++;
    }
}

#include <sstream>

#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_17

template < typename C >
auto cds :: Sequence < C > :: Iterator :: toString() const noexcept -> cds :: String {
    std::stringstream oss;
    oss << "Sequence::Iterator { pSequence = " << this->pSeq.toString();

    if __CDS_cpplang_IfConstexpr ( meta :: isPrintable < decltype ( this->it ) > () ) {
        oss << ", it = " << this->it;
    } else {
        oss << ", value = " << * this->it;
    }

    oss << " }";
    return oss.str();
}

template < typename C >
__CDS_OptionalInline auto cds :: Sequence < C > ::Iterator::hash() const noexcept -> cds :: Index {
    if __CDS_cpplang_IfConstexpr ( meta :: isObjectDerived < decltype ( this->it ) > () )
        return this->it.hash ();
    else if __CDS_cpplang_IfConstexpr ( meta :: isObjectDerived < decltype ( * this->it ) > () )
        return (* this->it).hash ();
    else
        return 0;

}

#else

#endif

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > :: Iterator :: equals ( cds :: Object const & o) const noexcept -> bool {
    if ( this == & o ) return true;
    auto p = dynamic_cast < decltype ( this ) > ( & o );
    if ( p == nullptr ) return false;

    return this->equals( * p );
}

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > :: Iterator :: value() const noexcept -> cds :: Sequence < C > :: Iterator :: CollectionElementType {
    return * this->precomputed;
}

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > ::Iterator::next() noexcept -> cds :: Sequence < C > :: Iterator & {
    ++ this->it;
    this->skipFiltered();
    return * this;
}

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > :: Iterator :: equals ( cds :: Sequence < C > :: Iterator const & otherIt) const noexcept -> cds :: Boolean {
    return this->it == otherIt.it;
}

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > :: Iterator :: operator== ( cds :: Sequence < C > :: Iterator const & otherIt) const noexcept -> bool {
    return this->equals (otherIt);
}

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > :: Iterator :: operator!= ( cds :: Sequence < C > :: Iterator const & otherIt) const noexcept -> bool {
    return ! this->equals (otherIt);
}

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > :: Iterator :: operator++() noexcept -> cds :: Sequence < C > :: Iterator & {
    return this->next();
}

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > :: Iterator :: operator++(int) noexcept -> cds :: Sequence < C > :: Iterator {
    auto c = * this; this->next(); return c;
}

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > :: Iterator :: operator*() const noexcept -> cds :: Sequence < C > :: Iterator :: CollectionElementType {
    return this->value();
}

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > :: begin() const noexcept -> cds :: Sequence < C > :: ConstIterator {
    return cds :: Sequence < C > :: ConstIterator ( this, this->pCollection.valueAt().valueAt().cbegin() );
}

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > :: end() const noexcept -> cds :: Sequence < C > :: ConstIterator {
    return cds :: Sequence < C > :: ConstIterator ( this, this->pCollection.valueAt().valueAt().cend() );
}

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > :: cbegin() const noexcept -> cds :: Sequence < C > :: ConstIterator {
    return cds :: Sequence < C > :: ConstIterator ( this, this->pCollection.valueAt().valueAt().cbegin() );
}

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > :: cend() const noexcept -> cds :: Sequence < C > :: ConstIterator {
    return cds :: Sequence < C > :: ConstIterator ( this, this->pCollection.valueAt().valueAt().cend() );
}

template < typename C >
__CDS_OptimalInline cds :: Sequence < C > :: ConstIterator :: ConstIterator (
        cds :: Sequence < C >                                           const * pSequence,
        cds :: Sequence < C > :: ConstIterator :: CollectionIterator    const & it
) noexcept :
        pSeq ( pSequence ),
        it (it) {

    this->skipFiltered();
}

template < typename C >
auto cds :: Sequence < C > :: ConstIterator :: skipFiltered() noexcept -> void {
    cds :: Boolean skip = true;

    while ( skip && this->it != this->pSeq->pCollection->valueAt().cend() ) {
        this->precomputed = cds :: Memory :: instance().create < cds :: Sequence < C > :: ConstIterator :: CollectionElementType > ( * this->it );
        skip = false;

        auto currentMapperIterator = this->pSeq.valueAt().storedMappers.begin();
        auto currentFilterIterator = this->pSeq.valueAt().storedPredicates.begin();

        auto currentIndexedMapperIterator = this->pSeq.valueAt().storedIndexedMappers.begin();
        auto currentIndexedFilterIterator = this->pSeq.valueAt().storedIndexedPredicates.begin();

        for ( cds :: uint32 i = 0; i < this->pSeq.valueAt().chainCount; i ++ ) {

            if (
                    currentMapperIterator != this->pSeq.valueAt().storedMappers.end() &&
                    ( * currentMapperIterator ).getSecond() == i
            ) {
                * this->precomputed = ( * ( * currentMapperIterator ).getFirst() ) ( * this->precomputed );
                ++ currentMapperIterator;

            } else if (
                    currentIndexedMapperIterator != this->pSeq.valueAt().storedIndexedMappers.end() &&
                    ( * currentIndexedMapperIterator ).getSecond() == i
            ) {
                * this->precomputed = ( * ( * currentIndexedMapperIterator ).getFirst() ) (
                        this->index,
                        * this->precomputed
                );

                ++ currentIndexedMapperIterator;

            } else if (
                    currentFilterIterator != this->pSeq.valueAt().storedPredicates.end() &&
                    ( * currentFilterIterator ).getSecond() == i
            ) {
                if ( ! ( * ( * currentFilterIterator ).getFirst())( * this->precomputed ) ) {
                    skip = true;
                    break;
                }

                ++ currentFilterIterator;

            } else if (
                    currentIndexedFilterIterator != this->pSeq.valueAt().storedIndexedPredicates.end() &&
                    ( * currentIndexedFilterIterator ).getSecond() == i
            ) {
                if ( ! (* ( * currentIndexedFilterIterator ).getFirst()) (this->index, * this->precomputed) ) {
                    skip = true;
                    break;
                }

                ++ currentIndexedFilterIterator;

            } else if (
                    currentFilterIterator           == this->pSeq.valueAt().storedPredicates.end()      &&
                    currentMapperIterator           == this->pSeq.valueAt().storedMappers.end()         &&
                    currentIndexedMapperIterator    == this->pSeq.valueAt().storedIndexedMappers.end()  &&
                    currentIndexedFilterIterator    == this->pSeq.valueAt().storedIndexedPredicates.end()
            )
                break;
        }

        if ( ! skip ) {

            for ( cds :: Index i = 0; i < this->pSeq.valueAt().chainCount; i++ ) {
                if (
                        currentMapperIterator != this->pSeq.valueAt().storedMappers.end() &&
                        ( * currentMapperIterator ).getSecond() == i
                ) {
                    * this->precomputed = ( * ( * currentMapperIterator ).getFirst())( * this->precomputed);
                    ++ currentMapperIterator;
                } else if (
                        currentIndexedMapperIterator != this->pSeq.valueAt().storedIndexedMappers.end() &&
                        ( * currentIndexedMapperIterator ).getSecond() == i
                ) {
                    * this->precomputed = ( * ( * currentIndexedMapperIterator ).getFirst())(
                            this->index,
                            * this->precomputed
                    );

                    ++ currentIndexedMapperIterator;
                }
            }

        }
        else {
            ++ this->it;
        }

        this->index ++;
    }
}

#include <sstream>

#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_17


template < typename C >
auto cds :: Sequence < C > :: ConstIterator :: toString() const noexcept -> cds :: String {
    std::stringstream oss;
    oss << "Sequence::Iterator { pSequence = " << this->pSeq.toString();

    if __CDS_cpplang_IfConstexpr ( meta :: isPrintable < decltype ( this->it ) > () ) {
        oss << ", it = " << this->it;
    } else {
        oss << ", value = " << * this->it;
    }

    oss << " }";
    return oss.str();
}

#else

#endif

#if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_17

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > :: ConstIterator :: hash() const noexcept -> cds :: Index {
    if __CDS_cpplang_IfConstexpr( meta :: isObjectDerived < decltype ( this->it ) > () )
        return this->it.hash ();
    else if __CDS_cpplang_IfConstexpr ( meta :: isObjectDerived < decltype ( * this->it ) > () )
        return (* this->it).hash ();
    else
        return 0;

}

#else

#endif

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > :: ConstIterator :: equals ( cds :: Object const & o ) const noexcept -> bool {
    if ( this == & o ) return true;
    auto p = dynamic_cast < decltype ( this ) > ( & o );
    if ( p == nullptr ) return false;

    return this->equals( * p );
}

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > :: ConstIterator :: value() const noexcept -> cds :: Sequence < C > :: ConstIterator :: CollectionElementType {
    return * this->precomputed;
}

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > :: ConstIterator :: next() noexcept -> cds :: Sequence < C > :: ConstIterator & {
    ++ this->it;
    this->skipFiltered();
    return * this;
}

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > :: ConstIterator :: equals ( cds :: Sequence < C > :: ConstIterator const & otherIt ) const noexcept -> cds :: Boolean {
    return this->it == otherIt.it;
}

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > :: ConstIterator :: operator== ( cds :: Sequence < C > :: ConstIterator const & otherIt) const noexcept -> bool {
    return this->equals (otherIt);
}

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > :: ConstIterator :: operator!= ( cds :: Sequence < C > :: ConstIterator const & otherIt) const noexcept -> bool {
    return ! this->equals (otherIt);
}

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > :: ConstIterator :: operator++() noexcept -> cds :: Sequence < C > :: ConstIterator & {
    return this->next();
}

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > :: ConstIterator :: operator++(int) noexcept -> cds :: Sequence < C > :: ConstIterator {
    auto c = * this; this->next(); return c;
}

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > :: ConstIterator :: operator*() const noexcept -> cds :: Sequence < C > :: ConstIterator :: CollectionElementType {
    return this->value();
}

/// endregion

/// region Object Derived Functions

template < typename C >
auto cds :: Sequence < C > ::toString() const noexcept -> cds :: String {
    std::stringstream oss;

    oss << "Sequence { chainCount = "
        << this->chainCount
        << ", elements = [ ";

    for ( auto e : * this )
        if __CDS_cpplang_IfConstexpr ( meta :: isPrintable < ElementType > () )
            oss << e << ", ";
        else
            oss << "Object at 0x" << std::hex << reinterpret_cast < AddressValueType > ( & e ) << ", ";

    auto s = oss.str();
    return s.replace(s.size() - 2, 2, "").append(" ]}");
}

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > ::hash() const noexcept -> cds :: Index {
    return this->pCollection.valueAt().hash();
}

template < typename C >
__CDS_OptimalInline auto cds :: Sequence < C > :: equals ( cds :: Object const & o ) const noexcept -> bool {
    if ( this == & o ) return true;
    auto p = dynamic_cast < decltype ( this ) > (& o);
    if ( p == nullptr ) return false;

    return this->pCollection == p->pCollection;
}


/// endregion

/// region template deduction

#if __CDS_cpplang_CTAD_available == true

namespace cds {

    Sequence ( String ) -> Sequence < String >;

    template < typename T >
    Sequence ( Array < T > & ) -> Sequence < Array < T > >;

    template < typename T >
    Sequence ( Array < T > const & ) -> Sequence < Array < T > const >;

    template < typename T >
    Sequence ( Array < T > && ) -> Sequence < Array < T > >;

    template < typename T >
    Sequence ( DoubleLinkedList < T > & ) -> Sequence < DoubleLinkedList < T > >;

    template < typename T >
    Sequence ( DoubleLinkedList < T > const & ) -> Sequence < DoubleLinkedList < T > const >;

    template < typename T >
    Sequence ( DoubleLinkedList < T > && ) -> Sequence < DoubleLinkedList < T > >;

    template < typename T, typename C >
    Sequence ( OrderedSet < T, C > & ) -> Sequence < OrderedSet < T, C > >;

    template < typename T, typename C >
    Sequence ( OrderedSet < T, C > const & ) -> Sequence < OrderedSet < T, C > const >;

    template < typename T, typename C >
    Sequence ( OrderedSet < T, C > && ) -> Sequence < OrderedSet < T, C > >;

    template < typename T >
    Sequence ( UnorderedSet < T > & ) -> Sequence < UnorderedSet < T > >;

    template < typename T >
    Sequence ( UnorderedSet < T > const & ) -> Sequence < UnorderedSet < T > const >;

    template < typename T >
    Sequence ( UnorderedSet < T > && ) -> Sequence < UnorderedSet < T > >;

    template < typename K, typename V >
    Sequence ( HashMap < K, V > & ) -> Sequence < HashMap < K, V > >;

    template < typename K, typename V >
    Sequence ( HashMap < K, V > const & ) -> Sequence < HashMap < K, V > const >;

    template < typename K, typename V >
    Sequence ( HashMap < K, V > && ) -> Sequence < HashMap < K, V > >;

    class JSON;
    Sequence ( JSON const & ) -> Sequence < JSON const >;

}

#include <CDS/Generator>

namespace cds {

    template < typename T, typename ... Args >
    Sequence ( Generator < T, Args ... > const & ) -> Sequence < Generator < T, Args ... > const >;

}

#include <CDS/Range>

namespace cds {

    Sequence ( Range && ) -> Sequence < Range >;

}

#include <CDS/Range>

namespace cds {

    Sequence ( Range const & ) -> Sequence < Range const >;

}

#include <CDS/Range>

namespace cds {

    Sequence ( Range & ) -> Sequence < Range >;

}

#endif

/// endregion

inline auto cds :: Range :: sequence() & noexcept -> cds :: Sequence < cds :: Range > {
    return cds :: Sequence < meta :: RemoveReference < decltype (*this) > > (*this);
}

inline auto cds :: Range :: sequence() const & noexcept -> cds :: Sequence < cds :: Range const > {
    return cds :: Sequence < meta :: RemoveReference < decltype (*this) > > (*this);
}

inline auto cds :: Range :: sequence() && noexcept -> cds :: Sequence < cds :: Range > {
    return cds :: Sequence < meta :: RemoveReference < decltype (* this) > > (std::move(* this));
}

inline auto cds :: Range :: sequence() const && noexcept -> cds :: Sequence < cds :: Range const > {
    return cds :: Sequence < meta :: RemoveReference < decltype (* this) > > (std::move(* this));
}

inline auto cds :: String :: sequence () const & noexcept -> cds :: Sequence < cds :: String const > {
    return cds :: Sequence < meta :: RemoveReference < decltype (*this) > > (*this);
}

inline auto cds :: String :: sequence () & noexcept -> cds :: Sequence < cds :: String > {
    return cds :: Sequence < meta :: RemoveReference < decltype (*this) > > (*this);
}

inline auto cds :: String :: sequence () const && noexcept -> cds :: Sequence < cds :: String const > {
    return cds :: Sequence < meta :: RemoveReference < decltype (* this) > > (std::move(* this));
}

inline auto cds :: String :: sequence () && noexcept -> cds :: Sequence < cds :: String > {
    return cds :: Sequence < meta :: RemoveReference < decltype (* this) > > (std::move(* this));
}

namespace cds {

    template <class T>
    auto UnorderedSet<T>::sequence() const & noexcept -> Sequence < UnorderedSet<T> const > {
        return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
    }

    template <class T>
    auto UnorderedSet<T>::sequence() & noexcept -> Sequence<UnorderedSet<T>> {
        return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
    }
    template <class T>
    auto UnorderedSet<T>::sequence() const && noexcept -> Sequence < UnorderedSet<T> const > {
        return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (std::move(*this));
    }

    template <class T>
    auto UnorderedSet<T>::sequence() && noexcept -> Sequence<UnorderedSet<T>> {
        return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (std::move(*this));
    }

}

namespace cds {

    template <class T, class C> __CDS_Requires ( ValidSetComparator <T, C> )
    auto OrderedSet<T, C>::sequence() const & noexcept -> Sequence < OrderedSet < T, C > const > {
        return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
    }

    template <class T, class C> __CDS_Requires ( ValidSetComparator <T, C> )
    auto OrderedSet<T, C>::sequence() & noexcept -> Sequence < OrderedSet < T, C > > {
        return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
    }

    template <class T, class C> __CDS_Requires ( ValidSetComparator <T, C> )
    auto OrderedSet<T, C>::sequence() const && noexcept -> Sequence < OrderedSet < T, C > const > {
        return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (std::move(*this));
    }

    template <class T, class C> __CDS_Requires ( ValidSetComparator <T, C> )
    auto OrderedSet<T, C>::sequence() && noexcept -> Sequence < OrderedSet < T, C > > {
        return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (std::move(*this));
    }

}

#if defined(CDS_HASHSET_HPP) && !defined(CDS_HASHSET_SEQUENCE)
#define CDS_HASHSET_SEQUENCE

namespace cds {

    template < typename T, typename H > __CDS_Requires (
            UniqueIdentifiable < T > &&
            HashCalculatorHasBoundaryFunction < H >
    ) auto HashSet < T, H > :: sequence () const & noexcept -> Sequence < HashSet const > {
        return Sequence < RemoveReference < decltype ( * this ) > > ( * this );
    }

    template < typename T, typename H > __CDS_Requires (
            UniqueIdentifiable < T > &&
            HashCalculatorHasBoundaryFunction < H >
    ) auto HashSet < T, H > :: sequence () & noexcept -> Sequence < HashSet > {
        return Sequence < RemoveReference < decltype ( * this ) > > ( * this );
    }

    template < typename T, typename H > __CDS_Requires (
            UniqueIdentifiable < T > &&
            HashCalculatorHasBoundaryFunction < H >
    ) auto HashSet < T, H > :: sequence () const && noexcept -> Sequence < HashSet const > {
        return Sequence < RemoveReference < decltype ( * this ) > > ( std :: move ( * this ) );
    }

    template < typename T, typename H > __CDS_Requires (
            UniqueIdentifiable < T > &&
            HashCalculatorHasBoundaryFunction < H >
    ) auto HashSet < T, H > :: sequence () && noexcept -> Sequence < HashSet > {
        return Sequence < RemoveReference < decltype ( * this ) > > ( std :: move ( * this ) );
    }

}

#endif

#if defined(CDS_STATICARRAY_HPP) && !defined(CDS_STATICARRAY_SEQUENCE)
#define CDS_STATICARRAY_SEQUENCE

namespace cds {

    template < typename T, Size capacity >
    auto StaticArray < T, capacity > :: sequence () const & noexcept -> Sequence < StaticArray < T, capacity > const > {
        return Sequence < RemoveReference < decltype ( * this ) > > ( * this );
    }

    template < typename T, Size capacity >
    auto StaticArray < T, capacity > :: sequence () & noexcept -> Sequence < StaticArray < T, capacity > > {
        return Sequence < RemoveReference < decltype ( * this ) > > ( * this );
    }

    template < typename T, Size capacity >
    auto StaticArray < T, capacity > :: sequence () const && noexcept -> Sequence < StaticArray < T, capacity > const > {
    return Sequence < RemoveReference < decltype ( * this ) > > ( std :: move ( * this ) );
    }

    template < typename T, Size capacity >
    auto StaticArray < T, capacity > :: sequence () && noexcept -> Sequence < StaticArray < T, capacity > > {
        return Sequence < RemoveReference < decltype ( * this ) > > ( std :: move ( * this ) );
    }

}

#endif


__CDS_Meta_RegisterParseTemplateType(Sequence)

#include "../experimental/shared/array/impl/ArraySequence.hpp"
#include "../experimental/shared/string/impl/StringSequence.hpp"
#include "../experimental/shared/string/view/impl/StringViewSequence.hpp"

#endif //CDS_SEQUENCE_HPP