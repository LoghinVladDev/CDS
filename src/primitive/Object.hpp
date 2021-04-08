//
// Created by loghin on 22.01.2021.
//

#ifndef CDS_OBJECT_HPP
#define CDS_OBJECT_HPP

#include "../prepro.h"
#include <CDS/String>

class Object {
public:
    virtual auto toString () const noexcept -> String = 0;
    virtual auto operator == (Object const & o) const noexcept -> bool { return this == & o; }
    virtual auto operator != (Object const & o) const noexcept -> bool { return ! ( * this == o ); }

    friend auto operator << ( std::ostream & out, const Object & o ) noexcept -> std::ostream & {
        return ( out << o.toString() );
    }

    virtual inline explicit operator String () const noexcept { return this->toString(); }

    virtual auto hash () const noexcept -> Index { return 0; }
    virtual auto copy () const noexcept -> Object * { return nullptr; }
    virtual ~Object () noexcept = default;
};


#endif //CDS_OBJECT_HPP
