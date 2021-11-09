//
// Created by loghin on 17.02.2021.
//

#ifndef CDS_STD_TYPES_H
#define CDS_STD_TYPES_H

namespace cds {

    using CString           = char *;
    using StringLiteral     = const char *;

    using uint8             = unsigned char;
    using uint16            = unsigned short int;
    using uint32            = unsigned int;
    using uint64            = unsigned long long int;

    using sint8             = signed char;
    using sint16            = signed short int;
    using sint32            = signed int;
    using sint64            = signed long long int;

    using Byte              = uint8;

    using Size              = uint64;
    using SignedSize        = sint64;

    using Index             = sint64;

    using AddressValueType  = uint64;

}

#endif //CDS_STD_TYPES_H
