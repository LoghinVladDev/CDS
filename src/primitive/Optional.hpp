//
// Created by loghin on 26.01.2021.
//

#ifndef CDS_OPTIONAL_HPP
#define CDS_OPTIONAL_HPP

#include <CDS/pointer/UniquePointer>
#include <CDS/Memory>

namespace cds {

    template < typename T >
    class Optional : public Object {
    public:
        using Value                 = T;
        using ValueReference        = T &;
        using ValueConstReference   = T const &;

    private:
        UniquePointer<T> pObj;

    public:
        constexpr Optional() noexcept = default;
        __CDS_cpplang_NonConstConstexprMemberFunction Optional(Optional const & object) noexcept {
            * this = object;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction Optional(Optional && optional) noexcept :
                pObj ( std :: move ( optional.pObj ) ){

        }

        __CDS_cpplang_ConstexprDestructor ~Optional() noexcept override = default;

        __CDS_cpplang_ConstexprDynamicAllocation Optional ( ValueConstReference value ) noexcept : // NOLINT(google-explicit-constructor)
                pObj ( Memory :: instance().create < Value > (value ) ) {

        }

        __CDS_cpplang_ConstexprDynamicAllocation auto operator = ( ValueConstReference value ) noexcept -> Optional & {
            this->pObj.reset( Memory :: instance().create < Value > (value ));
            return * this;
        }

        constexpr auto operator -> () const noexcept -> UniquePointer<T> const & {
            return this->pObj;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator -> () noexcept -> UniquePointer<T> & {
            return this->pObj;
        }

        constexpr auto operator * () const noexcept (false) -> ValueReference {
            return * this->pObj;
        }

        __CDS_NoDiscard constexpr auto hasValue () const noexcept -> bool {
            return this->pObj != nullptr;
        }

        __CDS_NoDiscard constexpr auto isEmpty () const noexcept -> bool {
            return ! this->hasValue(); // NOLINT(clion-misra-cpp2008-5-3-1)
        }

        __CDS_NoDiscard constexpr auto isPresent () const noexcept -> bool {
            return this->hasValue();
        }

        constexpr auto value () const noexcept(false) -> ValueReference {
            return * this->pObj;
        }

        __CDS_MaybeUnused constexpr auto valueOr (ValueReference value) const noexcept -> ValueReference {
            return this->hasValue() ? this->value() : value;
        }

        __CDS_MaybeUnused constexpr auto valueOr (ValueConstReference value) const noexcept -> ValueConstReference {
            return this->hasValue() ? this->value() : value;
        }

        template < typename Action >
        __CDS_MaybeUnused __CDS_cpplang_ConstexprNonLiteralReturn auto ifPresent (Action const & action) const noexcept -> void {
            if ( this->isPresent() ) {
                action(this->pObj.valueAt());
            }
        }

        template < typename Action, typename EmptyAction >
        __CDS_MaybeUnused __CDS_cpplang_ConstexprNonLiteralReturn auto ifPresentOrElse ( Action const & action, EmptyAction const & onElse ) const noexcept -> void {
            if ( this->isPresent() ) {
                action(this->pObj.valueAt());
            } else {
                onElse();
            }
        }

        template < typename Predicate >
        __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned auto filter ( Predicate const & predicate ) const noexcept -> Optional {
            if ( this->isEmpty() ) {
                return * this;
            }

            return predicate (this->pObj.valueAt()) ? (*this) : Optional();
        }

        template < typename Mapper >
        __CDS_cpplang_ConstexprDestructor auto map ( Mapper const & mapper ) const noexcept -> Optional < ReturnOf < Mapper > > {
            if ( this->isEmpty() ) {
                return Optional < ReturnOf < Mapper> > ();
            }

            return Optional < ReturnOf < Mapper > > (mapper(this->pObj.valueAt()));
        }

        template < typename Supplier >
        __CDS_MaybeUnused __CDS_cpplang_ConstexprDestructor auto orSupply (Supplier const & supplier) const noexcept -> Optional {
            if ( this->isPresent() ) {
                return * this;
            }

            return supplier();
        }

        __CDS_MaybeUnused constexpr auto orElse (ValueConstReference other) const noexcept -> ValueConstReference {
            return this->isPresent() ? this->pObj.valueAt() : other;
        }

        __CDS_MaybeUnused constexpr auto orElse (ValueReference other) const noexcept -> ValueReference {
            return this->isPresent() ? this->pObj.valueAt() : other;
        }

        template < typename Supplier >
        __CDS_MaybeUnused constexpr auto orElseGet (Supplier const & supplier) const noexcept -> T {
            return this->isPresent() ? this->pObj.valueAt() : supplier();
        }

        constexpr explicit operator bool () const noexcept {
            return this->hasValue();
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto clear () noexcept -> Optional & {
            this->pObj.reset();
            return * this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (Optional const & object) noexcept -> Optional & {
            if ( this == & object ) {
                return * this;
            }

            if ( ! object.hasValue() ) { // NOLINT(clion-misra-cpp2008-5-3-1)
                if ( this->hasValue() ) {
                    this->pObj.reset();
                }

                return * this;
            }

            this->pObj.reset( Memory :: instance ().create < Value > ( * object.pObj ) );

            return * this;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (Optional && optional) noexcept -> Optional & {
            if ( this == & optional ) {
                return * this;
            }

            this->pObj = std :: move ( optional.pObj );
            return * this;
        }

        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto equals ( Object const & object ) const noexcept -> bool override {
            if ( this == & object ) {
                return true;
            }

            auto pOptional = dynamic_cast < Optional < T > const * > ( & object );
            if (pOptional == nullptr ) {
                return false;
            }

            return this->operator==(*pOptional);
        }

        constexpr auto operator == ( Optional const & optional ) const noexcept -> bool {
            return
                this == & optional ||
                Type < T > :: compare (this->value(), optional.value() );
        }

        __CDS_NoDiscard __CDS_OptionalInline auto toString() const noexcept -> String final {
            std::stringstream oss;
            oss << "| ";
            if ( this->hasValue() ) {
                oss << this->value();
            } else {
                oss << "none";
            }

            oss << " |";
            return {oss.str()};
        }

        __CDS_NoDiscard __CDS_cpplang_ConstexprDynamicAllocation auto copy () const noexcept -> Optional * override {
            return Memory :: instance().create < Optional >( * this );
        }
    };

}

#if __CDS_cpplang_CTAD_available

namespace cds {

    template < typename T >
    Optional ( T ) -> Optional < T >;

}

#endif

__CDS_RegisterParseTypeTemplateT(Optional) // NOLINT(clion-misra-cpp2008-8-0-1)

#endif //CDS_OPTIONAL_HPP
