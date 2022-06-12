//
// Created by loghin on 6/3/22.
//

#ifndef __CDS_EX_ARRAY_CTAD_HPP__
#define __CDS_EX_ARRAY_CTAD_HPP__

#if __CDS_cpplang_CTAD_available

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        Array (
                std :: initializer_list < __ElementType >
        ) -> Array < __ElementType >;

    }
}

#endif

#endif // __CDS_EX_ARRAY_CTAD_HPP__
