//
// Created by loghin on 22.01.2021.
//

#ifndef __CDS_EX_OBJECT_HPP__
#define __CDS_EX_OBJECT_HPP__

#include "../prepro.h"
#include <ostream>
#include <CDS/Hasher>

namespace cds {

    class String; // NOLINT(cppcoreguidelines-virtual-class-destructor)

    namespace experimental {

        /**
         * @class Base class of all CDS objects
         */
        class Object {

        public:
            /**
             * @brief String conversion function, used to obtain String representation of the object
             * @exceptsafe
             * @return String = string representation
             */
            __CDS_NoDiscard virtual auto toString () const noexcept -> String;

        public:
            /**
             * @brief Explicit Comparison Function with generic CDS/Object
             * @param object : Object cref = Constant Reference to an Object-derived instance
             * @exceptsafe
             * @return bool = true if objects are equal, false otherwise
             */
            __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto equals (
                    Object const & object
            ) const noexcept -> bool;

        public:
            /**
             * @brief Operator << overload for std :: ostream types, used to easily print String representation of object
             * @param out : std :: ostream ref = Reference to a std :: ostream type or type-derived object
             * @param object : Object cref = Constant Reference to an Object-derived instance
             * @exceptsafe
             * @return std :: ostream ref = Reference to received 'out' parameter
             */
            friend auto operator << (
                    std :: ostream        & out,
                    Object          const &
            ) noexcept -> std::ostream &;

        public:
            /**
             * @brief String cast operator, used to obtain String representation of the object
             * @exceptsafe
             * @return String = string representation
             */
            virtual explicit operator String () const noexcept;

        public:
            /**
             * @brief Hash function
             * @exceptsafe
             * @return Index = hash code value of the instance
             */
            __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr virtual auto hash () const noexcept -> Index;

        public:
            /**
             * @brief implicit destructor
             * @exceptsafe
             */
            virtual ~Object () noexcept = default;
        };

    }

}

#include <CDS/String>
#include "object/impl/Object.hpp"

#endif // __CDS_EX_OBJECT_HPP__
