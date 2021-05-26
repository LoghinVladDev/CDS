//
// Created by loghin on 27.01.2021.
//

#ifndef CDS_REFERENCE_HPP
#define CDS_REFERENCE_HPP

#include <utility>
#include <functional>

namespace dataTypes::refWrapper {
    template <class T>
    constexpr T & hiddenRef ( T & t ) noexcept { return t; }

    template <class T>
    void hiddenRef ( T && ) = delete;
}

#include <CDS/Pointer>
template <class T>
class Reference : public Object {
public:
    using Pointer = T *;
    using Value = T;

private:
    Pointer p;

public:

    template < class V, class = decltype (
    dataTypes::refWrapper::hiddenRef<T>(std::declval<V>()),
            std::enable_if_t < ! std::is_same < Reference,
#if __cpp_lib_remove_cvref >= 201711
                    std::remove_cvref_t <V>
#else
                    std::remove_cv_t<std::remove_reference_t<V>>
#endif
            > ::value >()
    ) > constexpr Reference ( V && v ) noexcept(noexcept(dataTypes::refWrapper::hiddenRef<T>(std::forward<V>(v)))) : // NOLINT(google-explicit-constructor,bugprone-forwarding-reference-overload)
            p ( std::addressof( dataTypes::refWrapper::hiddenRef<T>(std::forward<V>(v)))) {

    }

    Reference(Reference const &) noexcept = default;
    Reference & operator = ( Reference const & ) noexcept = default;
    ~Reference () noexcept override = default;

    constexpr operator T& () const noexcept { return *p; } // NOLINT(google-explicit-constructor)
    constexpr T& get () const noexcept { return *p; }

    constexpr operator T& () noexcept { return *p; } // NOLINT(google-explicit-constructor)
    constexpr T& get () noexcept(false) { return *p; }

    inline auto operator == (const Object & o) const noexcept -> bool final {
        if ( this == & o ) return true;
        auto a = dynamic_cast < Reference const * > ( & o );
        if ( a == nullptr ) return false;
        return a->get() == this->get();
    }

    [[nodiscard]] auto toString() const noexcept -> String final {
#if defined(CDS_GLM)
        constexpr auto isVec = [] {
            if constexpr (
                    std::is_same <int, Value>::type::value ||
                    std::is_same <int, Value>::type::value ||
                    std::is_same <int, Value>::type::value ||
                    std::is_same <int, Value>::type::value
            )
                return true;
            return false;
        };
#endif

        std::stringstream oss;
        oss << "< " << (std::is_const<T>::value ? "const " : "") << "& of 0x" << std::hex
            << reinterpret_cast < typename PointerBase<T>::PointerType > ( p ) << std::dec << " : " <<
            #if defined(CDS_GLM)
            (isVec () ? String(*p) : (*p))
            #else
            (*p)
            #endif
            << " >";
        return String(oss.str());
    }

    template <class...ArgTypes>
    constexpr std::invoke_result_t<T&, ArgTypes...> operator () (ArgTypes&&... args) const {
        return std::invoke(get(), std::forward<ArgTypes>(args)...);
    }
};

template <class T>
Reference(T&) -> Reference<T>;


#endif //CDS_REFERENCE_HPP
