//
// Created by loghin on 25.01.2021.
//

#ifndef CDS_SET_HPP
#define CDS_SET_HPP

#include <CDS/Collection>

namespace cds {

    template < typename T > __CDS_Requires( UniqueIdentifiable < T > )
    class Set : public Collection < T > {
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
        auto __CDS_OptimalInline remove ( const T & e, Size ) noexcept -> bool final { return this->remove(e); }
        auto __CDS_OptimalInline removeAll ( const T & o ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeFirst ( const T & o ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeLast ( const T & o ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeOf ( const Collection<T> &, Size ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeFirstOf ( const Collection<T> & o ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeAllOf ( const Collection<T> & o ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeLastOf ( const Collection<T> & ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeNotOf ( const Collection<T> &, Size ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeFirstNotOf ( const Collection<T> & o ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeAllNotOf ( const Collection<T> & o ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeLastNotOf ( const Collection<T> & ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeOf ( const std::initializer_list<T> &, Size ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeFirstOf ( const std::initializer_list<T> & o ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeAllOf ( const std::initializer_list<T> & o ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeLastOf ( const std::initializer_list<T> & ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeNotOf ( const std::initializer_list<T> &, Size ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeFirstNotOf ( const std::initializer_list<T> & o ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeAllNotOf ( const std::initializer_list<T> & o ) noexcept -> bool final { return false; }
        auto __CDS_OptimalInline removeLastNotOf ( const std::initializer_list<T> & ) noexcept -> bool final { return false; }
        auto makeUnique () noexcept -> void final { }

    public:
        virtual auto remove ( ElementCRef ) noexcept -> bool = 0;
        auto clear () noexcept -> void override = 0;
        __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto size () const noexcept -> Size override = 0;

        template < typename V = T, EnableIf < Type < V > :: copyConstructible > = 0 >
        __CDS_OptimalInline auto insert ( ElementCRef e ) noexcept -> void {
            return this->add(e);
        }

        template < typename V = T, EnableIf < Type < V > :: moveConstructible > = 0 >
        __CDS_OptimalInline auto insert ( ElementMRef e ) noexcept -> void {
            return this->add(e);
        }

        __CDS_NoDiscard auto toString() const noexcept -> String final {
            if ( this->empty() )
                return {"{ }"};

            std::stringstream out;
            out << "{ ";

            for ( ElementCRef e : (*this) )
                Type < T > ::streamPrint( out, e ) << ", ";

            auto s = out.str();
            return {s.substr(0, s.length() - 2).append(" }")};
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
