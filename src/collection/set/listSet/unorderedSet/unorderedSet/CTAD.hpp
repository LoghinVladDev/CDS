//
// Created by loghin on 6/15/22.
//

#ifndef __CDS_UNORDERED_SET_CTAD_HPP__
#define __CDS_UNORDERED_SET_CTAD_HPP__

#if __CDS_cpplang_CTAD_available

namespace cds {

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    UnorderedSet (
            std :: initializer_list < __ElementType >
    ) -> UnorderedSet < __ElementType >;

}

#endif

#endif // __CDS_UNORDERED_SET_CTAD_HPP__
