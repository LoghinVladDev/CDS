//
// Created by loghin on 26.01.2021.
//

#ifndef CDS_OPTIONAL_HPP
#define CDS_OPTIONAL_HPP

#include <CDS/Pointer>

template <class T>
class Optional final : public Object {
public:
    using Value                 = T;
    using ValueReference        = T &;
    using ValueConstReference   = T const &;

private:
    UniquePointer<T> pObj;

public:
    Optional() noexcept = default;
    Optional(Optional const & o) noexcept {
        * this = o;
    }
    ~Optional() noexcept final = default;

    Optional ( ValueConstReference v ) noexcept : pObj ( new Value( v ) ) { } // NOLINT(google-explicit-constructor)
    Optional & operator = ( ValueConstReference v ) noexcept {
        this->pObj.reset(new Value ( v ));
        return * this;
    }

    auto operator -> () const noexcept -> UniquePointer<T> const & { return this->pObj; }
    auto operator -> () noexcept -> UniquePointer<T> & { return this->pObj; }
    auto operator * () const noexcept (false) -> ValueReference { return * this->pObj; }

    [[nodiscard]] inline auto hasValue () const noexcept -> bool { return ! pObj.isNull(); }
    [[nodiscard]] inline auto isEmpty () const noexcept -> bool { return ! this->hasValue(); }
    [[nodiscard]] inline auto isPresent () const noexcept -> bool { return this->hasValue(); }

    inline auto value () const noexcept(false) -> ValueConstReference { return * this->pObj; }
    inline auto value () noexcept(false) -> ValueReference { return * this->pObj; }
    inline auto valueOr (ValueReference v) noexcept -> ValueReference { return this->hasValue() ? this->value() : v; }
    inline auto valueOr (ValueConstReference v) noexcept -> ValueConstReference { return this->hasValue() ? this->value() : v; }

    template < typename Action >
    inline auto ifPresent (Action const & action) const noexcept -> void {
        if ( isPresent() ) action ( pObj.valueAt() );
    }

    template < typename Action, typename EmptyAction >
    inline auto ifPresentOrElse ( Action const & action, EmptyAction const & onElse ) const noexcept -> void {
        if ( isPresent() ) action ( pObj.valueAt() );
        else onElse ();
    }

    template < typename Predicate >
    inline auto filter ( Predicate const & predicate ) const noexcept -> Optional {
        if ( isEmpty() ) return * this;
        return predicate (pObj.valueAt()) ? (*this) : Optional();
    }

    template < typename Mapper >
    inline auto map ( Mapper const & mapper ) const noexcept -> Optional < returnOf < Mapper > > {
        if ( isEmpty() ) return Optional < returnOf < Mapper > > ();
        return Optional < returnOf < Mapper > > (mapper(this->pObj.valueAt()));
    }

    template < typename Supplier >
    inline auto orSupply (Supplier const & supplier) const noexcept -> Optional {
        if ( isPresent() ) return * this;
        return supplier();
    }

    auto orElse (T const & other) const noexcept -> T const & { return isPresent() ? this->pObj.valueAt() : other; }

    template < typename Supplier >
    auto orElseGet (Supplier const & supplier) const noexcept -> T { return isPresent() ? this->pObj.valueAt() : supplier(); }

    inline explicit operator bool () const noexcept { return this->hasValue(); }

    inline auto clear () noexcept -> Optional & {
        this->pObj.reset();
        return * this;
    }

    Optional & operator = (Optional const & o) noexcept {
        if ( this == & o )
            return * this;

        if ( ! o.hasValue() ) {
            if ( hasValue() )
                pObj.reset();
            return * this;
        }

        pObj.reset( new Value ( * o.pObj ) );

        return * this;
    }

    auto equals ( Object const & o ) const noexcept -> bool override {
        if ( this == & o ) return true;
        auto p = dynamic_cast < decltype (this) > ( & o );
        if ( p == nullptr ) return false;

        return this->operator==(*p);
    }

    auto operator == ( Optional const & o ) const noexcept -> bool {
        if ( & o == this ) return true;

        return Type < T > :: deepCompare ( this->value(), o.value() );
    }

    [[nodiscard]] auto toString() const noexcept -> String final {
        std::stringstream oss;
        oss << "| ";
        if ( this->hasValue() )
            oss << this->value();
        else
            oss << "none";
        oss << " |";
        return String(oss.str());
    }

    [[nodiscard]] auto copy () const noexcept -> Optional * override {
        return new Optional( * this );
    }
};

template < typename T >
Optional ( T ) -> Optional < T >;

#endif //CDS_OPTIONAL_HPP
