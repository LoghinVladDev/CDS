//
// Created by loghin on 6/3/22.
//

#ifndef __CDS_EX_STRING_HPP__
#define __CDS_EX_STRING_HPP__

#include <CDS/experimental/Object>

#include "string/BaseString.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

    namespace experimental {

        using String = hidden :: impl :: BaseString < char >;
        using WideString = hidden :: impl :: BaseString < wchar_t >;

    }
}

#endif // __CDS_EX_STRING_HPP__
