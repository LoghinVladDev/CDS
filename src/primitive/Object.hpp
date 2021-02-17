//
// Created by loghin on 22.01.2021.
//

#ifndef CDS_OBJECT_HPP
#define CDS_OBJECT_HPP
#include <String.hpp>

class Object {
public:
    virtual auto toString () const noexcept -> String = 0;
    virtual auto operator == (Object const & o) const noexcept -> bool { return this == & o; }
    virtual auto operator != (Object const & o) const noexcept -> bool { return ! ( * this == o ); }

    friend auto operator << ( std::ostream & out, const Object & o ) noexcept -> std::ostream & {
        return ( out << o.toString() );
    }

    virtual auto hash () const noexcept -> Index { return 0; }
};


#endif //CDS_OBJECT_HPP
