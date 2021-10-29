//
// Created by loghin on 28.10.2021.
//

#ifndef CDS_FUNCTION_HPP
#define CDS_FUNCTION_HPP

#include <tuple>
#include <CDS/Object>
#include <CDS/Utility>
#include <CDS/Traits>

namespace Utility {
    class UndefinedClass;
}

template < typename ReturnType, typename ... ArgumentTypes >
class Function : public Object {};

template < typename ReturnType, typename ... ArgumentTypes >
class Function < ReturnType ( ArgumentTypes ... ) > : public Object {
private:
    using GenericFunctionAddress = void *;

    template < typename FunctionSignature, typename Functor >
    class FunctorHandler;

    template < typename FunctionSignature >
    class SubstitutingStaticHandler;

    using GenericFunctorAddress = void *;
    using GenericConstFunctorAddress = void const *;

    using Invoker = auto (*) ( GenericFunctorAddress, ArgumentTypes && ... ) noexcept ( false ) -> ReturnType;
    using Creator = auto (*) ( GenericConstFunctorAddress ) noexcept -> GenericFunctorAddress;
    using Deleter = auto (*) ( GenericFunctorAddress ) noexcept -> void;

    struct Manager {
        Invoker invoker;
        Creator creator;
        Deleter deleter;
    };

    template < typename SubstitutedReturnType, typename SubstitutedFunctor, typename ... SubstitutedArgumentTypePack >
    class FunctorHandler < SubstitutedReturnType ( SubstitutedArgumentTypePack ... ), SubstitutedFunctor > {
    public:
        using SubstitutedFunctorAddress             = SubstitutedFunctor *;
        using SubstitutedConstFunctorAddress        = SubstitutedFunctor const *;

        __CDS_OptimalInline static auto invoke (
                GenericFunctorAddress pObject,
                SubstitutedArgumentTypePack && ... argumentTypes
        ) noexcept ( false ) -> SubstitutedReturnType {
            static auto pMemberFunction = & SubstitutedFunctor :: operator ();

            return (
                reinterpret_cast < SubstitutedFunctorAddress > ( pObject )
                    ->* pMemberFunction
            ) ( std :: forward < SubstitutedArgumentTypePack > ( argumentTypes ) ... );
        }

        __CDS_OptimalInline static auto clear ( GenericFunctorAddress pObject ) noexcept -> void {
            delete reinterpret_cast < SubstitutedFunctorAddress > ( pObject );
        }

        __CDS_OptimalInline static auto copy ( GenericConstFunctorAddress pObject ) noexcept -> GenericFunctorAddress {
            return reinterpret_cast < GenericFunctorAddress > ( new SubstitutedFunctor (
                * reinterpret_cast < SubstitutedConstFunctorAddress > ( pObject )
            ) );
        }

        constexpr static Manager manager = { invoke, copy, clear };
    };

    template < typename RequestedReturnType, typename ... RequestedArgumentTypes >
    class SubstitutingStaticHandler < RequestedReturnType ( RequestedArgumentTypes ... ) > {
    public:
        __CDS_OptimalInline static auto invoke (
                GenericFunctorAddress pFunction,
                ArgumentTypes && ... argumentTypes
        ) noexcept (false) -> RequestedReturnType {
            auto castedFunction = reinterpret_cast < RequestedReturnType ( * ) ( RequestedArgumentTypes ... ) > ( pFunction );

            return castedFunction ( std :: forward < RequestedArgumentTypes > ( argumentTypes ) ... );
        }

        __CDS_OptimalInline static auto copy ( GenericConstFunctorAddress pFunction ) noexcept -> GenericFunctorAddress {
            return const_cast < GenericFunctorAddress > ( pFunction );
        }

        __CDS_OptimalInline static auto clear ( GenericFunctorAddress ) noexcept -> void {
            /// do nothing
        }

        constexpr static Manager manager { invoke, copy, clear };
    };

    GenericFunctionAddress      pCallableObject { nullptr };
    Manager const             * pManager { nullptr };

    template < typename Functor, EnableIf < Type < Functor > :: isCallableObject > = 0 >
    __CDS_OptimalInline auto initHandler ( Functor const & functor ) noexcept -> void {
        this->pManager = & FunctorHandler < ReturnType ( ArgumentTypes ... ), Functor > :: manager;

        this->pCallableObject = this->pManager->creator ( reinterpret_cast < GenericConstFunctorAddress > ( & functor ) );
    }

    template < typename RequestedReturnType, typename ... RequestedArgumentTypes >
    __CDS_OptimalInline auto initHandler ( RequestedReturnType ( * requestedStaticFunction ) ( RequestedArgumentTypes ... ) ) noexcept -> void {
        this->pManager = & SubstitutingStaticHandler < RequestedReturnType ( RequestedArgumentTypes ... ) > :: manager;

        this->pCallableObject = this->pManager->creator ( reinterpret_cast < GenericFunctorAddress > ( requestedStaticFunction ) );
    }


public:
    constexpr Function () noexcept = default;

    template < typename RequestedReturnType, typename ... RequestedArgumentTypes >
    constexpr Function ( RequestedReturnType (* requestedStaticFunction ) ( RequestedArgumentTypes ... ) ) noexcept { // NOLINT(google-explicit-constructor)
        this->initHandler( requestedStaticFunction );
    }

    template < typename Functor, EnableIf < Type < Functor > :: isCallableObject > = 0 >
    __CDS_OptimalInline Function ( Functor const & functor ) noexcept { // NOLINT(google-explicit-constructor)
        this->initHandler ( functor );
    }

    __CDS_OptimalInline Function ( Function const & function ) noexcept {
        this->pManager = function.pManager;
        this->pCallableObject = this->pManager->creator ( function.pCallableObject );
    }

    __CDS_OptimalInline Function ( Function && function ) noexcept = delete;
    auto operator = ( Function && ) noexcept = delete;

    template < typename Functor, EnableIf < Type < Functor > :: isCallableObject > = 0 >
    __CDS_OptimalInline auto operator = ( Functor const & functor ) noexcept -> Function & {
        if ( this->pCallableObject == reinterpret_cast < GenericConstFunctorAddress > ( & functor ) ) return * this;
        if ( this->pManager != nullptr ) this->pManager->deleter ( this->pCallableObject );

        this->initHandler ( functor );

        return * this;
    }

    template < typename RequestedReturnType, typename ... RequestedArgumentTypes >
    constexpr auto operator = ( RequestedReturnType (* requestedStaticFunction ) ( RequestedArgumentTypes ... ) ) noexcept -> Function & {
        if ( this->pCallableObject == reinterpret_cast < GenericFunctorAddress > ( requestedStaticFunction ) ) return * this;
        if ( this->pManager != nullptr ) this->pManager->deleter ( this->pCallableObject );

        this->initHandler ( requestedStaticFunction );
        return * this;
    }

    __CDS_OptimalInline auto operator = ( Function const & function ) noexcept -> Function & {
        if ( this == & function ) return * this;
        if ( this->pCallableObject == function.pCallableObject ) return * this;

        if ( this->pManager != nullptr ) this->pManager->deleter ( this->pCallableObject );

        this->pManager = function.pManager;
        this->pCallableObject = this->pManager->creator ( function.pCallableObject );

        return * this;
    }

    __CDS_OptimalInline auto operator () ( ArgumentTypes ... arguments ) const noexcept (false) -> ReturnType {
        if ( this->pCallableObject == nullptr )
            throw NullPointerException ("Function Variable not assigned");

        return this->pManager->invoker ( this->pCallableObject, std :: forward < ArgumentTypes > (arguments ) ... );
    }

    __CDS_OptimalInline ~Function() noexcept override {
        if ( this->pManager != nullptr )
            this->pManager->deleter ( this->pCallableObject );
    }
};

template < typename ReturnType, typename ... ArgumentTypes >
class Function < ReturnType ( ArgumentTypes ... ) noexcept > : public Object {
private:
    using GenericFunctionAddress = void *;

    template < typename FunctionSignature, typename Functor >
    class FunctorHandler;

    template < typename FunctionSignature >
    class SubstitutingStaticHandler;

    using GenericFunctorAddress = void *;
    using GenericConstFunctorAddress = void const *;

    using Invoker = auto (*) ( GenericFunctorAddress, ArgumentTypes && ... ) noexcept -> ReturnType;
    using Creator = auto (*) ( GenericConstFunctorAddress ) noexcept -> GenericFunctorAddress;
    using Deleter = auto (*) ( GenericFunctorAddress ) noexcept -> void;

    struct Manager {
        Invoker invoker;
        Creator creator;
        Deleter deleter;
    };

    template < typename SubstitutedReturnType, typename SubstitutedFunctor, typename ... SubstitutedArgumentTypePack >
    class FunctorHandler < SubstitutedReturnType ( SubstitutedArgumentTypePack ... ) noexcept, SubstitutedFunctor > {
    public:
        using SubstitutedFunctorAddress             = SubstitutedFunctor *;
        using SubstitutedConstFunctorAddress        = SubstitutedFunctor const *;

        __CDS_OptimalInline static auto invoke (
                GenericFunctorAddress pObject,
                SubstitutedArgumentTypePack && ... argumentTypes
        ) noexcept -> SubstitutedReturnType {
            static auto pMemberFunction = & SubstitutedFunctor :: operator ();

            return (
                reinterpret_cast < SubstitutedFunctorAddress > ( pObject )
                    ->* pMemberFunction
            ) ( std :: forward < SubstitutedArgumentTypePack > ( argumentTypes ) ... );
        }

        __CDS_OptimalInline static auto clear ( GenericFunctorAddress pObject ) noexcept -> void {
            delete reinterpret_cast < SubstitutedFunctorAddress > ( pObject );
        }

        __CDS_OptimalInline static auto copy ( GenericConstFunctorAddress pObject ) noexcept -> GenericFunctorAddress {
            return reinterpret_cast < GenericFunctorAddress > ( new SubstitutedFunctor (
                * reinterpret_cast < SubstitutedConstFunctorAddress > ( pObject )
            ) );
        }

        constexpr static Manager manager = { invoke, copy, clear };
    };

    template < typename RequestedReturnType, typename ... RequestedArgumentTypes >
    class SubstitutingStaticHandler < RequestedReturnType ( RequestedArgumentTypes ... ) noexcept > {
    public:
        __CDS_OptimalInline static auto invoke (
                GenericFunctorAddress pFunction,
                ArgumentTypes && ... argumentTypes
        ) noexcept -> RequestedReturnType {
            auto castedFunction = reinterpret_cast < RequestedReturnType ( * ) ( RequestedArgumentTypes ... ) noexcept > ( pFunction );

            return castedFunction ( std :: forward < RequestedArgumentTypes > ( argumentTypes ) ... );
        }

        __CDS_OptimalInline static auto copy ( GenericConstFunctorAddress pFunction ) noexcept -> GenericFunctorAddress {
            return const_cast < GenericFunctorAddress > ( pFunction );
        }

        __CDS_OptimalInline static auto clear ( GenericFunctorAddress ) noexcept -> void {
            /// do nothing
        }

        constexpr static Manager manager { invoke, copy, clear };
    };

    GenericFunctionAddress      pCallableObject { nullptr };
    Manager const             * pManager { nullptr };

    template < typename Functor, EnableIf < Type < Functor > :: isCallableObject > = 0 >
    __CDS_OptimalInline auto initHandler ( Functor const & functor ) noexcept -> void {
        this->pManager = & FunctorHandler < ReturnType ( ArgumentTypes ... ) noexcept, Functor > :: manager;

        this->pCallableObject = this->pManager->creator ( reinterpret_cast < GenericConstFunctorAddress > ( & functor ) );
    }

    template < typename RequestedReturnType, typename ... RequestedArgumentTypes >
    __CDS_OptimalInline auto initHandler ( RequestedReturnType ( * requestedStaticFunction ) ( RequestedArgumentTypes ... ) ) noexcept -> void {
        this->pManager = & SubstitutingStaticHandler < RequestedReturnType ( RequestedArgumentTypes ... ) noexcept > :: manager;

        this->pCallableObject = this->pManager->creator ( reinterpret_cast < GenericFunctorAddress > ( requestedStaticFunction ) );
    }


public:
    constexpr Function () noexcept = default;

    template < typename RequestedReturnType, typename ... RequestedArgumentTypes >
    constexpr Function ( RequestedReturnType (* requestedStaticFunction ) ( RequestedArgumentTypes ... ) noexcept ) noexcept { // NOLINT(google-explicit-constructor)
        this->initHandler( requestedStaticFunction );
    }

    template < typename Functor, EnableIf < Type < Functor > :: isCallableObject > = 0 >
    __CDS_OptimalInline Function ( Functor const & functor ) noexcept { // NOLINT(google-explicit-constructor)
        this->initHandler ( functor );
    }

    __CDS_OptimalInline Function ( Function const & function ) noexcept {
        this->pManager = function.pManager;
        this->pCallableObject = this->pManager->creator ( function.pCallableObject );
    }

    __CDS_OptimalInline Function ( Function && function ) noexcept = delete;
    auto operator = ( Function && ) noexcept = delete;

    template < typename Functor, EnableIf < Type < Functor > :: isCallableObject > = 0 >
    __CDS_OptimalInline auto operator = ( Functor const & functor ) noexcept -> Function & {
        if ( this->pCallableObject == reinterpret_cast < GenericConstFunctorAddress > ( & functor ) ) return * this;
        if ( this->pManager != nullptr ) this->pManager->deleter ( this->pCallableObject );

        this->initHandler ( functor );

        return * this;
    }

    template < typename RequestedReturnType, typename ... RequestedArgumentTypes >
    constexpr auto operator = ( RequestedReturnType (* requestedStaticFunction ) ( RequestedArgumentTypes ... ) noexcept ) noexcept -> Function & {
        if ( this->pCallableObject == reinterpret_cast < GenericFunctorAddress > ( requestedStaticFunction ) ) return * this;
        if ( this->pManager != nullptr ) this->pManager->deleter ( this->pCallableObject );

        this->initHandler ( requestedStaticFunction );
        return * this;
    }

    __CDS_OptimalInline auto operator = ( Function const & function ) noexcept -> Function & {
        if ( this == & function ) return * this;
        if ( this->pCallableObject == function.pCallableObject ) return * this;

        if ( this->pManager != nullptr ) this->pManager->deleter ( this->pCallableObject );

        this->pManager = function.pManager;
        this->pCallableObject = this->pManager->creator ( function.pCallableObject );

        return * this;
    }

    __CDS_OptimalInline auto operator () ( ArgumentTypes ... arguments ) const noexcept (false) -> ReturnType {
        if ( this->pCallableObject == nullptr )
            throw NullPointerException ("Function Variable not assigned");

        return this->pManager->invoker ( this->pCallableObject, std :: forward < ArgumentTypes > (arguments ) ... );
    }

    __CDS_OptimalInline ~Function() noexcept override {
        if ( this->pManager != nullptr )
            this->pManager->deleter ( this->pCallableObject );
    }
};


#if __CDS_cpplang_CTAD_available == true

#include "FunctionDeduction.hpp"

#endif

#endif //CDS_FUNCTION_HPP
