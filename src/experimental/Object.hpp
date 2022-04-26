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

        class Object {
        public:
            __CDS_NoDiscard virtual auto toString () const noexcept -> String;
            __CDS_NoDiscard virtual auto equals (Object const & object) const noexcept -> bool {
                return this == & object;
            }

            friend auto operator << (std::ostream &, Object const &) noexcept -> std::ostream &;
            virtual explicit operator String () const noexcept;

            __CDS_NoDiscard virtual auto hash () const noexcept -> Index {
                return 0;
            }

            virtual ~Object () noexcept = default;
        };

    }

}

namespace cds {

    template <> auto hash < experimental :: Object > ( experimental :: Object const & object ) noexcept -> Index {
        return object.hash();
    }

}

#include <CDS/String>
#include "object/impl/Object.hpp"

#endif // __CDS_EX_OBJECT_HPP__
