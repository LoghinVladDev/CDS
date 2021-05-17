//
// Created by loghin on 26.01.2021.
//

#ifndef CDS_POINTER_HPP
#define CDS_POINTER_HPP

#include <CDS/Object>
#include <sstream>

template <class T>
class PointerBase : public Object {
public:
    using PointerType           = std::size_t;
    using Value                 = T;
    using ValueReference        = T &;
    using Pointer               = T *;

protected:
    mutable Pointer pObj {nullptr};

public:
    class NullPointerException : public std::exception {
    public:
        [[nodiscard]] auto what() const noexcept -> StringLiteral override {
            return "Tried de-referencing a null pointer";
        }
    };

    PointerBase() noexcept = default;
    explicit PointerBase(Pointer p) noexcept : pObj(p) {}

    ~PointerBase() noexcept override = default;

    auto copy () const noexcept -> PointerBase * override = 0;

    auto operator == (Object const & o) const noexcept -> bool final {
        if ( this == & o ) return true;
        auto p = dynamic_cast < PointerBase<T> const * > ( & o );
        if ( p == nullptr ) return false;
        if ( this->pObj == p->pObj ) return true;
        if ( this->pObj == nullptr || p->pObj == nullptr ) return false;
        return (* p->pObj) == (* this->pObj);
    }

    inline auto operator * () const noexcept (false) -> ValueReference {
        if ( pObj == nullptr ) throw NullPointerException();
        return * pObj;
    }

    constexpr inline auto isNull () const noexcept -> bool { return pObj == nullptr; }
    constexpr inline auto operator -> () const noexcept (false) -> Pointer {
        if ( pObj == nullptr )
            throw NullPointerException();

        return pObj;
    }

    constexpr inline explicit operator bool () const noexcept { return isNull(); }
    constexpr inline auto get () const noexcept -> Pointer { return pObj; }
#if __cpp_constexpr >= 201907
    constexpr inline virtual auto release () noexcept -> Pointer { auto p = pObj; pObj = nullptr; return p; }
    constexpr inline virtual auto reset ( Pointer p = nullptr ) noexcept -> void { auto oldP = pObj; pObj = p; delete oldP; }
#else
    inline virtual auto release () noexcept -> Pointer { auto p = pObj; pObj = nullptr; return p; }
    inline virtual auto reset ( Pointer p = nullptr ) noexcept -> void { auto oldP = pObj; pObj = p; delete oldP; }
#endif

    [[nodiscard]] auto toString() const noexcept -> String final {
        std::stringstream oss;

        oss << "< 0x" << std::hex << reinterpret_cast < PointerType > ( pObj ) << std::dec << " : ";
        if ( pObj == nullptr )
            oss << "null";
        else
            oss << (* pObj);
        oss << " >";

        return String(oss.str());
    }
};

template <class T>
class UniquePointer final : public PointerBase<T> {
public:
    UniquePointer() noexcept = default;
    UniquePointer(typename PointerBase<T>::Pointer p) noexcept : PointerBase<T>(p) { }

    UniquePointer( UniquePointer const & o ) noexcept = delete;
    UniquePointer( UniquePointer & o ) noexcept : PointerBase<T>(o.release()) { }
    UniquePointer( UniquePointer && o ) noexcept : PointerBase<T>(o.release()) { }

    auto copy () const noexcept -> UniquePointer * override {
        return nullptr;
    }

    inline UniquePointer & operator = ( UniquePointer && p ) noexcept {
        if ( &p == this ) return * this;

        this->reset(p.release());
        return * this;
    }

    inline UniquePointer & operator = ( UniquePointer & p ) noexcept {
        if ( &p == this ) return * this;

        this->reset(p.release());

        return * this;
    }

    inline UniquePointer & operator = ( decltype(nullptr) ) noexcept {
        this->reset();
        return * this;
    }

    ~UniquePointer() noexcept final { this->reset(); }
};

template <class T>
class SharedPointer final : public PointerBase<T> {
private:
    struct SharedPointerControlBlock {
        Size ownerCount {0ull};
    };

    SharedPointerControlBlock * pControl { nullptr };

public:
    SharedPointer() noexcept = default;
    SharedPointer(SharedPointer const & p) noexcept : PointerBase<T>(p.pObj) {
        this->pControl = p.pControl;
        p.pControl->ownerCount ++;
    }

    auto copy () const noexcept -> SharedPointer * override {
        return new SharedPointer(* this);
    }

    SharedPointer(typename PointerBase<T>::Pointer p) noexcept : PointerBase<T>(p) {
        this->pControl = new SharedPointerControlBlock { 1ull };
    }

    SharedPointer & operator = ( SharedPointer const & o ) noexcept {
        if ( this == & o )
            return * this;

        this->pObj = o.pObj;
        this->pControl = o.pControl;
        if ( this->pControl != nullptr )
            this->pControl->ownerCount++;

        return * this;
    }

    ~SharedPointer() noexcept final {
        this->reset();
    }

    auto release () noexcept -> typename PointerBase<T>::Pointer final {
        auto p = this->pObj;
        this->reset();
        return p;
    }

    auto reset ( typename PointerBase<T>::Pointer p = nullptr ) noexcept -> void final {
        auto pVal = this->pObj;
        this->pObj = p;

        if ( this->pControl != nullptr ) {
            this->pControl->ownerCount --;
            if ( this->pControl->ownerCount == 0 ) {
                delete this->pControl;
                delete pVal;
            }

            this->pControl = nullptr;
        }

        if ( this->pObj != nullptr )
            this->pControl = new SharedPointerControlBlock { 1ull };
    }
};

template <class T>
class ForeignPointer final : public PointerBase<T> {
public:
    ForeignPointer() noexcept : PointerBase<T>(nullptr) {}
    ForeignPointer(typename PointerBase<T>::Pointer p) noexcept : PointerBase<T>(p) {}

    ForeignPointer( ForeignPointer const & o ) noexcept : PointerBase<T>(o.pObj) {}
    ForeignPointer( ForeignPointer && o ) noexcept : PointerBase<T>(o.release()) {}

    auto copy () const noexcept -> ForeignPointer * override {
        return new ForeignPointer ( * this );
    }

    inline ForeignPointer & operator = ( ForeignPointer const & p ) noexcept {
        if ( &p == this ) return * this;

        this->reset( p.pObj );
        return * this;
    }

    inline ForeignPointer & operator = ( ForeignPointer && o ) noexcept {
        if ( &o == this ) return * this;

        this->reset( o.release() );
        return * this;
    }

    constexpr inline auto reset ( typename PointerBase<T>::Pointer p = nullptr ) noexcept -> void final { this->pObj = p; }
};

template < typename T >
UniquePointer ( T * ) -> UniquePointer < T >;

template < typename T >
SharedPointer ( T * ) -> SharedPointer < T >;

template < typename T >
ForeignPointer ( T * ) -> ForeignPointer < T >;


#endif //CDS_POINTER_HPP
