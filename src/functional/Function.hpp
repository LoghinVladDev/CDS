//
// Created by loghin on 28.10.2021.
//

#ifndef CDS_FUNCTION_HPP
#define CDS_FUNCTION_HPP

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
    using GenericMemberFunctionType = ReturnType ( Utility::UndefinedClass:: * ) ( ArgumentTypes ... );

    using GenericFunctionAddress = void *;

    template < typename FunctionSignature, typename Functor >
    class FunctorHandler;

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

    using StaticFunction = ReturnType (*) ( ArgumentTypes ... );

    template < typename SubstitutedReturnType, typename SubstitutedFunctor, typename ... SubstitutedArgumentTypePack >
    class FunctorHandler < SubstitutedReturnType ( SubstitutedArgumentTypePack ... ), SubstitutedFunctor > {
    public:
        using SubstitutedFunctorFunctionType        = SubstitutedReturnType ( SubstitutedFunctor :: * ) ( SubstitutedArgumentTypePack && ... );
        using SubstitutedFunctorAddress             = SubstitutedFunctor *;
        using SubstitutedConstFunctorAddress        = SubstitutedFunctor const *;

        using GenericRefMemberFunctionType          = ReturnType ( Utility::UndefinedClass:: * ) ( ArgumentTypes && ... );

        __CDS_OptimalInline static auto invoke (
                GenericFunctorAddress pObject,
                SubstitutedArgumentTypePack && ... argumentTypes
        ) noexcept ( false ) -> SubstitutedReturnType {
            static auto pMemberFunction = & SubstitutedFunctor :: operator ();

            auto pCastedObject = reinterpret_cast < SubstitutedFunctorAddress > ( pObject );

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

    GenericFunctionAddress      pCallableObject { nullptr };
    Manager const             * pManager { nullptr };

    template < typename Functor, EnableIf < Type < Functor > :: isCallableObject > = 0 >
    __CDS_OptimalInline auto initHandler ( Functor const & functor ) noexcept -> void {
        this->pManager = & FunctorHandler < ReturnType ( ArgumentTypes ... ), Functor > :: manager;

        this->pCallableObject = this->pManager->creator ( reinterpret_cast < GenericConstFunctorAddress > ( & functor ) );
    }

public:
    constexpr Function () noexcept = default;

    constexpr Function ( StaticFunction function ) noexcept : // NOLINT(google-explicit-constructor)
            pCallableObject ( reinterpret_cast < GenericFunctionAddress > ( function ) ) {

    }

    template < typename TemplatedFunction, EnableIf < Type < TemplatedFunction > :: isFunction > = 0 >
    __CDS_OptimalInline Function ( TemplatedFunction const & function ) noexcept : // NOLINT(google-explicit-constructor)
            pCallableObject ( reinterpret_cast < GenericFunctionAddress > ( function ) ){

    }

    __CDS_OptimalInline Function ( Function const & function ) noexcept {
        if ( function.pManager == nullptr ) {
            this->pCallableObject = function.pCallableObject;
        } else {
            this->pManager = function.pManager;
            this->pCallableObject = this->pManager->creator ( function.pCallableObject );
        }
    }

    __CDS_OptimalInline Function ( Function && function ) noexcept = delete;
    auto operator = ( Function && ) noexcept = delete;

    template < typename Functor, EnableIf < Type < Functor > :: isCallableObject > = 0 >
    __CDS_OptimalInline Function ( Functor const & functor ) noexcept { // NOLINT(google-explicit-constructor)
        this->initHandler ( functor );
    }

    template < typename Functor, EnableIf < Type < Functor > :: isCallableObject > = 0 >
    __CDS_OptimalInline auto operator = ( Functor const & functor ) noexcept -> Function & {
        if ( this->pCallableObject == reinterpret_cast < GenericConstFunctorAddress > ( & functor ) ) return * this;
        if ( this->pManager != nullptr ) this->pManager->deleter ( this->pCallableObject );

        this->initHandler ( functor );

        return * this;
    }

    template < typename TemplatedFunction, EnableIf < Type < TemplatedFunction > :: isFunction > = 0 >
    __CDS_OptimalInline auto operator = ( TemplatedFunction const & function ) noexcept -> Function & {
        if ( this->pCallableObject == reinterpret_cast < GenericFunctorAddress > ( function ) ) return * this;
        if ( this->pManager != nullptr ) {

            this->pManager->deleter ( this->pCallableObject );
            this->pManager = nullptr;
        }

        this->pCallableObject = reinterpret_cast < GenericFunctorAddress > ( function );
        return * this;
    }

    constexpr auto operator = ( StaticFunction function ) noexcept -> Function & {
        if ( this->pCallableObject == reinterpret_cast < GenericFunctorAddress > ( function ) ) return * this;
        if ( this->pManager != nullptr ) {

            this->pManager->deleter ( this->pCallableObject );
            this->pManager = nullptr;
        }

        this->pCallableObject = reinterpret_cast < GenericFunctorAddress > ( function );
        return * this;
    }

    __CDS_OptimalInline auto operator = ( Function const & function ) noexcept -> Function & {
        if ( this == & function ) return * this;
        if ( this->pCallableObject == function.pCallableObject ) return * this;

        if ( this->pManager != nullptr ) this->pManager->deleter ( this->pCallableObject );

        if ( function.pManager == nullptr ) {
            this->pCallableObject = function.pCallableObject;
            this->pManager = nullptr;
        } else {
            this->pManager = function.pManager;
            this->pCallableObject = this->pManager->creator ( function.pCallableObject );
        }

        return * this;
    }

    __CDS_OptimalInline auto operator () ( ArgumentTypes ... arguments ) const noexcept (false) -> ReturnType {
        if ( this->pCallableObject == nullptr )
            throw NullPointerException ("Function Variable not assigned");

        if ( this->pManager == nullptr )
            return ( * reinterpret_cast < StaticFunction > ( this->pCallableObject ) ) ( std :: forward < ArgumentTypes > ( arguments ) ... );
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
    using GenericMemberFunctionType = ReturnType ( Utility::UndefinedClass:: * ) ( ArgumentTypes ... ) noexcept;

    using GenericFunctionAddress = void *;

    template < typename FunctionSignature, typename Functor >
    class FunctorHandler;

    using GenericFunctorAddress = void *;
    using GenericConstFunctorAddress = void const *;

    using Invoker = auto (*) (GenericFunctorAddress, ArgumentTypes && ... ) noexcept -> ReturnType;
    using Creator = auto (*) ( GenericConstFunctorAddress ) noexcept -> GenericFunctorAddress;
    using Deleter = auto (*) ( GenericFunctorAddress ) noexcept -> void;

    struct Manager {
        Invoker invoker;
        Creator creator;
        Deleter deleter;
    };

    using StaticFunction = ReturnType (*) ( ArgumentTypes ... );

    template < typename SubstitutedReturnType, typename SubstitutedFunctor, typename ... SubstitutedArgumentTypePack >
    class FunctorHandler < SubstitutedReturnType ( SubstitutedArgumentTypePack ... ), SubstitutedFunctor > {
    public:
        using SubstitutedFunctorFunctionType    = SubstitutedReturnType ( SubstitutedFunctor :: * ) ( SubstitutedArgumentTypePack && ... ) noexcept;
        using SubstitutedFunctorAddress         = SubstitutedFunctor *;
        using SubstitutedConstFunctorAddress    = SubstitutedFunctor const *;

        __CDS_OptimalInline static auto invoke (
                GenericFunctorAddress pObject,
                SubstitutedArgumentTypePack && ... argumentTypes
        ) noexcept -> SubstitutedReturnType {
            static auto pMemberFunction = reinterpret_cast < GenericMemberFunctionType > ( & SubstitutedFunctor :: operator () );

            return (
                reinterpret_cast < SubstitutedFunctorAddress > ( pObject )
                    ->* reinterpret_cast < SubstitutedFunctorFunctionType > ( pMemberFunction )
            ) ( std :: forward < SubstitutedArgumentTypePack > (argumentTypes ) ... );
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

    GenericFunctionAddress      pCallableObject { nullptr };
    Manager const             * pManager { nullptr };

    template < typename Functor, EnableIf < Type < Functor > :: isCallableObject > = 0 >
    __CDS_OptimalInline auto initHandler ( Functor const & functor ) noexcept -> void {
        this->pManager = & FunctorHandler < ReturnType ( ArgumentTypes ... ), Functor > :: manager;

        this->pCallableObject = this->pManager->creator ( reinterpret_cast < GenericConstFunctorAddress > ( & functor ) );
    }

public:
    constexpr Function () noexcept = default;

    constexpr Function ( StaticFunction function ) noexcept : // NOLINT(google-explicit-constructor)
            pCallableObject ( reinterpret_cast < GenericFunctionAddress > ( function ) ) {

    }

    __CDS_OptimalInline Function ( Function const & function ) noexcept {
        if ( function.pManager == nullptr ) {
            this->pCallableObject = function.pCallableObject;
        } else {
            this->pManager = function.pManager;
            this->pCallableObject = this->pManager->creator ( function.pCallableObject );
        }
    }

    template < typename TemplatedFunction, EnableIf < Type < TemplatedFunction > :: isFunction > = 0 >
    __CDS_OptimalInline Function ( TemplatedFunction const & function ) noexcept : // NOLINT(google-explicit-constructor)
            pCallableObject ( reinterpret_cast < GenericFunctionAddress > ( function ) ){

    }

    template < typename Functor, EnableIf < Type < Functor > :: isCallableObject > = 0 >
    __CDS_OptimalInline Function ( Functor const & functor ) noexcept { // NOLINT(google-explicit-constructor)
        this->initHandler ( functor );
    }

    template < typename Functor, EnableIf < Type < Functor > :: isCallableObject > = 0 >
    __CDS_OptimalInline auto operator = ( Functor const & functor ) noexcept -> Function & {
        if ( this->pCallableObject == reinterpret_cast < GenericConstFunctorAddress > ( & functor ) ) return * this;
        if ( this->pManager != nullptr ) this->pManager->deleter ( this->pCallableObject );

        this->initHandler ( functor );

        return * this;
    }

    constexpr auto operator = ( StaticFunction function ) noexcept -> Function & {
        if ( this->pCallableObject == reinterpret_cast < GenericFunctorAddress > ( function ) ) return * this;
        if ( this->pManager != nullptr ) {

            this->pManager->deleter ( this->pCallableObject );
            this->pManager = nullptr;
        }

        this->pCallableObject = reinterpret_cast < GenericFunctorAddress > ( function );
        return * this;
    }

    template < typename TemplatedFunction, EnableIf < Type < TemplatedFunction > :: isFunction > = 0 >
    __CDS_OptimalInline auto operator = ( TemplatedFunction const & function ) noexcept -> Function & {
        if ( this->pCallableObject == reinterpret_cast < GenericFunctorAddress > ( function ) ) return * this;
        if ( this->pManager != nullptr ) {

            this->pManager->deleter ( this->pCallableObject );
            this->pManager = nullptr;
        }

        this->pCallableObject = reinterpret_cast < GenericFunctorAddress > ( function );
        return * this;
    }

    __CDS_OptimalInline auto operator = ( Function const & function ) noexcept -> Function & {
        if ( this == & function ) return * this;
        if ( this->pCallableObject == function.pCallableObject ) return * this;

        if ( this->pManager != nullptr ) this->pManager->deleter ( this->pCallableObject );

        if ( function.pManager == nullptr ) {
            this->pCallableObject = function.pCallableObject;
            this->pManager = nullptr;
        } else {
            this->pManager = function.pManager;
            this->pCallableObject = this->pManager->creator ( function.pCallableObject );
        }

        return * this;
    }

    __CDS_OptimalInline auto operator () ( ArgumentTypes ... arguments ) const noexcept (false) -> ReturnType {
        if ( this->pCallableObject == nullptr )
            throw NullPointerException ("Function Variable not assigned");

        if ( this->pManager == nullptr )
            return ( * reinterpret_cast < StaticFunction > ( this->pCallableObject ) ) ( std :: forward < ArgumentTypes > ( arguments ) ... );
        return this->pManager->invoker ( this->pCallableObject, std :: forward < ArgumentTypes > ( arguments ) ... );
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
