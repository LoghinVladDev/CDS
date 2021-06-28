//
// Created by loghin on 22.01.2021.
//

#ifndef CDS_OBJECT_HPP
#define CDS_OBJECT_HPP

#include "../prepro.h"
#include <ostream>

class String;

class Object {
public:
    virtual auto toString () const noexcept -> String;
    virtual auto equals (Object const & o) const noexcept -> bool { return this == & o; }
//    virtual auto operator == (Object const & o) const noexcept -> bool { return this == & o; }
//    virtual auto operator != (Object const & o) const noexcept -> bool { return ! ( * this == o ); }

    friend auto operator << (std::ostream &, Object const &) noexcept -> std::ostream &;
    virtual explicit operator String () const noexcept;

    virtual auto hash () const noexcept -> Index { return 0; }
    virtual auto copy () const noexcept -> Object * { return nullptr; }
    virtual ~Object () noexcept = default;
};

#include <CDS/Types>

namespace dataTypes {
    template<> auto hash<Object>(Object const &o) noexcept -> Index { return o.hash(); }
}

#include <CDS/String>

#endif //CDS_OBJECT_HPP
