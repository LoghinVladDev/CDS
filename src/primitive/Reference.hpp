//
// Created by loghin on 27.01.2021.
//

#ifndef CDS_REFERENCE_HPP
#define CDS_REFERENCE_HPP

#include <CDS/Object>
#include <CDS/Traits>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility { // NOLINT(modernize-concat-nested-namespaces)
        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace referenceImpl {

                template < typename T >
                constexpr T & hiddenRef(T & unused) noexcept { return unused; }

                template < typename T >
                __CDS_MaybeUnused constexpr auto hiddenRef(T && ) -> void = delete;

            }
        }
    }
}

#include <CDS/Pointer>

namespace cds {

    template < typename T >
    class Reference : public Object {
    public:
        using Pointer = T *;
        using Value = T;

    private:
        Pointer p;

    public:

        template < class V, class = decltype (
            utility :: hidden :: referenceImpl :: hiddenRef < T > ( std::declval < V > () ), // NOLINT(clion-misra-cpp2008-5-18-1)
            std :: enable_if <
                ! std::is_same < // NOLINT(clion-misra-cpp2008-5-3-1)
                    Reference,
                    RemoveConst < RemoveReference < V >
                >
            > :: value > ()
        ) > constexpr Reference ( V && value ) noexcept ( noexcept ( utility :: hidden :: referenceImpl :: hiddenRef < T > (std :: forward < V > (value )))) : // NOLINT(google-explicit-constructor,bugprone-forwarding-reference-overload)
                p ( std :: addressof ( utility :: hidden :: referenceImpl :: hiddenRef < T > ( std :: forward < V > (value )))) {

        }

        constexpr Reference(Reference const &) noexcept = default;
        __CDS_cpplang_NonConstConstexprMemberFunction Reference & operator = ( Reference const & ) noexcept = default;
        __CDS_cpplang_ConstexprDestructor ~Reference () noexcept override = default;

        constexpr operator T & () const noexcept { // NOLINT(google-explicit-constructor)
            return * this->p;
        }

        constexpr T & get () const noexcept {
            return * this->p;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction operator T & () noexcept { // NOLINT(google-explicit-constructor)
            return *p;
        }

        __CDS_cpplang_NonConstConstexprMemberFunction T & get () noexcept(false) {
            return *p;
        }

        constexpr auto operator == (Reference const & reference) const noexcept -> bool {
            return
                this == & reference ||
                Type < T > :: compare (reference.get(), this->get() );
        }

        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto equals ( Object const & object ) const noexcept -> bool final {
            if ( this == & object ) {
                return true;
            }

            auto pReference = dynamic_cast < Reference < T > const * > ( & object );
            if (pReference == nullptr ) {
                return false;
            }

            return this->operator==(*pReference);
        }

        __CDS_NoDiscard __CDS_OptionalInline auto toString() const noexcept -> String final {
            std::stringstream oss;

            Type < T > :: streamPrint ( oss << "< " << (std::is_const<T>::value ? "const " : "") << "& of 0x" << std::hex
                << reinterpret_cast < AddressValueType > ( p ) << std::dec << " : " , *p ) << " >";
            return oss.str();
        }

        __CDS_NoDiscard __CDS_OptimalInline auto copy () const noexcept -> Reference < T > * override {
            return Memory :: instance () .create < Reference < T > > ( * this );
        }

    #if __CDS_cpplang_core_version >= __CDS_cpplang_core_version_17

        template <class...ArgTypes>
        constexpr std::invoke_result_t<T&, ArgTypes...> operator () (ArgTypes&&... args) const {
            return std::invoke(get(), std::forward<ArgTypes>(args)...);
        }

    #else

    #endif

    };

}

#if __CDS_cpplang_CTAD_available == true

namespace cds {

    template <class T>
    Reference(T&) -> Reference<T>;

}

#endif

__CDS_RegisterParseTypeTemplateT(Reference) // NOLINT(clion-misra-cpp2008-8-0-1)

#endif //CDS_REFERENCE_HPP
