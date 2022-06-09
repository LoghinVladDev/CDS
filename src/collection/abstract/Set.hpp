//
// Created by loghin on 25.01.2021.
//

#ifndef CDS_SET_HPP
#define CDS_SET_HPP

#include <CDS/Collection>

namespace cds {

    template < typename T > __CDS_Requires( UniqueIdentifiable < T > )
    class Set : public Collection < T > { // NOLINT(cppcoreguidelines-virtual-class-destructor)
    public:
        using ElementType               = typename Collection < T > :: ElementType;

    protected:
        using ElementRef                = typename Collection < T > :: ElementRef;
        using ElementCRef               = typename Collection < T > :: ElementCRef;
        using ElementMRef               = typename Collection < T > :: ElementMRef;
        using ElementPtr                = typename Collection < T > :: ElementPtr;
        using ElementPtrRef             = typename Collection < T > :: ElementPtrRef;
        using ElementCPtr               = typename Collection < T > :: ElementCPtr;
        using InitializerList           = typename Collection < T > :: InitializerList;

    public:
        using Iterator                  = typename Collection < T > :: Iterator;
        using ConstIterator             = typename Collection < T > :: ConstIterator;

        using ReverseIterator           = typename Collection < T > :: ReverseIterator;
        using ConstReverseIterator      = typename Collection < T > :: ConstReverseIterator;

    protected:
        using DelegateIterator          = typename Collection < T > :: DelegateIterator;
        using DelegateConstIterator     = typename Collection < T > :: DelegateConstIterator;

        constexpr Set () noexcept = default;

    public:
        __CDS_cpplang_ConstexprDestructor ~Set () noexcept override = default;

    protected:
        auto __CDS_OptimalInline remove (const T & element, Size ) noexcept -> bool final { return this->remove(element); }
        auto __CDS_OptimalInline removeLast ( const T & element ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeOf ( const Collection<T> &, Size ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeLastOf ( const Collection<T> & ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeNotOf ( const Collection<T> &, Size ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeLastNotOf ( const Collection<T> & ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeOf ( const std::initializer_list<T> &, Size ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeLastOf ( const std::initializer_list<T> & ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeNotOf ( const std::initializer_list<T> &, Size ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeLastNotOf ( const std::initializer_list<T> & ) noexcept -> bool final { return false; }

    public:
        virtual auto remove ( ElementCRef ) noexcept -> bool = 0;
        auto clear () noexcept -> void override = 0;
        __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto size () const noexcept -> Size override = 0;

        template < typename V = T, meta :: EnableIf < meta :: isCopyConstructible < V > () > = 0 >
        __CDS_OptimalInline auto insert ( ElementCRef element ) noexcept -> void {
            return this->add(element);
        }

        template < typename V = T, meta :: EnableIf < meta :: isMoveConstructible < V > () > = 0 >
        __CDS_OptimalInline auto insert ( ElementMRef element ) noexcept -> void {
            return this->add(element);
        }

        __CDS_NoDiscard auto toString() const noexcept -> String final {
            if ( this->empty() ) {
                return {"{ }"};
            }

            std::stringstream out;
            out << "{ ";

            for ( ElementCRef element __CDS_MaybeUnused : (*this) ) {
                meta :: print (out, element ) << ", ";
            }

            auto asString = out.str();
            return {asString.substr(0u, asString.length() - 2u).append(" }")};
        }

        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto empty () const noexcept -> bool final {
            return this->size () == 0;
        }
    };

}

#include <CDS/ListSet>
#include <CDS/HashSet>
#include <CDS/Concepts>

#endif //CDS_SET_HPP
