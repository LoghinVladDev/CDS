//
// Created by loghin on 6/3/22.
//

#ifndef __CDS_STRING_HPP__
#define __CDS_STRING_HPP__

#include <CDS/Object>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

    namespace __hidden {
        namespace __impl {

            template < typename __CharType >
            class __BaseString;

            template < typename __CharType >
            class __BaseStringView;

        }
    }

    using String            = __hidden :: __impl :: __BaseString < char >;
    using WideString        = __hidden :: __impl :: __BaseString < wchar_t >;

    using StringView        = __hidden :: __impl :: __BaseStringView < char >;
    using WideStringView    = __hidden :: __impl :: __BaseStringView < wchar_t >;

}

#include "string/BaseString.hpp"

#endif // __CDS_STRING_HPP__
