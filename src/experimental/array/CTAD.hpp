//
// Created by loghin on 6/3/22.
//

#ifndef __CDS_EX_ARRAY_CTAD_HPP__
#define __CDS_EX_ARRAY_CTAD_HPP__

#if __CDS_cpplang_CTAD_available

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        Array (
                std :: initializer_list < T >
        ) -> Array < T >;

    }
}

#endif

#endif // __CDS_EX_ARRAY_CTAD_HPP__
