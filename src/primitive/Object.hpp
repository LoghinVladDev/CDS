//
// Created by loghin on 22.01.2021.
//

#ifndef CDS_OBJECT_HPP
#define CDS_OBJECT_HPP

#include "../prepro.h"
#include <ostream>
#include <CDS/Hasher>

namespace cds {

    class String;

    class Object {
    public:
        __CDS_NoDiscard virtual auto toString () const noexcept -> String;
        __CDS_NoDiscard virtual auto equals (Object const & o) const noexcept -> bool {
            return this == & o;
        }

        friend auto operator << (std::ostream &, Object const &) noexcept -> std::ostream &;
        virtual explicit operator String () const noexcept;

        __CDS_NoDiscard virtual auto hash () const noexcept -> Index {
            return 0;
        }

        __CDS_NoDiscard virtual auto copy () const noexcept -> Object * {
            return nullptr;
        }

        virtual ~Object () noexcept = default;
    };

}

#include <CDS/Types>

namespace cds {

    template<> auto hash<Object>(Object const &o) noexcept -> Index {
        return o.hash();
    }

}

#include <CDS/String>

#endif //CDS_OBJECT_HPP
