//
// Created by loghin on 6/3/22.
//

#ifndef __CDS_EX_STRING_HPP__
#define __CDS_EX_STRING_HPP__

#include <CDS/experimental/Object>

#include "string/BaseString.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

    namespace experimental {

        using String            = __hidden :: __impl :: __BaseString < char >;
        using WideString        = __hidden :: __impl :: __BaseString < wchar_t >;

        using StringView        = __hidden :: __impl :: __BaseStringView < char >;
        using WideStringView    = __hidden :: __impl :: __BaseStringView < wchar_t >;

    }
}

#endif // __CDS_EX_STRING_HPP__
