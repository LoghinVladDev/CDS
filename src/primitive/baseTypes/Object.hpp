/*
 * Created by loghin on 22.01.2021.
 */

#ifndef __CDS_OBJECT_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_OBJECT_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include "../../prepro.h"
#include <ostream>

namespace cds {

    namespace __hidden {        /* NOLINT(bugprone-reserved-identifier, modernize-concat-nested-namespaces, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __CharType >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            class __BaseString;                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

        } /* namespace __impl */
    } /* namespace __hidden */

    /**
     * @class Base class of all CDS objects
     */
    class Object {

    protected: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr Object () noexcept = default;

    protected: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr Object (
                Object const &
        ) noexcept = default;

    protected: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr Object (
                Object &&
        ) noexcept = default;

    protected: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                Object const &
        ) noexcept -> Object & = default;

    protected: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                Object &&
        ) noexcept -> Object & = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief implicit destructor
         * @exceptsafe
         */
        __CDS_cpplang_ConstexprDestructor virtual ~Object () noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief String conversion function, used to obtain String representation of the object
         * @exceptsafe
         * @return String = string representation
         */
        __CDS_NoDiscard virtual auto toString () const noexcept(false) -> __hidden :: __impl :: __BaseString < char >;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Explicit Comparison Function with generic CDS/Object
         * @param object : Object cref = Constant Reference to an Object-derived instance
         * @exceptsafe
         * @return bool = true if objects are equal, false otherwise
         */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto equals (
                Object const & object
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Operator << overload for std :: ostream types, used to easily print String representation of object
         * @param out : std :: ostream ref = Reference to a std :: ostream type or type-derived object
         * @param object : Object cref = Constant Reference to an Object-derived instance
         * @exceptsafe
         * @return std :: ostream ref = Reference to received 'out' parameter
         */
        friend auto operator << (
                std :: ostream        & out,
                Object          const & object
        ) noexcept(false) -> std::ostream &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief String cast operator, used to obtain String representation of the object
         * @exceptsafe
         * @return String = string representation
         */
        __CDS_Explicit operator __hidden :: __impl :: __BaseString < char > () const noexcept(false);

    public: /* NOLINT(readability-redundant-access-specifiers) */
        /**
         * @brief Hash function
         * @exceptsafe
         * @return Index = hash code value of the instance
         */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto hash () const noexcept -> Size;
    };

} /* namespace cds */

#include <CDS/String>                                   /* NOLINT(llvm-include-order) */
#include "object/impl/HashBase.hpp"                     /* NOLINT(llvm-include-order) */
#include "object/impl/Object.hpp"                       /* NOLINT(llvm-include-order) */
#include "../../shared/object/impl/ObjectToString.hpp"  /* NOLINT(llvm-include-order) */

#endif /* __CDS_OBJECT_HPP__ */
